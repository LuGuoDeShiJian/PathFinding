#include "core/Grid.h"
namespace luguo::PathFind
{
    Grid::Grid(int width, int height, const std::vector<std::vector<bool>> &matrix)
        : width(width), height(height)
    {
        buildNodes(matrix);
    }

    Grid::Grid(const std::vector<std::vector<bool>> &matrix)
        : width(matrix[0].size()), height(matrix.size())
    {
        buildNodes(matrix);
    }

    Grid::~Grid() = default;

    Node *Grid::getNodeAt(int x, int y) const
    {
        if (!isInside(x, y))
            return nullptr;
        return nodes[y][x].get();
    }

    bool Grid::isWalkableAt(int x, int y) const
    {
        return isInside(x, y) && nodes[y][x]->walkable;
    }

    bool Grid::isInside(int x, int y) const
    {
        if (nodes.empty() || nodes[0].empty())
            return false;
        return (x >= 0 && x < width) && (y >= 0 && y < height);
    }
    void Grid::setWalkableAt(int x, int y, bool walkable)
    {
        if (isInside(x, y))
            nodes[y][x]->walkable = walkable;
    }

    std::vector<Node *> Grid::getNeighbors(const Node *node, DiagonalMovement movement) const
    {
        int x = node->x;
        int y = node->y;
        std::vector<Node *> neighbors;

        // Precompute walkability for all 8 directions
        bool dirs[8] = {
            isWalkableAt(x, y - 1),     // Up
            isWalkableAt(x + 1, y),     // Right
            isWalkableAt(x, y + 1),     // Down
            isWalkableAt(x - 1, y),     // Left
            isWalkableAt(x - 1, y - 1), // Top-left
            isWalkableAt(x + 1, y - 1), // Top-right
            isWalkableAt(x + 1, y + 1), // Bottom-right
            isWalkableAt(x - 1, y + 1)  // Bottom-left
        };

        static const int dx[8] = {0, 1, 0, -1, -1, 1, 1, -1};
        static const int dy[8] = {-1, 0, 1, 0, -1, -1, 1, 1};

        switch (movement)
        {
        case DiagonalMovement::Never:
            for (int i = 0; i < 4; ++i)
                if (dirs[i])
                    neighbors.push_back(nodes[y + dy[i]][x + dx[i]].get());
            break;
        case DiagonalMovement::OnlyWhenNoObstacles:
            for (int i = 4; i < 8; ++i)
                if (dirs[i] && (dirs[i - 4] || dirs[i - 3] || dirs[i - 2] || dirs[i - 1]))
                    neighbors.push_back(nodes[y + dy[i]][x + dx[i]].get());
            [[fallthrough]];
        case DiagonalMovement::IfAtMostOneObstacle:
            for (int i = 4; i < 8; ++i)
                if (dirs[i] && (dirs[i - 4] + dirs[i - 3] + dirs[i - 2] + dirs[i - 1]) <= 1)
                    neighbors.push_back(nodes[y + dy[i]][x + dx[i]].get());
            [[fallthrough]];
        case DiagonalMovement::Always:
            for (int i = 0; i < 8; ++i)
                if (dirs[i])
                    neighbors.push_back(nodes[y + dy[i]][x + dx[i]].get());
            break;
        }

        return neighbors;
    }

    Grid *Grid::clone() const
    {
        auto newGrid = new Grid(width, height);
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                newGrid->nodes[y][x]->walkable = nodes[y][x]->walkable;
        return newGrid;
    }

    int Grid::getWidth() const
    {
        return width;
    }
    int Grid::getHeight() const
    {
        return height;
    }
    int Grid::getWalkableCount() const
    {
        int count = 0;
        for (const auto &row : nodes)
        {
            for (const auto &node : row)
            {
                if (node->walkable)
                    count++;
            }
        }
        return count;
    }
    void Grid::buildNodes(const std::vector<std::vector<bool>> &matrix)
    {
        nodes.resize(height);
        for (int y = 0; y < height; ++y)
        {
            nodes[y].resize(width);
            for (int x = 0; x < width; ++x)
                nodes[y][x] = std::make_unique<Node>(x, y, matrix.empty() ? true : matrix[y][x] == 0);
        }
    }
}