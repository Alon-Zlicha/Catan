/*alonz1414@gmail.com*/
#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include "developmentCard.hpp"
#include "player.hpp"

namespace ariel {

    class MonopolyCard : public DevelopmentCard {
    public:
        MonopolyCard();
        bool playCard(Player& p,Catan &catan);
    };

} 

#endif 
