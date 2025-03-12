#include "finders/JPFMoveDiagonallyIfAtMostOneObstacle.h"

namespace luguo::PathFind
{
    // 构造函数实现，通过调用基类构造函数完成相关初始化工作
    JPFMoveDiagonallyIfAtMostOneObstacle::JPFMoveDiagonallyIfAtMostOneObstacle(Grid *grid, Heuristic::Type type, bool trackJumpRecursion) : JumpPointFinderBase(grid, type, trackJumpRecursion) {}

    // 重写_jump函数，按照特定规则（对角线移动仅当至多有一个障碍物时）进行跳跃点搜索逻辑的实现
    std::vector<int> JPFMoveDiagonallyIfAtMostOneObstacle::_jump(int x, int y, int px, int py)
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
            if ((grid->isWalkableAt(x - dx, y + dy) && !grid->isWalkableAt(x - dx, y)) ||
                (grid->isWalkableAt(x + dx, y - dy) && !grid->isWalkableAt(x, y - dy)))
            {
                return {x, y};
            }
            // 当沿对角线移动时，检查垂直/水平跳跃点
            if (this->_jump(x + dx, y, x, y).size() > 0 || this->_jump(x, y + dy, x, y).size() > 0)
            {
                return {x, y};
            }
        }
        // 水平/垂直方向
        else
        {
            if (dx != 0) // 沿x方向移动
            {
                if ((grid->isWalkableAt(x + dx, y + 1) && !grid->isWalkableAt(x, y + 1)) ||
                    (grid->isWalkableAt(x + dx, y - 1) && !grid->isWalkableAt(x, y - 1)))
                {
                    return {x, y};
                }
            }
            else
            {
                if ((grid->isWalkableAt(x + 1, y + dy) && !grid->isWalkableAt(x + 1, y)) ||
                    (grid->isWalkableAt(x - 1, y + dy) && !grid->isWalkableAt(x - 1, y)))
                {
                    return {x, y};
                }
            }
        }

        // 沿对角线移动时，确保垂直/水平邻居之一可通行以允许路径通过
        if (grid->isWalkableAt(x + dx, y) || grid->isWalkableAt(x, y + dy))
        {
            return this->_jump(x + dx, y + dy, x, y);
        }
        else
        {
            return {};
        }
    }

    // 重写_findNeighbors函数，依据特定规则（对角线移动仅当至多有一个障碍物时）查找给定节点的邻居节点
    std::vector<std::pair<int, int>> JPFMoveDiagonallyIfAtMostOneObstacle::_findNeighbors(Node *node)
    {
        Node *parent = node->parent;
        int x = node->x;
        int y = node->y;
        Grid *grid = this->grid;
        int px, py, nx, ny, dx, dy;
        std::vector<std::pair<int, int>> neighbors;

        // 有向剪枝：可忽略多数邻居，除非强制要求
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
                if (grid->isWalkableAt(x, y + dy) || grid->isWalkableAt(x + dx, y))
                {
                    neighbors.push_back({x + dx, y + dy});
                }
                if (!grid->isWalkableAt(x - dx, y) && grid->isWalkableAt(x, y + dy))
                {
                    neighbors.push_back({x - dx, y + dy});
                }
                if (!grid->isWalkableAt(x, y - dy) && grid->isWalkableAt(x + dx, y))
                {
                    neighbors.push_back({x + dx, y - dy});
                }
            }
            // 沿水平/垂直方向搜索
            else
            {
                if (dx == 0)
                {
                    if (grid->isWalkableAt(x, y + dy))
                    {
                        neighbors.push_back({x, y + dy});
                        if (!grid->isWalkableAt(x + 1, y))
                        {
                            neighbors.push_back({x + 1, y + dy});
                        }
                        if (!grid->isWalkableAt(x - 1, y))
                        {
                            neighbors.push_back({x - 1, y + dy});
                        }
                    }
                }
                else
                {
                    if (grid->isWalkableAt(x + dx, y))
                    {
                        neighbors.push_back({x + dx, y});
                        if (!grid->isWalkableAt(x, y + 1))
                        {
                            neighbors.push_back({x + dx, y + 1});
                        }
                        if (!grid->isWalkableAt(x, y - 1))
                        {
                            neighbors.push_back({x + dx, y - 1});
                        }
                    }
                }
            }
        }
        // 返回所有邻居
        else
        {
            std::vector<Node *> neighborNodes = grid->getNeighbors(node, DiagonalMovement::IfAtMostOneObstacle);
            for (size_t i = 0; i < neighborNodes.size(); ++i)
            {
                Node *neighborNode = neighborNodes[i];
                neighbors.push_back({neighborNode->x, neighborNode->y});
            }
        }

        return neighbors;
    }
}