#include "PathFind.h"

namespace luguo::PathFind
{
    std::vector<Node *> findPath(Node *start, Node *end, Grid *grid, const PathFindType &type, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight)
    {
        switch (type)
        {
        case PathFindType::JPSFind:
            return JPSfind(start, end, grid, heuristicType, diagonalMovement);
        case PathFindType::IDAFind:
            return IDAfind(start, end, grid, heuristicType, diagonalMovement, weight);
        case PathFindType::AStarFind:
            return AStarfind(start, end, grid, heuristicType, diagonalMovement, weight);
        case PathFindType::BestFind:
            return Bestfind(start, end, grid, heuristicType, diagonalMovement, weight);
        case PathFindType::BFSFind:
            return BFSfind(start, end, grid, diagonalMovement);
        case PathFindType::DIJKFind:
            return DIJKfind(start, end, grid, heuristicType, diagonalMovement, weight);
        default:
            return std::vector<Node *>();
        }
    }
    std::vector<Node *> JPSfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement)
    {
        JPSFind F(grid, heuristicType, diagonalMovement);
        JPSBase *FP = F.createFinder();
        auto FH = FP->findPath(start->x, start->y, end->x, end->y);
        delete FP;
        return FH;
    }
    std::vector<Node *> IDAfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight)
    {
        weight = weight < 1 ? 1 : weight;
        IDAFind F(diagonalMovement, heuristicType, weight);
        return F.findPath(start->x, start->y, end->x, end->y, grid);
    }
    std::vector<Node *> AStarfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight)
    {
        weight = weight < 1 ? 1 : weight;
        AStarFind F(diagonalMovement, heuristicType, weight);
        return F.findPath(start->x, start->y, end->x, end->y, grid);
    }
    std::vector<Node *> Bestfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight)
    {
        weight = weight < 1 ? 1 : weight;
        BestFind F(diagonalMovement, heuristicType, weight);
        return F.findPath(start->x, start->y, end->x, end->y, grid);
    }
    std::vector<Node *> BFSfind(Node *start, Node *end, Grid *grid, DiagonalMovement diagonalMovement)
    {
        BFSFind F(diagonalMovement);
        return F.findPath(start->x, start->y, end->x, end->y, grid);
    }
    std::vector<Node *> DIJKfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight)
    {
        weight = weight < 1 ? 1 : weight;
        DIJKFind F(diagonalMovement, heuristicType, weight);
        return F.findPath(start->x, start->y, end->x, end->y, grid);
    }
}