#pragma once
#include <iostream>
#include <memory>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <ctime>
namespace luguo::PathFind
{
    /**
     * @brief 曼哈顿距离
     */
    double manhattan(int dx, int dy);
    /**
     * @brief 欧几里得距离
     */
    double euclidean(int dx, int dy);
    /**
     * @brief 八叉树距离
     */
    double octile(int dx, int dy);
    /**
     * @brief 切比雪夫距离
     */
    double chebyshev(int dx, int dy);
    /**
     * @brief 启发式函数，用于设置和使用启发式函数
     */
    class Heuristic
    {

    public:
        /**
         * @brief 构造函数，初始化函数指针为曼哈顿距离计算函数
         */
        enum class Type
        {
            // 曼哈顿距离，用于计算在网格中从一个点到另一个点的水平和垂直距离总和
            MANHATTAN,
            // 欧几里得距离，用于计算在网格中从一个点到另一个点的直线距离
            EUCLIDEAN,
            // 八叉树距离，用于计算在网格中从一个点到另一个点的对角距离
            OCTILE,
            // 切比雪夫距离，用于计算在网格中从一个点到另一个点的最大坐标差
            CHEBYSHEV,
        };

        /**
         * @brief 设置启发式函数类型
         * @param type 启发式函数类型
         */
        void setHeuristicFunction(Type type);

        /**
         * @brief 计算启发式函数
         * @param dx x方向上的距离
         * @param dy y方向上的距离
         * @return 启发式函数值
         */
        double heuristic(int dx, int dy);

    private:
        /**
         * @brief 启发式函数指针，指向启发式函数计算函
         */
        double (*distanceFunction)(int, int);
    };
}