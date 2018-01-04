//
// Created by Lou Landry on 30/12/2017.
//

#ifndef IMACMAN_LOADER_HPP
#define IMACMAN_LOADER_HPP

#include <vector>
#include <string>
#include <fstream>
#include "Tile.hpp"
#include "Tools.hpp"

class BoardLoader {
public:
    BoardLoader() = default;

    std::vector<std::vector<Tile*>> createTileMatrix(std::string filePath);

private:
    std::vector<std::string> load(std::string filePath);

    std::vector<std::vector<std::string>> loadDataMatrix(std::string filePath);


    Tile* createTile(std::string type, int id, glm::vec2 center, std::vector<Tile **> neighbours);

    std::vector<Tile **>
    findNeighbours(int i, int j, std::vector<std::vector<Tile*>> &tiles, std::vector<std::vector<std::string>> &dataMatrix);
};


#endif //IMACMAN_LOADER_HPP
