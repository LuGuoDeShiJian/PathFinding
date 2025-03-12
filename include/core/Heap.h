#pragma once
#include <vector>
#include <algorithm>
#include "Node.h"

namespace luguo::PathFind
{
    class Heap
    {
    public:
        Heap();
        bool empty() const;
        void push(Node *node);
        Node *pop();
        void updateItem(Node *node);

    private:
        std::vector<Node *> heap;
        struct Comparator
        {
            bool operator()(const Node *a, const Node *b) const
            {
                return a->f > b->f;
            }
        };
    };
}