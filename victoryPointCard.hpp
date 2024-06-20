/*alonz1414@gmail.com*/
#ifndef VICTORYPOINTCARD_HPP
#define VICTORYPOINTCARD_HPP

#include "developmentCard.hpp"
#include "player.hpp"

namespace ariel
{

    class VictoryPointCard : public DevelopmentCard
    {
    public:
        VictoryPointCard();
        bool playCard(Player &p,Catan &catan);
        static int getTotalVictoryPointCards(); // Static method to get total victory point cards in the game

    private:
        static int totalVictoryPointCards;
    };

} 

#endif 
