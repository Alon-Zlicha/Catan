#include "roadsBuildingCard.hpp"

namespace ariel
{

    RoadsBuildingCard::RoadsBuildingCard() : DevelopmentCard("Roads building") {}

    RoadsBuildingCard::~RoadsBuildingCard() {}
    bool RoadsBuildingCard::playCard(Player &p, Catan &catan)
    {
        /* To build 2 roads, the player needs 2 brick and 2 lumber.
        getting those resources for free and then building 2 roads
        is the same as buliding 2 roads for free */
        p.addResourcesFromTheBank(BRICK, LUMBER);
        p.addResourcesFromTheBank(BRICK, LUMBER);
        p.placeRoadTwice(catan);
        return true;
    }

} 
