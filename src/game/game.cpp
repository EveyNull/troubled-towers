#include <string>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

#include "game.h"
#include <iostream>
/**
 *   @brief   Default Constructor.
 *   @details Consider setting the game's width and height
 *            and even seeding the random number generator.
 */
MyASGEGame::MyASGEGame()
{
  game_name = "ASGE Game";
}

/**
 *   @brief   Destructor.
 *   @details Remove any non-managed memory and callbacks.
 */
MyASGEGame::~MyASGEGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));

  this->inputs->unregisterCallback(
    static_cast<unsigned int>(mouse_callback_id));
}

/**
 *   @brief   Initialises the game.
 *   @details The game window is created and all assets required to
 *            run the game are loaded. The keyHandler and clickHandler
 *            callback should also be set in the initialise function.
 *   @return  True if the game initialised correctly.
 */
bool MyASGEGame::init()
{
  setupResolution();
  if (!initAPI())
  {
    return false;
  }

  // toggleFPS();

  // input handling functions
  inputs->use_threads = false;

  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &MyASGEGame::keyHandler, this);

  mouse_callback_id = inputs->addCallbackFnc(
    ASGE::E_MOUSE_CLICK, &MyASGEGame::clickHandler, this);

  renderer->setClearColour(background_color);

  renderer->setFont(0);
  font_width = static_cast<int>((ceil(11 * font_scale)) * screen_scale);

  ASGE::DebugPrinter{} << font_width << std::endl;

  if (!readDataFromJson())
  {
    return false;
  }
  player = new Player();
  player->setCurrentLocation(&locations.at(0));
  text_parser = std::make_unique<TextParser>();
  command_manager = std::make_unique<CommandManager>(player, locations, verbs);
  screen_display =
    std::make_unique<ScreenDisplay>(renderer, game_height, game_width);

  updateScreenOutput();

  return true;
}

/**
 *   @brief   Sets the game window resolution
 *   @details This function is designed to create the window size, any
 *            aspect ratio scaling factors and safe zones to ensure the
 *            game frames when resolutions are changed in size.
 *   @return  void
 */
void MyASGEGame::setupResolution()
{
  // how will you calculate the game's resolution?
  // will it scale correctly in full screen? what AR will you use?
  // how will the game be framed in native 16:9 resolutions?
  // here are some arbitrary values for you to adjust as you see fit
  // https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/
  // Scaling_and_MultiResolution_in_2D_Games.php

  // Apple II had Hi-Res support of 320x200 with four colours!!
  game_width = static_cast<int>(320 * screen_scale);
  game_height = static_cast<int>(200 * screen_scale);
}

/**
 *   @brief   Processes any key inputs
 *   @details This function is added as a callback to handle the game's
 *            keyboard input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as
 *            you see fit.
 *   @param   data The event data relating to key input.
 *   @see     KeyEvent
 *   @return  void
 */
void MyASGEGame::keyHandler(ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->action == ASGE::KEYS::KEY_PRESSED && key->key < 266)
  {
    new_keypress = true;
    input_key = "";
    if (key->key == ASGE::KEYS::KEY_BACKSPACE)
    {
      backspace_pressed = true;
    }
    else if (key->key == ASGE::KEYS::KEY_ENTER)
    {
      enter_pressed = true;
    }
    else
    {
      input_key = key->key;
    }
  }
  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
}

/**
 *   @brief   Processes any click inputs
 *   @details This function is added as a callback to handle the game's
 *            mouse button input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as you
 *            see fit.
 *   @param   data The event data relating to key input.
 *   @see     ClickEvent
 *   @return  void
 */
void MyASGEGame::clickHandler(ASGE::SharedEventData data)
{
  auto click = static_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;

  ASGE::DebugPrinter{} << "x_pos: " << x_pos << std::endl;
  ASGE::DebugPrinter{} << "y_pos: " << y_pos << std::endl;
}

/**
 *   @brief   Updates the scene
 *   @details Prepares the renderer subsystem before drawing the
 *            current frame. Once the current frame is has finished
 *            the buffers are swapped accordingly and the image shown.
 *   @return  void
 */
void MyASGEGame::update(const ASGE::GameTime& game_time)
{
  if (!player->getFlag(player->flagNumber() - 1))
  {
    handleInput();
  }
  screen_display->update(game_time);
}

/**
 *   @brief   Renders the scene
 *   @details Renders all the game objects to the current frame.
 *            Once the current frame is has finished the buffers are
 *            swapped accordingly and the image shown.
 *   @return  void
 */
void MyASGEGame::render(const ASGE::GameTime&)
{
  std::string render_text = insertNewLinesAtScreenWidth(
    screen_display->getCommandResponseText(), font_width);
  if (!player->getFlag(player->flagNumber() - 1))
  {
    render_text += "\n" + screen_display->getLocationInfoText() +
                   insertNewLinesAtScreenWidth(
                     screen_display->getPlayerInputText(), font_width);
  }
  renderer->renderText(render_text, 0, 25, font_scale * screen_scale, text_color);
  renderer->renderText(
    screen_display->getErrorText(), 100, 200, font_scale * screen_scale, text_color);
  if (use_scanlines)
  {
    renderer->renderSprite(*screen_display->getRollingBar());
    for (ASGE::Sprite* sprite : *screen_display->getScanLines())
    {
      renderer->renderSprite(*sprite);
    }
  }
}

bool checkFile(ASGE::FILEIO::File& file, std::string path)
{
  if (!file.open(path))
  {
    ASGE::DebugPrinter{} << "Failed to open file at " << path << std::endl;
    return false;
  }
  return true;
}

bool MyASGEGame::readDataFromJson()
{
  File file = File();
  if (!checkFile(file, json_directory + json_file_names[0]))
  {
    return false;
  }
  readItemsFromJson(file);
  file = File();
  if (!checkFile(file, json_directory + json_file_names[1]))
  {
    return false;
  }
  readLocationFromJson(file);
  file = File();
  if (!checkFile(file, json_directory + json_file_names[2]))
  {
    return false;
  }
  readVerbsFromJson(file);
  return true;
}

void MyASGEGame::readItemsFromJson(MyASGEGame::File& file)
{
  ASGE::FILEIO::IOBuffer buffer = file.read();
  file.close();
  auto json =
    nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);
  for (auto& item : json)
  {
    std::vector<std::string> descriptions;
    for (auto& desc : item["Descriptions"])
    {
      descriptions.push_back(desc);
    }
    Item new_item(item["ID"].get<int>(),
                  item["Name"].get<std::string>(),
                  descriptions,
                  item["Pickupable"].get<bool>());
    items.push_back(new_item);
  }
}

void MyASGEGame::readLocationFromJson(ASGE::FILEIO::File& file)
{
  ASGE::FILEIO::IOBuffer buffer = file.read();
  file.close();
  auto json =
    nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);

  for (auto& room : json)
  {
    std::list<Item*> new_items;
    for (auto& item : room["Items"])
    {
      Item* new_item = FindObjectHelper::findItemById(&items, item.get<int>());
      if (new_item == nullptr)
      {
        ASGE::DebugPrinter{} << "Failed to find object with ID: "
                             << item.get<int>();
        continue;
      }
      new_items.push_back(new_item);
    }
    Location new_loc(room["ID"].get<int>(),
                     room["Name"].get<std::string>(),
                     room["Description"].get<std::string>(),
                     std::map<int, Location*>(),
                     room["Is_Dark"].get<bool>(),
                     new_items);
    locations.push_back(new_loc);
  }
  for (auto& room : json)
  {
    Location* loc =
      FindObjectHelper::findLocationById(&locations, room["ID"].get<int>());
    std::map<std::string, int> routes =
      room["Routes"].get<std::map<std::string, int>>();
    for (std::pair<std::string, int> route : routes)
    {
      Direction dir = Direction(std::stoi(route.first));
      loc->addRoute(
        dir, FindObjectHelper::findLocationById(&locations, route.second));
    }
  }
}

void MyASGEGame::readVerbsFromJson(MyASGEGame::File& file)
{
  ASGE::FILEIO::IOBuffer buffer = file.read();
  file.close();
  auto json =
    nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);

  for (auto& verb : json)
  {
    std::map<Item*, Action*> new_action_set;
    for (auto& action : verb["Actions"])
    {
      auto* new_action = new Action;
      new_action->success_response = action["ReturnString"].get<std::string>();
      new_action->failure_response = action["FailureString"].get<std::string>();
      for (auto& reaction : action["Reactions"])
      {
        auto* new_reaction = new Reaction;
        new_reaction->target_object = FindObjectHelper::findItemById(
          &items, reaction["ActionTarget"].get<int>());
        new_reaction->action = (ReturnAction)reaction["ActionID"].get<int>();
        for (auto& required_item : reaction["RequiredObjects"])
        {
          RequiredItem new_item;
          new_item.item_required = FindObjectHelper::findItemById(
            &items, required_item["ID"].get<int>());
          new_item.state_required = required_item["State"].get<int>();
          new_reaction->required_objects.push_back(new_item);
        }
        for (auto& parameter : reaction["Parameters"])
        {
          new_reaction->parameters.push_back(parameter);
        }
        new_action->reactions.push_back(new_reaction);
      }
      new_action_set.insert(
        std::pair<Item*, Action*>(FindObjectHelper::findItemById(
                                    &items, action["TargetObject"].get<int>()),
                                  new_action));
    }
    Verb new_verb(verb["Name"].get<std::string>(), new_action_set);
    verbs.push_back(new_verb);
  }
}

void MyASGEGame::handleInput()
{
  if (new_keypress)
  {
    screen_display->setErrorText("");
    new_keypress = false;
  }
  if (input_key.length() > 0)
  {
    char new_letter;
    if (text_parser->checkValidInput(input_key, new_letter))
    {
      screen_display->setPlayerInputText(text_parser->addToCommand(new_letter));
      input_key = "";
    }
    else
    {
      screen_display->setErrorText("Invalid Input");
    }
  }
  if (backspace_pressed)
  {
    screen_display->setPlayerInputText(text_parser->removeFromCommand());
    backspace_pressed = false;
  }
  if (enter_pressed)
  {
    screen_display->setCommandResponseText(
      command_manager->handleInput(text_parser->getSpokenWords()));
    screen_display->setPlayerInputText(text_parser->getCurrentCommandInput());
    enter_pressed = false;
    updateScreenOutput();
  }
}

void MyASGEGame::updateScreenOutput()
{
  std::string location_info =
    "YOU ARE AT: " + player->getCurrentLocation()->getWord() + "\n";
  if (player->getCurrentLocation()->getPresentItems().size() > 0)
  {
    location_info += "THINGS YOU SEE HERE: \n";
    for (Item* item : player->getCurrentLocation()->getPresentItems())
    {
      location_info += "- " + item->getWord() + "\n";
    }
  }
  location_info += "YOU SEE EXITS TO THE:";
  std::string directions[6] = { "N", "S", "E", "W", "U", "D" };
  for (std::pair<int, Location*> route :
       player->getCurrentLocation()->getRoutes())
  {
    location_info += directions[route.first] + ",";
  }
  location_info.pop_back();
  location_info += ".\n";
  screen_display->setLocationInfoText(location_info);
}
std::string
MyASGEGame::insertNewLinesAtScreenWidth(const std::string& str, int font_width)
{
  std::string return_str = str;
  int counter = 0;
  for (int itr = 0; itr < return_str.length(); itr++)
  {
    counter += font_width;
    if (counter >= game_width)
    {
      return_str.insert(itr, "\n");
      counter = 0;
    }
  }
  return return_str;
}