//
//  BezierCurve.h
//  cse167proj4
//
//  Created by LSQ on 11/11/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#ifndef BezierCurve_h
#define BezierCurve_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

#include "Node.h"

class BezierCurve: public Node
{
public:
    std::vector<glm::vec3> points;
    std::vector<glm::ivec2> indices;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> cps;
    static std::vector<int> pindices;
    float length;
    static glm::mat4 B;
    glm::mat4 P;
    int index;
    GLuint vao;
    GLuint vbos[2];
    GLuint ebo;
    GLuint pvao;
    GLuint pvbos[2];
    GLuint pebo;
    BezierCurve(int index);
    void draw(glm::mat4 P);
    void render(glm::mat4 P);
    void update();
    glm::vec3 getPoint(GLfloat t);
    void setColor(std::vector<glm::vec3> colors);
};

#endif /* BezierCurve_h */
