#pragma once
#include <vector>
#include <memory>
#include "Node.h"
#include "DiagonalMovement.h"

namespace luguo::PathFind
{
    class Grid
    {
    public:
        Grid(int width, int height, const std::vector<std::vector<bool>> &matrix = {});
        Grid(const std::vector<std::vector<bool>> &matrix);
        ~Grid();

        Node *getNodeAt(int x, int y) const;
        bool isWalkableAt(int x, int y) const;
        bool isInside(int x, int y) const;
        void setWalkableAt(int x, int y, bool walkable);
        std::vector<Node *> getNeighbors(const Node *node, DiagonalMovement movement) const;

        Grid *clone() const;

        int getWidth() const;
        int getHeight() const;
        int getWalkableCount() const;

    private:
        int width;
        int height;
        std::vector<std::vector<std::unique_ptr<Node>>> nodes;

        void buildNodes(const std::vector<std::vector<bool>> &matrix);
    };
}