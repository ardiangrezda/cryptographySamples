/* Exapmle of polyalphabetic encryption
	The encrypted file takes input file as a text file, whereas the encrypted file is created as output
	The decrypted file takes input file as a encrypted file, whereas the decrypted file is created as output

  	Syntax:	encPolyAlphabetic encPolialfabetik inputFile 
		encPolyAlphabetic decPolialfabetik inputFile 
		
	The encrypion is done as following:
		First symbol -> symbol->Rot(key 1)
		Second symbol -> symbol->Rot(key 2)
		Third symbol -> symbol->Rot(key 3)
		Forth symbol -> symbol->Rot(key 1)
		Fifth symbol -> symbol->Rot(key 2)
		Sixth symbol -> symbol->Rot(key 3)
		etc...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int *Qelesat;
int NumriQelesave = 0;

// The encryption function takes pointer of the file and file name as arguments.
// If everything will be OK, it will return 0
// If there is an error, the function returns 1
int encPolialfabetik(FILE *inputFile, char *FileName);

// The decryption function takes pointer of the file and file name as arguments.
// If everything will be OK, it will return 0
// If there is an error, the function returns 1
int decPolialfabetik(FILE *inputFile, char *FileNameEncrypted);

int CheckIfNumber();
int main( int argc, char *argv[])
{
	// the number of arguments should be 3
	if (argc != 3)
	{
		printf("The number of arguments should be 3. \n");
		printf("Syntax\t: encPolyAlphabetic encPolialfabetik inputFile \n");
		printf("or\t\t: encPolyAlphabetic decPolialfabetik inputFile\n");
		exit(1);
	}
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// if the second argument is not ENCPOLIALFABETIK or DECPOLIALFABETIK, 
	// the program will terminate
	if ((strcmp(argv[1], "ENCPOLIALFABETIK") != 0 ) && (strcmp(argv[1], "DECPOLIALFABETIK") != 0))
	{
		printf("The second argument should be either ENCPOLIALFABETIK or DECPOLIALFABETIK\n");
		exit(1);
	}
	
	// verify if the file exists as second parameter
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("File %s does not exist or could not be opened!!\n", argv[2]);
		exit(1);		
	}
	long position, fileSize;
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	fclose(inputFile);
	
	printf("Number of keys: ");
	NumriQelesave = CheckIfNumber(); 

	// The keys are created dynamically, depending on variable NumriQelesave
	Qelesat	= new int[NumriQelesave];
	for (int i = 0; i < NumriQelesave; i++)
	{
		printf("\Key %d: ", i);
		Qelesat[i] = CheckIfNumber(); 
		if (Qelesat[i]  > 26 || Qelesat[i] == 0)
		{
			printf("\Key %d should be from 1-26!!", i);
			i--;
		}
	}
	// If the second argument is ENCPOLIALFABETIK, then function encPolialfabetik is called
	if (!strcmp(argv[1], "ENCPOLIALFABETIK"))
	{
		if (encPolialfabetik(inputFile, argv[2]))
		{
			printf("There was an error in ecryption!\n");
			exit(1);
		}
	}
	// If the second argument is DECPOLIALFABETIK, then function decPolialfabetik is called
	else if (!strcmp(argv[1], "DECPOLIALFABETIK"))
	{
		if (decPolialfabetik(inputFile, argv[2]))
		{
			printf("There was an error in decryption!\n");
			exit(1);
		}
	}
	
	return 0;

}
int encPolialfabetik(FILE *inputFile, char *FileName)
{
	char FileNameEncrypted[200], FileNameOnly[200];
	char *Extension;
	// Finds the last apperance of the dot (.) in the filename
	// and saves it into Extension variable	Extension = strrchr(FileName,'.');
	Extension = strrchr(FileName,'.');
	Extension = strupr(Extension);

	// if variable Extension is .ENC, then will return to main()
	if (!strcmp(Extension, ".ENC"))
	{
		printf("Input file should not have extension .ENC!\n");
		return 1;
	}
	
	if((inputFile = fopen(FileName, "r+b" )) == NULL )
	{
		printf("The original file could not be opeened\n");
		return 1;		
	}

	strncpy(FileNameOnly, FileName, Extension - FileName);
	FileNameOnly[Extension - FileName] = '\0';
	sprintf(FileNameEncrypted, "%s.ENC", FileNameOnly);

	FILE *EncryptedFile;
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		printf("Encrypted file could not be opened\n");
		return 1;
	}
	// ch - character of the input file
	// ch1 - encrypted character
	// ReadCh is read character % Number of keys
	// i.e. if NumriQelesave is 4, ReadCh mund te kete vlerat 0,1,2,3
	int ch, ch1, ReadCh;
	ReadCh = 0;
	
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			if (isalpha(ch))
			{
				if (isupper(ch))
				{
					ch1 = 'A' + (ch % 65 + Qelesat[ReadCh]) % 26 ;
				}
				else
				{
					ch1 = 'a' + (ch % 97 + Qelesat[ReadCh]) % 26 ;
				}
				ReadCh++;
				ReadCh = ReadCh % NumriQelesave;
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

int decPolialfabetik(FILE *inputFile, char *FileNameEncrypted)
{
	char FileNameDecrypted[200], FileNameOnly[200];
	char *Extension;
	Extension = strrchr(FileNameEncrypted,'.');
	Extension = strupr(Extension);
	// input file should have extension .ENC, otherwise it return 1
	if (strcmp(Extension, ".ENC"))
	{
		printf("Input file should have extension .ENC!\n");
		return 1;
	}

	if((inputFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		printf("Encrypted file could not be opened\n");
		return 1;		
	}
	
	strncpy(FileNameOnly, FileNameEncrypted, Extension - FileNameEncrypted);
	FileNameOnly[Extension - FileNameEncrypted] = '\0';
	sprintf(FileNameDecrypted, "%s.DCP", FileNameOnly);

	FILE *DecryptedFile;
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		printf("Decrypted file could not be opeend\n");
		return 1;
	}
	// ch- input character, ch1- decrypted character
	int ch, ch1, ReadCh;
	ReadCh = 0;
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			if (isalpha(ch))
			{
				if (isupper(ch))
				{
					ch1 = 'A' + (26 + ch % 65 - Qelesat[ReadCh]) % 26;
				}
				else
				{
					ch1 = 'a' + (26 + ch % 97 - Qelesat[ReadCh]) % 26;
				}
				ReadCh++;
				ReadCh = ReadCh % NumriQelesave;
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

int CheckIfNumber()
{
	int Number = 0;
	int tempCharacter;
	do
	{
		tempCharacter = getch();
		if (tempCharacter >= '0' && tempCharacter <= '9')
		{
			if (Number != 0 || tempCharacter != '0')
			{
				putch(tempCharacter);
				Number = Number * 10 + tempCharacter - 48 ;
			}
			else
				printf("\a");
		}
		else if (tempCharacter == 0xd)
		{
		}
		else
		{
			printf("\a");
		}
	} while (tempCharacter != 0xd);
	return Number;
}
