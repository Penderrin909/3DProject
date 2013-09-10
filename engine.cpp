
#include "engine.hpp"

engine::engine()
{
    Surf_Display = NULL;
    running = true;
}

engine::~engine()
{
    
}

void engine::init()
{
    SDL_Init(SDL_INIT_EVERYTHING/*|SDL_INIT_NOPARACHUTE*/);
    
    Surf_Display = SDL_SetVideoMode( screenSize[0], screenSize[1], 32, SDL_OPENGL );
    
    glEnable(GL_DEPTH_TEST);
    
    x = 0.0, y = 0.0, z = 0.0;
    angleX = 0.0, angleY = 0.0, angleZ = 0.0;
    xrel = NULL, yrel = NULL;
    Xpos = NULL, Ypos = NULL;
    
    //SDL_WM_GrabInput(SDL_GRAB_ON);
}

void engine::render()
{
    
    //clears the screen's color and depth (default is black but can change with glClearColor(...))
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //drawing to an area starting at the bottom left, 640 wide, 480 high.
    glViewport(0,0,screenSize[0],screenSize[1]);
    //OpenGL is a state machine. tell it that future commands changing the matrix are to change OpenGL's projection matrix
    glMatrixMode(GL_PROJECTION);
    //Reset the projection matrix
    glLoadIdentity();
    //Multiply a perspective projection matrix into opengls projection matrix
    gluPerspective(45.0, (double)(screenSize[0])/(double)(screenSize[1]), 0.1f, 100.0f);
    //tell it that future commands changing the matric are to change the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    
    //reset the modelview matrix
    glLoadIdentity();
    //multiply opengls modelview matrix with a transform matric that simulates a camera at (0,0,-1) looking towards the location (0,0,0) with up defined to be (0,1,0)
    gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);
    //x,y,z
    
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
    
    //glRotate (a, x, y, z);
    glRotatef(angleX, -1, 0, 0);
    glRotatef(angleY, 0, -1, 0);
    //glRotatef(angleZ, 0, 0, -1);
    
    glTranslatef(x,y,z);
    
    
    for(int i = 0; i<10; i++)
    {
        drawRect(i*4);
    }
    
    //Now we're going to draw some lines to show the cardinal axes.  Every subsequent pair of vertices
    //will be a single line.
    glBegin(GL_LINES);
    //All subsequent vertices will be red.
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f); glVertex3f(1.0f,0.0,0.0);
    //All subsequent vertices will be green.
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f); glVertex3f(0.0f,1.0,0.0);
    //All subsequent vertices will be blue.
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f,0.0f,0.0f); glVertex3f(0.0f,0.0,1.0);
    //Since OpenGL thinks the color is blue now, all subsequent vertices will be blue.  But, we want the
    //triangle above to be white the *next* time we call this function!  So, reset the color to white.
    glColor3f(1.0f,1.0f,1.0f);
    glEnd();
    
    //OpenGL works best double-buffered. SDL automatically sets that up. this will draw what we have just draw to the screen so that we can se it.
    SDL_GL_SwapBuffers();
}

void engine::event()
{//SDL_WM_GrabInput
    
    float speed = .05;
    float zDir = (speed)*(cos(angleX*(pi/180))*cos(angleY*(pi/180)));
    float yDir = (speed)*sin(angleX*(pi/180));
    float xDir = (speed)*sin(angleY*(pi/180))*cos(angleX*(pi/180));
    
    SDL_PumpEvents();
    Uint8 *keyboard_state = SDL_GetKeyState(NULL);
    //SDL_GetMouseState(&Xpos,&Ypos);
    //SDL_GetRelativeMouseState(&xrel,&yrel);
    
    if(keyboard_state[SDLK_q] || keyboard_state[SDLK_ESCAPE])
    {
        running = false;
    }
    
    if(keyboard_state[SDLK_d])
    {
        z+=zDir;
        y-=yDir;
        x+=xDir;
    }
    
    if(keyboard_state[SDLK_a])
    {
        z-=zDir;
        y+=yDir;
        x-=xDir;
    }
    
    if(keyboard_state[SDLK_w])
    {
        z-=zDir;
        y+=yDir;
        x-=xDir;
    }
    
    if(keyboard_state[SDLK_s])
    {
        z+=zDir;
        y-=yDir;
        x+=xDir;
    }
    
    /*
    if(keyboard_state[SDLK_e])
    {
        y-=.1;
    }
    
    if(keyboard_state[SDLK_c])
    {
        y+=.1;
    }
    */
    
    if(keyboard_state[SDLK_UP])
    {
        angleX++;
    }
    
    /*
    if((Xpos > screenSize[0]/2)&&(xrel != 0)&&(yrel != 0))
    {
        angleX+=2;
    }
    */
    if(keyboard_state[SDLK_DOWN])
    {
        angleX--;
    }
    
    if(keyboard_state[SDLK_RIGHT])
    {
        angleY++;
    }
    
    if(keyboard_state[SDLK_LEFT])
    {
        angleY--;
    }
    
    //std::cout<<xrel<<" "<<yrel<<"\n";
    
    if(angleX>360 || angleX<-360) angleX = 0;
    if(angleY>360 || angleY<-360) angleY = 0;
    
    std::cout<<angleX<<" "<<angleY<<" "<<angleZ<<std::endl;    
}

void engine::drawRect(int start) //accepts first vertex in lower right hand corner
{
    glBegin(GL_LINE_LOOP); // bottom
    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f(-2.0f,start/2+0.0f,start+2.0f);
    glVertex3f(-2.0f,start/2+0.0f,start+-2.0f);
    glVertex3f(2.0f,start/2+0.0f,start+-2.0f);
    glVertex3f(2.0f,start/2+0.0f,start+2.0f);
    glEnd();//end drawing of line loop
    
    glBegin(GL_LINE_LOOP);// side
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(-2.0f,start/2+0.0f,start+2.0f);
    glVertex3f(-2.0f,start/2+2.0f,start+2.0f);
    glVertex3f(+2.0f,start/2+2.0f,start+2.0f);
    glVertex3f(+2.0f,start/2+0.0f,start+2.0f);
    glEnd();//end drawing of line loop
    
}

void engine::quit()
{
    
}
