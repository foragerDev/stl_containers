#ifndef __HASH_MAP__
#define __HASH_MAP__

#include <list>
#include <vector>
#include <functional>

template <typename Key, typename T, typename KeyEqual=std::equal_to<>, typename Hash=std::hash<Key>>
class hash_map{

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<Key, T>;

    virtual ~hash_map() = default; // destructor

    explicit hash_map(const KeyEqual& equal = KeyEqual(), size_t buckets=101, const Hash& hash = Hash());
    hash_map(const hash_map<Key, T, KeyEqual, Hash>& src) = default;
    hash_map(hash_map<Key, T, KeyEqual, Hash>& src) noexcept = default;
    
    // copy constructor
    hash_map<Key, T, KeyEqual, Hash>& operator=(const hash_map<Key, T, KeyEqual, Hash>& src);
    hash_map<Key, T, KeyEqual, Hash>& operator=(hash_map<Key, T, KeyEqual, Hash>&& src) noexcept;

    void insert(const value_type& value);
    void erase(const key_type& value);
    void clear() noexcept;

    value_type* find(const key_type& key);
    const value_type* find(const key_type& key) const;

    T& operator[](const key_type& key);

    void swap(hash_map<Key, T, KeyEqual, Hash>& other) noexcept;
    void swap(hash_map<Key, T, KeyEqual, Hash>& first, hash_map<Key, T, KeyEqual, Hash>&second) noexcept;

private:
    using ListType = std::list<value_type>;
    std::vector<ListType> m_buckets;
    size_t m_size = 0;
    KeyEqual m_equal;
    Hash m_hash;

    std::pair<typename hash_map<Key, T, KeyEqual, Hash>::ListType::iterator, size_t> find_element(const key_type& key);
};

#include "hash_map.tpp"
#endif //HASH_MAP