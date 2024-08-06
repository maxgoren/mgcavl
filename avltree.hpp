#ifndef avltree_hpp
#define avltree_hpp
#include <iostream>
#include "avlnode.hpp"
#include "avliterator.hpp"
using namespace std;

const bool LEFT = true;
const bool RIGHT = false;

template <class K, class cmpType = std::less<K>>
class AVLTree {
    private:
        using iter = AVLIterator<K>;
        using const_iter = ConstAVLIterator<K>;
        using reverse_iter = ReverseAVLIterator<K>;
        using reverse_const_iter = ReverseConstAVLIterator<K>;
        using node_type = avlnode<K>;
        using link_type = node_type*;
        K nullInfo;
        link_type root;
        int count;
        int size(link_type h) { return h == nullptr ? 0:h->n; }
        int height(link_type h) { return h == nullptr ? -1:h->height; } 
        avlnode<K>* select(avlnode<K>* h, int k) {
            if (h == nullptr)
                return nullptr;
            int t = size(h->left);
            if (t > k) return select(h->left, k);
            else if (t < k) return select(h->right, k-t-1);
            else return h;
        }
        int rank(link_type h, K key) {
            if (h == nullptr)
                return -1;
            if (key < h->info) return rank(h->left, key);
            else if (h->info < key) return rank(h->right, key) + 1 + size(h->left);
            else return size(h->left);
        }
        link_type rotL(link_type h) {
            link_type x = h->right; h->right = x->left; x->left = h;
            h->height = 1 + max(height(h->left), height(h->right));
            x->height = 1 + max(height(x->left), height(x->right));
            x->n = h->n;
            h->n = 1 + size(h->left) + size(h->right);
            return x;
        }
        link_type rotR(link_type h) {
            link_type x = h->left; h->left = x->right; x->right = h;
            x->height = h->height;
            h->height = 1 + max(height(h->left), height(h->right));
            x->height = 1 + max(height(x->left), height(x->right));
            x->n = h->n;
            h->n = 1 + size(h->left) + size(h->right);
            return x;
        }
        link_type rotate(link_type h, bool dir) {
            if (dir) {
                h = rotL(h);
            } else {
                h = rotR(h);
            }
            return h;
        }
        link_type doubleRotate(link_type h, bool dir) {
            if (dir) {
                h->right = rotR(h->right);
            } else {
                h->left = rotL(h->left);
            }
            return rotate(h, dir);
        }
        int balanceFactor(link_type h) {
            return height(h->left) - height(h->right);
        }
        link_type balanceAVL(link_type h) {
            h->height = 1 + max(height(h->left), height(h->right));
            h->n = 1 + size(h->left) + size(h->right);
            if (balanceFactor(h) < -1) {
                if (balanceFactor(h->right) > 0)
                    h = doubleRotate(h, LEFT);
                 else
                    h = rotate(h, LEFT);
            } else if (balanceFactor(h) > 1) {
                if (balanceFactor(h->left) < 0)
                    h = doubleRotate(h, RIGHT);
                else
                    h = rotate(h, RIGHT);
            }
            return h;
        }
        link_type put(link_type h, K k) {
            if (h == nullptr) {
                count++;
                return new node_type(k);
            }
            if (k == h->info) {
                h->info = k;
                return h;
            }
            if (cmpType()(k, h->info)) {
                h->left = put(h->left, k);
            } else {
                h->right = put(h->right, k);
            }
            return balanceAVL(h);
        }
        void preorder(link_type h) {
            if (h != nullptr) {
                cout<<h->info<<" ";
                preorder(h->left);
                preorder(h->right);
            }
        }
        link_type get(link_type h, K key) {
            if (h == nullptr)
                return nullptr;
            if (cmpType()(key, h->info)) return get(h->left, key);
            else if (cmpType()(h->info, key)) return get(h->right, key);
            else return h;
        }
        int max(int a, int b) {
            return (a > b) ? a:b;
        }
        link_type max(link_type h) {
            if (h == nullptr || h->right == nullptr)
                return h;
            return max(h->right);
        }
        link_type min(link_type h) {
            if (h == nullptr || h->left == nullptr)
                return h;
            return min(h->left);
        }
        link_type inorderSuccessor(link_type h) {
            return min(h->right);
        }
        link_type inorderPredecessor(link_type h) {
            return max(h->left);
        }
        link_type eraseMax(link_type h) {
            if (h == nullptr)
                return h;
            if (h->right == nullptr)
                return h->left;
            h->right = eraseMax(h->right);
            return balanceAVL(h);
        }
        link_type eraseMin(link_type h) {
            if (h == nullptr)
                return h;
            if (h->left == nullptr) {
                return h->right;
            }
            h->left = eraseMin(h->left);
            return balanceAVL(h);
        }
        link_type removeNode(link_type h) {
            link_type tmp = h;
            if (h->right == nullptr) {
                h = h->left;
            } else if (h->left == nullptr) {
                h = h->right;
            } else {
                if (size(h->right) > size(h->left)) {
                    h = inorderSuccessor(tmp);
                    h->right = eraseMin(tmp->right);
                    h->left = tmp->left;
                } else {
                    h = inorderPredecessor(tmp);
                    h->left = eraseMax(tmp->left);
                    h->right = tmp->right;
                }
            }
            delete tmp; 
            count--;
            return h;
        }
        link_type erase(link_type h, K key) {
            if (h == nullptr)
                return h;
            if (cmpType()(key, h->info))      h->left = erase(h->left, key);
            else if (cmpType()(h->info, key)) h->right = erase(h->right, key);
            else h = removeNode(h);
            return h == nullptr ? h:balanceAVL(h);
        }
        link_type ceil(link_type h, K key) {
            if (h == nullptr)
                return nullptr;
            if (key == h->info) {
                return h;
            }
            if (cmpType()(h->info, key))
                return ceil(h->right, key);
            link_type sc = ceil(h->left, key);
            return (sc != nullptr && cmpType()(sc->info, key)) ? sc:h; 
        }
        link_type floor(link_type h, K key) {
            if (h == nullptr)
                return nullptr;
            if (key == h->info)
                return h;
            if (cmpType()(h->info, key))
                return floor(h->left, key);
            link_type sf = floor(h->right, key);
            return (sf != nullptr) ? sf:h;
        }
        void cleanup(link_type h) {
            if (h != nullptr) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
        link_type makeCopy(link_type h) {
            if (h == nullptr) {
                return nullptr;
            }
            link_type t = new avlnode<K>(h->info.key(), h->info.value());
            t->height = h->height;
            t->n = h->n;
            t->left = makeCopy(h->left);
            t->right = makeCopy(h->right);
            return t;
        }
        bool validate(link_type h) {
            if (h == nullptr)
                return true;
            if (h->left && cmpType()(h->info, h->left->info))
                return false;
            if (h->right && cmpType()(h->right->info, h->info))
                return false;
            if (height(h->left) > height(h->right) + 1)
                return false;
            if (height(h->right) > height(h->left) + 1)
                return false;
            return validate(h->left) && validate(h->right);
        }
    public:
        AVLTree() {
            root = nullptr;
            count = 0;
        }
        AVLTree(const AVLTree& avlt) {
            *this = avlt;
        }
        ~AVLTree() {
            cleanup(root);
        }
        bool empty() {
            return root == nullptr;
        }
        int size() const {
            return count;
        }
        void clear() {
            cleanup(root);
            count = 0;
            root = nullptr;
        }
        K& select(int k) {
            return select(root, k);
        }
        int rank(K key) {
            return rank(root, key);
        }
        void insert(K k) {
            root = put(root, k);
        }
        void erase(K k) {
            root = erase(root, k);
        }
        K& get(K key) {
            link_type h = get(root, key);
            if (h == nullptr)
                return nullInfo;
            return h->info;
        }
        bool contains(K key) {
            return get(key).empty() == false;
        }
        AVLIterator<K> lower_bound(K key) {
            link_type h = floor(root, key);
            return get(key) == nullInfo ? AVLIterator<K>(root, rank(root,key)+1):AVLIterator<K>(root, rank(root,key));
        }
        AVLIterator<K> upper_bound(K key) {
            link_type h = ceil(root, key);
            return h == nullptr ? AVLIterator(root, rank(root,key)):AVLIterator(root, rank(root, key)+1);
        }
        AVLIterator<K> find(K key) {
            int keyrank = rank(root, key);
            return keyrank < 0 ? end():AVLIterator<K>(root, keyrank);
        }
        AVLIterator<K> begin() {
            return AVLIterator<K>(root, 0);
        }
        AVLIterator<K> end() {
            return AVLIterator<K>(root, count);
        }
        ReverseAVLIterator<K> rbegin() {
            return ReverseAVLIterator<K>(root, count-1);
        }
        ReverseAVLIterator<K> rend() {
            return ReverseAVLIterator<K>(root, -1);
        }
        ConstAVLIterator<K> cbegin() {
            return ConstAVLIterator<K>(root, 0);
        }
        ConstAVLIterator<K> cend() {
            return ConstAVLIterator<K>(root, count);
        }
        AVLTree& operator=(const AVLTree& avlt) const {
            if (this != &avlt) {
                cleanup(root);
                count = avlt.count;
                root = makeCopy(avlt.root);
            }
            return *this;
        }
        bool validate() {
            return validate(root);
        }
};


#endif