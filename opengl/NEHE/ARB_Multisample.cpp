#include <windows.h>
#include "glew.h"
#include "wglew.h"
#include "arb_multisample.h"

// �������ǽ�Ҫʹ��
#define WGL_SAMPLE_BUFFERS_ARB		 0x2041
#define WGL_SAMPLES_ARB			     0x2042

bool	arbMultisampleSupported	= false;
int		arbMultisampleFormat	= 0;

// �ж��Ƿ�֧�������չ
bool WGLisExtensionSupported(const char *extension)
{
	const size_t extlen = strlen(extension);
	const char *supported = NULL;

	// ������WGL����չ�в����Ƿ�֧���ض�����չ
	PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");

	if (wglGetExtString)
		supported = ((char*(__stdcall*)(HDC))wglGetExtString)(wglGetCurrentDC());

	//��OpenGL����չ�в����Ƿ�֧���ض�����չ
	if (supported == NULL)
		supported = (char*)glGetString(GL_EXTENSIONS);

	// �������֧�֣��򷵻�ʧ��
	if (supported == NULL)
		return false;

	// �����Ƿ������Ҫ����չ��
	for (const char* p = supported; ; p++)
	{
		p = strstr(p, extension);

		if (p == NULL)
			return false;														

		if ((p==supported || p[-1]==' ') && (p[extlen]=='\0' || p[extlen]==' '))
			return true;															
	}
}

// ��ʼ��������Ⱦ
bool InitMultisample(HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd)
{  
	 // ����Ƿ�֧�ֶ�����Ⱦ
	if (!WGLisExtensionSupported("WGL_ARB_multisample"))
	{
		arbMultisampleSupported=false;
		return false;
	}

	// ����wglChoosePixelFormatARB���������
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");	
	if (!wglChoosePixelFormatARB) 
	{
		arbMultisampleSupported=false;
		return false;
	}

	HDC hDC = GetDC(hWnd);

	int		pixelFormat;
	int		valid;
	UINT	numFormats;
	float	fAttributes[] = {0,0};

	//����Ĵ������ö��ز��������ظ�ʽ
	int iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
		WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB,24,
		WGL_ALPHA_BITS_ARB,8,
		WGL_DEPTH_BITS_ARB,16,
		WGL_STENCIL_BITS_ARB,0,
		WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
		WGL_SAMPLES_ARB,4,
		0,0
	};

	// �������ǲ����Ƿ�֧��4��������Ķ��ز���
	valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
	// �������true����numformats����1�����ʾ�ɹ�����ô���ö��ز���
	if (valid && numFormats >= 1)
	{
		arbMultisampleSupported = true;
		arbMultisampleFormat = pixelFormat;	
		return arbMultisampleSupported;
	}

	// �������ǲ����Ƿ�֧��2��������Ķ��ز���
	iAttributes[19] = 2;
	// �������true����numformats����1�����ʾ�ɹ�����ô���ö��ز���
	valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
	if (valid && numFormats >= 1)
	{
		arbMultisampleSupported = true;
		arbMultisampleFormat = pixelFormat;	 
		return arbMultisampleSupported;
	}
	  
	// ����֧�ֶ��ز���
	return  arbMultisampleSupported;
}
