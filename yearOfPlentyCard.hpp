#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "developmentCard.hpp"
#include "player.hpp"

namespace ariel {

    class YearOfPlentyCard: public DevelopmentCard {
    public:
        YearOfPlentyCard();
        ~YearOfPlentyCard();
        bool playCard(Player& p,Catan &catan);
    };

} 
#endif 
