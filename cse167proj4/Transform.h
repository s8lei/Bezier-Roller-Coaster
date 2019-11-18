//
//  Transform.h
//  cse167proj3
//
//  Created by LSQ on 10/24/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <list>

#include "Node.h"

class Transform: public Node
{
public:
    glm::mat4 M = glm::mat4(1.0f);
    std::list<Node*> children;
    int index = -1;
    float angle = 0.0f;
    bool walkDirection = true;
    Transform(int index = -1);
    void addChild(Node* child);
    void draw(glm::mat4 C);
    void update();
    void scale(float scale);
    void translate(glm::vec3 displacement);
    void rotate(float angle, glm::vec3 axis);
};

#endif /* Transform_h */
