#include<iostream>
#include<vector>
#include<map>

#define variable first
#define producoes second

using namespace std;

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
  
  return 0;
}

