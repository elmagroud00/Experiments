#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL/SDL.h>
#include "VdpauContext.h"
#include "VdpauDecoderContext.h"
#include "DecoderThread.h"
#include <X11/Xlib.h>
#include "LoadImage.h"
#include "util.h"

VideoPlayer *m_videoPlayer = NULL;
VideoPlayer *m_videoPlayer2 = NULL;
GLuint m_curTex;
GLuint m_curTex2;
GLuint *m_picTex;

void initializeGL()
{
    glBindTexture(GL_TEXTURE_2D, 0 );
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
 //   GLfloat lightPos[] = {0.0f, 0.0f, 75.0f, 1.0f};
  //  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
 //   GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
 //   GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
  //  GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
 //   GLfloat spotDir[] = {0.0f, 0.0f, -1.0f};
 //   glEnable(GL_LIGHTING);
  //  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
 //   glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
 //   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
 //   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
 //   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
  //  glEnable(GL_LIGHT0);
 //   glEnable(GL_COLOR_MATERIAL);
  //  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  //  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
 //   glMateriali(GL_FRONT, GL_SHININESS, 128);
 //   glDisable(GL_LIGHTING);
}

void paintGL1()
{
	long long begin = Dayus();
	fprintf(stderr, "begin to paint: %lld\n", begin);
	int index= m_videoPlayer->createGLSurface(&m_curTex);
	glDisable(GL_ALPHA_TEST);
	if(index != -1)
	{
		fprintf(stderr, "texture index = %d\n", index);
		glBindTexture(GL_TEXTURE_2D, m_curTex);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glViewport(0, 0, 1920, 1080);
		//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		//glTranslatef(0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		fprintf(stderr, "no textrue to paint\n");
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	m_videoPlayer->releaseGLSurface(index);
	long long end = Dayus();
	fprintf(stderr, "end to paint: %lld\n", end);
	fprintf(stderr, "paint used: %lld (us)\n", end - begin);
}

void paintGL2()
{
	int index= m_videoPlayer2->createGLSurface(&m_curTex2);
	glDisable(GL_ALPHA_TEST);

	if(index != -1)
	{
		fprintf(stderr, "texture index = %d\n", index);
		glBindTexture(GL_TEXTURE_2D, m_curTex2);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glViewport(0, 0, 200, 200);
		//glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		fprintf(stderr, "no textrue to paint\n");
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	m_videoPlayer2->releaseGLSurface(index);
}

void paintGL3(const unsigned int width, const unsigned int height)
{
	glBindTexture(GL_TEXTURE_2D, *m_picTex);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		    	GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, m_picTex);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, 1920, 1080);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
//	free(m_curTex2);
}

int main(int argc, char **argv)
{

	SDL_Init(SDL_INIT_EVERYTHING);
	av_register_all();
	avcodec_register_all();

	XInitThreads();

	Display *dpy;
	Window root;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	Window win;

	unsigned int width =  1920;
	unsigned int height = 1080;
	unsigned int x_pos = 0;
	unsigned int y_pos = 0;

	GLXFBConfig *fc;
	GLXWindow glw;
	GLXContext glc;
	int attr[] = {
			GLX_RENDER_TYPE,
			GLX_RGBA_BIT,
			GLX_DOUBLEBUFFER,
			True,
			GLX_DEPTH_SIZE,
			16,
			None
	};
	int nelements;

	dpy = XOpenDisplay(NULL);
	if(dpy == NULL)
	{
		printf("Cannot connect to XServer\n");
		return -1;
	}
	fc = glXChooseFBConfig(dpy, 0, attr, &nelements);
	if(fc == NULL)
	{
		printf("no appropriate framebiffer config fond\n");
		return -1;
	}
	vi = glXGetVisualFromFBConfig(dpy, *fc);
	if(vi == NULL)
	{
		printf("no appropriate visual found\n");
		return -1;
	}
	root = DefaultRootWindow(dpy);
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	win = XCreateWindow(dpy, root, x_pos, y_pos, width, height,
			0, vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask , &swa);
	XMapWindow(dpy, win);
	//XStoreName(dpy, win, "MyPlayer");
//	glw = glXCreateWindow(dpy, *fc, win, NULL);
	glc = glXCreateNewContext(dpy, *fc, GLX_RGBA_TYPE, NULL, GL_TRUE);
	glXMakeContextCurrent(dpy, win, win, glc);
//	GLXDrawable gld = glXGetCurrentDrawable();


	initializeGL();
	//glXMakeCurrent (dpy, None, NULL);
	//m_videoPlayer = new VideoPlayer(dpy, glc, win);
	m_videoPlayer = new VideoPlayer();
	m_videoPlayer->setFileName("/home/sijiewang/Videos/mollystheory-tlr1_h480p.mov");
	m_videoPlayer->startPlay();

/*	m_videoPlayer2 = new VideoPlayer(dpy, glc, win2);
	m_videoPlayer2->setFileName(argv[1]);
	m_videoPlayer2->startPlay();
	//m_videoPlayer2 = new VideoPlayer(cw2->getDpy(), cw2->getGLC(), cw2->getWin());
	//m_videoPlayer2->setFileName("/home/sijiewang/Videos/1920x1080_Kara_Lupin_30帧_196.2M_3min15s.mov");
	//m_videoPlayer2->startPlay();

/*	int picWidth;
	int picHeight;
	bool HasAlpha;
	loadPngImage("/home/sijiewang/Pictures/2.png", &picWidth, &picHeight, &HasAlpha, (GLubyte**)&m_picTex);
	//paintGL3(width, height);*/

  //  drawStr(0, 0 , "%s", "Hello, world aaaaaaaaaaaaaaaaaaaaaaaaa!");
   // glXSwapBuffers(dpy, win);
   // sleep(10000);
//decoderVideo2OutputSurface finish

	while(1)
	{
		/*
		i++;

		if( i == 700)
		{
	           m_videoPlayer->stopPlay();
	           m_videoPlayer->setFileName("/home/sijiewang/Videos/mollystheory-tlr1_h480p.mov");
	           m_videoPlayer->startPlay();

       }
       if(i == 1500)
	   {
	           m_videoPlayer->stopPlay();
	           m_videoPlayer->setFileName("/home/sijiewang/Videos/1920x1080_Kara_Lupin_30帧_196.2M_3min15s.mov");
               m_videoPlayer->startPlay();

	    }
       if(i == 1900)
    	   i = 0;

*/
	    paintGL1();
	//    paintGL2();
	    glXSwapBuffers(dpy, win);
	//    glXSwapBuffers(dpy, win2);
	   // paintGL3(picWidth, picHeight);

	}

/*	glXMakeCurrent (dpy, None, NULL);
	glXDestroyContext (dpy, glc);
	XDestroyWindow (dpy, win);
	XCloseDisplay (dpy);*/

	return 0;
}

