#pragma once
#include "JPFAlways.h"
#include "JPFNever.h"
#include "JPFIfAtMostOneObstacle.h"
#include "JPFNever.h"
#include "JPFNoObstacles.h"

namespace luguo::PathFind
{
    class JumpPointFinder
    {
    public:
        JumpPointFinder(Grid *grid, const Heuristic::Type &heuristicType = Heuristic::Type::MANHATTAN, DiagonalMovement diagonalMovement = DiagonalMovement::Never);

        JumpPointFinderBase *createFinder();

    private:
        Heuristic::Type heuristicType;
        DiagonalMovement diagonalMovement;
        Grid *grid;
    };
}