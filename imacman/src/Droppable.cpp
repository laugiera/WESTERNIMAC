//
// Created by Lou Landry on 31/12/2017.
//

#include "Droppable.hpp"

void Droppable::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0.5, position.y), 0, glm::vec3(0,1,0), glm::vec3(0.2, 0.15, 0.2));
}

int Droppable::drop(/*CactusMan &player*/) {


}

void Droppable::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/cube", appFolderPath + "/imacman", "3D2", "directionallight");
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

int Fruit::drop(/*CactusMan &player*/){
    return FRUIT;
    //int currentScore=player.getScore();
    //player.setScore(currentScore+500);
}

int Gum::drop(/*CactusMan &player*/){
    return GUM;
    //int currentScore=player.getScore();
    //player.setScore(currentScore+10);
}

int SuperGum::drop(/*CactusMan &player*/){
    return SUPERGUM;
    //int currentScore=player.getScore();
    //player.setScore(currentScore+200);
    //SuperMoodOn=true;
}