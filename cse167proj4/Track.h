//
//  Track.h
//  cse167proj4
//
//  Created by LSQ on 11/11/19.
//  Copyright © 2019 LSQ. All rights reserved.
//

#ifndef Track_h
#define Track_h
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
#include "BezierCurve.h"

class Track: public Node
{
public:
    std::vector<BezierCurve *> curves;
    static std::vector<glm::vec3> cps;
    static std::vector<glm::vec3> colors;
    Track();
    void draw(glm::mat4 C);
    void update();
    void addCurves(BezierCurve * curve);
    void drawCH();
    void updateCP(int index, glm::vec3 cp);
    void highlight(int index, int prevIdx);
//    void scale(float scale);
//    void translate(glm::vec3 displacement);
//    void rotate(float angle, glm::vec3 axis);
};

#endif /* Track_h */
