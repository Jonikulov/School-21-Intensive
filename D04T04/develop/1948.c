#include <stdio.h>

int find_remainder(int a, int b);
int calculate_lpd(int x);

int main() {
    int x;

    if (scanf("%d", &x) != 1) {
	printf("n/a");
	return 1;
    }

    if (x == 0 || x==1 || x == -1) {
	printf("n/a");
	return 2;
    }

    if (x<0) x*= -1;

    printf("%d", calculate_lpd(x));

    return 0;
}

int find_remainder(int a, int b) {

    while (a >= b) {
	a -= b;
    }

    return a;
}

int calculate_lpd(int x) {
    int is_prime;
    int lpd;
    
    for (int i=2; i<x+1; i++) {
	// Identify if `i` is prime
	is_prime = 1;
	for (int j=2; j<i; j++) {
	    if (find_remainder(i, j) == 0) {
		is_prime = 0;
		break;
	    }
	}
	// Check if `i` is divisor of `x`
	if (is_prime && find_remainder(x, i)==0) {
	    lpd = i;
	}
    }

    return lpd;
}
