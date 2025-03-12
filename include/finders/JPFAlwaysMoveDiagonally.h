#pragma once
#include "JumpPointFinderBase.h"

namespace luguo::PathFind
{
    // 按照总是沿对角线移动的规则实现跳跃点搜索逻辑
    class JPFAlwaysMoveDiagonally : public JumpPointFinderBase
    {
    public:
        // 按照总是沿对角线移动的规则实现跳跃点搜索逻辑
        JPFAlwaysMoveDiagonally(Grid *_grid, Heuristic::Type type = Heuristic::Type::MANHATTAN, bool _trackJumpRecursion = false);

    protected:
        std::vector<int> _jump(int x, int y, int px, int py) override;
        std::vector<std::pair<int, int>> _findNeighbors(Node *node) override;
    };
}
