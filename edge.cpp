#include "edge.hpp"

namespace ariel
{
    Edge::Edge(Vertex *v1, Vertex *v2)
        : v1(v1), v2(v2), piece(nullptr) {}

    Edge::Edge() : v1(nullptr), v2(nullptr), piece(nullptr) {}

    Edge::~Edge()
    {
    }

    Vertex *Edge::getV1() const
    {
        return this->v1;
    }

    Vertex *Edge::getV2() const
    {
        return this->v2;
    }

    Piece *Edge::getPiece() const
    {
        return piece;
    }

    void Edge::setPiece(Piece *p)
    {
        piece = p;
    }

    void Edge::addToAdjacentEdges(Edge *edge)
    {
        if (edge->getV1() != nullptr && edge->getV2() != nullptr)
        {
            if (edge->getV1() == v1 || edge->getV1() == v2 || edge->getV2() == v1 || edge->getV2() == v2)
            {
                this->adjacentEdges.push_back(edge);
            }
        }
    }

    bool Edge::isAdjacentHex(const Hex &hex) const
    {
        if (v1 != nullptr && v2 != nullptr)
        {
            if (v1->isAdjacentHex(hex) && v2->isAdjacentHex(hex))
            {
                return true;
            }
        }
        return false;
    }

    bool Edge::isValidEdge()
    {
        if (this->getPiece() == nullptr)
        {
            return true;
        }
        return false;
    }

    bool Edge::isNearSettlement(const Player &p)
    {
        if (v1->getPiece() != nullptr && v1->getPiece()->getPlayer()->getName() == p.getName())
        {
            return true;
        }
        if (v2->getPiece() != nullptr && v2->getPiece()->getPlayer()->getName() == p.getName())
        {
            return true;
        }
        return false;
    }

    bool Edge::isNearRoad(const Player &p)
    {
        for (size_t i = 0; i < adjacentEdges.size(); i++)
        {
            if (adjacentEdges[i]->getPiece() != nullptr && adjacentEdges[i]->getPiece()->getPlayer()->getName() == p.getName())
            {
                return true;
            }
        }
        return false;
    }

}
