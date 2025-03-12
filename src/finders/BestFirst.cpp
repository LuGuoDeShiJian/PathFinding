#include "finders/BestFirst.h"

namespace luguo::PathFind
{
    BestFirst::BestFirst(const DiagonalMovement diagonalMovement, const Heuristic::Type heuristicType, const double weight)
        : AStar(diagonalMovement, heuristicType, weight) {}

    // 计算启发式函数
    double BestFirst::heuristic(const Node *a, const Node *b)
    {
        // 调用AStarFinder的启发式函数
        double origValue = AStar::heuristic(a, b);
        // 返回启发式函数的值乘以1000000
        return origValue * 1000000;
    }

}
