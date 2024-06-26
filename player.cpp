/*alonz1414@gmail.com*/
#include "player.hpp"
#include "catan.hpp"
#include <algorithm>
using namespace std;
namespace ariel
{
    Player::Player() : _name(""), _points(0)
    {
        for (int i = 0; i < SIZE; i++)
        {
            resources[i] = 0;
        }
    }
    Player::Player(string name) : _name(name), _points(0)
    {
        for (int i = 0; i < SIZE; i++)
        {
            resources[i] = 0;
        }
    }
    // Destructor
    Player::~Player()
    {
        for (Piece *piece : _pieces)
        {
            delete piece;
        }
        _pieces.clear();
        for (DevelopmentCard *card : cards)
        {
            delete card;
        }
        cards.clear();
    }

    std::string Player::getName() const
    {
        return this->_name;
    }

    bool Player::placeSettlementStart(size_t x, size_t y, Board &b)
    {

        Settlement *s = new Settlement(this, x, y);
        if (b.addSettlementToBoard(x, y, s))
        {
            addPieceToPlayer(s);
            this->_points++;
            vector<Hex *> hexes = b.getVertices()[x][y].getAdjacentHexes();
            for (size_t i = 0; i < hexes.size(); i++)
            {
                addResource(hexes[i]->getLandType());
            }
            return true;
        }
        delete s;
        return false;
    }

    bool Player::placeSettlement(size_t x, size_t y, Board &b)
    {
        if (resources[BRICK] >= 1 && resources[LUMBER] >= 1 && resources[GRAIN] >= 1 && resources[WOOL] >= 1)
        {
            Vertex *v = b.getVertexByCoordinates(x, y);
            if (v != nullptr)
            {
                if (v->isFarFromSettlement() && v->isNearRoad())
                {
                    Settlement *s = new Settlement(this, x, y);
                    if (b.addSettlementToBoard(x, y, s))
                    {
                        addPieceToPlayer(s);
                        resources[BRICK]--;
                        resources[LUMBER]--;
                        resources[GRAIN]--;
                        resources[WOOL]--;
                        this->_points++;
                        return true;
                    }
                    else
                    {
                        delete s;
                        return false;
                    }
                }
                else
                {
                    cout << this->_name << "Failed to place settlement! You can place a new settlement only next to a road and at least two vertices away from another settlement or city." << std::endl;
                    return false;
                }
            }
        }
        cout << "Failed to place settlement! You don't have enough resources. You need 1 brick, 1 lumber, 1 grain, and 1 wool." << std::endl;
        return false;
    }

    bool Player::placeRoadStart(size_t x1, size_t y1, size_t x2, size_t y2, Board &b)
    {
        Edge *e = b.getEdgeByCoordinates(x1, y1, x2, y2);
        if (e == nullptr)
        {
            cout << "Invalid coordinates! Cannot place Road" << endl;
            return false;
        }
        Road *r = new Road(this, e);
        if (b.addRoadToBoard(*e, *r))
        {
            addPieceToPlayer(r);
            return true;
        }
        delete r;
        return false;
    }

    bool Player::placeRoad(size_t x1, size_t y1, size_t x2, size_t y2, Board &b)
    {
        Edge *e = b.getEdgeByCoordinates(x1, y1, x2, y2);
        if (e == nullptr)
        {
            cout << "Invalid coordinates! Cannot place Road" << endl;
            return false;
        }
        if (resources[BRICK] >= 1 && resources[LUMBER] >= 1)
        {
            if (e->isNearSettlement(*this) || e->isNearRoad(*this))
            {
                Road *r = new Road(this, e);
                if (b.addRoadToBoard(*e, *r))
                {
                    addPieceToPlayer(r);
                    r->setPlayer(this);
                    resources[BRICK]--;
                    resources[LUMBER]--;
                    return true;
                }
                else
                {
                    delete r;
                    return false;
                }
            }
            else
            {
                cout << "Failed to place road! Roads can only be placed adjacent to your own settlements, cities, or your own existing roads." << endl;
            }
        }
        else
        {
            cout << "Failed to place road! You don't have enough resources. You need 1 brick and 1 lumber." << std::endl;
        }
        return false;
    }
    /*The player recivied resource for free to place 2 road.So he loses those resources even thogh he failed to place the roads*/
    void Player::placeRoadTwice(Catan &catan)
    {
        size_t x, y, x2, y2;
        while (true)
        {
            cout << "Place first road - ";
            cin >> x >> y >> x2 >> y2;
            Board &b = catan.getBoard();
            if (this->placeRoad(x, y, x2, y2, b))
            {
                break;
            }
            cout << "Press 1 to give up, any other number to keep trying - " << endl;
            cin >> x;
            if (x == 1)
            {
                // giving up before placing one road
                resources[BRICK] -= 2;
                resources[LUMBER] -= 2;
                return;
            }
        }
        while (true)
        {
            cout << "Place second road - ";
            cin >> x >> y >> x2 >> y2;
            Board &b = catan.getBoard();
            if (this->placeRoad(x, y, x2, y2, b))
            {
                return;
            }
            cout << "Press 1 to give up, any other number to keep trying - " << endl;
            cin >> x;
            if (x == 1)
            {
                // giving up after placing one road
                resources[BRICK]--;
                resources[LUMBER]--;
                return;
            }
        }
    }

    bool Player::upgradeToCity(size_t x, size_t y, Board &b)
    {
        if (resources[ORE] >= 3 && resources[GRAIN] >= 2)
        {
            bool found = false;
            for (auto piece : _pieces)
            {
                if (piece->getVertex()->getX() == x && piece->getVertex()->getY() == y)
                {
                    found = true;
                    if (piece->upgradeToCity())
                    {
                        this->_points++; // Gain a point for upgrading to a city
                        resources[ORE] -= 3;
                        resources[GRAIN] -= 2;
                        return true;
                    }
                    else
                    {
                        cout << "Failed to upgrade to a city! The piece is already a city." << endl;
                    }
                }
            }
            if (!found)
            {
                std::cout << "Failed to upgrade to city! You don't have a settlement at the given vertex." << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to upgrade to city! You don't have enough resources. You need 3 ore and 2 grain." << std::endl;
        }
        return false;
    }

    void Player::addPieceToPlayer(Piece *piece)
    {
        this->_pieces.push_back(piece);
    }

    void Player::addResource(string landType)
    {
        if (landType == "Agricultural")
        {
            resources[GRAIN]++;
        }
        else if (landType == "Forest")
        {
            resources[LUMBER]++;
        }
        else if (landType == "Hills")
        {
            resources[BRICK]++;
        }
        else if (landType == "Pasture")
        {
            resources[WOOL]++;
        }
        else if (landType == "Mountains")
        {
            resources[ORE]++;
        }
    }

    void Player::printResources()
    {
        cout << this->_name << " resources:  " << endl;
        cout << "Brick - " << resources[BRICK] << endl;
        cout << "Ore - " << resources[ORE] << endl;
        cout << "Grain - " << resources[GRAIN] << endl;
        cout << "Wool - " << resources[WOOL] << endl;
        cout << "Lumber - " << resources[LUMBER] << endl;
    }

    void Player::printDevelopmentCards()
    {
        int knight, victoryPoint, yearOfPlenty, monopoly, roadsBuilding;
        countDevelopmentCards(knight, victoryPoint, yearOfPlenty, monopoly, roadsBuilding);
        cout << this->_name << " development cards: " << endl;
        cout << "Knight - " << knight << endl;
        cout << "Victory point - " << victoryPoint << endl;
        cout << "Year of plenty - " << yearOfPlenty << endl;
        cout << "Monopoly - " << monopoly << endl;
        cout << "Roads building - " << roadsBuilding << endl;
    }

    void Player::rollDice(Catan &catan)
    {
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int total = dice1 + dice2;
        std::cout << "dice 1 - " << dice1 << std::endl;
        std::cout << "dice 2 - " << dice2 << std::endl;
        std::cout << "total - " << total << std::endl;
        if (total != 7)
        {
            Board &b = catan.getBoard();
            b.addResources(total);
        }
        else
        {
            Player *otherPlayer1, *otherPlayer2;
            catan.getOtherPlayers(otherPlayer1, otherPlayer2);
            returnHalf();
            otherPlayer1->returnHalf();
            otherPlayer2->returnHalf();
        }
    }
    void Player::returnHalf()
    {
        int total = getTotalReources();
        if (total > 7)
        {
            int totalToReturn = 0;
            while (true)
            {
                printResources();
                cout << this->getName() << " needs to return " << total / 2 << " resources - " << endl;
                cout << "Enter the amounts of resources to return in the following order: (Brick, Ore, Grain, Wool, Lumber):";
                int returnResources[SIZE];
                totalToReturn = 0;
                bool validInput = true;

                for (int i = 0; i < SIZE; i++)
                {
                    cin >> returnResources[i];
                    if (returnResources[i] > resources[i])
                    {
                        validInput = false;
                        cout << "You don't have enough resources to return. Please try again." << endl;
                        break;
                    }
                    totalToReturn += returnResources[i];
                }

                if (validInput && totalToReturn == total / 2)
                {
                    for (int i = 0; i < SIZE; i++)
                    {
                        resources[i] -= returnResources[i];
                    }
                    printResources();
                    return;
                }
                else if (validInput)
                {
                    cout << "Not enough total resources. Please try again." << endl;
                }
            }
        }
    }

    int *Player::getResources()
    {
        return resources;
    }

    bool Player::buyDevelopmentCard(Catan &catan)
    {
        if (resources[WOOL] >= 1 && resources[ORE] >= 1 && resources[GRAIN] >= 1)
        {
            DevelopmentCard *card = DevelopmentCard::createDevelopmentCard();
            if (card != nullptr)
            {
                cout << card->getCardType() << endl;
                this->cards.push_back(card);
                if (card->getCardType() == "Knight" || card->getCardType() == "Victory point")
                {
                    card->playCard(*this, catan);
                }
                resources[WOOL]--;
                resources[ORE]--;
                resources[GRAIN]--;
                return true;
            }
            return false;
        }
        std::cout << "Failed to buy a development card! You don't have enough resources. You need 1 ore, 1 grain, and 1 wool." << std::endl;
        return false;
    }

    bool Player::playPromotionCard(int choice, Catan &catan)
    {
        std::string cardType;
        if (choice == 1)
        {
            cardType = "Monopoly";
        }
        if (choice == 2)
        {
            cardType = "Year of plenty";
        }
        if (choice == 3)
        {
            cardType = "Roads building";
        }
        for (size_t i = 0; i < cards.size(); i++)
        {
            if (cardType == cards[i]->getCardType())
            {
                bool shouldRemove = false;
                while (!shouldRemove)
                {
                    shouldRemove = cards[i]->playCard(*this, catan);
                }
                delete cards[i];
                cards.erase(cards.begin() + i);
                return true;
            }
        }
        cout << "You don't have this card" << endl;
        return false;
    }
    bool Player::hasThreeKnights() const
    {
        int knightCount = 0;
        for (DevelopmentCard *card : cards)
        {
            if (card->getCardType() == "Knight")
            {
                knightCount++;
            }
        }
        return knightCount == 3;
    }

    int Player::getPoints()
    {
        return this->_points;
    }

    void Player::updatePoints(int num)
    {
        this->_points += num;
    }

    void Player::printPoints() const
    {
        std::cout << this->_name << " has " << this->_points << " points" << std::endl;
    }
    void Player::printPieces() const
    {
        cout << this->_name << "'s pieces:  " << endl;
        for (size_t i = 0; i < _pieces.size(); i++)
        {
            cout << _pieces[i]->getType() << " - " << _pieces[i]->toString() << endl;
        }
    }
    void Player::addResourceFromOthers(int choice, Catan &catan)
    {
        Player *otherPlayer1, *otherPlayer2;
        catan.getOtherPlayers(otherPlayer1, otherPlayer2);
        if (otherPlayer1->resources[choice] > 0)
        {
            otherPlayer1->resources[choice]--;
            this->resources[choice]++;
        }
        if (otherPlayer2->resources[choice] > 0)
        {
            otherPlayer2->resources[choice]--;
            this->resources[choice]++;
        }
    }

    void Player::addResourcesFromTheBank(int choice1, int choice2)
    {
        resources[choice1]++;
        resources[choice2]++;
    }

    bool Player::trade(Player *otherPlayer)
    {
        int knight, victoryPoint, yearOfPlenty, monopoly, roadsBuilding;
        int knightOther, victoryPointOther, yearOfPlentyOther, monopolyOther, roadsBuildingOther;
        this->countDevelopmentCards(knight, victoryPoint, yearOfPlenty, monopoly, roadsBuilding);
        otherPlayer->countDevelopmentCards(knightOther, victoryPointOther, yearOfPlentyOther, monopolyOther, roadsBuildingOther);
        int cardsArr[SIZE] = {knight, victoryPoint, yearOfPlenty, monopoly, roadsBuilding};
        int cardsOtherArr[SIZE] = {knightOther, victoryPointOther, yearOfPlentyOther, monopolyOther, roadsBuildingOther};
        printPoints();
        printResources();
        printDevelopmentCards();
        otherPlayer->printPoints();
        otherPlayer->printResources();
        otherPlayer->printDevelopmentCards();
        cout << "Starting trade with " << otherPlayer->getName() << endl;
        cout << "Enter the amounts of resources to receive in the following order: (Brick, Ore, Grain, Wool, Lumber):";
        int receiveResources[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            cin >> receiveResources[i];
            if (receiveResources[i] > otherPlayer->resources[i])
            {
                cout << otherPlayer->getName() << " doesn't have enough resources to give. Trade aborted." << endl;
                return false;
            }
        }
        cout << "Enter the amounts of development cards to receive in the following order: (Knight, Victory point, Year of Plenty, Monopoly, Roads Building): ";
        int receiveCards[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            cin >> receiveCards[i];
            if (receiveCards[i] > cardsOtherArr[i])
            {
                cout << otherPlayer->getName() << " doesn't have enough development cards to give. Trade aborted." << endl;
                return false;
            }
        }
        cout << "Enter the amounts of resources to give in the following order: (Brick, Ore, Grain, Wool, Lumber): ";
        int giveResources[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            cin >> giveResources[i];
            if (giveResources[i] > resources[i])
            {
                cout << "You don't have enough resources to give. Trade aborted." << endl;
                return false;
            }
        }
        cout << "Enter the amounts of development cards to give in the following order: (Knight, Victory point, Year of Plenty, Monopoly, Roads Building): ";
        int giveCards[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            cin >> giveCards[i];
            if (giveCards[i] > cardsArr[i])
            {
                cout << "You don't have enough development cards to give. Trade aborted." << endl;
                return false;
            }
        }
        int confirmation;
        cout << "Press 1 to confirm the trade, any other number to cancel: ";
        cin >> confirmation;
        if (confirmation != 1)
        {
            cout << "Trade cancelled." << endl;
            return false;
        }
        // Execute the trade
        for (int i = 0; i < SIZE; i++)
        {
            resources[i] -= giveResources[i];
            otherPlayer->resources[i] += giveResources[i];
            resources[i] += receiveResources[i];
            otherPlayer->resources[i] -= receiveResources[i];
        }
        const string developmentCardTypes[SIZE] = {"Knight", "Victory point", "Year of plenty", "Monopoly", "Roads building"};
        for (int i = 0; i < SIZE; ++i)
        {
            while (receiveCards[i] > 0)
            {
                bool cardFound = false;

                // Loop through otherPlayer's cards
                for (size_t k = 0; k < otherPlayer->cards.size(); ++k)
                {
                    DevelopmentCard *cardToMove = otherPlayer->cards[k];

                    if (cardToMove && cardToMove->getCardType() == developmentCardTypes[i])
                    {
                        cardFound = true;

                        if (developmentCardTypes[i] == "Knight")
                        {
                            if (otherPlayer->hasThreeKnights())
                            {
                                otherPlayer->updatePoints(-2);
                            }
                            otherPlayer->moveDevelopmentCardTo(*this, cardToMove);
                            if (this->hasThreeKnights())
                            {
                                this->updatePoints(2);
                            }
                        }
                        else if (developmentCardTypes[i] == "Victory point")
                        {
                            otherPlayer->moveDevelopmentCardTo(*this, cardToMove);
                            otherPlayer->updatePoints(-1);
                            this->updatePoints(1);
                        }
                        else
                        {
                            otherPlayer->moveDevelopmentCardTo(*this, cardToMove);
                        }

                        receiveCards[i]--;
                        break;
                    }
                }

                if (!cardFound)
                {
                    cout << otherPlayer->getName() << " doesn't have enough " << developmentCardTypes[i] << " cards to give. Trade aborted." << endl;
                    return false;
                }
            }
        }

        // Loop through giveCards and move corresponding cards from this player to otherPlayer
        for (int i = 0; i < SIZE; ++i)
        {
            while (giveCards[i] > 0)
            {
                bool cardFound = false;

                // Loop through this player's cards
                for (size_t k = 0; k < this->cards.size(); ++k)
                {
                    DevelopmentCard *cardToMove = this->cards[k];

                    if (cardToMove && cardToMove->getCardType() == developmentCardTypes[i])
                    {
                        cardFound = true;

                        if (developmentCardTypes[i] == "Knight")
                        {
                            if (this->hasThreeKnights())
                            {
                                this->updatePoints(-2);
                            }
                            this->moveDevelopmentCardTo(*otherPlayer, cardToMove);
                            if (otherPlayer->hasThreeKnights())
                            {
                                otherPlayer->updatePoints(2);
                            }
                        }
                        else if (developmentCardTypes[i] == "Victory point")
                        {
                            this->moveDevelopmentCardTo(*otherPlayer, cardToMove);
                            this->updatePoints(-1);
                            otherPlayer->updatePoints(1);
                        }
                        else
                        {
                            this->moveDevelopmentCardTo(*otherPlayer, cardToMove);
                        }

                        giveCards[i]--;
                        break;
                    }
                }

                if (!cardFound)
                {
                    cout << "You don't have enough " << developmentCardTypes[i] << " cards to give. Trade aborted." << endl;
                    return false;
                }
            }
        }
        cout << "Trade successful!" << endl;
        printPoints();
        printResources();
        printDevelopmentCards();
        otherPlayer->printPoints();
        otherPlayer->printResources();
        otherPlayer->printDevelopmentCards();
        return true;
    }
    void Player::moveDevelopmentCardTo(Player &p, DevelopmentCard *card)
    {
        if (card == nullptr)
        {
            std::cout << "Error: Trying to move a null card." << std::endl;
            return;
        }
        // Find the card in the current player's collection
        auto it = std::find(cards.begin(), cards.end(), card);
        if (it != cards.end())
        {
            // Remove the card from the current player's collection
            cards.erase(it);
            // Add the card to the target player's collection
            p.cards.push_back(card);
        }
    }
    void Player::countDevelopmentCards(int &knight, int &victoryPoint, int &yearOfPlenty, int &monopoly, int &roadsBuilding)
    {
        knight = 0, victoryPoint = 0;
        yearOfPlenty = 0, monopoly = 0, roadsBuilding = 0;
        for (size_t i = 0; i < cards.size(); i++)
        {
            if (cards[i]->getCardType() == "Knight")
            {
                knight++;
            }
            else if (cards[i]->getCardType() == "Victory point")
            {
                victoryPoint++;
            }
            else if (cards[i]->getCardType() == "Year of plenty")
            {
                yearOfPlenty++;
            }
            else if (cards[i]->getCardType() == "Monopoly")
            {
                monopoly++;
            }
            else if (cards[i]->getCardType() == "Roads building")
            {
                roadsBuilding++;
            }
        }
    }
    int Player::getTotalReources()
    {
        return resources[BRICK] + resources[ORE] + resources[WOOL] + resources[GRAIN] + resources[LUMBER];
    }
    std::vector<DevelopmentCard *> &Player::getDevCards()
    {
        return this->cards;
    }
}
