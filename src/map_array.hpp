#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray
{
public:
    class ArrayIterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = std::pair<Key, Value>*;
        using reference = std::pair<Key, Value>&;

        explicit ArrayIterator(pointer ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++() 
        {
            ++ptr;
            return *this;
        }
        ArrayIterator& operator--() 
        {
            --ptr;
            return *this; 
        }
        ArrayIterator operator++(int) 
        {
            ArrayIterator temp = *this; 
            ++(*this); return temp;
        }
        ArrayIterator operator--(int) 
        {
            ArrayIterator temp = *this;
            --(*this);
            return temp;
        }
        ArrayIterator& operator+=(difference_type d)
        { ptr += d;
        return *this; 
        }
        ArrayIterator& operator-=(difference_type d)
        {
            ptr -= d; 
            return *this; 
        }
        friend ArrayIterator operator+(ArrayIterator it, difference_type d)
        { 
            it += d;
            return it; 
        }
        friend ArrayIterator operator+(difference_type d, ArrayIterator it)
        { 
            it += d;
            return it; 
        }
        friend ArrayIterator operator-(ArrayIterator it, difference_type d)
        {
            it -= d; 
            return it;
        }
        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs)
        {
            return lhs.ptr - rhs.ptr; 
        }
        auto operator<=>(const ArrayIterator& other) const = default;
        reference operator*() const 
        {
            return *ptr;
        }
        pointer operator->() const
        { 
            return ptr; 
        }
        reference operator[](difference_type d) const
        {
            return ptr[d]; 
        }

    private:
        pointer ptr;
    };

    using value_type = std::pair<Key, Value>;
    using iterator = ArrayIterator;

    iterator begin() { return iterator(data.data()); }
    iterator end() { return iterator(data.data() + data.size()); }
    Value& operator[](const Key& key);

private:
    std::vector<value_type> data;
};

template <typename Key, typename Value>
Value& MapArray<Key, Value>::operator[](const Key& key) {
    auto it = std::find_if(data.begin(), data.end(),
        [&key](const value_type& p) { return p.first == key; });

    if (it != data.end()) {
        return it->second;
    }
    else {
        data.emplace_back(key, Value{});
        return data.back().second;
    }
}

#endif 
