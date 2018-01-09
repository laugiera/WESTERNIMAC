//
// Created by Amel on 1/1/2018.
//

#include "Ghost.hpp"


Ghost::Ghost(Tile *tile, int baseState) : startingTile(tile), tile(tile), baseState(baseState) {
    state = nullptr;
    renderModel = nullptr;
    position = tile->getCenter();
    createRenderModel();
    setBaseState();
}

Ghost::Ghost(){}

Ghost::~Ghost(){
    delete renderModel;
    delete state;
}

void Ghost::move() {
    state->move(position, rotation);
    if(state->getTimer() == 0){
        delete state;
        setBaseState();
    }
}

int Ghost::collide(/*CactusMan &Player*/){
    return state->getCollisionReturn();

}

void Ghost::render() {
    renderModel->transform(glm::vec3(position.x, 0.2, position.y), 0, glm::vec3(0,1,0), glm::vec3(0.5));
}

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

void Ghost::returnToStartPos() {
    tile = startingTile;
    position = tile->getCenter();
}

void Ghost::setScaredState() {
    if(!state || state->getCollisionReturn()==-1){
        delete state;
        state = new ScaredGhostState(400,200);
    } else {
        int timer = state->getTimer();
        int nbPoints = state->getCollisionReturn();
        delete state;
        state = new ScaredGhostState(timer,nbPoints*2);
    }
    state->setColor(renderModel);
}

void Ghost::setBaseState() {
    //delete state; bug why?
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
    }
    state->setColor(renderModel);
}


//returns vector of path from s to d
/*std::vector<Tile *> Ghost::isReachable(Tile s, Tile d, std::vector<std::vector<Tile>> tiles)
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


