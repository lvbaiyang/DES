//
// Created by 吕百杨 on 2018/4/9.
//
#include <bitset>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef DES_KEY_H
#define DES_KEY_H

#endif //DES_KEY_H
class Key{
private:
	bitset<48> K_set[16];
	bitset<28> C[16];
	bitset<28> D[16];
	bitset<64> readKey();
	bitset<56> PC_1_Change(bitset<64> K);
	bitset<28> lShift(bitset<28> subkey, int bit);
	void PC_2_Change();
	void getCD(bitset<56> K_new);

public:
	Key();

	bitset<48> showK_set(int i);
};