//
// Created by e22-watson on 16/10/2019.
//
#include "../Utility/WordTypes/Object.h"
#include <vector>

#ifndef BASIC_REB0RN_GAME_EVEYNULL_ITEM_H
#  define BASIC_REB0RN_GAME_EVEYNULL_ITEM_H

class Item : public Object
{
 public:
  using Object::Object;
  Item(int new_id,
       const std::string& new_name,
       const std::vector<std::string>& new_descs,
       bool new_pickupable);
  int getId() override;
  bool getPickupable();
  int getState();
  void changeState(int index);
  const std::string& getDescription() override;

 private:
  int id = -1;
  int state = 0;
  std::string name = "NULL";
  bool pickupable = false;
  std::vector<std::string> descriptions = std::vector<std::string>{};
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_ITEM_H
