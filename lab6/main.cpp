#include<iostream>
#include<chrono>
#include<iomanip>
#include"BMerge.h"

#define MAX_EXPR 10
#define MIN_EXPR 2

using namespace std;

void output_file(string str) {
	fstream f;
	f.open(str, ios::in | ios::binary);

	ITEM i;
	while (true) {
		f.read((char*)&i, sizeof(ITEM));
		if (f.eof()) {
			break;
		}

		cout << i.key << endl;

	}
	f.close();
}

int main() {
	init_f0(10000);

	cout.setf(ios::left);
	cout << setw(5) << "Ways" << setw(6) << "Time" << setw(6) << "Pass" << endl;

	for (int i = MIN_EXPR; i <= MAX_EXPR; i++) {
		int count = 0;

		auto start = chrono::steady_clock::now();

		b_merge(i, count);

		auto end = chrono::steady_clock::now();
		auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

		cout << setw(5) << i << setw(6) << elapsed.count() / 1000.0 << setw(6) << count << endl;
	}

	return 0;
}