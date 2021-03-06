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
#include "Armory.h"
#include "Camera.h"
#include "ClientSocket.h"
#include "DoubleBuffer.h"
#include "Font.h"
#include "GameSoundEffects.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
#include "Stage.h"
#include "Stream.h"
#include "TextureManager.h"
#include "Water.h"
#include "Weapons/Bullet.h"
#include "Weapons/Explosion.h"
#include "Wind.h"
#include "Window.h"
#include "Worm.h"
#include "BackgroundMusic.h"
#include "GameBackgroundMusic.h"
#include "BackgroundMusicPlayer.h"

namespace GUI {
using GameOutput = IO::Stream<IO::PlayerMsg>;
class Game {
   public:
    bool youWin{false};

    Game(Window &w, Worms::Stage &&stage, std::vector<std::string> &backgroundPaths, ClientSocket &socket,
             std::uint8_t team);
    ~Game();
    void start();
    void update(float dt);
    void render();

    void exit();

   private:
    void renderStatic();
    void renderBackground();
    void handleCamera(float dt);

    void inputWorker();
    void outputWorker();

    std::atomic<bool> quit{false};
    float scale{13.0f};            // pixels per meter
    float lastCameraUpdate{0.0f};  // pixels per meter
    Window &window;
    GameTextureManager texture_mgr;
    GameSoundEffectManager sound_effect_mgr;
    GameBackgroundMusicManager background_music_mgr;
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
    std::uint8_t team{0};
    uint8_t explodedQuantity{0};
    GUI::Wind wind;
    GUI::Water water;
    std::unique_ptr<Animation> currentPlayerArrow{nullptr};
    std::unique_ptr<GUI::BackgroundMusicPlayer> backGroundMusicPlayer{nullptr};
    
    void loadTextureManager();
    void loadBackgroundManager();
    void loadSoundManager();
};
}  // namespace GUI

#endif  //__GUIGame_H__
