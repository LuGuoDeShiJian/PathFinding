#include "finders/BestFirstFinder.h"

namespace luguo::PathFind
{
    BestFirstFinder::BestFirstFinder(const DiagonalMovement diagonalMovement, const Heuristic::Type heuristicType, const double weight)
        : AStarFinder(diagonalMovement, heuristicType, weight) {}

    double BestFirstFinder::heuristic(const Node *a, const Node *b)
    {
        double origValue = AStarFinder::heuristic(a, b);
        return origValue * 1000000;
    }

}
