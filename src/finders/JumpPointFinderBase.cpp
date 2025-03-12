#include "finders/JumpPointFinderBase.h"

namespace luguo::PathFind
{

    // findPath函数实现，具体的寻路逻辑，在给定的地图网格中查找从起始到目标的路径
    std::vector<Node *> JumpPointFinderBase::findPath(int startX, int startY, int endX, int endY)
    {

        startNode = grid->getNodeAt(startX, startY);
        endNode = grid->getNodeAt(endX, endY);

        // 设置起始节点的g值和f值为0，通常g值表示从起始点到当前节点的实际代价，初始为0
        startNode->g = 0;
        startNode->f = 0;

        // 将起始节点加入开放列表，并标记其为已打开状态
        openList.push(startNode);
        startNode->opened = true;

        Node *node;
        // 只要开放列表不为空，就持续进行搜索循环
        while (!openList.empty())
        {
            // 弹出开放列表中f值最小的节点，作为当前要探索的节点
            node = openList.pop();
            node->closed = true;

            // 如果当前节点就是目标节点，说明找到了路径，通过Util类中的函数回溯路径后返回节点指针向量
            if (node == endNode)
            {

                return Util::expandPath(Util::backtrace(endNode)); // backtrace函数返回的是从起始节点到目标节点的路径节点指针向量
                // return Util().backtrace(endNode);
            }

            // 调用虚函数识别当前节点的后继节点（不同的具体寻路算法子类会有不同的实现逻辑）
            _identifySuccessors(node);
        }

        // 如果循环结束仍未找到路径，返回空的节点指针向量表示寻路失败
        return std::vector<Node *>();
    }

    // 构造函数实现，初始化相关成员变量，并设置启发式函数类型
    JumpPointFinderBase::JumpPointFinderBase(Grid *_grid, Heuristic::Type type, bool _trackJumpRecursion)
    {
        grid = _grid;
        trackJumpRecursion = _trackJumpRecursion;
        heuristic.setHeuristicFunction(type);
    }

    // 识别后继节点函数，调用查找邻居节点和跳跃操作函数，不同子类可重写这两个函数
    void JumpPointFinderBase::_identifySuccessors(Node *node)
    {
        auto neighbors = _findNeighbors(node);
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            auto neighbor = neighbors[i];
            auto jumpPoint = _jump(neighbor.first, neighbor.second, node->x, node->y);
            if (!jumpPoint.empty())
            {
                Node *jumpNode = grid->getNodeAt(jumpPoint[0], jumpPoint[1]);
                if (jumpNode->closed)
                {
                    continue;
                }
                // d = Heuristic.octile(abs(jx - x), abs(jy - y));
                double d = octile(abs(jumpPoint[0] - node->x), abs(jumpPoint[1] - node->y));
                // double d = std::sqrt(std::pow(jumpPoint[0] - node->x, 2) + std::pow(jumpPoint[1] - node->y, 2));
                double ng = node->g + d;

                // 使用Heuristic类配置的启发式函数来计算h值
                jumpNode->h = heuristic.heuristic(std::abs(jumpNode->x - endNode->x), std::abs(jumpNode->y - endNode->y));
                jumpNode->f = jumpNode->g + jumpNode->h;
                jumpNode->parent = node;

                if (!jumpNode->opened)
                {
                    openList.push(jumpNode);
                    jumpNode->opened = true;
                }
                else
                {
                    openList.updateItem(jumpNode);
                }
            }
        }
    }
}