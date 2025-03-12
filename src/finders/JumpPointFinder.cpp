#include "finders/JumpPointFinder.h"

namespace luguo::PathFind
{
    // 构造函数实现，初始化启发式函数类型和对角线移动规则参数
    JumpPointFinder::JumpPointFinder(Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement) : heuristicType(heuristicType), diagonalMovement(diagonalMovement), grid(grid) {}

    // 根据配置创建并返回相应的寻路算法实例指针（调用者需负责释放内存，比如使用delete操作符）
    JumpPointFinderBase *JumpPointFinder::createFinder()
    {
        if (diagonalMovement == DiagonalMovement::Never)
        {
            return new JPFNever(grid, heuristicType);
        }
        else if (diagonalMovement == DiagonalMovement::Always)
        {
            return new JPFAlways(grid, heuristicType);
        }
        else if (diagonalMovement == DiagonalMovement::OnlyWhenNoObstacles)
        {
            return new JPFNoObstacles(grid, heuristicType);
        }
        else
        {
            return new JPFIfAtMostOneObstacle(grid, heuristicType);
        }
    }
}