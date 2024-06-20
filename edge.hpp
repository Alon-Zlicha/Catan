/*alonz1414@gmail.com*/
#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>
#include "piece.hpp"
#include "board.hpp"

namespace ariel
{
    class Vertex;
    class Hex;
    class Piece;
    class Player;
    class Edge
    {
    private:
        Vertex *v1;
        Vertex *v2;
        Piece *piece;
        std::vector<Edge *> adjacentEdges;

    public:
        Edge();
        ~Edge();
        Edge(Vertex *v1, Vertex *v2);
        Vertex *getV1() const;
        Vertex *getV2() const;
        Piece *getPiece() const;
        void addToAdjacentHexes(Hex *hex);
        void addToAdjacentEdges(Edge *edge);
        void setPiece(Piece *p);
        bool isAdjacentHex(const Hex &hex) const;
        bool isValidEdge();
        bool isNearSettlement(const Player &p);
        bool isNearRoad(const Player &p);
    };
}
#endif 
