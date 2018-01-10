//
// Created by Lou Landry on 30/12/2017.
//

#include "BoardLoader.hpp"

/**
 * Loads the content of a file in a vector of strings, each strings represents a line
 * @param filePath path to the file
 * @return vector of strings each representing a line from the file
 */
std::vector<std::string> BoardLoader::load(std::string filePath) {
    std::ifstream file (filePath);
    std::string line;
    std::vector<std::string> fileContent;
    if(file.is_open()){
        while(std::getline(file, line) && !line.empty() && line!= " "  ){
            fileContent.push_back(line);
        }
        file.close();
    } else {
        throw std::runtime_error(filePath + " : File doesn't exist or could not be opened");
    }
    if(fileContent.empty()){
        throw std::runtime_error("File is empty");
    }
    return fileContent;
}

/**
 * Creates a vector of tiles from a file
 * @param filePath path to the file
 * @return matrix of Tiles
 */
std::vector<std::vector<Tile*>> BoardLoader::createTileMatrix(std::string filePath) {
    std::vector<std::vector<Tile*>> gameBoard;
    float tileSize = 1;
    float offset = tileSize/2;


    try {
        std::vector<std::vector<std::string>> dataMatrix = loadDataMatrix(filePath);
        unsigned int lineNumber = dataMatrix.size();
        unsigned int colNumber = dataMatrix[0].size();
        //fil matrix with default Tiles
        for(int i = 0; i<lineNumber; i++){
            gameBoard.push_back(std::vector<Tile*>(colNumber, new Tile()));
        }
        //creates tile from a character (EMPTY, GUM, SUPERGUM, FRUIT, WALL, GHOST, PACMAN ) and it's position in the matrix
        for(int i = 0; i<lineNumber; i++){
            for(int j = 0 ; j < colNumber; j++){
                std::vector<Tile **> neighbours = findNeighbours(i,j,gameBoard, dataMatrix);
                Tile * t = createTile(dataMatrix[i][j], i*colNumber + j, glm::vec2(offset+float(j)*tileSize, offset+float(i)*tileSize), neighbours);
                gameBoard[i][j] = t;
            }
        }
        return gameBoard;
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Puts data from the file in a matrix
 * @param filePath path to the file
 * @return matrix of strings representing different types of Tiles
 */
std::vector<std::vector<std::string>> BoardLoader::loadDataMatrix(std::string filePath){
    std::vector<std::string> fileContent = load(filePath);
    std::vector<std::vector<std::string>> dataMatrix;
    auto parse = [&dataMatrix](std::string & s){
        std::vector<std::string> line = Tools::stringToVector(s, ";");
        dataMatrix.push_back(line);
    };
    for_each(fileContent.begin(), fileContent.end(), parse);
    return dataMatrix;
}

/**
 * creates a tile from string data indicating what type of element is on the tile
 * @param type : string data
 * @param id : tile id
 * @param center : tile center coordinates on the gameboard
 * @param neighbours : vector of pointers on the walkable tiles adjacent to the tile to be created
 * @return
 */
Tile * BoardLoader::createTile(std::string type, int id, glm::vec2 center, std::vector<Tile **> neighbours){
    if(type == "EMPTY"){
        return new Tile(id, center, neighbours, EMPTY);
    } else if (type == "WALL") {
        return new Tile(id, center, neighbours, WALL);
    } else if (type == "GUM") {
        return new Tile(id, center, neighbours, GUM);
    } else if (type == "SUPERGUM") {
        return new Tile(id, center, neighbours, SUPERGUM);
    } else if (type == "FRUIT") {
        return new Tile(id, center, neighbours, FRUIT);
    } else if (type == "GHOST") {
        return new Tile(id, center, neighbours, GHOST);
    } else if (type == "PACMAN") {
        return new Tile(id, center, neighbours, PACMAN);
    } else if (type == "PORTAL") {
        return new Tile(id, center, neighbours, PORTAL);
    } else throw std::runtime_error("In file : Tile (id:"+ std::to_string(id) +") initial state data empty or incorrect");
}

/**
 * Find walkable neighbours of a tile
 * @param i line index
 * @param j column index
 * @param tiles gameboard matrix
 * @param dataMatrix data matrix from the file
 * @return pointer to the memory space the neighbours will occupy in the gameboard matrix
 */
std::vector<Tile **> BoardLoader::findNeighbours(int i, int j, std::vector<std::vector<Tile*>> & tiles, std::vector<std::vector<std::string>> &dataMatrix ) {
    std::vector<Tile **> neighbours;
    //checks for each lateral neighbour if there is a wall on the tile or not
    //if not add to the neighbours vector
    if(dataMatrix[i][j] != "WALL"){
        if(i-1 >= 0 && dataMatrix[i-1][j] != "WALL"){
            Tile ** t = &tiles[i-1][j];
            neighbours.push_back(t);
        }
        if(i+1 < tiles.size() && dataMatrix[i+1][j] != "WALL"){
            Tile ** t = &tiles[i+1][j];
            neighbours.push_back(t);
        }
        if(j-1 >=0 && dataMatrix[i][j-1] != "WALL"){
            Tile ** t = &tiles[i][j-1];
            neighbours.push_back(t);
        }
        if(j+1 < tiles[i].size() && dataMatrix[i][j+1] != "WALL"){
            Tile ** t = &tiles[i][j+1];
            neighbours.push_back(t);
        }
    }
    return neighbours;
}


