//
// Created by Amel on 29/12/2017.
//

#ifndef IMACMAN_CACTUSMAN_HPP
#define IMACMAN_CACTUSMAN_HPP


class CactusMan {

public:
    CactusMan();
    ~CactusMan();
    void moveFront(float step);
    void moveLeft();
    void collision();

private :
    float pos_x, pos_y, pos_z, rot_x, rot_y, rot_z;
    int score, lives;
    bool canMove; // false when he is facing a wall

};


#endif //IMACMAN_CACTUSMAN_HPP
