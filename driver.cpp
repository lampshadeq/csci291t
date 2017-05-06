/*******************************************************************************
*
*******************************************************************************/
#ifdef _WIN32
  #define WINDOWS_LEAN_AND_MEAN
  #define NOMINMAX
#endif

#include <GLScene.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>

using namespace std;

bool             createGLWindow(char*, int, int, int, bool);
GLvoid           killGLWindow(bool);
LRESULT CALLBACK windowProcedure(HWND, UINT, WPARAM, LPARAM);

bool      active, keys[256];
GLScene*  scene;
HDC       deviceContext;
HGLRC     renderingContext;
HINSTANCE inst;
HWND      handler;

/*******************************************************************************
* The starting point of the program.
*
* @params
*   currInst  - the current instance of the program
*   prevInst  - the previous instance of the program
*   cmdParams - command line parameters
*   showState - window show state
*
* @output
*   0 if successful, 1 otherwise
*******************************************************************************/
int WINAPI WinMain(HINSTANCE currInst, HINSTANCE prevInst, LPSTR cmdParams,
                   int showState) {
  bool  done, fullscreen;
  char* title;
  int   bits, fullscreenWidth, fullscreenHeight;
  MSG   msg;

  // Initialize variables
  active           = true;
  done             = false;
  bits             = 256;
  title            = "Chicken Cheese Crusaders";
  scene            = new GLScene();
  deviceContext    = NULL;
  renderingContext = NULL;
  handler          = NULL;

  // Get the fullscreen dimensions
  fullscreenWidth  = GetSystemMetrics(SM_CXSCREEN);
  fullscreenHeight = GetSystemMetrics(SM_CYSCREEN);

  // Set the full screen mode as default
  fullscreen = true;

  // Create the OpenGL window
  if (!createGLWindow(title, fullscreenWidth, fullscreenHeight, bits,
                      fullscreen)) {
    return 1;
  }

  // Game loop
  while (!done) {
    // Check if there is a message waiting
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      // Quit message received
      if (msg.message == WM_QUIT) {
        done = true;
      }

      // Process the message
      else {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    // No message
    else {
      // Draw the scene, watching for ESC key or a quit signal
      if ((active && !scene->draw()) || (keys[VK_ESCAPE])) {
        done = true;
      }

      // Not quitting, so update the screen using double-buffering technique
      else {
        SwapBuffers(deviceContext);
      }

      // Check if F1 is being pressed
      if (keys[VK_F1]) {
        // Update the F1 key status and fullscreen flag
        keys[VK_F1] = false;
        fullscreen  = !fullscreen;

        // Kill the current window
        killGLWindow(fullscreen);

        // Recreate the window
        if (!createGLWindow(title, fullscreenWidth, fullscreenHeight, bits,
                            fullscreen)) {
          return 1;
        }
      }
    }
  }

  // Cleanup and quit
  killGLWindow(fullscreen);
  delete scene;
  return msg.wParam;
}

/*******************************************************************************
* Create the OpenGL window.
*
* @params
*   title      - the title to appear at the top of the window
*   width      - the width of the window
*   height     - the height of the window
*   bits       - the number of bits to be used for the color display
*   fullscreen - true if the user is requesting fullscreen mode, false otherwise
*
* @output
*   true if successfully created the window, false otherwise
*******************************************************************************/
bool createGLWindow(char* title, int width, int height, int bits,
                    bool fullscreen) {
  GLuint    pixelFormat;
  DEVMODE   dmScreenSettings;
  DWORD     style, extStyle;
  RECT      windowRect;
  WNDCLASS  wc;

  // Setup the window's rectangle
  windowRect.left   = (long) 0;
  windowRect.right  = (long) width;
  windowRect.top    = (long) 0;
  windowRect.bottom = (long) height;

  // Grab the current instance of the window
  inst = GetModuleHandle(NULL);

  // Setup the window class structure
  wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc   = (WNDPROC) windowProcedure;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = inst;
  wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = "OpenGL";

  // Register the window class
  if (!RegisterClass(&wc)) {
    MessageBox(NULL, "Failed to register the window class.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Switch to fullscreen mode
  if (fullscreen) {
    // Clear the memory
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

    // Setup the screen settings
    dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth  = width;
    dmScreenSettings.dmPelsHeight = height;
    dmScreenSettings.dmBitsPerPel = bits;
    dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH |
                                    DM_PELSHEIGHT;
  }

  // Set the styles
  if (fullscreen) {
    style    = WS_POPUP;
    extStyle = WS_EX_APPWINDOW;

    ShowCursor(false);
  }
  else {
    style    = WS_OVERLAPPEDWINDOW;
    extStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  }

  // Adjust the window to the true requested size
  AdjustWindowRectEx(&windowRect, style, false, extStyle);

  // Create the window
  handler = CreateWindowEx(extStyle, "OpenGL", title,
                           style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0,
                           windowRect.right - windowRect.left,
                           windowRect.bottom - windowRect.top, NULL, NULL,
                           inst, NULL);
  if (!handler) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "Window creation error.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Create the pixel format descriptor
  static PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
    bits, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0,
    0, 0
  };

  // Get the device context
  deviceContext = GetDC(handler);
  if (!deviceContext) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "Could not create GL device context.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Get the pixel format
  pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
  if (!pixelFormat) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "Could not find suitable pixel format.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Set the pixel format
  if (!SetPixelFormat(deviceContext, pixelFormat, &pfd)) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "Could not set the pixel format.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Get the rendering context
  renderingContext = wglCreateContext(deviceContext);
  if (!renderingContext) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "Could not create GL rendering context.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Active the rendering context
  if (!wglMakeCurrent(deviceContext, renderingContext)) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "Could not activate the GL rendering context.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  // Show the window at a slightly higher priority with keyboard focus
  ShowWindow(handler, SW_SHOW);
  SetForegroundWindow(handler);
  SetFocus(handler);

  // Setup and initialize our perspective OpenGL screen
  scene->resizeScene(width, height);
  if (!scene->init()) {
    killGLWindow(fullscreen);
    MessageBox(NULL, "OpenGL initialization failed.", "ERROR",
               MB_OK | MB_ICONEXCLAMATION);

    return false;
  }

  return true;
}

/*******************************************************************************
* Kill the OpenGL window, including resource clean-up.
*
* @params
*   fullscreen - true if the user is requesting fullscreen mode, false otherwise
*******************************************************************************/
GLvoid killGLWindow(bool fullscreen) {
  // Switch back to desktop mode and show the cursor
  if (fullscreen) {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(true);
  }

  // Release and delete the rendering context
  if (renderingContext) {
    if (!wglMakeCurrent(NULL, NULL)) {
      MessageBox(NULL,
                 "Release of device context and rendering context failed.",
                 "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    }

    if (!wglDeleteContext(renderingContext)) {
      MessageBox(NULL, "Deletion of rendering context failed.",
                 "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    }

    renderingContext = NULL;
  }

  // Release the device context
  if (deviceContext && !ReleaseDC(handler, deviceContext)) {
    MessageBox(NULL, "Release of device context failed.", "SHUTDOWN ERROR",
               MB_OK | MB_ICONINFORMATION);

    deviceContext = NULL;
  }

  // Destroy the window handler
  if (handler && !DestroyWindow(handler)) {
    MessageBox(NULL, "Release of handler failed.", "SHUTDOWN ERROR",
               MB_OK | MB_ICONINFORMATION);

    handler = NULL;
  }

  // Unregister the instance class
  if (!UnregisterClass("OpenGL", inst)) {
    MessageBox(NULL, "Could not unregister the instance class.",
               "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

    inst = NULL;
  }
}

/*******************************************************************************
* The window procedure.
*
* @params
*   h   - the handler for this window
*   msg - message for this window
*   wp  - additional message information
*   lp  - additional message information
*
* @output
*   0 if the message was handled, calls the default procedure otherwise
*******************************************************************************/
LRESULT CALLBACK windowProcedure(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
  bool flag;

  // Pass the message to the scene
  scene->windowMsg(h, msg, wp, lp);

  // Check what kind of message the window received
  flag = true;
  switch (msg) {
    // Activate event
    case WM_ACTIVATE:
      // Check minimization state
      if (!HIWORD(wp)) {
        active = true;
      }
      else {
        active = false;
      }
      break;

    // System command event
    case WM_SYSCOMMAND:
      // Check the system call
      switch (wp) {
        // Screensaver mode or powersave mode, prevent them
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
          break;

        default:
          flag = false;
          break;
      }
      break;

    // Close event, send a quit message
    case WM_CLOSE:
      PostQuitMessage(0);
      break;

    // Key down event
    case WM_KEYDOWN:
      keys[wp] = true;
      break;

    // Key up event
    case WM_KEYUP:
      keys[wp] = false;
      break;

    // All other events
    default:
      flag = false;
      break;
  }

  // Passed unhandled messages to the default procedure
  if (flag) {
    return 0;
  }
  else {
    return DefWindowProc(h, msg, wp, lp);
  }
}
