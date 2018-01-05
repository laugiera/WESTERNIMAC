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
    //returns vector of path from s to d
    static std::vector<Tile *> isReachable(Tile s, Tile d, std::vector<std::vector<Tile>> tiles);
    void createRenderModel();
    virtual void color() = 0;
    void render();

private:
    Tile * tile;
    glm::vec2 position;
    float angle;

protected:
    RenderModel * renderModel;

};


#endif //IMACMAN_GHOST_HPP
