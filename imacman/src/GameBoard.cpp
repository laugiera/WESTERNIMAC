//
// Created by Lou Landry on 30/12/2017.
//

#include "GameBoard.hpp"

GameBoard::GameBoard(const std::string &boardPath) : boardPath(boardPath),
                                                     cam2D(new Camera2D()),
                                                     camFPS(new CameraFPS()),
                                                     gumNumber(0)
{

    try {
        loadBoard();
        createGhosts();
        createCactusman();
    } catch (std::runtime_error &e){
        std::string message("GameBoard has not been properly initialized : ");
        message += e.what();
        throw std::runtime_error(message);
    }
    currentCam = camFPS;
    handleCamera();


}

/**
 * Loads the Tile matrix from a file
 * Throws std::runtime_error if no Tiles have been found
 */
void GameBoard::loadBoard() {
    BoardLoader boardLoader = BoardLoader();
    tiles = boardLoader.createTileMatrix(boardPath);
    if (tiles.empty() || tiles[0].empty() ){
        throw std::runtime_error("Tiles have not been loaded");
    }

}

/**
 * Creates 4 ghost at their starting position. The starting position has been set in the file
 * Has to be called after loadBoard().
 * Throws std::runtime_error if no starting position has been found
 */
void GameBoard::createGhosts() {
    //look for tiles in the tileMatrix which have GHOST for initialState
    std::vector<Tile*> startingTiles;
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            if(tile->getInitialState() == GHOST){
                startingTiles.push_back(tile);
            }
            //putting that here for the moment later will mix create Ghost and create CactusMan and this in a switch
            else if(tile->getInitialState() == GUM || tile->getInitialState() == SUPERGUM){
                gumNumber ++;
            }
        }
    }
    if(startingTiles.size() < 4){
        throw std::runtime_error("No starting position has been set for the ghosts");
    } else {
        ghosts.push_back(new Ghost(startingTiles[0], BLINKY)); // change for Blinky
        ghosts.push_back(new Ghost(startingTiles[1], PINKY)); // change for Pinky
        ghosts.push_back(new Ghost(startingTiles[2], INKY)); // change for Inky
        ghosts.push_back(new Ghost(startingTiles[3], CLYDE)); // change for Clide
    }

}

/**
 * Creates Cactusman at its starting position. The starting position has been set in the file
 * Has to be called after loadBoard().
 * Throws std::runtime_error if no starting position has been found
 */
void GameBoard::createCactusman() {
    //look for the tile in the tileMatrix which has PACMAN for initialState
    Tile * startingTile;
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            if(tile->getInitialState() == PACMAN){
                startingTile = tile;
            }
        }
    }
    if(!startingTile){
        throw std::runtime_error("No starting position has been set for Cactusman");
    } else {
        player = new CactusMan(startingTile);
    }
}


void GameBoard::handleCollisions() {
    int type = player->dropTile();
    switch (type) {
        case GUM:
            gumNumber --;
            break;
        case SUPERGUM:
            gumNumber --;
            for(Ghost * ghost : ghosts){
                ghost->setScaredState();
            }
            break;
        case PORTAL:
            handlePortal();
            break;
        default:
            break;
    }
    player->testGhostEncounter(ghosts);
}

CactusMan *GameBoard::getPlayer() const {
    return player;
}

void GameBoard::render(glimac::SDLWindowManager & windowManager) {
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            tile->render();
        }
    }
    player->render();
    for (Ghost* & ghost : ghosts){
        ghost->render();
    }
    glm::mat4 viewMatrix = currentCam->getViewMatrix();
    OpenGlManager::getInstance().drawAll(windowManager,viewMatrix, player->getPosition());
}

void GameBoard::changeCamera() {
    if (currentCam == cam2D) {
        currentCam = camFPS;
        player->setCam2D(false);
    }
    else if (currentCam == camFPS) {
        currentCam = cam2D;
        player->setCam2D(true);
    }
}

GameBoard::~GameBoard() {

}


void GameBoard::updateScore(std::string filePath){
    try {
        std::vector<std::string> fileContent = BoardLoader().load(filePath);
        if(fileContent.size()<2) throw std::runtime_error("Not enough data");
        player->setLives(Tools::intFromString(fileContent[0]));
        player->setScore(Tools::intFromString(fileContent[1]));
    } catch (std::runtime_error &e) {
        std::cerr << "Saves scores and lives could not be loaded : " << e.what() << std::endl;
    }
}


void GameBoard::moveUp() {
    player->moveFront(1);


}

void GameBoard::moveDown() {
    player->moveFront(-1);
}

void GameBoard::moveLeft() {
    player->moveLeft(1);
}

void GameBoard::moveRight() {
    player->moveLeft(-1);

}

void GameBoard::zoom() {
    cam2D->zoom(-1);
}

void GameBoard::dezoom() {
    cam2D->zoom(1);
}

void GameBoard::destroyCamera() {
    currentCam = nullptr;
    delete(cam2D);
    delete(camFPS);
}

void GameBoard::destroyTiles() {
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            delete(tile);
        }
        tileLine.clear(); // should check if useful
    }

}

void GameBoard::destroy() {
    destroyCamera();
    destroyTiles();
}

bool GameBoard::hasWon() {
    return gumNumber == 0;
}

bool GameBoard::hasLost() {
    return player->getLives() == 0;
}

void GameBoard::handleGhosts() {
    for(Ghost * ghost : ghosts){
        ghost->move();
    }
}

void GameBoard::handlePortal() {
    for(std::vector<Tile *> tileLine : tiles) {
        for( Tile * tile : tileLine) {
            if(tile->getInitialState() == PORTAL && !player->isOnTile(tile)) {
                tile = *(tile->getNeighbours()[0]);
                player->teleport(tile);
                handleCamera();
                return;
            }
        }
    }
}

void GameBoard::handleCamera() {
    cam2D->follow(*player);
    camFPS->follow(*player);
}

glm::mat4 GameBoard::getCurrentCamMatrix() const {
    return currentCam->getViewMatrix();
}

void GameBoard::setCurrentCam(Camera *currentCam) {
    GameBoard::currentCam = currentCam;
}







