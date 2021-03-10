#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#define KEY		11

int encrypttranspos(FILE *inputFile, char *FileName);
int decrypttranspos(FILE *inputFile, char *FileName);

int main( int argc, char *argv[])
{
	// the number of arguments should be 3
	if (argc != 3)
	{
		printf("The number of arguments should be 3. \n");
		printf("Syntax\t: transpos encryptTransposition inputFile\n");
		printf("or\t\t: transpos decryptTransposition inputFile\n");
		exit(1);
	}

	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// if the second argument is not ENCRYPTTRANSPOSITION or DECRYPTTRANSPOSITION, the programs ends
	if ((strcmp(argv[1], "ENCRYPTTRANSPOSITION") != 0 ) && (strcmp(argv[1], "DECRYPTTRANSPOSITION") != 0))
	{
		printf("The second argument should be either ENCRYPTTRANSPOSITION or DECRYPTTRANSPOSITION\n");
		exit(1);
	}
	
	// verify if the file exist 
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("File %s could not be opened or does not exist!\n", argv[2]);
		exit(1);		
	}

	fclose(inputFile);
	// If the second argument is ENCRYPTTRANSPOSITION, function encrypttranspos is called
	if (!strcmp(argv[1], "ENCRYPTTRANSPOSITION"))
	{
		if (encrypttranspos(inputFile, argv[2]))
		{
			printf("There has been an error in encryption!\n");
			exit(1);
		}
	}
	// If the second parameter is DECRYPTTRANSPOSITION, function decrypttranspos is called
	else if (!strcmp(argv[1], "DECRYPTTRANSPOSITION"))
	{
		if (decrypttranspos(inputFile, argv[2]))
		{
			printf("There has been an error in decryption!\n");
			exit(1);
		}
	}
	
	return 0;

}

int encrypttranspos(FILE *inputFile, char *FileName)
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
		printf("The input file should not have extension .ENC!\n");
		return 1;
	}
	
	if((inputFile = fopen(FileName, "r+b" )) == NULL )
	{
		printf("The original file could not be opened\n");
		return 1;		
	}

	strncpy(FileNameOnly, FileName, Extension - FileName);
	FileNameOnly[Extension - FileName] = '\0';
	// variable FileNameEncrypted copies file name appended by .ENC
	sprintf(FileNameEncrypted, "%s.ENC", FileNameOnly);

	FILE *EncryptedFile;
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		printf("The encrypted file could not be opened\n");
		return 1;
	}
	int ch, i;
	long position, fileSize;
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	for (i = 0; i < KEY; i++)
	{
		// move file pointer from the begining + i (0, 1, 2, ...)
		fseek(inputFile, i, SEEK_SET);
		while (!feof(inputFile))
		{
			ch = fgetc(inputFile);
			fputc(ch, EncryptedFile);
			// move file pointer for KEY - 1
			fseek(inputFile, KEY - 1, SEEK_CUR);
			position = ftell(inputFile);
			// if the position of the pointer file is greater than 
			// the file size, will break from while loop
			if (position >= fileSize)
			{
				break;
			}
		}
		fputc(32, EncryptedFile);
	}
	fclose(inputFile);
	fclose(EncryptedFile);
	return 0;
}

int decrypttranspos(FILE *inputFile, char *FileNameEncrypted)
{
	char FileNameDecrypted[200], FileNameOnly[200];
	char *Extension;
	Extension = strrchr(FileNameEncrypted,'.');
	Extension = strupr(Extension);
	// input file must have extension .ENC
	if (strcmp(Extension, ".ENC"))
	{
		printf("Input file should have extension .ENC!\n");
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
	
	int ch, i, j = 0;
	long position, fileSize;

	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	long NumriRreshave = fileSize / KEY;
	long ZhvendosjaPointeritFile;

	for (i = 0; i < NumriRreshave; i++)
	{
		// move file pointer from the begining + i (0, 1, 2, ...)
		fseek(inputFile, i, SEEK_SET);
		// j determines for how much should be pointer moved
		j = 0;
		while (!feof(inputFile))
		{
			ch = fgetc(inputFile);
			fputc(ch, DecryptedFile);
			j++;
			if (j > fileSize % KEY)
				ZhvendosjaPointeritFile = NumriRreshave - 1;
			else
				ZhvendosjaPointeritFile = NumriRreshave;
			fseek(inputFile, ZhvendosjaPointeritFile, SEEK_CUR);
			position = ftell(inputFile);

			if (position >= fileSize)
			{
				break;
			}
		}
	}
	fclose(DecryptedFile);
	// there has been some blanks in the decrypted file . The blanks should be deleted .
	// This can be done by reducing output filenkriptuar
	int fh;
	if( fh = _open( FileNameDecrypted, _O_RDWR )  != -1 )
	{
		int AAS = _chsize( _fileno(DecryptedFile), fileSize - KEY);
	}
	_close(fh);
	fclose(inputFile);
	return 0;
}

