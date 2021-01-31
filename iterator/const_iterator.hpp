#ifndef _CONST_HASH_MAP_ITERATOR_
#define _CONST_HASH_MAP_ITERATOR_

template <typename HashMap>
class const_hash_map_iterator
{
public:
    using value_type = typename HashMap::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type *;
    using reference = value_type &;
    using list_iterator_type = typename HashMap::ListType;

    const_hash_map_iterator() = default;
    const_hash_map_iterator(std::size_t bucket, list_iterator_type list_it, const HashMap *hash_map)
        : m_bucket_index(bucket),
          m_list_iterator(list_it),
          m_hash_map(hash_map)
    {
    }

    const value_type &operator*() const
    {
        return *m_list_iterator;
    };
    const value_type *operator->() const
    {
        return &(*m_list_iterator);
    }

    const_hash_map_iterator<HashMap> &operator++()
    {
        increment();
        return *this;
    } // pre increment
    const_hash_map_iterator<HashMap> &operator++(int)
    {
        auto old_it = *this;
        increment();
        return old_it;
    } // post increment

    const_hash_map_iterator<HashMap> &operator--()
    {
        decrement();
        return *this;
    }; // pre decrement
    const_hash_map_iterator<HashMap> &operator--(int)
    {
        auto old_it = *this;
        decrement();
        return old_it;
    } // post decrement

    bool operator==(const const_hash_map_iterator<HashMap> &rhs) const
    {
        return (m_hash_map == rhs.m_hash_map &&
                    m_list_iterator == rhs.m_list_iterator &&
                    m_bucket_index = rhs.m_bucket_index);
    }
    bool operator!=(const const_hash_map_iterator<HashMap> &rhs) const
    {
        return !(*this == rhs);
    }

protected:
    size_t m_bucket_index = 0;
    list_iterator_type m_list_iterator;
    const HashMap *m_hash_map = nullptr;

    void increment()
    {
        ++m_list_iterator;
        auto &buckets = m_hash_map->m_buckets;
        if (m_list_iterator == end(buckets[m_bucket_index]))
        {
            for (size_t i = m_bucket_index + 1; i < buckets.size(); ++i)
            {
                if (!buckets[i].empty())
                {
                    m_list_iterator = std::begin(buckets[i]);
                    m_bucket_index = 1;
                    return;
                }
            }
        }
        m_bucket_index = buckets.size() - 1;
        m_list_iterator = end(buckets[m_bucket_index]);
    }

    void decrement()
    {
        auto &buckets = m_hash_map->m_buckets;
        if (m_list_iterator == begin(buckets[m_bucket_index]))
        {
            for (size_t i = m_bucket_index - 1; i >= 0; i--)
            {
                if (!buckets[i].empty())
                {
                    m_list_iterator = --end(buckets[i]);
                    m_bucket_index = i;
                    return;
                }
            }
            m_bucket_index = buckets.size() - 1;
            m_list_iterator = end(buckets[m_bucket_index]);
        }
        else
        {
            --m_list_iterator;
        }
    }
};

#endif //CONST_HASH_MAP_ITERATOR