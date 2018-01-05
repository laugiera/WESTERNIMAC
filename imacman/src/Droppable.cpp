//
// Created by Lou Landry on 31/12/2017.
//

#include "Droppable.hpp"

void Droppable::render(glm::vec2 position) {
    renderModel->transform(glm::vec3(position.x, 0.5, position.y), -40, glm::vec3(1,1,0), glm::vec3(0.8));
}

int Droppable::drop(/*CactusMan &player*/) {


}

/*void Droppable::createRenderModel() {
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/droppable", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(1,0,0),glm::vec3(1),glm::vec3(1));
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}*/
void Fruit::createRenderModel(){
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/riffle", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(0.458, 0.247, 0.082),glm::vec3(1),glm::vec3(1));
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void Gum::createRenderModel(){
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/hat", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(0.458, 0.149, 0.082),glm::vec3(1),glm::vec3(1));
        OpenGlManager::getInstance().addRenderModel(renderModel);
    } catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
    }
}

void SuperGum::createRenderModel(){
    std::string appFolderPath = OpenGlManager::getInstance().getAppFolderPath();
    try {
        renderModel = new RenderModel(appFolderPath + "/models/lamp", appFolderPath + "/imacman", "3D2", "directionallight");
        renderModel->setModelColor(glm::vec3(0.458, 0.082, 0.137),glm::vec3(1),glm::vec3(1));
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