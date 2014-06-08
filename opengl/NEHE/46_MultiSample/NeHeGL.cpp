#include <windows.h>													// Windowsͷ�ļ�
#include "glew.h"														// OpenGLͷ�ļ�
#include "NeHeGL.h"														// NeheGLͷ�ļ�


#include "ARB_MULTISAMPLE.h"

BOOL DestroyWindowGL (GL_Window* window);
BOOL CreateWindowGL (GL_Window* window);

// ����һ���û��Զ�����Ϣ
#define WM_TOGGLEFULLSCREEN (WM_USER+1)									
																		
static BOOL g_isProgramLooping;											// �Ƿ���г���ѭ��							
static BOOL g_createFullScreen;											// ���TRUE���򴴽�ȫ������					                       

void TerminateApplication (GL_Window* window)							// �رճ���
{
	PostMessage (window->hWnd, WM_QUIT, 0, 0);							// �����˳�����
	g_isProgramLooping = FALSE;											// ֹͣ����ѭ��
}

void ToggleFullscreen (GL_Window* window)								// �л�ȫ��/����ģʽ
{
	PostMessage (window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);				// �����л�����
}

void ReshapeGL (int width, int height)									// ���ݴ��ڴ�С������OpenGL�ӿڴ�С
{
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// ���ô��ڿɼ���Ϊ���ڴ�С
	glMatrixMode (GL_PROJECTION);										// ����ͶӰ����
	glLoadIdentity ();													// ������
	gluPerspective (45.0f, (GLfloat)(width)/(GLfloat)(height),			// ���ÿ�����̦��
					1.0f, 1000.0f);		
	glMatrixMode (GL_MODELVIEW);										// ����Ϊģ�ͱ任����
	glLoadIdentity ();													// ������
}

BOOL ChangeScreenResolution (int width, int height, int bitsPerPixel)	// �ı���Ļ�Ĵ�С��λ��
{
	DEVMODE dmScreenSettings;											// �豸ģʽ
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));					// ��0
	dmScreenSettings.dmSize				= sizeof (DEVMODE);				// ����Ϊ�ýṹ�Ĵ�С
	dmScreenSettings.dmPelsWidth		= width;						// ���ÿ��
	dmScreenSettings.dmPelsHeight		= height;						// ���ø߶�
	dmScreenSettings.dmBitsPerPel		= bitsPerPixel;					// ����λ��
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;			// ������Ҫ�ı�ĵط�
	if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)	// �ı���ʾģʽ
	{
		return FALSE;													// �����򷵻�
	}
	return TRUE;														// �ɹ�����
}

BOOL CreateWindowGL (GL_Window* window)									
{
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// ���ô�������Ϊһ��ĵ���ʽ����
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;						// ���ô��ڵ���չ����

	PIXELFORMATDESCRIPTOR pfd =											//pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{																	
		sizeof (PIXELFORMATDESCRIPTOR),									// ������ʽ�������Ĵ�С
		1,																// �汾��
		PFD_DRAW_TO_WINDOW |											// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |											// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,												// ����֧��˫����
		PFD_TYPE_RGBA,													// ���� RGBA ��ʽ
		window->init.bitsPerPixel,										// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,												// ���Ե�ɫ��λ
		0,																// ��Alpha����
		0,																// ����Shift Bit
		0,																// ���ۼӻ���
		0, 0, 0, 0,														// ���Ծۼ�λ
		16,																// 16λ Z-���� (��Ȼ���) 
		0,																// ���ɰ建��
		0,																// �޸�������
		PFD_MAIN_PLANE,													// ����ͼ��
		0,																// ��ʹ���ص���
		0, 0, 0															// ���Բ�����
	};

	RECT windowRect = {0, 0, window->init.width, window->init.height};	// ��¼���ڵĴ�С

	GLuint PixelFormat;													// ����������ظ�ʽ

	if (window->init.isFullScreen == TRUE)								// ���Ϊȫ��ģʽ
	{
		if (ChangeScreenResolution (window->init.width, window->init.height, window->init.bitsPerPixel) == FALSE)
		{
			//ȫ��ģʽʧ�ܣ������Ի��򣬸�֪�ڴ���ģʽ������
			MessageBox (HWND_DESKTOP, "ģʽ�л�ʧ��\n�ڴ���ģʽ������", "����", MB_OK | MB_ICONEXCLAMATION);
			window->init.isFullScreen = FALSE;							// ����isFullscreenΪFalse
		}
		//��ȫ��ģʽ������
		else															
		{
			ShowCursor(FALSE);											// ����ʾ���
			windowStyle = WS_POPUP;										// ���ô���ģʽΪ����ʽ����
			windowExtendedStyle |= WS_EX_TOPMOST;						// ���ô��ڵ���չģʽΪ��㴰��
		}																
	}
	else																//�����Ϊȫ��ģʽ
	{
		//�������ڴ�С�������ɱ߿�ȴ��ڲ���
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}

	// ����OpenGL����
	window->hWnd = CreateWindowEx (windowExtendedStyle,					// ��չ������
								   window->init.application->className,	// ������
								   window->init.title,					// ���ڱ���
								   windowStyle,							// ����Ĵ���������
								   0, 0,								// ����λ��
								   windowRect.right - windowRect.left,	// ��������õĴ��ڿ��
								   windowRect.bottom - windowRect.top,	// ��������õĴ��ڸ߶�
								   HWND_DESKTOP,						// �޸�����
								   0,									// �޲˵�
								   window->init.application->hInstance, // ʵ��
								   window);								// ��window��WM_CREATE����window�ṹ
																		
	if (window->hWnd == 0)												// ���ڴ����Ƿ�ɹ�	
	{
		return FALSE;													// ���ɹ��򷵻�
	}

	window->hDC = GetDC (window->hWnd);									// �����豸������
	if (window->hDC == 0)												// �Ƿ�ɹ�����豸������
	{
		// ʧ��
		DestroyWindow (window->hWnd);									// ɾ������
		window->hWnd = 0;												// ���ô��ھ��Ϊ0
		return FALSE;													// ����ʧ��
	}

	//PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// ѡ��һ�����ݵ����ظ�ʽ
	//if (PixelFormat == 0)												// �Ƿ������ݵ����ظ�ʽ
	//{
	//	// ʧ��
	//	ReleaseDC (window->hWnd, window->hDC);							// �ͷ��豸������
	//	window->hDC = 0;												// ���ô����豸������Ϊ0
	//	DestroyWindow (window->hWnd);									// ɾ������
	//	window->hWnd = 0;												// ���ô��ھ��Ϊ0
	//	return FALSE;													// ���ش���
	//}
/***********************************����Ĵ���***********************************************************************************/
	//��������ö��ز���
	if(!arbMultisampleSupported)
	{
		PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// ѡ��һ�����ݵ����ظ�ʽ
		if (PixelFormat == 0)												// �Ƿ������ݵ����ظ�ʽ
		{																	   												   
			ReleaseDC (window->hWnd, window->hDC);							// �ͷ��豸������
			window->hDC = 0;												// ���ô����豸������Ϊ0
			DestroyWindow (window->hWnd);									// ɾ������
			window->hWnd = 0;												// ���ô��ھ��Ϊ0
			return FALSE;													// ���ش���
		}

	}
	//������ö��ز���
	else
	{
		PixelFormat = arbMultisampleFormat;									//���ò�����ʽΪ���ز�����ʽ
	}
/********************************************************************************************************************************/
	if (SetPixelFormat (window->hDC, PixelFormat, &pfd) == FALSE)		// �������ظ�ʽ
	{
		// ����
		ReleaseDC (window->hWnd, window->hDC);							// �ͷ��豸������
		window->hDC = 0;												// ���ô����豸������Ϊ0
		DestroyWindow (window->hWnd);									// ɾ������
		window->hWnd = 0;												// ���ô��ھ��Ϊ0
		return FALSE;													// ���ش���
	}

	window->hRC = wglCreateContext (window->hDC);						// ����OpenGL��Ⱦ������
	if (window->hRC == 0)												// ���û�гɹ�����
	{
		ReleaseDC (window->hWnd, window->hDC);							// �ͷ��豸������
		window->hDC = 0;												// ���ô����豸������Ϊ0
		DestroyWindow (window->hWnd);									// ɾ������
		window->hWnd = 0;												// ���ô��ھ��Ϊ0
		return FALSE;													// ���ش���
	}

	if (wglMakeCurrent (window->hDC, window->hRC) == FALSE)				// ����RCΪ��ǰ��OpenGL����Ⱦ������
	{
		wglDeleteContext (window->hRC);									// ɾ����ǰ��OpenGL��Ⱦ������
		window->hRC = 0;												// �ͷ��豸������
		ReleaseDC (window->hWnd, window->hDC);							// ���ô����豸������Ϊ0
		window->hDC = 0;												// ɾ������
		DestroyWindow (window->hWnd);									// ���ô��ھ��Ϊ0
		window->hWnd = 0;												// ���ش���
		return FALSE;													
	}
/***********************************����Ĵ���***********************************************************************************/
	//����Ƿ�֧�ֶ��ز���
	if(!arbMultisampleSupported && CHECK_FOR_MULTISAMPLE)
	{
		//����ǣ���ʼ�����ز���
		if(InitMultisample(window->init.application->hInstance,window->hWnd,pfd))
		{
			//���ĵ�ǰ����
			DestroyWindowGL (window);
			//����һ��֧�ֶ��ز����Ĵ���
			return CreateWindowGL(window);
		}
	}
/********************************************************************************************************************************/
	ShowWindow (window->hWnd, SW_NORMAL);								// ��ʾ����
	window->isVisible = TRUE;											// ���ô���Ϊ�ɼ�

	ReshapeGL (window->init.width, window->init.height);				// ���ݴ��ڴ�С������OpenGL��Ӧ�Ĵ��ڴ�С

	ZeroMemory (window->keys, sizeof (Keys));							// ��ʼ��������¼��

	window->lastTickCount = GetTickCount ();							// ��¼��ǰ��ʱ����

	return TRUE;														// ���ڴ�����ϣ��ɹ�����
																		
}

BOOL DestroyWindowGL (GL_Window* window)								// ɾ������
{
	if (window->hWnd != 0)												// ������ھ����Ϊ0
	{	
		if (window->hDC != 0)											// ��������豸������Ϊ0
		{
			wglMakeCurrent (window->hDC, 0);							// �ͷŵ�ǰ��OpenGL��Ⱦ������
			if (window->hRC != 0)										
			{
				wglDeleteContext (window->hRC);						
				window->hRC = 0;										

			}
			ReleaseDC (window->hWnd, window->hDC);						// �ͷŴ����豸������	
			window->hDC = 0;											
		}
		DestroyWindow (window->hWnd);									// ɾ������
		window->hWnd = 0;												
	}

	if (window->init.isFullScreen)										// �����ȫ��ģʽ���任Ϊ��ʼģʽ
	{
		ChangeDisplaySettings (NULL,0);									
	}
	ShowCursor(TRUE);													// ��ʾ���
	return TRUE;														// ɾ��������ϣ��ɹ�����
}

// ������Ϣ������
LRESULT CALLBACK WindowProc (HWND hWnd,									// ���ڵľ��	
							 UINT uMsg,									// ���ڵ���Ϣ
							 WPARAM wParam,								// ���ӵ���Ϣ����
							 LPARAM lParam)								// ���ӵ���Ϣ����
{
	// ���ش�����Ϣ
	GL_Window* window = (GL_Window*)(GetWindowLong (hWnd, GWL_USERDATA));

	//ѭ������ÿ����Ϣ
	switch (uMsg)														
	{
		case WM_SYSCOMMAND:												// ����ϵͳ��Ϣ
		{
			switch (wParam)												// ���ϵͳ����
			{
				case SC_SCREENSAVE:										// �����Ҫ������������
				case SC_MONITORPOWER:									// �����Ҫ�ر���ʾ��
				return 0;												// �ػ��������Ϣ����������
			}
			break;														
		}
		return 0;														

		case WM_CREATE:													// ���ڴ���
		{
			CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);			// ��ô����Ĵ�����Ϣ
			window = (GL_Window*)(creation->lpCreateParams);			
			SetWindowLong (hWnd, GWL_USERDATA, (LONG)(window));
		}
		return 0;														

		case WM_CLOSE:													// �رմ���
			TerminateApplication(window);								// ��������
		return 0;														

		case WM_SIZE:													// �ı��С
			switch (wParam)												
			{
				case SIZE_MINIMIZED:									// ��С��
					window->isVisible = FALSE;							// ����ǣ��贰�ڲ��ɼ�
				return 0;												

				case SIZE_MAXIMIZED:									// ���
					window->isVisible = TRUE;							// ���ô��ڿɼ�
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// ����OpenGL���ڵĴ�С
				return 0;												

				case SIZE_RESTORED:										// �����Ƿ�����������
					window->isVisible = TRUE;							// ���ô��ڿɼ�
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// ����OpenGL���ڵĴ�С
				return 0;												
			}
		break;															

		case WM_KEYDOWN:												// ���°�������
			if ((wParam >= 0) && (wParam <= 255))						// ���Ϊ����֧�ֵ�256���ַ�
			{
				window->keys->keyDown [wParam] = TRUE;					// ��¼�Ǹ��ַ�������
				return 0;												
			}
		break;															

		case WM_KEYUP:													// ���°�������
			if ((wParam >= 0) && (wParam <= 255))						
			{
				window->keys->keyDown [wParam] = FALSE;					// ��¼�Ǹ��ַ����ͷ�
				return 0;												
			}
		break;															

		case WM_TOGGLEFULLSCREEN:										// �л�ȫƴ/����ģʽ
			g_createFullScreen = (g_createFullScreen == TRUE) ? FALSE : TRUE;
			PostMessage (hWnd, WM_QUIT, 0, 0);
		break;															
	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam);					
}

BOOL RegisterWindowClass (Application* application)						// ע��һ������			
{																		
	WNDCLASSEX windowClass;												// ������
	ZeroMemory (&windowClass, sizeof (WNDCLASSEX));						// ��սṹΪ0
	windowClass.cbSize			= sizeof (WNDCLASSEX);					// ���ڽṹ�Ĵ�С
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// ���ô�������Ϊ���ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	windowClass.lpfnWndProc		= (WNDPROC)(WindowProc);				// WndProc������Ϣ
	windowClass.hInstance		= application->hInstance;				// ����ʵ��
	windowClass.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE);			// ���ñ���
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			// ������
	windowClass.lpszClassName	= application->className;				// ��������



	if (RegisterClassEx (&windowClass) == 0)							// ����ע�ᴰ����
	{
		MessageBox(NULL,"ע�ᴰ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;													// �˳�������FALSE									
	}
	return TRUE;														
}

// ������ڣ�Windows��ѭ��
int WINAPI WinMain (HINSTANCE hInstance,			// ��ǰ����ʵ��
					HINSTANCE hPrevInstance,		// ǰһ������ʵ��
					LPSTR lpCmdLine,				// �����в���
					int nCmdShow)					// ������ʾ״̬
{
	Application			application;				// ����ṹ					
	GL_Window			window;						// ���ڽṹ			
	Keys				keys;						// �����ṹ			
	BOOL				isMessagePumpActive;		// 					
	MSG					msg;						// ��Ϣ�ṹ					
	DWORD				tickCount;					// ��������			

	application.className = "OpenGL";				// ������ΪOpenGL					
	application.hInstance = hInstance;				// ��������ʵ��	

	// ���ô�����Ϣ
	ZeroMemory (&window, sizeof (GL_Window));							// ������ṹ��0
	window.keys					= &keys;								// ���ñ��水��������
	window.init.application		= &application;							// �������ʵ��
	window.init.title			= "NeHe's Tutorial";					// ���ñ���
	window.init.width			= 640;									// ���ô��ڿ��
	window.init.height			= 480;									// ���ô��ڸ߶�
	window.init.bitsPerPixel	= 32;									// ������ɫ���Ϊ32									
	window.init.isFullScreen	= TRUE;									// ����ȥȫ��Ļ״̬

	ZeroMemory (&keys, sizeof (Keys));									//��ձ��水��������

	// ѯ���Ƿ���ȫ��״̬������
	if (MessageBox (HWND_DESKTOP, "������ȫ��״̬������ô?", "��ʼȫ������", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		window.init.isFullScreen = FALSE;								
	}

	// ע�ᴰ��
	if (RegisterWindowClass (&application) == FALSE)					
	{
		MessageBox (HWND_DESKTOP, "ע�ᴰ��ʧ��!", "����", MB_OK | MB_ICONEXCLAMATION);
		return -1;														
	}

	g_isProgramLooping = TRUE;											// ���ó���ѭ��ΪTRUE
	g_createFullScreen = window.init.isFullScreen;						// ��¼�Ƿ񴴽�ȫ������
	while (g_isProgramLooping)											// �������ѭ��ΪTRUE
	{
		//����һ������
		window.init.isFullScreen = g_createFullScreen;					
		if (CreateWindowGL (&window) == TRUE)							
		{
			// ����������ʼ��OpenGL
			if (Initialize (&window, &keys) == FALSE)					
			{
				// ���ʧ�ܣ����˳�
				TerminateApplication(&window);							
			}
			//��ʼ���ɹ�
			else														
			{
				// �����Ϣ����������Ϣ��������
				isMessagePumpActive = TRUE;								
				while (isMessagePumpActive == TRUE)						
				{
					// ���һ����Ϣ
					if (PeekMessage (&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
					{
						// ��������˳���Ϣ������Ϣ���͵�������
						if (msg.message != WM_QUIT)						
						{
							DispatchMessage (&msg);						
						}
						// ��������˳�
						else											
						{
							isMessagePumpActive = FALSE;				
						}
					}
					//���û����Ϣ
					else												
					{
						//���ڲ��ɼ�
						if (window.isVisible == FALSE)					
						{
							//�ȴ���һ����Ϣ
							WaitMessage ();								
						}
						//���ڿɼ�
						else											
						{
							//��õ�ǰʱ�������ֵ
							tickCount = GetTickCount ();				
							//����ʱ�䣬���³���
							Update (tickCount - window.lastTickCount);	
							//��¼��ǰ��ʱ�������ֵ
							window.lastTickCount = tickCount;			
							//���Ƴ���
							Draw ();									
							//����֡����
							SwapBuffers (window.hDC);					
						}
					}
				}														
			}															

			//׼��ж��
			Deinitialize ();											

			//ɾ����ǰ����
			DestroyWindowGL (&window);									
		}
		//�����˳�����
		else															
		{
			MessageBox (HWND_DESKTOP, "����OpenGL���ڴ���", "����", MB_OK | MB_ICONEXCLAMATION);
			g_isProgramLooping = FALSE;									
		}
	}																	

	// ȡ��ע��Ĵ���
	UnregisterClass (application.className, application.hInstance);		
	return 0;
}																		
