//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_GHOST_HPP
#define IMACMAN_GHOST_HPP

#include "Tile.hpp"
#include "ScaredGhostState.hpp"
#include "ClydeState.hpp"
#include "PinkyState.hpp"
#include "InkyState.hpp"
#include "BlinkyState.hpp"
#include "WaitingState.hpp"

enum{INKY, PINKY, BLINKY, CLYDE};

class Ghost {
public:
    Ghost() = default;
    Ghost(Tile *tile, int baseState);
    ~Ghost();
    void setBaseState();
    void move();
    int collide();
    void returnToStartPos();
    void setScaredState();
    //returns vector of path from s to d
    void createRenderModel();
    void render();
    int Dijkstra(int A, int B, std::vector<std::vector<int>> neighbours);
    const glm::vec2 &getPosition() const;

private:
    Tile * startingTile;
    Tile * tile;
    glm::vec2 position;
    float rotation;
    int baseState;
    GhostState * state;
    RenderModel * renderModel;

};


#endif //IMACMAN_GHOST_HPP
