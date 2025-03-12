#pragma once
#include "Grid.h"
#include "Node.h"
#include <vector>

namespace luguo::PathFind
{
    class Util
    {
    public:
        /**
         * 根据父节点记录回溯并返回路径。
         * （包含起始节点和结束节点）
         * @param node 结束节点
         * @return 路径，以节点指针向量形式返回
         */
        static std::vector<Node *> backtrace(const Node *node);

        /**
         * 从起始节点和结束节点进行回溯，并返回合并后的路径。
         * （包含起始节点和结束节点）
         * @param nodeA
         * @param nodeB
         * @return 合并后的路径，以节点指针向量形式返回
         */
        static std::vector<Node *> biBacktrace(const Node *nodeA, const Node *nodeB);

        /**
         * 计算路径的长度。
         * @param path 路径，以节点指针向量形式传入
         * @return 路径的长度
         */
        static double pathLength(const std::vector<Node *> &path);

        /**
         * 给定起始坐标和结束坐标，基于布雷森汉姆算法（Bresenham's algorithm）返回位于这两个坐标所构成直线上的所有坐标对应的节点指针。
         * @param x0 起始 x 坐标
         * @param y0 起始 y 坐标
         * @param x1 结束 x 坐标
         * @param y1 结束 y 坐标
         * @return 直线上坐标对应的节点指针向量
         */
        static std::vector<Node *> interpolate(int x0, int y0, int x1, int y1);

        /**
         * 给定一条压缩后的路径（以节点指针向量表示），返回一条对其所有线段进行插值后的新路径（同样以节点指针向量表示）。
         * @param path 路径，以节点指针向量形式传入
         * @return 扩展后的路径，以节点指针向量形式返回
         */
        static std::vector<Node *> expandPath(const std::vector<Node *> &path);

        /**
         * 对给定的路径进行平滑处理。
         * 原始路径不会被修改，将返回一条新的路径（以节点指针向量表示）。
         * @param grid 用于检查节点可通行性的网格对象
         * @param path 路径，以节点指针向量形式传入
         * @return 平滑后的路径，以节点指针向量形式返回
         */
        static std::vector<Node *> smoothenPath(const Grid &grid, const std::vector<Node *> &path);

        /**
         * 压缩一条路径，移除冗余节点且不改变路径形状。
         * 原始路径不会被修改。
         * @param path 路径，以节点指针向量形式传入
         * @return 压缩后的路径，以节点指针向量形式返回
         */
        static std::vector<Node *> compressPath(const std::vector<Node *> &path);
    };
    /**
     * 获取对角线移动策略的名称。
     * @param DiagonalMovement 对角线移动策略类型
     * @return 对应的名称
     */
    inline std::string getName(DiagonalMovement T, int lang = 0)
    {
        switch (T)
        {
        case DiagonalMovement::Always:
            if (lang == 0)
                return "总是移动对角线";
            return "Always";
        case DiagonalMovement::Never:
            if (lang == 0)
                return "从不移动对角线";
            return "Never";
        case DiagonalMovement::IfAtMostOneObstacle:
            if (lang == 0)
                return "最多移动一个对角线";
            return "IfAtMostOneObstacle";
        case DiagonalMovement::OnlyWhenNoObstacles:
            if (lang == 0)
                return "只有当没有障碍物时移动对角线";
            return "OnlyWhenNoObstacles";
        default:
            return "Unknown";
        }
    }
    /**
     * 获取启发式函数类型的名称。
     * @param Heuristic::Type 启发式函数类型
     * @param lang 语言类型，0 表示中文，1 表示英文
     * @return 对应的名称
     */
    inline std::string getName(Heuristic::Type T, int lang = 0)
    {
        switch (T)
        {
        case Heuristic::Type::MANHATTAN:
            if (lang == 0)
                return "曼哈顿距离";
            return "MANHATTAN";
        case Heuristic::Type::CHEBYSHEV:
            if (lang == 0)
                return "切比雪夫距离";
            return "CHEBYSHEV";
        case Heuristic::Type::EUCLIDEAN:
            if (lang == 0)
                return "欧几里得距离";
            return "EUCLIDEAN";
        case Heuristic::Type::OCTILE:
            if (lang == 0)
                return "八叉树距离";
            return "OCTILE";
        default:
            return "Unknown";
        }
    }
}
