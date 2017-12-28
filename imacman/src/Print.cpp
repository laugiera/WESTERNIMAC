//
// Created by natshez on 08/12/2017.
//

#include "Print.hpp"

void Print::printErrorMessage(std::string error){
    std::cerr<<"ERROR : "<<error<<std::endl;
    std::cout<<"****************************"<<std::endl;
}
void Print::printMessage(std::string message){
    std::cout<<message<<std::endl;
}
