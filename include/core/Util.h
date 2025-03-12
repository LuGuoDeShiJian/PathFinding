#pragma once
#include <vector>
#include <cmath>
#include "Grid.h"
#include "Node.h"
#include "Heuristic.h"
#include "Heap.h"

namespace luguo::PathFind
{
    class Util
    {
    public:
        static std::vector<Node *> backtrace(Node *endNode);
        static std::vector<Node *> biBacktrace(Node *nodeA, Node *nodeB);
        static double pathLength(const std::vector<Node *> &path);
        static std::vector<Node *> interpolate(int x0, int y0, int x1, int y1);
        static std::vector<Node *> expandPath(const std::vector<Node *> &path);
        static std::vector<Node *> smoothenPath(const Grid &grid, const std::vector<Node *> &path);
        static std::vector<Node *> compressPath(const std::vector<Node *> &path);
    };
}