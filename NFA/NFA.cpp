#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#define INVALID -10000000

using namespace std;

bool is_final_state(int item, set<int> set) {
  if (set.find(item) != set.end())
    return true;
  return false;
}

int automaton(int current_state, string word, map<pair<int, char>, vector<int>> table, set<int> final_states) {
  // printf("> Current state: q%d\n", current_state);
  if (word.size() > 0) {
    char token = word[0];
    // printf("-> Token read: '%c'\n", token);
    string new_word = word.erase(0, 1);
    vector<int> possible = table[make_pair(current_state, token)];
    // printf("T%d\n", possible.size());
    if (possible.size() == 0) {
      return INVALID;
    }

    for(auto state : possible) {
      // printf("-> Possible state: '%d':'%d'\n", current_state, state);
      // printf("-> Word: '%s'\n-----------\n", word.c_str());
      int end = automaton(state, new_word, table, final_states);
      if (is_final_state(end, final_states)) {
        // puts("MAS OQ É ISSO");
        // printf("%d", state);
        return end;
      }
      current_state = INVALID;
    }
  }
  // printf("%d\n", current_state);
  return current_state;
}

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
  map<pair<int, char>, vector<int>> table;

  for (int i = 0; i < n_states; i++) {
    for (int j = 0; j < n_alphabet; j++) {
      int current, n_next_states;
      char token;
      cin >> current >> token >> n_next_states;

      vector<int> next_states;
      for (int k = 0; k < n_next_states; k++) {
        int value;
        cin >> value;
        
        next_states.push_back(value);
      }

      table[make_pair(current, token)] = next_states;
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

  string word;
  getline(cin, word);
  string word_without_spaces = word;
  replace(word_without_spaces.begin(), word_without_spaces.end(), ' ', '\\'); // Replaces all spaces to '\'

  int current_state = initial_state;
  int last_state = automaton(current_state, word_without_spaces, table, final_states);

  // printf("> Last state: q%d\n", last_state);
  
  // printf("\n> Final states: { ");
  // for (auto i : final_states)
  //   printf("q%d ", i);
  // printf("}\n\n");

  if (is_final_state(last_state, final_states)) {
    // printf("SUCCESS: Word '%s' is a valid input!\n", word.c_str());
    puts("Aceito");
  } else {
    puts("Rejeito");
    // printf("FAILURE: Word '%s' is an invalid input!\n", word.c_str());
  }

  return 0;
}