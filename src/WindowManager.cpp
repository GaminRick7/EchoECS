#include "WindowManager.h"
#include <iostream>

void WindowManager::Init(const char * title, int width, int height, unsigned int positionX, unsigned int positionY){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    mWindow = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!mWindow) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    mGLContext = SDL_GL_CreateContext(mWindow);
    if (!mGLContext) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
    
    // Enable backface culling for better performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);  // Counter-clockwise winding order

    glViewport(0, 0, width, height);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}

void WindowManager::Shutdown(){
    if (mGLContext) {
        SDL_GL_DeleteContext(mGLContext);
        mGLContext = nullptr;
    }

    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void WindowManager::Update(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(mWindow);
}

bool WindowManager::ProcessEvents(){
    SDL_Event event;
    bool running = true;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    return running;
}