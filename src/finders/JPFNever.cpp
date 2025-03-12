#include "finders/JPFNever.h"

namespace luguo::PathFind
{
    // 构造函数实现，调用基类构造函数进行初始化
    JPFNever::JPFNever(Grid *_grid, Heuristic::Type type, bool _trackJumpRecursion)
        : JumpPointFinderBase(_grid, type, _trackJumpRecursion)
    {
        heuristic.setHeuristicFunction(type);
    }

    // 重写_jump函数，实现跳跃点搜索逻辑，遵循只允许水平或垂直移动的规则
    std::vector<int> JPFNever::_jump(int x, int y, int px, int py)
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
            // 当垂直移动时，检查水平跳跃点
            if (this->_jump(x + 1, y, x, y).size() > 0 || this->_jump(x - 1, y, x, y).size() > 0)
            {
                return {x, y};
            }
        }
        else
        {
            // 这里可以考虑抛出更合适的异常类型，目前简单输出错误信息示例
            std::cerr << "Only horizontal and vertical movements are allowed" << std::endl;
            return {};
        }

        return this->_jump(x + dx, y + dy, x, y);
    }

    // 重写_findNeighbors函数，根据节点是否有父节点来查找邻居节点，遵循特定规则
    std::vector<std::pair<int, int>> JPFNever::_findNeighbors(Node *node)
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

            if (dx != 0)
            {
                if (grid->isWalkableAt(x, y - 1))
                {
                    neighbors.push_back({x, y - 1});
                }
                if (grid->isWalkableAt(x, y + 1))
                {
                    neighbors.push_back({x, y + 1});
                }
                if (grid->isWalkableAt(x + dx, y))
                {
                    neighbors.push_back({x + dx, y});
                }
            }
            else if (dy != 0)
            {
                if (grid->isWalkableAt(x - 1, y))
                {
                    neighbors.push_back({x - 1, y});
                }
                if (grid->isWalkableAt(x + 1, y))
                {
                    neighbors.push_back({x + 1, y});
                }
                if (grid->isWalkableAt(x, y + dy))
                {
                    neighbors.push_back({x, y + dy});
                }
            }
        }
        // 返回所有邻居
        else
        {
            std::vector<Node *> neighborNodes = grid->getNeighbors(node, DiagonalMovement::Never);
            for (size_t i = 0; i < neighborNodes.size(); ++i)
            {
                Node *neighborNode = neighborNodes[i];
                neighbors.push_back({neighborNode->x, neighborNode->y});
            }
        }

        return neighbors;
    }
}