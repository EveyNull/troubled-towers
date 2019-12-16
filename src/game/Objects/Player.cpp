//
// Created by e22-watson on 16/10/2019.
//

#include "Player.h"

void Player::addItemToInventory(Item* new_item)
{
  inventory.push_back(new_item);
}

Location* Player::getCurrentLocation()
{
  return current_location;
}

void Player::setCurrentLocation(Location* new_location)
{
  current_location = new_location;
}

int Player::flagNumber()
{
  return static_cast<int>(flags.size());
}

void Player::setFlagTrue(int index)
{
  flags[index] = true;
}

bool Player::getFlag(int index)
{
  return flags[index];
}

const std::list<Item*>& Player::getInventory()
{
  return inventory;
}

bool Player::checkItemInInventory(int id)
{
  for (Item* item : inventory)
  {
    if (item->getId() == id)
    {
      return true;
    }
  }
  return false;
}

void Player::removeItemFromInventory(int target_item)
{
  for(auto itr = inventory.begin(); itr != inventory.end(); ++itr)
  {
    if ((*itr)->getId() == target_item)
    {
      inventory.erase(itr);
      break;
    }
  }
}

Item* Player::getItemInInventory(int id)
{
  for (Item* item : inventory)
  {
    if (item->getId() == id)
    {
      return item;
    }
  }
  return nullptr;
}