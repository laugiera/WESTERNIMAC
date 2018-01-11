//
// Created by Lou Landry on 30/12/2017.
//

#include "GameBoard.hpp"

GameBoard::GameBoard(const std::string &boardPath) : boardPath(boardPath),
                                                     cam2D(new Camera2D()),
                                                     camFPS(new CameraFPS()),
                                                     gumNumber(0),
                                                     tiles(),
                                                     player(nullptr),
                                                     ghosts()
{
    try {
        loadBoard();
        createCharacters();
    } catch (std::runtime_error &e){
        std::string message("GameBoard has not been properly initialized : ");
        message += e.what();
        throw std::runtime_error(message);
    }
    currentCam = camFPS;
    handleCamera();


}

GameBoard::~GameBoard() {
    currentCam = nullptr;
    delete(cam2D);
    delete(camFPS);
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            delete(tile);
        }
        tileLine.clear(); // should check if useful
    }
    for(Ghost * ghost : ghosts){
        delete ghost;
    }
    delete player;
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
 * Creates 4 ghost and the player at their starting position. The starting position has been set in the file
 * Has to be called after loadBoard().
 * Sets the number of Gums in total at the beginning of the game
 * Throws std::runtime_error if no starting position has been found
 */
void GameBoard::createCharacters() {

    std::vector<Tile*> startingTilesGhosts;
    Tile * startingTilePlayer = nullptr;
    for (std::vector<Tile*>& tileLine: tiles) {
        for(Tile * tile: tileLine ){
            switch(tile->getInitialState()){
                case GHOST :
                    startingTilesGhosts.push_back(tile);
                    break;
                case GUM :
                    gumNumber ++; //updates number of gums
                    break;
                case SUPERGUM :
                    gumNumber ++;
                    break;
                case PACMAN :
                    startingTilePlayer = tile;
                    break;
                default:
                    break;
            }
        }
    }
    //creates ghosts
    if(startingTilesGhosts.size() < 4){
        throw std::runtime_error("No starting position has been set for the ghosts");
    } else {
        ghosts.push_back(new Ghost(startingTilesGhosts[0], BLINKY)); // change for Blinky
        ghosts.push_back(new Ghost(startingTilesGhosts[1], PINKY)); // change for Pinky
        ghosts.push_back(new Ghost(startingTilesGhosts[2], INKY)); // change for Inky
        ghosts.push_back(new Ghost(startingTilesGhosts[3], CLYDE)); // change for Clide
    }
    // creates player
    if(!startingTilePlayer){
        throw std::runtime_error("No starting position has been set for Cactusman");
    } else {
        player = new CactusMan(startingTilePlayer);
    }

}

/**
 * Handles Player/GameElement collisions and player/ghost collisions on the board scope
 */
void GameBoard::handleCollisions() {
    int type = player->dropTile(); // the player's dropTile() fct handle the consequences of a drop in the player's scope
    switch (type) {
        case GUM:
            gumNumber --; // updates the total number of gums on the board (player wins when it reaches 0)
            break;
        case SUPERGUM:
            gumNumber --;
            //when player eats a supergum he can now eat ghosts -> achieved through a stated in the ghost object
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
    //player/ghosts collisions
    player->testGhostEncounter(ghosts);
}

/**
 * Call the render methodes of the gameboard's Tiles, Ghosts and Player to update their renderModels
 * then call the OpengkManager's drawAll() method to effectively draw all the elements of the game in the window
 * @param windowManager
 */
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

/**
 * Allows user to switch from one camera mode to the other
 */
void GameBoard::changeCamera() {
    if (currentCam == cam2D) {
        currentCam = camFPS;
        //when player.cam2D is set to false (FPS mode) the player's renderModel is not rendered
        player->setCam2D(false);
    }
    else if (currentCam == camFPS) {
        currentCam = cam2D;
        player->setCam2D(true);
    }
}

/**
 * Set the players's score and lives from a save file
 * @param filePath
 */
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


/*****MOVEMENT METHODES*****/

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


/**
 * Checks if player has won the game
 * @return
 */
bool GameBoard::hasWon() {
    return gumNumber == 0;
}

/**
 * Checks if player has lost the game
 * @return
 */
bool GameBoard::hasLost() {
    return player->getLives() == 0;
}

/**
 * Allows the ghosts to move
 */
void GameBoard::handleGhosts() {
    for(Ghost * ghost : ghosts){
        ghost->move();
    }
}

/**
 * Handle the consequences of a the player using a portal :
 * Teleports the player to the other portal
 */
void GameBoard::handlePortal() {
    //look for the other portal
    for(std::vector<Tile *> tileLine : tiles) {
        for( Tile * tile : tileLine) {
            if(tile->getInitialState() == PORTAL && !player->isOnTile(tile)) {
                //teleports the player on the first neighbouring tile of the portal
                tile = *(tile->getNeighbours()[0]);
                player->teleport(tile);
                handleCamera(); //updates the camera
                return;
            }
        }
    }
}

/**
 * Positions both camera on the player
 */
void GameBoard::handleCamera() {
    cam2D->follow(*player);
    camFPS->follow(*player);
}







