#pragma once
#include "JumpPointFinderBase.h"

namespace luguo::PathFind
{
    // （对角线移动仅当无障碍物时）的跳跃点搜索逻辑
    class JPFMoveDiagonallyIfNoObstacles : public JumpPointFinderBase
    {
    public:
        // （对角线移动仅当无障碍物时）的跳跃点搜索逻辑
        JPFMoveDiagonallyIfNoObstacles(Grid *_grid, Heuristic::Type type = Heuristic::Type::MANHATTAN, bool _trackJumpRecursion = false);

    protected:
        std::vector<int> _jump(int x, int y, int px, int py) override;
        std::vector<std::pair<int, int>> _findNeighbors(Node *node) override;
    };
}
