//
// Created by Tau on 15/10/2019.
//

#include "CommandManager.h"
#include <Engine/DebugPrinter.h>
#include <strstream>

std::vector<Word> getKeyWords(const std::string& input);
std::string pickUpItem(Item* target_object, Player* player, bool& failed);

CommandManager::CommandManager(Player* ptr_player,
                               std::vector<Location>& new_locations,
                               std::vector<Verb>& new_verbs) :
  player(ptr_player),
  locations(new_locations), valid_verbs(new_verbs)
{
}

std::string CommandManager::handleInput(const std::string& playerInput)
{
  std::vector<Word> player_input = getKeyWords(playerInput);
  Command player_command = checkValidCommand(player_input);
  if (player_command.verb == nullptr)
  {
    return "I DON'T KNOW HOW TO " + player_input.at(0).getWord();
  }

  else if (player_command.verb->getWord() == "GO" || player_input.size() < 2)
  {
    return executeBasicCommand(player_command);
  }
  return executeItemCommand(player_command.verb->checkValidCombination(
    dynamic_cast<Item*>(player_command.target)));
}

Direction stringToDirection(const std::string& string)
{
  if (string == "NORTH" || string == "N")
  {
    return Direction::NORTH;
  }
  if (string == "SOUTH" || string == "S")
  {
    return Direction::SOUTH;
  }
  if (string == "EAST" || string == "E")
  {
    return Direction::EAST;
  }
  if (string == "WEST" || string == "W")
  {
    return Direction::WEST;
  }
  if (string == "UP" || string == "U")
  {
    return Direction::UP;
  }
  if (string == "DOWN" || string == "P")
  {
    return Direction::DOWN;
  }
  return Direction::NULLDIR;
}

Command CommandManager::checkValidCommand(std::vector<Word> command)
{
  auto return_command = Command();
  for (Verb& verb : valid_verbs)
  {
    if (command.at(0).getWord() == verb.getWord())
    {
      return_command.verb = &verb;
      break;
    }
  }
  for (int itr = 0; itr < command.size(); itr++)
  {
    if (player->getCurrentLocation()->getHasRoute(
          stringToDirection(command.at(itr).getWord())))
    {
      return_command.target = player->getCurrentLocation()->getRoute(
        stringToDirection(command.at(itr).getWord()));
      return return_command;
    }
  }
  if (command.size() > 1)
  {
    auto itr =
      std::find_if(player->getCurrentLocation()->getPresentItems().begin(),
                   player->getCurrentLocation()->getPresentItems().end(),
                   [&command](Item* item) {
                     return static_cast<Word>(*item) == command.at(1);
                   });
    if (itr != player->getCurrentLocation()->getPresentItems().end())
    {
      return_command.target = *itr;
    }
    itr = std::find_if(player->getInventory().begin(),
                       player->getInventory().end(),
                       [&command](Item* item) {
                         return static_cast<Word>(*item) == command.at(1);
                       });
    if (itr != player->getInventory().end())
    {
      return_command.target = *itr;
    }
  }
  return return_command;
}

std::string CommandManager::executeBasicCommand(const Command& player_command)
{
  if (player_command.verb->getWord() == "GO")
  {
    if (player_command.target == nullptr)
    {
      return "GO WHERE?";
    }
    Location* target_loc = FindObjectHelper::findLocationById(
      &locations, dynamic_cast<Location*>(player_command.target)->getId());
    if (target_loc->getIsDark())
    {
      if (!player->checkItemInInventory(1))
      {
        return "YOU NEED LIGHT TO PROCEED";
      }
      if (player->getItemInInventory(1)->getState() != 1)
      {
        return "YOU SHOULD LIGHT YOUR CANDLE FIRST";
      }
    }
    player->setCurrentLocation(target_loc);
    if (player->getCurrentLocation()->getId() == 1)
    {
      bool all_true = true;
      for (int itr = 0; itr < player->flagNumber() - 1; itr++)
      {
        if (!player->getFlag(itr))
        {
          all_true = false;
        }
      }
      if (all_true)
      {
        player->setFlagTrue(player->flagNumber() - 1);
        return "YOU'VE PUT THE GHOSTS TO REST! YOU WIN";
      }
    }
    return "YOU WALK TO THE " + target_loc->getWord();
  }
  if (player_command.verb->getWord() == "HELP")
  {
    std::string help_text = "VERBS I RECOGNISE: ";
    for (Verb& verb : valid_verbs)
    {
      help_text += verb.getWord() + ",";
    }
    help_text.pop_back();
    help_text += ".";
    return help_text;
  }
  return "HUH?";
}

std::string CommandManager::executeItemCommand(Action* execute)
{
  bool failed = false;
  std::string response;
  if (execute == nullptr)
  {
    return "I DON'T THINK THAT WILL WORK!";
  }
  for (Reaction* reaction : execute->reactions)
  {
    if (!checkRequiredObjectsPresent(reaction))
    {
      failed = true;
      break;
    }
    switch (reaction->action)
    {
      case ReturnAction::PICK_UP_ITEM:
      {
        response = pickUpItem(
          dynamic_cast<Item*>(reaction->target_object), player, failed);
        break;
      }
      case ReturnAction::GET_ITEM_DESCRIPTION:
      {
        response = getItemDesc(dynamic_cast<Item*>(reaction->target_object));
        break;
      }
      case ReturnAction::CHANGE_OBJECT_STATE:
      {
        dynamic_cast<Item*>(reaction->target_object)
          ->changeState(reaction->parameters[0]);
        break;
      }
      case ReturnAction::MOVE_ITEM_TO_LOCATION:
      {
        FindObjectHelper::findLocationById(&locations, reaction->parameters[0])
          ->addNewItem(dynamic_cast<Item*>(reaction->target_object));
        break;
      }
      case ReturnAction ::ADD_ROUTE_TO_LOCATION:
      {
        FindObjectHelper::findLocationById(&locations,
                                           reaction->target_object->getId())
          ->addRoute(Direction(reaction->parameters[1]),
                     FindObjectHelper::findLocationById(
                       &locations, reaction->parameters[0]));
        break;
      }
      case ReturnAction::REMOVE_ITEM_FROM_LOCATION:
      {
        FindObjectHelper::findLocationById(&locations, reaction->parameters[0])
          ->removeItem(dynamic_cast<Item*>(reaction->target_object));
        break;
      }
      case ReturnAction ::DROP_ITEM:
      {
        player->removeItemFromInventory(reaction->target_object->getId());
        break;
      }
      case ReturnAction ::SET_FLAG_TRUE:
      {
        player->setFlagTrue(reaction->parameters[0]);
        break;
      }
      default:
        break;
    }
  }
  if (response.empty())
  {
    if (failed)
    {
      response = execute->failure_response;
    }
    else
    {
      response = execute->success_response;
    }
  }
  return response;
}

std::vector<Word> getKeyWords(const std::string& input)
{
  std::vector<Word> word_list;
  int space_index = (int)input.find(' ');
  if (space_index > 0)
  {
    word_list.emplace_back(Word(input.substr(0, space_index)));
  }
  word_list.emplace_back(Word(input.substr(space_index + 1, input.length())));
  return word_list;
}

bool CommandManager::checkRequiredObjectsPresent(Reaction* reaction)
{
  for (RequiredItem object : reaction->required_objects)
  {
    if (player->getCurrentLocation()->checkItemPresent(
          object.item_required->getId()) &&
        object.item_required->getState() == object.state_required)
    {
      continue;
    }
    if (player->getItemInInventory(object.item_required->getId()) &&
        object.item_required->getState() == object.state_required)
    {
      continue;
    }
    return false;
  }
  return true;
}

std::string pickUpItem(Item* target_object, Player* player, bool& failed)
{
  if (target_object == nullptr)
  {
    return "YOU DON'T SEE IT";
  }
  Item* item = dynamic_cast<Item*>(target_object);
  if(item)
  {
    if (player->getItemInInventory(item->getId()))
    {
      return "YOU ALREADY HAVE IT!";
    }
    if (item->getPickupable())
    {
      player->getCurrentLocation()->removeItem(item);
      player->addItemToInventory(item);
      return "PICKED UP THE " + item->getWord();
    } else
    {
      failed = true;
      return "";
    }
  }
  else
  {
    failed = true;
    return "";
  }
}

std::string CommandManager::getItemDesc(Item* target_object)
{
  if (target_object == nullptr)
  {
    return player->getCurrentLocation()->getDescription();
  }
  return target_object->getDescription();
}