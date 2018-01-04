//
// Created by Lou Landry on 08/12/2017.
//

#include "../include/Tools.hpp"
#include <iostream>


/**
 * Take a string representation of a bool and converts it to bool
 * @param s string
 * @return bool or throws std::invalid_argument
 */
bool Tools::boolFromString(std::string s) {
    if (s == "0" || s == "false" || s == "FALSE") {
        return false;
    } else if (s == "1" || s == "true" || s== "TRUE") {
        return true;
    } else {
        throw std::invalid_argument(s + " -> input does not represent a bool");
    }
}

/**
 * Take a string representation of an int and converts it to int
 * @param s string
 * @return string or throws std::invalid_argument
 */
int Tools::intFromString(std::string s) {
    std::regex reg("[0-9]+$");
    if(!std::regex_match(s, reg)){
        throw std::invalid_argument(s+ " -> input does not represent an int");
    }
    return std::stoi(s);
}

/**
 * Puts a string to lower case
 * @param s string
 * @return string
 */
std::string Tools::toLowerCase(const std::string & s) {
    std::string new_string = s;
    std::transform(new_string.begin(), new_string.end(),new_string.begin(), ::tolower);
    return new_string;
}

/**
 * Puts a string to upper case
 * @param s string
 * @return string
 */
std::string Tools::toUpperCase(const std::string &s) {
    std::string new_string = s;
    std::transform(new_string.begin(), new_string.end(),new_string.begin(), ::toupper);
    return new_string;
}

/**
 * Removes all blank characters from a string and puts it to lower case for comparison purposes
 * @param s string
 * @return string
 */
std::string Tools::sanitizeInput(const std::string s) {
    std::string new_string = s;
    std::size_t pos = new_string.find(" ");
    while(pos != std::string::npos) {
        new_string.erase(pos,1);
        pos = new_string.find(" ");
    }
    return toLowerCase(new_string);
}


/**
 * Parse a string using a string as delimitor adn puts all substrings in a vector
 * @param _data string
 * @param delimitor string
 * @return vector<string>
 */
std::vector<std::string> Tools::stringToVector(std::string _data, std::string delimitor) {
    std::vector<std::string> content_vector;
    //put data string in c char *
    char * data = new char [_data.length()+1];
    std::strcpy (data, _data.c_str());
    //tokenize
    char * vector_element = strtok(data, delimitor.c_str());
    while(vector_element != NULL){
        content_vector.push_back(std::string(vector_element)); //push substring in vector
        vector_element = strtok(nullptr, delimitor.c_str());
    }
    return content_vector;
}

std::string Tools::getFolderPath(const std::string & filePath) {
#ifdef _WIN32
    char pathSeparator = '\\';
#else
    char pathSeparator = '/';
#endif
    size_t pos = filePath.find_last_of(pathSeparator);
    return filePath.substr(0, pos); //return substring from beginning to last pathseparator
}

bool Tools::WaitForSeconds(double secondsToWait){

    clock_t startTime = clock(); //Start timer
    double secondsPassed;

    bool wait =true;
    while(wait)
    {
        secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
        if(secondsPassed >= secondsToWait)
        {
            wait = false;
        }
    }
}

float  Tools::SquareDistance(glm::vec2 v1, glm::vec2 v2){ //check the square to avoid using roots
    return pow((v2.x-v2.x),2) - pow((v1.y-v1.y),2);
}
/*
//returns vector of path from s to d
std::vector<Tile *> Tools::isReachable(Tile s, Tile d, std::vector<std::vector<Tile>> tiles)
{
    // Create a path vector for BFS
    std::vector<Tile *> path;

    // Base case
    if (s.getId() == d.getId())
        return path;

    // Mark all the tiles as not visited
    bool *visited = new bool[tiles.size()];
    for (int i = 0; i < tiles.size(); i++)
        visited[i] = false;


    // Mark the current tile as visited and add it to path vector
    visited[s.getId()] = true;
    path.push_back(&s);

    // it will be used to get all adjacent tiles of a tile

    std::vector<Tile *>::iterator i;

    while (!path.empty())
    {
        s = *path.front();

        // Get all adjacent tiles of the tile s
        // If a adjacent has not been visited, then mark it visited
        // and add it to path vector
        for (i == **(s.getNeighbours()).begin(); i != **(s.getNeighbours()).end(); ++i)
        {
            // If this adjacent tile is the destination node, then
            // return the path
            if (**i == d)
                return path;

            // Else, continue to do BFS
            if (!visited[**i])
            {
                visited[**i] = true;
                path.push_back(*i);
            }
        }
    }

    // If BFS is complete without visiting d
    return nullptr;
}

*/





