#include "finders/BreadthFirstFinder.h"
#include <queue>

namespace luguo::PathFind
{
    BreadthFirstFinder::BreadthFirstFinder(DiagonalMovement diagonalMovement) : diagonalMovement(diagonalMovement) {}
    std::vector<Node *> BreadthFirstFinder::findPath(int startX, int startY, int endX, int endY, Grid *grid)
    {
        std::queue<Node *> openList;
        Node *startNode = grid->getNodeAt(startX, startY);
        Node *endNode = grid->getNodeAt(endX, endY);
        Node *node;
        std::vector<Node *> neighbors;

        openList.push(startNode);
        startNode->opened = true;

        while (!openList.empty())
        {
            node = openList.front();
            openList.pop();
            node->closed = true;

            if (node == endNode)
            {
                return Util::backtrace(endNode);
            }

            neighbors = grid->getNeighbors(node, diagonalMovement);
            for (auto &neighbor : neighbors)
            {
                if (neighbor->closed || neighbor->opened)
                {
                    continue;
                }

                openList.push(neighbor);
                neighbor->opened = true;
                neighbor->parent = node;
            }
        }

        return std::vector<Node *>();
    }
}
