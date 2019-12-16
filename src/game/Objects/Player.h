//
// Created by e22-watson on 16/10/2019.
//

#include "Location.h"
#include <list>
#include <bitset>
#include <memory>

#ifndef BASIC_REB0RN_GAME_EVEYNULL_PLAYER_H
#  define BASIC_REB0RN_GAME_EVEYNULL_PLAYER_H

class Player
{
 public:
  Player() = default;
  ~Player() = default;
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  Location* getCurrentLocation();
  void setCurrentLocation(Location* new_location);

  int flagNumber();
  bool getFlag(int index);
  void setFlagTrue(int index);

  const std::list<Item*>& getInventory();
  void addItemToInventory(Item* new_item);
  void removeItemFromInventory(int target_item);
  bool checkItemInInventory(int id);
  Item* getItemInInventory(int id);

 private:
  Location* current_location = nullptr;
  std::list<Item*> inventory = std::list<Item*>{};
  std::bitset<4> flags;
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_PLAYER_H
