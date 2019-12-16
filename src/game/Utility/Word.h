//
// Created by Tau on 15/10/2019.
//
#include <string>

#ifndef PROJECT_WORD_H
#  define PROJECT_WORD_H

class Word
{
 public:
  explicit Word() = default;
  ~Word() = default;
  explicit Word(const std::string& word_name);
  std::string getWord();
  void setWord(const std::string& word_name);

  bool operator==(Word& comp_word);
  bool operator!=(Word& comp_word);

 private:
  std::string word;
};

#endif // PROJECT_WORD_H
