
#include "Game.h"

int main() {
    Game * game = new Game();

    eng::Engine engine;

    engine.SetApplication(game);

    if (engine.Initialize()) {
        engine.Run();
    }
    engine.Shutdown();

    return 0;
}