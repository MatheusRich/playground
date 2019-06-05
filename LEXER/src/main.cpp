#include "lexer.h"

int main(){
    terminals_list terminals;
    terminals = Lexer::LoadTerminals();
    puts("terminals map:");
    for(auto terminal : terminals){
        printf("token: '%s', code: %d\n",terminal.first.c_str(),terminal.second);
    }
    // printf("%d\n", terminals.size());
    return 0;
}