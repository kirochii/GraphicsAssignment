
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float cameraYaw = 0.0f;    // left/right rotation (around Y-axis)
float cameraPitch = 0.0f;  // up/down rotation (around X-axis)
float rotationSpeed = 5.0f; // degrees per key press

#define PI 3.14159265359

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

			// Arrow Keys
		case VK_UP:
			cameraPitch -= rotationSpeed;
			break;
		case VK_DOWN:
			cameraPitch += rotationSpeed;
			break;
		case VK_LEFT:
			cameraYaw -= rotationSpeed;
			break;
		case VK_RIGHT:
			cameraYaw += rotationSpeed;
			break;

			// WASD keys
		case 'W':
			cameraPitch -= rotationSpeed;
			break;
		case 'S':
			cameraPitch += rotationSpeed;
			break;
		case 'A':
			cameraYaw -= rotationSpeed;
			break;
		case 'D':
			cameraYaw += rotationSpeed;
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void guide() {
    //guide measurement
    glBegin(GL_LINES);
    glVertex3f(-0.9, 0.8, 0);
    glVertex3f(0.9, 0.8, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, 0.6, 0);
    glVertex3f(0.9, 0.6, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, 0.4, 0);
    glVertex3f(0.9, 0.4, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, 0.2, 0);
    glVertex3f(0.9, 0.2, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, 0, 0);
    glVertex3f(0.9, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, -0.2, 0);
    glVertex3f(0.9, -0.2, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, -0.4, 0);
    glVertex3f(0.9, -0.4, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, -0.6, 0);
    glVertex3f(0.9, -0.6, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.9, -0.8, 0);
    glVertex3f(0.9, -0.8, 0);
    glEnd();
}

void body() {
    //belt (code start bottom right, clockwise), physical rendering start middle to left
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(0, 0.19, -0.07);
    glVertex3f(0.04, 0.19, -0.07);
    glVertex3f(0.07, 0.19, -0.05);
    glVertex3f(0.09, 0.19, -0.03);
    glVertex3f(0.09, 0.19, 0.03);
    glVertex3f(0.07, 0.19, 0.05);
    glVertex3f(0.04, 0.19, 0.07);
    glVertex3f(0, 0.19, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.04, 0.24, 0.07);
    glVertex3f(0, 0.24, 0.07);
    glVertex3f(0, 0.19, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.07, 0.24, 0.05);
    glVertex3f(-0.04, 0.24, 0.07);
    glVertex3f(-0.04, 0.19, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.09, 0.24, 0.03);
    glVertex3f(-0.07, 0.24, 0.05);
    glVertex3f(-0.07, 0.19, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.09, 0.24, -0.03);
    glVertex3f(-0.09, 0.24, 0.03);
    glVertex3f(-0.09, 0.19, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.19, -0.07);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(-0.04, 0.24, -0.07);
    glVertex3f(0, 0.24, -0.07);
    glVertex3f(0, 0.19, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.07, 0.24, -0.05);
    glVertex3f(-0.04, 0.24, -0.07);
    glVertex3f(-0.04, 0.19, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.09, 0.24, -0.03);
    glVertex3f(-0.07, 0.24, -0.05);
    glVertex3f(-0.07, 0.19, -0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(0.04, 0.19, 0.07);
    glVertex3f(0.04, 0.24, 0.07);
    glVertex3f(0, 0.24, 0.07);
    glVertex3f(0, 0.19, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.19, 0.07);
    glVertex3f(0.07, 0.19, 0.05);
    glVertex3f(0.07, 0.24, 0.05);
    glVertex3f(0.04, 0.24, 0.07);
    glVertex3f(0.04, 0.19, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.07, 0.19, 0.05);
    glVertex3f(0.09, 0.19, 0.03);
    glVertex3f(0.09, 0.24, 0.03);
    glVertex3f(0.07, 0.24, 0.05);
    glVertex3f(0.07, 0.19, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.09, 0.19, 0.03);
    glVertex3f(0.09, 0.19, -0.03);
    glVertex3f(0.09, 0.24, -0.03);
    glVertex3f(0.09, 0.24, 0.03);
    glVertex3f(0.09, 0.19, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.19, -0.07);
    glVertex3f(0.04, 0.19, -0.07);
    glVertex3f(0.04, 0.24, -0.07);
    glVertex3f(0, 0.24, -0.07);
    glVertex3f(0, 0.19, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.19, -0.07);
    glVertex3f(0.07, 0.19, -0.05);
    glVertex3f(0.07, 0.24, -0.05);
    glVertex3f(0.04, 0.24, -0.07);
    glVertex3f(0.04, 0.19, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.07, 0.19, -0.05);
    glVertex3f(0.09, 0.19, -0.03);
    glVertex3f(0.09, 0.24, -0.03);
    glVertex3f(0.07, 0.24, -0.05);
    glVertex3f(0.07, 0.19, -0.05);
    glEnd();

    //body 1st layer (code start bottom right, clockwise), physical rendering start middle to left
    glBegin(GL_QUADS);
    glVertex3f(0, 0.24, 0.07);
    glVertex3f(-0.04, 0.24, 0.07);
    glVertex3f(-0.05, 0.29, 0.09);
    glVertex3f(0, 0.29, 0.09);
    glVertex3f(0, 0.24, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.24, 0.07);
    glVertex3f(-0.07, 0.24, 0.05);
    glVertex3f(-0.12, 0.29, 0.05);
    glVertex3f(-0.05, 0.29, 0.09);
    glVertex3f(-0.04, 0.24, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.07, 0.24, 0.05);
    glVertex3f(-0.09, 0.24, 0.03);
    glVertex3f(-0.12, 0.29, 0.05);
    glVertex3f(-0.07, 0.24, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.09, 0.24, 0.03);
    glVertex3f(-0.09, 0.24, -0.03);
    glVertex3f(-0.12, 0.29, -0.05);
    glVertex3f(-0.12, 0.29, 0.05);
    glVertex3f(-0.09, 0.24, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.24, 0.07);
    glVertex3f(0.04, 0.24, 0.07);
    glVertex3f(0.05, 0.29, 0.09);
    glVertex3f(0, 0.29, 0.09);
    glVertex3f(0, 0.24, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.24, 0.07);
    glVertex3f(0.07, 0.24, 0.05);
    glVertex3f(0.12, 0.29, 0.05);
    glVertex3f(0.05, 0.29, 0.09);
    glVertex3f(0.04, 0.24, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.07, 0.24, 0.05);
    glVertex3f(0.09, 0.24, 0.03);
    glVertex3f(0.12, 0.29, 0.05);
    glVertex3f(0.07, 0.24, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.09, 0.24, 0.03);
    glVertex3f(0.09, 0.24, -0.03);
    glVertex3f(0.12, 0.29, -0.05);
    glVertex3f(0.12, 0.29, 0.05);
    glVertex3f(0.09, 0.24, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.24, -0.07);
    glVertex3f(-0.04, 0.24, -0.07);
    glVertex3f(-0.05, 0.29, -0.09);
    glVertex3f(0, 0.29, -0.09);
    glVertex3f(0, 0.24, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.24, -0.07);
    glVertex3f(-0.07, 0.24, -0.05);
    glVertex3f(-0.12, 0.29, -0.05);
    glVertex3f(-0.05, 0.29, -0.09);
    glVertex3f(-0.04, 0.24, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.07, 0.24, -0.05);
    glVertex3f(-0.09, 0.24, -0.03);
    glVertex3f(-0.12, 0.29, -0.05);
    glVertex3f(-0.07, 0.24, -0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.24, -0.07);
    glVertex3f(0.04, 0.24, -0.07);
    glVertex3f(0.05, 0.29, -0.09);
    glVertex3f(0, 0.29, -0.09);
    glVertex3f(0, 0.24, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.24, -0.07);
    glVertex3f(0.07, 0.24, -0.05);
    glVertex3f(0.12, 0.29, -0.05);
    glVertex3f(0.05, 0.29, -0.09);
    glVertex3f(0.04, 0.24, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.07, 0.24, -0.05);
    glVertex3f(0.09, 0.24, -0.03);
    glVertex3f(0.12, 0.29, -0.05);
    glVertex3f(0.07, 0.24, -0.05);
    glEnd();

    //body 2nd layer (code start bottom right, clockwise), physical rendering start middle to left
    glBegin(GL_QUADS);
    glVertex3f(0, 0.29, 0.09);
    glVertex3f(-0.05, 0.29, 0.09);
    glVertex3f(-0.05, 0.36, 0.07);
    glVertex3f(0, 0.36, 0.07);
    glVertex3f(0, 0.29, 0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.05, 0.29, 0.09);
    glVertex3f(-0.12, 0.29, 0.05);
    glVertex3f(-0.10, 0.37, 0.06);
    glVertex3f(-0.05, 0.36, 0.07);
    glVertex3f(-0.05, 0.29, 0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.12, 0.29, 0.05);
    glVertex3f(-0.12, 0.29, -0.05);
    glVertex3f(-0.10, 0.37, -0.06);
    glVertex3f(-0.10, 0.37, 0.06);
    glVertex3f(-0.12, 0.29, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.29, 0.09);
    glVertex3f(0.05, 0.29, 0.09);
    glVertex3f(0.05, 0.36, 0.07);
    glVertex3f(0, 0.36, 0.07);
    glVertex3f(0, 0.29, 0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.29, 0.09);
    glVertex3f(0.12, 0.29, 0.05);
    glVertex3f(0.10, 0.37, 0.06);
    glVertex3f(0.05, 0.36, 0.07);
    glVertex3f(0.05, 0.29, 0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.12, 0.29, 0.05);
    glVertex3f(0.12, 0.29, -0.05);
    glVertex3f(0.10, 0.37, -0.06);
    glVertex3f(0.10, 0.37, 0.06);
    glVertex3f(0.12, 0.29, 0.05);
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(0, 0.29, -0.09);
    glVertex3f(-0.05, 0.29, -0.09);
    glVertex3f(-0.05, 0.36, -0.07);
    glVertex3f(0, 0.36, -0.07);
    glVertex3f(0, 0.29, -0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.05, 0.29, -0.09);
    glVertex3f(-0.12, 0.29, -0.05);
    glVertex3f(-0.10, 0.37, -0.06);
    glVertex3f(-0.05, 0.36, -0.07);
    glVertex3f(-0.05, 0.29, -0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.29, -0.09);
    glVertex3f(0.05, 0.29, -0.09);
    glVertex3f(0.05, 0.36, -0.07);
    glVertex3f(0, 0.36, -0.07);
    glVertex3f(0, 0.29, -0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.29, -0.09);
    glVertex3f(0.12, 0.29, -0.05);
    glVertex3f(0.10, 0.37, -0.06);
    glVertex3f(0.05, 0.36, -0.07);
    glVertex3f(0.05, 0.29, -0.09);
    glEnd();

    //body 3rd layer (code start bottom right, clockwise), physical rendering start middle to left
    glBegin(GL_QUADS);
    glVertex3f(0, 0.36, 0.07);
    glVertex3f(-0.05, 0.36, 0.07);
    glVertex3f(-0.06, 0.45, 0.07);
    glVertex3f(0, 0.45, 0.07);
    glVertex3f(0, 0.36, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.05, 0.36, 0.07);
    glVertex3f(-0.10, 0.37, 0.06);
    glVertex3f(-0.13, 0.45, 0.04);
    glVertex3f(-0.06, 0.45, 0.07);
    glVertex3f(-0.05, 0.36, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.10, 0.37, 0.06);
    glVertex3f(-0.10, 0.37, -0.06);
    glVertex3f(-0.13, 0.45, -0.04);
    glVertex3f(-0.13, 0.45, 0.04);
    glVertex3f(-0.10, 0.37, 0.06);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.36, 0.07);
    glVertex3f(0.05, 0.36, 0.07);
    glVertex3f(0.06, 0.45, 0.07);
    glVertex3f(0, 0.45, 0.07);
    glVertex3f(0, 0.36, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.36, 0.07);
    glVertex3f(0.10, 0.37, 0.06);
    glVertex3f(0.13, 0.45, 0.04);
    glVertex3f(0.06, 0.45, 0.07);
    glVertex3f(0.05, 0.36, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.10, 0.37, 0.06);
    glVertex3f(0.10, 0.37, -0.06);
    glVertex3f(0.13, 0.45, -0.04);
    glVertex3f(0.13, 0.45, 0.04);
    glVertex3f(0.10, 0.37, 0.06);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.36, -0.07);
    glVertex3f(-0.05, 0.36, -0.07);
    glVertex3f(-0.06, 0.45, -0.07);
    glVertex3f(0, 0.45, -0.07);
    glVertex3f(0, 0.36, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.05, 0.36, -0.07);
    glVertex3f(-0.10, 0.37, -0.06);
    glVertex3f(-0.13, 0.45, -0.04);
    glVertex3f(-0.06, 0.45, -0.07);
    glVertex3f(-0.05, 0.36, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.36, -0.07);
    glVertex3f(0.05, 0.36, -0.07);
    glVertex3f(0.06, 0.45, -0.07);
    glVertex3f(0, 0.45, -0.07);
    glVertex3f(0, 0.36, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.36, -0.07);
    glVertex3f(0.10, 0.37, -0.06);
    glVertex3f(0.13, 0.45, -0.04);
    glVertex3f(0.06, 0.45, -0.07);
    glVertex3f(0.05, 0.36, -0.07);
    glEnd();


    //body 4th layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.45, 0.07);
    glVertex3f(-0.06, 0.45, 0.07);
    glVertex3f(-0.08, 0.52, 0.04);
    glVertex3f(0, 0.53, 0.05);
    glVertex3f(0, 0.45, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.06, 0.45, 0.07);
    glVertex3f(-0.13, 0.45, 0.04);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.08, 0.52, 0.04);
    glVertex3f(-0.06, 0.45, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0, 0.45, 0.07);
    glVertex3f(0.06, 0.45, 0.07);
    glVertex3f(0.08, 0.52, 0.04);
    glVertex3f(-0, 0.53, 0.05);
    glVertex3f(-0, 0.45, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.06, 0.45, 0.07);
    glVertex3f(0.13, 0.45, 0.04);
    glVertex3f(0.16, 0.52, 0.03);
    glVertex3f(0.08, 0.52, 0.04);
    glVertex3f(0.06, 0.45, 0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.45, -0.07);
    glVertex3f(-0.06, 0.45, -0.07);
    glVertex3f(-0.08, 0.52, -0.09);
    glVertex3f(0, 0.52, -0.11);
    glVertex3f(0, 0.45, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.06, 0.45, -0.07);
    glVertex3f(-0.13, 0.45, -0.04);
    glVertex3f(-0.13, 0.52, -0.07);
    glVertex3f(-0.08, 0.52, -0.09);
    glVertex3f(-0.06, 0.45, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.13, 0.45, 0.04);
    glVertex3f(-0.13, 0.45, -0.04);
    glVertex3f(-0.13, 0.52, -0.07);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.13, 0.45, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.45, -0.07);
    glVertex3f(0.06, 0.45, -0.07);
    glVertex3f(0.08, 0.52, -0.09);
    glVertex3f(0, 0.52, -0.11);
    glVertex3f(0, 0.45, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.06, 0.45, -0.07);
    glVertex3f(0.13, 0.45, -0.04);
    glVertex3f(0.13, 0.52, -0.07);
    glVertex3f(0.08, 0.52, -0.09);
    glVertex3f(0.06, 0.45, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.13, 0.45, 0.04);
    glVertex3f(0.13, 0.45, -0.04);
    glVertex3f(0.13, 0.52, -0.07);
    glVertex3f(0.16, 0.52, 0.03);
    glVertex3f(0.13, 0.45, 0.04);
    glEnd();

    //body 5th layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.53, 0.05);
    glVertex3f(-0.08, 0.52, 0.04);
    glVertex3f(-0.04, 0.56, 0.01);
    glVertex3f(0, 0.53, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.08, 0.52, 0.04);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.13, 0.54, 0.0);
    glVertex3f(-0.04, 0.56, 0.01);
    glVertex3f(-0.08, 0.52, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.13, 0.52, -0.07);
    glVertex3f(-0.13, 0.54, -0.04);
    glVertex3f(-0.13, 0.54, 0.0);
    glVertex3f(-0.16, 0.52, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.53, 0.05);
    glVertex3f(0.08, 0.52, 0.04);
    glVertex3f(0.04, 0.56, 0.01);
    glVertex3f(0, 0.53, 0.05);
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(0.08, 0.52, 0.04);
    glVertex3f(0.16, 0.52, 0.03);
    glVertex3f(0.13, 0.54, 0.0);
    glVertex3f(0.04, 0.56, 0.01);
    glVertex3f(0.08, 0.52, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.16, 0.52, 0.03);
    glVertex3f(0.13, 0.52, -0.07);
    glVertex3f(0.13, 0.54, -0.04);
    glVertex3f(0.13, 0.54, 0.0);
    glVertex3f(0.16, 0.52, 0.03);
    glEnd();

    //5th layer back
    glBegin(GL_QUADS);
    glVertex3f(0, 0.52, -0.11);
    glVertex3f(-0.08, 0.52, -0.09);
    glVertex3f(-0.08, 0.56, -0.06);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(0, 0.52, -0.11);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.08, 0.52, -0.09);
    glVertex3f(-0.13, 0.52, -0.07);
    glVertex3f(-0.13, 0.54, -0.04);
    glVertex3f(-0.08, 0.56, -0.06);
    glVertex3f(-0.08, 0.52, -0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.52, -0.11);
    glVertex3f(0.08, 0.52, -0.09);
    glVertex3f(0.08, 0.56, -0.06);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(0, 0.52, -0.11);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.08, 0.52, -0.09);
    glVertex3f(0.13, 0.52, -0.07);
    glVertex3f(0.13, 0.54, -0.04);
    glVertex3f(0.08, 0.56, -0.06);
    glVertex3f(0.08, 0.52, -0.09);
    glEnd();


    //collar
    glBegin(GL_QUADS);
    glVertex3f(0, 0.53, 0.05);
    glVertex3f(-0.04, 0.56, 0.01);
    glVertex3f(-0.04, 0.6, 0.01);
    glVertex3f(0, 0.53, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.53, 0.05);
    glVertex3f(0.04, 0.56, 0.01);
    glVertex3f(0.04, 0.6, 0.01);
    glVertex3f(0, 0.53, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.56, 0.01);
    glVertex3f(-0.04, 0.56, -0.04);
    glVertex3f(-0.04, 0.6, -0.04);
    glVertex3f(-0.04, 0.6, 0.01);
    glVertex3f(-0.04, 0.56, 0.01);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.56, 0.01);
    glVertex3f(0.04, 0.56, -0.04);
    glVertex3f(0.04, 0.6, -0.04);
    glVertex3f(0.04, 0.6, 0.01);
    glVertex3f(0.04, 0.56, 0.01);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.56, -0.04);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(0, 0.6, -0.07);
    glVertex3f(-0.04, 0.6, -0.04);
    glVertex3f(-0.04, 0.56, -0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.56, -0.04);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(0, 0.6, -0.07);
    glVertex3f(0.04, 0.6, -0.04);
    glVertex3f(0.04, 0.56, -0.04);
    glEnd();

    //top shoulder
    glBegin(GL_QUADS);
    glVertex3f(-0.08, 0.56, -0.06);
    glVertex3f(-0.04, 0.56, -0.04);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(-0.08, 0.56, -0.06);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.08, 0.56, -0.06);
    glVertex3f(0.04, 0.56, -0.04);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(0.08, 0.56, -0.06);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(-0.04, 0.56, 0.01);
    glVertex3f(-0.13, 0.54, 0.0);
    glVertex3f(-0.13, 0.54, -0.04);
    glVertex3f(-0.08, 0.56, -0.06);
    glVertex3f(-0.04, 0.56, -0.04);
    glVertex3f(-0.04, 0.56, 0.01);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.04, 0.56, 0.01);
    glVertex3f(0.13, 0.54, 0.0);
    glVertex3f(0.13, 0.54, -0.04);
    glVertex3f(0.08, 0.56, -0.06);
    glVertex3f(0.04, 0.56, -0.04);
    glVertex3f(0.04, 0.56, 0.01);
    glEnd();

    //body
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.53, 0.05);
    glVertex3f(-0.04, 0.56, 0.01);
    glVertex3f(-0.04, 0.56, -0.04);
    glVertex3f(0, 0.56, -0.07);
    glVertex3f(0.04, 0.56, -0.04);
    glVertex3f(0.04, 0.56, 0.01);
    glVertex3f(0, 0.53, 0.05);
    glEnd();


}

void neck() {
    float radius = 0.03;
    float height = 0.15;
    int slices = 6;
    float zOffset = -0.02;
    float yOffset = 0.50;

    float angleStep = 2.0f * PI / slices;

    // --- Side Surface ---
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle) + zOffset;  // Apply Z offset

        glNormal3f(cos(angle), 0.0f, sin(angle));
        glVertex3f(x, yOffset, z);                  // Bottom vertex
        glVertex3f(x, yOffset + height, z);         // Top vertex
    }
    glEnd();

    // --- Top Cap ---
    glBegin(GL_QUADS);
    for (int i = 0; i < slices; ++i) {
        float angle0 = i * angleStep;
        float angle1 = (i + 1) * angleStep;

        float x0 = radius * cos(angle0);
        float z0 = radius * sin(angle0) + zOffset;
        float x1 = radius * cos(angle1);
        float z1 = radius * sin(angle1) + zOffset;

        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, yOffset + height, zOffset);
        glVertex3f(x0, yOffset + height, z0);
        glVertex3f(x1, yOffset + height, z1);
        glVertex3f(0.0f, yOffset + height, zOffset);
    }
    glEnd();

    // --- Bottom Cap ---
    glBegin(GL_QUADS);
    for (int i = 0; i < slices; ++i) {
        float angle0 = i * angleStep;
        float angle1 = (i + 1) * angleStep;

        float x0 = radius * cos(angle0);
        float z0 = radius * sin(angle0) + zOffset;
        float x1 = radius * cos(angle1);
        float z1 = radius * sin(angle1) + zOffset;

        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, yOffset, zOffset);
        glVertex3f(x1, yOffset, z1);
        glVertex3f(x0, yOffset, z0);
        glVertex3f(0.0f, yOffset, zOffset);
    }
    glEnd();
}

void head() {

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1.0f, 0.0f, 0.0f);

    guide();
	body();
    neck();

    glColor3f(1.0f, 1.0f, 1.0f);
    head();

	glFlush();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------