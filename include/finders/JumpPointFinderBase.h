#pragma once
#include "../Core/Util.h"

namespace luguo::PathFind
{
    /**
     * 跳跃点搜索算法基类。
     * --
     * + 所有跳跃点搜索算法都应该继承此类。
     * + + 该类提供了一些基本的功能，如初始化，查找路径等。
     * + + 所有继承此类的跳跃点搜索算法都应该实现 _findNeighbors 和 _jump 函数。
     */
    class JumpPointFinderBase
    {
    protected:
        Heap openList;
        Node *startNode;
        Node *endNode;
        Grid *grid;
        bool trackJumpRecursion;
        Heuristic heuristic;

    public:
        /**
         * 构造函数。
         * --
         * + 初始化跳跃点搜索算法。
         * + + grid: 网格。
         * + + type: 距离类型。
         * + + trackJumpRecursion: 是否跟踪跳跃递归。
         */
        JumpPointFinderBase(Grid *_grid, Heuristic::Type type = Heuristic::Type::MANHATTAN, bool _trackJumpRecursion = false);
        /**
         * 寻找路径，在完成了初始化后调用。
         * --
         * + return
         * + + 返回一条向量路径。
         * + + 如果找不到路径，则返回一个空向量。
         */
        std::vector<Node *> findPath(int startX, int startY, int endX, int endY);

    protected:
        virtual std::vector<std::pair<int, int>> _findNeighbors(Node *node) = 0;
        virtual std::vector<int> _jump(int x, int y, int px, int py) = 0;
        void _identifySuccessors(Node *node);
    };
}
