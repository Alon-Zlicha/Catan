#include "settlement.hpp"

namespace ariel
{
    Settlement::Settlement(Player *p, size_t x, size_t y) : Piece(p, x, y), isCity(false) {}
    std::string Settlement::getType() const
    {
        return isCity ? "City" : "Settlement";
    }

    bool Settlement::upgradeToCity()
    {
        if (!isCity)
        {
            isCity = true;
            return true;
        }
        return false;
    }

    std::string Settlement::toString() const
    {
        return "(" + std::to_string(vertex->getX()) + "," + std::to_string(vertex->getY()) + ")";
    }
}