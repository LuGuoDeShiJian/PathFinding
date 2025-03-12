#pragma once
#include "AStar.h"

namespace luguo::PathFind
{
    class Dijkstra : public AStar
    {
    public:
        Dijkstra(const DiagonalMovement diagonalMovement = DiagonalMovement::Never,
                 const Heuristic::Type heuristicType = Heuristic::Type::MANHATTAN,
                 const double weight = 1);

    protected:
        double heuristic(const Node *a, const Node *b) override;
    };
}
