#include "core/Util.h"

namespace luguo::PathFind
{
    std::vector<Node *> Util::backtrace(const Node *node)
    {
        std::vector<Node *> path;
        const Node *currentNode = node;
        while (currentNode != nullptr)
        {
            path.push_back(const_cast<Node *>(currentNode));
            currentNode = currentNode->parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    std::vector<Node *> Util::biBacktrace(const Node *nodeA, const Node *nodeB)
    {
        std::vector<Node *> pathA = Util::backtrace(nodeA);
        std::vector<Node *> pathB = Util::backtrace(nodeB);
        std::vector<Node *> combinedPath;
        combinedPath = pathA;
        combinedPath.insert(combinedPath.end(), pathB.rbegin(), pathB.rend());
        return combinedPath;
    }

    double Util::pathLength(const std::vector<Node *> &path)
    {
        if (path.size() < 2)
        {
            return 0.0;
        }
        double sum = 0.0;
        for (size_t i = 1; i < path.size(); ++i)
        {
            Node *prevNode = path[i - 1];
            Node *currNode = path[i];
            int dx = prevNode->x - currNode->x;
            int dy = prevNode->y - currNode->y;
            sum += std::sqrt(static_cast<double>(dx * dx + dy * dy));
        }
        return sum;
    }

    std::vector<Node *> Util::interpolate(int x0, int y0, int x1, int y1)
    {
        std::vector<Node *> line;
        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;
        int e2;

        while (true)
        {
            Node *node = new Node(x0, y0);
            line.push_back(node);
            if (x0 == x1 && y0 == y1)
            {
                break;
            }
            e2 = 2 * err;
            if (e2 > -dy)
            {
                err = err - dy;
                x0 += sx;
            }
            if (e2 < dx)
            {
                err = err + dx;
                y0 += sy;
            }
        }
        if (!line.empty())
        {
            line.pop_back();
        }
        return line;
    }

    // Given a compressed path, return a new path that has all the segments
    // in it interpolated.
    std::vector<Node *> Util::expandPath(const std::vector<Node *> &path)
    {
        if (path.size() < 2)
        {
            return std::vector<Node *>();
        }
        std::vector<Node *> expanded;
        for (size_t i = 0; i < path.size() - 1; ++i)
        {
            Node *node0 = path[i];
            Node *node1 = path[i + 1];
            std::vector<Node *> interpolated = Util::interpolate(node0->x, node0->y, node1->x, node1->y);
            expanded.insert(expanded.end(), interpolated.begin(), interpolated.end());
        }
        expanded.push_back(path.back());
        return expanded;
    }

    // Smoothen the given path.
    std::vector<Node *> Util::smoothenPath(const Grid &grid, const std::vector<Node *> &path)
    {
        assert(path.size() >= 3 && "Input path should have at least 3 nodes for smoothening.");
        int x0 = path[0]->x;
        int y0 = path[0]->y;
        int x1 = path.back()->x;
        int y1 = path.back()->y;
        int sx = x0;
        int sy = y0;
        std::vector<Node *> newPath = {path[0]};

        for (size_t i = 2; i < path.size(); ++i)
        {
            Node *node = path[i];
            int ex = node->x;
            int ey = node->y;
            std::vector<Node *> line = Util::interpolate(sx, sy, ex, ey);
            bool blocked = false;
            for (size_t j = 1; j < line.size(); ++j)
            {
                Node *testNode = line[j];
                if (!grid.isWalkableAt(testNode->x, testNode->y))
                {
                    blocked = true;
                    break;
                }
            }
            if (blocked)
            {
                Node *lastValidNode = path[i - 1];
                newPath.push_back(lastValidNode);
                sx = lastValidNode->x;
                sy = lastValidNode->y;
            }
        }
        newPath.push_back(path.back());
        return newPath;
    }

    // Compress a path, remove redundant nodes without altering the shape
    std::vector<Node *> Util::compressPath(const std::vector<Node *> &path)
    {
        if (path.size() < 3)
        {
            return path;
        }
        std::vector<Node *> compressed;
        int sx = path[0]->x;
        int sy = path[0]->y;
        Node *px = path[1];
        Node *py = path[1];
        int dx = px->x - sx;
        int dy = py->y - sy;
        double sq = std::sqrt(static_cast<double>(dx * dx + dy * dy));
        dx /= sq;
        dy /= sq;
        compressed.push_back(path[0]);

        for (size_t i = 2; i < path.size(); ++i)
        {
            Node *lx = px;
            Node *ly = py;
            Node *ldx = new Node(dx, dy);
            Node *ldy = new Node(dx, dy);
            px = path[i];
            py = path[i];
            dx = px->x - lx->x;
            dy = px->y - ly->y;
            double newSq = std::sqrt(static_cast<double>(dx * dx + dy * dy));
            dx /= newSq;
            dy /= newSq;
            if (dx != ldx->x || dy != ldy->y)
            {
                compressed.push_back(lx);
            }
        }
        compressed.push_back(px);
        return compressed;
    }
}
