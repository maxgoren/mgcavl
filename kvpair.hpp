#ifndef kvpair_hpp
#define kvpair_hpp

/*
    Key/Value pair container
      - default constructable with test for emptyness 
      - key is immutable
*/

template <class K, class V>
class KVPair {
    private:
        K _key;
        V _value;
        bool _empty;
    public:
        KVPair(K k, V v) {
            _key = k;
            _value = v;
            _empty = false;
        }
        KVPair() {
            _empty = true; 
            _key = K();
            _value = V();
        }
        void clear() { 
            _empty = true;
            _key = K();
            _value = V();
        }
        const K& key() const { 
            return _key; 
        }
        V& value() { 
            return _value; 
        }
        bool empty() { 
            return _empty; 
        }
        void setValue(V val) {
            _value = val;
        }
        bool operator==(const KVPair& op) const {
            return _key == op._key;
        }
        bool operator!=(const KVPair& op) const {
            return !(*this == op);
        }
};

#endif