#include <GL/glut.h>
#include <png.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include <GL/gl.h>

GLubyte *textureImage;
int width, height;
bool hasAlpha;
Display *dpy;
Window win;
GLXContext glc;

bool loadPngImage(char *name, int *outWidth, int *outHeight, bool *outHasAlpha, GLubyte **outData)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = false;
	int color_type, interlace_type;
	FILE *fp;

	printf("png file : %s\n", name);
	if((fp = fopen(name, "rb")) == NULL)
	{
		printf("%s: open png file error: \n", __FILE__);
		perror("open filed:\n");
		return false;
	}
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(NULL == png_ptr)
	{
		fclose(fp);
		return false;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if(NULL == info_ptr)
	{
		fclose(fp);
		return false;
	}
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		pclose(fp);
		return false;
	}
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);
	*outWidth = info_ptr->width;
	*outHeight = info_ptr->height;
	switch(info_ptr->color_type)
	{
		case PNG_COLOR_TYPE_RGBA:
			*outHasAlpha = true;
			break;
		case PNG_COLOR_TYPE_RGB:
			*outHasAlpha = false;
			break;
		default:
			printf("%s: color type: %d not supported\n", __FILE__, info_ptr->color_type);
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			fclose(fp);
			return false;
	}
	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*)malloc(row_bytes * *outHeight);
	png_bytepp row_pointer = png_get_rows(png_ptr, info_ptr);
	int i;
	for(i = 0; i < *outHeight; i++)
	{
		//note that png is ordered top to buttom,
		//but OpenGL expect it bottom to top
		//so the order swapped
		memcpy(*outData + (row_bytes * (*outHeight -true -i)), row_pointer[i], row_bytes);
	}
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	fclose(fp);
	printf("read png finished\n");
	return true;
}

static Display *XDisplay;
static XVisualInfo *gl_vinfo;

static void initGL(void)
{
    glBindTexture( GL_TEXTURE_2D, 0 );
    glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// Black Background
    glClearDepth(1.0f);							// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
}

void  display(void)
{
    glBindTexture(GL_TEXTURE_2D, *textureImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                     0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, textureImage);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,600, 600);
//    glRotatef(180, 0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f,  1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
//    free(textureImage);
}

/*Create window for GL*/
static void initWin()
{
	//Display *dpy;
	Window root;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	//Window win;
	XWindowAttributes gwa;
	XEvent xev;

	GLXFBConfig *fc;
	GLXWindow glw;
	//GLXContext glc;
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
		return;
	}
	fc = glXChooseFBConfig(dpy, 0, attr, &nelements);
	if(fc == NULL)
	{
		printf("no appropriate framebiffer config fond\n");
		return;
	}
	vi = glXGetVisualFromFBConfig(dpy, *fc);
	if(vi == NULL)
	{
		printf("no appropriate visual found\n");
		return;
	}
	root = DefaultRootWindow(dpy);
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	win = XCreateWindow(dpy, root, 0, 0, 1920, 1080,
			0, vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask , &swa);
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "SIMPLE");
	glw = glXCreateWindow(dpy, *fc, win, NULL);
	glc = glXCreateNewContext(dpy, *fc, GLX_RGBA_TYPE, NULL, GL_TRUE);
	glXMakeContextCurrent(dpy, win, win, glc);
/*	glXMakeCurrent(dpy, None, NULL);
	glXDestroyContext(dpy, glc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
	*/
	return; 
}

void play(char *filename)
{
	bool success = loadPngImage(filename, &width, &height, &hasAlpha, &textureImage);
	if(!success)
	{
		printf("Unable to load Image");
		return;
	}
	printf("Image loaded width = %d height = %d hasAlpha = %d", width, height, hasAlpha);
}

int main(int argc, char **argv)
{
	initWin();
	initGL();
	play("/home/sijiewang/Pictures/1.png");
	display();
   	glXSwapBuffers(dpy, win);
    sleep(10000000);
	return 0;
}
