#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "droneschool.h"
#include "texture.h"
#include <vector>

class CUserInterface_SDL {
    public:
    CUserInterface_SDL (CDroneSchool & droneSchool)
    : m_droneSchool(droneSchool)
    , m_window(nullptr)
    , m_renderer(nullptr)
    , m_close(false) {
    }

    ~CUserInterface_SDL() {
        // destroy renderer
        SDL_DestroyRenderer(m_renderer);
    
        // destroy window
        SDL_DestroyWindow(m_window);
        
        // close SDL
        SDL_Quit();
    }

    bool init() {
        // returns zero on success else non-zero
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
        }
        m_window = SDL_CreateWindow("Drone School", // creates a window
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        1000, 1000, 0);
        if (!m_window) return false;


        // triggers the program that controls
        // your graphics hardware and sets flags
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    
        // creates a renderer to render our images
        m_renderer = SDL_CreateRenderer(m_window, -1, render_flags);
        if (!m_renderer) return false;

        if (!m_droneTextures.loadFromFile("resources/rod.png", m_renderer)) {
            return false;
        }
        if (!m_rectTexture.createFromRect(m_droneTextures.m_width/10, m_droneTextures.m_height/10, m_renderer)) {
            return false;
        }
        return true;
    }

    void animationLoop() {
        while (m_close == false) {
            // Events from user actions
            handleEvents();
            // Update entities
            update();
            // draw new animation frame 
            drawFrame();

            // calculates to 60 fps (I know I know, don't judge me.)
            SDL_Delay(1000 / 60);
        }
    }

    private:
    void handleEvents() {
        SDL_Event event;
        CSupervisor * pSupervisor = m_droneSchool.getSupervisor();
        if (pSupervisor == nullptr) { 
            std::cerr << "No supervisor!" << std::endl;
            m_close = false;
            return;
        }
        CRemoteControl * pRemote = pSupervisor->getRemote();

        // Events management
        while (SDL_PollEvent(&event)) {    
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                m_close = true;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    if (pRemote) pRemote->goForward();
                    break;
                case SDL_SCANCODE_S:
                    if (pRemote) pRemote->goBackward();
                    break;
                case SDL_SCANCODE_A:
                    if (pRemote) pRemote->turnLeft();
                    break;
                case SDL_SCANCODE_D:
                    if (pRemote) pRemote->turnRight();
                    break;
                case SDL_SCANCODE_LEFT:
                    pSupervisor->selectPrev();
                    break;
                case SDL_SCANCODE_RIGHT:
                    pSupervisor->selectPrev();
                    break;

                case SDL_SCANCODE_SPACE:
                    if (pRemote) pRemote->stop();
                    break;
                default:
                    break;
                }
            }
        }
    }

    void update() {
        m_droneSchool.updateDrones();
    }

    void drawFrame() {
        // clears the screen
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(m_renderer);

        // Render drones
        const auto & drones = m_droneSchool.getDrones();
        for (auto pDrone : drones) {
            CCoord position = pDrone->getPosition();
            SDL_FRect dest = {(float)position.x, (float)position.y, m_droneTextures.m_width/10.0f, m_droneTextures.m_height/10.0f};
            SDL_RenderCopyExF(m_renderer, m_droneTextures.getData(), NULL, &dest, pDrone->getAngle(), NULL, (SDL_RendererFlip)0);
            SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderDrawPointF(m_renderer, pDrone->getTarget().x, pDrone->getTarget().y);
        }
        
        // Render rectangle around selected drone
        CSupervisor * pSupervisor = m_droneSchool.getSupervisor();
        if (pSupervisor) {
            CRemoteControl * pRemote = pSupervisor->getSelectedDrone();
            if (pRemote) {
                CCoord p = pRemote->getDronesLocation();
                double angle = pRemote->getDronesAngle();
                SDL_FRect selectedDroneRect = {(float)p.x, (float)p.y, m_droneTextures.m_width/10.0f, m_droneTextures.m_height/10.0f};
                
                SDL_RenderCopyExF(m_renderer, m_rectTexture.getData(), nullptr, &selectedDroneRect, angle, nullptr, (SDL_RendererFlip)0);
            }
        }
        
        
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(m_renderer);
    }

    private:
        CDroneSchool &  m_droneSchool;
        SDL_Window *    m_window;
        SDL_Renderer *  m_renderer;
        bool            m_close;
        CTexture        m_droneTextures;
        CTexture        m_rectTexture;
};
#endif // USERINTERFACE_H