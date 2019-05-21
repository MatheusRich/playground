#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<set>
#include <fstream>

std::set<std::string> reserved_words;

std::string char_to_str(char c) {
  return std::string(1, c);
}

bool is_separator(char c) { // maybe input should be a string
  return (c == ' ' || c == ',');
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

bool is_label(std::string word){
    if(reserved_words.find(word) != reserved_words.end())
        return true;
    return false;
}


#define CMD 0
#define ARG1 1
#define ARG2 2
#define CODE_FILE "./in.mepa"



int main (){
    std::map<std::string,int> labels;
    std::vector<std::vector<std::string>> instructions;

    reserved_words.insert("INPP");
    reserved_words.insert("PARA");

    std::string line ="";
    int line_code = 0;

    puts("aq1ui");

    std::ifstream code_file(CODE_FILE,std::ios::in);
    if(!code_file.good()){
        exit(-1);
    }

    while(std::getline(code_file,line)){
        printf("%d",line_code);
        std::vector<std::string> list;
        while(line.size() > 0)         {
            std::string separated = split_by_separators(line);
            line = line.substr(separated.size(), line.size() - 1);
            if(is_label(separated)){
                labels[separated] = line_code;
            }
            else{
                list.push_back(separated);
            }
        }
        instructions[line_code++] = list;
    }
    
    int p =0;

    puts("aq1ui");

    if(instructions[p][CMD] != "INPP"){
       exit(-1);
    }
    std::vector<int> stack;
    int s =0;
    stack[0] = 42;

    puts("aq1ui");


    while(1){
      if(++p >= instructions.size()){
        exit(-1);
      }
      if(instructions[p][CMD] != "PARA"){
        printf("%d", stack[s]);
        break;
      }
      // do stuff

    }

    return 0;
}