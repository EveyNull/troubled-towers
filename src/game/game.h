#pragma once
#include "Utility/CommandManager.h"
#include "Utility/FindObjectHelper.h"
#include "Utility/ScreenDisplay.h"
#include "Utility/TextParser.h"
#include <Engine/FileIO.h>
#include <Engine/Font.h>
#include <Engine/OGLGame.h>
#include <nlohmann/json.hpp>
#include <string>

/**
 *  An OpenGL Game based on ASGE.
 */
class MyASGEGame : public ASGE::OGLGame
{
  using File = ASGE::FILEIO::File;

 public:
  MyASGEGame();
  ~MyASGEGame() final;
  bool init() override;

  void handleInput();
  void updateScreenOutput();

  bool readDataFromJson();
  void readItemsFromJson(File& file);
  void readVerbsFromJson(File& file);
  void readLocationFromJson(File& file);

  std::string
  insertNewLinesAtScreenWidth(const std::string& str, int font_width);

 private:
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void setupResolution();

  void update(const ASGE::GameTime&) override;
  void render(const ASGE::GameTime&) override;

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */

  std::unique_ptr<TextParser> text_parser;
  std::unique_ptr<ScreenDisplay> screen_display;
  std::unique_ptr<CommandManager> command_manager;

  ASGE::Colour background_color = ASGE::COLOURS::BLUE;
  ASGE::Colour text_color = ASGE::COLOURS::WHITE;

  bool use_scanlines = true;

  float font_scale = 0.85f;
  int font_width = 0;

  Player* player = nullptr;
  std::vector<Location> locations;
  std::vector<Item> items;
  std::vector<Verb> verbs;

  std::string json_directory = "/JSON";
  std::string json_file_names[3] = { "/Items.json",
                                     "/Locations.json",
                                     "/Verbs.json" };

  bool new_keypress = false;
  std::string input_key = "";
  bool backspace_pressed = false;
  bool enter_pressed = false;

  float screen_scale = 2.f;
};