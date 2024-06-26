/*alonz1414@gmail.com*/
#include "piece.hpp"
#include "player.hpp"

namespace ariel
{
    Piece::Piece(Player *p, size_t x, size_t y) : player(p)
    {
        vertex = new Vertex(x, y);
    }
    

    Player *Piece::getPlayer() const
    {
        return this->player;
    }

    void Piece::setPlayer(Player *p)
    {
        this->player=p;
    }

    Vertex *Piece::getVertex() const
    {
        return this->vertex;
    }
    // destructor
    Piece::~Piece()
    {
        delete vertex;
    }
}
