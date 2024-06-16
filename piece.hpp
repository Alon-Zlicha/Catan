#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

namespace ariel
{
    class Vertex;
    class Player;
    class Piece
    {
    protected:
        Player *player;
        Vertex *vertex;

    public:
        Piece(Player *p, size_t x, size_t y);
        virtual ~Piece(); 
        Player *getPlayer() const;
        Vertex *getVertex() const;
        virtual std::string getType() const = 0;
        virtual bool upgradeToCity() =0;
        virtual std::string toString() const=0;
    };
}

#endif 
