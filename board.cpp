/*alonz1414@gmail.com*/
#include "board.hpp"
#include "edge.hpp"

namespace ariel
{
    Board::Board()
    {
        initBoard();
    }
    Board::~Board()
    {
        for (Edge *edge : edges)
        {
            delete edge;
        }
    }
    // copy constuctor. To avoid double deletion
    Board::Board(const Board &other)
    {
        hexes = other.hexes;
        vertices = other.vertices;
        for (Edge *edge : other.edges)
        {
            edges.push_back(new Edge(*edge));
        }
    }
    void Board::initBoard()
    {
        initHexes();
        initVertices();
        initEdges();
    }

    void Board::initHexes()
    {
        hexes.resize(5);
        hexes[0].resize(3);
        hexes[1].resize(4);
        hexes[2].resize(5);
        hexes[3].resize(4);
        hexes[4].resize(3);
        srand(static_cast<size_t>(time(nullptr)));
        for (size_t i = 0; i < 3; i++)
        {
            hexes[0][i] = Hex();
            hexes[0][i].setID(i + 1);
        }
        for (size_t i = 0; i < 4; i++)
        {
            hexes[1][i] = Hex();
            hexes[1][i].setID(i + 4);
        }
        for (size_t i = 0; i < 5; i++)
        {
            hexes[2][i] = Hex();
            hexes[2][i].setID(i + 8);
        }
        for (size_t i = 0; i < 4; i++)
        {
            hexes[3][i] = Hex();
            hexes[3][i].setID(i + 13);
        }
        for (size_t i = 0; i < 3; i++)
        {
            hexes[4][i] = Hex();
            hexes[4][i].setID(i + 17);
        }
    }
    void Board::initVertices()
    {
        vertices.resize(12);
        vertices[0].resize(3);
        vertices[1].resize(4);
        vertices[2].resize(4);
        vertices[3].resize(5);
        vertices[4].resize(5);
        vertices[5].resize(6);
        vertices[6].resize(6);
        vertices[7].resize(5);
        vertices[8].resize(5);
        vertices[9].resize(4);
        vertices[10].resize(4);
        vertices[11].resize(3);

        for (size_t i = 0; i < 3; i++)
        {
            vertices[0][i] = Vertex(0, i);
        }
        for (size_t i = 0; i < 4; i++)
        {
            vertices[1][i] = Vertex(1, i);
        }
        for (size_t i = 0; i < 4; i++)
        {
            vertices[2][i] = Vertex(2, i);
        }
        for (size_t i = 0; i < 5; i++)
        {
            vertices[3][i] = Vertex(3, i);
        }
        for (size_t i = 0; i < 5; i++)
        {
            vertices[4][i] = Vertex(4, i);
        }
        for (size_t i = 0; i < 6; i++)
        {
            vertices[5][i] = Vertex(5, i);
        }
        for (size_t i = 0; i < 6; i++)
        {
            vertices[6][i] = Vertex(6, i);
        }
        for (size_t i = 0; i < 5; i++)
        {
            vertices[7][i] = Vertex(7, i);
        }
        for (size_t i = 0; i < 5; i++)
        {
            vertices[8][i] = Vertex(8, i);
        }
        for (size_t i = 0; i < 4; i++)
        {
            vertices[9][i] = Vertex(9, i);
        }
        for (size_t i = 0; i < 4; i++)
        {
            vertices[10][i] = Vertex(10, i);
        }
        for (size_t i = 0; i < 3; i++)
        {
            vertices[11][i] = Vertex(11, i);
        }

        for (size_t x = 0; x < hexes.size(); x++)
        {
            for (size_t y = 0; y < hexes[x].size(); y++)
            {
                Hex &hex = hexes[x][y];
                if (x < 2)
                {
                    vertices[2 * x + 3][y + 1].addToAdjacentHexes(&hex); // bottom vertex
                }
                else
                {
                    vertices[2 * x + 3][y].addToAdjacentHexes(&hex); // bottom vertex
                }
                if (x < 3)
                {
                    vertices[2 * x][y].addToAdjacentHexes(&hex); // top vertex
                }
                else
                {
                    vertices[2 * x][y + 1].addToAdjacentHexes(&hex); // top vertex
                }
                vertices[2 * x + 1][y + 1].addToAdjacentHexes(&hex); // top-right vertex
                vertices[2 * x + 2][y + 1].addToAdjacentHexes(&hex); // bottom-right vertex
                vertices[2 * x + 2][y].addToAdjacentHexes(&hex);     // bottom-left vertex
                vertices[2 * x + 1][y].addToAdjacentHexes(&hex);     // top-left vertex
            }
        }
    }

    void Board::initEdges()
    {
        edges.clear();     
        edges.reserve(72); 

        for (size_t x = 0; x < vertices.size() - 1; x++)
        {
            for (size_t y = 0; y < vertices[x].size(); y++)
            {
                if (x < 6 || x % 2 != 0 || y < vertices[x].size() - 1)
                {
                    Edge *e = new Edge(&vertices[x][y], &vertices[x + 1][y]);
                    edges.push_back(e);
                    vertices[x][y].addToAdjacentEdges(e);
                    vertices[x][y].addToAdjacentVertices(&vertices[x + 1][y]);
                    vertices[x + 1][y].addToAdjacentVertices(&vertices[x][y]);
                    vertices[x + 1][y].addToAdjacentEdges(e);
                }
                if (x < 6 && x % 2 == 0)
                {
                    Edge *e = new Edge(&vertices[x][y], &vertices[x + 1][y + 1]);
                    edges.push_back(e);
                    vertices[x][y].addToAdjacentEdges(e);
                    vertices[x][y].addToAdjacentVertices(&vertices[x + 1][y + 1]);
                    vertices[x + 1][y + 1].addToAdjacentVertices(&vertices[x][y]);
                    vertices[x + 1][y + 1].addToAdjacentEdges(e);
                }
                else if (x >= 6 && x % 2 == 0 && y > 0)
                {
                    Edge *e = new Edge(&vertices[x][y], &vertices[x + 1][y - 1]);
                    edges.push_back(e);
                    vertices[x][y].addToAdjacentEdges(e);
                    vertices[x][y].addToAdjacentVertices(&vertices[x + 1][y - 1]);
                    vertices[x + 1][y - 1].addToAdjacentVertices(&vertices[x][y]);
                    vertices[x + 1][y - 1].addToAdjacentEdges(e);
                }
            }
        }
        for (Edge *edge1 : edges)
        {
            for (Edge *edge2 : edges)
            {
                if (edge1 != edge2)
                {
                    edge1->addToAdjacentEdges(edge2);
                }
            }
        }
    }
    Edge *Board::getEdgeByCoordinates(size_t x1, size_t y1, size_t x2, size_t y2)
    {
        for (Edge *edge : edges)
        {
            if ((edge->getV1()->getX() == x1 && edge->getV1()->getY() == y1 && edge->getV2()->getX() == x2 && edge->getV2()->getY() == y2) ||
                (edge->getV1()->getX() == x2 && edge->getV1()->getY() == y2 && edge->getV2()->getX() == x1 && edge->getV2()->getY() == y1))
            {
                return edge;
            }
        }
        return nullptr;
    }

    Vertex *Board::getVertexByCoordinates(size_t x, size_t y)
    {
        static const std::vector<size_t> rowSizes = {3, 4, 4, 5, 5, 6, 6, 5, 5, 4, 4, 3};
        if (x >= rowSizes.size())
        {
            std::cerr << "Invalid row index!" << std::endl;
            return nullptr;
        }
        if (y >= rowSizes[x])
        {
            std::cerr << "Invalid column index for the given row!" << std::endl;
            return nullptr;
        }
        return &vertices[x][y];
    }

    void Board::printHexas()
    {

        std::cout << "Board:" << std::endl;
        std::cout << "            ";
        for (size_t i = 0; i < 3; i++)
        {
            std::cout << "    ";
            std::cout << hexes[0][i].getID() << "(" << hexes[0][i].getNumber() << "," << hexes[0][i].getLandType() << ")";
        }
        std::cout << std::endl
                  << std::endl;
        std::cout << "      ";
        for (size_t i = 0; i < 4; i++)
        {
            std::cout << "    ";
            std::cout << hexes[1][i].getID() << "(" << hexes[1][i].getNumber() << "," << hexes[1][i].getLandType() << ")";
        }
        std::cout << std::endl
                  << std::endl;
        for (size_t i = 0; i < 5; i++)
        {
            std::cout << "    ";
            std::cout << hexes[2][i].getID() << "(" << hexes[2][i].getNumber() << "," << hexes[2][i].getLandType() << ")";
        }
        std::cout << std::endl
                  << std::endl;
        std::cout << "      ";
        for (size_t i = 0; i < 4; i++)
        {
            std::cout << "    ";
            std::cout << hexes[3][i].getID() << "(" << hexes[3][i].getNumber() << "," << hexes[3][i].getLandType() << ")";
        }
        std::cout << std::endl
                  << std::endl;
        std::cout << "            ";
        for (size_t i = 0; i < 3; i++)
        {
            std::cout << "    ";
            std::cout << hexes[4][i].getID() << "(" << hexes[4][i].getNumber() << "," << hexes[4][i].getLandType() << ")";
        }
        std::cout << std::endl;
    }

    bool Board::addSettlementToBoard(size_t x, size_t y, Piece *piece)
    {
        if (x >= vertices.size() || y >= vertices[x].size())
        {
            std::cout << "Invalid coordinates! Cannot place Settlement" << std::endl;
            return false;
        }
        if (vertices[x][y].isValidVertex())
        {
            vertices[x][y].setPiece(piece);
            return true;
        }
        std::cout << "Invalid Vertex! " << vertices[x][y].getPiece()->getPlayer()->getName() << " already has a settlement/city in this vertex" << std::endl;
        return false;
    }
    bool Board::addRoadToBoard(Edge &e, Piece &piece)
    {
        if (e.isValidEdge())
        {
            e.setPiece(&piece);
            return true;
        }
        std::cout << "Invalid Edge! " << e.getPiece()->getPlayer()->getName() << " already has a road in this edge" << std::endl;
        return false;
    }
    std::vector<std::vector<Vertex>> &Board::getVertices()
    {
        return this->vertices;
    }
    std::vector<std::vector<Hex>> &Board::getHexes()
    {
        return this->hexes;
    }
    void Board::addResources(int number) const
    {
        for (size_t i = 0; i < hexes.size(); i++)
        {
            for (size_t j = 0; j < hexes[i].size(); j++)
            {
                const Hex &hex = hexes[i][j];
                int num = hex.getNumber();
                std::string landType = hex.getLandType();
                if (number == num)
                {
                    for (size_t x = 0; x < vertices.size(); x++)
                    {
                        for (size_t y = 0; y < vertices[x].size(); y++)
                        {
                            Piece *piece = vertices[x][y].getPiece();
                            if (piece != nullptr && vertices[x][y].isAdjacentHex(hex))
                            {
                                Player *player = piece->getPlayer();
                                if (landType != "Desert")
                                {
                                    player->addResource(landType);
                                    if (piece->getType() == "City") // Add double resource if the Piece is a City
                                    {
                                        player->addResource(landType);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}