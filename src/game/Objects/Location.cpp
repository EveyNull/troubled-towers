//
// Created by e22-watson on 16/10/2019.
//

#include "Location.h"

Location::Location(int new_id,
                   const std::string& new_name,
                   const std::string& new_desc,
                   const std::map<int, Location*>& new_routes,
                   bool new_is_dark,
                   const std::list<Item*>& new_items) :
  id(new_id),
  name(new_name), description(new_desc), routes(new_routes),
  is_dark(new_is_dark), items_here(new_items)
{
  setWord(new_name);
}

int Location::getId()
{
  return id;
}

const std::string& Location::getDescription()
{
  return description;
}

void Location::addNewItem(Item* new_item)
{
  items_here.push_back(new_item);
}

void Location::addRoute(Direction dir, Location* new_route)
{
  if (routes.count(dir) <= 0)
  {
    routes.insert(std::pair<int, Location*>(dir, new_route));
  }
}

void Location::removeItem(Item* item)
{
  items_here.erase(std::remove(items_here.begin(), items_here.end(), item),
                   items_here.end());
}

bool Location::getIsDark()
{
  return is_dark;
}

const Location::RouteMap& Location::getRoutes()
{
  return routes;
}

bool Location::getHasRoute(Direction route)
{
  return routes.count(route) > 0;
}

Location* Location::getRoute(Direction route)
{
  return routes[route];
}

bool Location::checkItemPresent(int id)
{
  for (Item* item : items_here)
  {
    if (item->getId() == id)
    {
      return true;
    }
  }
  return false;
}

const std::list<Item*>& Location::getPresentItems()
{
  return items_here;
}