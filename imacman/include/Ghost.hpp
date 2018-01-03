//
// Created by Amel on 1/1/2018.
//

#ifndef IMACMAN_GHOST_HPP
#define IMACMAN_GHOST_HPP

#include "Tile.hpp"
#include "CactusMan.hpp"

class Ghost {
public:
    Ghost();
    Ghost(Tile *tile);
    virtual ~Ghost();
    virtual void move(CactusMan &Player);
    void Drop(CactusMan &Player);
    void createRenderModel();
    void render();

private:
    Tile * tile;
    glm::vec2 position;
    float angle;
    RenderModel * renderModel;

};


#endif //IMACMAN_GHOST_HPP
