#include "finders/DijkstraFinder.h"

namespace luguo::PathFind
{
    DijkstraFinder::DijkstraFinder(const DiagonalMovement diagonalMovement, const Heuristic::Type heuristicType, const double weight)
        : AStarFinder(diagonalMovement, heuristicType, weight) {}

    double DijkstraFinder::heuristic(const Node *a, const Node *b)
    {
        return 0;
    }
}
