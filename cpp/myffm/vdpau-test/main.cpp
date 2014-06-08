#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include "VdpauContext.h"
#include "VdpauDecoderContext.h"
#include "DecoderThread.h"
#include <X11/Xlib.h>

int initializeGL()
{
	glClearColor(255.f, 255.0f, 255.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)1920 / (float)1080, 0.1f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearDepth(1.0f);													// 设置深度缓存
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算
	return 0;
}
DecoderThread *m_decoderThread = NULL;
GLuint m_curTex;

void testPaintGL()
{
	glClearColor(255.0f, 255.0f, 255.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glTranslatef(0.0f, -1.0f, -4.0f);
//	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glColor3f(1.0,20.0, 0.0);
	glVertex2f(0.0f, 0.0f); 
	glVertex2f(640.0f, 480.0f);
	glEnd();
}

void paintGL()
{
	int index= m_decoderThread->createGLSurface(&m_curTex);
	if(index != -1)
	{
		fprintf(stderr, "texture index = %d\n", index);
		glBindTexture(GL_TEXTURE_2D, m_curTex);
	}
	else
	{
		fprintf(stderr, "no textrue to paint\n");
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glTranslatef(-0.0f, 0.0f, -4.0f);
//	glRotatef(0.0f, -1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(640.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(640.0f, 480.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 480.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	m_decoderThread->releaseGLSurface(index);
	testPaintGL();
}

int main(int argc, char **argv)
{
	XInitThreads();
	Window win;
	Display *m_display = XOpenDisplay(NULL);
	static int attributes[] = {GLX_RGBA,
							   GLX_DOUBLEBUFFER,
							   GLX_DEPTH_SIZE, 16,
							   GLX_RED_SIZE, 8,
							   GLX_BLUE_SIZE, 8,
							   GLX_GREEN_SIZE, 8,
							   0};
	XVisualInfo *visualInfo = glXChooseVisual(m_display, DefaultScreen(m_display), attributes);
	XSetWindowAttributes winAttribs;
	winAttribs.event_mask = ExposureMask | VisibilityChangeMask |
							KeyPressMask | PointerMotionMask    |
							StructureNotifyMask;
	winAttribs.bit_gravity = StaticGravity;
	winAttribs.colormap = XCreateColormap(m_display, RootWindow(m_display, visualInfo->screen), 
										  visualInfo->visual, AllocNone);
	unsigned long winmask = CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
	win = XCreateWindow(m_display, DefaultRootWindow(m_display), 0, 0, 
					    1920, 1080, 0,
						visualInfo->depth, InputOutput,
						visualInfo->visual, winmask, &winAttribs);
	XMapWindow(m_display, win);

	GLXContext m_glContext = glXCreateContext(m_display, visualInfo, 0, True);
	glXMakeCurrent(m_display, win, m_glContext);

	GLXDrawable m_glDrawable = glXGetCurrentDrawable();


	initializeGL();
	SDL_Init(SDL_INIT_EVERYTHING);
	av_register_all();
	avcodec_register_all();
	printf("argv[1] = %s\n", argv[1]);
	char filename[256] = {0};
	memset(filename, 0x0, sizeof(filename));
	memcpy(filename, argv[1], strlen(argv[1]));
	printf("filename: %s\n", filename);
/*
	while(1)
	{
		testPaintGL();
		glXSwapBuffers(m_display, win);
	}
*/	
	m_decoderThread = new DecoderThread(m_display, m_glContext, m_glDrawable);
	m_decoderThread->start();

	while(1)
	{
		paintGL();	
		glXSwapBuffers(m_display, win);
	}

	glXSwapBuffers(m_display, win);
	
	usleep(100 * 1000 * 1000);
	fprintf(stderr, "hello\n");
	return 0;
}

