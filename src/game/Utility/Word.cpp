//
// Created by Tau on 15/10/2019.
//

#include "Word.h"
Word::Word(const std::string& word_name) : word(word_name) {}

std::string Word::getWord()
{
  return word;
}

void Word::setWord(const std::string& word_name)
{
  word = word_name;
}

bool Word::operator==(Word& comp_word)
{
  return word == comp_word.getWord();
}

bool Word::operator!=(Word& comp_word)
{
  return word != comp_word.getWord();
}