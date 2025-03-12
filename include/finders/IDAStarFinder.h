#pragma once
#include "../core/Util.h"
#include <variant>

namespace luguo::PathFind
{
    class IDAStarFinder
    {
    public:
        // 构造函数，初始化寻路算法相关配置参数
        IDAStarFinder(const DiagonalMovement diagonalMovement = DiagonalMovement::Never,
                      const Heuristic::Type heuristicType = Heuristic::Type::MANHATTAN,
                      const double weight = 1, const bool trackRecursion = false,
                      const int timeLimit = -1);

        // 修改返回类型为std::vector<Node *>，用于返回从起始到目标的路径节点指针列表
        std::vector<Node *> findPath(int startX, int startY, int endX, int endY, Grid *grid);

    private:
        DiagonalMovement diagonalMovement;
        Heuristic heuristics;
        double weight;
        bool trackRecursion;
        int timeLimit;

        // 计算启发式距离的私有辅助函数，根据设定的启发式类型计算两节点间距离估计值
        double heuristic(const Node *a, const Node *b);

        // 计算从一个节点到另一个节点移动代价的私有辅助函数
        double cost(const Node *from, const Node *to);

        // 实现IDA*算法核心递归搜索逻辑的私有函数，返回不同类型表示不同情况
        std::variant<double, Node *> recursiveSearch(const Node *node, double g, double cutoff,
                                                     std::vector<Node *> &route, int depth,
                                                     Grid *grid, const Node *endNode);

        // 记录开始时间的私有成员变量，用于和timeLimit配合判断是否超时
        std::clock_t startTime;
    };
}
