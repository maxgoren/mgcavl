#ifndef avlnode_hpp
#define avlnode_hpp

template <class K>
struct avlnode {
    K info;
    int height;
    int n;
    avlnode* left;
    avlnode* right;
    avlnode(K k) : info(k), height(-1), n(1), left(nullptr), right(nullptr) { }
};

template <class K>
int size(avlnode<K>*& h) {
    return (h == nullptr) ? 0:h->n;
}

template <class K>
int height(avlnode<K>*& h) {
    return (h == nullptr) ? -1:h->height;
}

#endif