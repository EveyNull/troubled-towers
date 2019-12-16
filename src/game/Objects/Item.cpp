//
// Created by e22-watson on 16/10/2019.
//

#include "Item.h"

Item::Item(int new_id,
           const std::string& new_name,
           const std::vector<std::string>& new_desc,
           bool new_pickupable) :
  id(new_id),
  name(new_name), descriptions(new_desc), pickupable(new_pickupable)
{
  setWord(new_name);
}

int Item::getId()
{
  return id;
}

bool Item::getPickupable()
{
  return pickupable;
}

int Item::getState()
{
  return state;
}

void Item::changeState(int index)
{
  state = index;
}

const std::string& Item::getDescription()
{
  return descriptions[state];
}