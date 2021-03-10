#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int key;
// The encryping fucntion takes pointer of the FILE and name of the file as the arguments.
// If the function returns 0, everything is OK,
// Otherwise if an error occurs, the function returns 1
int encZevdThjeshte(FILE *inputFile, char *FileName);

// The decrypting fucntion takes pointer of the FILE and name of the file as the arguments.
// If the function returns 0, everything is OK,
// Otherwise if an error occurs, the function returns 1
int decZevdThjeshte(FILE *inputFile, char *FileNameEncrypted);

int main( int argc, char *argv[])
{
	// the number of arguments should be 4
	if (argc != 4)
	{
		printf("Number of arguments should be 4. \n");
		printf("Syntax\t: encSimple encZevdThjeshte inputFile key\n");
		printf("or\t\t: encSimple decZevdThjeshte inputFile key\n");
		exit(1);
	}
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);
	// if the second argument is not ENCZEVDTHJESHTE or DECZEVDTHJESHTE, the programs ends
	if ((strcmp(argv[1], "ENCZEVDTHJESHTE") != 0 ) && (strcmp(argv[1], "DECZEVDTHJESHTE") != 0))
	{
		printf("The second parameter should be either ENCZEVDTHJESHTE or DECZEVDTHJESHTE\n");
		exit(1);
	}
	
	// verify if the file exist 
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("File %s could not be opened!\n", argv[2]);
		exit(1);		
	}
	fclose(inputFile);
	unsigned int i;
	// Check if the forth argument is number.
	// If it is not a number, the program ends.
	for (i = 0; i < strlen(argv[3]); i++)
	{
		if (!isdigit(argv[3][i]))
		{
			printf("The forth argument should be a number\n");
 			exit(1);
		}
	}
	// Extract key from the forth argument
	sscanf(argv[3], "%d", &key);
	if (key > 26 || key == 0)
	{
		printf("The forth argument should have values from 1-26\n");
		return 0;
	}
	// If the second argument is ENCZEVDTHJESHTE, the function encZevdThjeshte is called
	if (!strcmp(argv[1], "ENCZEVDTHJESHTE"))
	{
		if (encZevdThjeshte(inputFile, argv[2]))
		{
			printf("There has been an error in encryption!\n");
			exit(1);
		}
	}
	// If the second argument is DECZEVDTHJESHTE,  the function decZevdThjeshte is called
	else if (!strcmp(argv[1], "DECZEVDTHJESHTE"))
	{
		if (decZevdThjeshte(inputFile, argv[2]))
		{
			printf("There has been an error in decryption!\n");
			exit(1);
		}
	}
	
	return 0;

}
int encZevdThjeshte(FILE *inputFile, char *FileName)
{
	char FileNameEncrypted[200], FileNameOnly[200];
	char *Extension;
	// Finds the last apperance of the dot (.) in the filename
	// and saves it into Extension variable
	Extension = strrchr(FileName,'.');
	Extension = strupr(Extension);

	// if variable Extension is .ENC, the function returns 1
	if (!strcmp(Extension, ".ENC"))
	{
		printf("The input file extension should not be .ENC!\n");
		return 1;
	}
	
	if((inputFile = fopen(FileName, "r+b" )) == NULL )
	{
		printf("The original file could not be opened\n");
		return 1;		
	}

	strncpy(FileNameOnly, FileName, Extension - FileName);
	FileNameOnly[Extension - FileName] = '\0';
	sprintf(FileNameEncrypted, "%s.ENC", FileNameOnly);

	FILE *EncryptedFile;
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		printf("The encrypted file could not be opened\n");
		return 1;
	}
	// ch is the character of the input file 
	// ch1 is the character of the encrypted file 
	int ch, ch1;
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			// if the read symbol from the file is a character
			if (isalpha(ch))
			{
				if (isupper(ch))
					ch1 = 'A' + (ch % 65 + key) % 26 ;
				else
					ch1 = 'a' + (ch % 97 + key) % 26 ;
			}
			else
			{
				ch1 = ch;
			}
			fputc(ch1, EncryptedFile);
		}
	}
	fclose(inputFile);
	fclose(EncryptedFile);

	return 0;
}

int decZevdThjeshte(FILE *inputFile, char *FileNameEncrypted)
{
	char FileNameDecrypted[200], FileNameOnly[200];
	char *Extension;
	Extension = strrchr(FileNameEncrypted,'.');
	Extension = strupr(Extension);
	// input file must have extension .ENC
	if (strcmp(Extension, ".ENC"))
	{
		printf("The input file should have extension .ENC!\n");
		return 1;
	}

	if((inputFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		printf("The encrypted file could not be opened\n");
		return 1;		
	}
	
	strncpy(FileNameOnly, FileNameEncrypted, Extension - FileNameEncrypted);
	FileNameOnly[Extension - FileNameEncrypted] = '\0';
	sprintf(FileNameDecrypted, "%s.DCP", FileNameOnly);

	FILE *DecryptedFile;
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		printf("The decrypted file could not be opened\n");
		return 1;
	}
	// ch- input character, ch1- decrypted character
	int ch, ch1;
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			if (isalpha(ch))
			{
				if (isupper(ch))
					ch1 = 'A' + (26 + ch % 65 - key) % 26;
				else
					ch1 = 'a' + (26 + ch % 97 - key) % 26;
			}
			else
			{
				ch1 = ch;
			}
			fputc(ch1, DecryptedFile);
		}
	}
	fclose(inputFile);
	fclose(DecryptedFile);
	return 0;
}
