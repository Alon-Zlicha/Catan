/*alonz1414@gmail.com*/
#include "knightCard.hpp"

namespace ariel
{

    int KnightCard::totalKnights = 0;
    KnightCard::KnightCard() : DevelopmentCard("Knight")
    {
        totalKnights++;
    }

    bool KnightCard::playCard(Player &p,Catan &catan)
    {
        if (p.hasThreeKnights())
        {
            p.updatePoints(2);
            //the player hold largest army card
            //if he want to trade on largest army card he trades for 3 knights
        }
        return true;
        
    }
    int KnightCard::getTotalKnights()
    {
        return totalKnights;
    }

} 
