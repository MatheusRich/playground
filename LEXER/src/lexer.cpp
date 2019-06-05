#include "lexer.h"

#include <fstream>
#include <iostream>

std::string char_to_str(char c) {
  return std::string(1, c);
}

terminals_list Lexer::ReadRange(int begin_code, std::vector<char_range> ranges){
    terminals_list terminals;
    for(auto range : ranges){
        for(; range.first <= range.second; range.first++){
            terminals[char_to_str(range.first)] = begin_code++;
        }
    }    
    return terminals;
}

terminals_list Lexer::ReadList(int begin_code, std::vector<std::string> word_list){
    terminals_list terminals;
    for(auto word : word_list){
        terminals[word] = begin_code++;
    }
    return terminals;
}

terminals_list Lexer::LoadTerminals(){ // FIXME: Yes, this is not DRY. But we got no time to fix it
    terminals_list terminals;
    std::ifstream terminals_file(TERMINALS_FILE,std::ios::in);
    if(terminals_file.good()){
        std::string terminal_type;
        //check if the while stops at the eof
        while(std::getline(terminals_file, terminal_type)){
            if(terminal_type == "LETTERS"){
                std::vector<char_range> ranges;
                while(1){
                    char line[4];
                    terminals_file.read(line, 4 * sizeof(char));
                    // printf("read from terminals file: %c %c\n",line[0],line[2]);
                    if(line[0] == '#'){
                        break;
                    }
                    ranges.push_back(std::make_pair(line[0], line[2]));
                }
                terminals_list range_terminals = ReadRange(LETTERS_CODE, ranges);
                terminals.insert(range_terminals.begin(),range_terminals.end());
            }
            else if(terminal_type == "DIGITS"){
                std::vector<char_range> ranges;
                while(1){
                    char line[4];
                    terminals_file.read(line, 4 * sizeof(char));
                    // printf("read from terminals file: %c %c\n",line[0],line[2]);
                    if(line[0] == '#'){
                        break;
                    }
                    ranges.push_back(std::make_pair(line[0],line[2]));
                }
                terminals_list range_terminals = ReadRange(DIGITS_CODE, ranges);
                terminals.insert(range_terminals.begin(),range_terminals.end());
            }
            else if(terminal_type == "SEPARATORS") {
                std::vector<std::string> separators;

                while (1) {
                    char line[4];
                    terminals_file.getline(line, 4);
                    char separator = line[0];

                    if (separator == '\\') {
                        char c = line[1];
                        switch (c) {
                        case 'n':
                            separator = '\n';
                            break;

                        case 't':
                            separator = '\t';
                            break;
                        
                        default:
                            std::string msg = "ERROR: invalid separator '\\";
                            msg += c;
                            msg +=  + "'";
                            puts(msg.c_str());
                            exit(-1);
                        }
                    }

                    // printf("'%c'\n", separator);

                    if (separator == '#')
                        break;

                    separators.push_back(char_to_str(separator));
                }
                terminals_list separatorTerminals = ReadList(SEPARATORS_CODE, separators);
                terminals.insert(separatorTerminals.begin(), separatorTerminals.end());
            }
            else if(terminal_type == "RESERVED_WORDS") {
                std::vector<std::string> words;

                while (1) {
                    char line[256];
                    terminals_file.getline(line, 256);
                    // puts(line);

                    if (line[0] == '#')
                        break;

                    words.push_back(line);
                }
                terminals_list wordTerminals = ReadList(RESERVED_WORDS_CODE, words);
                terminals.insert(wordTerminals.begin(), wordTerminals.end());
            }
        }
    }
    else{
        puts("Error could not open terminals file");
        exit(-1);
    }
    terminals_file.close();
    return terminals;
}
