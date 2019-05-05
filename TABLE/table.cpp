#include<iostream>
#include<vector>
#include<map>

#define variable first
#define producoes second

using namespace std;

bool is_terminal(char c) {
  return islower(c);
}


int main(){
  /* ********** LER ENTRADA ********** */
  int nvar;

  cin >> nvar;

  map<string, vector<string>> tabela_de_producoes;

  for(int i=0; i < nvar; i++){
    string aux, aux2;
    int nprod;

    vector<string> aux3;

    cin >> aux >> nprod;    
  
    for(int j = 0; j < nprod; j++){
      cin >> aux2;
      aux3.push_back(aux2);
    }

    tabela_de_producoes[aux] = aux3;
  }

  cout << "\n";

  cout << "TABELA DE PRODUÇÕES\n";
  for(auto i : tabela_de_producoes){
    cout << i.variable << " -> (";
    string output = "";
    for(auto producao : i.producoes){
      output += (", " + producao);
    }
    cout << output.erase(0,2) <<")\n";
  }

  cout << "\n";


  /* ********** LER ENTRADA ********** */

  map<string, vector<pair<char,string>>> tabela1;

  for(auto row : tabela_de_producoes){
    vector<pair<char, string>> aux_row;

    for(auto producao : row.producoes){
      aux_row.push_back(make_pair(producao[0], producao));
    }

    tabela1[row.variable] = aux_row;
  }

  cout << "TABELA 1\n";
  for(auto row : tabela1){
    cout << row.first << " -> [";
    for(auto producao : row.second){
      cout << "(" << producao.first;
      cout << ", " << producao.second << ")";
    }
    cout << "]\n";
  }

  map<string, vector<pair<char, string>>> tabela2;

  for(auto row:tabela1) {
    int n_elements = row.second.size();
    tabela2[row.variable] = row.second; // copies tabela1 vector to table 2
    for (int i = 0; i< n_elements; i++) {
      char current = tabela2[row.variable][i].first; 
      if (not is_terminal(current)) {
        string scurrent = string(1, current);
        for (auto j : tabela1[scurrent]) {
          string from = tabela2[row.variable][i].second;
          auto asdf = make_pair(j.first, from);
          tabela2[row.variable].push_back(asdf);
          n_elements++;      
        }
      }
    }
  }

  cout << "\n";

  cout << "TABELA 2\n";
  for(auto row : tabela2){
    cout << row.first << " -> [";
    for(auto producao : row.second){
      cout << "(" << producao.first;
      cout << ", " << producao.second << ")";
    }
    cout << "]\n";
  }

  map<string, vector<pair<char, string>>> tabela_final;

  for(auto row : tabela2){
    for(auto producao : row.producoes){
      if(is_terminal(producao.first)) {
        tabela_final[row.variable].push_back(producao);
      }
    }
  }

  cout << "\n";

  cout << "TABELA FINAL\n";
  for(auto row : tabela_final){
    cout << row.first << " -> [";
    for(auto producao : row.second){
      cout << "(" << producao.first;
      cout << ", " << producao.second << ")";
    }
    cout << "]\n";
  }

  return 0;
}
