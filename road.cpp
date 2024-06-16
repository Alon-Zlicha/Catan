#include "road.hpp"
#include "edge.hpp"

namespace ariel
{
    Road::Road(Player *p, Edge *e)
        : Piece(p, e->getV1()->getX(), e->getV1()->getY()), vertex2(new Vertex(e->getV2()->getX(), e->getV2()->getY()))
    {
    }

    Road::~Road()
    {
        delete vertex2;
    }

    Vertex *Road::getVertex2()
    {
        return this->vertex2;
    }

    std::string Road::getType() const
    {
        return "Road";
    }

    bool Road::upgradeToCity()
    {
        // Roads cannot be upgraded to cities, so this function would typically return false
        return false;
    }
    std::string Road::toString() const
    {
        return "((" + std::to_string(vertex->getX()) + "," + std::to_string(vertex->getY()) + "),(" +
               std::to_string(vertex2->getX()) + "," + std::to_string(vertex2->getY()) + "))";
    }
}
