#pragma once
#include "DiagonalMovement.h"
#include "Heuristic.h"
#include "Heap.h"

namespace luguo::PathFind
{

    /**
     * 网格类，用于表示一个二维的地图，其中每个节点都有一个可通行状态。
     */
    class Grid
    {
    public:
        /**
         * 构造函数，根据宽度和高度初始化网格，同时可以选择传入一个二维矩阵来初始化节点的可通行状态
         * @param width 网格的宽度
         * @param height 网格的高度
         * @param matrix 二维矩阵，用于初始化节点的可通行状态，默认为空矩阵
         */
        Grid(int width, int height, const std::vector<std::vector<bool>> &matrix = {});
        /**
         * 构造函数，根据二维矩阵初始化网格
         * @param matrix 二维矩阵，用于初始化网格
         */
        Grid(const std::vector<std::vector<bool>> &matrix);
        /**
         * 析构函数，释放网格节点的内存
         */
        ~Grid();
        /**
         * 获得网格节点
         * @param x 节点的x坐标
         * @param y 节点的y坐标
         * @return 返回的Node指针
         * @throws 如果坐标超出了网格范围则返回空
         */
        Node *getNodeAt(int x, int y);

        /**
         * 判断指定坐标位置节点是否可通行
         * @param x 节点的x坐标
         * @param y 节点的y坐标
         * @return 返回节点是否可通行的布尔值
         * @throws 如果坐标超出了网格范围则抛出异常
         */
        bool isWalkableAt(int x, int y) const;

        /**
         * 判断指定坐标位置是否在网格内
         * @param x 节点的x坐标
         * @param y 节点的y坐标
         * @return 返回坐标是否在网格内的布尔值
         * @throws 如果坐标超出了网格范围则抛出异常
         */
        bool isInside(int x, int y) const;

        /**
         * 设置指定坐标位置节点的可通行状态
         *  @param x 节点的x坐标
         *  @param y 节点的y坐标
         *  @param walkable 节点是否可通行的布尔值
         *  @throws 如果坐标超出了网格范围则抛出异常
         */
        void setWalkableAt(int x, int y, bool walkable);

        /**
         * 根据移动规则DiagonalMovement获取指定节点的邻居节点
         * @param node 节点
         * @param diagonalMovement 对角线移动规则
         * @return 返回邻居节点的向量
         */
        std::vector<Node *> getNeighbors(const Node *node, DiagonalMovement diagonalMovement);

        /**
         * 克隆当前网格
         * @return 返回克隆后的网格指针
         */
        Grid *clone();

    private:
        int width;
        int height;
        std::vector<std::vector<Node *>> nodes;

        /**
         * 构建网格节点
         * --
         * @param matrix 二维矩阵，用于初始化节点的可通行状态，默认为空矩阵
         */
        void _buildNodes(const std::vector<std::vector<bool>> &matrix = {});
    };
}
