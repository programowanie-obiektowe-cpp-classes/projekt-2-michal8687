#include "game_mechanics.hpp"

float distance(Node origin, Node target)
{
    int dx = int(origin.x_coordinate) - int(target.x_coordinate);
    int dy = int(origin.y_coordinate) - int(target.y_coordinate);
    return sqrt(dx * dx + dy * dy);
}

int reverseDir(int dir)
{
    switch (dir)
    {
    case (1):
        return 2;
    case (2):
        return 1;
    case (3):
        return 4;
    case (4):
        return 3;
    default:
        return 0;
    }
}

Map::Map()
{
    //int collectibles = 0;
    
    // 0 = œciana
    // 1 = punkt
    // 2 = power pellet
    // 3 = pusty korytarz
    // 4 = tunel
    // 5 = wnêtrze domu duchów
    // 6 = brama domu duchów
    int initial_layout[31][28] =
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
        {0,2,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0},
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
        {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,3,0,0,3,0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,3,0,0,3,0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,3,3,3,3,3,3,3,3,3,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,0,0,0,6,6,0,0,0,3,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,0,5,5,5,5,5,5,0,3,0,0,1,0,0,0,0,0,0},
        {4,3,3,3,3,3,1,3,3,3,0,5,5,5,5,5,5,0,3,3,3,1,3,3,3,3,3,4},
        {0,0,0,0,0,0,1,0,0,3,0,5,5,5,5,5,5,0,3,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,3,3,3,3,3,3,3,3,3,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
        {0,2,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,2,0},
        {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
        {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
        {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            tile_layout[i][j] = initial_layout[i][j];
            /*
            if (tile_layout[i][j] == 1)
            {
                collectibles++;
                std::cout << collectibles << std::endl;
            }*/
        }
    }
    for (int y = 0; y < 31; y++)
    {
        for (int x = 0; x < 28; x++)
        {
            if (isWall(x, y))
            {
                continue;
            }
            Node new_node;
            new_node.connections[0] = x > 0 && !isWall(x - 1, y);//Lewo
            new_node.connections[1] = x < 28 && !isWall(x + 1, y);//Prawo
            new_node.connections[2] = y > 0 && !isWall(x, y - 1);//Gora
            new_node.connections[3] = y < 31 && !isWall(x, y + 1);//Dol
            int count = new_node.connections[0] + new_node.connections[1] + new_node.connections[2] + new_node.connections[3];
            bool isTurn = (new_node.connections[2] && new_node.connections[0]) 
                || (new_node.connections[2] && new_node.connections[1]) 
                || (new_node.connections[3] && new_node.connections[0]) 
                || (new_node.connections[3] && new_node.connections[1]);
            if (count >= 3 || isTurn)
            {
                new_node.x_coordinate = x;
                new_node.y_coordinate = y;
                nodes.push_back(new_node);
            }
        }
    }
    Node new_node;
    new_node.connections[0] = 0;
    new_node.connections[1] = 1;
    new_node.connections[2] = 0;
    new_node.connections[3] = 0;
    new_node.x_coordinate = 1;
    new_node.y_coordinate = 14;
    nodes.push_back(new_node);
    new_node.connections[0] = 1;
    new_node.connections[1] = 0;
    new_node.x_coordinate = 26;
    new_node.y_coordinate = 14;
    nodes.push_back(new_node);
    for (Node& n : nodes)
    {
        if (n.connections[0])
        {
            int x = n.x_coordinate;
            n.neighbours[0] = 0 - 1;
            while (x > -1)
            {
                x--;
                if (findNodeAt(x, n.y_coordinate) >= 0)
                {
                    n.neighbours[0] = findNodeAt(x, n.y_coordinate);
                    break;
                }
            }
        }
        if (n.connections[1])
        {
            int x = n.x_coordinate;
            n.neighbours[1] = 0-1;
            while (x < 28)
            {
                x++;
                if (findNodeAt(x, n.y_coordinate) >= 0)
                {
                    n.neighbours[1] = findNodeAt(x, n.y_coordinate);
                    break;
                }
            }
        }
        if (n.connections[2])
        {
            int y = n.y_coordinate;
            n.neighbours[2] = -1;
            while (y > -1)
            {
                y--;
                if (findNodeAt(n.x_coordinate, y) >= 0)
                {
                    n.neighbours[2] = findNodeAt(n.x_coordinate, y);
                    break;
                }
            }
        }
        if (n.connections[3])
        {
            int y = n.y_coordinate;
            n.neighbours[3] = -1;
            while (y > -1)
            {
                y++;
                if (findNodeAt(n.x_coordinate, y) >= 0)
                {
                    n.neighbours[3] = findNodeAt(n.x_coordinate, y);
                    break;
                }
            }
        }
        //std::cout << n.x_coordinate << "\t" << n.y_coordinate << "\t" << n.neighbours[0] << "\t" << n.neighbours[1] << "\t" << n.neighbours[2] << "\t" << n.neighbours[3] << std::endl;
    }
}

bool Map::isWall(int x_coordinate, int y_coordinate)
{
    if (0 <= x_coordinate && 28 > x_coordinate && 0 <= y_coordinate && 31 > y_coordinate)
    {
        if (tile_layout[y_coordinate][x_coordinate] == 0 || tile_layout[y_coordinate][x_coordinate] == 6 || tile_layout[y_coordinate][x_coordinate] == 5)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool Map::isTunnel(int x_coordinate, int y_coordinate)
{
    if (0 <= x_coordinate && 28 > x_coordinate && 0 <= y_coordinate && 31 > y_coordinate)
    {
        if (tile_layout[y_coordinate][x_coordinate] == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Map::collectItem(int x_coordinate, int y_coordinate)
{
    if (0 <= x_coordinate && 28 > x_coordinate && 0 <= y_coordinate && 31 > y_coordinate)
    {
        if (tile_layout[y_coordinate][x_coordinate] == 1 || tile_layout[y_coordinate][x_coordinate] == 2)
        {
            tile_layout[y_coordinate][x_coordinate] = 3;
        }
        else
        {
            std::cout << "No collection" << std::endl;
        }
    }
    else
    {
        throw("Invalid location outside map");
    }
}

int Map::findNodeAt(int x, int y)
{
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i].x_coordinate == x && nodes[i].y_coordinate == y)
        {
            return i;
        }
    }
    return -1;
}

std::vector<Node> Map::getNodes()
{
    return nodes;
}

int Map::operator()(int x_coordinate, int y_coordinate)
{
    return tile_layout[y_coordinate][x_coordinate];
}

Ghost& Ghost::operator=(const Ghost& g)
{
    if (this != &g)
    {
        state = g.state;           // 1 - CHASE, 2 - SCATTER, 3 - FRIGHTENED, 4 - EATEN
        speed = g.speed;         // aktualna prêdkoœæ
        dir = g.dir;             // aktualny kierunek
        x_coordinate = g.x_coordinate;
        y_coordinate = g.y_coordinate;          // pozycja (piksele)
        currentNode = g.currentNode;      // indeks wêz³a celu
        targetNode = g.targetNode;      // indeks wêz³a celu
    }
    return *this;
}

void Ghost::chooseDirection(Map map)
{
    currentNode = map.findNodeAt(x_coordinate, y_coordinate);
    int bestDir = -1;
    float bestDist = 50;
    if (currentNode == targetNode)
    {
        bestDir = 0;
    }
    else
    {
        for (int i = 1; i <= 4; i++)
        {
            if (!map.getNodes()[currentNode].connections[i - 1])
            {
                //std::cout << "No connection -> " << i << std::endl;
                continue;
            }
            if (reverseDir(dir) == i)
            {
                //std::cout << "No reverse -> " << i << std::endl;
                continue;
            }
            //std::cout << "Distance reading -> " << i << " reverse of previous " << reverseDir(dir) << std::endl;
            Node neighbour = map.getNodes()[map.getNodes()[currentNode].neighbours[i - 1]];
            float d = distance(neighbour, map.getNodes()[targetNode]);
            if (d < bestDist)
            {
                bestDist = d;
                bestDir = i;
            }
        }
    }
    dir = bestDir;
}

void Ghost::moveGhost(float timestep)
{
    float center;
    switch (dir)
    {
    case 1: 
        x_coordinate -= speed * timestep; 
        center = fmod(y_coordinate, 1) - 0.5;
        y_coordinate = y_coordinate - center;
        break;
    case 2: 
        x_coordinate += speed * timestep;
        center = fmod(y_coordinate, 1) - 0.5;
        y_coordinate = y_coordinate - center;
        break;
    case 3: 
        y_coordinate -= speed * timestep;
        center = fmod(x_coordinate, 1) - 0.5;
        x_coordinate = x_coordinate - center;
        break;
    case 4: 
        y_coordinate += speed * timestep;
        center = fmod(x_coordinate, 1) - 0.5;
        x_coordinate = x_coordinate - center;
        break;
    }
}

void Ghost::handleGhostTunnel(Map map)
{
    if (map(x_coordinate, y_coordinate) == 4)
    {
        if (x_coordinate < 0)
            x_coordinate = (28 - 1);
        else if (x_coordinate > 27)
            x_coordinate = 0;
    }
}

void Ghost::updateTargetNode(Map map, Player p)
{
    int bestDist = 50;
    int bestNode = currentNode;
    switch (state)
    {
    case 2:
        targetNode = 1;
        break;
    case 1:
        //computeChaseTarget(g);
        Node player_node;
        player_node.x_coordinate = p.x;
        player_node.y_coordinate = p.y;
        for (int i = 0; i < map.getNodes().size(); ++i)
        {
            if (distance(player_node, map.getNodes()[i]) < bestDist && !(i == currentNode))
            {
                bestDist = distance(player_node, map.getNodes()[i]);
                bestNode = i;
            }
        }
        targetNode = bestNode;
        break;
    case 3:
        targetNode = 64;
        break;

    case 4:
        targetNode = 23;
        break;
    }
}


Game::Game()
{
    player.x = 14;
    player.y = 23.5;
    player.speed = 7.5;
    player.direction = 1;
    player.next_direction = 0;
    points = 0;
    collectibles_left = 242;
    global_time = 0;
    for (int i = 0; i < 4; i++)
    {
        ghosts[i].y_coordinate = 11.5;
        ghosts[i].x_coordinate = 12.5;
        ghosts[i].currentNode = 0;
        ghosts[i].targetNode = 64;
        ghosts[i].dir = 2;
        ghosts[i].state = 2;
    }
}

Game::Game(const Game& g)
{
    Game z;
    z.player = g.player;
    z.map = g.map;
    z.points = g.points;
    z.collectibles_left = g.collectibles_left;
    z.global_time = g.global_time;
    z.ghosts[0] = g.ghosts[0];
    z.ghosts[1] = g.ghosts[1];
    z.ghosts[2] = g.ghosts[2];
    z.ghosts[3] = g.ghosts[3];
}

Game &Game::operator=(const Game& g)
{
    if (this != &g)
    {
        player = g.player;
        map = g.map;
        points = g.points;
        collectibles_left = g.collectibles_left;
        global_time = g.global_time;
        ghosts[0] = g.ghosts[0];
        ghosts[1] = g.ghosts[1];
        ghosts[2] = g.ghosts[2];
        ghosts[3] = g.ghosts[3];
    }
    return *this;
}

void Game::movePlayer(float elapsed_time)
{
    float predicted_x, predicted_y;
    predictedMovement(predicted_x, predicted_y, elapsed_time + 0.5 / player.speed, player.next_direction);
    //std::cout << "Zmiana kierunku " << player.direction << " x=" << predicted_x << " y=" << predicted_y << std::endl;
    if (player.next_direction > 0 && isCentered(player.x, elapsed_time * player.speed) && isCentered(player.y, elapsed_time * player.speed) && !map.isWall(predicted_x, predicted_y))
    {
        player.direction = player.next_direction;
    }
    else
    {
        predictedMovement(predicted_x, predicted_y, elapsed_time + 0.5 / player.speed, player.direction);
        //std::cout << "Podtrzymanie kierunku" << std::endl;
    }
    if (!map.isWall(predicted_x, predicted_y))
    {
        predictedMovement(player.x, player.y, elapsed_time, player.direction);
    }
    if (map.isTunnel(player.x, player.y))
    {
        if (player.x < 1)
        {
            player.x = 26.9;
        }
        else
        {
            player.x = 1.1;
        }
    }
}

void Game::setInputDirection(int dir)
{
    player.next_direction = dir;
}

float Game::getPlayerX()
{
    return player.x;
}

float Game::getPlayerY()
{
    return player.y;
}

bool isCentered(float coordinate, float frame_distance)
{
    float center = fmod(coordinate, 1) - 0.5;
    //std::cout << (fabs(center) < 0.2) << std::endl;
    return fabs(center) < frame_distance * 1.1;
}

void Game::predictedMovement(float& predicted_x, float& predicted_y, float elapsed_time, int direction)
{
    predicted_x = player.x;
    predicted_y = player.y;
    float center;
    if (direction == 1)
    {
        predicted_x = predicted_x - player.speed * elapsed_time;
        center = fmod(predicted_y, 1) - 0.5;
        predicted_y = predicted_y - center;
    }
    else if (direction == 2)
    {
        predicted_x = predicted_x + player.speed * elapsed_time;
        center = fmod(predicted_y, 1) - 0.5;
        predicted_y = predicted_y - center;
    }
    else if (direction == 3)
    {
        predicted_y = predicted_y - player.speed * elapsed_time;
        center = fmod(predicted_x, 1) - 0.5;
        predicted_x = predicted_x - center;
    }
    else if (direction == 4)
    {
        predicted_y = predicted_y + player.speed * elapsed_time;
        center = fmod(predicted_x, 1) - 0.5;
        predicted_x = predicted_x - center;
    }
}

int Game::getPoints()
{
    return points;
}

void Game::checkForCollectible()
{
    if (map(player.x, player.y) == 1)
    {
        points = points + 10;
        collectibles_left--;
        map.collectItem(player.x, player.y);
    }
}

Map Game::getMap()
{
    return map;
}

bool Game::checkVictory()
{
    if (collectibles_left == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Game::getSpeedForState(int state)
{
    switch (state)
    {
    case 1:
        return 7.5;
    case 2:
        return 7.5;
    case 3:
        return 7.5 * 0.5;
    case 4:
        return 7.5 * 1.5;
    default:
        return 0;
    }
}

bool Game::checkPacmanCollision()
{
    for (int i = 0; i < 4; i++)
    {
        float dx = ghosts[i].x_coordinate - player.x;
        float dy = ghosts[i].y_coordinate - player.y;

        if (sqrt(dx * dx + dy * dy) < 0.75)
        {
            if (ghosts[i].state == 3)
                ghosts[i].state = 4;
            else if (ghosts[i].state != 4)
                return true;
        }
    }
    return false;
}

void Game::updateGlobalModeTimer(float timestep)
{
    global_time = global_time + timestep;
    static const int mode_table[8][2] =
    {
        { 2, 7 },
        { 1, 20 },
        { 2, 7 },
        { 1, 20 },
        { 2, 5 },
        { 1, 20 },
        { 2, 5 },
        { 1, 1000000000 }
    };
    int current_mode = 1;
    float accounted_time = 0;
    for (int i = 0; i < 8; i++)
    {
        if (global_time > accounted_time)
        {
            current_mode = mode_table[i][0];
            //std::cout << " Accounted time " << accounted_time << std::endl;
        }
        accounted_time = accounted_time + mode_table[i][1];
    }
    for (int i = 0; i < 4; i++)
    {
        if (ghosts[i].state == 1 || ghosts[i].state == 2)
        {
            if (!(ghosts[i].state == current_mode) && ghosts[i].dir > 0)
            {
                std::cout << " State change " << ghosts[i].state << " to " << current_mode << " direction switch " << ghosts[i].dir << " to " << reverseDir(ghosts[i].dir) << std::endl;
                ghosts[i].dir = reverseDir(ghosts[i].dir);
            }
            ghosts[i].state = current_mode;
        }
    }
}

void Game::updateGhosts(float timestep)
{
    //std::cout << " state= " << ghosts[0].state << std::endl;
    updateGlobalModeTimer(timestep);
    for (int i = 0; i < 4; i++)
    {
        ghosts[i].previousTargetNode = ghosts[i].targetNode;
        ghosts[i].updateTargetNode(map, player);
        ghosts[i].speed = getSpeedForState(ghosts[i].state);
        if (map.findNodeAt(ghosts[i].x_coordinate, ghosts[i].y_coordinate) >= 0 && ghosts[i].atNodeCenter(timestep) 
            && (!(map.findNodeAt(ghosts[i].x_coordinate, ghosts[i].y_coordinate) == ghosts[i].currentNode) || !(ghosts[i].previousTargetNode == ghosts[i].targetNode)))
        {
            ghosts[i].chooseDirection(map);
            std::cout << " At node " << std::endl;
        }
        ghosts[i].moveGhost(timestep);
        ghosts[i].handleGhostTunnel(map);
    }
    std::cout << " t= " << global_time;
    std::cout << " dir= " << ghosts[0].dir << " target= " << ghosts[0].targetNode << " current= " << ghosts[0].currentNode;
    std::cout << " state= " << ghosts[0].state << std::endl;
}

Ghost* Game::getGhosts()
{
    return ghosts;
}