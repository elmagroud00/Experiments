#ifndef __ARB_MULTISAMPLE_H__
#define __ARB_MULTISAMPLE_H__

//ȫ�ֱ���
extern bool	arbMultisampleSupported;
extern int arbMultisampleFormat;

//����㲻��Ҫ���ز������������Ϊ0
#define CHECK_FOR_MULTISAMPLE 1

//�����ز���
bool InitMultisample(HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd);

#endif