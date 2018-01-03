//
// Created by Lou Landry on 29/12/2017.
//

#include "Tile.hpp"
#include "OpenGlManager.hpp"
#include "Wall.hpp"
#include "Gum.hpp"
#include "SuperGum.hpp"
#include "Fruit.hpp"
#include "Elevator.hpp"

Tile::Tile(int id, const glm::vec2 &center, const std::vector<Tile *> &neighbours, const int &initiateState)
        : id(id), center(center),
          neighbours(neighbours), initialState(initiateState)
{
    changeElement(initiateState);
}


std::ostream &operator<<(std::ostream &stream, Tile &tile) {
    std::string symbol;
    if(tile.initialState == WALL){
        symbol = "=";
    } else if (tile.initialState == GUM){
        symbol = ".";
    } else if (tile.initialState == SUPERGUM){
        symbol = "*";
    }
    stream << symbol;
    return stream;
}


/**
 * Update the Tile's owned game element
 * @param elementType enum const representing a gameElement
 */
void Tile::changeElement(int elementType) {
    if (elementType == WALL){
        element = new Wall();
    } else if(elementType == GUM){
        element = new Gum();
    } else if(elementType == SUPERGUM){
        element = new SuperGum();
    } else if(elementType == FRUIT){
        element = new Fruit();
    } else if(elementType == ELEVATOR){
        element = new Elevator();
    } else {
        element = nullptr;
    }
    createRenderModel();
}


/**
 * Send coordinate information the rendermodel associated to the Tile
 * If the Tile owns a gemeElement triggers the same method for said element
 */
void Tile::render() {
    renderModel->transform(glm::vec3(center.x, 0, center.y), 0, glm::vec3(0,1,0), glm::vec3(1, 0.05, 1));
    if(element){
        element->render(center);
    }

}

/**
 * Applies the effect of a collision to the player
 * Those effects depends on the Tile's owned gameElement which is why element.collide() is called
 * @param player
 */
void Tile::drop(CactusMan &player) {
    element->drop(player);
    if(initialState != WALL){
        changeElement(EMPTY);
    }
}

int Tile::type(){

    return 0; //need to add later
}

int Tile::getInitialState() const {
    return initialState;
}

const glm::vec2 &Tile::getCenter() const {
    return center;
}

const std::vector<Tile *> &Tile::getNeighbours() const {
    return neighbours;
}

void Tile::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube", appFolderPath + "/imacman", "3D2", "directionallight");
        OpenGlManager::getInstance().addRenderModel(renderModel);
        if(element){
            element->createRenderModel();
        }
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }


}


const int &Tile::getId() const {
    return id;
}

Tile::~Tile() {
    /*
    if(renderModel){
        OpenGlManager::getInstance().removeRenderModel(renderModel);
        delete renderModel;
    }
     */
}

