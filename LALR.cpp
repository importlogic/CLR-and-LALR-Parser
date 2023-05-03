#include <bits/stdc++.h>

using namespace std;

const int maxSize = 1000;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	vector<int> dsu(maxSize, -1);

	function<int(int)> find = [&](int p) -> int {
		if(dsu[p] < 0)
			return p;

		return dsu[p] = find(dsu[p]);
	};

	auto merge = [&](int x, int y) {
		if(x > y)
			swap(x, y);

		dsu[x] += dsu[y];
		dsu[y] = x;
	};

	ifstream input("items.txt");
	string next;
	string current = "";
	vector<string> items;	
	while(getline(input, next)){
		if(isdigit(next[0])){
			if(current.size()){
				items.push_back(current);
				current = "";
			}
		}
		else{
			current += next;
		}
	}
	items.push_back(current);
	input.close();
	input.clear();

	int n = items.size();

	vector<char> terminals, nonterminals;
	input.open("terminals.txt");
	while(getline(input, next))
		terminals.push_back(next[0]);
	input.close();
	input.clear();

	input.open("non-terminals.txt");
	while(getline(input, next))
		nonterminals.push_back(next[0]);
	input.close();
	input.clear();

	vector<map<char, string>> table(n);

	for(int i = 0; i < n; i++){
		for(auto t : terminals)
			table[i][t] = "";
		for(auto nt : nonterminals)
			table[i][nt] = "";
	}

	input.open("table.txt");
	int index;
	while(getline(input, next)){
		if(isdigit(next[0])){
			index = stoi(next);
		}
		else{
			table[index][next[0]] = next.substr(2);
		}
	}
	input.close();
	input.clear();
	
	vector<string> stateName(n);

	for(int i = 0; i < n; i++)
		stateName[i] = to_string(i);

	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(items[i] == items[j]){
				int x = find(i);
				int y = find(j);

				merge(i, j);

				stateName[i] += "," + to_string(j);
			}
		}
	}


	map<string, map<char, string>> lalrtable;

	for(int i = 0; i < n; i++){
		if(dsu[i] < 0){
			string name = stateName[i];
			for(auto item : table[i]){
				string cellitem = item.second;
				if(cellitem == "")
					continue;

				if(cellitem == "ac"){
					lalrtable[name][item.first] = cellitem;
				}
				else if(isdigit(cellitem[0])){
					int number = stoi(cellitem);
					number = find(number);
					lalrtable[name][item.first] = stateName[number];
				}
				else{
					int number = stoi(cellitem.substr(1));
					number = find(number);
					string ans = "";
					ans += cellitem[0];
					ans += stateName[number];
					lalrtable[name][item.first] = ans;
				}
			}
		}
		else{
			string daddy = stateName[dsu[i]];

			for(auto item : table[i]){
				string cellitem = item.second;
				if(cellitem == "")
					continue;

				if(cellitem == "ac"){
					if(lalrtable[daddy][item.first] == ""){
						lalrtable[daddy][item.first] = cellitem;
					}
					else if(lalrtable[daddy][item.first] != cellitem){
						cout << "LALR Table not possible!\n";
						return 0;
					}
				}
				else if(isdigit(cellitem[0])){
					int number = stoi(cellitem);
					number = find(number);

					if(lalrtable[daddy][item.first] == ""){
						lalrtable[daddy][item.first] = stateName[number];
					}
					else if(lalrtable[daddy][item.first] != stateName[number]){
						cout << "LALR Table not possible!\n";
						return 0;
					}
				}
				else{
					int number = stoi(cellitem.substr(1));
					number = find(number);
					string ans = "";
					ans += cellitem[0];
					ans += stateName[number];

					if(lalrtable[daddy][item.first] == ""){
						lalrtable[daddy][item.first] = ans;
					}
					else if(lalrtable[daddy][item.first] != ans){
						cout << "LALR Table not possible!\n";
						return 0;						
					}
				}
			}
		}
	}

	cout << "\n______________________________________________________________________________________________________________________\n";
	cout << "\n\tLALR(1) TABLE\n\n";
	cout << "______________________________________________________________________________________________________________________\n";
	cout << "\t|";
	for(auto nt : nonterminals)
		cout << "  " << nt << "\t\t|";
	for(auto t : terminals)
		cout << "  " << t << "\t\t|";
	cout << "\n______________________________________________________________________________________________________________________\n";



	for(int i = 0; i < n; i++){
		if(dsu[i] < 0){
			string state = stateName[i];
			cout << state << "\t|";
			for(auto nt : nonterminals)
				cout << "  " << lalrtable[state][nt] << "\t\t|";
			for(auto t : terminals)
				cout << "  " << lalrtable[state][t] << "\t\t|";
			cout << '\n';
		}
	}
	cout << "______________________________________________________________________________________________________________________\n\n";

	return 0;
}