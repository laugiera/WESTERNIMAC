//
// Created by Lou Landry on 29/12/2017.
//

#include "Tile.hpp"
#include "Wall.hpp"
#include "Elevator.hpp"

Tile::Tile(int id, const glm::vec2 &center, const std::vector<Tile **> &neighbours, const int &initiateState)
        : id(id), center(center),
          neighbours(neighbours), initialState(initiateState)
{
    element = nullptr;
    renderModel = nullptr;
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
    delete element; //bug
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
 * Return the tile's type;
 * @param player
 */
int Tile::drop() {
    int type;
    if(element){
        type = element->drop();
    } else type = EMPTY;
    if(type == GUM || type == SUPERGUM || type == FRUIT){
        changeElement(EMPTY);
    }
    return type;
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

const std::vector<Tile **> &Tile::getNeighbours() const {
    return neighbours;
}

void Tile::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        if(!renderModel){
            renderModel = new RenderModel(appFolderPath + "/models/cube", appFolderPath + "/imacman", "3D2", "directionallight");
            OpenGlManager::getInstance().addRenderModel(renderModel);
        }
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

bool Tile::isAligned(Tile *tile) {
    if(tile->getCenter().x == center.x || tile->getCenter().y == center.y ) {
        return true;
    } else return false;
}

