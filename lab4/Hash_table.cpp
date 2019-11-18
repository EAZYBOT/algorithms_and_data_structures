#include "Hash_table.h"

using namespace std;

Hash_table::Hash_table(int size_table)
{
	table.resize(size_table, 0);
	this->size_table_m = size_table;
}

void Hash_table::generate_r_massive(int size, int width)
{
	mt19937 gen(time(0));

	r.resize(size, 0);
	for (int i = 0; i < size; i++) {
		r[i] = gen() % width;
	}
}

int& Hash_table::get_item_by_div(int key)
{
	return table[hash_div(key)];
}

int& Hash_table::get_item_by_mul(int key)
{
	return table[hash_mul(key)];
}

int& Hash_table::get_item_by_AD(std::string str_key)
{
	return get_item_by_div(additive_method(str_key));
}

int& Hash_table::get_item_by_XD(std::string str_key)
{
	return get_item_by_div(xor_method(str_key));
}

int& Hash_table::get_item_by_AM(std::string str_key)
{
	return get_item_by_mul(additive_method(str_key));
}

int& Hash_table::get_item_by_XM(std::string str_key)
{
	return get_item_by_mul(xor_method(str_key));
}

int& Hash_table::get_item_by_index(int index)
{
	return table[index];
}

void Hash_table::clear_table()
{
	table.clear();
	table.resize(size_table_m, 0);
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

int Hash_table::additive_method(std::string str)
{
	int res = 0;

	for (char c : str) {
		res += c;
	}

	return res;
}

int Hash_table::xor_method(std::string str)
{
	int res = 0;

	for (int i = 0; i < str.size(); i++) {
		res += str[i] ^ r[i];
	}

	return res;
}
