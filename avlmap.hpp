#ifndef avlmap_hpp
#define avlmap_hpp
#include "kvpair.hpp"
#include "avltree.hpp"

template <class K, class V>
constexpr bool std::operator<(const KVPair<K,V>& lhs, const KVPair<K,V>& rhs) {
    return lhs.key() < rhs.key();
}

template <class K, class V>
class AVLMap {
    private:
        using value_type = KVPair<K,V>;
        using avl_iterator = AVLIterator<value_type>;
        using avl_reverse_iterator = ReverseAVLIterator<value_type>;
        using avl_const_iterator = ConstAVLIterator<value_type>;
        using _m_tree = AVLTree<value_type>;
        value_type nullInfo;
        _m_tree avl_tree;
    public:
        AVLMap() {

        }
        bool empty() const {
            return avl_tree.empty();
        }
        int size() const {
            return avl_tree.size();
        }
        void emplace(K key, V value) {
            avl_tree.insert(value_type(key, value));
        }
        void insert(value_type item) {
            avl_tree.insert(item);
        }
        void erase(K key) {
            avl_tree.erase(value_type(key, V()));
        }
        V& at(K key) {
            if (avl_tree.get(value_type(key,V())).empty()) {
                avl_tree.insert(value_type(key,V()));
            }
            return avl_tree.get(value_type(key,V())).value();
        }
        bool contains(K key) {
            return avl_tree.get(value_type(key, V()));
        }
        avl_iterator find(K key) {
            return avl_tree.find(value_type(key, V()));
        }
        avl_iterator lower_bound(K key) {
            return avl_tree.lower_bound(value_type(key,V()));
        }
        avl_iterator upper_bound(K key) {
            return avl_tree.upper_bound(value_type(key,V()));
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
            return avl_tree.rend();
        }
        bool validate() {
            return avl_tree.validate();
        }
        V& operator[](const K& key) {
            return at(key);
        }
};

#endif