#include "Hash_table.h"

using namespace std;

Hash_table::Hash_table(int size_table, int c)
{
	table.resize(size_table, "");
	this->size_table_m = size_table;
	this->c = c;
}

void Hash_table::generate_r_massive(int size, int width)
{
	mt19937 gen(time(0));

	r.resize(size, 0);
	for (int i = 0; i < size; i++) {
		r[i] = gen() % width;
	}
}

bool Hash_table::insert_by_linear_div(std::string str_key, int& len_search)
{
	bool result = false;

	int i = 0;

	int a = hash_div(xor_method(str_key));

	do {
		if (table[a] == "") {
			table[a] = str_key;
			result = true;
			break;
		}
		else if (table[a] == str_key) {
			break;
		}
		else {
			i++;
			a = (a + c) % size_table_m;
		}
	} while (i < size_table_m);

	len_search = i;
	
	return result;
}

bool Hash_table::insert_by_linear_mul(std::string str_key, int& len_search)
{
	bool result = false;

	int i = 0;

	int a = hash_mul(xor_method(str_key));

	do {
		if (table[a] == "") {
			table[a] = str_key;
			result = true;
			break;
		}
		else if (table[a] == str_key) {
			break;
		}
		else {
			i++;
			a = (a + c) % size_table_m;
		}
	} while (i < size_table_m);

	len_search = i;

	return result;
}

bool Hash_table::insert_by_quadratic_div(std::string str_key, int& len_search)
{
	bool result = false;

	int i = 0;

	int a = hash_div(xor_method(str_key));
	int b = 1;

	do {
		if (table[a] == "") {
			table[a] = str_key;
			result = true;
			break;
		}
		else if (table[a] == str_key) {
			break;
		}
		else {
			i++;
			a = (a + b + c) % size_table_m;
			b += 2;
		}
	} while (i < size_table_m);

	len_search = i;

	return result;
}

bool Hash_table::insert_by_quadratic_mul(std::string str_key, int& len_search)
{
	bool result = false;

	int i = 0;

	int a = hash_mul(xor_method(str_key));
	int b = 1;

	do {
		if (table[a] == "") {
			table[a] = str_key;
			result = true;
			break;
		}
		else if (table[a] == str_key) {
			break;
		}
		else {
			i++;
			a = (a + b + c) % size_table_m;
			b += 2;
		}
	} while (i < size_table_m);

	len_search = i;

	return result;
}

void Hash_table::clear_table()
{
	table.clear();
	table.resize(size_table_m, "");
}

int Hash_table::hash_div(int key)
{
	return key % size_table_m;
}

int Hash_table::hash_mul(int key)
{
	double tmp;

	return (int) this->size_table_m * modf(key * A, &tmp);
}

int Hash_table::xor_method(std::string str)
{
	int res = 0;

	for (int i = 0; i < str.size(); i++) {
		res += str[i] ^ r[i];
	}

	return res;
}
