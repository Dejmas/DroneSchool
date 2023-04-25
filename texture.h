#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
class CUserInterface_SDL;

class CTexture {
    public:
    friend CUserInterface_SDL;
    CTexture ()
    : m_image(nullptr)
    , m_width(0)
    , m_height(0)
    {
    }

    ~CTexture() {
        // destroy texture
        SDL_DestroyTexture(m_image);
    }

    bool loadFromFile(const std::string & filename, SDL_Renderer * rend) {
        // creates a surface to load an image into the main memory
        SDL_Surface* surface;
    
        // please provide a path for your image
        surface = IMG_Load(filename.c_str());

        if (surface == nullptr) return false;
    
        // loads image to our graphics hardware memory.
        m_image = SDL_CreateTextureFromSurface(rend, surface);
        if (m_image == nullptr) return false;
    
        // clears main-memory
        SDL_FreeSurface(surface);
    
        // connects our texture with dest to control position
        SDL_QueryTexture(m_image, NULL, NULL, &m_width, &m_height);
        return true;
    }

    bool createFromRect(int width, int height, SDL_Renderer * rend) {
        // init reactangle
        SDL_Rect rect = {0, 0, width, height};

        // makes RGB surface same size as rectangle
        SDL_Surface * surface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

        if (surface == nullptr) return false;

        // printing rectangle in RGB surface
        SDL_Renderer * softwareRenderer = SDL_CreateSoftwareRenderer(surface);
        if (softwareRenderer == nullptr) return false;
        // SDL_SetRenderDrawColor(softwareRenderer, 0x00, 0x00, 0x00, 0x00);
        // SDL_RenderClear(softwareRenderer);
        SDL_SetRenderDrawColor(softwareRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(softwareRenderer, &rect);

        // makes texture from surface
        m_image = SDL_CreateTextureFromSurface(rend, surface);
        if (m_image == nullptr) return false;
        // clears surface
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(softwareRenderer);
        return true;
    }

    SDL_Texture * getData() const {
        return m_image;
    }

    private:
        SDL_Texture* m_image;
        int          m_width,
                     m_height;
};

#endif // TEXTURE_H