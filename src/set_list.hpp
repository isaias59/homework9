#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList
{
    struct ListNode
    {
        T data;
        std::shared_ptr<ListNode> next;
    };
public:
    class ListIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr) {}

        ListIterator& operator++()
        { 
            ptr = ptr->next;
            return *this; 
        }
        ListIterator operator++(int) 
        {
            ListIterator temp = *this;
            ++(*this); return temp;
        }
        reference operator*() const
        {
            return ptr->data;
        }
        pointer operator->() const 
        { 
            return &ptr->data;
        }
        bool operator==(const ListIterator& other) const = default;

    private:
        std::shared_ptr<ListNode> ptr;
    };

    using value_type = T;
    using iterator = ListIterator;

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng)
    {
        std::ranges::for_each(std::forward<Rng>(rng),
            std::bind_front(&SetList::insert, this));
    }

    ListIterator begin() { return ListIterator(head); }
    ListIterator end() { return ListIterator(); }
    bool contains(const T& value);
    ListIterator insert(T value);

private:
    std::shared_ptr<ListNode> head = nullptr;
};

template <typename T>
bool SetList<T>::contains(const T& value)
{
    for (auto it = begin(); it != end(); ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
typename SetList<T>::ListIterator SetList<T>::insert(T value)
{
    if (!contains(value)) {
        auto new_node = std::make_shared<ListNode>(ListNode{ std::move(value), head });
        head = new_node;
        return ListIterator(new_node);
    }
    return end();
}

#endif 
