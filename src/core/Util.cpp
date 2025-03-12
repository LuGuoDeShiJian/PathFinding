#include "core/Util.h"
#include <bits/algorithmfwd.h>

namespace luguo::PathFind
{
    std::vector<Node *> Util::backtrace(Node *node)
    {
        std::vector<Node *> path;
        while (node)
        {
            path.emplace_back(node);
            node = node->parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    std::vector<Node *> Util::biBacktrace(Node *a, Node *b)
    {
        auto pathA = backtrace(a);
        auto pathB = backtrace(b);
        pathA.insert(pathA.end(), pathB.rbegin() + 1, pathB.rend());
        return pathA;
    }

    double Util::pathLength(const std::vector<Node *> &path)
    {
        double len = 0.0;
        for (size_t i = 1; i < path.size(); ++i)
        {
            int dx = path[i - 1]->x - path[i]->x;
            int dy = path[i - 1]->y - path[i]->y;
            len += std::hypot(dx, dy);
        }
        return len;
    }

    std::vector<Node *> Util::interpolate(int x0, int y0, int x1, int y1)
    {
        std::vector<Node *> line;
        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            line.emplace_back(new Node(x0, y0));
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y0 += sy;
            }
        }
        return line;
    }

    std::vector<Node *> Util::expandPath(const std::vector<Node *> &path)
    {
        if (path.size() < 2)
            return {};
        std::vector<Node *> expanded;
        for (size_t i = 0; i < path.size() - 1; ++i)
        {
            auto seg = interpolate(path[i]->x, path[i]->y, path[i + 1]->x, path[i + 1]->y);
            expanded.insert(expanded.end(), seg.begin(), seg.end());
        }
        expanded.pop_back();
        return expanded;
    }

    std::vector<Node *> Util::smoothenPath(const Grid &grid, const std::vector<Node *> &path)
    {
        if (path.size() < 3)
            return path;
        std::vector<Node *> newPath = {path[0]};
        int sx = path[0]->x, sy = path[0]->y;
        int ex = path.back()->x, ey = path.back()->y;

        for (size_t i = 2; i < path.size(); ++i)
        {
            int nx = path[i]->x, ny = path[i]->y;
            std::vector<Node *> line = interpolate(sx, sy, nx, ny);
            bool blocked = false;
            for (size_t j = 1; j < line.size(); ++j)
                if (!grid.isWalkableAt(line[j]->x, line[j]->y))
                {
                    blocked = true;
                    break;
                }
            if (blocked)
            {
                newPath.push_back(line.back());
                sx = line.back()->x;
                sy = line.back()->y;
            }
        }
        newPath.push_back(path.back());
        return newPath;
    }

    std::vector<Node *> Util::compressPath(const std::vector<Node *> &path)
    {
        if (path.size() < 3)
            return path;
        std::vector<Node *> compressed;
        compressed.reserve(path.size());

        compressed.push_back(path[0]);
        Node *prev = path[0];
        for (size_t i = 1; i < path.size(); ++i)
        {
            Node *curr = path[i];
            int dx = curr->x - prev->x;
            int dy = curr->y - prev->y;
            double dist = std::hypot(dx, dy);
            if (dist >= 1.0)
            {
                compressed.push_back(curr);
                prev = curr;
            }
        }
        return compressed;
    }
}
