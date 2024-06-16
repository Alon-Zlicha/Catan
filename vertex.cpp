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

    bool Vertex::isNearRoad(const Player &p)
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

    bool Vertex::isFarFromSettlement(const Player &p)
    {
        for (size_t i = 0; i < adjacentVertices.size(); i++)
        {
            if (adjacentVertices[i]->getPiece() != nullptr && adjacentVertices[i]->getPiece()->getPlayer()->getName() == p.getName())
            {
                return false;
            }
            for (size_t j = 0; j < adjacentVertices[i]->adjacentVertices.size(); j++)
            {
                if (adjacentVertices[i]->adjacentVertices[j]->getPiece() != nullptr && adjacentVertices[i]->adjacentVertices[j]->getPiece()->getPlayer()->getName() == p.getName())
                {
                    return false;
                }
            }
        }
        return true;
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

    void Vertex::printAdjHexes()
    {
        for (size_t i = 0; i < adjacentHexes.size(); i++)
        {
            std::cout << "**" << adjacentHexes[i]->getID() << "**" << std::endl;
        }
    }
    void Vertex::printAdjVertices()
    {
        for (size_t i = 0; i < adjacentVertices.size(); i++)
        {
            std::cout << "**" << adjacentVertices[i]->getX() << "**" << adjacentVertices[i]->getY() << std::endl;
        }
    }

    void Vertex::printAdjEdges()
    {
        std::cout << "Number of adjacent edges: " << adjacentEdges.size() << std::endl;
        for (size_t i = 0; i < adjacentEdges.size(); i++)
        {
            Edge *edge = adjacentEdges[i];
            Vertex *v1 = edge->getV1();
            Vertex *v2 = edge->getV2();

            if (v1 != nullptr && v2 != nullptr)
            {
                std::cout << "Edge " << i + 1 << ": (" << v1->getX() << ", " << v1->getY() << ") <-> ("
                          << v2->getX() << ", " << v2->getY() << ")" << std::endl;
            }
            else
            {
                std::cout << "Edge " << i + 1 << ": Invalid vertices" << std::endl;
            }
        }
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
