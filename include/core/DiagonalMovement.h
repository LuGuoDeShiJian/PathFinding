#pragma once
namespace luguo::PathFind
{
    //  定义一个枚举类DiagonalMovement，用于表示对角线移动的策略
    enum class DiagonalMovement
    {
        /**
         * @brief 总是允许对角线移动
         */
        Always,
        /**
         * @brief   从不允许对角线移动
         */
        Never,
        /**
         * @brief   仅当最多有一个障碍物时允许对角线移动
         */
        IfAtMostOneObstacle,
        /**
         * @brief   仅当没有任何障碍物时允许对角线移动
         */
        OnlyWhenNoObstacles
    };
}
