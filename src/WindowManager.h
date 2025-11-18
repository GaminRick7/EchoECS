#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <glad/glad.h>

class WindowManager {
    public:
        void Init(const char * title, int width, int height, unsigned int positionX, unsigned int positionY);
        void Shutdown();
        void Update();
        bool ProcessEvents();
    
    private:
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
};
