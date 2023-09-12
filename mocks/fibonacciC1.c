#import <stdio.h>

int main() {
	int i1 = 0; //first fibonacci register
	int i2 = 1;	//second fibonacci register
	int i3;	//third fibonacci register

	for(int i = 0; i < 10; i++) {
		i3 = i1 + i2;
		printf("%i", i3); // a: "bruh"
		i1 = i2;
		i2 = i3;
	}

	return 0;
}