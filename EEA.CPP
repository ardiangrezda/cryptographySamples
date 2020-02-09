#include <stdio.h>
void EEA(int a, int b, int *d, int *x, int *y);
int main()
{
	int a, b;
	printf("Te ipet a: ");
	scanf("%d", &a);
	printf("Te ipet b: ");
	scanf("%d", &b);
	int d, x, y;
	EEA(a, b, &d, &x, &y);
	printf("a = %d b = %d d = %d x = %d y = %d\n", a, b, d, x, y);
	return 0;
}

void EEA(int a, int b, int *d, int *x, int *y)
{
	int d1, x1, y1;
	if (b == 0)
	{
		*d = a;
		*x = 1;
		*y = 0;
		return;
	}
	else
	{
		EEA(b, a % b, &d1, &x1, &y1);
		*d = d1;
		*x = y1;
		*y = x1 - (a / b) * y1;
	}
}

