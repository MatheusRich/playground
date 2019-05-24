#include<iostream>
#include<string>
#include<map>
#include<vector>
#include <iterator>
#include<set>
#include <fstream>
#include <tuple>

#define ERROR_CODE -1
#define CMD 0
#define ARG1 1
#define ARG2 2
#define CODE_FILE "in.mepa"

std::vector<int> stack;
int s; // topo na pilha || posicao atual na pilha
int p; // program counter || posicao no codigo || instrucao atual

void ERROR(std::string msg) { // TODO: improve color handling
  printf("\033[1;31m[ERROR]\033[0m at \"%s\", line %d: %s\n", CODE_FILE, p + 1, msg.c_str());
  exit(ERROR_CODE);
}

std::string char_to_str(char c) {
  return std::string(1, c);
}
typedef struct command {
  std::string cmd[3] = {"", "", ""};
} Command;

bool is_separator(std::string c) { // maybe input should be a string
  return (c == " " || c == "," || c == "\n");
}

std::string split_by_separators(std::string input) {
  std::string output = "";

  for(char c : input) {
    if (is_separator(char_to_str(c))) {
      if(output.size() == 0) // single separator, no word
        output += c;
      break;
    } else {
      output += c;
    }
  }
  return output;
}

bool is_label(std::string word){
    if(word.back() == ':')
        return true;
    return false;
}

int main (){
    std::map<std::string,int> labels;
    std::vector<Command> instructions;

    std::ifstream code_file(CODE_FILE, std::ios::in);
    if(!code_file.good()){
        exit(-1);
    }

    std::string line ="";
    int line_code = 0;

    while(std::getline(code_file,line)) {
        Command list;
        int i = 0;
        while(line.size() > 0) {
            std::string separated = split_by_separators(line);
            line = line.substr(separated.size(), line.size() - 1);
            if(is_label(separated)){
                separated.pop_back();
                labels[separated] = line_code;
            }
            else if(!is_separator(separated)){
                list.cmd[i] = separated;
                i++;
            }
        }
        instructions.push_back(list);
        line_code++;
    }
    
    p = 0; // program counter || posicao no codigo || instrucao atual

    if(instructions[p].cmd[CMD]!= "INPP") {
      puts(instructions[p].cmd[CMD].c_str());
      exit(-1);
    }
    s = 0; // topo na pilha || posicao atual na pilha
    stack.push_back(0);


    while(1){
      p++;
      if(p >= instructions.size()) {
        ERROR("Unexpected end of file.");
      }
      else if(instructions[p].cmd[CMD] == "CRCT") {
        s++;
        std::vector<int>::iterator itPos = stack.begin() + s;
        stack.insert(itPos, stoi(instructions[p].cmd[ARG1]));
      }
      else if(instructions[p].cmd[CMD] == "SOMA") {
        stack[s-1] = stack[s-1] + stack[s];
        s--;
      }
      else if(instructions[p].cmd[CMD] == "SUBT") {
        stack[s-1] = stack[s-1] - stack[s];
        s--;
      }
      else if(instructions[p].cmd[CMD] == "MULT") {
        stack[s-1] = stack[s-1] * stack[s];
        s--;
      }
      else if(instructions[p].cmd[CMD] == "DIVI") {
        stack[s-1] = stack[s-1] / stack[s];
        s--;
      }
      else if(instructions[p].cmd[CMD] == "INVR") {
        stack[s] = -(stack[s]);
      }
      else if(instructions[p].cmd[CMD] == "CONJ") {
        if(stack[s-1] == 1 && stack[s] == 1) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "DISJ") {
        if(stack[s-1] == 1 || stack[s] == 1) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "NEGA") {
        stack[s] = 1 - stack[s];
      }
      else if(instructions[p].cmd[CMD] == "CMME") {
        if(stack[s-1] < stack[s]) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "CMMA") {
        if(stack[s-1] > stack[s]) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "CMIG") {
        if(stack[s-1] == stack[s]) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "CMDG") {
        if(stack[s-1] != stack[s]) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "CMEG") {
        if(stack[s-1] <= stack[s]) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "CMAG") {
        if(stack[s-1] >= stack[s]) {
          stack[s-1] = 1;
        }
        else {
          stack[s-1] = 0;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "DSVS") {
        p = labels[instructions[p].cmd[ARG1]] - 1;
      }
      else if(instructions[p].cmd[CMD] == "DSVF") {
        if(stack[s] == 0) {
          p = labels[instructions[p].cmd[ARG1]] - 1;
        }
        s--;
      }
      else if(instructions[p].cmd[CMD] == "NADA") {
        // NADA
      }
      else if(instructions[p].cmd[CMD] == "PARA") {
        // DUMP MOSTRAR TODA PILHA
        for(int i = 0; i <= s; i++) {
          printf("%d\n", stack[i]); 
        }
        break;
      }
      else if(instructions[p].cmd[CMD] == "CRVL") {
        s++;

        std::vector<int>::iterator itPos = stack.begin() + s;
        stack.insert(itPos, stack.at(stoi(instructions[p].cmd[ARG1])));
      }
      // FAZER DEPOIS COM ESCOPO
      // else if(instructions[p].cmd[CMD] == "CREN") {
      //   s++;

      //   std::vector<int>::iterator itPos = stack.begin() + s;
      //   stack.insert(itPos, stoi(instructions[p].cmd[ARG1]));
      // }
      else if(instructions[p].cmd[CMD] == "ARMZ") {
        stack[stoi(instructions[p].cmd[ARG1])] = stack[s];
        s--;
      }
    }

    return 0;
}