#ifndef _WINDOW_H_
#define _WINDOW_H_

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <array>

#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"
#include "shader.h"
#include "Node.h"
#include "Transform.h"
#include "Geometry.h"
#include "BoundSphere.h"
#include "Track.h"
#include "BezierCurve.h"

class Window
{
public:
    static int width;
    static int height;
    static const char* windowTitle;
    static PointCloud * bunnyPoints;
    static PointCloud * bearPoints;
    static PointCloud * dragonPoints;
    static PointCloud * lightPoints;
    static PointCloud * spotPoints;
    static Cube * skybox;
    static Geometry * metalSphere;
    static Track * track;
    
    static Transform * cameraView;
    static Transform * robot;
    static BoundSphere * sphere;
    static Geometry * body;
    static Transform * thead;
    static Geometry * head;
    static Transform * tleye;
    static Transform * treye;
    static Geometry * robeye;
    static Transform * tlarm;
    static Transform * trarm;
    static Geometry * limb;
    static Transform * tlleg;
    static Transform * trleg;
    
    static Transform * translations[100];
    static Transform * quarters[4];
    static BoundSphere * spheres[4];
    static Object * currentObj;
    static float fov;
    static float nearDist;
    static float farDist;
    static glm::vec3 nc;
    static glm::vec3 fc;
    static glm::vec3 rightNormal;
    static glm::vec3 leftNormal;
    static glm::vec3 upNormal;
    static glm::vec3 bottomNormal;
    static std::vector<glm::vec3> planeN;
    static std::vector<float> planeD;
    static int visibleCount;
    static int prevCount;
    static int cullCount;
    static bool debug;
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::vec3 eye, center, up, direction;
    static GLuint program, projectionLoc, viewLoc, modelLoc, colorLoc, cameraPosLoc, skyLoc, isCPLoc, skyboxShader, skyProjectionLoc, skyViewLoc, skyboxLoc, skycolorLoc;
    static bool colorMode, isPtLight, isDirLight, isSptLight;
    static int keyMode;
    static bool rotate;
    static glm::vec3 lastPos;
    static glm::vec3 curPos;
    static glm::vec2 last;
    static glm::vec2 cur;
    static float yaw;
    static float pitch;
    static float legAngle;
    static bool walkDirection;
    
    static int cpIndex;
    static int prevCpIdx;
    static bool manipulate;
    static bool pause;
    static bool rider;
    static glm::vec3 prevEye;
    static glm::vec3 prevDir;
    static bool physics;
    
    static bool initializeProgram();
    static bool initializeObjects();
    static void cleanUp();
    static GLFWwindow* createWindow(int width, int height);
    static void resizeCallback(GLFWwindow* window, int width, int height);
    static void idleCallback();
    static void displayCallback(GLFWwindow*);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static glm::vec3 trackBallMapping(glm::vec2 point);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void setModelView(glm::mat4 M);
    static void setColor(glm::vec3 color);
    static void calcFrustum();
    static void setIsCP(bool iscp);
};

#endif

