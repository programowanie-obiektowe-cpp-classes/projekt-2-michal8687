#include <iostream>
#include <vector>

bool isCentered(float coordinate, float frame_distance);
int reverseDir(int dir);

struct Node
{
    int x_coordinate, y_coordinate;
    bool connections[4];
    int neighbours[4];
};

float distance(Node origin, Node target);

class Map
{
public:
	Map();
	int operator()(int y, int x);
    bool isWall(int x_coordinate, int y_coordinate);
    bool isTunnel(int x_coordinate, int y_coordinate);
    void collectItem(int x_coordinate, int y_coordinate);
    int findNodeAt(int x, int y);
    std::vector<Node> getNodes();
    //std::vector<Node> nodes;
private:
	int tile_layout[31][28];
    std::vector<Node> nodes;
};

struct Player
{
    float x;        // pozycja w kafelkach
    float y;
    float speed;    // kafelek / s
    int direction;        // aktualny kierunek
    int next_direction;    // kierunek ¿¹dany (z inputu)
};

struct Ghost
{
    bool atNodeCenter(float timestep) { return isCentered(x_coordinate, timestep * speed) && isCentered(y_coordinate, timestep * speed); }
    void chooseDirection(Map map);
    void moveGhost(float timestep);
    void handleGhostTunnel(Map map);
    void updateTargetNode(Map map, Player p);
    Ghost& operator=(const Ghost& g);
    int state;           // 1 - CHASE, 2 - SCATTER, 3 - FRIGHTENED, 4 - EATEN
    float speed;         // aktualna prêdkoœæ
    int dir;             // aktualny kierunek
    float x_coordinate, y_coordinate;          // pozycja (piksele)
    //int nextDir;         // wybrany kierunek na skrzy¿owaniu
    int currentNode;
    int targetNode;      // indeks wêz³a celu
    int previousTargetNode;      // indeks wêz³a celu
};

class Game
{
public:
    Game();
    Game(const Game&);
    Game& operator=(const Game& g);
    ~Game() = default;
    void movePlayer(float elapsed_time);
    void setInputDirection(int dir);
    float getPlayerX();
    float getPlayerY();
    void predictedMovement(float& predicted_x, float& predicted_y, float elapsed_time, int direction);
    int getPoints();
    void checkForCollectible();
    Map getMap();
    bool checkVictory();
    int getSpeedForState(int state);
    bool checkPacmanCollision();
    void updateGlobalModeTimer(float timestep);
    void updateGhosts(float timestep);
    Ghost* getGhosts();
private:
    Player player;
    Map map;
    Ghost ghosts[4];
    int points;
    int collectibles_left;
    float global_time;
};