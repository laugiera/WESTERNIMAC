//
// Created by Lou Landry on 31/12/2017.
//

#include "GameElement.hpp"


GameElement::~GameElement() {
    //removes the model from vector of models to render
    if(renderModel){
        OpenGlManager::getInstance().removeRenderModel(renderModel);
        delete renderModel;
    }
}
