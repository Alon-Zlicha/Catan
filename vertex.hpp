#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <cstddef>
#include "piece.hpp"
#include "hex.hpp"
namespace ariel
{
    class Edge;
    class Vertex
    {
    private:
        // Coordinates of the vertex
        size_t x;
        size_t y;
        Piece *piece;
        // Adjacent hexes and edges
        std::vector<Hex *> adjacentHexes;
        std::vector<Edge *> adjacentEdges;
        std::vector<Vertex*> adjacentVertices;

    public:
        Vertex();
        Vertex(size_t x, size_t y);
        size_t getX() const;
        size_t getY() const;
        std::vector<Hex *>  getAdjacentHexes() const;
        void addToAdjacentHexes(Hex *hex);
        void addToAdjacentEdges(Edge *edge);
        void addToAdjacentVertices(Vertex * vertex);
        void printAdjHexes();
        void printAdjVertices();
        void printAdjEdges();
        bool isAdjacentHex(const Hex &hex) const;
        bool isValidVertex();
        Piece *getPiece() const;
        void setPiece(Piece *p);
        friend bool operator==(const Vertex &v1, const Vertex &v2);
        bool isNearRoad(const Player &p);
        bool isFarFromSettlement(const Player &p);
    };
}

#endif 
