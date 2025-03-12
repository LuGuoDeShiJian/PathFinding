#pragma once
#include "JumpPointFinderBase.h"

namespace luguo::PathFind
{
    class JPFNoObstacles : public JumpPointFinderBase
    {
    public:
        JPFNoObstacles(Grid *_grid, Heuristic::Type type = Heuristic::Type::MANHATTAN, bool _trackJumpRecursion = false);

    protected:
        std::vector<int> _jump(int x, int y, int px, int py) override;
        std::vector<std::pair<int, int>> _findNeighbors(Node *node) override;
    };
}
