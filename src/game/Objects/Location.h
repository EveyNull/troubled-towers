//
// Created by e22-watson on 16/10/2019.
//
#include "../Utility/WordTypes/Direction.h"
#include "../Utility/WordTypes/Object.h"
#include "Item.h"
#include <algorithm>
#include <map>
#include <list>

#ifndef BASIC_REB0RN_GAME_EVEYNULL_LOCATION_H
#  define BASIC_REB0RN_GAME_EVEYNULL_LOCATION_H

class Location : public Object
{
 public:
  using RouteMap = std::map<int, Location*>;

  Location(int new_id,
           const std::string& new_name,
           const std::string& new_desc,
           const RouteMap& new_routes,
           bool new_is_dark,
           const std::list<Item*>& new_items);
  ~Location() = default;

  void addNewItem(Item* new_item);
  void addRoute(Direction dir, Location* new_route);

  int getId() override;
  const std::string& getDescription() override;

  bool getIsDark();

  const RouteMap& getRoutes();
  bool getHasRoute(Direction route);
  Location* getRoute(Direction route);

  bool checkItemPresent(int id);
  const std::list<Item*>& getPresentItems();
  void removeItem(Item* item);

 private:
  int id = -1;

  std::string name;
  std::string description;

  bool is_dark;

  RouteMap routes;
  std::list<Item*> items_here;
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_LOCATION_H
