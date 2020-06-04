#include <iostream>
#include "./Constants.h"
#include "./Game.h"

int main(int argc, char *args[]){
    Game* game = new Game(); 

    game -> Initialize( WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game->IsRunning()){
        game-> Update();
        game-> ProcessInput();
        game-> Render();
    }
    game->Destroy();
    std::cout<< "Game is running..."<<"\n";
    return 0;
}