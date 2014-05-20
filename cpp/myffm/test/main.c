#include <stdio.h>
#include <unistd.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <pthread.h>
#include <string.h>

#define QUEUE_MAX_LEN 100

GLuint *texture;
int width1;
int height1;

void LoadJpgTextureGL(const char *file, unsigned char *tex, int *width, int *height)
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
	//texturebuf = tempjpg;
   tex = tempjpg;
   *width = cinfo.output_width;
   *height = cinfo.output_height;
    fprintf(stderr, "width = %d\n", *width);
    fprintf(stderr, "height = %d\n", *height);

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	free(buffer);
	fclose(jpefile);
/*	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,cinfo.output_width,cinfo.output_height,0,GL_RGB,GL_UNSIGNED_BYTE,texturebuf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	printf("load jpeg texture ok\n");

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(texturebuf);
	free(buffer);
*/	
}

void RenderScence(void)
{
    GLuint tex1;
    int width1;
    int height1;

    LoadJpgTextureGL("/home/sijiewang/Pictures/2.jpg", (unsigned char*)&tex1, &width1, &height1);
    fprintf(stderr, "width = %d\n", width1);
    fprintf(stderr, "height = %d\n", height1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.0f, 0.0f, -4.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D,tex1);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width1, height1, 0,GL_RGB, GL_UNSIGNED_BYTE, &tex1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);	glVertex3f(-1.0f,-1.5f,0.0f);
	glTexCoord2f(1.0f,0.0f);    glVertex3f(2.0f,-1.5f,0.0f);
    glTexCoord2f(1.0f,1.0f);	glVertex3f(2.0f,0.5f,0.0f);
	glTexCoord2f(0.0f,1.0f);	glVertex3f(-1.0f,0.5f,0.0f);
	glEnd();
	glFlush(); 
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);// 清屏为黑色
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)640/(float)480,0.1f,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);													// 设置深度缓存
	glEnable(GL_DEPTH_TEST);											// 开启深度测试
	glDepthFunc(GL_LEQUAL);												// 选择深度测试方式
	glShadeModel(GL_SMOOTH);											// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);					// 最精细的透视计算
/*	
//	glGenTextures(1,texture);
	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, data->width, data->height, 0,GL_RGB,GL_UNSIGNED_BYTE,data->data);
//	free(data->data);
//	free(data); */
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScence);
	SetupRC();
	glutMainLoop();

	return 0;
}
