
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

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
    //1st layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.6, 0.05);
    glVertex3f(-0.02, 0.6, 0.05);
    glVertex3f(-0.04, 0.63, 0.06);
    glVertex3f(0, 0.63, 0.06);
    glVertex3f(0, 0.6, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.02, 0.6, 0.05);
    glVertex3f(-0.06, 0.63, 0.04);
    glVertex3f(-0.04, 0.63, 0.06);
    glVertex3f(-0.02, 0.6, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.02, 0.6, 0.05);
    glVertex3f(-0.03, 0.61, 0.01);
    glVertex3f(-0.06, 0.64, 0.01);
    glVertex3f(-0.06, 0.63, 0.04);
    glVertex3f(-0.02, 0.6, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.03, 0.61, 0.01);
    glVertex3f(-0.03, 0.62, -0.01);
    glVertex3f(-0.06, 0.65, -0.02);
    glVertex3f(-0.06, 0.64, 0.01);
    glVertex3f(-0.03, 0.61, 0.01);
    glEnd();

    //2nd layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.63, 0.06);
    glVertex3f(-0.04, 0.63, 0.06);
    glVertex3f(-0.04, 0.65, 0.065);
    glVertex3f(0, 0.65, 0.065);
    glVertex3f(0, 0.63, 0.06);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.63, 0.06);
    glVertex3f(-0.06, 0.63, 0.04);
    glVertex3f(-0.07, 0.66, 0.03);
    glVertex3f(-0.04, 0.65, 0.065);
    glVertex3f(-0.04, 0.63, 0.06);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.06, 0.63, 0.04);
    glVertex3f(-0.06, 0.64, 0.01);
    glVertex3f(-0.06, 0.65, -0.02);
    glVertex3f(-0.07, 0.66, -0.02);
    glVertex3f(-0.07, 0.66, 0.03);
    glVertex3f(-0.06, 0.63, 0.04);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.06, 0.65, -0.02);
    glVertex3f(-0.07, 0.66, -0.02);
    glVertex3f(-0.05, 0.65, -0.06);
    glVertex3f(-0.06, 0.66, -0.07);
    glVertex3f(-0.015, 0.65, -0.075);
    glVertex3f(-0.03, 0.66, -0.085);
    glVertex3f(0, 0.65, -0.07);
    glVertex3f(0, 0.66, -0.09);
    glEnd();

    //3rd layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.65, 0.065);
    glVertex3f(-0.04, 0.65, 0.065);
    glVertex3f(-0.01, 0.67, 0.04);
    glVertex3f(0, 0.67, 0.04);
    glVertex3f(0, 0.65, 0.065);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.65, 0.065);
    glVertex3f(-0.05, 0.66, 0.03);
    glVertex3f(-0.01, 0.67, 0.04);
    glVertex3f(-0.04, 0.65, 0.065);
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.65, 0.065);
    glVertex3f(-0.07, 0.66, 0.03);
    glVertex3f(-0.05, 0.66, 0.03);
    glVertex3f(-0.04, 0.65, 0.065);
    glEnd();


    //4th layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.67, 0.04);
    glVertex3f(-0.01, 0.67, 0.04);
    glVertex3f(-0.01, 0.7, 0.045);
    glVertex3f(0, 0.7, 0.045);
    glVertex3f(0, 0.67, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.01, 0.67, 0.04);
    glVertex3f(-0.05, 0.66, 0.03);
    glVertex3f(-0.05, 0.7, 0.03);
    glVertex3f(-0.01, 0.7, 0.045);
    glVertex3f(-0.01, 0.67, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.05, 0.66, 0.03);
    glVertex3f(-0.07, 0.66, 0.03);
    glVertex3f(-0.07, 0.7, 0.03);
    glVertex3f(-0.05, 0.7, 0.03);
    glVertex3f(-0.05, 0.66, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.07, 0.66, 0.03);
    glVertex3f(-0.07, 0.66, -0.02);
    glVertex3f(-0.08, 0.7, -0.02);
    glVertex3f(-0.07, 0.7, 0.03);
    glVertex3f(-0.07, 0.66, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.07, 0.66, -0.02);
    glVertex3f(-0.06, 0.66, -0.07);
    glVertex3f(-0.06, 0.7, -0.07);
    glVertex3f(-0.08, 0.7, -0.02);
    glVertex3f(-0.07, 0.66, -0.02);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.06, 0.66, -0.07);
    glVertex3f(-0.03, 0.66, -0.085);
    glVertex3f(-0.03, 0.7, -0.09);
    glVertex3f(-0.06, 0.7, -0.07);
    glVertex3f(-0.06, 0.66, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.03, 0.66, -0.085);
    glVertex3f(0, 0.66, -0.09);
    glVertex3f(0, 0.7, -0.1);
    glVertex3f(-0.03, 0.7, -0.09);
    glVertex3f(-0.03, 0.66, -0.085);
    glEnd();


    //5th layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.7, 0.045);
    glVertex3f(-0.01, 0.7, 0.045);
    glVertex3f(-0.02, 0.72, 0.045);
    glVertex3f(0, 0.72, 0.045);
    glVertex3f(0, 0.7, 0.045);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.01, 0.7, 0.045);
    glVertex3f(-0.02, 0.72, 0.045);
    glVertex3f(-0.05, 0.7, 0.03);
    glVertex3f(-0.04, 0.72, 0.03);
    glVertex3f(-0.07, 0.7, 0.03);
    glVertex3f(-0.07, 0.72, 0.03);
    glVertex3f(-0.08, 0.7, -0.02);
    glVertex3f(-0.08, 0.72, -0.02);
    glVertex3f(-0.06, 0.7, -0.07);
    glVertex3f(-0.06, 0.72, -0.07);
    glVertex3f(-0.03, 0.7, -0.09);
    glVertex3f(-0.03, 0.72, -0.09);
    glVertex3f(0, 0.7, -0.1);
    glVertex3f(0, 0.72, -0.1);
    glEnd();
    

    //6th layer
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.72, 0.045);
    glVertex3f(0, 0.76, 0.035);
    glVertex3f(-0.02, 0.72, 0.045);
    glVertex3f(-0.02, 0.76, 0.035);
    glVertex3f(-0.04, 0.72, 0.03);
    glVertex3f(-0.04, 0.76, 0.03);
    glVertex3f(-0.07, 0.72, 0.03);
    glVertex3f(-0.055, 0.76, 0.02);
    glVertex3f(-0.08, 0.72, -0.02);
    glVertex3f(-0.07, 0.76, -0.02);
    glVertex3f(-0.06, 0.72, -0.07);
    glVertex3f(-0.05, 0.76, -0.07);
    glVertex3f(-0.03, 0.72, -0.09);
    glVertex3f(-0.03, 0.76, -0.085);
    glVertex3f(0, 0.72, -0.1);
    glVertex3f(0, 0.76, -0.09);
    glEnd();

    //7th layer
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.76, 0.035);
    glVertex3f(0, 0.79, 0);
    glVertex3f(-0.02, 0.76, 0.035);
    glVertex3f(-0.02, 0.79, 0);
    glVertex3f(-0.04, 0.76, 0.03);
    glVertex3f(-0.035, 0.79, 0);
    glVertex3f(-0.055, 0.76, 0.02);
    glVertex3f(-0.04, 0.79, 0);
    glVertex3f(-0.07, 0.76, -0.02);
    glVertex3f(-0.035, 0.79, -0.02);
    glVertex3f(-0.05, 0.76, -0.07);
    glVertex3f(-0.035, 0.79, -0.05);
    glVertex3f(-0.03, 0.76, -0.085);
    glVertex3f(-0.03, 0.79, -0.06);
    glVertex3f(0, 0.76, -0.09);
    glVertex3f(0, 0.79, -0.06);
    glEnd();

    //8th layer
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0.8, -0.03);
    glVertex3f(0, 0.79, 0);
    glVertex3f(-0.02, 0.79, 0);
    glVertex3f(-0.035, 0.79, 0);
    glVertex3f(-0.04, 0.79, 0);
    glVertex3f(-0.035, 0.79, -0.02);
    glVertex3f(-0.035, 0.79, -0.05);
    glVertex3f(-0.03, 0.79, -0.06);
    glVertex3f(0, 0.79, -0.06);
    glEnd();

    //ear
    glBegin(GL_POLYGON);
    glVertex3f(-0.07, 0.66, -0.02);
    glVertex3f(-0.07, 0.66, -0.04);
    glVertex3f(-0.09, 0.68, -0.05);
    glVertex3f(-0.09, 0.69, -0.05);
    glVertex3f(-0.09, 0.7, -0.04);
    glVertex3f(-0.09, 0.7, -0.03);
    glVertex3f(-0.075, 0.68, -0.02);
    glVertex3f(-0.07, 0.66, -0.02);
    glEnd();

    //bottom
    glBegin(GL_POLYGON);
    glVertex3f(-0.06, 0.65, -0.02);
    glVertex3f(-0.05, 0.65, -0.06);
    glVertex3f(-0.015, 0.65, -0.075);
    glVertex3f(0, 0.65, -0.07);
    glVertex3f(0, 0.63, 0.06);
    glVertex3f(-0.06, 0.65, -0.02);
    glEnd();

    //jaw
    glBegin(GL_POLYGON);
    glVertex3f(-0.03, 0.62, -0.01);
    glVertex3f(0, 0.62, -0.01);
    glVertex3f(0, 0.65, -0.02);
    glVertex3f(-0.06, 0.65, -0.02);
    glVertex3f(-0.03, 0.62, -0.01);
    glEnd();

    //chin
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.6, 0.05);
    glVertex3f(-0.02, 0.6, 0.05);
    glVertex3f(-0.03, 0.61, 0.01);
    glVertex3f(-0.03, 0.62, -0.01);
    glVertex3f(0, 0.62, -0.01);
    glVertex3f(0, 0.6, 0.05);
    glEnd();





    //flip horizontal
    //1st layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.6, 0.05);
    glVertex3f(0.02, 0.6, 0.05);
    glVertex3f(0.04, 0.63, 0.06);
    glVertex3f(0, 0.63, 0.06);
    glVertex3f(0, 0.6, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.02, 0.6, 0.05);
    glVertex3f(0.06, 0.63, 0.04);
    glVertex3f(0.04, 0.63, 0.06);
    glVertex3f(0.02, 0.6, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.02, 0.6, 0.05);
    glVertex3f(0.03, 0.61, 0.01);
    glVertex3f(0.06, 0.64, 0.01);
    glVertex3f(0.06, 0.63, 0.04);
    glVertex3f(0.02, 0.6, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.03, 0.61, 0.01);
    glVertex3f(0.03, 0.62, -0.01);
    glVertex3f(0.06, 0.65, -0.02);
    glVertex3f(0.06, 0.64, 0.01);
    glVertex3f(0.03, 0.61, 0.01);
    glEnd();

    //2nd layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.63, 0.06);
    glVertex3f(0.04, 0.63, 0.06);
    glVertex3f(0.04, 0.65, 0.065);
    glVertex3f(0, 0.65, 0.065);
    glVertex3f(0, 0.63, 0.06);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.63, 0.06);
    glVertex3f(0.06, 0.63, 0.04);
    glVertex3f(0.07, 0.66, 0.03);
    glVertex3f(0.04, 0.65, 0.065);
    glVertex3f(0.04, 0.63, 0.06);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.06, 0.63, 0.04);
    glVertex3f(0.06, 0.64, 0.01);
    glVertex3f(0.06, 0.65, -0.02);
    glVertex3f(0.07, 0.66, -0.02);
    glVertex3f(0.07, 0.66, 0.03);
    glVertex3f(0.06, 0.63, 0.04);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(0.06, 0.65, -0.02);
    glVertex3f(0.07, 0.66, -0.02);
    glVertex3f(0.05, 0.65, -0.06);
    glVertex3f(0.06, 0.66, -0.07);
    glVertex3f(0.015, 0.65, -0.075);
    glVertex3f(0.03, 0.66, -0.085);
    glVertex3f(0, 0.65, -0.07);
    glVertex3f(0, 0.66, -0.09);
    glEnd();

    //3rd layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.65, 0.065);
    glVertex3f(0.04, 0.65, 0.065);
    glVertex3f(0.01, 0.67, 0.04);
    glVertex3f(0, 0.67, 0.04);
    glVertex3f(0, 0.65, 0.065);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.65, 0.065);
    glVertex3f(0.05, 0.66, 0.03);
    glVertex3f(0.01, 0.67, 0.04);
    glVertex3f(0.04, 0.65, 0.065);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.04, 0.65, 0.065);
    glVertex3f(0.07, 0.66, 0.03);
    glVertex3f(0.05, 0.66, 0.03);
    glVertex3f(0.04, 0.65, 0.065);
    glEnd();

    //4th layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.67, 0.04);
    glVertex3f(0.01, 0.67, 0.04);
    glVertex3f(0.01, 0.7, 0.045);
    glVertex3f(0, 0.7, 0.045);
    glVertex3f(0, 0.67, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.01, 0.67, 0.04);
    glVertex3f(0.05, 0.66, 0.03);
    glVertex3f(0.05, 0.7, 0.03);
    glVertex3f(0.01, 0.7, 0.045);
    glVertex3f(0.01, 0.67, 0.04);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.05, 0.66, 0.03);
    glVertex3f(0.07, 0.66, 0.03);
    glVertex3f(0.07, 0.7, 0.03);
    glVertex3f(0.05, 0.7, 0.03);
    glVertex3f(0.05, 0.66, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.07, 0.66, 0.03);
    glVertex3f(0.07, 0.66, -0.02);
    glVertex3f(0.08, 0.7, -0.02);
    glVertex3f(0.07, 0.7, 0.03);
    glVertex3f(0.07, 0.66, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.07, 0.66, -0.02);
    glVertex3f(0.06, 0.66, -0.07);
    glVertex3f(0.06, 0.7, -0.07);
    glVertex3f(0.08, 0.7, -0.02);
    glVertex3f(0.07, 0.66, -0.02);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.06, 0.66, -0.07);
    glVertex3f(0.03, 0.66, -0.085);
    glVertex3f(0.03, 0.7, -0.09);
    glVertex3f(0.06, 0.7, -0.07);
    glVertex3f(0.06, 0.66, -0.07);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.03, 0.66, -0.085);
    glVertex3f(0, 0.66, -0.09);
    glVertex3f(0, 0.7, -0.1);
    glVertex3f(0.03, 0.7, -0.09);
    glVertex3f(0.03, 0.66, -0.085);
    glEnd();

    //5th layer
    glBegin(GL_QUADS);
    glVertex3f(0, 0.7, 0.045);
    glVertex3f(0.01, 0.7, 0.045);
    glVertex3f(0.02, 0.72, 0.045);
    glVertex3f(0, 0.72, 0.045);
    glVertex3f(0, 0.7, 0.045);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(0.01, 0.7, 0.045);
    glVertex3f(0.02, 0.72, 0.045);
    glVertex3f(0.05, 0.7, 0.03);
    glVertex3f(0.04, 0.72, 0.03);
    glVertex3f(0.07, 0.7, 0.03);
    glVertex3f(0.07, 0.72, 0.03);
    glVertex3f(0.08, 0.7, -0.02);
    glVertex3f(0.08, 0.72, -0.02);
    glVertex3f(0.06, 0.7, -0.07);
    glVertex3f(0.06, 0.72, -0.07);
    glVertex3f(0.03, 0.7, -0.09);
    glVertex3f(0.03, 0.72, -0.09);
    glVertex3f(0, 0.7, -0.1);
    glVertex3f(0, 0.72, -0.1);
    glEnd();

    //6th layer
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.72, 0.045);
    glVertex3f(0, 0.76, 0.035);
    glVertex3f(0.02, 0.72, 0.045);
    glVertex3f(0.02, 0.76, 0.035);
    glVertex3f(0.04, 0.72, 0.03);
    glVertex3f(0.04, 0.76, 0.03);
    glVertex3f(0.07, 0.72, 0.03);
    glVertex3f(0.055, 0.76, 0.02);
    glVertex3f(0.08, 0.72, -0.02);
    glVertex3f(0.07, 0.76, -0.02);
    glVertex3f(0.06, 0.72, -0.07);
    glVertex3f(0.05, 0.76, -0.07);
    glVertex3f(0.03, 0.72, -0.09);
    glVertex3f(0.03, 0.76, -0.085);
    glVertex3f(0, 0.72, -0.1);
    glVertex3f(0, 0.76, -0.09);
    glEnd();

    //7th layer
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.76, 0.035);
    glVertex3f(0, 0.79, 0);
    glVertex3f(0.02, 0.76, 0.035);
    glVertex3f(0.02, 0.79, 0);
    glVertex3f(0.04, 0.76, 0.03);
    glVertex3f(0.035, 0.79, 0);
    glVertex3f(0.055, 0.76, 0.02);
    glVertex3f(0.04, 0.79, 0);
    glVertex3f(0.07, 0.76, -0.02);
    glVertex3f(0.035, 0.79, -0.02);
    glVertex3f(0.05, 0.76, -0.07);
    glVertex3f(0.035, 0.79, -0.05);
    glVertex3f(0.03, 0.76, -0.085);
    glVertex3f(0.03, 0.79, -0.06);
    glVertex3f(0, 0.76, -0.09);
    glVertex3f(0, 0.79, -0.06);
    glEnd();

    //8th layer
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0.8, -0.03);
    glVertex3f(0, 0.79, 0);
    glVertex3f(0.02, 0.79, 0);
    glVertex3f(0.035, 0.79, 0);
    glVertex3f(0.04, 0.79, 0);
    glVertex3f(0.035, 0.79, -0.02);
    glVertex3f(0.035, 0.79, -0.05);
    glVertex3f(0.03, 0.79, -0.06);
    glVertex3f(0, 0.79, -0.06);
    glEnd();

    //ear
    glBegin(GL_POLYGON);
    glVertex3f(0.07, 0.66, -0.02);
    glVertex3f(0.07, 0.66, -0.04);
    glVertex3f(0.09, 0.68, -0.05);
    glVertex3f(0.09, 0.69, -0.05);
    glVertex3f(0.09, 0.7, -0.04);
    glVertex3f(0.09, 0.7, -0.03);
    glVertex3f(0.075, 0.68, -0.02);
    glVertex3f(0.07, 0.66, -0.02);
    glEnd();

    //bottom
    glBegin(GL_POLYGON);
    glVertex3f(0.06, 0.65, -0.02);
    glVertex3f(0.05, 0.65, -0.06);
    glVertex3f(0.015, 0.65, -0.075);
    glVertex3f(0, 0.65, -0.07);
    glVertex3f(0, 0.63, 0.06);
    glVertex3f(0.06, 0.65, -0.02);
    glEnd();

    //jaw
    glBegin(GL_POLYGON);
    glVertex3f(0.03, 0.62, -0.01);
    glVertex3f(0, 0.62, -0.01);
    glVertex3f(0, 0.65, -0.02);
    glVertex3f(0.06, 0.65, -0.02);
    glVertex3f(0.03, 0.62, -0.01);
    glEnd();

    //chin
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.6, 0.05);
    glVertex3f(0.02, 0.6, 0.05);
    glVertex3f(0.03, 0.61, 0.01);
    glVertex3f(0.03, 0.62, -0.01);
    glVertex3f(0, 0.62, -0.01);
    glVertex3f(0, 0.6, 0.05);
    glEnd();


}

void hair() {
    //layer
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0.74, 0.040);
    glVertex3f(-0.03, 0.74, 0.040);
    glVertex3f(-0.04, 0.76, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.74, 0.040);
    glVertex3f(-0.04, 0.76, 0.05);
    glVertex3f(-0.03, 0.81, 0.035);
    glVertex3f(0, 0.79, 0.03);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.04, 0.76, 0.05);
    glVertex3f(-0.075, 0.73, 0.05);
    glVertex3f(-0.075, 0.74, 0.03);
    glVertex3f(-0.03, 0.81, 0.035);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.075, 0.73, 0.05);
    glVertex3f(-0.13, 0.7, -0.05);
    glVertex3f(-0.075, 0.74, 0.03);
    glEnd();

    //layer 1
    glBegin(GL_QUADS);
    glVertex3f(0, 0.83, -0.05);
    glVertex3f(0, 0.83, -0.02);
    glVertex3f(-0.02, 0.83, -0.02);
    glVertex3f(-0.02, 0.83, -0.05);
    glEnd();
    

    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.8, 0.025);
    glVertex3f(0, 0.83, -0.02);
    glVertex3f(-0.04, 0.8, 0.025);
    glVertex3f(-0.02, 0.83, -0.02);
    glVertex3f(-0.08, 0.8, -0.01);
    glVertex3f(-0.02, 0.83, -0.02);
    glVertex3f(-0.08, 0.8, -0.08);
    glVertex3f(-0.02, 0.83, -0.05);
    glVertex3f(-0.03, 0.8, -0.1);
    glVertex3f(-0.02, 0.83, -0.05);
    glVertex3f(0, 0.8, -0.1);
    glVertex3f(0, 0.83, -0.05);
    glEnd();

    //layer 2
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.76, 0.035);
    glVertex3f(0, 0.8, 0.025);
    glVertex3f(-0.04, 0.76, 0.035);
    glVertex3f(-0.04, 0.8, 0.025);
    glVertex3f(-0.11, 0.76, 0);
    glVertex3f(-0.08, 0.8, -0.01);
    glVertex3f(-0.09, 0.76, -0.1);
    glVertex3f(-0.08, 0.8, -0.08);
    glVertex3f(-0.03, 0.76, -0.14);
    glVertex3f(-0.03, 0.8, -0.1);
    glVertex3f(0, 0.76, -0.14);
    glVertex3f(0, 0.8, -0.1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.11, 0.76, 0);
    glVertex3f(-0.09, 0.76, -0.1);
    glVertex3f(-0.13, 0.74, -0.08);
    glEnd();

    //layer 3
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.74, 0.040);
    glVertex3f(0, 0.76, 0.035);
    glVertex3f(-0.040, 0.74, 0.040);
    glVertex3f(-0.04, 0.76, 0.035);
    glVertex3f(-0.08, 0.74, 0.01);
    glVertex3f(-0.075, 0.76, 0.01);
    glVertex3f(-0.055, 0.74, -0.07);
    glVertex3f(-0.055, 0.76, -0.07);
    glVertex3f(-0.03, 0.74, -0.09);
    glVertex3f(-0.03, 0.76, -0.09);
    glVertex3f(0, 0.74, -0.1);
    glVertex3f(0, 0.76, -0.1);
    glVertex3f(0, 0.74, -0.14);
    glVertex3f(0, 0.76, -0.14);
    glVertex3f(-0.03, 0.74, -0.14);
    glVertex3f(-0.03, 0.76, -0.14);
    glVertex3f(-0.09, 0.74, -0.1);
    glVertex3f(-0.09, 0.76, -0.1);
    glVertex3f(-0.11, 0.74, 0);
    glVertex3f(-0.11, 0.76, 0);
    glVertex3f(-0.08, 0.74, 0.01);
    glVertex3f(-0.075, 0.76, 0.01);
    glVertex3f(-0.08, 0.74, 0.01);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.11, 0.74, 0);
    glVertex3f(-0.11, 0.76, 0);
    glVertex3f(-0.04, 0.76, 0.035);
    glVertex3f(-0.040, 0.74, 0.040);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.11, 0.74, 0);
    glVertex3f(-0.040, 0.74, 0.040);
    glVertex3f(-0.08, 0.74, 0.01);
    glEnd();

    //layer 4
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.08, 0.7, -0.02);
    glVertex3f(-0.08, 0.74, 0.01);
    glVertex3f(-0.06, 0.7, -0.07);
    glVertex3f(-0.055, 0.74, -0.07);
    glVertex3f(-0.03, 0.7, -0.09);
    glVertex3f(-0.03, 0.74, -0.09);
    glVertex3f(0, 0.7, -0.1);
    glVertex3f(0, 0.74, -0.1);
    glVertex3f(0, 0.7, -0.14);
    glVertex3f(0, 0.74, -0.14);
    glVertex3f(-0.03, 0.7, -0.14);
    glVertex3f(-0.03, 0.74, -0.14);
    glVertex3f(-0.09, 0.7, -0.1);
    glVertex3f(-0.09, 0.74, -0.1);
    glVertex3f(-0.11, 0.7, -0.04);
    glVertex3f(-0.11, 0.74, 0);
    glVertex3f(-0.08, 0.7, -0.02);
    glVertex3f(-0.08, 0.74, 0.01);
    glEnd();

    //layer 5
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.07, 0.66, -0.04);
    glVertex3f(-0.08, 0.7, -0.02);
    glVertex3f(-0.07, 0.66, -0.07);
    glVertex3f(-0.06, 0.7, -0.07);
    glVertex3f(-0.03, 0.66, -0.085);
    glVertex3f(-0.03, 0.7, -0.09);
    glVertex3f(0, 0.66, -0.09);
    glVertex3f(0, 0.7, -0.1);
    glVertex3f(0, 0.66, -0.13);
    glVertex3f(0, 0.7, -0.14);
    glVertex3f(-0.03, 0.66, -0.13);
    glVertex3f(-0.03, 0.7, -0.14);
    glVertex3f(-0.09, 0.66, -0.1);
    glVertex3f(-0.09, 0.7, -0.1);
    glVertex3f(-0.08, 0.66, -0.04);
    glVertex3f(-0.11, 0.7, -0.04);
    glVertex3f(-0.07, 0.66, -0.04);
    glVertex3f(-0.08, 0.7, -0.02);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.03, 0.66, -0.13);
    glVertex3f(-0.09, 0.66, -0.1);
    glVertex3f(-0.06, 0.63, -0.14);
    glEnd();


    //layer 6
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.07, 0.6, -0.04);
    glVertex3f(-0.07, 0.66, -0.04);
    glVertex3f(-0.07, 0.6, -0.07);
    glVertex3f(-0.07, 0.66, -0.07);
    glVertex3f(-0.03, 0.6, -0.085);
    glVertex3f(-0.03, 0.66, -0.085);
    glVertex3f(0, 0.6, -0.09);
    glVertex3f(0, 0.66, -0.09);
    glVertex3f(0, 0.6, -0.13);
    glVertex3f(0, 0.66, -0.13);
    glVertex3f(-0.03, 0.6, -0.13);
    glVertex3f(-0.03, 0.66, -0.13);
    glVertex3f(-0.09, 0.6, -0.1);
    glVertex3f(-0.09, 0.66, -0.1);
    glVertex3f(-0.08, 0.6, -0.04);
    glVertex3f(-0.08, 0.66, -0.04);
    glVertex3f(-0.07, 0.6, -0.04);
    glVertex3f(-0.07, 0.66, -0.04);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.09, 0.6, -0.1);
    glVertex3f(-0.08, 0.6, -0.04);
    glVertex3f(-0.1, 0.57, -0.08);
    glEnd();

    //layer 7
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.07, 0.55, -0.06);
    glVertex3f(-0.07, 0.6, -0.04);
    glVertex3f(-0.05, 0.55, -0.09);
    glVertex3f(-0.07, 0.6, -0.07);
    glVertex3f(-0.03, 0.55, -0.1);
    glVertex3f(-0.03, 0.6, -0.085);
    glVertex3f(0, 0.55, -0.12);
    glVertex3f(0, 0.6, -0.09);
    glVertex3f(0, 0.55, -0.15);
    glVertex3f(0, 0.6, -0.13);
    glVertex3f(-0.03, 0.55, -0.14);
    glVertex3f(-0.03, 0.6, -0.13);
    glVertex3f(-0.07, 0.55, -0.1);
    glVertex3f(-0.09, 0.6, -0.1);
    glVertex3f(-0.08, 0.55, -0.06);
    glVertex3f(-0.08, 0.6, -0.04);
    glVertex3f(-0.07, 0.55, -0.06);
    glVertex3f(-0.07, 0.6, -0.04);
    glEnd();

    //layer 8
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.05, 0.5, -0.09);
    glVertex3f(-0.07, 0.55, -0.06);
    glVertex3f(-0.03, 0.5, -0.12);
    glVertex3f(-0.05, 0.55, -0.09);
    glVertex3f(-0.03, 0.5, -0.12);
    glVertex3f(-0.03, 0.55, -0.1);
    glVertex3f(0, 0.5, -0.12);
    glVertex3f(0, 0.55, -0.12);
    glVertex3f(0, 0.5, -0.14);
    glVertex3f(0, 0.55, -0.15);
    glVertex3f(-0.04, 0.5, -0.13);
    glVertex3f(-0.03, 0.55, -0.14);
    glVertex3f(-0.06, 0.5, -0.11);
    glVertex3f(-0.07, 0.55, -0.1);
    glVertex3f(-0.07, 0.5, -0.09);
    glVertex3f(-0.08, 0.55, -0.06);
    glVertex3f(-0.05, 0.5, -0.09);
    glVertex3f(-0.07, 0.55, -0.06);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.04, 0.5, -0.13);
    glVertex3f(-0.06, 0.5, -0.11);
    glVertex3f(-0.07, 0.48, -0.12);
    glEnd();

    //layer 9
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.03, 0.45, -0.11);
    glVertex3f(-0.05, 0.5, -0.09);
    glVertex3f(-0.01, 0.45, -0.12);
    glVertex3f(-0.03, 0.5, -0.12);
    glVertex3f(0, 0.45, -0.12);
    glVertex3f(0, 0.5, -0.12);
    glVertex3f(0, 0.45, -0.12);
    glVertex3f(0, 0.5, -0.14);
    glVertex3f(-0.01, 0.45, -0.12);
    glVertex3f(-0.04, 0.5, -0.13);
    glVertex3f(-0.03, 0.45, -0.11);
    glVertex3f(-0.06, 0.5, -0.11);
    glVertex3f(-0.03, 0.45, -0.11);
    glVertex3f(-0.07, 0.5, -0.09);
    glVertex3f(-0.03, 0.45, -0.11);
    glVertex3f(-0.05, 0.5, -0.09);
    glEnd();

    //layer 10
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0.45, -0.12);
    glVertex3f(-0.01, 0.45, -0.12);
    glVertex3f(-0.005, 0.43, -0.11);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.03, 0.45, -0.11);
    glVertex3f(-0.01, 0.45, -0.12);
    glVertex3f(-0.015, 0.43, -0.11);
    glEnd();

}

void sword() {
    glBegin(GL_POLYGON);
    glVertex3f(-0.01, 0.8, 0);
    glVertex3f(-0.005, 0.8, -0.01);
    glVertex3f(0.005, 0.8, -0.01);
    glVertex3f(0.01, 0.8, 0);
    glVertex3f(0.005, 0.8, 0.01);
    glVertex3f(-0.005, 0.8, 0.01);
    glVertex3f(-0.01, 0.8, 0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.02, 0.79, 0);
    glVertex3f(-0.01, 0.8, 0);
    glVertex3f(-0.015, 0.79, -0.02);
    glVertex3f(-0.005, 0.8, -0.01);
    glVertex3f(0.015, 0.79, -0.02);
    glVertex3f(0.005, 0.8, -0.01);
    glVertex3f(0.02, 0.79, 0);
    glVertex3f(0.01, 0.8, 0);
    glVertex3f(0.015, 0.79, 0.02);
    glVertex3f(0.005, 0.8, 0.01);
    glVertex3f(-0.015, 0.79, 0.02);
    glVertex3f(-0.005, 0.8, 0.01);
    glVertex3f(-0.02, 0.79, 0);
    glVertex3f(-0.01, 0.8, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.01, 0.78, 0);
    glVertex3f(-0.005, 0.78, -0.01);
    glVertex3f(0.005, 0.78, -0.01);
    glVertex3f(0.01, 0.78, 0);
    glVertex3f(0.005, 0.78, 0.01);
    glVertex3f(-0.005, 0.78, 0.01);
    glVertex3f(-0.01, 0.78, 0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.01, 0.78, 0);
    glVertex3f(-0.02, 0.79, 0);
    glVertex3f(-0.005, 0.78, -0.01);
    glVertex3f(-0.015, 0.79, -0.02);
    glVertex3f(0.005, 0.78, -0.01);
    glVertex3f(0.015, 0.79, -0.02);
    glVertex3f(0.01, 0.78, 0);
    glVertex3f(0.02, 0.79, 0);
    glVertex3f(0.005, 0.78, 0.01);
    glVertex3f(0.015, 0.79, 0.02);
    glVertex3f(-0.005, 0.78, 0.01);
    glVertex3f(-0.015, 0.79, 0.02);
    glVertex3f(-0.01, 0.78, 0);
    glVertex3f(-0.02, 0.79, 0);
    glEnd();

    //handle
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0, 0.78, 0);
    glRotatef(90, 1, 0, 0);
    GLUquadricObj* cylinder = NULL;
    cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluCylinder(cylinder, 0.01, 0.01, 0.24, 10, 1);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
    glPopMatrix();

    //base
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.1, 0.5, 0.015);
    glVertex3f(-0.1, 0.52, 0.015);
    glVertex3f(0.1, 0.55, 0.015);
    glVertex3f(0.1, 0.57, 0.015);
    glVertex3f(0.1, 0.55, -0.015);
    glVertex3f(0.1, 0.57, -0.015);
    glVertex3f(-0.1, 0.5, -0.015);
    glVertex3f(-0.1, 0.52, -0.015);
    glVertex3f(-0.1, 0.5, 0.015);
    glVertex3f(-0.1, 0.52, 0.015);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.1, 0.52, 0.015);
    glVertex3f(0.1, 0.57, 0.015);
    glVertex3f(0.1, 0.57, -0.015);
    glVertex3f(-0.1, 0.52, -0.015);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.1, 0.5, 0.015);
    glVertex3f(0.1, 0.55, 0.015);
    glVertex3f(0.1, 0.55, -0.015);
    glVertex3f(-0.1, 0.5, -0.015);
    glEnd();

    //blade
    glBegin(GL_POLYGON);
    glVertex3f(-0.07, -0.15, 0);
    glVertex3f(-0.07, 0.51, 0);
    glVertex3f(0.07, 0.55, 0);
    glVertex3f(0.07, 0.37, 0);
    glVertex3f(0.05, 0.39, 0);
    glVertex3f(0.05, 0.35, 0);
    glVertex3f(0.07, 0.33, 0);
    glVertex3f(0.07, 0.29, 0);
    glVertex3f(0.05, 0.31, 0);
    glVertex3f(0.05, 0.27, 0);
    glVertex3f(0.07, 0.25, 0);
    glVertex3f(0.07, -0.3, 0);
    glEnd();
}

void thigh() {
    //top cover
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(0, 0.19, -0.07);
    glVertex3f(0, 0.19, 0.07);
    glEnd();


    //layer 1
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.08, 0.09);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(-0.01, 0.08, 0.09);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.09, 0.08, 0.066);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.12, 0.08, 0.04);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.12, 0.08, -0.04);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.09, 0.08, -0.066);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.01, 0.08, -0.09);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(0, 0.08, -0.09);
    glVertex3f(0, 0.19, -0.07);
    glEnd();

    //layer 2
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0.02, 0.06);
    glVertex3f(0, 0.08, 0.09);
    glVertex3f(-0.02, 0.02, 0.05);
    glVertex3f(-0.01, 0.08, 0.09);
    glVertex3f(-0.1, 0.02, 0.08);
    glVertex3f(-0.09, 0.08, 0.066);
    glVertex3f(-0.13, 0.02, 0.03);
    glVertex3f(-0.12, 0.08, 0.04);
    glVertex3f(-0.13, 0.02, -0.03);
    glVertex3f(-0.12, 0.08, -0.04);
    glVertex3f(-0.08, 0.02, -0.08);
    glVertex3f(-0.09, 0.08, -0.066);
    glVertex3f(-0.02, 0.02, -0.05);
    glVertex3f(-0.01, 0.08, -0.09);
    glVertex3f(0, 0.02, -0.06);
    glVertex3f(0, 0.08, -0.09);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0, 0.02, 0.06);
    glVertex3f(-0.02, 0.02, 0.05);
    glVertex3f(-0.02, 0.02, -0.05);
    glVertex3f(0, 0.02, -0.06);
    glEnd();

    //layer 3
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.04, -0.09, 0.03);
    glVertex3f(-0.02, 0.02, 0.05);
    glVertex3f(-0.08, -0.09, 0.04);
    glVertex3f(-0.1, 0.02, 0.08);
    glVertex3f(-0.11, -0.09, 0.02);
    glVertex3f(-0.13, 0.02, 0.03);
    glVertex3f(-0.11, -0.09, -0.02);
    glVertex3f(-0.13, 0.02, -0.03);
    glVertex3f(-0.08, -0.09, -0.04);
    glVertex3f(-0.08, 0.02, -0.08);
    glVertex3f(-0.04, -0.09, -0.03);
    glVertex3f(-0.02, 0.02, -0.05);
    glVertex3f(-0.04, -0.09, 0.03);
    glVertex3f(-0.02, 0.02, 0.05);
    glEnd();


    //layer 4
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.02, -0.23, 0.04);
    glVertex3f(-0.04, -0.09, 0.03);
    glVertex3f(-0.09, -0.23, 0.06);
    glVertex3f(-0.08, -0.09, 0.04);
    glVertex3f(-0.14, -0.23, 0.04);
    glVertex3f(-0.11, -0.09, 0.02);
    glVertex3f(-0.14, -0.23, -0.04);
    glVertex3f(-0.11, -0.09, -0.02);
    glVertex3f(-0.09, -0.23, -0.05);
    glVertex3f(-0.08, -0.09, -0.04);
    glVertex3f(-0.02, -0.23, -0.04);
    glVertex3f(-0.04, -0.09, -0.03);
    glVertex3f(-0.02, -0.23, 0.04);
    glVertex3f(-0.04, -0.09, 0.03);
    glEnd();

    //layer 5
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.04, -0.32, 0.02);
    glVertex3f(-0.02, -0.23, 0.04);
    glVertex3f(-0.07, -0.32, 0.04);
    glVertex3f(-0.09, -0.23, 0.06);
    glVertex3f(-0.1, -0.32, 0.02);
    glVertex3f(-0.14, -0.23, 0.04);
    glVertex3f(-0.1, -0.32, -0.02);
    glVertex3f(-0.14, -0.23, -0.04);
    glVertex3f(-0.07, -0.32, -0.04);
    glVertex3f(-0.09, -0.23, -0.05);
    glVertex3f(-0.04, -0.32, -0.02);
    glVertex3f(-0.02, -0.23, -0.04);
    glVertex3f(-0.04, -0.32, 0.02);
    glVertex3f(-0.02, -0.23, 0.04);
    glEnd();

    //bottom cover
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, -0.32, 0.02);
    glVertex3f(-0.07, -0.32, 0.04);
    glVertex3f(-0.1, -0.32, 0.02);
    glVertex3f(-0.1, -0.32, -0.02);
    glVertex3f(-0.07, -0.32, -0.04);
    glVertex3f(-0.04, -0.32, -0.02);
    glVertex3f(-0.04, -0.32, 0.02);
    glEnd();
}

void calf() {
    //top cover
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, -0.32, 0.02);
    glVertex3f(-0.07, -0.32, 0.04);
    glVertex3f(-0.1, -0.32, 0.02);
    glVertex3f(-0.1, -0.32, -0.02);
    glVertex3f(-0.07, -0.32, -0.04);
    glVertex3f(-0.04, -0.32, -0.02);
    glVertex3f(-0.04, -0.32, 0.02);
    glEnd();

    //layer 1
}


void display()
{
    //glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1.0f, 0.0f, 0.0f);

    guide();
    neck();
	body();
    head();

    hair();
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    hair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    sword();
    glPopMatrix();

    thigh();
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    thigh();
    glPopMatrix();

    glColor3f(1, 1, 1);
    calf();

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