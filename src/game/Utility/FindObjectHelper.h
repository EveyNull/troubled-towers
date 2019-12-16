//
// Created by e22-watson on 22/10/2019.
//
#pragma once
#include "../Objects/Item.h"
#include "../Objects/Location.h"
#ifndef BASIC_REB0RN_GAME_EVEYNULL_FINDOBJECTHELPER_H
#  define BASIC_REB0RN_GAME_EVEYNULL_FINDOBJECTHELPER_H

class FindObjectHelper
{
 public:
  static Item* findItemById(std::vector<Item>* items, int id);
  static Location* findLocationById(std::vector<Location>* locations, int id);
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_FINDOBJECTHELPER_H
