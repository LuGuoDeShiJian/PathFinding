#include "core/Heap.h"
#include <algorithm>
#include <utility>

namespace luguo::PathFind
{
    Heap::Heap() : nodeCompare() {}

    bool Heap::empty()
    {
        return nodes.empty();
    }

    void Heap::push(Node *node)
    {
        nodes.push_back(node);
        std::push_heap(nodes.begin(), nodes.end(), nodeCompare);
    }

    Node *Heap::pop()
    {
        std::pop_heap(nodes.begin(), nodes.end(), nodeCompare);
        Node *result = nodes.back();
        nodes.pop_back();
        return result;
    }

    void Heap::updateItem(Node *node)
    {
        auto it = std::find(nodes.begin(), nodes.end(), node);
        if (it != nodes.end())
        {
            nodes.erase(it);
            push(node);
        }
    }
}
