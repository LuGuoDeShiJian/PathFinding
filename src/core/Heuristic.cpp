#include "core/Heuristic.h"
namespace luguo::PathFind
{
    // 设置启发式函数类型的方法，根据传入的枚举值来设置具体使用的函数指针
    void Heuristic::setHeuristicFunction(Heuristic::Type type)
    {
        switch (type)
        {
        case Heuristic::Type::MANHATTAN:
            distanceFunction = manhattan;
            break;
        case Heuristic::Type::EUCLIDEAN:
            distanceFunction = euclidean;
            break;
        case Heuristic::Type::OCTILE:
            distanceFunction = octile;
            break;
        case Heuristic::Type::CHEBYSHEV:
            distanceFunction = chebyshev;
            break;
        default:
            // 如果传入了未知的类型，默认设置为曼哈顿距离函数
            distanceFunction = manhattan;
            break;
        }
    }

    // 计算距离的方法，调用当前设置的函数指针指向的函数来计算距离
    double Heuristic::heuristic(int dx, int dy)
    {
        return distanceFunction(dx, dy);
    }

    // 以下是具体的各种启发式函数的实现，和之前单独函数形式类似
    double manhattan(int dx, int dy)
    {
        return dx + dy;
    }

    double euclidean(int dx, int dy)
    {
        return std::sqrt(dx * dx + dy * dy);
    }

    double octile(int dx, int dy)
    {
        const double F = std::sqrt(2) - 1;
        return (dx < dy) ? F * dx + dy : F * dy + dx;
    }

    double chebyshev(int dx, int dy)
    {
        return std::max(dx, dy);
    }
}