//
// Created by e22-watson on 22/10/2019.
//

#include "FindObjectHelper.h"
Item* FindObjectHelper::findItemById(std::vector<Item>* items, int id)
{
  for (Item& item : *items)
  {
    if (item.getId() == id)
    {
      return &item;
    }
  }
  return nullptr;
}

Location*
FindObjectHelper::findLocationById(std::vector<Location>* locations, int id)
{
  for (Location& location : *locations)
  {
    if (location.getId() == id)
    {
      return &location;
    }
  }
  return nullptr;
}