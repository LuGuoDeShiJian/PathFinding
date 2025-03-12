#pragma once
namespace luguo::PathFind
{
    /**
     * @brief 节点类，用于表示网格中的一个位置，包含坐标、可通行状态、代价、父节点等信息
     */
    class Node
    {
    public:
        /**
         * 节点在网格中的x坐标
         */
        int x;
        /**
         * 节点在网格中的y坐标
         */
        int y;
        /**
         * 节点是否可通行，用于路径搜索算法中的障碍物判断
         */
        bool walkable;
        /**
         * 从起始节点到该节点的实际代价，初始化为0，后续根据路径搜索算法计算更新
         */
        double g;
        /**
         * 从该节点到目标节点的启发式代价，初始化为0，后续根据启发式函数计算更新
         */
        double h;
        /**
         * 该节点的总代价，即g+h，初始化为0，后续根据路径搜索算法计算更新
         */
        double f;
        /**
         * 标记节点是否在开放列表（待探索的节点列表）中
         */
        bool opened;
        /**
         * 标记节点是否在关闭列表（已探索的节点列表）中
         */
        bool closed;
        /**
         * 标记节点是否在跳跃点搜索递归中已被访问（用于跳跃点搜索实现逻辑）
         */
        bool tested;
        /**
         * 指向父节点的指针，用于路径回溯构建最终路径，初始化为nullptr
         */
        Node *parent;
        /**
         * 节点被涉及的路径数量，用于路径搜索算法中的节点复用情况，初始化为0
         */
        int retainCount;
        /**
         * 构造函数，可指定坐标和可通行状态初始化节点
         */
        Node(int _x = 0, int _y = 0, bool _walkable = true);
    };
}