/*alonz1414@gmail.com*/
#include "vertex.hpp"
#include "board.hpp"

namespace ariel
{
    Vertex::Vertex() : x(0), y(0), piece(nullptr) {}
    Vertex::Vertex(size_t x, size_t y) : x(x), y(y), piece(nullptr) {}

    size_t Vertex::getX() const
    {
        return x;
    }
    size_t Vertex::getY() const
    {
        return y;
    }

    Piece *Vertex::getPiece() const
    {
        return piece;
    }
    void Vertex::setPiece(Piece *p)
    {
        piece = p;
    }

    bool Vertex::isNearRoad()
    {
        for (size_t i = 0; i < adjacentEdges.size(); i++)
        {
            if (adjacentEdges[i]->getPiece() != nullptr)
            {
                return true;
            }
        }
        return false;
    }

    bool Vertex::isFarFromSettlement()
    {
        for (size_t i = 0; i < adjacentVertices.size();i++)
        {
            if (adjacentVertices[i] != nullptr)
            {
                if (adjacentVertices[i]->getPiece() != nullptr)
                {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<Vertex *> &Vertex::getAdjacentVertices()
    {
        return adjacentVertices;
    }

    std::vector<Hex *> Vertex::getAdjacentHexes() const
    {
        return this->adjacentHexes;
    }

    void Vertex::addToAdjacentHexes(Hex *hex)
    {
        this->adjacentHexes.push_back(hex);
    }

    void Vertex::addToAdjacentEdges(Edge *edge)
    {
        this->adjacentEdges.push_back(edge);
    }

    void Vertex::addToAdjacentVertices(Vertex *vertex)
    {
        this->adjacentVertices.push_back(vertex);
    }

    bool Vertex::isAdjacentHex(const Hex &hex) const
    {
        for (size_t i = 0; i < adjacentHexes.size(); i++)
        {
            if (adjacentHexes[i]->getID() == hex.getID())
            {
                return true;
            }
        }
        return false;
    }

    bool Vertex::isValidVertex()
    {
        if (this->piece == nullptr)
        {
            return true;
        }
        return false;
    }

    bool operator==(const Vertex &v1, const Vertex &v2)
    {
        return v1.x == v2.x && v1.y == v2.y;
    }
}
