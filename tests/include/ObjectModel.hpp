//
// Created by natshez on 28/12/2017.
//

#ifndef IMACMAN_OBJECTMODEL_H
#define IMACMAN_OBJECTMODEL_H
#include <glimac/Geometry.hpp>
#include <glimac/common.hpp>

#include "Print.hpp"


class ObjectModel {
public:
    ObjectModel(const std::string &_objPath);
    ~ObjectModel();

    const std::vector<glimac::ShapeVertex> &getVertices_vector() const;

    void setVertices_vector(const std::vector<glimac::ShapeVertex> &vertices_vector);

    const std::vector<uint32_t> &getIndices_vector() const;

    void setIndices_vector(const std::vector<uint32_t> &indices_vector);

    std::vector<float> getShininess() const;

    const std::vector<glm::vec3>  &getKs() const;

    const std::vector<glm::vec3>  &getKd() const;

    const glm::vec3 &getColor() const;

private:
    glimac::Geometry object;
    std::string objPath;
    std::string mtlPath;
    std::vector<glimac::ShapeVertex> vertices_vector;
    std::vector<uint32_t> indices_vector;
//    std::vector<float> shininess;
//    std::vector<glm::vec3> ks;
//    std::vector<glm::vec3> kd;
    glm::vec3 color;


};


#endif //IMACMAN_OBJECTMODEL_H
