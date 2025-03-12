#pragma once
#include "AStarFinder.h"

namespace luguo::PathFind
{
    class DijkstraFinder : public AStarFinder
    {
    public:
        DijkstraFinder(const DiagonalMovement diagonalMovement = DiagonalMovement::Never,
                       const Heuristic::Type heuristicType = Heuristic::Type::MANHATTAN,
                       const double weight = 1);

    protected:
        double heuristic(const Node *a, const Node *b) override;
    };
}
