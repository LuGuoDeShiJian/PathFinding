#include "core/Node.h"
namespace luguo::PathFind
{
    Node::Node(int _x, int _y, bool _walkable) : x(_x), y(_y), walkable(_walkable), g(0), h(0), f(0), opened(false), closed(false), tested(false), parent(nullptr) {}
}
