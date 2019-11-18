#pragma once

#include<string>
#include<vector>
#include<random>
#include<ctime>
#include<cmath>
#include<iostream>

class Hash_table
{
public:
	Hash_table(int size_table, int c);

	void generate_r_massive(int size, int width);

	bool insert_by_linear_div(std::string str_key, int& len_search);
	bool insert_by_linear_mul(std::string str_key, int& len_search);

	bool insert_by_quadratic_div(std::string str_key, int& len_search);
	bool insert_by_quadratic_mul(std::string str_key, int& len_search);

	void clear_table();


private:
	std::vector<std::string> table;
	std::vector<int> r;

	int size_table_m = 0;
	const double A = (sqrt(5) - 1) / 2;
	int c = 0;

	int hash_div(int key);
	int hash_mul(int key);

	int xor_method(std::string str);
};

