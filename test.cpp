#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include <sstream>
#include <iostream>
using namespace std;
using namespace ariel;
#define BRICK 0
#define ORE 1
#define GRAIN 2
#define WOOL 3
#define LUMBER 4
TEST_CASE("Board init")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    Board &b = catan.getBoard();
    Vertex *v = b.getVertexByCoordinates(0, 0);
    vector<vector<Hex>> &hexes = b.getHexes();
    Edge *e = b.getEdgeByCoordinates(0, 0, 0, 0); // no such edge
    e = b.getEdgeByCoordinates(0, 0, 1, 1);
    CHECK(e != nullptr);
    Hex h = hexes[0][0];
    bool flag = v->isAdjacentHex(h);
    CHECK(flag == true);
    v = b.getVertexByCoordinates(3, 0);
    flag = v->isAdjacentHex(h);
    CHECK(flag == false);
    v = b.getVertexByCoordinates(3, 1);
    flag = v->isAdjacentHex(h);
    CHECK(flag == true);
    e = b.getEdgeByCoordinates(0, 0, 1, 1);
    flag = e->isAdjacentHex(h);
    CHECK(flag == true);
    e = b.getEdgeByCoordinates(0, 0, 4, 3); // no such edge
    CHECK(e == nullptr);
    v = b.getVertexByCoordinates(1, 5); // no such vertex
    CHECK(v == nullptr);
    v = b.getVertexByCoordinates(4, 3);
    h = hexes[2][2];
    flag = v->isAdjacentHex(h);
    CHECK(flag == false);
    v = b.getVertexByCoordinates(6, 2);
    flag = v->isAdjacentHex(h);
    CHECK(flag == true);
    e = b.getEdgeByCoordinates(7, 2, 6, 3);
    flag = e->isAdjacentHex(h);
    CHECK(flag == true);
    flag = v->isNearRoad(); // has to be false because the board is empty
    CHECK(flag == false);
    v = b.getVertexByCoordinates(6, 3);
    h = hexes[3][2];
    flag = v->isAdjacentHex(h);
}
TEST_CASE("progress of the game")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    Board &b = catan.getBoard();
    // init board for testing
    vector<vector<int>> numbers = {
        {4, 5, 3},
        {10, 9, 11, 2},
        {6, 8, 3, 10, 9},
        {5, 12, 6, 11},
        {4, 9, 12}};
    vector<vector<string>> types = {
        {"Hills", "Pasture", "Agricultural"},
        {"Desert", "Mountains", "Hills", "Pasture"},
        {"Pasture", "Mountains", "Forest", "Agricultural", "Desert"},
        {"Pasture", "Forest", "Hills", "Desert", "Mountains"},
        {"Pasture", "Agricultural", "Forest"}};
    vector<vector<Hex>> &hexes = b.getHexes();
    for (size_t i = 0; i < hexes.size(); i++)
    {
        for (size_t j = 0; j < hexes[i].size(); j++)
        {
            hexes[i][j].setNumber(numbers[i][j]);
            hexes[i][j].setLandType(types[i][j]);
        }
    }
    SUBCASE("First turn placing settlemnets and roads")
    {
        b.printHexas();
        bool flag = p1.placeSettlementStart(0, 0, b); // p1 gets brick
        CHECK(flag == true);
        Vertex *v = b.getVertexByCoordinates(1, 0); // is close to (0,0)
        flag = v->isFarFromSettlement();
        CHECK(flag == false);
        flag = p1.placeSettlementStart(0, 0, b);
        CHECK(flag == false);
        flag = p1.placeSettlementStart(6, 3, b); // p1 now has 2 brick, 1 lumber, 1 grain
        CHECK(flag == true);
        int *resources = p1.getResources();
        CHECK(resources[BRICK] == 2);
        CHECK(resources[LUMBER] == 1);
        CHECK(resources[GRAIN] == 1);
        CHECK(resources[WOOL] == 0);
        CHECK(resources[ORE] == 0);
        flag = p1.placeRoadStart(0, 0, 0, 1, b); // no such edge
        CHECK(flag == false);
        flag = p1.placeRoadStart(8, 2, 9, 2, b);
        CHECK(flag == true);
        flag = p1.placeRoadStart(9, 2, 8, 2, b); // same edge as before
        CHECK(flag == false);
        flag = p1.placeRoadStart(0, 0, 1, 1, b);
        CHECK(flag == true);
        p2.placeSettlementStart(4, 2, b);
        p2.placeSettlementStart(7, 1, b);
        resources = p2.getResources();
        CHECK(resources[BRICK] == 1);
        CHECK(resources[LUMBER] == 2);
        CHECK(resources[GRAIN] == 0);
        CHECK(resources[WOOL] == 1);
        CHECK(resources[ORE] == 2);
        SUBCASE("Placing settlments/cities and roads")
        {
            resources = p1.getResources();
            flag = p1.placeRoad(11, 1, 10, 1, b); // not near other road or settlement
            CHECK(flag == false);
            flag = p1.placeRoad(9, 2, 10, 2, b); // is near other road
            CHECK(flag == true);
            CHECK(resources[BRICK] == 1); // check if the player paid for the road
            CHECK(resources[LUMBER] == 0);
            flag = p1.upgradeToCity(0, 0, b); // not enough resources
            CHECK(flag == false);
            resources[ORE] += 3;
            resources[GRAIN] += 2;
            flag = p1.upgradeToCity(4, 2, b); // not p1 settlement
            CHECK(flag == false);
            flag = p1.upgradeToCity(0, 0, b);
            CHECK(flag == true);
            CHECK(resources[GRAIN] == 1); // check if the player paid for the city
            CHECK(resources[ORE] == 0);
            flag = p1.placeSettlement(9, 2, b); // not enough resources
            CHECK(flag == false);
            flag = p1.placeSettlement(9, 2, b); // not near road
            CHECK(flag == false);
            resources = p1.getResources();
            resources[WOOL]++;
            resources[LUMBER]++;
            resources[BRICK]++;
            resources[GRAIN]++;
            Vertex *v = b.getVertexByCoordinates(7, 2);
            flag = v->isFarFromSettlement();
            CHECK(flag == false);
            flag = p1.placeSettlement(7, 2, b); // not 2 edges away from city/settlement
            CHECK(flag == false);
            v = b.getVertexByCoordinates(8, 2);
            flag = v->isNearRoad();
            CHECK(flag == true);
            flag = p1.placeSettlement(8, 2, b); // is near road and 2 edges away from other settlement
            CHECK(flag == true);
            CHECK(resources[BRICK] == 1); // check if the player paid for the city
            CHECK(resources[LUMBER] == 0);
            CHECK(resources[GRAIN] == 1);
            CHECK(resources[WOOL] == 0);
            CHECK(resources[ORE] == 0);
            SUBCASE("roll dices")
            {
                b.addResources(4);            // suppose 4 is the result of the dice roll
                CHECK(resources[BRICK] == 3); // Amit has city near hexagon with number 4 and land type Hills so he gets 2 brick
                b.addResources(6);
                CHECK(resources[BRICK] == 5); // Amit as 2 settlments near the same hexagon with number 6 and land Hills so he gets 2 brick
                resources = p2.getResources();
                b.addResources(10);           // Yossi has settlement near hexagon with number 10, but with land type Desert so he doesnt get any resource
                CHECK(resources[BRICK] == 1); // Each respurce remains with the same amount as before
                CHECK(resources[LUMBER] == 2);
                CHECK(resources[GRAIN] == 0);
                CHECK(resources[WOOL] == 1);
                CHECK(resources[ORE] == 2);
                b.addResources(3);
                CHECK(resources[LUMBER] == 3); // Yossi has settlement near hexagon with number 3 and land type Forest so he gets Lumber
            }
            SUBCASE("development cards")
            {
                resources = p1.getResources(); // Development card coast 1 Wool, 1 Ore and 1 Grain
                resources[WOOL] += 500;
                resources[ORE] += 500;
                resources[GRAIN] += 500;
                CHECK(resources[WOOL] == 500);
                CHECK(resources[ORE] == 500);
                CHECK(resources[GRAIN] == 501);
                int monopoly, yearOfPlenty, roadsBuilding, knight, victoryPoint;
                int count = 0;
                while (count < 500) // buy 500 development card
                {
                    if (p1.buyDevelopmentCard(catan))
                    {
                        count++;
                    }
                }
                resources = p3.getResources();
                resources[WOOL]++;
                streambuf *orig_cin = std::cin.rdbuf();
                istringstream input("4\n"); // Amit chooses to get Wool
                cin.rdbuf(input.rdbuf());
                p1.playPromotionCard(1, catan); // Amit player chooses to use monopoly card
                cin.rdbuf(orig_cin);
                resources = p1.getResources();
                CHECK(resources[WOOL] == 2);    // Amit gets 1 wool from Yossi and 1 from Dana
                istringstream input1("1\n2\n"); // Amit player chooses to get Brick and Ore from the bank
                streambuf *orig_cin1 = cin.rdbuf();
                cin.rdbuf(input1.rdbuf());
                p1.playPromotionCard(2, catan); // the player chooses to use year of plenty card
                cin.rdbuf(orig_cin);
                CHECK(resources[BRICK] == 2);
                CHECK(resources[ORE] == 1);
                SUBCASE("trade")
                {
                    // The players don't confrim the trade
                    istringstream input("1\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n1\n0\n");
                    streambuf *orig_cin = cin.rdbuf();
                    cin.rdbuf(input.rdbuf());
                    CHECK(!p1.trade(&p2));
                    // Amit gets 1 brick and gives 1 road builing card
                    istringstream input1("1\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n1\n1\n");
                    streambuf *orig_cin1 = cin.rdbuf();
                    cin.rdbuf(input1.rdbuf());
                    size_t size = p1.getDevCards().size();
                    int brick = resources[BRICK];
                    CHECK(p1.trade(&p2));
                    CHECK(p1.getDevCards().size() == size - 1); // Amit gave 1 development card
                    CHECK(resources[BRICK] == brick + 1);
                    cin.rdbuf(orig_cin);
                    // Trade fails.Yossi doesn't have 5 brick
                    istringstream input2("5\n");
                    streambuf *orig_cin2 = cin.rdbuf();
                    cin.rdbuf(input2.rdbuf());
                    CHECK(!p1.trade(&p2));
                    cin.rdbuf(orig_cin2);
                    // Amit had 3 knights and in the trade he gives 1 to Yossi, so he loses 2 points of largest army card
                    int p1_points = p1.getPoints();
                    istringstream input3("0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n1\n0\n0\n0\n0\n1\n");
                    streambuf *orig_cin3 = cin.rdbuf();
                    cin.rdbuf(input3.rdbuf());
                    CHECK(p1.trade(&p2));
                    CHECK(p1.getPoints() == p1_points - 2);
                    cin.rdbuf(orig_cin3);
                    // Yossi gets from Amir more 2 knights so he gets the largest army card and 2 points
                    int p2_points = p2.getPoints();
                    istringstream input4("0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n2\n0\n0\n0\n0\n1\n");
                    streambuf *orig_cin4 = cin.rdbuf();
                    cin.rdbuf(input4.rdbuf());
                    CHECK(p1.trade(&p2));
                    CHECK(p2.getPoints() == p2_points + 2);
                    cin.rdbuf(orig_cin4);
                    // Amit gave to Yossi 1 victory point card so he lost 1 point and Yossi earn 1 point
                    p2_points = p2.getPoints();
                    p1_points = p1.getPoints();
                    istringstream input5("0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n1\n0\n0\n0\n1\n");
                    streambuf *orig_cin5 = cin.rdbuf();
                    cin.rdbuf(input5.rdbuf());
                    CHECK(p1.trade(&p2));
                    CHECK(p2.getPoints() == p2_points + 1); // Yossi now with 5 points
                    CHECK(p1.getPoints() == p1_points - 1); // Amit with 7 points
                    cin.rdbuf(orig_cin5);
                    SUBCASE("check turn and winner")
                    {
                        catan.ChooseStartingPlayer(); // p1 always starts
                        Player *turn = catan.getTurn();
                        CHECK(turn->getName() == p1.getName());
                        catan.nextTurn(); // p2 is always second
                        turn = catan.getTurn();
                        CHECK(turn->getName() == p2.getName());
                        catan.nextTurn(); // p3 is always last
                        turn = catan.getTurn();
                        CHECK(turn->getName() == p3.getName());
                        catan.nextTurn(); // p1 turn's again
                        turn = catan.getTurn();
                        CHECK(turn->getName() == p1.getName());
                        // Amit gets 3 knights and 1 victory point. Now the number of Amit's points is 7+3=10. Amit is the winner and the game is over
                        istringstream input6("0\n0\n0\n0\n0\n3\n1\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n1\n");
                        streambuf *orig_cin6 = cin.rdbuf();
                        cin.rdbuf(input6.rdbuf());
                        CHECK(p1.trade(&p2));
                        CHECK(catan.checkWinner());
                        CHECK(catan.printWinner() == "The winner is: Amit with 10 points!");
                    }
                }
            }
        }
    }
}
