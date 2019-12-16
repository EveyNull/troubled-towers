//
// Created by e22-watson on 16/10/2019.
//

#include "Object.h"

Object::Object(int new_id,
               const std::string& new_name,
               const std::string& new_desc) :
  id(new_id),
  name(new_name), description(new_desc)
{
}

int Object::getId()
{
  return id;
}

const std::string& Object::getDescription()
{
  return description;
}