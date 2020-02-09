#include <stdio.h>
int gcd(int a, int b);
int main()
{
	int a, b;
	printf("Input value for a: ");
	scanf("%d", &a);
	printf("Input value for b: ");
	scanf("%d", &b);
	int d = gcd(a, b);
	printf("a = %d, b = %d, d = %d\n", a, b, d);
	return 0;
}
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a %b);
}
