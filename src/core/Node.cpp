#include "core/Node.h"
namespace luguo::PathFind
{
    Node::Node(int x, int y, bool walkable)
        : x(x), y(y), walkable(walkable)
    {
    }
}
