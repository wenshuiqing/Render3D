#include <windows.h>
#include <assert.h>
#include <string>
#include <WindowsX.h>
#include "device.h"
#include "rmathf.h"
#include "mesh.h"
#include "camera.h"
#include <iostream>
#include "gameobject.h"

using namespace std;
const int SCREEN_WIDTH = Screen::Width;
const int SCREEN_HEIGHT = Screen::Height;

//屏幕宽度和高度   
const int BITS = 32;				//每个像素的位数  
HDC screen_hdc;
HWND screen_hwnd;
HDC hCompatibleDC; //兼容HDC  
HBITMAP hCompatibleBitmap; //兼容BITMAP    
BITMAPINFO binfo; //BITMAPINFO结构体  
HINSTANCE ghInstance;


BYTE Buffer[SCREEN_WIDTH*SCREEN_HEIGHT * 4];
//渲染装置
Device *device;
Cube *cube;
Texture *tex;
float deltaTime;

void Display();
void SrcInit();
HWND Start(HINSTANCE hInstance, int nShowCmd, string wcName, string title);
void Update(HWND hwnd);
void Destroy(string wcName, HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lParam);






int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//1.创建窗口
	string windowClassName = "MyWindow";
	string title = "3DRender";
	HWND hwnd = Start(hInstance, nShowCmd, windowClassName, title);

	//时间初始化
	DWORD curTime = GetTickCount();
	DWORD preTime = GetTickCount();
	//2.消息循环
	MSG msg = { 0 };
	SrcInit();
	while (msg.message != WM_QUIT)
	{
		//获取消息
		if (PeekMessage(&msg, 0, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			curTime = GetTickCount();
			if (curTime - preTime > 30)
			{
				deltaTime = curTime - preTime;
				preTime = curTime;
				Update(hwnd);
			}
		}
	}

	//3.游戏结束
	Destroy(windowClassName, hInstance);
	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wparam, lParam);
	}
	return 0;
}
HWND Start(HINSTANCE hInstance, int nShowCmd, string wcName, string title)
{

	ghInstance = hInstance;
	//1.创建窗口类
	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = wcName.c_str();

	//2.注册窗口类
	assert(RegisterClassEx(&wndClass));

	//3.创建窗口
	HWND hwnd = CreateWindow(wcName.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);

	//4.调整大小，移动，显示，更新
	if (!hwnd)
	{
		return FALSE;
	}

	RECT  rectProgram, rectClient;
	GetWindowRect(hwnd, &rectProgram);   //获得程序窗口位于屏幕坐标
	GetClientRect(hwnd, &rectClient);      //获得客户区坐标
										   //非客户区宽,高
	int nWidth = rectProgram.right - rectProgram.left - (rectClient.right - rectClient.left);
	int nHeiht = rectProgram.bottom - rectProgram.top - (rectClient.bottom - rectClient.top);
	nWidth += SCREEN_WIDTH;
	nHeiht += SCREEN_HEIGHT;
	rectProgram.right = nWidth;
	rectProgram.bottom = nHeiht;
	int showToScreenx = GetSystemMetrics(SM_CXSCREEN) / 2 - nWidth / 2;    //居中处理
	int showToScreeny = GetSystemMetrics(SM_CYSCREEN) / 2 - nHeiht / 2;
	MoveWindow(hwnd, showToScreenx, showToScreeny, rectProgram.right, rectProgram.bottom, false);

	memset(&binfo, 0, sizeof(BITMAPINFO));
	binfo.bmiHeader.biBitCount = BITS;      //每个像素多少位，也可直接写24(RGB)或者32(RGBA)  
	binfo.bmiHeader.biCompression = BI_RGB;
	binfo.bmiHeader.biHeight = -SCREEN_HEIGHT;
	binfo.bmiHeader.biPlanes = 1;
	binfo.bmiHeader.biSizeImage = 0;
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = SCREEN_WIDTH;



	//获取屏幕HDC  
	screen_hwnd = hwnd;
	screen_hdc = GetDC(screen_hwnd);

	//获取兼容HDC和兼容Bitmap,兼容Bitmap选入兼容HDC(每个HDC内存每时刻仅能选入一个GDI资源,GDI资源要选入HDC才能进行绘制)  
	hCompatibleDC = CreateCompatibleDC(screen_hdc);
	hCompatibleBitmap = CreateCompatibleBitmap(screen_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hCompatibleBitmap);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	return hwnd;
}


void SrcInit()
{
	device = new Device(SCREEN_WIDTH, SCREEN_HEIGHT, Buffer, Color(1.0f, 0, 0, 1.0f));
	cube = new Cube;

	cube->transform->Scale(2, 2, 2);
	cube->transform->Rotate(0.0, 45.0, 0.0);

	tex = new Texture("102.bmp", 148, 149);
	Texture::LoadTexture(screen_hdc, tex);
}
void Update(HWND hwnd)
{
	//cube->transform->Rotate(-1.f, Axis::Y);
	device->Render(cube, tex);
	device->RenderTexture(tex, tex->width, tex->height);
	Display();
}
void Display()
{
	////将颜色数据打印到屏幕上，这下面两个函数每帧都得调用  
	SetDIBits(screen_hdc, hCompatibleBitmap, 0, SCREEN_HEIGHT, Buffer, (BITMAPINFO*)&binfo, DIB_RGB_COLORS);
	BitBlt(screen_hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hCompatibleDC, 0, 0, SRCCOPY);
}
void Destroy(string wcName, HINSTANCE hInstance)
{
	/*delete device;
	device = nullptr;*/
	delete cube;
	cube = nullptr;
	//5.注销窗口类
	UnregisterClass(wcName.c_str(), hInstance);
}