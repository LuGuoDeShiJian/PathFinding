#pragma once
#include "../core/Util.h"
#include <variant>

namespace luguo::PathFind
{
    class IDAStar
    {
    public:
        IDAStar(const DiagonalMovement diagonalMovement = DiagonalMovement::Never,
                const Heuristic::Type heuristicType = Heuristic::Type::MANHATTAN,
                const double weight = 1, const bool trackRecursion = false,
                const int timeLimit = -1);
        std::vector<Node *> findPath(int startX, int startY, int endX, int endY, Grid *grid);

    private:
        DiagonalMovement diagonalMovement;
        Heuristic heuristics;
        double weight;
        bool trackRecursion;
        int timeLimit;

        double heuristic(const Node *a, const Node *b);

        double cost(const Node *from, const Node *to);

        std::variant<double, Node *> recursiveSearch(const Node *node, double g, double cutoff,
                                                     std::vector<Node *> &route, int depth,
                                                     Grid *grid, const Node *endNode);

        std::clock_t startTime;
    };
}
