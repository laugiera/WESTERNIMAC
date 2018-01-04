//
// Created by Lou Landry on 30/12/2017.
//

#ifndef IMACMAN_GAMEBOARD_HPP
#define IMACMAN_GAMEBOARD_HPP

#include "Tile.hpp"
#include <string>
#include "BoardLoader.hpp"
#include "InkyGhost.hpp"
#include "PinkyGhost.hpp"
#include "BlinkyGhost.hpp"
#include "ClydeGhost.hpp"
#include "CactusMan.hpp"
#include "CameraFPS.hpp"
#include "Camera2D.hpp"


class GameBoard {
public:
    GameBoard() = default;

    GameBoard(const std::string &boardPath);

    virtual ~GameBoard();

    void loadBoard();

    void createGhosts();

    void createCactusman();

    void collision(Tile &tile, CactusMan &player);

    void render(glimac::SDLWindowManager windowManager);

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

    void zoom();

    void dezoom();

    void changeCamera();

    void destroyCamera();


private:
    CactusMan player;
    std::vector<std::vector<Tile>> tiles;
    std::string boardPath;
    std::vector<Ghost*> ghosts;
    Camera * currentCam;
    Camera2D * cam2D;
    CameraFPS * camFPS;

};


#endif //IMACMAN_GAMEBOARD_HPP
