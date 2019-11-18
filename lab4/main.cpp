#include<iostream>
#include<map>
#include<random>
#include<ctime>
#include<fstream>
#include"Hash_table.h"

using namespace std;

ofstream f_res[4];

map<string, bool> set_keys;

void generate_n_keys(int n) {
	mt19937 gen(time(0));

	set_keys.clear();

	for (int i = 0; i < n; i++) {
		string key = "000000";
		do {
			for (char &c : key) {
				switch (gen() % 3) {

				case 0:
					c = 65 + gen() % 26;
					break;

				case 1:
					c = 97 + gen() % 26;
					break;

				case 2:
					c = 48 + gen() % 10;
					break;
				}
			}
		} while (set_keys[key]);
		set_keys[key] = true;
	}
}

int main() {
	int size_table, n_keys;
	cout << "Enter size hash-table and amount keys:" << endl;
	cin >> size_table >> n_keys;

	generate_n_keys(n_keys);

	Hash_table table(size_table);
	table.generate_r_massive(10, 256);

	for (int i = 0; i < 4; i++) {
		f_res[i].open("res_" + to_string(i) + ".csv");

		for (pair<string, bool> k : set_keys) {
			switch (i)
			{
			case 0:
				table.get_item_by_AD(k.first)++;
				break;

			case 1:
				table.get_item_by_XD(k.first)++;
				break;

			case 2:
				table.get_item_by_AM(k.first)++;
				break;

			case 3:
				table.get_item_by_XM(k.first)++;
				break;

			default:
				break;
			}
		}

		for (int j = 0; j < size_table; j++) {
			int n_item_keys = table.get_item_by_index(j);
			int n_colisions = (n_item_keys > 0) ? n_item_keys - 1 : 0;
			f_res[i] << j << "; " << n_item_keys << "; " << n_colisions << endl;
		}

		table.clear_table();

		f_res[i].close();
	}

	return 0;
}