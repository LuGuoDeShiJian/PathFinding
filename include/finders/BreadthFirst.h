#pragma once
#include "../core/Util.h"
namespace luguo::PathFind
{

    class BreadthFirst
    {
    public:
        BreadthFirst(DiagonalMovement diagonalMovement = DiagonalMovement::Never);
        std::vector<Node *> findPath(int startX, int startY, int endX, int endY, Grid *grid);

    private:
        DiagonalMovement diagonalMovement;
    };
}
