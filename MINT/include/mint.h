#ifndef MINT_H
#define MINT_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#define CODE_PATH "example.mepa"
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
  std::string codePath;

  bool IsSeparator(std::string s);
  bool IsLabel(std::string word);
  std::string SplitBySeparators(std::string input);

  std::string CurrentCMD();
  int CurrentARG1asInt();
  int CurrentARG2asInt();
  std::string CurrentARG1asStr();
  std::string CurrentARG2asStr();

  void ERROR(std::string msg);
  void CheckARGPresence(int arg);
  void Dump();

  void LoadCode();
  void InitProgram();
  void Execute();

public:
  void Run(std::string file = CODE_PATH);
};

#endif