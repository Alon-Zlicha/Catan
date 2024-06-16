#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
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
    flag = v->isNearRoad(p1); // has to be false because the board is empty
    CHECK(flag == false);
    v = b.getVertexByCoordinates(6, 3);
    h = hexes[3][2];
    v->printAdjHexes();
    flag = v->isAdjacentHex(h);
}
TEST_CASE("Progress of the game")
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
        flag = p1.placeSettlementStart(0, 0, b);
        CHECK(flag == false);
        flag = p1.placeSettlementStart(6, 3, b); // p1 now has 2 brick, 1 lumber, 1 grain
        CHECK(flag == true);
        int *resorces = p1.getResources();
        CHECK(resorces[BRICK] == 2);
        CHECK(resorces[LUMBER] == 1);
        CHECK(resorces[GRAIN] == 1);
        CHECK(resorces[WOOL] == 0);
        CHECK(resorces[ORE] == 0);
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
        resorces = p2.getResources();
        CHECK(resorces[BRICK] == 1);
        CHECK(resorces[LUMBER] == 2);
        CHECK(resorces[GRAIN] == 0);
        CHECK(resorces[WOOL] == 1);
        CHECK(resorces[ORE] == 2);
        SUBCASE("Placing settlments/cities and roads")
        {
            resorces = p1.getResources();
            flag = p1.placeRoad(11, 1, 10, 1, b); // not near other road or settlement
            CHECK(flag == false);
            flag = p1.placeRoad(9, 2, 10, 2, b); // is near other road
            CHECK(flag == true);
            CHECK(resorces[BRICK] == 1); // check if the player paid for the road
            CHECK(resorces[LUMBER] == 0);
            flag = p1.upgradeToCity(0, 0, b); // not enough resources
            CHECK(flag == false);
            resorces[ORE] += 3;
            resorces[GRAIN] += 2;
            flag = p1.upgradeToCity(4, 2, b); // not p1 settlement
            CHECK(flag == false);
            flag = p1.upgradeToCity(0, 0, b);
            CHECK(flag == true);
            CHECK(resorces[GRAIN] == 1); // check if the player paid for the city
            CHECK(resorces[ORE] == 0);
            flag = p1.placeSettlement(9, 2, b); // not enough resources
            CHECK(flag == false);
            flag = p1.placeSettlement(9, 2, b); // not near road
            CHECK(flag == false);
            resorces = p1.getResources();
            resorces[WOOL]++;
            resorces[LUMBER]++;
            resorces[BRICK]++;
            resorces[GRAIN]++;
            Vertex *v=b.getVertexByCoordinates(7,2);
            flag=v->isFarFromSettlement(p1);
            CHECK(flag==false);
            flag = p1.placeSettlement(7, 2, b); // not far enough from city/settlement
            CHECK(flag == false);
            v=b.getVertexByCoordinates(9,2);
            flag=v->isNearRoad(p1);
            CHECK(flag==true);
            flag = p1.placeSettlement(9, 2, b); // is near road or far from othe settlement
            CHECK(flag==true);
            CHECK(resorces[BRICK] == 1);        // check if the player paid for the city
            CHECK(resorces[LUMBER] == 0);
            CHECK(resorces[GRAIN] == 1);
            CHECK(resorces[WOOL] == 0);
            CHECK(resorces[ORE] == 0);
            p1.printPieces();
        }
    }
}
