#ifndef avlset_hpp
#define avlset_hpp
#include "avltree.hpp"

template <class K>
class AVLSet {
    private:
        using avl_const_iterator = ConstAVLIterator<K>;
        using avl_iterator = AVLIterator<K>;
        using avl_reverse_iterator = ReverseAVLIterator<K>;
        using _m_tree = AVLTree<K>;
        _m_tree avl_tree;
    public:
        AVLSet() {

        }
        bool empty() const {
            return avl_tree.empty();
        }
        int size() const {
            return avl_tree.size();
        }
        void insert(K key) {
            avl_tree.insert(key);
        }
        void erase(K key) {
            avl_tree.erase(key);
        }
        bool contains(K key) {
            return avl_tree.contains(key);
        }
        avl_iterator find(K key) {
            return avl_tree.find(key);
        }
        avl_iterator lower_bound(K key) {
            return avl_tree.lower_bound(key);
        }
        avl_iterator upper_bound(K key) {
            return avl_tree.upper_bound(key);
        }
        avl_iterator begin() {
            return avl_tree.begin();
        }
        avl_iterator end() {
            return avl_tree.end();
        }
        avl_reverse_iterator rbegin() {
            return avl_tree.rbegin();
        }
        avl_reverse_iterator rend() {
            return avl_tree.end();
        }
        avl_const_iterator cbegin() {
            return avl_tree.cbegin();
        }
        avl_const_iterator cend() {
            return avl_tree.cend();
        }
        bool validate() {
            return avl_tree.validate();
        }
};



#endif