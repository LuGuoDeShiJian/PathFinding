#pragma once
#include "JumpPointFinderBase.h"

namespace luguo::PathFind
{
    // 遵循只允许水平或垂直移动的规则
    class JPFNeverMoveDiagonally : public JumpPointFinderBase
    {
    public:
        // 遵循只允许水平或垂直移动的规则
        JPFNeverMoveDiagonally(Grid *_grid, Heuristic::Type type = Heuristic::Type::MANHATTAN, bool _trackJumpRecursion = false);

    protected:
        std::vector<int> _jump(int x, int y, int px, int py) override;
        std::vector<std::pair<int, int>> _findNeighbors(Node *node) override;
    };
}
