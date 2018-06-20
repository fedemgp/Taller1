/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */
#include <iostream>
#include <string>

#include "Socket.h"
#include "GUIGame.h"
#include "LobbyAssistant.h"

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./client HOST PORT" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        std::string host = argv[1];
        std::string port = argv[2];
        ClientSocket socket(host.data(), port.data());

        GUI::Window window{};
        window.clear();
        //TODO start a thread running this
        GUI::LobbyAssistant lobby(socket, window);
        lobby.run();
        //TODO join Lobby thread

        socket = std::move(lobby.getSocket());

        GUI::Game game{window, Worms::Stage{}, socket};
        game.start();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unkown error in main thread" << std::endl;
        return 1;
    }
    return 0;
}
