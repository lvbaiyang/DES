//
// Created by 吕百杨 on 2018/4/9.
//
#include "Key.h"

int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
               1, 58, 50, 42, 34, 26, 18,
              10,  2, 59, 51, 43, 35, 27,
              19, 11,  3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
               7, 62, 54, 46, 38, 30, 22,
              14,  6, 61, 53, 45, 37, 29,
              21, 13,  5, 28, 20, 12,  4};

int PC_2[] = {14, 17, 11, 24,  1,  5,
               3, 28, 15,  6, 21, 10,
              23, 19, 12,  4, 26,  8,
              16,  7, 27, 20, 13,  2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32};

int shiftBit[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};


Key::Key() {
	bitset<64> K = readKey();
//	bitset<64> K(0x133457799BBCDFF1);
//	cout << K << endl;
	bitset<56> K_new = PC_1_Change(K);
	getCD(K_new);
	PC_2_Change();
}

//读取
bitset<64> Key::readKey() {
	ifstream f("/Users/lvbaiyang/Desktop/Key.txt");
	char temp[8];
	int i = 0;
	while(!f.eof()) {
		f >> temp[i];
		i++;
	}

	bitset<64> K;
	for(int i = 7; i >= 0; i--) {
		bitset<8> a (temp[i]);
		for(int j = 8*i; j < 8*(i+1); j++) {
			K[j] = a[j%8];
		}
	}

	return K;
}

//PC_1变换
bitset<56> Key::PC_1_Change(bitset<64> K) {
	bitset<56> K_new;
	for(int i = 0; i < 56; i++) {
		K_new[55-i] = K[64-PC_1[i]];
	}
//	cout << K_new  << endl;
	return K_new;
}

//移位
bitset<28> Key::lShift(bitset<28> subkey, int bit) {//bit 表示左移bit位
	bitset<28> subkey_new;
	subkey_new = subkey<<bit;
	for(int i = 0; i < bit; i++) {
		subkey_new[i] = subkey[28 - bit + i];
	}
	return subkey_new;
}

bitset<48> Key::showK_set(int i) {
	return K_set[i];
}

//得到C0-C16,D0-D16
void Key::getCD(bitset<56> K_new) {
	bitset<28> C_new;
	bitset<28> D_new;
	for(int i = 0; i < 28; i++) {
		D_new[i] = K_new[i];
	}
	for(int i = 28; i < 56; i++) {
		C_new[i-28] = K_new[i];
	}

//	cout << "Cnew " << C_new << endl << "Dnew " << D_new << endl;
	for(int i = 0; i < 16; i++) {
		if(i == 0){
			C[i] = lShift(C_new, shiftBit[i]);
			D[i] = lShift(D_new, shiftBit[i]);
		}else{
			C[i] = lShift(C[i - 1], shiftBit[i]);
			D[i] = lShift(D[i - 1], shiftBit[i]);
		}
	}

//	for(int i = 0; i < 16; i++) {
//		cout << "C[" << i << "] :" << C[i] << endl;
//		cout << "D[" << i << "] :" << D[i] << endl;
//		cout << endl;
//	}
}

//PC_2变换
void Key::PC_2_Change() {
	bitset<56> temp;
	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 28; j++) {
			temp[j] = D[i][j];
			temp[j+28] = C[i][j];
		}//得到CiDi，便于做PC-2变换
		for(int a = 0; a < 48; a++) {
			K_set[i][47-a] = temp[56-PC_2[a]];
		}
	}
}












