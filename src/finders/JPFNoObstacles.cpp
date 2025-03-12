#include "finders/JPFNoObstacles.h"

namespace luguo::PathFind
{
    // 构造函数实现，调用基类构造函数来完成初始化操作
    JPFNoObstacles::JPFNoObstacles(Grid *grid, Heuristic::Type type, bool trackJumpRecursion) : JumpPointFinderBase(grid, type, trackJumpRecursion) {}

    // 重写_jump函数，实现按照特定规则（对角线移动仅当无障碍物时）的跳跃点搜索逻辑
    std::vector<int> JPFNoObstacles::_jump(int x, int y, int px, int py)
    {
        Grid *grid = this->grid;
        int dx = x - px;
        int dy = y - py;

        if (!grid->isWalkableAt(x, y))
        {
            return {};
        }

        if (this->trackJumpRecursion)
        {
            Node *node = grid->getNodeAt(x, y);
            node->tested = true;
        }

        if (grid->getNodeAt(x, y) == this->endNode)
        {
            return {x, y};
        }

        // 检查强制邻居，沿对角线方向
        if (dx != 0 && dy != 0)
        {
            // if ((grid->isWalkableAt(x - dx, y + dy) &&!grid->isWalkableAt(x - dx, y)) ||
            //     (grid->isWalkableAt(x + dx, y - dy) &&!grid->isWalkableAt(x, y - dy)))
            // {
            //     return {x, y};
            // }
            // 当沿对角线移动时，必须检查垂直/水平跳跃点
            if (this->_jump(x + dx, y, x, y).size() > 0 || this->_jump(x, y + dy, x, y).size() > 0)
            {
                return {x, y};
            }
        }
        // 水平/垂直方向
        else
        {
            if (dx != 0)
            {
                if ((grid->isWalkableAt(x, y - 1) && !grid->isWalkableAt(x - dx, y - 1)) ||
                    (grid->isWalkableAt(x, y + 1) && !grid->isWalkableAt(x - dx, y + 1)))
                {
                    return {x, y};
                }
            }
            else if (dy != 0)
            {
                if ((grid->isWalkableAt(x - 1, y) && !grid->isWalkableAt(x - 1, y - dy)) ||
                    (grid->isWalkableAt(x + 1, y) && !grid->isWalkableAt(x + 1, y - dy)))
                {
                    return {x, y};
                }
                // 当垂直移动时，原本检查水平跳跃点的部分（目前被注释掉，可根据实际需求决定是否启用）
                // if (this->_jump(x + 1, y, x, y).size() > 0 || this->_jump(x - 1, y, x, y).size() > 0)
                // {
                //     return {x, y};
                // }
            }
        }

        // 沿对角线移动时，必须确保垂直/水平邻居之一是可通行的，以允许路径通过
        if (grid->isWalkableAt(x + dx, y) && grid->isWalkableAt(x, y + dy))
        {
            return this->_jump(x + dx, y + dy, x, y);
        }
        else
        {
            return {};
        }
    }

    // 重写_findNeighbors函数，按照特定规则（对角线移动仅当无障碍物时）查找给定节点的邻居节点
    std::vector<std::pair<int, int>> JPFNoObstacles::_findNeighbors(Node *node)
    {
        Node *parent = node->parent;
        int x = node->x;
        int y = node->y;
        Grid *grid = this->grid;
        int px, py, nx, ny, dx, dy;
        std::vector<std::pair<int, int>> neighbors;

        // 有向剪枝：可以忽略大多数邻居，除非强制
        if (parent)
        {
            px = parent->x;
            py = parent->y;
            // 获取归一化的移动方向
            dx = (x - px) / std::max(std::abs(x - px), 1);
            dy = (y - py) / std::max(std::abs(y - py), 1);

            // 沿对角线方向搜索
            if (dx != 0 && dy != 0)
            {
                if (grid->isWalkableAt(x, y + dy))
                {
                    neighbors.push_back({x, y + dy});
                }
                if (grid->isWalkableAt(x + dx, y))
                {
                    neighbors.push_back({x + dx, y});
                }
                if (grid->isWalkableAt(x, y + dy) && grid->isWalkableAt(x + dx, y))
                {
                    neighbors.push_back({x + dx, y + dy});
                }
            }
            // 沿水平/垂直方向搜索
            else
            {
                bool isNextWalkable;
                if (dx != 0)
                {
                    isNextWalkable = grid->isWalkableAt(x + dx, y);
                    bool isTopWalkable = grid->isWalkableAt(x, y + 1);
                    bool isBottomWalkable = grid->isWalkableAt(x, y - 1);

                    if (isNextWalkable)
                    {
                        neighbors.push_back({x + dx, y});
                        if (isTopWalkable)
                        {
                            neighbors.push_back({x + dx, y + 1});
                        }
                        if (isBottomWalkable)
                        {
                            neighbors.push_back({x + dx, y - 1});
                        }
                    }
                    if (isTopWalkable)
                    {
                        neighbors.push_back({x, y + 1});
                    }
                    if (isBottomWalkable)
                    {
                        neighbors.push_back({x, y - 1});
                    }
                }
                else if (dy != 0)
                {
                    isNextWalkable = grid->isWalkableAt(x, y + dy);
                    bool isRightWalkable = grid->isWalkableAt(x + 1, y);
                    bool isLeftWalkable = grid->isWalkableAt(x - 1, y);

                    if (isNextWalkable)
                    {
                        neighbors.push_back({x, y + dy});
                        if (isRightWalkable)
                        {
                            neighbors.push_back({x + 1, y + dy});
                        }
                        if (isLeftWalkable)
                        {
                            neighbors.push_back({x - 1, y + dy});
                        }
                    }
                    if (isRightWalkable)
                    {
                        neighbors.push_back({x + 1, y});
                    }
                    if (isLeftWalkable)
                    {
                        neighbors.push_back({x - 1, y});
                    }
                }
            }
        }
        // 返回所有邻居
        else
        {
            std::vector<Node *> neighborNodes = grid->getNeighbors(node, DiagonalMovement::OnlyWhenNoObstacles);
            for (size_t i = 0; i < neighborNodes.size(); ++i)
            {
                Node *neighborNode = neighborNodes[i];
                neighbors.push_back({neighborNode->x, neighborNode->y});
            }
        }

        return neighbors;
    }
}