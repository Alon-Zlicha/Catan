#include "developmentCard.hpp"
#include "monopolyCard.hpp"
#include "roadsBuildingCard.hpp"
#include "yearOfPlentyCard.hpp"
#include "knightCard.hpp"
#include "victoryPointCard.hpp"
#include <cstdlib>
#include <ctime>

namespace ariel
{

    DevelopmentCard::DevelopmentCard(const std::string &type) : cardType(type) {}

    DevelopmentCard::~DevelopmentCard() {}

    std::string DevelopmentCard::getCardType() const
    {
        return cardType;
    }

    DevelopmentCard *DevelopmentCard::createDevelopmentCard() // factory design pattern when player buy a development card
    {
        int random;
        do
        {
            random = std::rand() % 5;
            switch (random)
            {
            case 0:
                return new MonopolyCard();
            case 1:
                return new RoadsBuildingCard();
            case 2:
                return new YearOfPlentyCard();
            case 3:
                if (KnightCard::getTotalKnights() < 3)
                {
                    return new KnightCard();
                }
                break;
            case 4:
                if (VictoryPointCard::getTotalVictoryPointCards() < 4)
                {
                    return new VictoryPointCard();
                }
            default:
                return nullptr;
            }
        } while (random == 3 || random == 4); // Retry if knight card was selected and there are already 3 or victory point card was selected and there are already 4 
        return nullptr;
    }
}
