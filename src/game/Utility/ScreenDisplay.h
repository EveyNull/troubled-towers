//
// Created by Tau on 15/10/2019.
//

#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <list>
#include <string>

#ifndef PROJECT_SCREENDISPLAY_H
#  define PROJECT_SCREENDISPLAY_H

class ScreenDisplay
{
 public:
  ScreenDisplay(std::unique_ptr<ASGE::Renderer>& renderer,
                int& game_height,
                int& game_width);
  ~ScreenDisplay();

  void update(const ASGE::GameTime&);

  void createScanLines(std::unique_ptr<ASGE::Renderer>& renderer);

  ASGE::Sprite* getRollingBar();
  std::list<ASGE::Sprite*>* getScanLines();

  const std::string& getCommandResponseText();
  void setCommandResponseText(const std::string& cmd_response_text);

  const std::string& getLocationInfoText();
  void setLocationInfoText(const std::string& location_info_text);

  const std::string& getPlayerInputText();
  void setPlayerInputText(const std::string& player_input_text);

  const std::string& getErrorText();
  void setErrorText(const std::string& error_text);

 private:
  int screen_height, screen_width = 0;

  std::list<ASGE::Sprite*>* scanlines = nullptr;
  std::unique_ptr<ASGE::Sprite> rolling_bar = nullptr;

  std::string cmd_response_text;
  std::string location_info_text;
  std::string player_input_text;
  std::string error_text;

  float rolling_bar_move_speed = 0.1f;
};

#endif // PROJECT_SCREENDISPLAY_H
