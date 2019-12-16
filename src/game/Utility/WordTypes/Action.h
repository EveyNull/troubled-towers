//
// Created by Tau on 23/10/2019.
//
#pragma once
#include "Reaction.h"
#ifndef PROJECT_ACTION_H
#  define PROJECT_ACTION_H

#endif // PROJECT_ACTION_H

struct Action
{
  std::vector<Reaction*> reactions;
  std::string success_response;
  std::string failure_response;
};