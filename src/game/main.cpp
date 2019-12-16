#include "game.h"
int main()
{
  MyASGEGame asge_game;
  if (asge_game.init())
  {
    asge_game.run();
  }
  return 0;
}