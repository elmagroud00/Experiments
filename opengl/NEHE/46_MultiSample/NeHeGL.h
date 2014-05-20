#ifndef GL_FRAMEWORK__INCLUDED
#define GL_FRAMEWORK__INCLUDED

#include <windows.h>								// Windowsͷ�ļ�		

typedef struct {									// ���水����Ϣ
	BOOL keyDown [256];								// TRUE��ʾ������
} Keys;												

typedef struct {									// ���������Ϣ
	HINSTANCE		hInstance;						// ����ʵ��
	const char*		className;						// ���򴰿ڵ�����
} Application;										

typedef struct {									// ������ʼ���ṹ
	Application*		application;				// ����ṹ
	char*				title;						// ���ڱ���
	int					width;						// ���ڿ��
	int					height;						// ���ڸ߶�
	int					bitsPerPixel;				// ����λ��
	BOOL				isFullScreen;				// �Ƿ�ȫ����ʾ
} GL_WindowInit;									

typedef struct {									// ���洰����Ϣ
	Keys*				keys;						// �����ṹ
	HWND				hWnd;						// ���ھ��
	HDC					hDC;						// �����豸�������� 
	HGLRC				hRC;						// OpenGL��Ⱦ��������
	GL_WindowInit		init;						// ��ʼ�����ڽṹ
	BOOL				isVisible;					// �����Ƿ�ɼ�
	DWORD				lastTickCount;				// ��һ�μ�ʱ����ֵ
} GL_Window;										

void TerminateApplication (GL_Window* window);		// �رճ���

void ToggleFullscreen (GL_Window* window);			//�л�����ģʽ��ȫ��ģʽ

// ��ʼ��
BOOL Initialize (GL_Window* window, Keys* keys);	

void Deinitialize (void);							// �ر��ͷ���Դ

void Update (DWORD milliseconds);					// ���³���

void Draw (void);									// ����

#endif												// GL_FRAMEWORK__INCLUDED
