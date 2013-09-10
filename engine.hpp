#ifndef ENGINE_HPP
#define ENGINE_HPP


#ifdef __linux__
*#include <GL/gl.h>
#include <GL/glu.h>
#elif __APPLE__
#include <OpenGL/GL.h> //MAC OS STUFF
#include <OpenGL/GLU.h>
#endif



#include <cmath>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

const int screenSize[2] = {640, 480};
const float pi = 3.14159265359;

class engine
{
public:
    
    engine();
    ~engine();
    
    void init();
    void render();
    void event();
    void quit();

    SDL_Surface *Surf_Display;
    bool running;
    
    SDL_Event events;
    
private:
    
    double x, y, z; //translate
    double angleX, angleY, angleZ;
    int xrel, yrel;
    int Xpos, Ypos;
    void drawRect(int start);
};


#endif /* ENGINE_HPP */