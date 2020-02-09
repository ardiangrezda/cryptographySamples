/* Example of encryption of blocks of bytes
	Encryption algorithm as reads input original file (as text file) and
	at the exit is obtained encrypted file
	Decrytion algorithm reads encrypted file and after decrytion decrypted file is obtained
	Encrypted file should have extension .enc, whereas
	decrypted file should have extension .dcp

  	Syntax:	encBlock encBllok inputFile 
				encBlock decBllok inputFile 
	Here n block are taken as input and byte 0 is replaced by byte n-1,
	byte 1 with byte n -1, byte 2 with byte n - 3, etc
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// encryption function which as input arguments takes pointer to a FILE,
// file name and number of blocks. Function returns 0 if everything goes OK, 
// otherwise if something goes wrong, it returns 1
int encBllok(FILE *inputFile, char *FileName, int bllok);

// decryption function which as input arguments takes pointer to a FILE,
// file name and number of blocks. Function returns 0 if everything goes OK, 
// otherwise if something goes wrong, it returns 1
int decBllok(FILE *inputFile, char *FileNameEncrypted, int bllok);

int CheckIfNumber();

void SwapBytes(char *szBuffer, int numread);

int main( int argc, char *argv[])
{
	// number of arguments must be 4
	if (argc != 4)
	{
		printf("Number of arguments should be 4. \n");
		printf("Syntax\t: encBlock encBllok inputFile bllok\n");
		printf("or\t\t: encBlock decBllok inputFile bllok\n");
		exit(1);
	}
	// arguments 1 and 2 should be converted into capital letters
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// if the second argument is not ENCBLLOK or DECBLLOK, 
	// the program will terminate
	if ((strcmp(argv[1], "ENCBLLOK") != 0 ) && (strcmp(argv[1], "DECBLLOK") != 0))
	{
		printf("The second argument must be ENCBLLOK or DECBLLOK\n");
		exit(1);
	}
	
	// verify if the file exists as second parameter
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("File %s does not exist or could not be opened!\n", argv[2]);
		exit(1);		
	}
	long fileSize;
	// determine file size
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	// close the file
	fclose(inputFile);
	unsigned int i;
	// verify if the forth argument is a number,
	// and if it not, then the program will terminate
	for (i = 0; i < strlen(argv[3]); i++)
	{
		if (!isdigit(argv[3][i]))
		{
			printf("The forth argument should be a number\n");
 			exit(1);
		}
	}
	// extract the block from the forth argument
	int bllok;
	sscanf(argv[3], "%d", &bllok);
	if (fileSize < bllok)
	{
		printf("File size is smaller then block of bytes!!\n");
		exit(1);
	}
	// If the second argument is ENCBLLOK, then function encBllok is called
	if (!strcmp(argv[1], "ENCBLLOK"))
	{
		if (encBllok(inputFile, argv[2], bllok))
		{
			printf("There was an error in ecryption!\n");
			exit(1);
		}
	}
	// if the second argument is DECBLLOK, then function decBllok is called
	else if (!strcmp(argv[1], "DECBLLOK"))
	{
		if (decBllok(inputFile, argv[2], bllok))
		{
			printf("There was an error in decryption!\n");
			exit(1);
		}
	}
	
	return 0;

}

int encBllok(FILE *inputFile, char *FileName, int bllok)
{
	char FileNameEncrypted[200], FileNameOnly[200];
	char *Extension;
	// Finds the last apperance of the dot (.) in the filename
	// and saves it into Extension variable	Extension = strrchr(FileName,'.');
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

	// copy characters from FileName to FileNameOnly. 
	// the coping is done until the last occurency of dot (.) in variable FileName
	strncpy(FileNameOnly, FileName, Extension - FileName);

	// variable FileNameOnly ends with '\0'
	FileNameOnly[Extension - FileName] = '\0';
	// variable FileNameEncrypted copies only name of the file, but it is appended by extension .ENC
	sprintf(FileNameEncrypted, "%s.ENC", FileNameOnly);

	FILE *EncryptedFile;
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		printf("Encrypted file could not be opened\n");
		return 1;
	}
	
	int numread, numwritten;
	char *szBuffer = new char [bllok];

	while (!feof(inputFile))
	{
		numread = fread(szBuffer, sizeof(char), bllok, inputFile);
		szBuffer[numread] = '\0';
		SwapBytes(szBuffer, numread);
		numwritten = fwrite(szBuffer, sizeof(char), numread, EncryptedFile);
	}
	// files are closed
	szBuffer = 0;
	delete [] szBuffer;
	fclose(inputFile);
	fclose(EncryptedFile);
	
	return 0;
}

int decBllok(FILE *inputFile, char *FileNameEncrypted, int bllok)
{
	char FileNameDecrypted[200], FileNameOnly[200];
	char *Extension;
	Extension = strrchr(FileNameEncrypted,'.');
	Extension = strupr(Extension);
	// input file should have extension .ENC, otherwise will return
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
	int numread, numwritten;
	char *szBuffer = new char [bllok];
	while (!feof(inputFile))
	{
		numread = fread(szBuffer, sizeof(char), bllok, inputFile);
		szBuffer[numread] = '\0';
		SwapBytes(szBuffer, numread);
		numwritten = fwrite(szBuffer, sizeof(char), numread, DecryptedFile);
	}
	szBuffer = 0;
	delete [] szBuffer;
	fclose(inputFile);
	fclose(DecryptedFile);
	return 0;
}


void SwapBytes(char *szBuffer, int numread)
{
	char temp;
	int len = strlen(szBuffer);
	for (int i = 0; i < len / 2; i++)
	{
		temp = szBuffer[len - i - 1];
		szBuffer[len - i - 1] = szBuffer[i];
		szBuffer[i] = temp;
	}
}
