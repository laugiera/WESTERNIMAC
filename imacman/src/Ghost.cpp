//
// Created by Amel on 1/1/2018.
//

#include "Ghost.hpp"


Ghost::Ghost(Tile *tile, int baseState) : startingTile(tile), tile(tile), baseState(baseState), state(nullptr) {
    state = new WaitingState(baseState*100);
    renderModel = nullptr;
    position = tile->getCenter();
    createRenderModel();
}

Ghost::~Ghost(){
    delete renderModel;
    delete state;
}

/**
 * Handle ghost movement.
 * Dependent on the ghost's state
 */
void Ghost::move() {
    state->move(position, tile);
    //if the current state has a positive timer, state will be changed when this timers falls to 0.
    //Permanent states have a negative timer and don't use the state.countdown() method
    if(state->getTimer() == 0){
        delete state;
        setBaseState();
    }
}

/**
 * Handles consequences of a ghost/player collision
 * @return -1 if the player should loose a life, any other number is the number of points the player wins
 */
int Ghost::collide(){
    return state->getCollisionReturn();

}

/**
 * Transforms the render model for it to be drawn when OpenGLManager::drawAll() is called
 */
void Ghost::render() {
    //color is handled by the state
    renderModel->transform(glm::vec3(position.x, 0.2, position.y), 0, glm::vec3(0,1,0), glm::vec3(0.5));
}

/**
 * Creates the renderModel and adds it to the renderlist of OpenGLManager
 */
void Ghost::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/ghost", appFolderPath + "/imacman", "3D2", "texture");
        renderModel->setTexture(appFolderPath + "/textures/tumbleweed.jpg");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

const glm::vec2 &Ghost::getPosition() const {
    return position;
}

/**
 * Teleports the ghost to its starting position
 */
void Ghost::returnToStartPos() {
    tile = startingTile;
    position = tile->getCenter();
}

/**
 * Updates the state to a ScaredState in which the ghost can be eaten
 * If called while the current state is already a ScaredState doubles the ghost's point value
 */
void Ghost::setScaredState() {
    if(!state || state->getCollisionReturn()==-1){
        delete state;
        state = new ScaredGhostState(400,200); // set Scared State
    } else {
        int nbPoints = state->getCollisionReturn();
        state->setCollisionReturn(nbPoints*2); //double the point value
    }
    state->setColor(renderModel); //updates color of the model according to new state
}

/**
 * Sets one the 4 base state according to the ghost's baseState attribute
 */
void Ghost::setBaseState() {
    //delete state; //-> bugs the game
    switch(baseState) {
        case INKY :
            state = new InkyState();
            break;
        case PINKY :
            state = new PinkyState();
            break;
        case BLINKY :
            state = new BlinkyState();
            break;
        case CLYDE :
            state = new ClydeState();
            break;
        default:
            state = new WaitingState(1000);
    }
    state->setColor(renderModel);
}


