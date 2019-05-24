#include "mint.h"

#include <iterator>
#include <fstream>

#define ERROR_CODE 0 // exit without breaking Make run
#define CMD 0
#define ARG1 1
#define ARG2 2


std::string char_to_str(char c) {
  return std::string(1, c);
}

void Mint::ERROR(std::string msg) { // TODO: improve color handling
  printf("\033[1;31m[ERROR]\033[0m at \"%s\", line %d: %s\n", CODE_FILE, p + 1, msg.c_str());
  exit(ERROR_CODE);
}

bool Mint::IsSeparator(std::string s) {
  return (s == " " || s == "," || s == "\n");
}

std::string Mint::SplitBySeparators(std::string input) {
  std::string output = "";

  for (char c : input) {
    if (IsSeparator(char_to_str(c))) {
      if (output.size() == 0) // single separator, no word
        output += c;
      break;
    } else {
      output += c;
    }
  }
  return output;
}

bool Mint::IsLabel(std::string word) { //TODO: update this to check if !separator && !reserved_word
  if(word.back() == ':')
    return true;
  return false;
}

void Mint::LoadCode(std::string file) {
  std::ifstream code_file(file, std::ios::in);

  if(not code_file.good()){
    ERROR("Could not open mepa code.");
  }

  std::string line = "";
  int line_code = 0;

  while(std::getline(code_file, line)) {
    Command list;
    int i = 0;
    while(line.size() > 0) {
      std::string token = SplitBySeparators(line);
      line = line.substr(token.size(), line.size() - 1);
      if(IsLabel(token)){
        token.pop_back();
        labels[token] = line_code;
      }
      else if(not IsSeparator(token)){
        list.instruction[i] = token;
        i++;
      }
    }
    instructions.push_back(list);
    line_code++;
  }
}

std::string Mint::CurrentCMD() {
  return instructions[p].instruction[CMD];
}

int Mint::CurrentARG1asInt() {
  return stoi(instructions[p].instruction[ARG1]);
}

int Mint::CurrentARG2asInt() {
  return stoi(instructions[p].instruction[ARG2]);
}

std::string Mint::CurrentARG1asStr() {
  return instructions[p].instruction[ARG1];
}

std::string Mint::CurrentARG2asStr() {
  return instructions[p].instruction[ARG2];
}

void Mint::InitProgram() {
  p = 0;
  s = 0;
  stack.push_back(STACK_INITIAL_VALUE);

  if (CurrentCMD() != "INPP") {
    ERROR("The first instruction should be \"INPP\", but it was \"" + CurrentCMD() + "\".");
  }
}

void Mint::Execute() {
  while(true){
    p++;
    if(p >= int(instructions.size())) {
      ERROR("Unexpected end of file.");
    }
    else if(CurrentCMD() == "CRCT") {
      s++;
      std::vector<int>::iterator itPos = stack.begin() + s; // This sucks
      this->stack.insert(itPos, CurrentARG1asInt());
    }
    else if(CurrentCMD() == "SOMA") {
      stack[s-1] = stack[s-1] + stack[s];
      s--;
    }
    else if(CurrentCMD() == "SUBT") {
      stack[s-1] = stack[s-1] - stack[s];
      s--;
    }
    else if(CurrentCMD() == "MULT") {
      stack[s-1] = stack[s-1] * stack[s];
      s--;
    }
    else if(CurrentCMD() == "DIVI") {
      stack[s-1] = stack[s-1] / stack[s];
      s--;
    }
    else if(CurrentCMD() == "INVR") {
      stack[s] = -(stack[s]);
    }
    else if(CurrentCMD() == "CONJ") {
      if(stack[s-1] == 1 && stack[s] == 1) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "DISJ") {
      if(stack[s-1] == 1 || stack[s] == 1) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "NEGA") {
      stack[s] = 1 - stack[s];
    }
    else if(CurrentCMD() == "CMME") {
      if(stack[s-1] < stack[s]) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "CMMA") {
      if(stack[s-1] > stack[s]) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "CMIG") {
      if(stack[s-1] == stack[s]) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "CMDG") {
      if(stack[s-1] != stack[s]) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "CMEG") {
      if(stack[s-1] <= stack[s]) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "CMAG") {
      if(stack[s-1] >= stack[s]) {
        stack[s-1] = 1;
      }
      else {
        stack[s-1] = 0;
      }
      s--;
    }
    else if(CurrentCMD() == "DSVS") {
      p = labels[CurrentARG1asStr()] - 1;
    }
    else if(CurrentCMD() == "DSVF") {
      if(stack[s] == 0) {
        p = labels[CurrentARG1asStr()] - 1;
      }
      s--;
    }
    else if(CurrentCMD() == "NADA") {
      // NADA
    }
    else if(CurrentCMD() == "PARA") {
      // DUMP MOSTRAR TODA PILHA
      for(int i = 0; i <= s; i++) {
        printf("%d\n", stack[i]); 
      }
      break;
    }
    else if(CurrentCMD() == "CRVL") {
      s++;

      std::vector<int>::iterator itPos = stack.begin() + s;
      stack.insert(itPos, stack.at(CurrentARG1asInt()));
    }
    // FAZER DEPOIS COM ESCOPO
    // else if(CurrentCMD() == "CREN") {
    //   s++;

    //   std::vector<int>::iterator itPos = stack.begin() + s;
    //   stack.insert(itPos, CurrentARG1asInt());
    // }
    else if(CurrentCMD() == "ARMZ") {
      stack[CurrentARG1asInt()] = stack[s];
      s--;
    }
  }
}

void Mint::Run() {
  LoadCode();
  InitProgram();
  Execute();
}
