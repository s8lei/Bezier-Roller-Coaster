//
//  BezierCurve.cpp
//  cse167proj4
//
//  Created by LSQ on 11/11/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#include <stdio.h>
#include "BezierCurve.h"
#include "Window.h"

glm::mat4 BezierCurve::B = glm::mat4(-1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0);
std::vector<int> BezierCurve::pindices = {0, 1, 2, 3};
BezierCurve::BezierCurve(int index)
{
    this->index = index;
}
void BezierCurve::draw(glm::mat4 P)
{
    render(P);
    Window::setIsCP(true);
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, indices.size()*2, GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
    
    Window::setIsCP(true);
    glBindVertexArray(pvao);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(13);
    glDrawElements(GL_POINTS, pindices.size(), GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
    
}

void BezierCurve::render(glm::mat4 P)
{
    cps.clear();
    cps.push_back(glm::vec3(P[0]));
    cps.push_back(glm::vec3(P[1]));
    cps.push_back(glm::vec3(P[2]));
    cps.push_back(glm::vec3(P[3]));

    this->P = P;
    points.clear();
    for ( int i = 0; i <= 150; i++)
    {
        float t = float(i)/150.0f;
        glm::vec3 x = getPoint(t);
        points.push_back(x);
        if ( i != 150)
        indices.push_back(glm::ivec2(i, i+1));
    }
    length = sqrt(glm::dot(points[1]-points[0], points[1]-points[0]));
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbos);
    glGenBuffers(1, &ebo);
     
    // Bind to the VAO.
    glBindVertexArray(vao);

    // Bind to the first VBO. We will use it to store the points.
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(),
        points.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access points through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Bind to the EBO. We will use it to store the indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Pass in the data.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec2) * indices.size(),
        indices.data(), GL_STATIC_DRAW);
     
    // Unbind from the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
    
    
    
    glGenVertexArrays(1, &pvao);
    glGenBuffers(2, pvbos);
    glGenBuffers(1, &pebo);
     
    // Bind to the VAO.
    glBindVertexArray(pvao);

    // Bind to the first VBO. We will use it to store the points.
    glBindBuffer(GL_ARRAY_BUFFER, pvbos[0]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cps.size(),
        cps.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access points through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(),
    colors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    
    // Bind to the EBO. We will use it to store the indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pebo);
    // Pass in the data.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * pindices.size(),
        pindices.data(), GL_STATIC_DRAW);
     
    // Unbind from the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void BezierCurve::update()
{
    
}

glm::vec3 BezierCurve::getPoint(GLfloat t)
{
    glm::vec4 tvec = glm::vec4(glm::pow(t, 3.0f), glm::pow(t, 2.0f), t, 1.0f);
    glm::vec3 x = glm::vec3(P * B * tvec);
    return x;
}

void BezierCurve::setColor(std::vector<glm::vec3> colors)
{
    this->colors = colors;
//    if (Window::manipulate)
//    {
//        std::cout<<index<<std::endl<<colors.size()<<std::endl;
//        for (int i = 0; i < 4; i ++)
//        {
//            std::cout<<colors[i].x<<colors[i].y<<colors[i].z<<std::endl;
//        }
//    }
}
