#pragma once
#include "JPFAlwaysMoveDiagonally.h"
#include "JPFNeverMoveDiagonally.h"
#include "JPFAlwaysMoveDiagonally.h"
#include "JPFMoveDiagonallyIfNoObstacles.h"
#include "JPFMoveDiagonallyIfAtMostOneObstacle.h"

namespace luguo::PathFind
{
    class JumpPointFinder
    {
    public:
        // 构造函数，根据传入的配置参数决定返回不同类型的寻路算法实例
        JumpPointFinder(Grid *grid, const Heuristic::Type &heuristicType = Heuristic::Type::MANHATTAN, DiagonalMovement diagonalMovement = DiagonalMovement::Never);

        // 根据配置返回相应的寻路算法实例指针（调用者需要负责释放内存）
        JumpPointFinderBase *createFinder();

    private:
        Heuristic::Type heuristicType;
        DiagonalMovement diagonalMovement;
        Grid *grid;
    };
}