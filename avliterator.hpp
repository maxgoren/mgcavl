#ifndef rankbasediterator_hpp
#define rankbasediterator_hpp
#include "avlnode.hpp"

template <class K>
class AVLIterator {
    private:
        avlnode<K>* tree;
        int pos;
        K nullInfo;
        avlnode<K>* fetch(avlnode<K>* h, int k) {
            if (h == nullptr)
                return nullptr;
            int t = h->left == nullptr ? 0:h->left->n;
            if (t > k) return fetch(h->left, k);
            else if (t < k) return fetch(h->right, k-t-1);
            else return h;
        }
    public:
        AVLIterator(avlnode<K>* rootptr, int p) {
            tree = rootptr;
            pos = p;
        }
        bool done() {
            return tree != nullptr && pos >= tree->size();
        }
        K& get() {
            return fetch(tree, pos)->info;
        }
        void next() {
            pos++;
        }
        AVLIterator& operator++() {
            ++pos;
            return *this;
        }
        AVLIterator& operator++(int) {
            AVLIterator it = *this;
            ++it;
            return *this;
        }
        AVLIterator& operator--() {
            --pos;
            return *this;
        }
        AVLIterator& operator--(int) {
            AVLIterator it = *this;
            --it;
            return *this;
        }
        K& operator*() {
            avlnode<K>* h = fetch(tree, pos);
            if (h == nullptr)
                return nullInfo;
            return h->info;
        }
        bool operator==(const AVLIterator& oit) const {
            return tree == oit.tree && pos == oit.pos;
        }
        bool operator!=(const AVLIterator& oit) const {
            return !(*this==oit);
        }
};

template <class K>
class ConstAVLIterator : public AVLIterator<K> {
    private:
        using base_iter = AVLIterator<K>;
    public:
        ConstAVLIterator(avlnode<K>* curr, int p) {
            base_iter::tree = curr;
            base_iter::pos = p;
        }
        const K& operator*() const {
            avlnode<K>* h = fetch(base_iter::tree, base_iter::pos);
            if (h == nullptr)
                return base_iter::nullInfo;
            return const_cast<K>(h->info);
        }
        bool operator==(const ConstAVLIterator& oit) const {
            return base_iter::tree == oit.tree && base_iter::pos == oit.pos;
        }
        bool operator!=(const ConstAVLIterator& oit) const {
            return !(*this==oit);
        }        
};

template <class K>
class ReverseAVLIterator {
    private:
        avlnode<K>* tree;
        int pos;
        K nullInfo;
        avlnode<K>* fetch(avlnode<K>* h, int k) {
            if (h == nullptr)
                return nullptr;
            int t = h->left ? h->left->n:0;
            if (t > k) return fetch(h->left, k);
            else if (t < k) return fetch(h->right, k-t-1);
            else return h;
        }
    public:
        ReverseAVLIterator(avlnode<K>* rootptr, int p) {
            tree = rootptr;
            pos = p;
        }
        bool done() {
            return tree != nullptr && pos >= tree->size();
        }
        K& get() {
            return fetch(tree, pos)->info;
        }
        void next() {
            pos++;
        }
        ReverseAVLIterator& operator--() {
            ++pos;
            return *this;
        }
        ReverseAVLIterator& operator--(int) {
            ReverseAVLIterator it = *this;
            ++it;
            return *this;
        }
        ReverseAVLIterator& operator++() {
            --pos;
            return *this;
        }
        ReverseAVLIterator& operator++(int) {
            ReverseAVLIterator it = *this;
            --it;
            return *this;
        }
        K& operator*() {
            avlnode<K>* h = fetch(tree, pos);
            if (h == nullptr)
                return nullInfo;
            return h->info;
        }
        bool operator==(const ReverseAVLIterator& oit) const {
            return tree == oit.tree && pos == oit.pos;
        }
        bool operator!=(const ReverseAVLIterator& oit) const {
            return !(*this==oit);
        }
};

template <class K>
class ReverseConstAVLIterator : public ReverseAVLIterator<K> {
    private:
        using base_iter = ReverseAVLIterator<K>;
    public:
        ReverseConstAVLIterator(avlnode<K>* curr, int p) {
            base_iter::tree = curr;
            base_iter::pos = p;
        }
        const K& operator*() const {
            avlnode<K>* h = fetch(base_iter::tree, base_iter::pos);
            if (h == nullptr)
                return base_iter::nullInfo;
            return const_cast<K>(h->info);
        }
        bool operator==(const ReverseConstAVLIterator& oit) const {
            return base_iter::tree == oit.tree && base_iter::pos == oit.pos;
        }
        bool operator!=(const ReverseConstAVLIterator& oit) const {
            return !(*this==oit);
        }        
};

#endif