#include "finders/IDAStar.h"

namespace luguo::PathFind
{
    // 构造函数实现，根据传入参数初始化类的成员变量，并根据对角线移动规则确定合适的启发式函数类型
    IDAStar::IDAStar(const DiagonalMovement diagonalMovement,
                     const Heuristic::Type heuristicType, const double weight,
                     const bool trackRecursion, const int timeLimit)
        : diagonalMovement(diagonalMovement),
          heuristics(),
          weight(weight), trackRecursion(trackRecursion), timeLimit(timeLimit),
          startTime(0)
    {
        heuristics.setHeuristicFunction(heuristicType);
    }

    // 计算启发式距离的辅助函数实现，依据启发式函数类型计算两节点坐标差值对应的距离估计值
    double IDAStar::heuristic(const Node *a, const Node *b)
    {
        return heuristics.heuristic(std::abs(b->x - a->x), std::abs(b->y - a->y));
    }

    // 计算移动代价的辅助函数实现，根据节点坐标判断是水平/垂直移动还是对角线移动，返回相应代价
    double IDAStar::cost(const Node *from, const Node *to)
    {
        return (from->x == to->x || from->y == to->y) ? 1 : std::sqrt(2);
    }

    // 核心的递归搜索函数实现，遵循IDA*算法的迭代加深搜索逻辑进行路径查找
    std::variant<double, Node *> IDAStar::recursiveSearch(const Node *node, double g, double cutoff,
                                                          std::vector<Node *> &route, int depth,
                                                          Grid *grid, const Node *endNode)
    {
        static int nodesVisited = 0;
        nodesVisited++;

        // 检查是否超过时间限制，使用成员变量startTime进行判断
        if (timeLimit > 0 && (std::clock() - startTime > static_cast<std::clock_t>(timeLimit * CLOCKS_PER_SEC)))
        {
            return std::numeric_limits<double>::max();
        }

        // 计算当前节点的评估函数值（f值），结合已走过的实际代价、启发式估计值和权重
        double f = g + heuristic(node, endNode) * weight;

        // 如果f值超过当前搜索深度限制（cutoff），返回f值用于更新下次迭代的深度限制
        if (f > cutoff)
        {
            return f;
        }

        // 如果当前节点就是目标节点，将其指针存入路径数组并返回该节点，表示找到路径
        if (node == endNode)
        {
            route.push_back(const_cast<Node *>(node));
            return const_cast<Node *>(node);
        }

        double min = std::numeric_limits<double>::max();
        Node *neighbor;
        std::vector<Node *> neighbors = grid->getNeighbors(node, diagonalMovement);

        // 以下对邻居节点按启发式距离排序的代码被注释掉，因会改变原始算法逻辑（可按需启用）
        // std::sort(neighbors.begin(), neighbors.end(), [this, endNode](const Node *a, const Node *b) {
        //     return heuristic(a, endNode) < heuristic(b, endNode);
        // });

        for (size_t k = 0; k < neighbors.size(); ++k)
        {
            neighbor = neighbors[k];

            if (trackRecursion)
            {
                // 处理节点的访问计数、测试标记等逻辑，用于可视化或统计目的（简单示意，可完善）
                neighbor->retainCount++;
                neighbor->tested = true;
            }

            auto result = recursiveSearch(neighbor, g + cost(node, neighbor), cutoff, route, depth + 1, grid, endNode);

            // 如果递归返回的是节点指针，说明找到路径，存入当前节点指针并返回找到的节点
            if (std::holds_alternative<Node *>(result))
            {
                route.push_back(const_cast<Node *>(node));
                return std::get<Node *>(result);
            }

            // 如果启用跟踪递归且邻居节点访问计数减为0，重置测试标记
            if (trackRecursion && (--neighbor->retainCount == 0))
            {
                neighbor->tested = false;
            }

            // 更新最小的f值，用于判断是否更新搜索深度限制
            if (std::get<double>(result) < min)
            {
                min = std::get<double>(result);
            }
        }

        // 如果遍历完邻居未找到路径，返回最小的f值用于更新下次迭代深度限制
        return min;
    }

    // 对外提供的寻路函数实现，通过不断迭代加深搜索深度尝试找到从起始到目标的路径
    std::vector<Node *> IDAStar::findPath(int startX, int startY, int endX, int endY, Grid *grid)
    {
        startTime = std::clock();
        Node *startNode = grid->getNodeAt(startX, startY);
        Node *endNode = grid->getNodeAt(endX, endY);

        // 初始搜索深度限制设为起始节点到目标节点的启发式距离估计值
        double cutoff = heuristic(startNode, endNode);
        std::vector<Node *> route;

        for (int j = 0; true; ++j)
        {
            route.clear();
            route.resize(0);

            auto result = recursiveSearch(startNode, 0, cutoff, route, 0, grid, endNode);

            // 如果返回表示未找到路径的特殊值，直接返回空路径
            if (std::holds_alternative<double>(result) && std::get<double>(result) == std::numeric_limits<double>::max())
            {
                return {};
            }

            // 如果返回节点指针，说明找到路径，对路径节点指针列表反转（因为是从目标往回回溯添加的节点指针）
            if (std::holds_alternative<Node *>(result))
            {
                std::reverse(route.begin(), route.end());
                return route;
            }

            // 更新搜索深度限制为返回的较小的f值，继续下一轮迭代
            cutoff = std::get<double>(result);
        }

        return {};
    }
}
