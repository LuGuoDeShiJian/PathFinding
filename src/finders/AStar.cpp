#include "finders/AStar.h"

namespace luguo::PathFind
{
    AStar::AStar(const DiagonalMovement diagonalMovement, const Heuristic::Type heuristicType, const double weight)
        : diagonalMovement(diagonalMovement), weight(weight), heuristics()
    {
        heuristics.setHeuristicFunction(heuristicType);
    }
    double AStar::heuristic(const Node *a, const Node *b)
    {
        return heuristics.heuristic(std::abs(b->x - a->x), std::abs(b->y - a->y));
    }

    std::vector<Node *> AStar::findPath(int startX, int startY, int endX, int endY, Grid *grid)
    {
        Node *startNode = grid->getNodeAt(startX, startY);
        Node *endNode = grid->getNodeAt(endX, endY);
        startNode->g = 0;
        startNode->f = 0;
        openList.push(startNode);
        startNode->opened = true;
        Node *node;
        while (!openList.empty())
        {
            node = openList.pop();
            node->closed = true;

            if (node == endNode)
            {
                return Util::backtrace(endNode);
            }

            std::vector<Node *> neighbors = grid->getNeighbors(node, diagonalMovement);
            for (Node *neighbor : neighbors)
            {
                if (neighbor->closed)
                    continue;

                double ng = node->g + ((neighbor->x - node->x == 0 || neighbor->y - node->y == 0) ? 1 : std::sqrt(2));

                if (!neighbor->opened || ng < neighbor->g)
                {
                    neighbor->g = ng;
                    neighbor->h = neighbor->h || weight * heuristic(endNode, neighbor);
                    neighbor->f = neighbor->g + neighbor->h;
                    neighbor->parent = node;

                    if (!neighbor->opened)
                    {
                        openList.push(neighbor);
                        neighbor->opened = true;
                    }
                    else
                    {
                        openList.updateItem(neighbor);
                    }
                }
            }
        }

        return std::vector<Node *>();
    }
}
