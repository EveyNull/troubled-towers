//
// Created by e22-watson on 11/10/2019.
//

#include "TextParser.h"

bool TextParser::checkValidInput(std::string inputText, char& newChar)
{
  std::regex_match(inputText, acceptable_characters);
  std::smatch results;

  bool matched = std::regex_match(inputText, results, acceptable_characters);
  if (matched)
  {
    newChar = results.str().at(0);
  }
  return matched;
}

std::string TextParser::addToCommand(char newChar)
{
  current_command_input.append(1, newChar);
  return current_command_input;
}

std::string TextParser::removeFromCommand()
{
  if (current_command_input.length() > 0)
  {
    current_command_input.erase(current_command_input.length() - 1, 1);
  }
  return current_command_input;
}

std::string TextParser::getSpokenWords()
{
  std::string return_value = current_command_input;
  current_command_input = "";
  return return_value;
}

std::string TextParser::getCurrentCommandInput()
{
  return current_command_input;
}