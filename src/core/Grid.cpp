#include "core/Grid.h"

namespace luguo::PathFind
{
    Grid::Grid(int width, int height, const std::vector<std::vector<bool>> &matrix) : width(width), height(height)
    {
        _buildNodes(matrix);
    }

    Grid::Grid(const std::vector<std::vector<bool>> &matrix) : width(matrix[0].size()), height(matrix.size())
    {
        _buildNodes(matrix);
    }
    Grid::~Grid()
    {
        for (auto &row : nodes)
        {
            for (auto &node : row)
            {
                delete node;
            }
            row.clear();
        }
        nodes.clear();
    }

    Node *Grid::getNodeAt(int x, int y)
    {
        if (isInside(x, y))
        {
            return nodes[y][x];
        }
        return nullptr;
    }

    bool Grid::isWalkableAt(int x, int y) const
    {
        return isInside(x, y) && nodes[y][x]->walkable;
    }

    bool Grid::isInside(int x, int y) const
    {
        if (nodes.empty() || nodes[0].empty())
        {
            std::cerr << "Grid is not properly initialized. Cannot determine if the coordinate is inside the grid." << std::endl;
            return false;
        }
        return (x >= 0 && x < width) && (y >= 0 && y < height);
    }

    void Grid::setWalkableAt(int x, int y, bool walkable)
    {
        if (isInside(x, y))
        {
            nodes[y][x]->walkable = walkable;
        }
        else
        {
            std::cerr << "Coordinate is outside the grid, cannot set walkable status." << std::endl;
        }
    }
    std::vector<Node *> Grid::getNeighbors(const Node *node, DiagonalMovement diagonalMovement)
    {
        int x = node->x;
        int y = node->y;
        std::vector<Node *> neighbors;
        bool s0 = false, d0 = false;
        bool s1 = false, d1 = false;
        bool s2 = false, d2 = false;
        bool s3 = false, d3 = false;

        // ↑
        if (isWalkableAt(x, y - 1))
        {
            neighbors.push_back(nodes[y - 1][x]);
            s0 = true;
        }
        // →
        if (isWalkableAt(x + 1, y))
        {
            neighbors.push_back(nodes[y][x + 1]);
            s1 = true;
        }
        // ↓
        if (isWalkableAt(x, y + 1))
        {
            neighbors.push_back(nodes[y + 1][x]);
            s2 = true;
        }
        // ←
        if (isWalkableAt(x - 1, y))
        {
            neighbors.push_back(nodes[y][x - 1]);
            s3 = true;
        }

        switch (diagonalMovement)
        {
        case DiagonalMovement::Never:
            return neighbors;
        case DiagonalMovement::OnlyWhenNoObstacles:
            d0 = s3 && s0;
            d1 = s0 && s1;
            d2 = s1 && s2;
            d3 = s2 && s3;
            break;
        case DiagonalMovement::IfAtMostOneObstacle:
            d0 = s3 || s0;
            d1 = s0 || s1;
            d2 = s1 || s2;
            d3 = s2 || s3;
            break;
        case DiagonalMovement::Always:
            d0 = true;
            d1 = true;
            d2 = true;
            d3 = true;
            break;
        default:
            std::cerr << "Incorrect value of diagonalMovement" << std::endl;
            return neighbors;
        }

        // ↖
        if (d0 && isWalkableAt(x - 1, y - 1))
        {
            neighbors.push_back(nodes[y - 1][x - 1]);
        }
        // ↗
        if (d1 && isWalkableAt(x + 1, y - 1))
        {
            neighbors.push_back(nodes[y - 1][x + 1]);
        }
        // ↘
        if (d2 && isWalkableAt(x + 1, y + 1))
        {
            neighbors.push_back(nodes[y + 1][x + 1]);
        }
        // ↙
        if (d3 && isWalkableAt(x - 1, y + 1))
        {
            neighbors.push_back(nodes[y + 1][x - 1]);
        }

        return neighbors;
    }

    Grid *Grid::clone()
    {
        std::vector<std::vector<bool>> matrix(height, std::vector<bool>(width));
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                matrix[i][j] = nodes[i][j]->walkable;
            }
        }

        Grid *newGrid = new Grid(width, height, matrix);
        return newGrid;
    }

    void Grid::_buildNodes(const std::vector<std::vector<bool>> &matrix)
    {
        nodes.resize(height);
        for (int i = 0; i < height; ++i)
        {
            nodes[i].resize(width);
            for (int j = 0; j < width; ++j)
            {
                nodes[i][j] = new Node(j, i);
            }
        }

        if (!matrix.empty() && matrix.size() == height && matrix[0].size() == width)
        {
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    // 0表示可通行，1表示不可通行
                    nodes[i][j]->walkable = matrix[i][j] == 0;
                }
            }
        }
    }
}