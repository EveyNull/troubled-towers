//
// Created by Tau on 15/10/2019.
//

#include "ScreenDisplay.h"

ScreenDisplay::ScreenDisplay(std::unique_ptr<ASGE::Renderer>& renderer,
                             int& game_height,
                             int& game_width)
{
  screen_height = game_height;
  screen_width = game_width;
  createScanLines(renderer);
}

ScreenDisplay::~ScreenDisplay()
{
  if (scanlines)
  {
    for (ASGE::Sprite* sprite : *scanlines)
    {
      delete sprite;
      sprite = nullptr;
    }
    delete scanlines;
    scanlines = nullptr;
  }
  rolling_bar = nullptr;
}

void ScreenDisplay::update(const ASGE::GameTime& game_time)
{
  if (rolling_bar->yPos() <= 0 - rolling_bar->height())
  {
    rolling_bar->yPos(screen_height);
  }
  else
  {
    rolling_bar->yPos(rolling_bar->yPos() - (rolling_bar_move_speed *
                                             (float)game_time.delta.count()));
  }
}

void ScreenDisplay::createScanLines(std::unique_ptr<ASGE::Renderer>& renderer)
{
  scanlines = new std::list<ASGE::Sprite*>();
  for (int i = 1; i < screen_height; i += 2)
  {
    ASGE::Sprite* new_sprite = renderer->createRawSprite();
    new_sprite->loadTexture("onepixel.png");
    new_sprite->colour(ASGE::COLOURS::BLACK);
    new_sprite->height(1);
    new_sprite->width(screen_width);
    new_sprite->xPos(0);
    new_sprite->yPos(i);
    scanlines->push_back(new_sprite);
  }
  rolling_bar = renderer->createUniqueSprite();
  rolling_bar->loadTexture("onepixel.png");
  rolling_bar->colour(ASGE::COLOURS::BLACK);
  rolling_bar->opacity(0.4f);
  rolling_bar->height(10.f);
  rolling_bar->width(screen_width);
  rolling_bar->xPos(0);
  rolling_bar->yPos(screen_height - rolling_bar->height());
}

ASGE::Sprite* ScreenDisplay::getRollingBar()
{
  return rolling_bar.get();
}

std::list<ASGE::Sprite*>* ScreenDisplay::getScanLines()
{
  return scanlines;
}

const std::string& ScreenDisplay::getCommandResponseText()
{
  return cmd_response_text;
}

void ScreenDisplay::setCommandResponseText(const std::string& cmd_response_text)
{
  ScreenDisplay::cmd_response_text = cmd_response_text;
}

const std::string& ScreenDisplay::getLocationInfoText()
{
  return location_info_text;
}

void ScreenDisplay::setLocationInfoText(const std::string& location_info_text)
{
  ScreenDisplay::location_info_text = location_info_text;
}

const std::string& ScreenDisplay::getPlayerInputText()
{
  return player_input_text;
}

void ScreenDisplay::setPlayerInputText(const std::string& player_input_text)
{
  ScreenDisplay::player_input_text = player_input_text;
}

const std::string& ScreenDisplay::getErrorText()
{
  return error_text;
}

void ScreenDisplay::setErrorText(const std::string& error_text)
{
  ScreenDisplay::error_text = error_text;
}