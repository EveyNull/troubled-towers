//
// Created by e22-watson on 16/10/2019.
//
#include "../Word.h"

#ifndef BASIC_REB0RN_GAME_EVEYNULL_OBJECT_H
#  define BASIC_REB0RN_GAME_EVEYNULL_OBJECT_H

class Object : public Word
{
 public:
  using Word::Word;
  Object(int new_id, const std::string& new_name, const std::string& new_desc);
  virtual ~Object() = default;
  virtual int getId();
  virtual const std::string& getDescription();

 private:
  int id = -1;
  std::string name;
  std::string description;
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_OBJECT_H
