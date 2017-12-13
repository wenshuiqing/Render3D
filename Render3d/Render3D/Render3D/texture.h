#pragma once
#include <string>
#include <windows.h>
class Texture
{
public:
	unsigned char  *buffer;
	std::string path;
	int width;
	int height;
	int bit = 32;
public:
	Texture(std::string path, int width, int height,int bit=32) :path(path), width(width), height(height),bit(bit)
	{
		buffer = new unsigned char[width*height * 4];
	}

	static void LoadTexture(HDC hdc, Texture *tex)
	{
		BITMAPINFO binfoTex;
		memset(&binfoTex, 0, sizeof(BITMAPINFO));
		binfoTex.bmiHeader.biBitCount = tex->bit;
		binfoTex.bmiHeader.biCompression = BI_RGB;
		binfoTex.bmiHeader.biHeight = -tex->height;
		binfoTex.bmiHeader.biPlanes = 1;
		binfoTex.bmiHeader.biSizeImage = 0;
		binfoTex.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		binfoTex.bmiHeader.biWidth = tex->width;
		//载入纹理图
		HBITMAP hTextureBitmap = (HBITMAP)LoadImage(NULL, tex->path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		//获取纹理的像素
		GetDIBits(hdc, hTextureBitmap, 0, tex->height, tex->buffer, (BITMAPINFO*)&binfoTex, DIB_RGB_COLORS);
	}


	virtual ~Texture()
	{
		delete buffer;
		buffer = nullptr;
	}


private:

	
};
