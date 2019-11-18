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
	Hash_table(int size_table);

	void generate_r_massive(int size, int width);

	int& get_item_by_div(int key);
	int& get_item_by_mul(int key);

	// Additive + Divide
	int& get_item_by_AD(std::string str_key);
	// XOR + Divide
	int& get_item_by_XD(std::string str_key);
	// Additive + Multiply
	int& get_item_by_AM(std::string str_key);
	// XOR + Multiply
	int& get_item_by_XM(std::string str_key);

	int& get_item_by_index(int index);

	void clear_table();


private:
	std::vector<int> table;
	std::vector<int> r;

	int size_table_m = 0;
	const double A = (sqrt(5) - 1) / 2;

	int hash_div(int key);
	int hash_mul(int key);

	int additive_method(std::string str);
	int xor_method(std::string str);
};

