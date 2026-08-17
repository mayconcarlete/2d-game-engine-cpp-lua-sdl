#include <iostream>
#include <SDL3/SDL.h>
#include <Game/Game.hpp>

int main(int argc, char* argv[])
{
   Game game;

   game.Initialize();
   game.Run();

   game.Destroy();
   
   return 0;
}
