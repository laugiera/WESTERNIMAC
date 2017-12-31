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

/*      ks = object.getM_Materials()[0].m_Ks;
        shininess = object.getM_Materials()[0].m_shininess;
        kd = object.getM_Materials()[0].m_Kd;*/
        color = glm::vec3(1,0,0);
    }catch (std::runtime_error e){
        Print::printErrorMessage(e.what());
    }
}

const glm::vec3 &ObjectModel::getColor() const {
    return color;
}

/*std::vector<float> ObjectModel::getShininess() const {
    return shininess;
}

const std::vector<glm::vec3> &ObjectModel::getKs() const {
    return ks;
}

const std::vector<glm::vec3> &ObjectModel::getKd() const {
    return kd;
}*/

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

