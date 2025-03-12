#pragma once
#include "../core/Util.h"
namespace luguo::PathFind
{
    class AStar
    {
    public:
        AStar(const DiagonalMovement diagonalMovement = DiagonalMovement::Never,
              const Heuristic::Type heuristicType = Heuristic::Type::MANHATTAN,
              const double weight = 1);
        std::vector<Node *> findPath(int startX, int startY, int endX, int endY, Grid *grid);

    private:
        DiagonalMovement diagonalMovement;
        Heuristic heuristics;
        double weight;
        Heap openList;

    protected:
        virtual double heuristic(const Node *a, const Node *b);
    };
}
