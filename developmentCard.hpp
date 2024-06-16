#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>
#include "player.hpp"

namespace ariel
{
    class Catan;
    class DevelopmentCard
    {
    protected:
        std::string cardType;

    public:
        DevelopmentCard(const std::string &type);
        virtual ~DevelopmentCard();
        std::string getCardType() const;
        static DevelopmentCard *createDevelopmentCard();
        virtual bool playCard(Player &p,Catan &catan) = 0;
        friend bool operator==(const DevelopmentCard &card1,const DevelopmentCard &card2);
        friend bool operator!=(const DevelopmentCard &card1,const DevelopmentCard &card2);
    };

} 

#endif 
