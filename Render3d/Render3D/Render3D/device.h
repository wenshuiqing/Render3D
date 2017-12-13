#pragma once
#include "rmathf.h"
#include "camera.h"
#include "mesh.h"
#include "gameobject.h"
#include <iostream>
using namespace mf;

class Device
{
private:

	struct a2v
	{
		mf::Vector3 vertex;
		mf::Vector3 normal;
		mf::Vector2 texcoord;
	};

	struct v2f
	{
		mf::Vector3 pos;
		mf::Vector3 wNormal;
		mf::Vector3 wPos;
		mf::Vector2 uv;
	};


public:

	Device(int width, int height, BYTE *frameBuffer, Color brushColor)
		:width(width), height(height), colorBuffer(frameBuffer), brushColor(brushColor)
	{
		depthBuffer = new float[width*height];
		camera = new Camera;
	}
	void Clear(float r, float g, float b, float a, bool isClearDepth = true)
	{
		for (unsigned int i = 0; i < (width*height * 4); i += 4)
		{
			colorBuffer[i] = (BYTE)(b * 255);
			colorBuffer[i + 1] = (BYTE)(g * 255);
			colorBuffer[i + 2] = (BYTE)(r * 255);
			colorBuffer[i + 3] = (BYTE)(a * 255);
		}
		if (isClearDepth)
		{
			for (unsigned int i = 0; i < (width*height); i++)
			{
				depthBuffer[i] = FLT_MAX;
			}
		}
	}
	void Clear(Color color, bool isClearDepth = true)
	{
		for (unsigned int i = 0; i < width*height * 4; i += 4)
		{
			colorBuffer[i] = (BYTE)color.b * 255;
			colorBuffer[i + 1] = (BYTE)color.g * 255;
			colorBuffer[i + 2] = (BYTE)color.r * 255;
			colorBuffer[i + 3] = (BYTE)color.a * 255;
		}

		if (isClearDepth)
		{
			for (unsigned int i = 0; i < (width*height); i++)
			{
				depthBuffer[i] = FLT_MAX;
			}
		}
	}

	void SetColor(Color color)
	{
		brushColor = color;
	}
	void SetColor(float r, float g, float b, float a)
	{
		brushColor.r = r;
		brushColor.g = g;
		brushColor.b = b;
		brushColor.a = a;
	}


	void DrawPoint(int x, int y)
	{
		if (x >= 0 && y >= 0 && x < width && y < height)
		{
			SetPixel(x, y);
		}
	}
	void DrawPoint(Vector2 p)
	{
		if (p.x >= 0 && p.y >= 0 && p.x < width && p.y < height)
		{
			SetPixel(p.x, p.y);
		}
	}
	void DrawLine_midlle(Vector2 p0, Vector2 p1)
	{
		float temp = (p0 - p1).Magnitude();
		if (temp < 2)
			return;

		Vector2 mid = p0 + (p1 - p0) / 2;
		DrawPoint(mid);
		DrawLine_midlle(p0, mid);
		DrawLine_midlle(mid, p1);
	}
	void DrawLine_Bresenham(Vector2 p0, Vector2 p1)
	{
		int x0 = (int)p0.x;
		int y0 = (int)p0.y;
		int x1 = (int)p1.x;
		int y1 = (int)p1.y;

		auto dx = abs(x1 - x0);
		auto dy = abs(y1 - y0);
		auto sx = (x0 < x1) ? 1 : -1;
		auto sy = (y0 < y1) ? 1 : -1;
		auto err = dx - dy;

		while (true)
		{
			DrawPoint(Vector2(x0, y0));

			if ((x0 == x1) && (y0 == y1))break;
			auto e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy; x0 += sx;
			}
			if (e2 < dx)
			{
				err += dx; y0 += sy;
			}
		}
	}

	void DrawWireTriangle(Vector2 p0, Vector2 p1, Vector2 p2)
	{
		DrawLine_Bresenham(p0, p1);
		DrawLine_Bresenham(p1, p2);
		DrawLine_Bresenham(p2, p0);
	}



	void DrawFillTriangle(Vector3 p1, Vector3 p2, Vector3 p3)
	{
		if (p1.y > p2.y)
		{
			auto temp = p2;
			p2 = p1;
			p1 = temp;
		}

		if (p2.y > p3.y)
		{
			auto temp = p2;
			p2 = p3;
			p3 = temp;
		}

		if (p1.y > p2.y)
		{
			auto temp = p2;
			p2 = p1;
			p1 = temp;
		}

		float dP1P2, dP1P3;


		if (p2.y - p1.y > 0)
			dP1P2 = (p2.x - p1.x) / (p2.y - p1.y);
		else
			dP1P2 = 0;

		if (p3.y - p1.y > 0)
			dP1P3 = (p3.x - p1.x) / (p3.y - p1.y);
		else
			dP1P3 = 0;

		// P1
		// -
		// -- 
		// - -
		// -  -
		// -   - P2
		// -  -
		// - -
		// -
		// P3
		if (dP1P2 > dP1P3)
		{
			for (auto y = (int)p1.y; y <= (int)p3.y; y++)
			{
				if (y < p2.y)
				{
					ProcessScanLine(y, p1, p3, p1, p2);
				}
				else
				{
					ProcessScanLine(y, p1, p3, p2, p3);
				}
			}
		}
		//       P1
		//        -
		//       -- 
		//      - -
		//     -  -
		// P2 -   - 
		//     -  -
		//      - -
		//        -
		//       P3
		else
		{
			for (auto y = (int)p1.y; y <= (int)p3.y; y++)
			{
				if (y < p2.y)
				{
					ProcessScanLine(y, p1, p2, p1, p3);
				}
				else
				{
					ProcessScanLine(y, p2, p3, p1, p3);
				}
			}
		}


	}

	void DrawFillTriangle(v2f p1, v2f p2, v2f p3)
	{
		if (!RemoveBackfaceTriangle(p1.pos, p2.pos, p3.pos))
		{
			return;
		}
		if (p1.pos.y > p2.pos.y)
		{
			auto temp = p2;
			p2 = p1;
			p1 = temp;
		}

		if (p2.pos.y > p3.pos.y)
		{
			auto temp = p2;
			p2 = p3;
			p3 = temp;
		}

		if (p1.pos.y > p2.pos.y)
		{
			auto temp = p2;
			p2 = p1;
			p1 = temp;
		}

		float dP1P2, dP1P3;


		if (p2.pos.y - p1.pos.y > 0)
			dP1P2 = (p2.pos.x - p1.pos.x) / (p2.pos.y - p1.pos.y);
		else
			dP1P2 = 0;

		if (p3.pos.y - p1.pos.y > 0)
			dP1P3 = (p3.pos.x - p1.pos.x) / (p3.pos.y - p1.pos.y);
		else
			dP1P3 = 0;

		// P1
		// -
		// -- 
		// - -
		// -  -
		// -   - P2
		// -  -
		// - -
		// -
		// P3
		if (dP1P2 > dP1P3)
		{
			for (auto y = (int)p1.pos.y; y <= (int)p3.pos.y; y++)
			{
				if (y < p2.pos.y)
				{
					ProcessScanLine(y, p1, p3, p1, p2);
				}
				else
				{
					ProcessScanLine(y, p1, p3, p2, p3);
				}
			}
		}
		//       P1
		//        -
		//       -- 
		//      - -
		//     -  -
		// P2 -   - 
		//     -  -
		//      - -
		//        -
		//       P3
		else
		{
			for (auto y = (int)p1.pos.y; y <= (int)p3.pos.y; y++)
			{
				if (y < p2.pos.y)
				{
					ProcessScanLine(y, p1, p2, p1, p3);
				}
				else
				{
					ProcessScanLine(y, p2, p3, p1, p3);
				}
			}
		}


	}


	Vector3 Project(Vector3 coord, Matrix4x4 transMat)
	{
		auto point = mf::TransformCoordinate(coord, transMat);

		auto x = point.x * width + width / 2.0f;
		auto y = -point.y * height + height / 2.0f;
		return Vector3(x, y, point.z);
	}

	//顶点着色器
	v2f VertexShader(a2v v, Matrix4x4 mvp, Matrix4x4 obj2world)
	{
		v2f out;

		auto point = v.vertex* mvp;
		auto x = point.x * width + width / 2.0f;
		auto y = -point.y * height + height / 2.0f;

		out.pos = Vector3(x, y, point.z);
		out.uv = v.texcoord;
		out.wPos = v.vertex* obj2world;
		out.wNormal = v.normal* obj2world;
		return out;
	}

	Color FragmentShader(v2f in)
	{
		Vector3 lightColor(1.0f, 1.0f, 0.8f);
		Vector3 lightDir(1.0f, 1.0f, -1.0f);
		Vector3 normal = mf::Normalize(in.wNormal);

		float ndotl = mf::Dot(normal, lightDir);

		float diff = ndotl*0.5 + 0.5;
		Color tex = tex2D(texture0, in.uv);
		Color temp = Color(1.0f)*diff*tex;
		return temp;
	}


	void Render(Model *model, Texture *tex)
	{
		Clear(0, 0, 0, 0);


		texture0 = tex;
		mf::Matrix4x4 viewMatrix = camera->GetViewMatrix();
		mf::Matrix4x4 projection = camera->GetProjectionMatrix();
		mf::Matrix4x4 worldMatrix = model->transform->ToWorldMatrix();

		mf::Matrix4x4 mvp = worldMatrix*viewMatrix*projection;
		SetColor(1, 1, 1, 1);

		Mesh* m = model->GetMesh();
		for (int i = 0; i < m->vertices.size(); i += 3)
		{
			a2v a1 = { m->vertices[i].vertex ,m->vertices[i].normal ,m->vertices[i].texcoord };
			a2v a2 = { m->vertices[i + 1].vertex ,m->vertices[i + 1].normal ,m->vertices[i + 1].texcoord };
			a2v a3 = { m->vertices[i + 2].vertex ,m->vertices[i + 2].normal ,m->vertices[i + 2].texcoord };

			v2f in1 = VertexShader(a1, mvp, worldMatrix);
			v2f in2 = VertexShader(a2, mvp, worldMatrix);
			v2f in3 = VertexShader(a3, mvp, worldMatrix);

			/*auto p1 = Project(m->vertices[i].vertex, mvp);
			auto p2 = Project(m->vertices[i+1].vertex, mvp);
			auto p3 = Project(m->vertices[i+2].vertex, mvp);
			DrawFillTriangle(p1, p2, p3);*/
			DrawFillTriangle(in1, in2, in3);
			//DrawWireTriangle(Vector2(point.x, point.y), Vector2(point1.x, point1.y), Vector2(point2.x, point2.y));
		}


	}


	void RenderTexture(Texture *tex, int width, int height)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{

				int pos = (j + i * tex->width) * 4;
				float b = tex->buffer[pos] / 255.0f;
				float g = tex->buffer[pos + 1] / 255.0f;
				float r = tex->buffer[pos + 2] / 255.0f;
				float a = tex->buffer[pos + 3] / 255.0f;

				SetColor(r, g, b, a);
				DrawPoint(j, i);
			}
		}
	}


	~Device()
	{
		delete[] colorBuffer;
		colorBuffer = nullptr;
		delete[] depthBuffer;
		depthBuffer = nullptr;

		delete camera;
		camera = nullptr;
		delete texture0;
		texture0 = nullptr;
	}

private:
	int width;
	int height;
	Camera *camera;
	BYTE *colorBuffer;
	float *depthBuffer;
	Color brushColor;
	Texture *texture0;
private:
	void SetPixel(int x, int y)
	{
		int index4 = (x + y * width) * 4;
		colorBuffer[index4] = (BYTE)(brushColor.b * 255);
		colorBuffer[index4 + 1] = (BYTE)(brushColor.g * 255);
		colorBuffer[index4 + 2] = (BYTE)(brushColor.r * 255);
		colorBuffer[index4 + 3] = (BYTE)(brushColor.a * 255);


	}

	//深度测试
	bool Test(int x, int y, float z)
	{
		if (x < 0 || x >= camera->width || y < 0 || y >= camera->height)//裁剪区域
		{
			return false;
		}
		int index = (x + y * width);
		if (depthBuffer[index] > z)
		{
			depthBuffer[index] = z;//深度写入
			return true;
		}
		else
		{
			return false;
		}
	}

	void ProcessScanLine(int y, Vector3 pa, Vector3 pb, Vector3 pc, Vector3 pd)
	{

		auto gradient1 = pa.y != pb.y ? (y - pa.y) / (pb.y - pa.y) : 1;
		auto gradient2 = pc.y != pd.y ? (y - pc.y) / (pd.y - pc.y) : 1;

		int sx = (int)mf::lerp(pa.x, pb.x, gradient1);
		int ex = (int)mf::lerp(pc.x, pd.x, gradient2);


		float z1 = mf::lerp(pa.z, pb.z, gradient1);
		float z2 = mf::lerp(pc.z, pd.z, gradient2);


		for (auto x = sx; x < ex; x++)
		{
			float gradient = (x - sx) / (float)(ex - sx);

			auto z = mf::lerp(z1, z2, gradient);
			if (Test(x, y, z))
			{
				DrawPoint(x, y);
			}
		}
	}

	void ProcessScanLine(int y, v2f pa, v2f pb, v2f pc, v2f pd)
	{

		auto gradient1 = pa.pos.y != pb.pos.y ? (y - pa.pos.y) / (pb.pos.y - pa.pos.y) : 1;
		auto gradient2 = pc.pos.y != pd.pos.y ? (y - pc.pos.y) / (pd.pos.y - pc.pos.y) : 1;

		int sx = (int)mf::lerp(pa.pos.x, pb.pos.x, gradient1);
		int ex = (int)mf::lerp(pc.pos.x, pd.pos.x, gradient2);


		float z1 = mf::lerp(pa.pos.z, pb.pos.z, gradient1);
		float z2 = mf::lerp(pc.pos.z, pd.pos.z, gradient2);

		auto swpl = mf::Lerp(pa.wPos, pb.wPos, gradient1);
		auto ewpl = mf::Lerp(pc.wPos, pd.wPos, gradient2);

		auto snl = mf::Lerp(pa.wNormal, pb.wNormal, gradient1);
		auto enl = mf::Lerp(pc.wNormal, pd.wNormal, gradient2);

		auto suvl = mf::Lerp(pa.uv, pb.uv, gradient1);
		auto euvl = mf::Lerp(pc.uv, pd.uv, gradient2);

		for (auto x = sx; x < ex; x++)
		{
			float gradient = (x - sx) / (float)(ex - sx);

			auto z = mf::lerp(z1, z2, gradient);
			auto wpos = mf::Lerp(swpl, ewpl, gradient);
			auto normal = mf::Lerp(snl, enl, gradient);
			auto uv = mf::Lerp(suvl, euvl, gradient);
			v2f in = { Vector3(x,y,z),normal,wpos,uv };
			if (Test(x, y, z))
			{
				//std::cout << uv.x << "  " << uv.y << std::endl;
				SetColor(FragmentShader(in));
				DrawPoint(x, y);
			}
		}
	}

	//背面剔除
	bool RemoveBackfaceTriangle(Vector3 pa, Vector3 pb, Vector3 pc)
	{
		Vector3 a = pb - pa;
		Vector3 b = pc - pa;

		Vector3 normal = mf::Cross(b, a);
		float dot = mf::Dot(normal, -camera->ZFront);
		if (dot < 0)
		{
			return false;
		}
		else
		{
			return true;
		}

	}
};
