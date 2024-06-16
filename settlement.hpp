#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include "piece.hpp"
#include "vertex.hpp"
namespace ariel
{
    
    class Settlement : public Piece
    {
    private:
        bool isCity; // Flag to indicate if this settlement has been upgraded to a city

    public:
        Settlement(Player *p, size_t x, size_t y);
        std::string getType() const override;
        bool upgradeToCity() override;
        std::string toString() const override;
    };
}
#endif 
