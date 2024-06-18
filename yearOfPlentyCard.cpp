#include "yearOfPlentyCard.hpp"

namespace ariel
{

    YearOfPlentyCard::YearOfPlentyCard() : DevelopmentCard("Year of plenty") {}

    YearOfPlentyCard::~YearOfPlentyCard() {}

    bool YearOfPlentyCard::playCard(Player &p,Catan &catan)
    {
        std::cout << "Choose the first resource: press 1 for brick, 2 for ore, 3 for grain, 4 for wool, or 5 for lumber - " << std::endl;
        int choice1;
        std::cin >> choice1;
        std::cout << "Choose the second resource: press 1 for brick, 2 for ore, 3 for grain, 4 for wool, or 5 for lumber - " << std::endl;
        int choice2;
        std::cin >> choice2;
        if(choice1>5 || choice2>5 || choice1<1 || choice2<1){
            std::cout<< "Invalid choices!"<<std::endl;
            return false;
        }
        p.addResourcesFromTheBank(choice1-1,choice2-1);
        return true;
    }

} 
