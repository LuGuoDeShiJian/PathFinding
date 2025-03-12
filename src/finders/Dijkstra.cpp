#include "finders/Dijkstra.h"

namespace luguo::PathFind
{
    Dijkstra::Dijkstra(const DiagonalMovement diagonalMovement, const Heuristic::Type heuristicType, const double weight)
        : AStar(diagonalMovement, heuristicType, weight) {}

    double Dijkstra::heuristic(const Node *a, const Node *b)
    {
        return 0;
    }
}
