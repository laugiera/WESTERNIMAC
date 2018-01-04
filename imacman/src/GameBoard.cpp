//
// Created by Lou Landry on 30/12/2017.
//

#include "GameBoard.hpp"
#include "OpenGlManager.hpp"

GameBoard::GameBoard(const std::string &boardPath) : boardPath(boardPath),
                                                     cam2D(new Camera2D()),
                                                     camFPS(new CameraFPS()){
    currentCam = camFPS;
    try {
        loadBoard();
        createGhosts();
        createCactusman();
    } catch (std::runtime_error &e){
        std::string message("GameBoard has not been properly initialized : ");
        message += e.what();
        throw std::runtime_error(message);
    }


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
    for (std::vector<Tile>& tileLine: tiles) {
        for(Tile & tile: tileLine ){
            if(tile.getInitialState() == GHOST){
                startingTiles.push_back(&tile);
            }
        }
    }
    if(startingTiles.size() < 4){
        throw std::runtime_error("No starting position has been set for the ghosts");
    } else {
        ghosts.push_back(new BlinkyGhost(startingTiles[0])); // change for Blinky
        ghosts.push_back(new PinkyGhost(startingTiles[1])); // change for Pinky
        ghosts.push_back(new InkyGhost(startingTiles[2])); // change for Inky
        ghosts.push_back(new ClydeGhost(startingTiles[3])); // change for Clide
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
    for (auto& tileLine: tiles) {
        for(auto & tile: tileLine ){
            if(tile.getInitialState() == PACMAN){
                startingTile = &tile;
            }
        }
    }
    if(!startingTile){
        throw std::runtime_error("No starting position has been set for Cactusman");
    } else {
        player = CactusMan(startingTile);
    }
}

float  SquareDistance(glm::vec2 v1, glm::vec2 v2){ //check the square to avoid using roots

    return pow((v2.x-v2.x),2) - pow((v1.y-v1.y),2);

}
void GameBoard::collision(Tile &tile, CactusMan &player){

    std::vector<Tile *> neighbours= tile.getNeighbours();

    for(unsigned int i;i<neighbours.size();i++){

        if (SquareDistance(player.getPosition(),neighbours[i]->getCenter())< 0.25){ //distance less than (0.5)²
            tile=*(neighbours[i]);
            break;
        }
    }
    if(tile.type() == GUM || tile.type() == SUPERGUM || tile.type() == FRUIT){
        if (SquareDistance(player.getPosition(),tile.getCenter()) < 0.04 ){ //distance less than 0.2
            tile.drop(player);
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
}

void GameBoard::render(glimac::SDLWindowManager & windowManager) {
    for (std::vector<Tile>& tileLine: tiles) {
        for(Tile & tile: tileLine ){
            tile.render();
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
    if (currentCam == cam2D)
        currentCam = camFPS;
    else if (currentCam == camFPS)
        currentCam = cam2D;
}

GameBoard::~GameBoard() {

}

void GameBoard::moveUp() {
    currentCam->moveFront(2.0);
}

void GameBoard::moveDown() {
    currentCam->moveFront(-2.0);
}

void GameBoard::moveLeft() {
    currentCam->moveLeft(2.0);
}

void GameBoard::moveRight() {
    currentCam->moveLeft(-2.0);
}

void GameBoard::zoom() {
    currentCam->moveFront(1);
}

void GameBoard::dezoom() {
    currentCam->moveFront(-1);
}

void GameBoard::destroyCamera() {
    currentCam = nullptr;
    delete(cam2D);
    delete(camFPS);
}







