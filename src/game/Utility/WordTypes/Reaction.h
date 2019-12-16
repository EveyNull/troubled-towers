//
// Created by Tau on 23/10/2019.
//
#pragma once
#include "../../Objects/Item.h"
#include "Object.h"
#include "ReturnAction.h"
#include <vector>
#ifndef PROJECT_REACTION_H
#  define PROJECT_REACTION_H

#endif // PROJECT_REACTION_H

struct RequiredItem
{
  Item* item_required;
  int state_required;
};

struct Reaction
{
  ReturnAction action;
  Object* target_object;
  std::vector<RequiredItem> required_objects;
  std::vector<int> parameters;
};