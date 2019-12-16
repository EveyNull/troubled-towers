//
// Created by Tau on 15/10/2019.
//
#include "../Objects/Item.h"
#include "../Objects/Location.h"
#include "../Objects/Player.h"
#include "Command.h"
#include "FindObjectHelper.h"
#include "Word.h"
#include "WordTypes/Object.h"
#include <algorithm>
#include <string>
#include <vector>

#ifndef PROJECT_COMMANDMANAGER_H
#  define PROJECT_COMMANDMANAGER_H

class CommandManager
{
 public:
  CommandManager(Player* ptr_player,
                 std::vector<Location>& new_locations,
                 std::vector<Verb>& new_verbs);
  ~CommandManager() = default;
  std::string handleInput(const std::string& playerInput);
  Command checkValidCommand(std::vector<Word> command);
  std::string executeBasicCommand(const Command& player_command);
  std::string executeItemCommand(Action* execute);
  bool checkRequiredObjectsPresent(Reaction* reaction);
  std::string getItemDesc(Item* target_object);

 private:
  Player* player = nullptr;
  std::vector<Location> locations;
  std::vector<Verb> valid_verbs;
};

#endif // PROJECT_COMMANDMANAGER_H
