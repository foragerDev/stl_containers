#ifndef _HASH_MAP_
#define _HASH_MAP_

#include "../iterator/const_iterator.hpp"
#include "../iterator/iterator.hpp"
#include <list>
#include <vector>
#include <functional>
template <typename Key, typename T, typename KeyEqual = std::equal_to<>, typename Hash = std::hash<Key>>
class hash_map
{

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<Key, T>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using hash_map_type = hash_map<Key, T, KeyEqual, Hash>;
    using iterator = hash_map_iterator<hash_map_type>;
    using const_iterator = const_hash_map_iterator<hash_map_type>;

    friend class const_hash_map_iterator<hash_map_type>;
    friend class hash_map_iterator<hash_map_type>;

    virtual ~hash_map() = default; // destructor

    explicit hash_map(const KeyEqual &equal = KeyEqual(), size_t buckets = 101, const Hash &hash = Hash());
    hash_map(const hash_map<Key, T, KeyEqual, Hash> &src) = default;
    hash_map(hash_map<Key, T, KeyEqual, Hash> &&src) noexcept = default;

    // copy constructor
    hash_map<Key, T, KeyEqual, Hash> &operator=(const hash_map<Key, T, KeyEqual, Hash> &src);
    hash_map<Key, T, KeyEqual, Hash> &operator=(hash_map<Key, T, KeyEqual, Hash> &&src) noexcept;

    void insert(const value_type &value);
    void erase(const key_type &value);
    void clear() noexcept;

    value_type *find(const key_type &key);
    const value_type *find(const key_type &key) const;

    T &operator[](const key_type &key);

    void swap(hash_map<Key, T, KeyEqual, Hash> &other) noexcept;
    void swap(hash_map<Key, T, KeyEqual, Hash> &first, hash_map<Key, T, KeyEqual, Hash> &second) noexcept;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    // Unimplemented
    iterator rbegin();
    const_iterator rbegin() const;
    const_iterator crbegin() const;

    iterator rend();
    const_iterator rend() const;
    const_iterator crend() const;

    bool operator==(hash_map<Key, T, KeyEqual, Hash> &other) const;
    bool operator!=(hash_map<Key, T, KeyEqual, Hash> &other) const;

    size_type size() const;
    size_type max_size() const;
    bool empty() const;

private:
    using ListType = std::list<value_type>;
    std::vector<ListType> m_buckets;
    size_t m_size = 0;
    KeyEqual m_equal;
    Hash m_hash;

    std::pair<typename hash_map<Key, T, KeyEqual, Hash>::ListType::iterator, size_t> find_element(const key_type &key);
};

#include "hash_map.tpp"
#endif //HASH_MAP