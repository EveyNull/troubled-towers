//
// Created by e22-watson on 16/10/2019.
//

#include "Verb.h"

Verb::Verb(const std::string& new_name,
           std::map<Item*, Action*>& n_valid_combinations) :
  name(new_name),
  valid_combinations(n_valid_combinations)
{
  setWord(new_name);
}

Action* Verb::checkValidCombination(Item* target_object)
{
  if (valid_combinations.count(target_object) > 0 && target_object != nullptr)
  {
    return { valid_combinations.at(target_object) };
  }
  else if (valid_combinations.count(nullptr))
  {
    Action* action = valid_combinations.at(nullptr);
    for (auto& reaction : action->reactions)
    {
      reaction->target_object = target_object;
    }
    return action;
  }
  return nullptr;
}