#pragma once
namespace luguo::PathFind
{
    class Node
    {
    public:
        int x, y;
        bool walkable;
        double g{}, h{}, f{};
        mutable bool opened = false;
        mutable bool closed = false;
        mutable bool tested = false;
        Node *parent = nullptr;
        int retainCount = 0;

        Node(int x, int y, bool walkable = false);
    };
}