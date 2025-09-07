#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <sstream>
#include <string>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#define WINDOW_TITLE "OpenGL Window"
#define PI 3.14159265359

struct Phase {
    // A class used for different "steps" to animation
    // Example: Each step has different rotations, duration, angle of rotation
    // Create an object and loop through the steps for animation

    double duration;   // seconds
    float rotX;          // ΔX rotation over duration
    float rotY;          // ΔY rotation
    float rotZ;          // ΔZ rotation
};

struct BodyPart {
    // Keeps track of transformation for this body part
    float rotX = 0, rotY = 0, rotZ = 0;   // accumulated rotation

    float startValX = 0, startValY = 0, startValZ = 0;
    float endValX = 0, endValY = 0, endValZ = 0;

    double phaseStartTime = 0;
    int currentPhase = 0;

    Phase* phases;
    int numPhases;

    static std::vector<BodyPart*>& getAllParts() {
        static std::vector<BodyPart*> parts;
        return parts;
    }

    BodyPart(Phase* p = nullptr, int n = 0)
        : phases(p), numPhases(n) {
        getAllParts().push_back(this);
    }

};

// Camera System Variables
// Camera System
struct Camera {
    float posX = 0.0f, posY = 0.0f, posZ = 3.0f;  // Camera position (closer to character)
    float targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;  // Look at target
    float upX = 0.0f, upY = 1.0f, upZ = 0.0f;  // Up vector
    
    // Projection settings
    bool isPerspective = true;  // true for perspective, false for orthographic
    float fov = 45.0f;  // Field of view for perspective
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    
    // Orthographic settings
    float orthoLeft = -5.0f;   // Smaller bounds = bigger character
    float orthoRight = 5.0f;
    float orthoBottom = -5.0f;
    float orthoTop = 5.0f;
    
    // Movement and rotation
    float moveSpeed = 0.5f;
    float rotationSpeed = 2.0f;
    float zoomSpeed = 0.1f;
    
    // Zoom limits
    float minZoom = 0.5f;
    float maxZoom = 50.0f;
    float currentZoom = 2.0f;  // Smaller zoom = bigger character
    
    // Mouse controls
    bool mouseDown = false;
    int lastMouseX = 0, lastMouseY = 0;
};
Camera camera;

float cameraYaw = 0.0f;    // left/right rotation (around Y-axis)
float cameraPitch = 0.0f;  // up/down rotation (around X-axis)
float rotationSpeed = 5.0f; // degrees per key press


int qNo = 2;
bool opposite = false; //toggle clockwise & counter clockwise rotations
bool toggleRight = false; //toggle left and right limbs
float RotationSpeed = 10; //set degree for each key press

//Key 2: Rotation
float speed2 = 1;
float headX = 0, headY = 0, headZ = 0;
float LUArmX = 0, LUArmY = 0, LUArmZ = 0;
float LLArmX = 0, LLArmY = 0, LLArmZ = 0;
float LPArmX = 0, LPArmY = 0, LPArmZ = 0;
float RUArmX = 0, RUArmY = 0, RUArmZ = 0;
float RLArmX = 0, RLArmY = 0, RLArmZ = 0;
float RPArmX = 0, RPArmY = 0, RPArmZ = 0;
float bodyX = 0, bodyY = 0, bodyZ = 0;
float LULegX = 0, LULegY = 0, LULegZ = 0;
float LLLegX = 0, LLLegY = 0, LLLegZ = 0;
float LFLegX = 0, LFLegY = 0, LFLegZ = 0;
float RULegX = 0, RULegY = 0, RULegZ = 0;
float RLLegX = 0, RLLegY = 0, RLLegZ = 0;
float RFLegX = 0, RFLegY = 0, RFLegZ = 0;

//Key 4: Rotation
Phase head4Phases[] = {
    {0, 10, 0, 0},
    {0.5, 10, 0, 0},
    {1, -15, 40, 25},
    {1, -20, 40, 35},
    {0.25, -45, -15, 0},
    {0.5, 5, -5, 0},
    {1, -5, -5, 0},
};
Phase LUArm4Phases[] = {
    {0, -45, -5, -25},
    {0.5, -45, -5, -25},
    {1, -45, -75, -50},
    {1, -45, -75, -50},
    {0.25, -35, -50, -80},
    {0.5, 160, -65, -115},
    {1, 160, -65, -115},
};
Phase LLArm4Phases[] = {
    {0, -85, -25, 25},
    {0.5, -85, -25, 25},
    {1, 30, -90, 35},
    {1, 30, -90, 35},
    {0.25, 40, -95, 15},
    {0.5, 25, -225, 35},
    {1, 25, -225, 35},
};
Phase LPArm4Phases[] = {
    {0, -55, 25, 5},
    {0.5, -55, 25, 5},
    {1, 65, 5, -10},
    {1, 65, 5, -10},
    {0.25, 50, -25, -10},
    {0.5, 0, -45, -10},
    {1, 10, -45, -10},
};
Phase RUArm4Phases[] = {
    {0, -90, 0, 40},
    {0.5, -90, 0, 40},
    {1, -50, 35, 20},
    {1, -50, 35, 20},
    {0.25, -30, -20, -25},
    {0.5, -65, -20, 10},
    {1, -65, -20, 10},
};
Phase RLArm4Phases[] = {
    {0, -20, 40, 5},
    {0.5, -20, 40, 5},
    {1, -10, 20, 55},
    {1, -10, 20, 55},
    {0.25, 5, 60, 0},
    {0.5, 10, 60, 5},
    {1, 10, 60, 5},
};
Phase RPArm4Phases[] = {
    {0, -35, 10, 0},
    {0.5, -35, 10, 0},
    {1, 30, -5, 30},
    {1, 30, -5, 30},
    {0.25, 5, -25, 30},
    {0.5, -15, -25, 30},
    {1, 0, -25, 55},
};
Phase body4Phases[] = {
    {0, -5, 0, 0},
    {0.5, -5, 0, 0},
    {1, 25, -105, -5},
    {1, 30, -100, -5},
    {0.25, 65, -20, 0},
    {0.5, 65, -10, 0},
    {1, 65, -10, 0},
};
Phase LULeg4Phases[] = {
    {0, -5, 0, -5},
    {0.5, -5, 0, -5},
    {1, -35, -10, -25},
    {1, -40, -10, -25},
    {0.25, -25, -15, -20},
    {0.5, -60, -15, -20},
    {1, -55, -15, -20},
};
Phase LLLeg4Phases[] = {
    {0, 10, 0, 0},
    {0.5, 10, 0, 0},
    {1, 50, 5, 5},
    {1, 55, 5, 5},
    {0.25, 115, 5, 5},
    {0.5, 120, 5, -30},
    {1, 120, 5, -30},
};
Phase LFLeg4Phases[] = {
    {0, -5, 0, 0},
    {0.5, -5, 0, 0},
    {1, -10, -15, 0},
    {1, -10, -15, 0},
    {0.25, -10, -15, 0},
    {0.5, -60, -15, 0},
    {1, -65, -15, 0},
};
Phase RULeg4Phases[] = {
    {0, -5, 0, -5},
    {0.5, -5, 0, -5},
    {1, 15, 15, -15},
    {1, 20, 15, -15},
    {0.25, 5, 15, -5},
    {0.5, 55, -10, -10},
    {1, 60, -10, -10},
};
Phase RLLeg4Phases[] = {
    {0, 10, 0, 0},
    {0.5, 10, 0, 0},
    {1, 35, 5, -15},
    {1, 40, 5, -15},
    {0.25, 40, 5, -15},
    {0.5, 5, 5, -15},
    {1, 0, 5, -15},
};
Phase RFLeg4Phases[] = {
    {0, -5, 0, 0},
    {0.5, -5, 0, 0},
    {1, -25, 5, 10},
    {1, -25, 5, 10},
    {0.25, -25, 5, 10},
    {0.5, -5, 5, 10},
    {1, -15, 5, 10},
};
BodyPart head4(head4Phases, sizeof(head4Phases) / sizeof(head4Phases[0]));
BodyPart LUArm4(LUArm4Phases, sizeof(LUArm4Phases) / sizeof(LUArm4Phases[0]));
BodyPart LLArm4(LLArm4Phases, sizeof(LLArm4Phases) / sizeof(LLArm4Phases[0]));
BodyPart LPArm4(LPArm4Phases, sizeof(LPArm4Phases) / sizeof(LPArm4Phases[0]));
BodyPart RUArm4(RUArm4Phases, sizeof(RUArm4Phases) / sizeof(RUArm4Phases[0]));
BodyPart RLArm4(RLArm4Phases, sizeof(RLArm4Phases) / sizeof(RLArm4Phases[0]));
BodyPart RPArm4(RPArm4Phases, sizeof(RPArm4Phases) / sizeof(RPArm4Phases[0]));
BodyPart body4(body4Phases, sizeof(body4Phases) / sizeof(body4Phases[0]));
BodyPart LULeg4(LULeg4Phases, sizeof(LULeg4Phases) / sizeof(LULeg4Phases[0]));
BodyPart LLLeg4(LLLeg4Phases, sizeof(LLLeg4Phases) / sizeof(LLLeg4Phases[0]));
BodyPart LFLeg4(LFLeg4Phases, sizeof(LFLeg4Phases) / sizeof(LFLeg4Phases[0]));
BodyPart RULeg4(RULeg4Phases, sizeof(RULeg4Phases) / sizeof(RULeg4Phases[0]));
BodyPart RLLeg4(RLLeg4Phases, sizeof(RLLeg4Phases) / sizeof(RLLeg4Phases[0]));
BodyPart RFLeg4(RFLeg4Phases, sizeof(RFLeg4Phases) / sizeof(RFLeg4Phases[0]));

//Key 5
Phase head5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 0, 20, 5},
};
Phase LUArm5Phases[] = {
    {0, 0, 0, 0},
    {1.5, -25, 0, 15},
    {2, -30, 0, -30},
};
Phase LLArm5Phases[] = {
    {0, 0, 0, 0},
    {1.5, -15, 0, 10},
    {2, 0, 0, -20},
};
Phase LPArm5Phases[] = {
    {0, 0, 0, 0},
    {1.5, -20, 0, 5},
    {2, 0, 0, 0},
};
Phase RUArm5Phases[] = {
    {0, 0, 0, 0},
    {1.5, -20, 0, 10},
    {2, -10, 0, -5},
};
Phase RLArm5Phases[] = {
    {0, 0, 0, 0},
    {1.5, -15, 0, 5},
    {2, 0, 0, 0},
};
Phase RPArm5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 0, 0, 0},
};
Phase body5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 10, -10, -5},
};
Phase LULeg5Phases[] = {
    {0, 0, 0, 0},
    {1.5, -15, 0, -10},
    {2, -40, -30, -15},
};
Phase LLLeg5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 30, 0, 0},
};
Phase LFLeg5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 0, 0, 0},
};
Phase RULeg5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 10, 0, -5},
    {2, 25, 40, -25},
};
Phase RLLeg5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 0, 0, 0},
};
Phase RFLeg5Phases[] = {
    {0, 0, 0, 0},
    {1.5, 0, 0, 0},
    {2, 0, 0, 0},
};


BodyPart head5(head5Phases, sizeof(head5Phases) / sizeof(head5Phases[0]));
BodyPart LUArm5(LUArm5Phases, sizeof(LUArm5Phases) / sizeof(LUArm5Phases[0]));
BodyPart LLArm5(LLArm5Phases, sizeof(LLArm5Phases) / sizeof(LLArm5Phases[0]));
BodyPart LPArm5(LPArm5Phases, sizeof(LPArm5Phases) / sizeof(LPArm5Phases[0]));
BodyPart RUArm5(RUArm5Phases, sizeof(RUArm5Phases) / sizeof(RUArm5Phases[0]));
BodyPart RLArm5(RLArm5Phases, sizeof(RLArm5Phases) / sizeof(RLArm5Phases[0]));
BodyPart RPArm5(RPArm5Phases, sizeof(RPArm5Phases) / sizeof(RPArm5Phases[0]));
BodyPart body5(body5Phases, sizeof(body5Phases) / sizeof(body5Phases[0]));
BodyPart LULeg5(LULeg5Phases, sizeof(LULeg5Phases) / sizeof(LULeg5Phases[0]));
BodyPart LLLeg5(LLLeg5Phases, sizeof(LLLeg5Phases) / sizeof(LLLeg5Phases[0]));
BodyPart LFLeg5(LFLeg5Phases, sizeof(LFLeg5Phases) / sizeof(LFLeg5Phases[0]));
BodyPart RULeg5(RULeg5Phases, sizeof(RULeg5Phases) / sizeof(RULeg5Phases[0]));
BodyPart RLLeg5(RLLeg5Phases, sizeof(RLLeg5Phases) / sizeof(RLLeg5Phases[0]));
BodyPart RFLeg5(RFLeg5Phases, sizeof(RFLeg5Phases) / sizeof(RFLeg5Phases[0]));

float swordDefenseAngle = 0.0f;
float swordDefenseSpeed = 90.0f;
float swordRotationSpeed = 90.0f;
int numSwords = 2;
float swordRadius = 0.8f;
float swordHeight = 0.3f;
float weaponSize = 1.0f;
bool swordDefenseActive = true;

float key5Time = 0.0f;
float key5AnimationSpeed = 0.9f;

int swordState = 0;  // 0=default, 1=both hands holding sword, 2=sword rotation only
int rotatingSwordCount = 2;

// Camera System Functions
void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (camera.isPerspective) {
        // Perspective projection using gluPerspective
        gluPerspective(camera.fov, 1.0f, camera.nearPlane, camera.farPlane);
    } else {
        // Orthographic projection using glOrtho
        float left = camera.orthoLeft * camera.currentZoom;
        float right = camera.orthoRight * camera.currentZoom;
        float bottom = camera.orthoBottom * camera.currentZoom;
        float top = camera.orthoTop * camera.currentZoom;
        glOrtho(left, right, bottom, top, camera.nearPlane, camera.farPlane);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void setupView() {
    glLoadIdentity();
    gluLookAt(camera.posX, camera.posY, camera.posZ,
              camera.targetX, camera.targetY, camera.targetZ,
              camera.upX, camera.upY, camera.upZ);
}

void updateCamera() {
    // Update camera position based on current zoom
    float distance = sqrt((camera.posX - camera.targetX) * (camera.posX - camera.targetX) +
                         (camera.posY - camera.targetY) * (camera.posY - camera.targetY) +
                         (camera.posZ - camera.targetZ) * (camera.posZ - camera.targetZ));
    
    if (distance > 0) {
        float ratio = camera.currentZoom / distance;
        camera.posX = camera.targetX + (camera.posX - camera.targetX) * ratio;
        camera.posY = camera.targetY + (camera.posY - camera.targetY) * ratio;
        camera.posZ = camera.targetZ + (camera.posZ - camera.targetZ) * ratio;
    }
}

void rotateCamera(float deltaYaw, float deltaPitch) {
    // Convert to radians
    float yawRad = deltaYaw * PI / 180.0f;
    float pitchRad = deltaPitch * PI / 180.0f;
    
    // Calculate camera direction vector
    float dirX = camera.posX - camera.targetX;
    float dirY = camera.posY - camera.targetY;
    float dirZ = camera.posZ - camera.targetZ;
    
    // Rotate around Y axis (yaw)
    float cosYaw = cos(yawRad);
    float sinYaw = sin(yawRad);
    float newDirX = dirX * cosYaw + dirZ * sinYaw;
    float newDirZ = -dirX * sinYaw + dirZ * cosYaw;
    dirX = newDirX;
    dirZ = newDirZ;
    
    // Rotate around X axis (pitch) - limit pitch to avoid gimbal lock
    float cosPitch = cos(pitchRad);
    float sinPitch = sin(pitchRad);
    float newDirY = dirY * cosPitch - dirZ * sinPitch;
    newDirZ = dirY * sinPitch + dirZ * cosPitch;
    dirY = newDirY;
    dirZ = newDirZ;
    
    // Update camera position
    camera.posX = camera.targetX + dirX;
    camera.posY = camera.targetY + dirY;
    camera.posZ = camera.targetZ + dirZ;
}

void moveCamera(float deltaX, float deltaY, float deltaZ) {
    camera.posX += deltaX * camera.moveSpeed;
    camera.posY += deltaY * camera.moveSpeed;
    camera.posZ += deltaZ * camera.moveSpeed;
    
    camera.targetX += deltaX * camera.moveSpeed;
    camera.targetY += deltaY * camera.moveSpeed;
    camera.targetZ += deltaZ * camera.moveSpeed;
}

void zoomCamera(float delta) {
    camera.currentZoom += delta * camera.zoomSpeed;
    
    // Apply zoom limits
    if (camera.currentZoom < camera.minZoom) {
        camera.currentZoom = camera.minZoom;
    } else if (camera.currentZoom > camera.maxZoom) {
        camera.currentZoom = camera.maxZoom;
    }
    
    updateCamera();
}

void resetCamera() {
    // Reset camera
    camera.posX = 0.0f;
    camera.posY = 0.0f;
    camera.posZ = 3.0f;  // Closer to character
    camera.targetX = 0.0f;
    camera.targetY = 0.0f;
    camera.targetZ = 0.0f;
    camera.currentZoom = 2.0f;  // Bigger character by default
    camera.isPerspective = true;
    cameraYaw = 0.0f;
    cameraPitch = 0.0f;
    
    // Reset all character animation variables to default
    headX = 0; headY = 0; headZ = 0;
    LUArmX = 0; LUArmY = 0; LUArmZ = 0;
    LLArmX = 0; LLArmY = 0; LLArmZ = 0;
    LPArmX = 0; LPArmY = 0; LPArmZ = 0;
    RUArmX = 0; RUArmY = 0; RUArmZ = 0;
    RLArmX = 0; RLArmY = 0; RLArmZ = 0;
    RPArmX = 0; RPArmY = 0; RPArmZ = 0;
    bodyX = 0; bodyY = 0; bodyZ = 0;
    LULegX = 0; LULegY = 0; LULegZ = 0;
    LLLegX = 0; LLLegY = 0; LLLegZ = 0;
    LFLegX = 0; LFLegY = 0; LFLegZ = 0;
    RULegX = 0; RULegY = 0; RULegZ = 0;
    RLLegX = 0; RLLegY = 0; RLLegZ = 0;
    RFLegX = 0; RFLegY = 0; RFLegZ = 0;
    
    // Reset toggle states
    opposite = false;
    toggleRight = false;
    
    // Reset mode to default
    qNo = 2;
}


void printRotations() {
    std::ostringstream oss;

    oss << "Head: (" << headX << ", " << headY << ", " << headZ << ")\n";
    oss << "Left Upper Arm: (" << LUArmX << ", " << LUArmY << ", " << LUArmZ << ")\n";
    oss << "Left Lower Arm: (" << LLArmX << ", " << LLArmY << ", " << LLArmZ << ")\n";
    oss << "Left Palm: (" << LPArmX << ", " << LPArmY << ", " << LPArmZ << ")\n";
    oss << "Right Upper Arm: (" << RUArmX << ", " << RUArmY << ", " << RUArmZ << ")\n";
    oss << "Right Lower Arm: (" << RLArmX << ", " << RLArmY << ", " << RLArmZ << ")\n";
    oss << "Right Palm: (" << RPArmX << ", " << RPArmY << ", " << RPArmZ << ")\n";
    oss << "Body: (" << bodyX << ", " << bodyY << ", " << bodyZ << ")\n";
    oss << "Left Upper Leg: (" << LULegX << ", " << LULegY << ", " << LULegZ << ")\n";
    oss << "Left Lower Leg: (" << LLLegX << ", " << LLLegY << ", " << LLLegZ << ")\n";
    oss << "Left Foot: (" << LFLegX << ", " << LFLegY << ", " << LFLegZ << ")\n";
    oss << "Right Upper Leg: (" << RULegX << ", " << RULegY << ", " << RULegZ << ")\n";
    oss << "Right Lower Leg: (" << RLLegX << ", " << RLLegY << ", " << RLLegZ << ")\n";
    oss << "Right Foot: (" << RFLegX << ", " << RFLegY << ", " << RFLegZ << ")\n";

    std::string message = oss.str();
    MessageBox(NULL, message.c_str(), "Body Coordinates", MB_OK);
}


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        switch (wParam) {
            // Enhanced Camera Controls
        case 'W':
            // Rotate camera pitch up
            cameraPitch -= rotationSpeed;
            rotateCamera(0, -rotationSpeed);
            break;
        case 'S':
            // Rotate camera pitch down
            cameraPitch += rotationSpeed;
            rotateCamera(0, rotationSpeed);
            break;
        case 'A':
            cameraYaw += rotationSpeed;
            rotateCamera(rotationSpeed, 0);
            break;
        case 'D':
            cameraYaw -= rotationSpeed;
            rotateCamera(-rotationSpeed, 0);
            break;
            
            // Pitch controls (up/down rotation)
        case VK_F1:
            cameraPitch -= rotationSpeed;
            rotateCamera(0, -rotationSpeed);
            break;
        case VK_F2:
            cameraPitch += rotationSpeed;
            rotateCamera(0, rotationSpeed);
            break;
            
            // Camera Movement
        case VK_UP:
            moveCamera(0, camera.moveSpeed, 0);
            break;
        case VK_DOWN:
            moveCamera(0, -camera.moveSpeed, 0);
            break;
        case VK_LEFT:
            moveCamera(-camera.moveSpeed, 0, 0);
            break;
        case VK_RIGHT:
            moveCamera(camera.moveSpeed, 0, 0);
            break;
        case VK_PRIOR:  // Page Up
            moveCamera(0, 0, camera.moveSpeed);
            break;
        case VK_NEXT:   // Page Down
            moveCamera(0, 0, -camera.moveSpeed);
            break;
            
            // Zoom Controls (now only mouse wheel)
            
            // Projection Toggle
        case VK_OEM_3:  // ` key - Toggle projection
            camera.isPerspective = !camera.isPerspective;
            break;
            
            // Reset Camera
        case VK_MENU:  // Alt key - Reset everything to default
            resetCamera();
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
        case '5':
            qNo = 5;
            break;
            
        case VK_SPACE:
            printRotations();
            break;
        case VK_OEM_4:  // '[' key - Decrease sword size
            if (qNo == 5) {
                weaponSize -= 0.2f;
                if (weaponSize < 0.5f) weaponSize = 0.5f; 
            }
            break;
        case VK_OEM_6:  // ']' key - Increase sword size
            if (qNo == 5) {
                weaponSize += 0.2f;
                if (weaponSize > 3.0f) weaponSize = 3.0f; 
            }
            break;
        case VK_OEM_1:  // ';' key - Decrease sword defense speed
            if (qNo == 5) {
                swordDefenseSpeed -= 30.0f;
                if (swordDefenseSpeed < 30.0f) swordDefenseSpeed = 30.0f;
            }
            break;
        case VK_OEM_7:  // ''' key - Increase sword rotation speed
            if (qNo == 5) {
                swordDefenseSpeed += 30.0f;
                if (swordDefenseSpeed > 300.0f) swordDefenseSpeed = 300.0f;  // Max speed: 300.0
            }
            break;
      
        case VK_OEM_2:  // / key - Increase sword state/rotating count
            if (qNo == 5) {
                if (swordState < 2) {
                    swordState++;  // 0->1->2 progression
                } else {
                    // When in state 2, increase rotating sword count
                    if (rotatingSwordCount < 5) rotatingSwordCount++;
                }
            }
            break;
        case VK_OEM_5:  // \ key - Decrease sword state/rotating count
            if (qNo == 5) {
                if (swordState == 2 && rotatingSwordCount > 2) {
                    rotatingSwordCount--;  // Decrease rotating sword count (but keep minimum 2)
                } else if (swordState > 0) {
                    swordState--;  // Decrease sword state (2->1->0)
                }
            }
            break;

            //Toggle keys
        case VK_SUBTRACT:
        case VK_OEM_MINUS:  // - key
            if (qNo == 2)
                opposite = !opposite;  // Toggle clockwise/counter-clockwise
            if (qNo == 4) 
                if (speed2 > 0.5)
                        speed2 -= 0.5;
            break;
        case VK_OEM_PLUS:  // = key
            if (qNo == 2)
                toggleRight = !toggleRight;  // Toggle left/right limbs
            if (qNo == 4)
                    speed2 += 0.5;
            break;
        case '[':
            if (qNo == 5) {
                weaponSize -= 0.1f;
                if (weaponSize < 0.1f) weaponSize = 0.1f;  // Min size: 0.1x
            }
            break;
        case ']':
            if (qNo == 5) {
                weaponSize += 0.1f;
                if (weaponSize > 2.0f) weaponSize = 2.0f;  // Max size: 2.0x
            }
            break;
        case ',':
            if (qNo == 5) {
                swordDefenseSpeed += 10.0f;
                if (swordDefenseSpeed > 200.0f) swordDefenseSpeed = 200.0f;  // Max speed: 200
            }
            break;
        case '.':
            if (qNo == 5) {
                swordDefenseSpeed -= 10.0f;
                if (swordDefenseSpeed < 10.0f) swordDefenseSpeed = 10.0f;  // Min speed: 10
            }
            break;

        if (qNo == 2) {
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
        case '9':
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

        case VK_OEM_COMMA:  // < key
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

        case VK_OEM_PERIOD:  // > key
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
        
    case WM_MOUSEMOVE:
        if (camera.mouseDown) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            
            int deltaX = mouseX - camera.lastMouseX;
            int deltaY = mouseY - camera.lastMouseY;
            
            // Rotate camera based on mouse movement
            rotateCamera(deltaX * 0.5f, deltaY * 0.5f);
            
            camera.lastMouseX = mouseX;
            camera.lastMouseY = mouseY;
        }
        break;
        
    case WM_LBUTTONDOWN:
        camera.mouseDown = true;
        camera.lastMouseX = LOWORD(lParam);
        camera.lastMouseY = HIWORD(lParam);
        break;
        
    case WM_LBUTTONUP:
        camera.mouseDown = false;
        break;
        
    case WM_MOUSEWHEEL:
        {
            int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            float zoomDelta = wheelDelta > 0 ? -1.0f : 1.0f;
            zoomCamera(zoomDelta);
        }
        break;
        
        default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

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

double getTime() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;
    return elapsed.count(); // seconds
}

void startPhase(BodyPart& part) {
    Phase& p = part.phases[part.currentPhase];

    part.startValX = part.rotX;
    part.startValY = part.rotY;
    part.startValZ = part.rotZ;

    // Instead of adding p.rotX, deduct the previous rotation
    if (part.currentPhase == 0) {
        // First phase is relative to zero
        part.endValX = part.startValX + p.rotX;
        part.endValY = part.startValY + p.rotY;
        part.endValZ = part.startValZ + p.rotZ;
    }
    else {
        Phase& prev = part.phases[part.currentPhase - 1];
        part.endValX = part.startValX + (p.rotX - prev.rotX);
        part.endValY = part.startValY + (p.rotY - prev.rotY);
        part.endValZ = part.startValZ + (p.rotZ - prev.rotZ);
    }

    part.phaseStartTime = getTime();
}

//might have speed error, lemme know if it happens
void applyAnimation(BodyPart& part) {
    double now = getTime();
    double elapsed = now - part.phaseStartTime;
    double t;
    Phase& p = part.phases[part.currentPhase];
    
    if (qNo == 4) {
        t = (elapsed * speed2) / p.duration;
    }
    else {
        t = elapsed / p.duration;
    }

    if (t > 1.0) t = 1.0;
    float curX = part.startValX + (part.endValX - part.startValX) * (float)t;
    float curY = part.startValY + (part.endValY - part.startValY) * (float)t;
    float curZ = part.startValZ + (part.endValZ - part.startValZ) * (float)t;

    // Apply interpolated transforms
    glRotatef(curX, 1, 0, 0);
    glRotatef(curY, 0, 1, 0);
    glRotatef(curZ, 0, 0, 1);

    if (t >= 1.0) {
        part.rotX = part.endValX;
        part.rotY = part.endValY;
        part.rotZ = part.endValZ;

        part.currentPhase++;
        if (part.currentPhase >= part.numPhases) {
            part.currentPhase = 0; // loop
            part.rotX = part.rotY = part.rotZ = 0;
        }
        startPhase(part);
    }
}

void startAnimation() {
    for (BodyPart* part : BodyPart::getAllParts()) {
        part->currentPhase = 0;
        startPhase(*part);
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
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup camera projection and view
    setupProjection();
    setupView();
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

    // Setup camera projection and view
    setupProjection();
    setupView();
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
            glTranslatef(-0.2, 0.02, 0.6);
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
        //innerCloth();
        //outerCloth();

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
    }
}

void key3(){}

void key4() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup camera projection and view
    setupProjection();
    setupView();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(1, 1, 1);

    //upper body
    {
        glPushMatrix();
        glTranslatef(0, 0.24, 0);
        applyAnimation(body4);
        glTranslatef(0, -0.24, 0);

        //Head
        {
            glPushMatrix();
            glTranslatef(0, 0.6, -0.015);
            applyAnimation(head4);
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

        //Upper Arm (Right Arm)
        {
            glPushMatrix();
            glTranslatef(-0.13, 0.52, -0.02);
            applyAnimation(LUArm4);
            glTranslatef(0.13, -0.52, 0.02);
            upperArm();

            //Lower Arm
            glPushMatrix();
            glTranslatef(-0.16, 0.36, -0.05);
            applyAnimation(LLArm4);
            glTranslatef(0.16, -0.36, 0.05);
            lowerArm();

            //Palm
            glPushMatrix();
            glTranslatef(-0.20, 0.07, -0.02);
            applyAnimation(LPArm4);
            glTranslatef(0.20, -0.07, 0.02);

            glPushMatrix();
            glTranslatef(-0.2, 0.02, 0.6);
            glRotatef(-90, 0, 1, 0);
            glRotatef(90, 0, 0, 1);
            sword();
            glPopMatrix();
            palm();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        //Upper Arm (Left Arm)
        {
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);
            glPushMatrix();
            glTranslatef(-0.13, 0.52, -0.02);
            applyAnimation(RUArm4);
            glTranslatef(0.13, -0.52, 0.02);
            upperArm();

            //Lower Arm
            glPushMatrix();
            glTranslatef(-0.16, 0.36, -0.05);
            applyAnimation(RLArm4);
            glTranslatef(0.16, -0.36, 0.05);
            lowerArm();

            //Palm
            glPushMatrix();
            glTranslatef(-0.20, 0.07, -0.02);
            applyAnimation(RPArm4);
            glTranslatef(0.20, -0.07, 0.02);
            palm();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        body();
        innerCloth();
        outerCloth();


        glPopMatrix();

    }

    //lower body
    {
        //Upper leg (Right leg)
        {
            glPushMatrix();
            glTranslatef(-0.05, 0.19, 0);
            applyAnimation(LULeg4);
            glTranslatef(0.05, -0.19, 0);
            thigh();

            //Lower leg
            glPushMatrix();
            glTranslatef(-0.07, -0.32, 0);
            applyAnimation(LLLeg4);
            glTranslatef(0.07, 0.32, 0);
            calf();

            //Feet
            glPushMatrix();
            glTranslatef(-0.05, -0.62, 0);
            applyAnimation(LFLeg4);
            glTranslatef(0.05, 0.62, 0);
            feet();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        //Upper leg (Left leg)
        {
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);

            //Upper leg
            glPushMatrix();
            glTranslatef(-0.05, 0.19, 0);
            applyAnimation(RULeg4);
            glTranslatef(0.05, -0.19, 0);
            thigh();

            //Lower leg
            glPushMatrix();
            glTranslatef(-0.07, -0.32, 0);
            applyAnimation(RLLeg4);
            glTranslatef(0.07, 0.32, 0);
            calf();

            //Feet
            glPushMatrix();
            glTranslatef(-0.05, -0.62, 0);
            applyAnimation(RFLeg4);
            glTranslatef(0.05, 0.62, 0);
            feet();

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

  
    }
}

void key5() {
    // Update animation time
    static auto lastTime = std::chrono::high_resolution_clock::now();
    static int lastQNo = -1;
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = currentTime - lastTime;
    lastTime = currentTime;
    
    // Reset all Key 5 body parts when switching to Key 5
    if (lastQNo != 5) {
        head5.currentPhase = 0;
        LUArm5.currentPhase = 0;
        LLArm5.currentPhase = 0;
        LPArm5.currentPhase = 0;
        RUArm5.currentPhase = 0;
        RLArm5.currentPhase = 0;
        RPArm5.currentPhase = 0;
        body5.currentPhase = 0;
        LULeg5.currentPhase = 0;
        LLLeg5.currentPhase = 0;
        LFLeg5.currentPhase = 0;
        RULeg5.currentPhase = 0;
        RLLeg5.currentPhase = 0;
        RFLeg5.currentPhase = 0;
        
        startPhase(head5);
        startPhase(LUArm5);
        startPhase(LLArm5);
        startPhase(LPArm5);
        startPhase(RUArm5);
        startPhase(RLArm5);
        startPhase(RPArm5);
        startPhase(body5);
        startPhase(LULeg5);
        startPhase(LLLeg5);
        startPhase(LFLeg5);
        startPhase(RULeg5);
        startPhase(RLLeg5);
        startPhase(RFLeg5);
        
        // Start with default sword state (only right hand holding sword)
        swordState = 0;
        rotatingSwordCount = 2;
        
        key5Time = 0.0f;
        lastQNo = 5;
    }
    
    key5Time += elapsed.count();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup camera projection and view
    setupProjection();
    setupView();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1, 1, 1);

    // Always show animated character for all sword states
    if (true) {
        // Draw the FULL character like Key 4 (attack mode)
    //upper body
    {
        glPushMatrix();
        glTranslatef(0, 0.24, 0);
        
        // Apply body rotation from phases
        applyAnimation(body5);
        
        glTranslatef(0, -0.24, 0);

        //Head
        {
            glPushMatrix();
            glTranslatef(0, 0.6, -0.015);
            
            // Apply head rotation from phases
            applyAnimation(head5);
            
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

        //Upper Arm (Right Arm)
        {
            glPushMatrix();
            glTranslatef(-0.13, 0.52, -0.02);
            
            // Apply right upper arm rotation from phases
            applyAnimation(RUArm5);
            
            glTranslatef(0.13, -0.52, 0.02);
            upperArm();

            //Lower Arm
            glPushMatrix();
            glTranslatef(-0.16, 0.36, -0.05);
            
            // Apply right lower arm rotation from phases
            applyAnimation(RLArm5);
            
            glTranslatef(0.16, -0.36, 0.05);
            lowerArm();

            //Palm
            glPushMatrix();
            glTranslatef(-0.20, 0.07, -0.02);
            
            // Apply right palm rotation from phases
            applyAnimation(RPArm5);
            
            glTranslatef(0.20, -0.07, 0.02);

            // Draw sword in right hand for Key 5 (all states)
            if (swordState >= 0) {
                glPushMatrix();
                glTranslatef(-0.2, 0.02, 0.6);
                glRotatef(-90, 0, 1, 0);
                glRotatef(90, 0, 0, 1);
                
                // Apply weapon size scaling
                glScalef(weaponSize, weaponSize, weaponSize);
                
                sword();
                glPopMatrix();
            }
            palm();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        //Upper Arm (Left Arm)
        {
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);
            glPushMatrix();
            glTranslatef(-0.13, 0.52, -0.02);
            
            // Apply left upper arm rotation from phases
            applyAnimation(LUArm5);
            
            glTranslatef(0.13, -0.52, 0.02);
            upperArm();

            //Lower Arm
            glPushMatrix();
            glTranslatef(-0.16, 0.36, -0.05);
            
            // Apply left lower arm rotation from phases
            applyAnimation(LLArm5);
            
            glTranslatef(0.16, -0.36, 0.05);
            lowerArm();

            //Palm
            glPushMatrix();
            glTranslatef(-0.20, 0.07, -0.02);
            
            // Apply left palm rotation from phases
            applyAnimation(LPArm5);
            
            glTranslatef(0.20, -0.07, 0.02);

            // Draw sword in left hand for Key 5 (states 1 and 2)
            if (swordState >= 1) {
                glPushMatrix();
                glTranslatef(-0.2, 0.02, 0.6);
                glRotatef(-90, 0, 1, 0);
                glRotatef(90, 0, 0, 1);
                
                // Apply weapon size scaling
                glScalef(weaponSize, weaponSize, weaponSize);
                
                sword();
                glPopMatrix();
            }
            palm();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        body();
        innerCloth();
        outerCloth();
        glPopMatrix();
    }

    //lower body
    {
        //Upper leg (Right leg)
        {
            glPushMatrix();
            glTranslatef(-0.05, 0.19, 0);
            
            // Apply right upper leg rotation from phases
            applyAnimation(RULeg5);
            
            glTranslatef(0.05, -0.19, 0);
            thigh();

            //Lower leg
            glPushMatrix();
            glTranslatef(-0.07, -0.32, 0);
            
            // Apply right lower leg rotation from phases
            applyAnimation(RLLeg5);
            
            glTranslatef(0.07, 0.32, 0);
            calf();

            //Feet
            glPushMatrix();
            glTranslatef(-0.05, -0.62, 0);
            
            // Apply right foot rotation from phases
            applyAnimation(RFLeg5);
            
            glTranslatef(0.05, 0.62, 0);
            feet();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }

        //Upper leg (Left leg)
        {
            glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);

            //Upper leg
            glPushMatrix();
            glTranslatef(-0.05, 0.19, 0);
            
            // Apply left upper leg rotation from phases
            applyAnimation(LULeg5);
            
            glTranslatef(0.05, -0.19, 0);
            thigh();

            //Lower leg
            glPushMatrix();
            glTranslatef(-0.07, -0.32, 0);
            
            // Apply left lower leg rotation from phases
            applyAnimation(LLLeg5);
            
            glTranslatef(0.07, 0.32, 0);
            calf();

            //Feet
            glPushMatrix();
            glTranslatef(-0.05, -0.62, 0);
            
            // Apply left foot rotation from phases
            applyAnimation(LFLeg5);
            
            glTranslatef(0.05, 0.62, 0);
            feet();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }
    }
    } else {
        // Default character drawing for state 0 (no animation)
        guide();
        glColor3f(1, 1, 1);
        neck();
        body();
        head();
        upperArm();
        lowerArm();
        
        // Draw sword in right hand for state 0 (default)
        if (swordState == 0) {
            glPushMatrix();
            glTranslatef(0.2, -0.07, 0.02);
            glTranslatef(-0.2, 0.02, 0.6);
            glRotatef(-90, 0, 1, 0);
            glRotatef(90, 0, 0, 1);
            glScalef(weaponSize, weaponSize, weaponSize);
            sword();
            glPopMatrix();
        }
        
        palm();
        thigh();
        calf();
        feet();
    }

    // Draw rotating swords around character for state 2
    if (swordState == 2) {
        glColor3f(1.0f, 0.0f, 0.0f);  // Red color for rotating swords
        
        for (int i = 0; i < rotatingSwordCount; i++) {
            glPushMatrix();
            
            // Calculate angle for this sword
            float angle = (360.0f / rotatingSwordCount) * i;
            
            // Add rotation based on time
            float rotationAngle = key5Time * swordDefenseSpeed;
            angle += rotationAngle;
            
            // Position sword in circle around character
            float x = cos(angle * PI / 180.0f) * swordRadius;
            float z = sin(angle * PI / 180.0f) * swordRadius;
            
            glTranslatef(x, swordHeight, z);
            glRotatef(angle, 0, 1, 0);  // Face outward from center
            
            // Apply weapon size scaling
            glScalef(weaponSize, weaponSize, weaponSize);
            
            sword();
            glPopMatrix();
        }
    }


    glFlush();
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
    case 3:
        key3();
        break;
    case 4:
        key4();
        break;
    case 5:
        key5();
        break;
    default:
        key1();
        break;
   }
}

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

    startAnimation();

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        display();

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            printRotations();
            Sleep(200);
        }

        SwapBuffers(hdc);
    }

    UnregisterClass(WINDOW_TITLE, wc.hInstance);

    return true;
}