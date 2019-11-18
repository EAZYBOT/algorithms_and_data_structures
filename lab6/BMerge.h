#pragma once

#include<fstream>
#include<random>
#include<ctime>
#include<iostream>
#include<vector>
#include<string>

struct ITEM {
	int key = -1;
	char data[196] = "DATA";
};

void init_f0(int n_records);

void b_merge(int p, int &count);