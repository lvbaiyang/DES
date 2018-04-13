#include <iostream>
#include "Key.h"

int main() {
	Key test;
	for(int i = 0; i < 16; i++) {
		cout << test.showK_set(i) << endl;
	}
	return 0;
}