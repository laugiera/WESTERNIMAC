//
// Created by Lou Landry on 29/12/2017.
//

#include "Tile.hpp"
#include "Wall.hpp"
#include "Portal.hpp"

Tile::Tile(int id, const glm::vec2 &center, const std::vector<Tile **> &neighbours, const int &initiateState)
        : id(id), center(center),
          neighbours(neighbours), initialState(initiateState)
{
    element = nullptr;
    renderModel = nullptr;
    changeElement(initiateState);
}


/**
 * Update the Tile's owned game element
 * @param elementType enum const representing a gameElement
 */
void Tile::changeElement(int elementType) {
    delete element;
    if (elementType == WALL){
        element = new Wall();
    } else if(elementType == GUM){
        element = new Gum();
    } else if(elementType == SUPERGUM){
        element = new SuperGum();
    } else if(elementType == FRUIT){
        element = new Fruit();
    } else if(elementType == PORTAL){
        element = new Portal();
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
    renderModel->transform(glm::vec3(center.x, 0, center.y), 0, glm::vec3(0,1,0), glm::vec3(1));
    if(element){
        element->render(center);
    }

}

/**
 * Return the tile's type;
 * @param player
 */
int Tile::drop() {
    int type = getType();
    if(type == GUM || type == SUPERGUM || type == FRUIT){
        changeElement(EMPTY);
    }
    return type;
}

int Tile::getType(){
    if(element){
        return element->drop();
    } else return EMPTY;
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
        renderModel = new RenderModel(appFolderPath + "/models/tile", appFolderPath + "/imacman", "3D2", "texture");
        renderModel->setModelColor(glm::vec3(0.933, 0.862, 0.549),glm::vec3(1),glm::vec3(1));
        renderModel->setTexture(appFolderPath + "/textures/tile.jpg");

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
    delete element;
    if(renderModel){
        OpenGlManager::getInstance().removeRenderModel(renderModel);
        delete renderModel;
    }

}

bool Tile::isAligned(Tile *tile) {
    if(tile->getCenter().x == center.x || tile->getCenter().y == center.y ) {
        return true;
    } else return false;
}

std::ostream &operator<<(std::ostream &stream, Tile &tile) {
    std::string type;
    if(tile.getType()==EMPTY){
        type = "EMPTY";
    } else if(tile.getType()== WALL){
        type = "WALL";
    } else if(tile.getType()== GUM){
        type = "GUM";
    } else if(tile.getType()== SUPERGUM){
        type = "SUPERGUM";
    } else if(tile.getType()== FRUIT){
        type = "FRUIT";
    } else if(tile.getType()== PORTAL){
        type = "PORTAL";
    }
    stream << type;
    return stream;

}
