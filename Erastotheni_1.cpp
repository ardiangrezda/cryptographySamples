#include <stdio.h>
#include <math.h>
#include <conio.h>
int main()
{
	int n;
	printf("Te ipet numri: ");
	scanf("%d", &n);
	char *Composites = new char[n];
	int i, j;
	for (i = 0; i < n; i++)
	{
		Composites[i] = 0;
	}
	for (i = 2; i < sqrt(n); i++)
	{
		if (Composites[i] == 0)
		{
			for (j = 2 * i; j < n; j += i)
				Composites[j] = 1;
		}
	}
	printf("Numrat e thjeshte jane: \n");
	j = 1;
	int ch;
	for (i = 2; i < n; i++)
	{
		if (Composites[i] == 0)
		{
			printf("%d\t", i);
			j++;
			if ((j % 200) == 0)
			{
				printf("\n\aShtyp qfaredo karakteri <ESC> per dalje\n");
				ch = getch();
				if (ch == 0x1b)
				{
					break;
				}
			}
		}
	}
	printf("\n");
	delete [] Composites;
	Composites = 0;
	return 0; 
}