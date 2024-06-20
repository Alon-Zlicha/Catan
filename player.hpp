/*alonz1414@gmail.com*/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>
#include "board.hpp" 
#include "piece.hpp"
#include "settlement.hpp"
#include "road.hpp"
#include "developmentCard.hpp"
#define SIZE 5
#define BRICK 0
#define ORE 1
#define GRAIN 2
#define WOOL 3
#define LUMBER 4

namespace ariel
{
    class Catan;
    class Board;
    class DevelopmentCard; 

    class Player
    {
    private:
        std::string _name;
        int _points;
        std::vector<Piece *> _pieces;
        int resources[SIZE];
        std::vector<DevelopmentCard *> cards;
        void addPieceToPlayer(Piece *piece);
        void countDevelopmentCards(int &knight, int &victoryPoint, int &yearOfPlenty, int &monopoly, int &roadsBuilding);
        void moveDevelopmentCardTo(Player &p,DevelopmentCard *card);
        int getTotalReources();
        void returnHalf();

    public:
        Player();
        Player(std::string name);
        ~Player();
        std::string getName() const;
        bool placeSettlementStart(size_t x, size_t y, Board &b);
        bool placeSettlement(size_t x, size_t y, Board &b);
        bool placeRoadStart(size_t x1, size_t y1, size_t x2, size_t y2, Board &b);
        bool placeRoad(size_t x1, size_t y1, size_t x2, size_t y2, Board &b);
        void placeRoadTwice(Catan &catan);
        bool upgradeToCity(size_t x, size_t y, Board &b);
        void rollDice(Catan &catan);
        void addResource(std::string landType);
        bool buyDevelopmentCard(Catan &catan);
        bool playPromotionCard(int choice, Catan &catan);
        bool hasThreeKnights() const;
        int getPoints();
        void updatePoints(int num);
        void printPoints() const;
        void printPieces() const;
        void printResources();
        void printDevelopmentCards();
        void addResourceFromOthers(int choice, Catan &catan); 
        void addResourcesFromTheBank(int choice1, int choice2); 
        bool trade(Player *p);
        int* getResources(); //for test.cpp
        std::vector<DevelopmentCard *> &getDevCards(); //for test.cpp
    };
}

#endif
