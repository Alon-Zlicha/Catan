#include "player.hpp"
#include "board.hpp"
#include "piece.hpp"
#include "edge.hpp"
#include "catan.hpp"
#include "hex.hpp"
#include "vertex.hpp"
#include "settlement.hpp"
#include "developmentCard.hpp"
#include <iostream>
using namespace std;
using namespace ariel;

int main()
{
    srand(time(nullptr));
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    Board &b = catan.getBoard();
    size_t x, y, x2, y2;
    Player *turn = catan.getTurn();
    for (int i = 0; i < 3; i++)
    {
        b.printHexas();
        while (true)
        {
            cout << "Place first settlement - ";
            cin >> x >> y;
            if (turn->placeSettlementStart(x, y, b))
            {
                break;
            }
        }
        b.printHexas();
        while (true)
        {
            cout << "Place second settlement - ";
            cin >> x >> y;
            if (turn->placeSettlementStart(x, y, b))
            {
                break;
            }
        }
        b.printHexas();
        while (true)
        {
            cout << "Place first road - ";
            cin >> x >> y >> x2 >> y2;
            if (turn->placeRoadStart(x, y, x2, y2, b))
            {
                break;
            }
        }
        b.printHexas();
        while (true)
        {
            cout << "Place second road - ";
            cin >> x >> y >> x2 >> y2;
            if (turn->placeRoadStart(x, y, x2, y2, b))
            {
                break;
            }
        }
        turn->printPieces();
        turn->printResources();
        turn->printPoints();
        catan.nextTurn();
        turn = catan.getTurn();
    }
    bool rolled = false;
    bool traded = false;
    while (!catan.checkWinner())
    {
        if (catan.checkWinner())
        {
            break;
        }
        int choice;
        if (!rolled)
        {
            cout << "Press 1 to use a promotion card, press any other number to roll the dice - " << endl;
            cin >> choice;
            if (choice == 1)
            {
                while (1)
                {
                    turn->printDevelopmentCards();
                    cout << "Press 1 for \"Monopoly\", 2 for \"Year of Plenty\" or 3 for \"Roads building\".Press any other number to cancel   - " << endl;
                    cin >> choice;
                    if (choice > 0 && choice < 4)
                    {
                        if (turn->playPromotionCard(choice, catan))
                        {
                            turn->printPieces();
                            turn->printResources();
                            turn->printPoints();
                            rolled = false;
                            traded = false;
                            if (catan.checkWinner())
                            {
                                break;
                            }
                            catan.nextTurn();
                            turn = catan.getTurn();
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            turn->rollDice(catan);
            rolled = true;
            turn->printPieces();
            turn->printResources();
            turn->printPoints();
        }
        if (!traded)
        {
            cout << "Press 1 to use a promotion card, press 2 to trade with another player. Press any other number to skip - " << endl;
            cin >> choice;
            if (choice == 1)
            {
                while (1)
                {
                    turn->printDevelopmentCards();
                    cout << "Press 1 for \"Monopoly\", 2 for \"Year of Plenty\" or 3 for \"Roads building\".Press any other number to cancel   - " << endl;
                    cin >> choice;
                    if (choice > 0 && choice < 4)
                    {
                        if (turn->playPromotionCard(choice, catan))
                        {
                            turn->printPieces();
                            turn->printResources();
                            turn->printPoints();
                            rolled = false;
                            traded = false;
                            if (catan.checkWinner())
                            {
                                break;
                            }
                            catan.nextTurn();
                            turn = catan.getTurn();
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (choice == 2)
            {
                while (1)
                {
                    Player *otherPlayer1, *otherPlayer2;
                    catan.getOtherPlayers(otherPlayer1, otherPlayer2);
                    cout << "Choose the player you want to trade with: press 1 to trade with " << otherPlayer1->getName() << " or 2 to trade with " << otherPlayer2->getName() << ".Press any other number to cancle " << endl;
                    cin >> choice;
                    if (choice == 1)
                    {
                        if (turn->trade(otherPlayer1))
                        {
                            traded = true;
                            if (catan.checkWinner())
                            {
                                break;
                            }
                        }
                    }
                    else if (choice == 2)
                    {
                        if (turn->trade(otherPlayer2))
                        {
                            traded = true;
                            if (catan.checkWinner())
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        traded = true;
        cout << "Press 1 to use a promotion card, 2 to place a settlement, 3 to place a road, 4 to upgrade to a city, or 5 to buy a development card. Press any other number to end the turn - " << endl;
        cin >> choice;
        if (choice == 1)
        {
            while (1)
            {
                turn->printDevelopmentCards();
                cout << "Press 1 for \"Monopoly\", 2 for \"Year of Plenty\" or 3 for \"Roads building\".Press any other number to cancel   - " << endl;
                cin >> choice;
                if (choice > 0 && choice < 4)
                {
                    if (turn->playPromotionCard(choice, catan))
                    {
                        turn->printPieces();
                        turn->printResources();
                        turn->printPoints();
                        rolled = false;
                        traded = false;
                        if (catan.checkWinner())
                        {
                            break;
                        }
                        catan.nextTurn();
                        turn = catan.getTurn();
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else if (choice == 2)

        {
            while (true)
            {
                b.printHexas();
                turn->printPieces();
                cout << "Place settlement - ";
                cin >> x >> y;
                if (turn->placeSettlement(x, y, b))
                {
                    turn->printPieces();
                    turn->printResources();
                    turn->printPoints();
                    if (catan.checkWinner())
                    {
                        break;
                    }
                    break;
                }
                cout << "Press 1 if you want to cancel, any other number to keep trying - " << endl;
                cin >> x;
                if (x == 1)
                {
                    break;
                }
            }
        }
        else if (choice == 3)
        {
            while (true)
            {
                b.printHexas();
                turn->printPieces();
                cout << "Place road - ";
                cin >> x >> y >> x2 >> y2;
                if (turn->placeRoad(x, y, x2, y2, b))
                {
                    turn->printPieces();
                    turn->printResources();
                    turn->printPoints();
                    break;
                }
                cout << "Press 1 if you want to cancel, any other number to keep trying - " << endl;
                cin >> x;
                if (x == 1)
                {
                    break;
                }
            }
        }
        else if (choice == 4)
        {
            while (true)
            {
                b.printHexas();
                turn->printPieces();
                cout << "Choose the settlement you want to upgrade - " << endl;
                cin >> x >> y;
                if (turn->upgradeToCity(x, y, b))
                {
                    turn->printPieces();
                    turn->printResources();
                    turn->printPoints();
                    if (catan.checkWinner())
                    {
                        break;
                    }
                    break;
                }
                cout << "Press 1 if you want to cancel, any other number to keep trying - " << endl;
                cin >> x;
                if (x == 1)
                {
                    break;
                }
            }
        }
        else if (choice == 5)
        {
            turn->buyDevelopmentCard(catan);
            if (catan.checkWinner())
            {
                break;
            }
        }
        else
        {
            catan.nextTurn();
            turn = catan.getTurn();
            rolled = false;
            traded = false;
        }
    }
    cout << "Game Over" << endl;
    cout << catan.printWinner() << endl;
    return 0;
}
