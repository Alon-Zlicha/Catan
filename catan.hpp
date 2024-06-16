#ifndef CATAN_HPP
#define CATAN_HPP

#include "board.hpp"
#include "player.hpp"

namespace ariel
{
    class Catan
    {
    private:
        Board board;
        Player &p1;
        Player &p2;
        Player &p3;
        Player *turn;
        Player *winner;

    public:
        Catan(Player &p1, Player &p2, Player &p3);
        ~Catan();
        Player &ChooseStartingPlayer();
        Board &getBoard();
        void printWinner();
        void nextTurn();
        Player *getTurn();
        void getOtherPlayers(Player *&other1, Player *&other2);
        bool checkWinner();
    };
}

#endif 
