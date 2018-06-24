//
// Created by rodrigo on 24/06/18.
//

#ifndef INC_4_WORMS_CONNECTIONWINDOW_H
#define INC_4_WORMS_CONNECTIONWINDOW_H


#include <vector>

#include "Window.h"
#include "Font.h"
#include "GameStateMsg.h"
#include "GameWindow.h"
#include "Button.h"

#define CONNECT_MSG "Connect"
#define IP_FOCUS 0
#define PORT_FOCUS 1

namespace GUI {
    class ConnectionWindow : public GameWindow {
    public:
        uint8_t playersConnected{0};

        explicit ConnectionWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam);

        void start() override;
        void render() override;
        void appendCharacter(char text[32]) override;
        void buttonPressed(ScreenPosition sp) override;

    private:
        std::vector<Button> buttons;
        int textSize{50};
    };
}


#endif //INC_4_WORMS_CONNECTIONWINDOW_H
