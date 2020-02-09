#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int key;
// funksioni i enkriptimit i cili si argumente hyrese ka pointerin ne FILE 
// dhe emrin e datotekes. Ky funksion kthen 0 nese qdo gje perfundon ne rregull,
// perndryshe nese ka ndonje gabim ky funksion kthen 1
int encZevdThjeshte(FILE *inputFile, char *FileName);

// funksioni i dekriptimit i cili si argumente hyrese ka pointerin ne FILE 
// dhe emrin e datotekes. Ky funksion kthen 0 nese qdo gje perfundon ne rregull,
// perndryshe nese ka ndonje gabim ky funksion kthen 1
int decZevdThjeshte(FILE *inputFile, char *FileNameEncrypted);

int main( int argc, char *argv[])
{
	// numri i argumenteve duhet te jete 4
	if (argc != 4)
	{
		printf("Numri i argumenteve te dhena nga shfrytezuesi duhet te jete 4. \n");
		printf("Sintaksa\t: shembulli_25 encZevdThjeshte inputFile qelesi\n");
		printf("ose\t\t: shembulli_25 decZevdThjeshte inputFile qelesi\n");
		exit(1);
	}
	// argumentet 1 dhe 2 konvertohen ne shkronja te medha
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// nese argumenti i dyte nuk eshte ENCZEVDTHJESHTE ose DECZEVDTHJESHTE, 
	// programi perfundon
	if ((strcmp(argv[1], "ENCZEVDTHJESHTE") != 0 ) && (strcmp(argv[1], "DECZEVDTHJESHTE") != 0))
	{
		printf("Argumenti i dyte duhet te jete ENCZEVDTHJESHTE ose DECZEVDTHJESHTE\n");
		exit(1);
	}
	
	// verifikojme a ekziston datoteka e cila eshte marre si parametri i dyte (argv[2])
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("Datoteka %s nuk mund te hapet apo nuk ekziston!\n", argv[2]);
		exit(1);		
	}
	// mbyllim datoteken
	fclose(inputFile);
	unsigned int i;
	// verifiko a eshte argumenti i katert numer
	// e nese nuk eshte numer, atehere pason dalja nga programi
	for (i = 0; i < strlen(argv[3]); i++)
	{
		if (!isdigit(argv[3][i]))
		{
			printf("Argumenti i katert duhet te jete numer\n");
 			exit(1);
		}
	}
	// ekstrakto qelesin nga argumenti i katert
	sscanf(argv[3], "%d", &key);
	if (key > 26 || key == 0)
	{
		printf("Argumenti i katert duhet te kete vlera prej 1-26\n");
		return 0;
	}
	// Nese argumenti i dyte eshte ENCZEVDTHJESHTE, atehere thirret funksioni encZevdThjeshte
	if (!strcmp(argv[1], "ENCZEVDTHJESHTE"))
	{
		if (encZevdThjeshte(inputFile, argv[2]))
		{
			printf("Kemi nje gabim ne enkriptim!\n");
			exit(1);
		}
	}
	// Nese argumenti i dyte eshte DECZEVDTHJESHTE, atehere thirret funksioni decZevdThjeshte
	else if (!strcmp(argv[1], "DECZEVDTHJESHTE"))
	{
		if (decZevdThjeshte(inputFile, argv[2]))
		{
			printf("Kemi nje gabim ne decriptim!\n");
			exit(1);
		}
	}
	
	return 0;

}
int encZevdThjeshte(FILE *inputFile, char *FileName)
{
	char FileNameEncrypted[200], FileNameOnly[200];
	char *Extension;
	// Gjen paraqitjen e fundit te pikes ne emrin e datotekes dhe rezultatin e ruan
	// ne variablen Extension
	Extension = strrchr(FileName,'.');
	Extension = strupr(Extension);

	// nese variabla Extension eshte .ENC atehere ky funksion i kthehet funksionit main()
	if (!strcmp(Extension, ".ENC"))
	{
		printf("Datoteka hyrese duhet te mos kete ekstenzion .ENC!\n");
		return 1;
	}
	
	if((inputFile = fopen(FileName, "r+b" )) == NULL )
	{
		printf("Datoteka origjinale nuk mund te hapet\n");
		return 1;		
	}

	// kopjo karakteret prej variables FileName ne FileNameOnly. 
	// Kopjimi behet vetem deri te 
	// paraqitja e fundit e pikes ne variablen FileName
	strncpy(FileNameOnly, FileName, Extension - FileName);

	// variabla FileNameOnly perfundon me '\0'
	FileNameOnly[Extension - FileName] = '\0';
	// variabla FileNameEncrypted kopjon vetem emrin e datotekes, por i shtohet edhe 
	// ekstenzioni .ENC
	sprintf(FileNameEncrypted, "%s.ENC", FileNameOnly);

	FILE *EncryptedFile;
	if ((EncryptedFile = fopen(FileNameEncrypted, "w+b")) == NULL)
	{
		printf("Datoteka e encryptuar nuk mund te hapet\n");
		return 1;
	}
	// ch eshte karakteri i datotekes hyrese
	// ch1 eshte karakteri i enkriptuar
	int ch, ch1;
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			// nese karakteri i lexuar i datotekes eshte shkronje
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
			// shkruaj ne datoteken dalese
			fputc(ch1, EncryptedFile);
		}
	}
	// mbyllet datoteken hyrese dhe datoteken e enkriptuar
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
	// datoteka hyrese apo e enkriptuar duhet te kete ekstenzionin .ENC
	// perndryshe funksioni perfundon
	if (strcmp(Extension, ".ENC"))
	{
		printf("Datoteka hyrese e enkriptuar duhet te kete ekstenzionin .ENC!\n");
		return 1;
	}

	if((inputFile = fopen(FileNameEncrypted, "r+b" )) == NULL )
	{
		printf("Datoteka e enkriptuar nuk mund te hapet\n");
		return 1;		
	}
	
	strncpy(FileNameOnly, FileNameEncrypted, Extension - FileNameEncrypted);
	FileNameOnly[Extension - FileNameEncrypted] = '\0';
	sprintf(FileNameDecrypted, "%s.DCP", FileNameOnly);

	FILE *DecryptedFile;
	if ((DecryptedFile = fopen(FileNameDecrypted, "w+b")) == NULL)
	{
		printf("Datoteka e dekriptuar nuk mund te hapet\n");
		return 1;
	}
	// ch- karakteri hyres, ch1- karakteri i dekriptuar
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
