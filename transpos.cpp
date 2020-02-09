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
	// numri i argumenteve duhet te jete 3
	if (argc != 3)
	{
		printf("Numri i argumenteve te dhena nga shfrytezuesi duhet te jete 3. \n");
		printf("Sintaksa\t: shembulli_23 encryptTransposition inputFile\n");
		printf("ose\t\t: shembulli_23 decryptTransposition inputFile\n");
		exit(1);
	}
	// argumentet 1 dhe 2 konvertohen ne shkronja te medha
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// nese argumenti i dyte nuk eshte ENCRYPTTRANSPOSITION ose DECRYPTTRANSPOSITION, 
	// programi perfundon
	if ((strcmp(argv[1], "ENCRYPTTRANSPOSITION") != 0 ) && (strcmp(argv[1], "DECRYPTTRANSPOSITION") != 0))
	{
						 
		printf("Argumenti i dyte duhet te jete ENCRYPTTRANSPOSITION ose DECRYPTTRANSPOSITION\n");
		exit(1);
	}
	
	// verifikojme a ekziston file-i i cili eshte marre si parametri i dyte (argv[2])
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("File %s nuk mund te hapet apo nuk ekziston!\n", argv[2]);
		exit(1);		
	}
	// mbyllim file-in
	fclose(inputFile);
	// Nese argumenti i dyte eshte ENCRYPTTRANSPOSITION, atehere thirret funksioni encrypttranspos
	if (!strcmp(argv[1], "ENCRYPTTRANSPOSITION"))
	{
		if (encrypttranspos(inputFile, argv[2]))
		{
			printf("Kemi nje gabim ne enkriptim!\n");
			exit(1);
		}
	}
	// Nese argumenti i dyte eshte DECRYPTCESAR, atehere thirret funksioni decryptCesar
	else if (!strcmp(argv[1], "DECRYPTTRANSPOSITION"))
	{
		if (decrypttranspos(inputFile, argv[2]))
		{
			printf("Kemi nje gabim ne decriptim!\n");
			exit(1);
		}
	}
	
	return 0;

}

int encrypttranspos(FILE *inputFile, char *FileName)
{
	char FileNameEncrypted[200], FileNameOnly[200];
	char *Extension;

	// Gjen paraqitjen e fundit te pikes ne emrin e file-it dhe rezultatin e ruan
	// ne variablen Extension
	Extension = strrchr(FileName,'.');
	Extension = strupr(Extension);

	// nese variabla Extension eshte .ENC atehere ky funksion i kthehet funksionit main()
	if (!strcmp(Extension, ".ENC"))
	{
		printf("File-i hyres duhet te mos kete ekstenzion .ENC!\n");
		return 1;
	}
	
	if((inputFile = fopen(FileName, "r+b" )) == NULL )
	{
		printf("File-i origjinal nuk mund te hapet\n");
		return 1;		
	}

	// kopjo karakteret prej variables FileName ne FileNameOnly. 
	// Kopjimi behet vetem deri te 
	// paraqitja e fundit e pikes ne variablen FileName
	strncpy(FileNameOnly, FileName, Extension - FileName);

	// variabla FileNameOnly perfundon me '\0'
	FileNameOnly[Extension - FileName] = '\0';
	// variabla FileNameEncrypted kopjon vetem emrin e file-it, por i shtohet edhe 
	// ekstenzioni .ENC
	sprintf(FileNameEncrypted, "%s.ENC", FileNameOnly);

	FILE *EncryptedFile;
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		printf("File-i i encryptuar nuk mund te hapet\n");
		return 1;
	}
	int ch, i;
	long position, fileSize;
	// percakto madhesine e file-it
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
	for (i = 0; i < KEY; i++)
	{
		// zhvendos poziten e file-it prej fillimit + i (0, 1, 2, ...)
		fseek(inputFile, i, SEEK_SET);
		while (!feof(inputFile))
		{
			ch = fgetc(inputFile);
			fputc(ch, EncryptedFile);
			// zhvendose pointerin e file-it per KEY - 1
			fseek(inputFile, KEY - 1, SEEK_CUR);
			// trego poziten e file-it
			position = ftell(inputFile);
			// ne rast se pozita e pointerit te file-it 
			// eshte me e madhe se madhesia e file-it
			if (position >= fileSize)
			{
				break;
			}
		}
		fputc(32, EncryptedFile);
	}
	// mbyllet file-i hyres dhe file-i i enkriptuar
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
	// file-i hyres apo i enkriptuar duhet te kete ekstenzionin .ENC
	// perndryshe funksioni perfundon
	if (strcmp(Extension, ".ENC"))
	{
		printf("File-i hyres i enkriptuar duhet te kete ekstenzionin .ENC!\n");
		return 1;
	}

	if((inputFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		printf("File-i i enkriptuar nuk mund te hapet\n");
		return 1;		
	}
	
	strncpy(FileNameOnly, FileNameEncrypted, Extension - FileNameEncrypted);
	FileNameOnly[Extension - FileNameEncrypted] = '\0';
	sprintf(FileNameDecrypted, "%s.DCP", FileNameOnly);

	FILE *DecryptedFile;
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		printf("File-i i dekriptuar nuk mund te hapet\n");
		return 1;
	}
	
	int ch, i, j = 0;
	long position, fileSize;

	fseek(inputFile, 0, SEEK_END);
	// percakto madhesine e file-it hyres
	fileSize = ftell(inputFile);
	// percakto numrin e rreshtave ne matrice
	long NumriRreshave = fileSize / KEY;
	// Per tekstin e enkriptuar disa rreshta jane me
	// te medha, e disa me te vogla
	long ZhvendosjaPointeritFile;

	for (i = 0; i < NumriRreshave; i++)
	{
		// zhvendos poziten e file-it prej fillimit + i (0, 1, 2, ...)
		fseek(inputFile, i, SEEK_SET);
		// j percakton per sa duhet zhvendosur pointerin
		// e file-it, varesisht sa eshte madhesia 
		// e nje rreshti
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
			// tregon poziten e pointerit te file-it
			// ne pointer
			position = ftell(inputFile);

			if (position >= fileSize)
			{
				break;
			}
		}
	}
	fclose(DecryptedFile);
	// ne fund kane mbetur disa zbraztesira ne file-in e 
	// dekriptuar. Ato duhet te fshihen. Kete e bejme
	// duke e zvogluar madhesine e file-it te enkriptuar
	int fh;
	if( fh = _open( FileNameDecrypted, _O_RDWR )  != -1 )
	{
		int AAS = _chsize( _fileno(DecryptedFile), fileSize - KEY);
	}
	_close(fh);
	fclose(inputFile);
	return 0;
}

