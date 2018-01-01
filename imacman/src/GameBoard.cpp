//
// Created by Lou Landry on 30/12/2017.
//

#include "GameBoard.hpp"

GameBoard::GameBoard(const std::string &boardPath) : boardPath(boardPath) {
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
    for (auto& tileLine: tiles) {
        for(auto & tile: tileLine ){
            if(tile.getInitialState() == GHOST){
                startingTiles.push_back(&tile);
            }
        }
    }
    if(startingTiles.size() < 4){
        throw std::runtime_error("No starting position has been set for the ghosts");
    } else {
        ghosts.push_back(new Ghost(startingTiles[0])); // change for Blinky
        ghosts.push_back(new Ghost(startingTiles[1])); // change for Pinky
        ghosts.push_back(new Ghost(startingTiles[2])); // change for Inky
        ghosts.push_back(new Ghost(startingTiles[3])); // change for Clide
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
        //player = CactusMan(startingTile);
    }

}

