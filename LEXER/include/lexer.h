#ifndef LEXER_H
#define LEXER_H
#define TERMINALS_FILE "./terminals"
#define LETTERS_CODE 100
#define DIGITS_CODE 200
#define SEPARATORS_CODE 300
#define RESERVED_WORDS_CODE 400

#include <map>
#include <vector>
#include <string>


typedef std::pair<char,char> char_range;
typedef std::map<std::string,int> terminals_list;

// to do remove static from read terminals functions 
class Lexer {
private:
    static terminals_list ReadRange(int begin_code, std::vector<char_range> ranges);
    static terminals_list ReadList(int begin_code,std::vector<std::string> word_list);

public:
    static terminals_list LoadTerminals();
};

#endif