#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "developmentCard.hpp"
#include "player.hpp"

namespace ariel
{

    class KnightCard : public DevelopmentCard
    {
    public:
        KnightCard();
        ~KnightCard();
        bool playCard(Player &p,Catan &catan);
        static int getTotalKnights();       // Static method to get total knights in the game
    private:
        static int totalKnights;
    };

} 

#endif 
