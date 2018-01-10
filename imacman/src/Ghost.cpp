//
// Created by Amel on 1/1/2018.
//

#include "Ghost.hpp"


Ghost::Ghost(Tile *tile, int baseState) : startingTile(tile), tile(tile), baseState(baseState) {
    state = new WaitingState(baseState*100);
    renderModel = nullptr;
    position = tile->getCenter();
    createRenderModel();
}

Ghost::Ghost(){}

Ghost::~Ghost(){
    delete renderModel;
    delete state;
}

void Ghost::move() {
    state->move(position, tile);
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



/* given adjacency matrix adj, finds shortest path from A to B
    A, id of the tile A
    B, id of the tile B
    neighbours, vector of neighbours tiles id */

int Dijkstra(int A, int B, std::vector<std::vector<int>> neighbours) {
    int n = neighbours.size();
    std::vector<int> dist(n);
    std::vector<bool> vis(n);

    for(int i = 0; i < n; ++i) {
        dist[i] = -1; //initially put all distances to infinity
    }
    dist[A] = 0;

    for(int i = 0; i < n; ++i) {
        int cur = -1;
        for(int j = 0; j < n; ++j) {
            if (vis[j]) continue;
            if (cur == -1 || dist[j] < dist[cur]) {
                cur = j;
            }
        }

        vis[cur] = true;
        for(int j = 0; j < n; ++j) {
            int path = dist[cur] + neighbours[cur][j];
            if (path < dist[j]) {
                dist[j] = path;
            }
        }
    }

    //return dist[B]; //return shortest distances but we want the node
    return vis[1]; //returns the first visited node that leaded to the shortest way
}