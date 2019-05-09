#include <iostream>
#include <map>

#define SEPARATORS_BEGIN 1
#define SEPARATORS_END 5

bool is_in_range(int n, int min, int max) {
  return (n >= min && n <= max);
}


std::string char_to_str(char c) {
  return std::string(1, c);
}

bool is_separator(char c, std::map<std::string, int> separators) { // maybe input should be a string
  return separators.find(char_to_str(c)) != separators.end();
}
bool is_separator2(char c, std::map<std::string, int> separators) { // This allows having only one structure saving termianals and flaging the separators
  return (not(separators.find(char_to_str(c)) == separators.end())
          || is_in_range(separators[char_to_str(c)], SEPARATORS_BEGIN, SEPARATORS_END));
}

std::string split_by_separators(std::string input, std::map <std::string, int> separators) {
  std::string output = "";

  for(char c : input) {
    if (is_separator(c, separators)) {
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
  std::map <std::string, int> separators;
  int i = 1;
  separators["("] = i++;
  separators[")"] = i++;
  separators[","] = i++;
  separators[" "] = i++;
  separators["\n"] = i++; // Is this needed?


  std::string input = "program(a, b);";
  puts(("INPUT: '" + input + "'\n").c_str());

  puts("OUTPUT");
  i = 1;
  while (input.size() > 0) {
    std::string separated = split_by_separators(input, separators);
    input = input.substr(separated.size(), input.size() - 1);
    printf("Token %02d: '%s'\n", i++, separated.c_str());
  }

  return 0;
}