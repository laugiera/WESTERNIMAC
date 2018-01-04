//
// Created by natshez on 28/12/2017.
//

#include "ObjectModel.hpp"
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


        ks = glm::vec3(0);
        kd = glm::vec3(0);
        color = glm::vec3(0);
    }catch (std::runtime_error e){
        Print::printErrorMessage(e.what());
    }
}
ObjectModel::~ObjectModel(){
    vertices_vector.clear();
    indices_vector.clear();

}

const glm::vec3 &ObjectModel::getColor() const {
    return color;
}


const glm::vec3 &ObjectModel::getKs() const {
    return ks;
}

const glm::vec3 &ObjectModel::getKd() const {
    return kd;
}

void ObjectModel::setColor(glm::vec3 &_color, glm::vec3 &_kd, glm::vec3 &_ks){
    color = _color;
    ks = _ks;
    kd = _kd;
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

