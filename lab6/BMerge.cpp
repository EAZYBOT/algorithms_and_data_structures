#include "BMerge.h"

using namespace std;

void init_f0(int n_records)
{
	mt19937 gen(time(0));

	fstream f0;
	f0.open("file_0", ios::out | ios::binary | ios::trunc);

	for (int i = 0; i < n_records; i++) {
		ITEM out_rec;
		out_rec.key = gen() % 10000;

		f0.write((const char*) &out_rec, sizeof(ITEM));
	}

	f0.close();
}

void b_merge(int p, int &count)
{
	fstream f0;
	vector<fstream> f(2 * p);
	vector<int> t(2 * p);

	count = 0;

	f0.open("file_0", ios::in | ios::binary);
	for (int i = 0; i < p; i++) {
		f[i].open("file_" + to_string(i + 1), ios::out | ios::binary | ios::trunc);
	}

	int j = 0;
	int L = 0;

	ITEM item, preItem;
	while (true)
	{
		f0.read((char*)&item, sizeof(ITEM));

		if (f0.eof()) {
			L++;
			break;
		}

		if (item.key < preItem.key) {
			j = (j == p - 1) ? 0 : j + 1;
			L++;
		}

		f[j].write((const char*)&item, sizeof(ITEM));
		preItem = item;
	}

	for (int i = 0; i < p; i++) {
		f[i].close();
	}

	for (int i = 0; i < 2 * p; i++) {
		t[i] = i;
	}

	do {
		count++;

		int af = min(p, L);
		vector<int> ta(af);

		for (int i = 0; i < af; i++) {
			f[t[i]].open("file_" + to_string(t[i] + 1), ios::in | ios::binary);
		}

		for (int i = p; i < 2 * p; i++) {
			f[t[i]].open("file_" + to_string(t[i] + 1), ios::out| ios::binary | ios::trunc);
		}

		for (int i = 0; i < af; i++) {
			ta[i] = t[i];
		}

		L = 0;
		j = p;

		do {
			L++;
			int ao = af;

			do {
				ITEM min;
				int m = 0;

				f[ta[0]].read((char*)&min, sizeof(ITEM));

				ITEM mas_rep;
				for (int i = 1; i < ao; i++) {
					f[ta[i]].read((char*)&mas_rep, sizeof(ITEM));

					if (f[ta[i]].eof()) {
						continue;
					}

					if (min.key > mas_rep.key) {
						min = mas_rep;
						m = i;
					}
				}

				for (int i = 0; i < ao; i++) {
					if (m != i) {
						f[ta[i]].seekg(-(int)sizeof(ITEM), ios::cur);
					}
				}

				f[t[j]].write((const char*)&min, sizeof(ITEM));

				f[ta[m]].read((char*)&mas_rep, sizeof(ITEM));

				if (f[ta[m]].eof()) {
					af--;
					ao--;
					
					swap(ta[m], ta[ao]);
					swap(ta[ao], ta[af]);
				}
				else {
					f[ta[m]].seekg(-(int)sizeof(ITEM), ios::cur);
					if (mas_rep.key < min.key) {
						ao--;
						swap(ta[m], ta[ao]);

					}
				}

			} while (ao > 0);

			// Переключить J
			j = (j < (2 * p - 1)) ? j + 1 : p;
		} while (af > 0);

		// Переключение t[]
		for (int k = 0; k < p; k++) {
			swap(t[k], t[k + p]);
		}

		for (int i = 0; i < 2 * p; i++) {
			f[i].close();
		}

	} while (L > 1);
}
