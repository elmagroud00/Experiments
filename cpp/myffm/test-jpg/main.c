#include <stdio.h>
#include <unistd.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <pthread.h>
#include <string.h>

#define QUEUE_MAX_LEN 100

static GLuint texture;
typedef struct _queue_t
{
	struct _queue_t *prev;
	struct _queue_t *next;
	unsigned char *data;
	unsigned int width;
	unsigned int height;
}queue_t;

typedef struct _queue
{
	 queue_t *head;
	 queue_t *tail;
	 unsigned int length;	
	 pthread_mutex_t mutex;
	 pthread_cond_t cond;
}queue;

void QueueInit(queue *q)
{
	q->head = q->tail = NULL;
	q->length = 0;
	pthread_mutex_init(&q->mutex, NULL);
	pthread_cond_init(&q->cond, NULL);
}

void PushQueue(queue *q, unsigned char *data, unsigned width, unsigned height)
{
	if(!q)
		return;
	pthread_mutex_lock(&q->mutex);
	printf("PUSH : Queue length = %d\n", q->length);
	while(q->length > QUEUE_MAX_LEN)
	{
		fprintf(stderr, "full....\n");
		pthread_cond_wait(&q->cond, &q->mutex);
	}
	queue_t *tmp;
	tmp = (queue_t*)malloc(sizeof(queue_t));
	tmp->data = data;
	tmp->prev = tmp->next = NULL;
	tmp->width = width;
	tmp->height = height;
	if(q->tail)
		q->tail->next = tmp;
	q->tail = tmp;
	if(q->head == NULL)
		q->head = q->tail;
	q->length++;
	pthread_mutex_unlock(&q->mutex);
	pthread_cond_signal(&q->cond);
}

queue_t *PopQueue(queue *q)
{
	if(!q)
		return NULL; printf("POP : Queue length = %d\n", q->length);
	pthread_mutex_lock(&q->mutex);
	while(q->length < 1)
	{
		fprintf(stderr, "empty...\n");
		pthread_cond_wait(&q->cond, &q->mutex);
	}
	queue_t *tmp = NULL;
	tmp = q->head;
	q->head = tmp->next;
  	if(q->head)
  		q->head->prev = NULL;
	else
		q->tail = NULL;
	q->length--;
	pthread_mutex_unlock(&q->mutex);
	pthread_cond_signal(&q->cond);
	return tmp;
}

static queue JpgQueue;

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
	PushQueue(&JpgQueue, texturebuf, cinfo.output_width, cinfo.output_height);

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	free(buffer);
	fclose(jpefile);
/*
//	glGenTextures(1,&texture);
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
	queue_t *data;
	data = PopQueue(&JpgQueue);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.0f, 0.0f, -4.0f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, data->width, data->height, 0,GL_RGB, GL_UNSIGNED_BYTE, data->data);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f,-1.5f,0.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(2.0f,-1.5f,0.0f);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(2.0f,0.5f,0.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f,0.5f,0.0f);
	glEnd();
	glFlush();
	free(data->data);
	free(data);
}

void SetupRC(void)
{
	queue_t *data;
	data = PopQueue(&JpgQueue);
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
	
	glGenTextures(1,&texture);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, data->width, data->height, 0,GL_RGB,GL_UNSIGNED_BYTE,data->data);
	free(data->data);
	free(data);
}

void TimerFunc(int value)
{
//	LoadJpgTextureGL("/home/sijiewang/test2.jpg");
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

static int argc2 = 0;
static char **argv2 = NULL;

static void *CreateWindow(void *arg)
{
	glutInit(&argc2, argv2);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScence);
	glutTimerFunc(100, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
}	

int main(int argc, char **argv)
{
	argc2 = argc;
	argv2 = argv;	
	QueueInit(&JpgQueue);
	LoadJpgTextureGL("/home/sijiewang/Pictures/1.jpg");
	pthread_t pId;
	if(pthread_create(&pId, NULL, CreateWindow, NULL))
	{
		perror("Create thread failed\n");
		return -1;
	}
	while(1)
	{
		LoadJpgTextureGL("/home/sijiewang/Pictures/1.jpg");
		usleep(1);
		LoadJpgTextureGL("/home/sijiewang/Pictures/2.jpg");
		usleep(1);
	}
	pause();
	pause();
	return 0;
}
