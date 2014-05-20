#ifndef __ARB_MULTISAMPLE_H__
#define __ARB_MULTISAMPLE_H__

//全局变量
extern bool	arbMultisampleSupported;
extern int arbMultisampleFormat;

//如果你不想要多重采样，设置这个为0
#define CHECK_FOR_MULTISAMPLE 1

//检测多重采样
bool InitMultisample(HINSTANCE hInstance,HWND hWnd,PIXELFORMATDESCRIPTOR pfd);

#endif