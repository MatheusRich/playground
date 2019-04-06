#include <iostream>
#include <set>

#define MIN 0
#define MAIU 1
#define SPACE 2

using namespace std;

int tokenize(char token) {
  if (token >= 'a' && token <= 'z')
    return MIN;
  if (token >= 'A' && token <= 'Z')
    return MAIU;
  if (token == ' ')
    return SPACE;

  printf("ERROR: Invalid token: '%c'! Exiting!\n", token);
  exit(-1);
}

int main(int argc, char *argv[ ]) {
  int n_states;
  scanf("%d", &n_states);

  int n_alphabet;
  scanf("%d", &n_alphabet);

  string alphabet[n_alphabet];
  for (int i = 0; i < n_alphabet; i++) {
    cin >> alphabet[i];
  }

  int table[n_states][n_alphabet];
  for (int i = 0; i < n_states; i++) {
    for (int j = 0; j < n_alphabet; j++) {
      int aux;
      string aux2;
      cin >> aux >> aux2 >> table[i][j];
    }
  }

  int initial_state;
  scanf("%d", &initial_state);

  int n_final_states;
  scanf("%d", &n_final_states);

  set<int> final_states;
  for (int i = 0; i < n_final_states; i++) {
    int aux;
    scanf("%d", &aux);
    final_states.insert(aux);
  }

  int current_state = initial_state;

  getchar(); // Scaping \n

  string word;
  std::getline(std::cin, word);

  for (char current_token : word) {
    if (argv[1]) {
      printf(">Current state: q%d\n", current_state);
      printf("-Token read: %c\n", current_token);
    }

    current_state = table[current_state][tokenize(current_token)];
  }

  if (final_states.find(current_state) != final_states.end()) {
    puts("SUCCESS: Valid input!");
  } else {
    puts("FAILURE: Invalid input!");
  }

  return 0;
}