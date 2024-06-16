#ifndef ROAD_HPP
#define ROAD_HPP

#include "piece.hpp"
#include "edge.hpp"

namespace ariel
{
    class Edge;
    class Road : public Piece
    {
    private:
        Vertex *vertex2;

    public:
        Road(Player *p, Edge *e);             
        ~Road(); 
        Vertex* getVertex2();         // needed beacuse the second vertex field
        std::string getType() const override; 
        bool upgradeToCity() override;        
        std::string toString() const override;
    };
}

#endif 
