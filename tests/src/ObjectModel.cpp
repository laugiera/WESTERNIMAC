//
// Created by natshez on 28/12/2017.
//

#include "../include/ObjectModel.hpp"
ObjectModel::ObjectModel(const std::string &_path):objPath(_path+".obj"),mtlPath(_path+".mtl"), object(){
    try{
        object.loadOBJ(objPath,mtlPath,false);
        glimac::ShapeVertex vertices[object.getVertexCount()];
        for (int i = 0; i < object.getVertexCount(); ++i) {
            vertices[i].position = object.getVertexBuffer()[i].m_Position;
            vertices[i].normal = object.getVertexBuffer()[i].m_Normal;
            vertices[i].texCoords = object.getVertexBuffer()[i].m_TexCoords;
        }
        vertices_vector = std::vector<glimac::ShapeVertex>(vertices, vertices+object.getVertexCount());
        indices_vector = std::vector<uint32_t>(object.getIndexBuffer(), object.getIndexBuffer()+object.getIndexCount());
    }catch (std::runtime_error e){
        Print::printErrorMessage(e.what());
    }
}

const std::vector<glimac::ShapeVertex> &ObjectModel::getVertices_vector() const {
    return vertices_vector;
}

void ObjectModel::setVertices_vector(const std::vector<glimac::ShapeVertex> &vertices_vector) {
    ObjectModel::vertices_vector = vertices_vector;
}

const std::vector<uint32_t> &ObjectModel::getIndices_vector() const {
    return indices_vector;
}

void ObjectModel::setIndices_vector(const std::vector<uint32_t> &indices_vector) {
    ObjectModel::indices_vector = indices_vector;
}

