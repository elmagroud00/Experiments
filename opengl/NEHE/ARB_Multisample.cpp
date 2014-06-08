#include <windows.h>
#include "glew.h"
#include "wglew.h"
#include "arb_multisample.h"

// 声明我们将要使用
#define WGL_SAMPLE_BUFFERS_ARB		 0x2041
#define WGL_SAMPLES_ARB			     0x2042

bool	arbMultisampleSupported	= false;
int		arbMultisampleFormat	= 0;

// 判断是否支持这个扩展
bool WGLisExtensionSupported(const char *extension)
{
	const size_t extlen = strlen(extension);
	const char *supported = NULL;

	// 返回在WGL的扩展中查找是否支持特定的扩展
	PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");

	if (wglGetExtString)
		supported = ((char*(__stdcall*)(HDC))wglGetExtString)(wglGetCurrentDC());

	//在OpenGL的扩展中查找是否支持特定的扩展
	if (supported == NULL)
		supported = (char*)glGetString(GL_EXTENSIONS);

	// 如果都不支持，则返回失败
	if (supported == NULL)
		return false;

	// 查找是否包含需要的扩展名
	for (const char* p = supported; ; p++)
	{
		p = strstr(p, extension);

		if (p == NULL)
			return false;														

		if ((p==supported || p[-1]==' ') && (p[extlen]=='\0' || p[extlen]==' '))
			return true;															
	}
}

// 初始化多重渲染
bool InitMultisample(HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd)
{  
	 // 检测是否支持多重渲染
	if (!WGLisExtensionSupported("WGL_ARB_multisample"))
	{
		arbMultisampleSupported=false;
		return false;
	}

	// 返回wglChoosePixelFormatARB函数的入口
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

	//下面的代码设置多重采样的像素格式
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

	// 首先我们测试是否支持4个采样点的多重采样
	valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
	// 如果返回true并且numformats大于1，则表示成功，那么起用多重采样
	if (valid && numFormats >= 1)
	{
		arbMultisampleSupported = true;
		arbMultisampleFormat = pixelFormat;	
		return arbMultisampleSupported;
	}

	// 接着我们测试是否支持2个采样点的多重采样
	iAttributes[19] = 2;
	// 如果返回true并且numformats大于1，则表示成功，那么起用多重采样
	valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
	if (valid && numFormats >= 1)
	{
		arbMultisampleSupported = true;
		arbMultisampleFormat = pixelFormat;	 
		return arbMultisampleSupported;
	}
	  
	// 返回支持多重采样
	return  arbMultisampleSupported;
}
