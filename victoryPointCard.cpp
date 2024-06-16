#include "victoryPointCard.hpp"

namespace ariel
{

    int VictoryPointCard::totalVictoryPointCards = 0;
    VictoryPointCard::VictoryPointCard() : DevelopmentCard("Victory point")
    {
        totalVictoryPointCards++;
    }

    VictoryPointCard::~VictoryPointCard() {}

    bool VictoryPointCard::playCard(Player &p,Catan &catan)
    {
        p.updatePoints(1);
        return true;
    }
    int VictoryPointCard::getTotalVictoryPointCards()
    {
        return totalVictoryPointCards;
    }

} 
