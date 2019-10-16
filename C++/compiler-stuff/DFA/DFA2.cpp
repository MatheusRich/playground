#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
  int n_states;
  scanf("%d", &n_states);

  int n_alphabet;
  scanf("%d", &n_alphabet);

  char alphabet[n_alphabet];
  for (int i = 0; i < n_alphabet; i++) {
    cin >> alphabet[i];
  }

  // Current state + token -> next state
  map<pair<int, char>, int> table;

  for (int i = 0; i < n_states; i++) {
    for (int j = 0; j < n_alphabet; j++) {
      int current, next;
      char token;
      cin >> current >> token >> next;
      table[make_pair(current, token)] = next;
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

  getchar(); // Scaping \n

  int current_state = initial_state;
  string word;
  getline(cin, word);
  string word_without_spaces = word;
  replace(word_without_spaces.begin(), word_without_spaces.end(), ' ', '\\'); // Replaces all spaces to '\'

  for (char current_token : word_without_spaces) {
    printf("> Current state: q%d -> Token read: '%c'\n", current_state, current_token);

    auto key = make_pair(current_state, current_token);
    current_state = table[key];
  }
  printf("\n> Last state: q%d\n", current_state);
  printf("> Final states: ");
  for (auto i : final_states)
    printf("q%d ", i);
  printf("\n\n");

  if (final_states.find(current_state) != final_states.end()) {
    printf("SUCCESS: Word '%s' is a valid input!\n", word.c_str());
  } else {
    printf("FAILURE: Word '%s' is an invalid input!\n", word.c_str());
  }

  return 0;
}