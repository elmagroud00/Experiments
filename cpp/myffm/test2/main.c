#include <stdio.h>
#include <unistd.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <pthread.h>
#include <string.h>
#include <X11/Xlib.h>
#include <SDL/SDL.h>
#define QUEUE_MAX_LEN 100

static GLuint texture;
Display *dpy;
Window	win;

void LoadJpgTextureGL(char *file)
{
	FILE *jpefile;
	int sizebuf;
	unsigned char* buffer;
	unsigned char* texturebuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	if((jpefile = fopen(file,"rb"))==NULL)
	{
		perror("fopen jpeg");
		return; 
	}
	jpeg_stdio_src(&cinfo,jpefile);
	jpeg_read_header(&cinfo,TRUE);
	jpeg_start_decompress(&cinfo);

	sizebuf = cinfo.output_width * cinfo.output_components;
	buffer = (unsigned char *)malloc(sizebuf);
	texturebuf = (unsigned char *)malloc(sizebuf * cinfo.output_height);
	unsigned char *tempjpg = texturebuf;
	while(cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo,&buffer,1);
		memcpy(texturebuf,buffer,sizebuf);
		texturebuf +=sizebuf;
	}
	texturebuf = tempjpg;

	glClearColor (0.2, 0.4, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(-0.0f, 0.0f, -4.0f);
	//glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,cinfo.output_width,cinfo.output_height,0,GL_RGB,GL_UNSIGNED_BYTE,texturebuf);
/*
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-540.0f, 960.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(540.0f, 960.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(540.0f, -960.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-540.0f, -960.0f);
	glEnd();
	glFlush();
*/
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.5f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -1.5f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f, 0.5f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.5f, 0.0f);
	glEnd();
//	glFlush();
	sleep(1);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	printf("load jpeg texture ok\n");

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(texturebuf);
	free(buffer);
}

void paintGL()
{
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-540.0f, 960.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(540.0f, 960.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(540.0f, -960.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-540.0f, -960.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void initializeGL3(void)
{
	/* 启用深度测试（隐藏面摘除） */
	glEnable (GL_DEPTH_TEST);

	/* 设置投影矩阵 */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-1., 1., -1., 1., 1., 20.);

	/* 设置模型视图 */
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (0., 0., 10., 0., 0., 0., 0., 1., 0.);

}

void initializeGL(void)
{
	glClearColor(100.0f, 230.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (-1., 1., -1., 1., 1., 20.);
//	gluPerspective(45,(float)640/(float)480,0.1f,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0., 0., 10., 0., 0., 0., 0., 1., 0.);
//	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
//	glClearDepth(1.0f);													// 设置深度缓存
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算
	glGenTextures(1,&texture);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void initializeGL2()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算
}

int main(int argc, char **argv)
{
	Window root;
	XVisualInfo	*vi;
	Colormap	cmap;
	XSetWindowAttributes	swa;
	XWindowAttributes	gwa;
	XEvent	xev;
	unsigned int width = 640;
	unsigned int height = 480;
	GLXFBConfig	*fc;
	GLXWindow	glw;
	GLXContext	glc;
	int att[] = {GLX_RENDER_TYPE,
				 GLX_RGBA_BIT,
				 GLX_DEPTH_SIZE, 16,
				 None};
	int nelements;
	dpy = XOpenDisplay(NULL);
	if(dpy == NULL)
	{
		fprintf(stderr, "con not connect to X server\n");
		return -1;
	}
	fc = glXChooseFBConfig(dpy, 0, att, &nelements);
	if(fc == NULL)
	{
		fprintf(stderr, "no appropriate framebuffer config foune\n");
		return -1;
	}
	vi = glXGetVisualFromFBConfig(dpy, *fc);
	if(vi == NULL)
	{
		fprintf(stderr, "no appropriate visual found\n");
		return -1;
	}
	root = DefaultRootWindow(dpy);
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	win = XCreateWindow(dpy, root, 0, 0, width, height, 
					    0, vi->depth, InputOutput, vi->visual,
						CWColormap | CWEventMask, &swa);
	XMapWindow(dpy, win);
	glw = glXCreateWindow(dpy, *fc, win, NULL);
	glc = glXCreateNewContext(dpy, *fc, GLX_RGBA_TYPE, NULL, GL_TRUE);
	glXMakeContextCurrent(dpy, win, win, glc);

	initializeGL();

	LoadJpgTextureGL("/home/sijiewang/test1.jpg");
	glXSwapBuffers(dpy, win);
	sleep(2);
	LoadJpgTextureGL("/home/sijiewang/test2.jpg");
	glXSwapBuffers(dpy, win);
	sleep(1000);
	pause();

	glXMakeCurrent(dpy, None, NULL);
	glXDestroyContext(dpy, glc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
