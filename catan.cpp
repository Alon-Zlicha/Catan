#include "catan.hpp"
#include <iostream>

namespace ariel
{
    // Constructor
    Catan::Catan(Player &p1, Player &p2, Player &p3) : p1(p1), p2(p2), p3(p3) ,winner(nullptr)
    {
        turn = &ChooseStartingPlayer();
    }

    // Destructor
    Catan::~Catan()
    {
        
    }

    Player &Catan::ChooseStartingPlayer()
    {
        std::cout << "The starting player is: " << p1.getName() << std::endl;
        return p1;
    }

    Board &Catan::getBoard()
    {
        return board;
    }

    void Catan::printWinner()
    {
        std::cout << "The winner is: " << winner->getName() << " with " << winner->getPoints() << " points!" << std::endl;
    }

    Player *Catan::getTurn()
    {
        return this->turn;
    }

    void Catan::getOtherPlayers(Player *&other1, Player *&other2)
    {
        if (turn->getName() == p1.getName())
        {
            other1 = &p2;
            other2 = &p3;
        }
        else if (turn->getName() == p2.getName())
        {
            other1 = &p1;
            other2 = &p3;
        }
        else if (turn->getName() == p3.getName())
        {
            other1 = &p1;
            other2 = &p2;
        }
    }

    bool Catan::checkWinner()
    {
        if(turn->getPoints()>=10){
            winner=turn;
            return true;
        }
        return false;
    }

    void Catan::nextTurn()
    {
        if (turn == &p1)
        {
            turn = &p2;
        }
        else if (turn == &p2)
        {
            turn = &p3;
        }
        else
        {
            turn = &p1;
        }
        std::cout << "It's " << turn->getName() << "'s turn." << std::endl;
    }
}
