#ifndef USERINTERFACE_SDL_H
#define USERINTERFACE_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "userinterface.h"
#include "droneschool.h"
#include "item.h"
#include "texture.h"

#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

#include <ctime>
#include <ratio>
#include <chrono>
#include <thread>


namespace {
    const double FRAMES_PER_SEC = 60;
}



class CUserInterface_SDL : public IUserInterface {
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
                                        1200, 800, 0);
        if (!m_window) return false;


        // triggers the program that controls
        // your graphics hardware and sets flags
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    
        // creates a renderer to render our images
        m_renderer = SDL_CreateRenderer(m_window, -1, render_flags);
        if (!m_renderer) return false;

        return true;
    }

    void registerTexture(const std::string & name, const std::string & path) {
        auto texture = std::make_shared<CTexture> ();
        if (! texture->loadFromFile(path, m_renderer)) {
            throw std::invalid_argument("failed to load texture");
        }
        m_textureByName[name] = texture;
    }

    void animationLoop() {
        using namespace std::chrono;
        auto FRAME_DURATION = milliseconds(1000) / FRAMES_PER_SEC;
        high_resolution_clock::time_point timeLast = high_resolution_clock::now();
        while (m_close == false) {
            // Events from user actions
            handleEvents();
            // Update entities
            update();
            // Render new animation frame 
            renderFrame();

            // Calculates time to wait for 60 FRAMES PER SECOND
            high_resolution_clock::time_point timeNow = high_resolution_clock::now();
            auto timeElapsed = duration_cast<milliseconds>(timeNow - timeLast);
            auto timeToWait = FRAME_DURATION - timeElapsed;
            std::this_thread::sleep_for(timeToWait);
            timeLast = timeNow;
        }
    }

    private:
    void handleEvents() {
        SDL_Event event;

        CRemoteControl * pRemote = nullptr;
        TUserInputAction userActions;
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
                    userActions.m_forward = true;
                    break;
                case SDL_SCANCODE_S:
                    userActions.m_backward = true;
                    break;
                case SDL_SCANCODE_A:
                    userActions.m_turnLeft = true;
                    break;
                case SDL_SCANCODE_D:
                    userActions.m_turnRight = true;
                    break;
                case SDL_SCANCODE_RETURN:
                    userActions.m_pick = true;
                    break;
                case SDL_SCANCODE_LEFT:
                    break;
                case SDL_SCANCODE_RIGHT:
                    break;

                case SDL_SCANCODE_SPACE:
                    break;
                default:
                    break;
                }
            }
        }
        // assign user Actions
        m_userActions = userActions;
    }

    void update() {
        m_droneSchool.update();
    }

    void renderItem (const IItem * item) {
        CCoord position = item->getPosition();

        auto texture = m_textureByName.at(item->getTextureName());

        SDL_FRect dest = {(float)position.x - item->getWidth() / 2.0f, 
                          (float)position.y - item->getHeight() / 2.0f, 
                          (float)item->getWidth(), 
                          (float)item->getHeight()};
        SDL_RenderCopyExF(m_renderer, texture->getData(), NULL, &dest, 360.0-item->getAngle(), NULL, (SDL_RendererFlip)0);
        
    }

    void renderFrame() {
        // clears the screen
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(m_renderer);

        // Render Items
        const auto & items = m_droneSchool.getItems();
        for (auto item : items) {
            renderItem(item.get());
        }

        // Render Drone
        const auto & drone = m_droneSchool.getDrone();
        renderItem(drone);
                
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(m_renderer);
    }

    private:
        CDroneSchool &  m_droneSchool;
        SDL_Window *    m_window;
        SDL_Renderer *  m_renderer;
        bool            m_close;
        std::map <std::string, std::shared_ptr<CTexture>>   m_textureByName;
};
#endif // USERINTERFACE_H