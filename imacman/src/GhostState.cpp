//
// Created by Lou Landry on 06/01/2018.
//

#include "GhostState.hpp"

GhostState::GhostState(int timer, int collisionReturn) : timer(timer), collisionReturn(collisionReturn), speed(0.05) {}

GhostState::~GhostState() {
}

/*****GETTER SETTERS*****/

int GhostState::getTimer() const {
    return timer;
}

int GhostState::getCollisionReturn() const {
    return collisionReturn;
}

void GhostState::countDown() {
    timer --;
}

void GhostState::setSpeed(float speed) {
    GhostState::speed = speed;
}

void GhostState::setCollisionReturn(int value) {
    collisionReturn = value;
}

/**
 * Handles basic random movement for the ghosts
 * @param position reference to the ghost's position
 * @param currentTile reference to the ghost's tile
 */
void GhostState::move(glm::vec2 &position, Tile* & currentTile) {
    //define a random index, respecting the number of possible neighbours
    int randMax = currentTile->getNeighbours().size();
    srand(time(NULL));
    Tile * nextTile = *(currentTile->getNeighbours()[rand()%randMax]); //index designates the neighbouring target tile
    position += (nextTile->getCenter() - position) * speed; //move the ghost in direction of target tile
    if(isOnTile(position, nextTile)){
        currentTile = nextTile; //updates ghost current tile if necessary
    }

}

/**
 * Checks if the ghost is on passed tile
 * @param position reference to the ghost's position
 * @param tile tile to be tested
 * @return
 */
bool GhostState::isOnTile(glm::vec2 &position, const Tile *tile) {
    if(position.x >= tile->getCenter().x -0.5 &&
       position.x <= tile->getCenter().x + 0.5&&
       position.y >= tile->getCenter().y - 0.5 &&
       position.y <= tile->getCenter().y + 0.5 ) {
        return true;
    }
    return false;
}



/* given adjacency matrix adj, finds shortest path from A to B
    A, id of the tile A
    B, id of the tile B
    neighbours, vector of neighbours tiles id */

int GhostState::Dijkstra(int A, int B, std::vector<std::vector<int>> neighbours) {
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


