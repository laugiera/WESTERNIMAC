//
// Created by Amel on 29/12/2017.
//

#include <glm/vec2.hpp>
#include "CactusMan.hpp"

CactusMan::CactusMan(Tile *tile) : startingTile (tile), tile(tile), renderModel(nullptr) {
    position = glm::vec2(tile->getCenter().x, tile->getCenter().y);
    rotation = 0;
    score=0;
    lives = 3;
    computeDirectionVectors();
    createRenderModel();
}

CactusMan::~CactusMan(){
    delete renderModel;
}

/**
 * Handle moving Frontward and backward (FPS cam) and Up and Down (2D cam)
 * @param direction
 */
void CactusMan::moveFront(float direction){
    float testDistance = 0.55; // collision distance from wall
    glm::vec2 previousPosition = position; //keep previous position in case the movement is not possible (eg wall)
    if(cam2D){ //player movement is different depending on the camera used
        rotation = (direction>0)?180: 0;
        computeDirectionVectors();
        position += glm::vec2(frontVector.x, frontVector.z) * testDistance; // test movement with collision distance
        direction = glm::abs(direction); // 2D cam : we don't need the signed direction anymore cause we have backward rotation
    } else {
        position += glm::vec2(frontVector.x, frontVector.z) * testDistance * direction; //FPS cam : direction needs to be signed to walk backward
    }
    if(!isOnWalkableTile()){
        position = previousPosition;
    } else {
        // if movement is allowed update the coords using the real speed instead of the testDistance
        position = previousPosition + (glm::vec2(frontVector.x, frontVector.z) * speed * direction);
    }
}

/**
 * Rotates the player to the left, used in FPS Cam mode
 */
void CactusMan::rotateLeft(){
    if(isOnCrossRoad()){ // player has to be on a crossroad to rotate
        rotation += 90;
        computeDirectionVectors();
    }
}

/**
 * Rotates the player to the right, used in FPS Cam mode
 */
void CactusMan::rotateRight() {
    if(isOnCrossRoad()){
        rotation -= 90;
        computeDirectionVectors();
    }
}

/**
 * Handle rotating left and right in FPS mode and moving left and right in 2D mode
 * @param direction
 */
void CactusMan::moveLeft(float direction){
    if(cam2D) {
        //see MoveFront()
        float testDistance = 0.55;
        glm::vec2 previousPosition = position;
        rotation = (direction > 0) ? -90 : 90;
        computeDirectionVectors();
        position += glm::vec2(frontVector.x, frontVector.z) * testDistance;
        if (!isOnWalkableTile()) {
            position = previousPosition;
        } else {
            position = previousPosition + (glm::vec2(frontVector.x, frontVector.z) * speed);
        }
    } else { // if in FPS mode changing direction means rotating then moving front
        if(direction>0){
            rotateLeft();
        } else {
            rotateRight();
        }
    }
}

/**
 * Creates the rendermodel for CactusMan
 */
void CactusMan::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cactus", appFolderPath + "/imacman", "3D2", "cactus");
        renderModel->setModelColor(glm::vec3(0.850, 0.913, 0.788),glm::vec3(1),glm::vec3(1));
        renderModel->setTexture(appFolderPath + "/textures/cactus.jpg");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Updates the RenderModel with the player's coordinates, rotation and scale
 */
void CactusMan::render() {
    if(cam2D){
        renderModel->transform(glm::vec3(position.x, 0, position.y), rotation, glm::vec3(0,1,0), glm::vec3(1));
    }

}

/**
 * Compute the front and left vectors which will be used for player movement and cameras.
 * Has to be called after any rotation
 */
void CactusMan::computeDirectionVectors() {
    float _rotation = glm::radians(rotation);
    frontVector = glm::vec3(glm::cos(0.f)*glm::sin(_rotation),
                              glm::sin(0.f),
                              glm::cos(0.f)*glm::cos(_rotation));
    leftVector = glm::vec3(glm::sin(_rotation+(glm::pi<float>()*0.5)),
                             0,
                             glm::cos(_rotation+(glm::pi<float>()*0.5)));

}

/**
 * Checks if the player is on passed tile
 * @param tile
 * @return
 */
bool CactusMan::isOnTile(const Tile *tile) {
        if(position.x >= tile->getCenter().x -0.5 &&
           position.x <= tile->getCenter().x + 0.5&&
           position.y >= tile->getCenter().y - 0.5 &&
           position.y <= tile->getCenter().y + 0.5 ) {
            return true;
        }
    return false;
}

/**
 * Checks if the player is on a crossroad : Anything is considered a crossroad apart from a 2 way straight line
 * @return
 */
bool CactusMan::isOnCrossRoad() {
    if (tile->getNeighbours().size() == 2 &&
        (*tile->getNeighbours()[0])->isAligned(*tile->getNeighbours()[1])) {
        return false;
    }
    else if (glm::distance(position, tile->getCenter()) > 0.2){
        return false;
    }
    return true;
}

/**
 * Checks if the player is on a walkable tile
 * @return
 */
bool CactusMan::isOnWalkableTile() {
    if(isOnTile(tile)){ // if still on he same tile it is walkable
        return true;
    } else {
        //checks for each neighbouring walkable tile if the player is on it. If not then the player is in a wall
        for(int i = 0; i<tile->getNeighbours().size(); i++){
            if(isOnTile(*(tile->getNeighbours().at(i)))){
                Tile ** newTile = tile->getNeighbours().at(i);
                tile = *newTile; // update the player's tile
                return true;
            }
        }
        return false;
    }
}

/**
 * Retrieves a tile's type, updates the player's stats accordingly and returns the type;
 * @return
 */
int CactusMan::dropTile() {
    if(glm::distance(position, tile->getCenter()) < 0.3){
        int type = tile->drop();
        switch (type) {
            case GUM :
                score += 10;
                break;
            case SUPERGUM :
                //score += 50;
                break;
            case FRUIT :
                score += 500;
                break;
            default:
                break;
        }
        return type;
    }
    return EMPTY;
}

/**
 * Test ghosts collisions, updates the player's stats and eventually updates the ghosts state
 * @param ghosts
 */
void CactusMan::testGhostEncounter(std::vector<Ghost *> &ghosts) {
    for(Ghost * ghost : ghosts){
        if (glm::distance(position, ghost->getPosition()) < 0.5) {
            int what = ghost->collide();
            switch (what) {
                case -1: // default state for the ghosts
                    //player looses a life and everyone gets back to its starting position
                    lives --;
                    for(Ghost * ghost : ghosts){
                        ghost->returnToStartPos();
                    }
                    tile = startingTile;
                    position = tile->getCenter();
                    break;
                default: // any other number -> number of points gained by the player -> it means the ghosts are in ScaredState and the player can eat them
                    score += what;
                    ghost->returnToStartPos(); //only eaten ghost gets back to starting position
                    for(Ghost * ghost : ghosts){
                        ghost->setScaredState(); // ScaredState needs to be updated for all the ghosts to double the number of points
                    }
                    break;
            }
        }
    }

}

/**
 * Change player position to passed tile's center and updates the tile attribute
 * @param _tile
 */
void CactusMan::teleport(Tile *_tile) {
    tile = _tile;
    position = tile->getCenter();
}


void CactusMan::setCam2D(bool cam2D) {
    CactusMan::cam2D = cam2D;
}

float CactusMan::getRotation() const {
    return rotation;
}
const glm::vec3 &CactusMan::getFrontVector() const {
    return frontVector;
}

const glm::vec3 &CactusMan::getLeftVector() const {
    return leftVector;
}
