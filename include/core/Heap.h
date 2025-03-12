#pragma once
#include "Node.h"
#include <vector>

namespace luguo::PathFind
{
    /**
     * Heap 优先队列，用于存储节点，按照节点的 f 值进行排序
     */
    class Heap
    {
    public:
        Heap();
        bool empty();
        void push(Node *node);
        Node *pop();
        void updateItem(Node *node);

    private:
        std::vector<Node *> nodes;
        struct NodeCompare
        {
            bool operator()(Node *a, Node *b) const
            {
                return a->f > b->f;
            }
        } nodeCompare;
    };
}
