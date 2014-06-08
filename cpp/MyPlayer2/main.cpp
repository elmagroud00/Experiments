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

VideoPlayer *m_videoPlayer = NULL;
GLuint m_curTex;

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
}

void paintGL(const unsigned int width, const unsigned int height)
{
	int index= m_videoPlayer->createGLSurface(&m_curTex);
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
		glViewport(0, 0, width, height);
		//glRotatef(rot, 1.0f, 1.0f, 0.0f);
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
	m_videoPlayer->releaseGLSurface(index);
}

int main(int argc, char **argv)
{
	XInitThreads();
	Display *dpy;
	Window root;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	Window win;

	unsigned int width = 800;
	unsigned int height = 600;

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
	win = XCreateWindow(dpy, root, 0, 0, width, height,
			0, vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask , &swa);
	XMapWindow(dpy, win);
	//glw = glXCreateWindow(dpy, *fc, win, NULL);
	glc = glXCreateNewContext(dpy, *fc, GLX_RGBA_TYPE, NULL, GL_TRUE);
	glXMakeContextCurrent(dpy, win, win, glc);
	GLXDrawable gld = glXGetCurrentDrawable();

	initializeGL();
	SDL_Init(SDL_INIT_EVERYTHING);
	av_register_all();
	avcodec_register_all();

	m_videoPlayer = new VideoPlayer(dpy, glc, gld);
	m_videoPlayer->setFileName(argv[1]);
	m_videoPlayer->startPlay();

	int i = 0;
	int quit = 0;
	while(1)
	{
		if(i++ == 700)
		{
			m_videoPlayer->stopPlay();
			m_videoPlayer->setFileName("/home/sijiewang/Videos/mollystheory-tlr1_h480p.mov");
			m_videoPlayer->startPlay();
			m_videoPlayer->quitPlayer();
			quit = 1;
		}
		if(i == 1600)
		{
			m_videoPlayer->stopPlay();
			m_videoPlayer->setFileName("/home/sijiewang/Videos/A1.mp4");
			m_videoPlayer->startPlay();
			quit = 0;
		}
		if(quit == 0)
			paintGL(width, height);
		glXSwapBuffers(dpy, win);
	}

	glXMakeCurrent (dpy, None, NULL);
	glXDestroyContext (dpy, glc);
	XDestroyWindow (dpy, win);
	XCloseDisplay (dpy);

	return 0;
}

