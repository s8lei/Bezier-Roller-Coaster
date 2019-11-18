//
//  BoundSphere.h
//  cse167proj3
//
//  Created by LSQ on 10/30/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#ifndef BoundSphere_h
#define BoundSphere_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Geometry.h"
#include <vector>
#include <string>
#include <list>

class BoundSphere : public Geometry
{
private:
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> indices;
    GLuint vao;
    GLuint vbos[2];
    GLuint ebo;
public:
    BoundSphere(std::string filename, GLfloat radius, int index);
    int index;
    GLfloat radius;
    glm::mat4 M = glm::mat4(1.0f);
    std::list<Node*> children;
    bool colorSet;
    glm::vec3 color;
    int count = -1;
    bool cull = true;
    void draw(glm::mat4 C);
    void addChild(Node* child);
    bool checkVisibility(glm::mat4 C);
    bool ifRender = false;
    void update();
    
};

#endif /* BoundSphere_h */
