#pragma once
#include "../core/Util.h"
namespace luguo::PathFind
{

    class BreadthFirstFinder
    {
    public:
        BreadthFirstFinder(DiagonalMovement diagonalMovement = DiagonalMovement::Never);
        std::vector<Node *> findPath(int startX, int startY, int endX, int endY, Grid *grid);

    private:
        DiagonalMovement diagonalMovement;
    };
}
