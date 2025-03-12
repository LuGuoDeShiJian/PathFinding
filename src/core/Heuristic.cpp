#include "core/Heuristic.h"
namespace luguo::PathFind
{
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
            distanceFunction = manhattan;
            break;
        }
    }

    double Heuristic::heuristic(int dx, int dy)
    {
        return distanceFunction(dx, dy);
    }

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