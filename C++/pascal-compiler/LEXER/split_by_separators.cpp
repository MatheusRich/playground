#include <iostream>
#include <map>
#include <vector>
#include <iterator>

#define DIGITS_BEGIN 100
#define LETTERS_BEGIN 200
#define SEPARATORS_BEGIN 300
#define RESERVED_WORDS_BEGIN 400

using namespace std;

map<string, int> terminals;

std::string char_to_str(char c) {
  return std::string(1, c);
}

bool is_separator(char c) { // maybe input should be a string
  return terminals[char_to_str(c)]/SEPARATORS_BEGIN == 1;
}

std::string split_by_separators(std::string input) {
  std::string output = "";

  for(char c : input) {
    if (is_separator(c)) {
      if(output.size() == 0) // single separator, no word
        output += c;
      break;
    } else {
      output += c;
    }
  }

  return output;
}

int main() {
  vector<int> tokens;
  
  int i = DIGITS_BEGIN;
  char aux = '0';
  for(int c = 0;c < 10;c++){
    terminals[char_to_str(aux++)] = i++;
  }

  i = LETTERS_BEGIN;  
  aux = 'a';
  for(int c = 0;c < 26;c++){
    terminals[char_to_str(aux++)] = i++;
  }

  aux = 'A';
  for(int c = 0;c < 26;c++){
    terminals[char_to_str(aux++)] = i++;
  }

  i = SEPARATORS_BEGIN;
  terminals[","] = i++;
  terminals[";"] = i++;
  terminals["."] = i++;
  terminals["("] = i++;
  terminals[")"] = i++;
  terminals["{"] = i++;
  terminals["}"] = i++;
  terminals["="] = i++;
  terminals["<"] = i++;
  terminals[">"] = i++;
  terminals["+"] = i++;
  terminals["-"] = i++;
  terminals["*"] = i++;
  terminals[":"] = i++;
  terminals[" "] = i;
  terminals["\t"] = i;
  terminals["\n"] = i;


  i = RESERVED_WORDS_BEGIN;
  terminals["program"] = i++;
  terminals["label"] = i++;
  terminals["type"] = i++;
  terminals["var"] = i++;
  terminals["procedure"] = i++;
  terminals["function"] = i++;
  terminals["begin"] = i++;
  terminals["end"] = i++;
  terminals["goto"] = i++;
  terminals["if"] = i++;
  terminals["then"] = i++;
  terminals["else"] = i++;
  terminals["while"] = i++;
  terminals["do"] = i++;
  terminals["div"] = i++;
  terminals["or"] = i++;
  terminals["and"] = i++;
  terminals["not"] = i++;



  istreambuf_iterator<char> begin(std::cin),end;
  std::string input(begin,end);
  
  puts(("INPUT: '" + input + "'\n").c_str());

  puts("OUTPUT");
  while (input.size() > 0) {
    std::string separated = split_by_separators(input);
    input = input.substr(separated.size(), input.size() - 1);
    if (terminals.find(separated) != terminals.end()) {
      tokens.push_back(terminals[separated]);
    }
    else {
      for (char c : separated){
        tokens.push_back(terminals[string(1, c)]);
      }
    }

  }

  for(auto token : tokens) {
    if(token != 302) {
      for(auto &i : terminals) {
        if(token == i.second)
          printf("token %s\n",i.first.c_str());
      }
    }
  }
  return 0;
}
