/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GUIGame_H__
#define __GUIGame_H__

#include <atomic>
#include <list>
#include <thread>
#include <vector>

#include "Animation.h"
#include "Bullet.h"
#include "Camera.h"
#include "ClientSocket.h"
#include "DoubleBuffer.h"
#include "Explosion.h"
#include "Font.h"
#include "GameSoundEffects.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
#include "Stage.h"
#include "Stream.h"
#include "TextureManager.h"
#include "Window.h"
#include "Worm.h"
#include "Armory.h"

namespace GUI {
using GameOutput = IO::Stream<IO::PlayerMsg>;
class Game {
   public:
    Game(Window &w, Worms::Stage &&stage, ClientSocket &socket);
    ~Game();
    void start();
    void update(float dt);
    void render();

   private:
    void render_controls();
    void renderBackground();

    void inputWorker();
    void outputWorker();

    std::atomic<bool> quit{false};
    float scale{13.0f};  // pixels per meter
    Window &window;
    GameTextureManager texture_mgr;
    GameSoundEffectManager sound_effect_mgr;
    std::vector<Worm::Worm> worms;
    Worms::Stage stage;
    std::list<std::shared_ptr<Ammo::Bullet>> bullets;
    Camera cam;
    Font font;
    SDL_Color backgroundColor{0xba, 0x8d, 0xc6};
    std::vector<SDL_Color> teamColors;
    Armory armory;
    std::thread inputThread;
    std::thread outputThread;
    IO::DoubleBuffer<IO::GameStateMsg> snapshotBuffer;
    IO::GameStateMsg snapshot;
    GameOutput output;
    CommunicationSocket &socket;
};
}  // namespace GUI

#endif  //__GUIGame_H__