//
// Created by e22-watson on 11/10/2019.
//
#include "Word.h"
#include <list>
#include <regex>
#include <string>

#ifndef BASIC_REB0RN_GAME_EVEYNULL_TEXTPARSER_H
#  define BASIC_REB0RN_GAME_EVEYNULL_TEXTPARSER_H

class TextParser
{
 public:
  TextParser() = default;
  ~TextParser() = default;

  std::string addToCommand(char);
  std::string removeFromCommand();
  std::string getSpokenWords();

  bool checkValidInput(std::string, char&);

  std::string getCurrentCommandInput();

 private:
  const std::regex acceptable_characters = std::regex("^[a-zA-Z ]$");
  std::string current_command_input;
};

#endif // BASIC_REB0RN_GAME_EVEYNULL_TEXTPARSER_H
