#include <algorithm>
#include "hash_map.hpp"

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>::hash_map(const KeyEqual& keyEqual, size_t size, const Hash& hash):
    m_buckets(size), m_equal(keyEqual), m_hash(hash)
    {
        if(size == 0){
            throw std::invalid_argument("Number of buckets should be greater than zero");
        }
}


template<typename Key, typename T, typename KeyEqual, typename Hash>
std::pair<typename hash_map<Key, T, KeyEqual, Hash>::ListType::iterator, size_t> hash_map<Key, T, KeyEqual, Hash>::find_element(const key_type& key){
    size_t bucket = m_hash(key) % m_buckets.size();
    auto iter = std::find_if(
        std::begin(m_buckets[bucket]),
        std::end(m_buckets[bucket]),
        [this, &key](const auto& element){
            return m_equal(element.first, key);
            }
        );
    return std::make_pair(iter, bucket);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
typename hash_map<Key, T, KeyEqual, Hash>::value_type* 
hash_map<Key, T, KeyEqual, Hash>::find(const key_type& key){
    auto[it, bucket] = find_element(key);
    if(it == end(m_buckets[bucket])){
        return nullptr;
    }
    return &(*it);
}


template<typename Key, typename T, typename KeyEqual, typename Hash>
const typename hash_map<Key, T, KeyEqual, Hash>::value_type*
hash_map<Key, T, KeyEqual, Hash>::find(const key_type& key) const{
    return const_cast<hash_map<Key, T, KeyEqual, Hash>*>(this)->find(key);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
T& hash_map<Key, T, KeyEqual, Hash>::operator[](const Key& key){
    auto[it, bucket] = find_element(key);
    if(it == end(m_buckets[bucket])){
        m_size++;
        m_buckets[bucket].push_back(std::make_pair(key, T()));
        return m_buckets[bucket].back().second;
    }
    else  return it->second;
}
// Insert value in the container
template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::insert(const value_type& value){
    auto[it, bucket] = find_element(value.first);
    if(it == end(m_buckets[bucket])){
        return;
    }
    else {
        m_size++;
        m_buckets[bucket].push_back(value);
    }
}

//erase one element from the container
template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::erase(const key_type& key){
    auto[it, bucket] = find_element(key);
    if(it != end(m_buckets[bucket])){
        m_size++;
        m_buckets[bucket].erase(it);
    }
}

// Remove all the elements for the container
template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::clear() noexcept{
    for(auto& bucket: m_buckets){
        bucket.clear();
    }
    m_size = 0;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::swap(hash_map<Key, T, KeyEqual, Hash>& other) noexcept{
    using std::swap;

    swap(m_size, other.m_size);
    swap(m_buckets, other.m_buckets);
    swap(m_equal, other.m_equal);
    swap(m_hash, other.m_hash);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
void hash_map<Key, T, KeyEqual, Hash>::swap(
    hash_map<Key, T, KeyEqual, Hash>& first,
    hash_map<Key, T, KeyEqual, Hash>& second) noexcept{
    
    first.swap(second);
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>& hash_map<Key, T, KeyEqual, Hash>::operator=(
    const hash_map<Key, T, KeyEqual, Hash>& rhs){
    if(this == rhs){
        return *this;
    }

    // Copy swap idiom
    auto copy = rhs;
    swap(copy);
    return *this;
}

template<typename Key, typename T, typename KeyEqual, typename Hash>
hash_map<Key, T, KeyEqual, Hash>& hash_map<Key, T, KeyEqual, Hash>::operator=(
    hash_map<Key,T, KeyEqual, Hash>&& rhs) noexcept {
    swap(rhs);
    return *this;
}
