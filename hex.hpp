#ifndef HEX_HPP
#define HEX_HPP
#include <string>
#include <vector>
namespace ariel
{
    class Hex
    {
    private:
        int id;
        size_t number;
        std::string landType;

    public:
        Hex();
        int getNumber() const;
        std::string getLandType() const;
        int getID() const;
        void setID(int id);
        // 2 methods for test.cpp only
        void setNumber(int num);
        void setLandType(std::string type); 
    private:
        int generateHexNumber();
        std::string generateHexType();
    };
}
#endif 
