//
//  Transform.cpp
//  cse167proj3
//
//  Created by LSQ on 10/24/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#include <stdio.h>
#include "Transform.h"
#include <iostream>
#include "Window.h"

Transform::Transform(int index) {
    this->index = index;
}

void Transform::addChild(Node* child) {
    children.push_back(child);
}

void Transform::draw(glm::mat4 C) {
    glm::mat4 M_new = C*M;
    for (auto child : children) {
        child->draw(M_new);
//        std::cout<<"transform M is "<<std::endl<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<" "<<M[0][3]<<std::endl<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<" "<<M[1][3]<<std::endl<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<" "<<M[2][3]<<std::endl<<M[3][0]<<" "<<M[3][1]<<" "<<M[3][2]<<" "<<M[3][3];
    }
}

void Transform::update() {
    if (angle>=0.5f) {
        walkDirection = false;
        //std::cout<<"backward"<<std::endl;
    }
    else if (angle<=-0.5f) {
        walkDirection = true;
        //std::cout<<"forward"<<std::endl;
    }
    if (walkDirection) {
        angle+=0.005f;
        //tlleg->rotate(glm::radians(0.1f), glm::vec3(0, 1, 0));
        //tlleg->translate(-glm::vec3(lleg->M*glm::vec4(lleg->objCenter, 1.0f)));
        switch (index) {
            case 0:
                rotate(0.005f, glm::vec3(0, 0, 0.001));
                break;
            case 1:
                rotate(0.005f, glm::vec3(0, 0, -0.001));
            case 2:
                rotate(0.005f, glm::vec3(0.001, 0, 0));
                break;
            case 3:
                rotate(0.005f, glm::vec3(-0.001, 0, 0));
            default:
                break;
        }
//            tlleg->rotate(0.005f, glm::vec3(0.001, 0, 0));
//            tlarm->rotate(0.005f, glm::vec3(0, 0, 0.001));
//            //tlleg->translate(glm::vec3(lleg->M*glm::vec4(lleg->objCenter, 1.0f)));
//    //        trleg->translate(-glm::vec3(rleg->M*glm::vec4(lleg->objCenter, 1.0f)));
//            trleg->rotate(0.005f, glm::vec3(-0.001, 0, 0));
//            trarm->rotate(0.005f, glm::vec3(0, 0, -0.001));
//        trleg->translate(glm::vec3(rleg->M*glm::vec4(lleg->objCenter, 1.0f)));
    }
    else {
        angle-=0.005f;
        switch (index) {
            case 0:
                rotate(0.005f, glm::vec3(0, 0, -0.001));
                break;
            case 1:
                rotate(0.005f, glm::vec3(0, 0, 0.001));
            case 2:
                rotate(0.005f, glm::vec3(-0.001, 0, 0));
                break;
            case 3:
                rotate(0.005f, glm::vec3(0.001, 0, 0));
            default:
                break;
        }
        //tlleg->translate(-glm::vec3(lleg->M*glm::vec4(lleg->objCenter, 1.0f)));
//            tlleg->rotate(0.005f, glm::vec3(-0.001, 0, 0));
//            tlarm->rotate(0.005f, glm::vec3(0, 0, -0.001));
//            //tlleg->translate(glm::vec3(lleg->M*glm::vec4(lleg->objCenter, 1.0f)));
//    //        trleg->translate(-glm::vec3(rleg->M*glm::vec4(lleg->objCenter, 1.0f)));
//            trleg->rotate(0.005f, glm::vec3(0.001, 0, 0));
//            trarm->rotate(0.005f, glm::vec3(0, 0, 0.001));
//        trleg->translate(glm::vec3(rleg->M*glm::vec4(lleg->objCenter, 1.0f)));
    }
}

void Transform::scale(float scale)
{
    M = glm::scale(glm::vec3(scale, scale, scale)) * M;
}

void Transform::translate(glm::vec3 displacement)
{
    M = glm::translate(displacement) * M;
}

void Transform::rotate(float angle, glm::vec3 axis)
{
    M = glm::rotate(angle, axis) * M;
}
