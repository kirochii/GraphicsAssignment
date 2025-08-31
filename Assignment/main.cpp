
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <chrono>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#define WINDOW_TITLE "OpenGL Window"
#define PI 3.14159265359

struct Phase {
    // A class used for different "steps" to animation
    // Example: Each step has different rotations, duration, angle of rotation
    // Create an object and loop through the steps for animation

    double duration;   // seconds
    int type;          // 1 = rotateX, 2 = rotateY, 3 = rotateZ
    float value;       // angle or rotation
};

float cameraYaw = 0.0f;    // left/right rotation (around Y-axis)
float cameraPitch = 0.0f;  // up/down rotation (around X-axis)
float rotationSpeed = 5.0f; // degrees per key press

int qNo = 4;
bool opposite = false; //toggle clockwise & counter clockwise rotations
bool toggleRight = false; //toggle left and right limbs
float RotationSpeed = 10; //set degree for each key press

//Key 2: Rotation
float headX = 0, headY = 0, headZ = 0; //Head
float LUArmX = 0, LUArmY = 0, LUArmZ = 0; //Left Upper Arm
float LLArmX = 0, LLArmY = 0, LLArmZ = 0; //Left Lower Arm
float LPArmX = 0, LPArmY = 0, LPArmZ = 0; //Left Palm
float RUArmX = 0, RUArmY = 0, RUArmZ = 0; //Right Upper Arm
float RLArmX = 0, RLArmY = 0, RLArmZ = 0; //Right Lower Arm
float RPArmX = 0, RPArmY = 0, RPArmZ = 0; //Right Palm
float bodyX = 0, bodyY = 0, bodyZ = 0; //Body
float LULegX = 0, LULegY = 0, LULegZ = 0; //Left Upper Leg
float LLLegX = 0, LLLegY = 0, LLLegZ = 0; //Left Lower Leg
float LFLegX = 0, LFLegY = 0, LFLegZ = 0; //Left Feet
float RULegX = 0, RULegY = 0, RULegZ = 0; //Right Upper Leg
float RLLegX = 0, RLLegY = 0, RLLegZ = 0; //Right Lower Leg
float RFLegX = 0, RFLegY = 0, RFLegZ = 0; //Right Feet


//Key 4: Basic Attack
Phase phases[] = {
    {2.0, 1, 30.0f},   // rotate +30° X over 2s
    {2.0, 2, 50.0f},   // rotate +50° Y over 2s
    {2.0, 3, 40.0f},   // rotate +40° Z over 2s
    {2.0, 3, -40.0f},   // rotate +40° Z over 2s
    {2.0, 2, -50.0f},   // rotate +50° Y over 2s
    {2.0, 1, -30.0f},   // rotate +30° X over 2s
};
const int numPhases = sizeof(phases) / sizeof(phases[0]);
int currentPhase = 0;
double phaseStartTime = 0.0;
float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
float startVal = 0.0f;
float endVal = 0.0f;





LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        //Camera keys
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

        //Question controls
        case '1':
            qNo = 1;
            break;
        case '2':
            qNo = 2;
            break;
        case '3':
            qNo = 3;
            break;
        case '4':
            qNo = 4;
            break;

        //Q2 Controls
        if (qNo ==2) {
            //Toggle keys
            case VK_OEM_MINUS:
                opposite = !opposite;
                break;
            case VK_OEM_PLUS:
                toggleRight = !toggleRight;
                break;

            //Head
            case 'Q':
                if (!opposite)
                    headX += rotationSpeed;
                else
                    headX -= rotationSpeed;
                break;
            case 'E':
                if (!opposite)
                    headY += rotationSpeed;
                else
                    headY -= rotationSpeed;
                break;
            case 'R':
                if (!opposite)
                    headZ += rotationSpeed;
                else
                    headZ -= rotationSpeed;
                break;

            //Upper Arm
            case 'T':
                if (!toggleRight) {
                    if (!opposite)
                        LUArmX += rotationSpeed;
                    else
                        LUArmX -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RUArmX += rotationSpeed;
                    else
                        RUArmX -= rotationSpeed;
                }
                break;

            case 'Y':
                if (!toggleRight) {
                    if (!opposite)
                        LUArmY += rotationSpeed;
                    else
                        LUArmY -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RUArmY += rotationSpeed;
                    else
                        RUArmY -= rotationSpeed;
                }
                break;

            case 'U':
                if (!toggleRight) {
                    if (!opposite)
                        LUArmZ += rotationSpeed;
                    else
                        LUArmZ -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RUArmZ += rotationSpeed;
                    else
                        RUArmZ -= rotationSpeed;
                }
                break;

                // Lower Arm
            case 'I':
                if (!toggleRight) {
                    if (!opposite)
                        LLArmX += rotationSpeed;
                    else
                        LLArmX -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RLArmX += rotationSpeed;
                    else
                        RLArmX -= rotationSpeed;
                }
                break;

            case 'O':
                if (!toggleRight) {
                    if (!opposite)
                        LLArmY += rotationSpeed;
                    else
                        LLArmY -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RLArmY += rotationSpeed;
                    else
                        RLArmY -= rotationSpeed;
                }
                break;

            case 'P':
                if (!toggleRight) {
                    if (!opposite)
                        LLArmZ += rotationSpeed;
                    else
                        LLArmZ -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RLArmZ += rotationSpeed;
                    else
                        RLArmZ -= rotationSpeed;
                }
                break;

                // Palm
            case 'F':
                if (!toggleRight) {
                    if (!opposite)
                        LPArmX += rotationSpeed;
                    else
                        LPArmX -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RPArmX += rotationSpeed;
                    else
                        RPArmX -= rotationSpeed;
                }
                break;

            case 'G':
                if (!toggleRight) {
                    if (!opposite)
                        LPArmY += rotationSpeed;
                    else
                        LPArmY -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RPArmY += rotationSpeed;
                    else
                        RPArmY -= rotationSpeed;
                }
                break;

            case 'H':
                if (!toggleRight) {
                    if (!opposite)
                        LPArmZ += rotationSpeed;
                    else
                        LPArmZ -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RPArmZ += rotationSpeed;
                    else
                        RPArmZ -= rotationSpeed;
                }
                break;

            //Body
            case 'J':
                if (!opposite)
                    bodyX += rotationSpeed;
                else
                    bodyX -= rotationSpeed;
                break;
            case 'K':
                if (!opposite)
                    bodyY += rotationSpeed;
                else
                    bodyY -= rotationSpeed;
                break;
            case 'L':
                if (!opposite)
                    bodyZ += rotationSpeed;
                else
                    bodyZ -= rotationSpeed;
                break;

            // Upper Leg
            case 'Z':
                if (!toggleRight) {
                    if (!opposite)
                        LULegX += rotationSpeed;
                    else
                        LULegX -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RULegX += rotationSpeed;
                    else
                        RULegX -= rotationSpeed;
                }
                break;

            case 'X':
                if (!toggleRight) {
                    if (!opposite)
                        LULegY += rotationSpeed;
                    else
                        LULegY -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RULegY += rotationSpeed;
                    else
                        RULegY -= rotationSpeed;
                }
                break;

            case 'C':
                if (!toggleRight) {
                    if (!opposite)
                        LULegZ += rotationSpeed;
                    else
                        LULegZ -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RULegZ += rotationSpeed;
                    else
                        RULegZ -= rotationSpeed;
                }
                break;

            // Lower Leg
            case 'V':
                if (!toggleRight) {
                    if (!opposite)
                        LLLegX += rotationSpeed;
                    else
                        LLLegX -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RLLegX += rotationSpeed;
                    else
                        RLLegX -= rotationSpeed;
                }
                break;

            case 'B':
                if (!toggleRight) {
                    if (!opposite)
                        LLLegY += rotationSpeed;
                    else
                        LLLegY -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RLLegY += rotationSpeed;
                    else
                        RLLegY -= rotationSpeed;
                }
                break;

            case 'N':
                if (!toggleRight) {
                    if (!opposite)
                        LLLegZ += rotationSpeed;
                    else
                        LLLegZ -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RLLegZ += rotationSpeed;
                    else
                        RLLegZ -= rotationSpeed;
                }
                break;

            // Feet
            case 'M':
                if (!toggleRight) {
                    if (!opposite)
                        LFLegX += rotationSpeed;
                    else
                        LFLegX -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RFLegX += rotationSpeed;
                    else
                        RFLegX -= rotationSpeed;
                }
                break;

            case VK_OEM_COMMA:
                if (!toggleRight) {
                    if (!opposite)
                        LFLegY += rotationSpeed;
                    else
                        LFLegY -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RFLegY += rotationSpeed;
                    else
                        RFLegY -= rotationSpeed;
                }
                break;

            case VK_OEM_PERIOD:
                if (!toggleRight) {
                    if (!opposite)
                        LFLegZ += rotationSpeed;
                    else
                        LFLegZ -= rotationSpeed;
                }
                else {
                    if (!opposite)
                        RFLegZ += rotationSpeed;
                    else
                        RFLegZ -= rotationSpeed;
                }
                break;






















            }
             
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

//Returns the elapsed time since program started
double getTime() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;
    return elapsed.count(); // seconds
}

void startPhase(int idx, Phase phases) {
    Phase& p = phases[idx];

    if (p.type == 1) { startVal = rotX; endVal = rotX + p.value; }
    if (p.type == 2) { startVal = rotY; endVal = rotY + p.value; }
    if (p.type == 3) { startVal = rotZ; endVal = rotZ + p.value; }

    phaseStartTime = getTime();
}

void applyAnimation() {
    double now = getTime();
    double elapsed = now - phaseStartTime;

    Phase& p = phases[currentPhase];

    // progress 0..1
    double t = elapsed / p.duration;
    if (t > 1.0) t = 1.0;

    float currentVal = startVal + (endVal - startVal) * (float)t;

    // 🔹 Always apply the base accumulated rotations
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // 🔹 Add only the "extra" interpolation for the current phase
    if (p.type == 1) glRotatef(currentVal - rotX, 1, 0, 0);
    if (p.type == 2) glRotatef(currentVal - rotY, 0, 1, 0);
    if (p.type == 3) glRotatef(currentVal - rotZ, 0, 0, 1);

    // update rotation state so next phase continues smoothly
    if (t >= 1.0) {
        if (p.type == 1) rotX = endVal;
        if (p.type == 2) rotY = endVal;
        if (p.type == 3) rotZ = endVal;

        // advance phase
        currentPhase++;
        if (currentPhase >= numPhases) {
            currentPhase = 0;  // restart from phase 0
            // 🔸 but don't reset rotX,rotY,rotZ unless you want looping back to origin
        }
        startPhase(currentPhase);
    }
}


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





}

void upperArm() {
    // Shoulder
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.18, 0.48, -0.01);
    glVertex3f(-0.13, 0.52, -0.07);
    glVertex3f(-0.16, 0.48, -0.08);
    glVertex3f(-0.13, 0.52, -0.07);
    glVertex3f(-0.13, 0.48, -0.07);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.14, 0.48, 0.03);
    glVertex3f(-0.16, 0.52, 0.03);
    glVertex3f(-0.18, 0.48, -0.01);
    glEnd();

    // Upper Arm
    glBegin(GL_QUAD_STRIP);
    // First side
    glVertex3f(-0.16, 0.48, -0.08); // top outer
    glVertex3f(-0.17, 0.44, -0.08); // bottom outer
    // Second side
    glVertex3f(-0.18, 0.48, -0.01);  // top inner
    glVertex3f(-0.19, 0.44, -0.02);  // bottom inner
    // Third side
    glVertex3f(-0.14, 0.48, 0.03);  // top front
    glVertex3f(-0.13, 0.44, 0.01);  // bottom front
    // Fourth side
    glVertex3f(-0.13, 0.48, -0.07); // top back
    glVertex3f(-0.13, 0.44, -0.08); // bottom back
    // Close loop back to first vertices
    glVertex3f(-0.16, 0.48, -0.08); // top outer again
    glVertex3f(-0.17, 0.44, -0.08); // bottom outer again
    glEnd();

    glBegin(GL_QUAD_STRIP);
    // Side 1: Outer
    glVertex3f(-0.17, 0.44, -0.08);
    glVertex3f(-0.18, 0.40, -0.085);
    // Side 2: Front
    glVertex3f(-0.19, 0.44, -0.02);
    glVertex3f(-0.195, 0.40, -0.03);
    // Side 3: Inner
    glVertex3f(-0.13, 0.44, 0.01);
    glVertex3f(-0.12, 0.40, 0);
    // Side 4: Back
    glVertex3f(-0.13, 0.44, -0.08);
    glVertex3f(-0.14, 0.40, -0.09);
    // Close loop
    glVertex3f(-0.17, 0.44, -0.08);
    glVertex3f(-0.18, 0.40, -0.085);
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    // Side 1: Outer
    glVertex3f(-0.18, 0.40, -0.085);
    glVertex3f(-0.18, 0.37, -0.08);
    // Side 2: Front
    glVertex3f(-0.195, 0.40, -0.03);
    glVertex3f(-0.2, 0.37, -0.03);
    // Side 3: Inner
    glVertex3f(-0.12, 0.40, 0);
    glVertex3f(-0.13, 0.35, -0.01);
    // Side 4: Back
    glVertex3f(-0.14, 0.40, -0.09);
    glVertex3f(-0.14, 0.35, -0.09);
    // Close loop
    glVertex3f(-0.18, 0.40, -0.085);
    glVertex3f(-0.18, 0.37, -0.08);
    glEnd();

    //close bottom
    glBegin(GL_QUADS);
    glVertex3f(-0.18, 0.37, -0.08);
    glVertex3f(-0.2, 0.37, -0.03);
    glVertex3f(-0.13, 0.35, -0.01);
    glVertex3f(-0.14, 0.35, -0.09);
    glEnd();
}

void lowerArm() {
    //close top
    glBegin(GL_QUADS);
    glVertex3f(-0.18, 0.37, -0.08);
    glVertex3f(-0.2, 0.37, -0.03);
    glVertex3f(-0.13, 0.35, -0.01);
    glVertex3f(-0.14, 0.35, -0.09);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    // Side 1: Outer
    glVertex3f(-0.18, 0.37, -0.08);
    glVertex3f(-0.21, 0.30, -0.1);
    // Side 2: Front
    glVertex3f(-0.2, 0.37, -0.03);
    glVertex3f(-0.23, 0.30, -0.01);
    // Side 3: Inner
    glVertex3f(-0.13, 0.35, -0.01);
    glVertex3f(-0.15, 0.27, 0.02);
    // Side 4: Back
    glVertex3f(-0.14, 0.35, -0.09);
    glVertex3f(-0.12, 0.27, -0.09);
    // Close loop
    glVertex3f(-0.18, 0.37, -0.08);
    glVertex3f(-0.21, 0.30, -0.1);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    // Side 1: Outer
    glVertex3f(-0.21, 0.3, -0.1);
    glVertex3f(-0.19, 0.25, -0.08);
    // Side 2: Front
    glVertex3f(-0.23, 0.3, -0.01);
    glVertex3f(-0.21, 0.25, -0.03);
    // Side 3: Inner
    glVertex3f(-0.15, 0.27, 0.02);
    glVertex3f(-0.17, 0.24, 0);
    // Side 4: Back
    glVertex3f(-0.12, 0.27, -0.09);
    glVertex3f(-0.14, 0.24, -0.07);
    // Close loop
    glVertex3f(-0.21, 0.3, -0.1);
    glVertex3f(-0.19, 0.25, -0.08);
    glEnd();

    // Forearm
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.19, 0.25, -0.08);
    glVertex3f(-0.2, 0.07, -0.04);
    glVertex3f(-0.21, 0.25, -0.03);
    glVertex3f(-0.22, 0.07, -0.00);
    glVertex3f(-0.17, 0.24, 0);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.14, 0.24, -0.07);
    glVertex3f(-0.19, 0.07, -0.03);
    glVertex3f(-0.19, 0.25, -0.08);
    glVertex3f(-0.2, 0.07, -0.04);
    glEnd();

    //close bottom
    glBegin(GL_QUADS);
    glVertex3f(-0.2, 0.07, -0.04);
    glVertex3f(-0.22, 0.07, -0.00);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.19, 0.07, -0.03);
    glEnd();
}

void palm() {
    //close top
    glBegin(GL_QUADS);
    glVertex3f(-0.2, 0.07, -0.04);
    glVertex3f(-0.22, 0.07, -0.00);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.19, 0.07, -0.03);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.2, 0.07, -0.04);
    glVertex3f(-0.22, 0.0, -0.045);
    glVertex3f(-0.22, 0.07, -0.00);
    glVertex3f(-0.23, 0.02, 0.02);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.2, 0.02, 0.02);
    glVertex3f(-0.19, 0.07, -0.03);
    glVertex3f(-0.2, 0.0, -0.035);
    glVertex3f(-0.2, 0.07, -0.04);
    glVertex3f(-0.22, 0.0, -0.045);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.22, 0.0, -0.045);
    glVertex3f(-0.2, -0.03, -0.02);
    glVertex3f(-0.23, 0.02, 0.02);
    glVertex3f(-0.21, -0.01, 0.02);
    glVertex3f(-0.2, 0.02, 0.02);
    glVertex3f(-0.19, -0.01, 0.02);
    glVertex3f(-0.2, 0.0, -0.035);
    glVertex3f(-0.19, -0.03, -0.02);
    glVertex3f(-0.22, 0.0, -0.045);
    glVertex3f(-0.2, -0.03, -0.02);
    glEnd();


    //bottom cover
    glBegin(GL_QUADS);
    glVertex3f(-0.2, -0.03, -0.02);
    glVertex3f(-0.21, -0.01, 0.02);
    glVertex3f(-0.19, -0.01, 0.02);
    glVertex3f(-0.19, -0.03, -0.02);
    glEnd();

    //thumb
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.2, 0.04, 0.01);
    glVertex3f(-0.18, 0.04, 0.015);
    glVertex3f(-0.18, 0.02, 0.015);
    glVertex3f(-0.18, 0.03, 0);
    glVertex3f(-0.18, 0.01, 0);
    glVertex3f(-0.2, 0.07, -0.015);
    glVertex3f(-0.2, 0.04, -0.015);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.2, 0.04, 0.01);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.2, 0.07, 0);
    glVertex3f(-0.18, 0.04, 0.015);
    glVertex3f(-0.18, 0.03, 0);
    glVertex3f(-0.2, 0.07, -0.015);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.2, 0.04, 0.01);
    glVertex3f(-0.18, 0.02, 0.015);
    glVertex3f(-0.18, 0.01, 0);
    glVertex3f(-0.2, 0.04, -0.015);
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
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.04, -0.48, 0.01);
    glVertex3f(-0.04, -0.32, 0.02);
    glVertex3f(-0.06, -0.48, 0.02);
    glVertex3f(-0.07, -0.32, 0.04);
    glVertex3f(-0.08, -0.48, 0);
    glVertex3f(-0.1, -0.32, 0.02);
    glVertex3f(-0.08, -0.48, -0.04);
    glVertex3f(-0.1, -0.32, -0.02);
    glVertex3f(-0.06, -0.48, -0.05);
    glVertex3f(-0.07, -0.32, -0.04);
    glVertex3f(-0.03, -0.48, -0.03);
    glVertex3f(-0.04, -0.32, -0.02);
    glVertex3f(-0.04, -0.48, 0.01);
    glVertex3f(-0.04, -0.32, 0.02);
    glEnd();

    //layer 2
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.04, -0.48, 0.01);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.06, -0.48, 0.02);
    glVertex3f(-0.07, -0.62, 0.01);
    glVertex3f(-0.08, -0.48, 0);
    glVertex3f(-0.07, -0.62, -0.02);
    glVertex3f(-0.08, -0.48, -0.04);
    glVertex3f(-0.03, -0.62, -0.03);
    glVertex3f(-0.06, -0.48, -0.05);
    glVertex3f(-0.03, -0.62, -0.03);
    glVertex3f(-0.03, -0.48, -0.03);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.04, -0.48, 0.01);
    glEnd();

    //bottom cover
    glBegin(GL_QUADS);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.07, -0.62, 0.01);
    glVertex3f(-0.07, -0.62, -0.02);
    glVertex3f(-0.03, -0.62, -0.03);
    glEnd();

}

void feet() {
    //top cover
    glBegin(GL_QUADS);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.07, -0.62, 0.01);
    glVertex3f(-0.07, -0.62, -0.02);
    glVertex3f(-0.03, -0.62, -0.03);
    glEnd();

    //top
    glBegin(GL_QUADS);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.07, -0.62, 0.01);
    glVertex3f(-0.08, -0.65, 0.05);
    glVertex3f(-0.03, -0.65, 0.05);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.03, -0.65, 0.05);
    glVertex3f(-0.08, -0.65, 0.05);
    glVertex3f(-0.08, -0.66, 0.09);
    glVertex3f(-0.03, -0.66, 0.09);
    glEnd();

    //front
    glBegin(GL_QUADS);
    glVertex3f(-0.03, -0.66, 0.09);
    glVertex3f(-0.08, -0.66, 0.09);
    glVertex3f(-0.07, -0.68, 0.08);
    glVertex3f(-0.03, -0.68, 0.08);
    glEnd();

    //back
    glBegin(GL_QUADS);
    glVertex3f(-0.07, -0.62, -0.02);
    glVertex3f(-0.03, -0.62, -0.03);
    glVertex3f(-0.03, -0.68, -0.05);
    glVertex3f(-0.07, -0.68, -0.05);
    glEnd();

    //bottom
    glBegin(GL_QUADS);
    glVertex3f(-0.03, -0.68, -0.05);
    glVertex3f(-0.07, -0.68, -0.05);
    glVertex3f(-0.07, -0.68, 0.08);
    glVertex3f(-0.03, -0.68, 0.08);
    glEnd();

    //inner side
    glBegin(GL_POLYGON);
    glVertex3f(-0.03, -0.62, 0.01);
    glVertex3f(-0.03, -0.65, 0.05);
    glVertex3f(-0.03, -0.66, 0.09);
    glVertex3f(-0.03, -0.68, 0.08);
    glVertex3f(-0.03, -0.68, -0.05);
    glVertex3f(-0.03, -0.62, -0.03);
    glEnd();

    //outer side
    glBegin(GL_POLYGON);
    glVertex3f(-0.07, -0.62, 0.01);
    glVertex3f(-0.08, -0.65, 0.05);
    glVertex3f(-0.08, -0.66, 0.09);
    glVertex3f(-0.07, -0.68, 0.08);
    glVertex3f(-0.07, -0.68, -0.05);
    glVertex3f(-0.07, -0.62, -0.02);
    glEnd();
}

void innerCloth() {
    //layer 1
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.01, -0.01, 0.12);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(-0.04, -0.01, 0.12);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.09, -0.01, 0.12);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.15, -0.01, 0.04);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.15, -0.01, -0.04);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.09, -0.01, -0.11);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.02, -0.01, -0.12);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(0, -0.01, -0.12);
    glVertex3f(0, 0.19, -0.07);
    glVertex3f(0.02, -0.01, -0.12);
    glVertex3f(0.04, 0.19, -0.07);
    glVertex3f(0.09, -0.01, -0.11);
    glVertex3f(0.07, 0.19, -0.05);
    glVertex3f(0.15, -0.01, -0.04);
    glVertex3f(0.09, 0.19, -0.03);
    glEnd();

    //layer 2
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.02, -0.2, 0.12);
    glVertex3f(-0.01, -0.01, 0.12);
    glVertex3f(-0.04, -0.2, 0.13);
    glVertex3f(-0.04, -0.01, 0.12);
    glVertex3f(-0.09, -0.2, 0.11);
    glVertex3f(-0.09, -0.01, 0.12);
    glVertex3f(-0.13, -0.2, 0.08);
    glVertex3f(-0.09, -0.01, 0.12);
    glVertex3f(-0.17, -0.2, 0.06);
    glVertex3f(-0.15, -0.01, 0.04);
    glVertex3f(-0.14, -0.2, -0.06);
    glVertex3f(-0.15, -0.01, -0.04);
    glVertex3f(-0.08, -0.2, -0.1);
    glVertex3f(-0.09, -0.01, -0.11);
    glVertex3f(-0.02, -0.2, -0.14);
    glVertex3f(-0.02, -0.01, -0.12);
    glVertex3f(0, -0.2, -0.14);
    glVertex3f(0, -0.01, -0.12);
    glVertex3f(0.02, -0.2, -0.14);
    glVertex3f(0.02, -0.01, -0.12);
    glVertex3f(0.08, -0.2, -0.1);
    glVertex3f(0.09, -0.01, -0.11);
    glVertex3f(0.17, -0.2, -0.04);
    glVertex3f(0.15, -0.01, -0.04);
    glEnd();

    //layer 3
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.03, -0.42, 0.13);
    glVertex3f(-0.02, -0.2, 0.12);
    glVertex3f(-0.05, -0.43, 0.14);
    glVertex3f(-0.04, -0.2, 0.13);
    glVertex3f(-0.08, -0.42, 0.11);
    glVertex3f(-0.09, -0.2, 0.11);
    glVertex3f(-0.13, -0.42, 0.12);
    glVertex3f(-0.13, -0.2, 0.08);
    glVertex3f(-0.18, -0.4, 0.07);
    glVertex3f(-0.17, -0.2, 0.06);
    glVertex3f(-0.15, -0.41, -0.01);
    glVertex3f(-0.17, -0.2, 0.06);
    glVertex3f(-0.16, -0.4, -0.08);
    glVertex3f(-0.14, -0.2, -0.06);
    glVertex3f(-0.07, -0.42, -0.1);
    glVertex3f(-0.08, -0.2, -0.1);
    glVertex3f(-0.02, -0.41, -0.14);
    glVertex3f(-0.02, -0.2, -0.14);
    glVertex3f(0, -0.42, -0.14);
    glVertex3f(0, -0.2, -0.14);
    glVertex3f(0.02, -0.41, -0.14);
    glVertex3f(0.02, -0.2, -0.14);
    glVertex3f(0.07, -0.42, -0.08);
    glVertex3f(0.08, -0.2, -0.1);
    glVertex3f(0.18, -0.4, -0.03);
    glVertex3f(0.17, -0.2, -0.04);
    glEnd();

}

void outerCloth() {
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, -0.06, 0.15);
    glVertex3f(0, 0.19, 0.07);
    glVertex3f(-0.04, -0.05, 0.15);
    glVertex3f(-0.04, 0.19, 0.07);
    glVertex3f(-0.09, -0.04, 0.14);
    glVertex3f(-0.07, 0.19, 0.05);
    glVertex3f(-0.17, -0.05, 0.06);
    glVertex3f(-0.09, 0.19, 0.03);
    glVertex3f(-0.17, -0.05, -0.06);
    glVertex3f(-0.09, 0.19, -0.03);
    glVertex3f(-0.09, -0.04, -0.14);
    glVertex3f(-0.07, 0.19, -0.05);
    glVertex3f(-0.04, -0.05, -0.15);
    glVertex3f(-0.04, 0.19, -0.07);
    glVertex3f(0, -0.06, -0.15);
    glVertex3f(0, 0.19, -0.07);
    glVertex3f(0.04, -0.05, -0.15);
    glVertex3f(0.04, 0.19, -0.07);
    glVertex3f(0.09, -0.04, -0.14);
    glVertex3f(0.07, 0.19, -0.05);
    glVertex3f(0.17, -0.05, -0.06);
    glVertex3f(0.09, 0.19, -0.03);
    glVertex3f(0.17, -0.05, 0.06);
    glVertex3f(0.09, 0.19, 0.03);
    glVertex3f(0.09, -0.04, 0.14);
    glVertex3f(0.07, 0.19, 0.05);
    glVertex3f(0.04, -0.05, 0.15);
    glVertex3f(0.04, 0.19, 0.07);
    glVertex3f(0, -0.06, 0.15);
    glVertex3f(0, 0.19, 0.07);
    glEnd();


    //layer 2
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0, -0.06, -0.15);
    glVertex3f(0.04, -0.08, -0.16);
    glVertex3f(0.04, -0.05, -0.15);
    glVertex3f(0.09, -0.12, -0.16);
    glVertex3f(0.09, -0.04, -0.14);
    glVertex3f(0.09, -0.12, -0.16);
    glVertex3f(0.17, -0.05, -0.06);
    glVertex3f(0.19, -0.15, -0.08);
    glVertex3f(0.17, -0.05, 0.06);
    glVertex3f(0.2, -0.18, 0.11);
    glVertex3f(0.09, -0.04, 0.14);
    glVertex3f(0.1, -0.1, 0.15);
    glVertex3f(0.04, -0.05, 0.15);
    glVertex3f(0, -0.06, 0.15);
    glEnd();

}

void key1() {
    //glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1.0f, 0.0f, 0.0f);

    guide();

    glColor3f(1, 1, 1);
    neck();
    body();
    head();

    upperArm();
    lowerArm();
    palm();
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    upperArm();
    lowerArm();
    palm();
    glPopMatrix();

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

    calf();
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    calf();
    glPopMatrix();

    feet();
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    feet();
    glPopMatrix();

    innerCloth();

    outerCloth();


    glFlush();
}

void key2() {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1, 1, 1);


    //upper body
    {
        glPushMatrix();
        // Move pivot point to origin
        glTranslatef(0, 0.24, 0);

        glRotatef(bodyX, 1, 0, 0);
        glRotatef(bodyY, 0, 1, 0);
        glRotatef(bodyZ, 0, 0, 1);

        // Move back to original pivot location
        glTranslatef(0, -0.24, 0);

        //Push Head Rotation
        {
            glPushMatrix();
            // Move pivot point to origin
            glTranslatef(0, 0.6, -0.015);

            glRotatef(headX, 1, 0, 0);
            glRotatef(headY, 0, 1, 0);
            glRotatef(headZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0, -0.6, 0.015);

            hair();
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);
            hair();
            glPopMatrix();
            head();
            glPopMatrix();

            neck();
        }


        //Push Upper Arm Rotation
        {
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.13, 0.52, -0.02);

            glRotatef(LUArmX, 1, 0, 0);
            glRotatef(LUArmY, 0, 1, 0);
            glRotatef(LUArmZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.13, -0.52, 0.02);

            upperArm();


            //Push Lower Arm Rotation
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.16, 0.36, -0.05);

            glRotatef(LLArmX, 1, 0, 0);
            glRotatef(LLArmY, 0, 1, 0);
            glRotatef(LLArmZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.16, -0.36, 0.05);

            lowerArm();

            //Push Lower Arm Rotation
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.20, 0.07, -0.02);

            glRotatef(LPArmX, 1, 0, 0);
            glRotatef(LPArmY, 0, 1, 0);
            glRotatef(LPArmZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.20, -0.07, 0.02);

            glPushMatrix();
            glTranslatef(-0.2, 0.02, 0.65);
            glRotatef(-90, 0, 1, 0);
            glRotatef(90, 0, 0, 1);
            sword();
            glPopMatrix();

            palm();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        {
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);
            //Push Upper Arm Rotation
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.13, 0.52, -0.02);

            glRotatef(RUArmX, 1, 0, 0);
            glRotatef(RUArmY, 0, 1, 0);
            glRotatef(RUArmZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.13, -0.52, 0.02);

            upperArm();


            //Push Lower Arm Rotation
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.16, 0.36, -0.05);

            glRotatef(RLArmX, 1, 0, 0);
            glRotatef(RLArmY, 0, 1, 0);
            glRotatef(RLArmZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.16, -0.36, 0.05);

            lowerArm();

            //Push Lower Arm Rotation
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.20, 0.07, -0.02);

            glRotatef(RPArmX, 1, 0, 0);
            glRotatef(RPArmY, 0, 1, 0);
            glRotatef(RPArmZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.20, -0.07, 0.02);

            palm();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        body();

        glPopMatrix();

    }

    //lower body
    {
        //Upper leg
        {
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.05, 0.19, 0);

            glRotatef(LULegX, 1, 0, 0);
            glRotatef(LULegY, 0, 1, 0);
            glRotatef(LULegZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.05, -0.19, 0);

            thigh();


            //Lower leg
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.07, -0.32, 0);

            glRotatef(LLLegX, 1, 0, 0);
            glRotatef(LLLegY, 0, 1, 0);
            glRotatef(LLLegZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.07, 0.32, 0);

            calf();

            //Feet
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.05, -0.62, 0);

            glRotatef(LFLegX, 1, 0, 0);
            glRotatef(LFLegY, 0, 1, 0);
            glRotatef(LFLegZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.05, 0.62, 0);

            feet();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        //Right side
        {
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);

            //Upper leg
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.05, 0.19, 0);

            glRotatef(RULegX, 1, 0, 0);
            glRotatef(RULegY, 0, 1, 0);
            glRotatef(RULegZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.05, -0.19, 0);

            thigh();


            //Lower leg
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.07, -0.32, 0);

            glRotatef(RLLegX, 1, 0, 0);
            glRotatef(RLLegY, 0, 1, 0);
            glRotatef(RLLegZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.07, 0.32, 0);

            calf();

            //Feet
            glPushMatrix();

            // Move pivot point to origin
            glTranslatef(-0.05, -0.62, 0);

            glRotatef(RFLegX, 1, 0, 0);
            glRotatef(RFLegY, 0, 1, 0);
            glRotatef(RFLegZ, 0, 0, 1);

            // Move back to original pivot location
            glTranslatef(0.05, 0.62, 0);

            feet();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        innerCloth();
        outerCloth();
    }
}

void key4() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(1, 1, 1);


    glPushMatrix();
    applyAnimation();
    head();            // draw your object
    glPopMatrix();
}

void display()
{
    switch (qNo) {
    case 1:
        key1();
        break;
    case 2:
        key2();
        break;
    case 4:
        key4();
        break;
    default:
        key1();
        break;
   }
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

    startPhase(0);

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