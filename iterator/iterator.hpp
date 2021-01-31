#ifndef __CONST_HASH_MAP_ITERATOR__
#define __CONST_HASH_MAP_ITERATOR__

#include "const_iterator.hpp"

template <typename HashMap>
class hash_map_iterator : public const_hash_map_iterator<HashMap>
{
public:
    using value_type = typename HashMap::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type *;
    using reference = value_type &;
    using list_iterator_type = typename HashMap::ListType::iterator;

    hash_map_iterator() = default;
    hash_map_iterator(size_t bucket, list_iterator_type list_it, HashMap *hash_map) : const_hash_map_iterator<HashMap>(bucket, list_it, hash_map)
    {
    }

    reference operator*()
    {
        return const_cast<reference>(*this->m_list_iterator);
    }
    pointer operator->()
    {
        return const_cast<pointer>(&(*this->m_list_iterator));
    }

    hash_map_iterator<HashMap> &
    operator++()
    {
        this->increment();
        return *this;
    }
    hash_map_iterator<HashMap> &operator++(int)
    {
        auto old_it = *this;
        this->increment();
        return old_it;
    };

    hash_map_iterator<HashMap> &operator--()
    {
        this->decrement();
        return *this;
    }
    hash_map_iterator<HashMap> &operator--(int)
    {
        auto old_it = *this;
        this->decrement();
        return old_it;
    }
};

#endif //HASH_MAP_ITERATOR