/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>

#include "Color.h"
#include "Exception.h"

namespace GUI {
class Animation {
   public:
    Animation(const std::string &filename, SDL_Renderer &renderer, Color key);
    ~Animation();
    void update(float dt);
    void render(SDL_Renderer &renderer, int x, int y);
    void advanceFrame();
    void setFlip(SDL_RendererFlip flipType);
    SDL_RendererFlip getFlip();

   private:
    void free();
    /** SDL texture of the raw image. */
    SDL_Texture *texture{nullptr};
    /** Current animation frame. */
    int currentFrame{0};
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed{0.0f};
    /** Frames per seconds (should this be elsewere?). */
    float frameRate{1.0f / 30.0f};
    SDL_RendererFlip flipType{SDL_FLIP_NONE};
};
}  // namespace GUI

#endif  //__ANIMATION_H__
