#include<iostream>
#include<map>
#include<random>
#include<ctime>
#include<fstream>
#include"Hash_table.h"

using namespace std;

ofstream f_expr;

map<string, bool> set_keys;
mt19937 gen(time(0));

void generate_n_keys(int n) {
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
	int size_table, coef_c;
	cout << "Enter size hash-table, coef. C:" << endl;
	cin >> size_table >> coef_c;

	Hash_table table(size_table, coef_c);
	table.generate_r_massive(10, 256);

	for (int n_exp = 0; n_exp < 5; n_exp++) {
		f_expr.open("expr_" + to_string(n_exp) + ".csv");

		for (int i = 10; i <= size_table; i += 10) {
			f_expr << i << "; ";
		}
		f_expr << endl;

		for (int j = 0; j < 4; j++) {

			for (int i = 10; i <= size_table; i += 10) {
				generate_n_keys(10);

				int total_len = 0;

				for (pair<string, bool> k : set_keys) {
					int cur_len;
					switch (j)
					{
					case 0:
						table.insert_by_linear_div(k.first, cur_len);
						break;

					case 1:
						table.insert_by_linear_mul(k.first, cur_len);
						break;

					case 2:
						table.insert_by_quadratic_div(k.first, cur_len);
						break;

					case 3:
						table.insert_by_quadratic_mul(k.first, cur_len);
						break;

					default:
						break;
					}
					
					total_len += cur_len;
				}

				double tmp;
				int fir_part = total_len / 10.0;
				int sec_part = modf(total_len / 10.0, &tmp) * 100;

				f_expr << fir_part << "," << sec_part << "; ";
			}

			table.clear_table();
			f_expr << endl;
		}

		

		f_expr.close();
	}

	return 0;
}