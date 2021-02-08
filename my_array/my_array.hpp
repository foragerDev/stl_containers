#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T, std::size_t _size>
class my_array
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;

    // Not in use yet because no implemented
    // using array_type = my_array<T>;
    // using iterator = array_iterator<array_type>;
    // using const_iterator = const_array_iterator<array_type>;
    // using reverse_iterator = reverse_array_iterator<array_type>;
    // using const_reverse_iterator = const_array_reverse_iterator<array_type>;

    explicit my_array() : m_max_size(_size),
                          m_size(0),
                          m_data(_size <= 0 ? throw std::invalid_argument("Size must be greater than zero") : new T[_size]{})
    {
    }
    my_array(std::initializer_list<value_type> li) : my_array()
    {
        auto start = li.begin();
        auto end = li.end();
        auto data_start = m_data;
        while (start != end)
        {
            *data_start++ = *start++;
        }
        m_size = li.size();
    }

    template <typename InputIterator>
    my_array(InputIterator start, InputIterator end);

    my_array(const my_array &copy) : my_array()
    {
        for (size_t i = 0; i < copy.m_max_size; ++i)
        {
            m_data[i] = copy.m_data[i];
        }
        m_size = copy.size();
        m_max_size = copy.max_size();
    }

    my_array(my_array &&move)
    {
        swap(move);
    }

    const T &at(size_type i) const
    {
        if (i >= max_size)
        {
            throw std::out_of_range("Index of out range.");
        }
        return m_data[i];
    }

    T &at(size_type i)
    {
        return const_cast<T &>(this->at(i));
    }

    const T &front() const
    {
        return m_data[0];
    }
    T &front()
    {
        return const_cast<T &>(this->front());
    }

    const T &back() const
    {
        return m_data[m_size - 1];
    }
    T &back()
    {
        return const_cast<T &>(this->back());
    }

    T *data() noexcept
    {
        return m_data;
    }
    const T *data() const noexcept
    {
        return m_data;
    };

    bool empty() const
    {
        return m_size > 0;
    }; // check if container is empty or not

    size_type size() const
    {
        return m_size;
    }; // return the number of items in the container

    size_type max_size() const
    {
        return m_max_size;
    }; // return the maximum size of the container

    void fill(const T &value)
    {
        for (size_t i = 0; i < m_max_size; ++i)
        {
            m_data[i] = value;
        }
    } // fill the container with the provided value

    void swap(my_array &other) noexcept
    {
        std::swap(m_size, other.m_size);
        std::swap(m_max_size, other.m_max_size);
        std::swap(m_data, other.m_data);
    } // swap two arrays

    //operators
    my_array &operator=(const my_array &rhs) noexcept
    {
        my_array temp(rhs);
        swap(temp);
        return *this;
    };
    my_array &operator=(my_array &&rhs) noexcept
    {
        swap(rhs);
        return *this;
    };

    const T &operator[](int index) const
    {
        return m_data[index];
    }

    T &operator[](int index)
    {
        return const_cast<T &>(m_data[index]);
    }

    bool operator==(const my_array &rhs) const;
    bool operator!=(const my_array &rhs) const;
    bool operator<=(const my_array &rhs) const;
    bool operator>=(const my_array &rhs) const;
    bool operator>(const my_array &rhs) const;
    bool operator<(const my_array &rhs) const;

    ~my_array()
    {
        if (!empty())
        {
            delete[] m_data;
        }
    }

private:
    size_t m_size;
    size_t m_max_size;
    T *m_data;
};
