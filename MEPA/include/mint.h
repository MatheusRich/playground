#ifndef MINT_H
#define MINT_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#define CODE_FILE "in.mepa"
#define STACK_INITIAL_VALUE -999999

typedef struct command {
  std::string instruction[3] = {"", "", ""};
} Command;

// Mepa + Interpreter = Mint
class Mint {
private:
  int s;
  int p;
  std::map<std::string, int> labels;
  std::vector<int> stack;
  std::vector<Command> instructions;

  bool IsSeparator(std::string s);
  bool IsLabel(std::string word);
  std::string SplitBySeparators(std::string input);
  std::string CurrentCMD();
  void ERROR(std::string msg);

  void LoadCode(std::string file = CODE_FILE);
  void InitProgram();
  void Execute();

public:
  void Run();
};

#endif