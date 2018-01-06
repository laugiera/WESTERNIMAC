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
    camFPS->follow(player);
    cam2D->follow(player);


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
        player = CactusMan(startingTile);
    }
}


void GameBoard::handleCollisions() {
    int type = player.dropTile();
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
    }
    player.testGhostEncounter(ghosts);

    /* use to redo walls
        std::vector<Tile *> neighbours= tile.getNeighbours();

    for(unsigned int i;i<neighbours.size();i++){
        //check the square to avoid using roots
        if (SquareDistance(player.getPosition(),neighbours[i]->getCenter())< 0.25){ //distance less than (0.5)²
            tile=*(neighbours[i]);
            break;
        }
    }

    else if(tile.type() == ELEVATOR){
        //load upstairs gameboard

    } else if(tile.type() == EMPTY){
        //do nothing
    }
    else {

        // need to also check if dude is out of the map
        // freeze the y if y>board.height and freeze x if x>board.width
    }
     */
}

void GameBoard::render(glimac::SDLWindowManager & windowManager) {
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            tile->render();
        }
    }
    player.render();
    for (Ghost* & ghost : ghosts){
        ghost->render();
    }
    glm::mat4 viewMatrix = currentCam->getViewMatrix();
    OpenGlManager::getInstance().drawAll(windowManager,viewMatrix);
}

void GameBoard::changeCamera() {
    if (currentCam == cam2D) {
        currentCam = camFPS;
        player.setCam2D(false);
    }
    else if (currentCam == camFPS) {
        currentCam = cam2D;
        player.setCam2D(true);
    }
}

GameBoard::~GameBoard() {

}

void GameBoard::moveUp() {
    player.moveFront(0.2);
    camFPS->follow(player);
    cam2D->follow(player);


}

void GameBoard::moveDown() {
    player.moveFront(-0.2);
    camFPS->follow(player);
    cam2D->follow(player);
}

void GameBoard::moveLeft() {
    player.moveLeft(0.2);
    camFPS->follow(player);
    cam2D->follow(player);
}

void GameBoard::moveRight() {
    player.moveLeft(-0.2);
    camFPS->follow(player);
    cam2D->follow(player);

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
    return player.getLives() == 0;
}

void GameBoard::handleGhosts() {
    for(Ghost * ghost : ghosts){
        ghost->move();
    }
}







