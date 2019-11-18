//
//  Track.cpp
//  cse167proj4
//
//  Created by LSQ on 11/11/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#include "Track.h"
#include "Window.h"
#include <iostream>

std::vector<glm::vec3> Track::cps;
std::vector<glm::vec3> Track::colors;
Track::Track()
{
//    for (int i = 0; i < 24; i ++)
//    {
//        float theta = rand()%15;
//        float r = rand()%40-20;
    
//        float v0 = r * glm::cos(glm::radians(theta));
//        int v1 = rand()%40-20;
//        float v2 = r * glm::sin(glm::radians(theta));
//        cps.push_back(glm::vec3(v0, (float)v1, v2));
//    }
    cps.push_back(glm::vec3(1.0f, 3.0f, -20.0f));
    
    cps.push_back(glm::vec3(3.0f, 1.0f, -18.0f));
    cps.push_back(glm::vec3(10.0f, 3.0f, -13.0f));
    cps.push_back(glm::vec3(13.0f, 4.0f, -15.0f));
    
    cps.push_back(glm::vec3(16.0f, 5.0f, -17.0f));
    cps.push_back(glm::vec3(17.0f, 3.0f, -10.0f));
    cps.push_back(glm::vec3(19.0f, 2.0f, -3.0f));
    
    cps.push_back(glm::vec3(21.0f, 1.0f, 4.0f));
    cps.push_back(glm::vec3(20.0f, 1.0f, 6.0f));
    cps.push_back(glm::vec3(18.0f, 3.0f, 10.0f));
    
    cps.push_back(glm::vec3(16.0f, 5.0f, 14.0f));
    cps.push_back(glm::vec3(10.0f, 3.0f, 18.0f));
    cps.push_back(glm::vec3(5.0f, 2.0f, 20.0f));
    
    cps.push_back(glm::vec3(0.0f, 1.0f, 22.0f));
    cps.push_back(glm::vec3(-3.0f, 4.0f, 16.0f));
    cps.push_back(glm::vec3(-9.0f, 2.0f, 14.0f));
    
    cps.push_back(glm::vec3(-15.0f, 0.0f, 12.0f));
    cps.push_back(glm::vec3(-18.0f, 2.0f, 7.0f));
    cps.push_back(glm::vec3(-20.0f, 2.0f, 3.0f));
    
    cps.push_back(glm::vec3(-22.0f, 2.0f, -1.0f));
    cps.push_back(glm::vec3(-15.0f, 3.0f, -5.0f));
    cps.push_back(glm::vec3(-14.0f, 4.0f, -10.0f));
    
    cps.push_back(glm::vec3(-13.0f, 5.0f, -15.0f));
    cps.push_back(glm::vec3(-1.0f, 5.0f, -22.0f));
    for (int i = 0; i < 24; i ++)
    {
        colors.push_back(((i % 3) == 0? glm::vec3(1.0f, 0.0f, 0.0f): glm::vec3(0.0f, 1.0f, 0.0f)));
    }
}
void Track::draw(glm::mat4 C) {
    drawCH();
    glm::mat4 P;
    std::vector<glm::vec3> cpColors;
    for (auto curve : curves) {
        for (int i = 0; i < 4; i ++)
        {
            int index = curve->index;
            P[i] = glm::vec4(cps[(index * 3 + i)%24], 1.0f);
            cpColors.push_back(colors[(index * 3 + i)%24]);
        }
        curve->setColor(cpColors);
        cpColors.clear();
        curve->draw(P);
//        std::cout<<"transform M is "<<std::endl<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<" "<<M[0][3]<<std::endl<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<" "<<M[1][3]<<std::endl<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<" "<<M[2][3]<<std::endl<<M[3][0]<<" "<<M[3][1]<<" "<<M[3][2]<<" "<<M[3][3];
    }
}

void Track::update() {
}

void Track::addCurves(BezierCurve * curve)
{
    curves.push_back(curve);
}

void Track::drawCH()
{
    for (int i = 1; i < 9; i++)
    {
        GLuint vao;
        GLuint vbos[2];
        GLuint ebo;
        std::vector<glm::vec3> points = {cps[3*i-1], cps[(3*i)%24], cps[(3*i+1)%24]};
        std::vector<glm::ivec2> indices = {glm::ivec2(0, 1), glm::ivec2(1, 2)};
        std::vector<glm::vec3> chColors = {glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)};
        
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
        
        glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * chColors.size(),
        chColors.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        
        
        // Bind to the EBO. We will use it to store the indices.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        // Pass in the data.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec2) * indices.size(),
            indices.data(), GL_STATIC_DRAW);
         
        // Unbind from the VBO.
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Unbind from the VAO.
        glBindVertexArray(0);

        Window::setIsCP(true);
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, indices.size()*2, GL_UNSIGNED_INT, 0);
        // Unbind from the VAO.
        glBindVertexArray(0);
    }
}

void Track::updateCP(int index, glm::vec3 offset)
{
    cps[index] += offset;
    switch (index % 3) {
        case 0:
        {
            cps[index + 1] += offset;
            if (index == 0)
                cps[23] += offset;
            else
                cps[index-1] += offset;
            break;
        }
        case 1:
        {
            if (index == 1)
                cps[23] -= offset;
            else
                cps[index - 2] -= offset;
            break;
        }
        case 2:
        {
            if (index == 23)
                cps[1] -= offset;
            else
                cps[index + 2] -= offset;
            break;
        }
        default:
            break;
    }
        
}

void Track::highlight(int index, int prevIdx)
{
    std::cout<<"index is "<<index<<std::endl<<"prevIndex is "<<prevIdx<<std::endl;
    if (index >= 0)
        colors[index] = glm::vec3(255.0f,215.0f,0.0f);
    if (prevIdx >= 0)
        colors[prevIdx] = ((prevIdx % 3) == 0 ? glm::vec3(1.0f, 0.0f, 0.0f): glm::vec3(0.0f, 1.0f, 0.0f));
//    for (int i = 0; i < 24; i ++)
//    {
//        std::cout<<colors[i].x<<colors[i].y<<colors[i].z<<std::endl;
//    }
}
//void Track::scale(float scale)
//{
//    M = glm::scale(glm::vec3(scale, scale, scale)) * M;
//}
//
//void Track::translate(glm::vec3 displacement)
//{
//    M = glm::translate(displacement) * M;
//}
//
//void Track::rotate(float angle, glm::vec3 axis)
//{
//    M = glm::rotate(angle, axis) * M;
//}
