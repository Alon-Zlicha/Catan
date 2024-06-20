/*alonz1414@gmail.com*/
#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "developmentCard.hpp"
#include "player.hpp"

namespace ariel {

    class YearOfPlentyCard: public DevelopmentCard {
    public:
        YearOfPlentyCard();
        bool playCard(Player& p,Catan &catan);
    };

} 
#endif 
