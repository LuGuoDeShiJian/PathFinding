#pragma once
#include "finders/IDAStarFinder.h"
#include "finders/JumpPointFinder.h"
#include "finders/AStarFinder.h"
#include "finders/BestFirstFinder.h"
#include "finders/BreadthFirstFinder.h"
#include "finders/DijkstraFinder.h"
namespace luguo::PathFind
{
    enum class PathFindType
    {
        /**
         * @brief 跳跃点寻路
         */
        JPSFind,
        /**
         * @brief 迭代加深A*寻路
         */
        IDAFind,
        /**
         * @brief A*寻路
         */
        AStarFind,
        /**
         * @brief 基于A*的最佳优先寻路
         */
        BestFind,
        /**
         * @brief 广度优先寻路
         */
        BFSFind,
        /**
         * @brief 基于Dijkstra的最佳优先寻路
         */
        DIJKFind
    };
    typedef JumpPointFinder JPSFind;
    typedef IDAStarFinder IDAFind;
    typedef JumpPointFinderBase JPSBase;
    typedef AStarFinder AStarFind;
    typedef BestFirstFinder BestFind;
    typedef BreadthFirstFinder BFSFind;
    typedef DijkstraFinder DIJKFind;

    /**
     *  @brief 返回指定寻路算法类型的名称
     *  @param PathFindType 寻路算法类型
     *  @return 寻路算法类型的名称
     */
    inline std::string getName(PathFindType T, int lang = 0)
    {
        switch (T)
        {
        case PathFindType::JPSFind:
            if (lang == 0)
                return "跳点寻路";
            return "Jump Point Finder";
        case PathFindType::IDAFind:
            if (lang == 0)
                return "迭代加深A*寻路";
            return "IADStar Finder";
        case PathFindType::AStarFind:
            if (lang == 0)
                return "A*寻路";
            return "AStar Finder";
        case PathFindType::BestFind:
            if (lang == 0)
                return "最佳优先寻路";
            return "Best First Finder";
        case PathFindType::BFSFind:
            if (lang == 0)
                return "广度优先寻路";
            return "Breadth First Finder";
        case PathFindType::DIJKFind:
            if (lang == 0)
                return "Dijkstra寻路";
            return "Dijkstra Finder";
        default:
            return "Unknown";
        }
    }
    /**
     * 为二维网格进行路径查找
     * @param start 起点，类型为 Node*
     * @param end 终点，类型为 Node*
     * @param grid 地图网格，类型为 Grid*
     * @param type 路径查找类型，类型为 const PathFindType&
     * @param heuristicType 启发式类型，类型为 const Heuristic::Type&
     * @param diagonalMovement 对角线移动方式，类型为 DiagonalMovement
     * @return 包含路径节点的向量，如果找不到路径则返回空向量
     */
    std::vector<Node *> findPath(Node *start, Node *end, Grid *grid, const PathFindType &type, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight = 1);

    std::vector<Node *> JPSfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement);
    std::vector<Node *> IDAfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight);
    std::vector<Node *> AStarfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight);
    std::vector<Node *> Bestfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight);
    std::vector<Node *> BFSfind(Node *start, Node *end, Grid *grid, DiagonalMovement diagonalMovement);
    std::vector<Node *> DIJKfind(Node *start, Node *end, Grid *grid, const Heuristic::Type &heuristicType, DiagonalMovement diagonalMovement, double weight);
}