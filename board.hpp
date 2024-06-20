/*alonz1414@gmail.com*/
#ifndef BOARD_HPP
#define BOARD_HPP

#include "hex.hpp"
#include "vertex.hpp"
#include "player.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

namespace ariel
{
    class Edge;
    class Board
    {
    private:
        std::vector<std::vector<Hex>> hexes;
        std::vector<std::vector<Vertex>> vertices;
        std::vector<Edge *> edges;

    public:
        Board();
        ~Board();
        Board(const Board &other); // copy constuctor
        void printHexas();
        bool addSettlementToBoard(size_t x, size_t y, Piece *piece);
        bool addRoadToBoard(Edge &e, Piece &piece);
        std::vector<std::vector<Vertex>> &getVertices();
        std::vector<std::vector<Hex>> &getHexes();
        void addResources(int number) const; // for roll dice
        Edge *getEdgeByCoordinates(size_t x1, size_t y1, size_t x2, size_t y2);
        Vertex *getVertexByCoordinates(size_t x, size_t y);

    private:
        void initBoard();
        void initHexes();
        void initVertices();
        void initEdges();
    };
}

#endif
