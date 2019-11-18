//
//  Geometry.cpp
//  cse167proj3
//
//  Created by LSQ on 10/24/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#include <stdio.h>
#include "Geometry.h"
#include "Window.h"

#include <sstream>
#include <iostream>
#include <fstream>

std::map<std::string, int> Geometry::colorForObj = {{"head_s.obj", 1}, {"eyeball_s.obj", 2}, {"body_s.obj", 3}, {"limb_s.obj", 4}, {"sphere.obj", 5}};
Geometry::Geometry(std::string filename, GLfloat radius) {
    init(filename);
    setRadius(radius);
    findCenter();
    
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(),
    normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
   
    // Bind to the EBO. We will use it to store the indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Pass in the data.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(),
        indices.data(), GL_STATIC_DRAW);
    
    // Unbind from the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void Geometry::setModelMatrix(glm::mat4 C) {
    M = C;
//    std::cout<<"transform M is "<<std::endl<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<" "<<M[0][3]<<std::endl<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<" "<<M[1][3]<<std::endl<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<" "<<M[2][3]<<std::endl<<M[3][0]<<" "<<M[3][1]<<" "<<M[3][2]<<" "<<M[3][3];
    Window::setModelView(M);
}

void Geometry::setColor() {
    glm::vec3 color;
    switch (colorForObj[filename]) {
        case 1:
            color = glm::vec3(0.6f, 1.0f, 0.0f);
            break;
        case 2:
            color = glm::vec3(0.0f, 0.0f, 0.0f);
            break;
        case 3:
            color = glm::vec3(0.0f, 1.0f, 0.0f);
            break;
        case 4:
            color = glm::vec3(0.0f, 1.0f, 0.0f);
            break;
        case 5:
            color = glm::vec3(0.0f, 1.0f, 1.0f);
        default:
            break;
    }
    Window::setColor(color);
}

void Geometry::render() {
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Cube::cubemapTexture);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, indices.size()*3, GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}
void Geometry::draw(glm::mat4 C) {
 //   setModelMatrix(C);
//    setColor();
//    std::cout<<"filename is "<<filename<<std::endl;
    render();
}

void Geometry::init(std::string filename) {
    std::ifstream objFile(filename); // The obj file we are reading.
    this->filename = filename;
    // Check whether the file can be opened.
    if (objFile.is_open())
    {
        std::string line; // A line in the file.

        // Read lines from the file.
        while (std::getline(objFile, line))
        {
            // Turn the line into a string stream for processing.
            std::stringstream ss;
            ss << line;
            
            // Read the first word of the line.
            std::string label;
            ss >> label;

            // If the line is about vertex (starting with a "v").
            if (label == "v")
            {
                // Read the later three float numbers and use them as the
                // coordinates.
                glm::vec3 point;
                ss >> point.x >> point.y >> point.z;

                // Process the point. For example, you can save it to a.
                points.push_back(point);
            }
            if (label == "vn")
            {
                glm::vec3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            if (label == "f")
            {
                glm::ivec3 index;
                std::string ind;
                ss >> ind;
                ind = ind.substr(0, ind.size()/2-1);
                index.x = stoi(ind)-1;
                ss >> ind;
                ind = ind.substr(0, ind.size()/2-1);
                index.y = stoi(ind)-1;
                ss >> ind;
                ind = ind.substr(0, ind.size()/2-1);
                index.z = stoi(ind)-1;
                indices.push_back(index);
            }
        }
    }
    else
    {
        std::cerr << "Can't open the file " << filename << std::endl;
    }

    objFile.close();
}

void Geometry::update() {
    curT = glfwGetTime();
    BezierCurve * curve = track->curves[cvIdx];
    glm::vec3 ls = curve->getPoint((float)(lsIdx+1)/150.0f) - curve->getPoint((float)lsIdx/150.0f);
//    glm::vec3 ls = curve->getPoint((float)(lsIdx+1)) - curve->getPoint((float)lsIdx);
//    std::cout<<"line segment: "<< ls.x <<" "<<ls.y<<" "<<ls.z<<std::endl;
    glm::vec3 dir = glm::normalize(ls);
//    std::cout<<"direction: "<< dir.x <<" "<<dir.y<<" "<<dir.z<<std::endl;
    float deltaDist = velocity * (curT - prevT);
//    std::cout << "time difference is " << curT - prevT << std::endl;
    distance += deltaDist;
    
    if (distance >= sqrt(glm::dot(ls, ls)))
    {
        lsIdx +=1;
        float distTt = distance - sqrt(glm::dot(ls, ls));
//        std::cout<<"lsIdx is "<<lsIdx<<std::endl;
//        std::cout<<"ls to cross"<< (int)(distTt/(curve->length)) <<std::endl;
        if (lsIdx + (int)(distTt/(curve->length))>=150)
        {
            float remain = distTt - (150-lsIdx)*curve->length;
            cvIdx = (cvIdx + 1) % 8;
            curve = track->curves[cvIdx];
            lsIdx = (int)(remain/(curve->length));
            M = glm::translate(curve->getPoint((float)lsIdx/150.0f));
            deltaDist = remain - lsIdx*curve->length;
            distance = remain;
            ls = curve->getPoint((float)(lsIdx+1)/150.0f) - curve->getPoint((float)lsIdx/150.0f);
            dir = glm::normalize(ls);
        }
        else
        {
            int lsc = (int)(distTt/(curve->length));
            deltaDist = distTt - lsc * curve->length;
            lsIdx += lsc;
            M = glm::translate(curve->getPoint((float)lsIdx/150.0f));
            ls = curve->getPoint((float)(lsIdx+1)/150.0f) - curve->getPoint((float)lsIdx/150.0f);
            dir = glm::normalize(ls);
            distance = deltaDist;
        }
    }
    
    glm::vec3 translate = deltaDist * dir;
    //std::cout<<"translate : "<<translate.x <<" "<<translate.y<<" "<<translate.z<<std::endl;
    M = glm::translate(translate) * M;
    prevT = curT;
}

glm::vec3 Geometry::top() {
    float y_max = std::numeric_limits<float>::lowest();
    int index = 0;
    for ( int i = 0; i<points.size(); i++ )
    {
        y_max = fmax(y_max, glm::vec3(M*glm::vec4(points[i], 1.0f)).y);
        index = i;
    }
    return glm::vec3(M*glm::vec4(points[index], 1.0f));
}

void Geometry::findCenter()
{
    float x_min = std::numeric_limits<float>::max();
    float x_max = std::numeric_limits<float>::lowest();
    float y_min = std::numeric_limits<float>::max();
    float y_max = std::numeric_limits<float>::lowest();
    float z_min = std::numeric_limits<float>::max();
    float z_max = std::numeric_limits<float>::lowest();
    for ( int i = 0; i<points.size(); i++ )
    {
        x_min = fmin(x_min, points[i].x);
        x_max = fmax(x_max, points[i].x);
        y_min = fmin(y_min, points[i].y);
        y_max = fmax(y_max, points[i].y);
        z_min = fmin(z_min, points[i].z);
        z_max = fmax(z_max, points[i].z);
        
    }
    
    objCenter.x = (x_max+x_min)/2;
    objCenter.y = (y_max+y_min)/2;
    objCenter.z = (z_max+z_min)/2;
}

void Geometry::setRadius(GLfloat radius)
{
    if (radius > 0.0f) {
        for ( int i = 0; i<points.size(); i++ )
        {
            points[i] *= radius/(sqrt(glm::dot(points[i], points[i])));
        }
    }
}

void Geometry::setTrack(Track *track)
{
    this->track = track;
}

void Geometry::viewFromRider()
{
    Window::eye = glm::vec3(M * glm::vec4(0.0f, 3.0f, 0.0f, 1.0f));
    BezierCurve * curve = track->curves[cvIdx];
    glm::vec3 ls = curve->getPoint((float)(lsIdx+1)/150.0f) - curve->getPoint((float)lsIdx/150.0f);
    Window::direction = ls;
    Window::view = glm::lookAt(Window::eye, Window::eye+Window::direction, Window::up);
}

void Geometry::physicsUpdate()
{
    
}
