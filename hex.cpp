/*alonz1414@gmail.com*/
#include "hex.hpp"
namespace ariel
{
    Hex::Hex() {
        id=0;
        number=generateHexNumber();
        landType=generateHexType();
    }
    int Hex::getNumber() const
    {
        return this->number;
    }
    std::string Hex:: getLandType() const{
        return this->landType;
    }
    int Hex::getID() const
    {
        return this->id;
    }
    void Hex::setID(int id)
    {
        this->id=id;
    }
    void Hex::setNumber(int num)
    {
        this->number=num;
    }
    void Hex::setLandType(std::string type)
    {
        this->landType=type;
    }
    int Hex::generateHexNumber()
    {
        int num;
        do
        {
            num = rand() % 11 + 2;
        } while (num == 7);

        return num;
    }
    std::string Hex::generateHexType()
    {
        std::vector<std::string> lands = {"Forest", "Hills", "Pasture", "Agricultural", "Desert", "Mountains"};
        int landsIndex = rand() % lands.size();

        return lands[landsIndex];
    }
}
