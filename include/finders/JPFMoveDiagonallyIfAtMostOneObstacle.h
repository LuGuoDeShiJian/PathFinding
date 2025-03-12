#pragma once
#include "JumpPointFinderBase.h"
namespace luguo::PathFind
{
    // （对角线移动仅当至多有一个障碍物时）进行跳跃点搜索逻辑的实现
    class JPFMoveDiagonallyIfAtMostOneObstacle : public JumpPointFinderBase
    {
    public:
        // （对角线移动仅当至多有一个障碍物时）进行跳跃点搜索逻辑的实现
        JPFMoveDiagonallyIfAtMostOneObstacle(Grid *_grid, Heuristic::Type type = Heuristic::Type::MANHATTAN, bool _trackJumpRecursion = false);

    protected:
        std::vector<int> _jump(int x, int y, int px, int py) override;
        std::vector<std::pair<int, int>> _findNeighbors(Node *node) override;
    };
}
