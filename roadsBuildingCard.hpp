#ifndef ROADSBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include "developmentCard.hpp"
#include "player.hpp"

namespace ariel {

    class RoadsBuildingCard : public DevelopmentCard {
    public:
        RoadsBuildingCard();
        ~RoadsBuildingCard();
        bool playCard(Player& p,Catan &catan);
    };

} 

#endif 
