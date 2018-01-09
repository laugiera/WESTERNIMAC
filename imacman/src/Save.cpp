//
// Created by Amel on 9/1/2018.
//

#include "Save.h"
Save::Save(){

}

void Save::saveGame(CactusMan &player, std::vector<std::vector<Tile*>> TileMatrix){

    std::string filePath = "/data/saveGame.txt";
    std::ofstream SaveGameFile (filePath.c_str(),std::ios_base::app);

    if (SaveGameFile.is_open())
    {
        SaveGameFile << player.getLives();
        SaveGameFile << "\n";
        SaveGameFile << player.getScore();
        SaveGameFile << "\n";

        for(int i = 0; i<TileMatrix.size(); i++){
            for(int j = 0 ; j < TileMatrix.size(); j++){
                SaveGameFile << TileMatrix[i][j];
            }
        }
        SaveGameFile.close();
    }
    else {
        throw std::runtime_error(filePath + " : File doesn't exist or could not be opened");
    }

}