#include "core/Heap.h"

namespace luguo::PathFind
{
    Heap::Heap() = default;

    bool Heap::empty() const
    {
        return heap.empty();
    }

    void Heap::push(Node *node)
    {
        heap.push_back(node);
        std::push_heap(heap.begin(), heap.end(), Comparator());
    }

    Node *Heap::pop()
    {
        std::pop_heap(heap.begin(), heap.end(), Comparator());
        Node *top = heap.back();
        heap.pop_back();
        return top;
    }

    void Heap::updateItem(Node *node)
    {
        auto it = std::find(heap.begin(), heap.end(), node);
        if (it != heap.end())
        {
            std::iter_swap(it, heap.end() - 1);
            std::pop_heap(heap.begin(), heap.end(), Comparator());
        }
    }
}