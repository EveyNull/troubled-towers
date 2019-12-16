//
// Created by e22-watson on 16/10/2019.
//
#include "../../Objects/Item.h"
#include "../Word.h"
#include "Action.h"
#include "Reaction.h"
#include "ReturnAction.h"
#include <map>

#ifndef BASIC_REB0RN_GAME_EVEYNULL_VERB_H
#  define BASIC_REB0RN_GAME_EVEYNULL_VERB_H

class Verb : public Word
{
 public:
  Verb(const std::string& new_name,
       std::map<Item*, Action*>& n_valid_combinations);
  ~Verb() = default;
  Action* checkValidCombination(Item* target_object);

 private:
  std::string name;
  std::map<Item*, Action*> valid_combinations;
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_VERB_H
