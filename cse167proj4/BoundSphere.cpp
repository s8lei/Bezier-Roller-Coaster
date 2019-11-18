//
//  BoundSphere.cpp
//  cse167proj3
//
//  Created by LSQ on 10/30/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#include "BoundSphere.h"
#include "Window.h"

BoundSphere::BoundSphere(std::string filename, GLfloat radius, int index) : Geometry(filename, radius)
{
    this->index = index;
    this->radius = radius;
}
void BoundSphere::addChild(Node* child) {
    children.push_back(child);
}
void BoundSphere::draw(glm::mat4 C)
{
//    setModelMatrix(C);
//    setColor();
//    if (ifRender)
//    {
//        render();
//    }
//    std::cout<<"currentModelC is "<<std::endl<<C[0][0]<<" "<<C[0][1]<<" "<<C[0][2]<<" "<<C[0][3]<<std::endl<<C[1][0]<<" "<<C[1][1]<<" "<<C[1][2]<<" "<<C[1][3]<<std::endl<<C[2][0]<<" "<<C[2][1]<<" "<<C[2][2]<<" "<<C[2][3]<<std::endl<<C[3][0]<<" "<<C[3][1]<<" "<<C[3][2]<<" "<<C[3][3]<<std::endl;
    bool visible = cull? checkVisibility(C*M): true;
    glm::mat4 M_new = C;
    if (visible)
    {
        setModelMatrix(C*M);
        glm::vec3 qColor[2] = {glm::vec3(0, 76, 153), glm::vec3(255, 204, 204)};
        color = qColor[index];
        //color = qColor[index];
        Window::setColor(color);
        if (ifRender)
        {
            
            glBindVertexArray(Geometry::vao);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, Geometry::indices.size()*3, GL_UNSIGNED_INT, 0);
            // Unbind from the VAO.
            glBindVertexArray(0);
        }
        if (children.size()>0 && index == 1)
            Window::visibleCount ++;
        for (auto child : children) {
            child->draw(M_new);
        }
    }
    else if ( cull )
        if (index == 0)
            Window::cullCount ++;
}

bool BoundSphere::checkVisibility(glm::mat4 C)
{
    float dist;
    int count = 0;
    int count1 = 0;
    glm::vec3 center = glm::vec3(glm::inverse(Window::view) * C * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    
//    std::cout<< "center is " << center.x <<" "<< center.y <<" "<< center.z << std::endl;
    for ( int i = 0; i<6; i++ )
    {
        dist = glm::dot(center, Window::planeN[i]) - Window::planeD[i];
        if (dist<-radius)
        {
            count++;
        }
        if (dist<=0 && dist>=-radius)
            count1 ++;
    }
    if (count > 0 && count1==0)
        return false;
    return true;
}

void BoundSphere::update()
{
    
}
