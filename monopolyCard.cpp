/*alonz1414@gmail.com*/
#include "monopolyCard.hpp"

namespace ariel
{

    MonopolyCard::MonopolyCard() : DevelopmentCard("Monopoly") {}


    bool MonopolyCard::playCard(Player &p,Catan &catan)
    {
        std::cout << "Choose a resource: press 1 for brick, 2 for ore, 3 for grain, 4 for wool, or 5 for lumber - " << std::endl;
        int choice;
        std::cin >> choice; 
        if(choice>5 || choice<1){
            std::cout<<"Invalid choice!"<<std::endl;
            return false;
        }
        p.addResourceFromOthers(choice-1,catan);
        return true;
    }

} 
