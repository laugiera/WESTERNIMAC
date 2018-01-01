//
// Created by Amel on 29/12/2017.
//

#ifndef IMACMAN_CACTUSMAN_H
#define IMACMAN_CACTUSMAN_H


class CactusMan {

public:
    CactusMan();
    ~CactusMan();
    void moveFront(float step);
    void moveLeft();

private :
    float pos_x, pos_y, pos_z, rot_x, rot_y, rot_z;

};


#endif //IMACMAN_CACTUSMAN_H
