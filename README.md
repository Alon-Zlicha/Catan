# Catan Game Project
Settlers of Catan is a board game for 3 players that combines strategic thinking, resource management and trading ability.
## Board Structure
Hexagon Tiles: The board consists of 19 hexagonal tiles, each representing different terrain types (e.g., hills, forest) and numbered from 2 to 12 (except for the desert, which yields no resources).
Vertices: Points where settlements and cities are placed. They connect to adjacent hex tiles and can be upgraded from settlements to cities.Each vertex is represented by a unique pair of coordinates that denote its specific position on the board. The board is structured into 12 rows of vertices, each row varying in the number of vertices it contains.
Edges: connect vertices and can hold roads.Represnted by 2 vertices(4 coordinates).
## Game Rules
### Purpose of the game 
The purpose of the game is to score 10 or more victory points to win. Victory points are earned by building settlements, cities and by getting specific development cards in the game.
### The beginning of the game
The turn order is determined by the order in which players enter the game.
Players start with 2 settlements and 2 roads.
Each settlement provides initial resources based on adjacent hexagon tiles.
### Resource Types
Resources include Brick, Lumber, Wool, Grain and Ore.
These resources are obtained from different terrain types (hills, forest, pasture, agricultural and maountains).
### Player's Turn
Players take turns rolling dice, collecting resources based on the result.
During their turn, players can trade resources with other players , build roads, settlements, cities, or buy development cards.
Players can use cards at any point during their turn. however, using a card ends their turn immediately.
Once a settlement is upgraded to a city, the player loses the point of the settlement and receives 2 points
## Rules Of Building
  Road: It costs 1 brick and 1 lumber. A road can only be built adjacent to a settlement (or city) owned by the player or to other road sections that are also owned by the player.
  Settlement: The costs 1 brick, 1 lumber, 1 wool, and 1 grain. A settlement can be built at a vertex where at least one road leads out, and it must be at least 2 edges away from any other settlement.
  City: A city can replace an existing settlement. It costs 3 ore and 2 grain.Once a settlement is upgraded to a city, the player loses the point of the settlement and receives 2 points.A city increases resource production from adjacent tiles to double the original amount.
### Development Cards 
Development cards costs 1 wool 1 ore and 1 grain.Development cards include:
  Monopoly: The player chooses a resource and the other players are required to transfer this resource to him.
  Year of Plenty: The player gets to choose two resources from the bank.
  Knight: Used to build the Largest Army card, which provides two victory points based on having all three knights in the game.
  Victory Point cards: These cards provide one victory point to the player who holds them. There are only 4 of them in the game.
  Road Building: Allows the player to build two roads for free on the board.
### Game End  
The game ends on a turn where one player has reached 10 or more victory points. To win the game, the player needs to have his turn and in that turn have at least 10 points.  
### Trading
Players can trade with each other, exchanging cards or resources as they see fit.
### Special Event
If a player rolls a 7, all players with more than 7 resource cards must discard half of their cards.
## Hierarchy of Classes
The Catan game project uses a built-in hierarchy of classes to manage its game mechanics efficiently. At the core of this structure are abstract classes and composition relationships.
### Abstract Classes And Inheritance
Piece: simplifies common features and behaviors of game pieces such as settlements and roads, ensuring consistent functionality across different types of player pieces on the board.
DevelopmentCard: By defining an abstract class for development cards and deriving specific card types from it, the game can handle randomly chosen cards uniformly, ensuring consistent handling of card effects and interactions within the game logic.
### Composition
Composition in the project involves relationships where higher-level objects are constructed using lower-level objects as building blocks. For instance, the Board class utilizes Edge, Vertex, and Hexagon components, which in turn incorporate Piece instances like Settlements and Roads. This compositional approach allows for modular design, encapsulation of responsibilities, and easy management of complex interactions between game elements.
## Testing The project
The test file verifies the implementation of the Catan game. It covers aspects such as board initialization, player actions like placing settlements and building roads, resource management through dice rolls, the functionality of development cards, and player trading. Sub-cases are used to test specific scenarios, ensuring that all game mechanics adhere to the rules and validating the overall reliability and coherence of the game's implementation.
