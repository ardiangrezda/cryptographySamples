/* Shembull i shifrimit polialfabetik
	Algoritmi i enkriptimit si file hyres e merr file-in origjinal
	si text file, ndersa ne dalje fitohet file i enkriptuar
	Ndersa algoritmi i dekriptimit si hyrje e merr file-in e enkriptuar 
	dhe pas dekriptimit fitohet file-i i dekriptuar
	File origjinal (si file hyres i algoritmit te enkriptuar) duhet te jete
	i identik me file-in dales te dekriptuar (file-i dales i 
	algoritmit te dekriptuar)
	File i enkriptuar do te kete ekstenzionin .enc, ndersa 
	file i dekriptuar do te kete ekstensionin .dcp

  	Sintaksa:	shembulli_26 encPolialfabetik inputFile 
				shembulli_26 decPolialfabetik inputFile 
	
	Ketu shfrytezohet shifrimi polialfabetik per enkriptim/dekriptim
	Dmth .	Simboli i pare	-> simboli->Rot(qelesi 1)
			Simboli i dyte	-> simboli->Rot(qelesi 2)
			Simboli i trete -> simboli->Rot(qelesi 3)
			etj,
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int *Qelesat;
int NumriQelesave = 0;
// funksioni i enkriptimit i cili si argumente hyrese ka pointerin ne FILE 
// dhe emrin e datotekes. Ky funksion kthen 0 nese qdo gje perfundon ne rregull,
// perndryshe nese ka ndonje gabim ky funksion kthen 1
int encPolialfabetik(FILE *inputFile, char *FileName);

// funksioni i dekriptimit i cili si argumente hyrese ka pointerin ne FILE 
// dhe emrin e datotekes. Ky funksion kthen 0 nese qdo gje perfundon ne rregull,
// perndryshe nese ka ndonje gabim ky funksion kthen 1
int decPolialfabetik(FILE *inputFile, char *FileNameEncrypted);

int CheckIfNumber();
int main( int argc, char *argv[])
{
	// numri i argumenteve duhet te jete 3
	if (argc != 3)
	{
		printf("Numri i argumenteve te dhena nga shfrytezuesi duhet te jete 3. \n");
		printf("Sintaksa\t: shembulli_26 encPolialfabetik inputFile \n");
		printf("ose\t\t: shembulli_26 decPolialfabetik inputFile\n");
		exit(1);
	}
	// argumentet 1 dhe 2 konvertohen ne shkronja te medha
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// nese argumenti i dyte nuk eshte ENCPOLIALFABETIK ose DECPOLIALFABETIK, 
	// programi perfundon
	if ((strcmp(argv[1], "ENCPOLIALFABETIK") != 0 ) && (strcmp(argv[1], "DECPOLIALFABETIK") != 0))
	{
		printf("Argumenti i dyte duhet te jete ENCPOLIALFABETIK ose DECPOLIALFABETIK\n");
		exit(1);
	}
	
	// verifikojme a ekziston datoteka e cila eshte marre si parametri i dyte (argv[2])
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("Datoteka %s nuk mund te hapet apo nuk ekziston!\n", argv[2]);
		exit(1);		
	}
	long position, fileSize;
	// percakto madhesine e file-it
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);

	// mbyllim datoteken
	fclose(inputFile);
	
	printf("Numri i qelesave: ");
	NumriQelesave = CheckIfNumber(); 

	// krijon qelesat dinamikisht, varesisht nga variabla NumriQelesave
	Qelesat	= new int[NumriQelesave];
	for (int i = 0; i < NumriQelesave; i++)
	{
		printf("\nQelesi %d: ", i);
		Qelesat[i] = CheckIfNumber(); 
		if (Qelesat[i]  > 26 || Qelesat[i] == 0)
		{
			printf("\nQelesi %d duhet te kete vlera prej 1-26!!", i);
			i--;
		}
	}
	// Nese argumenti i dyte eshte ENCPOLIALFABETIK, atehere thirret funksioni encPolialfabetik
	if (!strcmp(argv[1], "ENCPOLIALFABETIK"))
	{
		if (encPolialfabetik(inputFile, argv[2]))
		{
			printf("Kemi nje gabim ne enkriptim!\n");
			exit(1);
		}
	}
	// Nese argumenti i dyte eshte DECPOLIALFABETIK, atehere thirret funksioni decPolialfabetik
	else if (!strcmp(argv[1], "DECPOLIALFABETIK"))
	{
		if (decPolialfabetik(inputFile, argv[2]))
		{
			printf("Kemi nje gabim ne decriptim!\n");
			exit(1);
		}
	}
	
	return 0;

}
int encPolialfabetik(FILE *inputFile, char *FileName)
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
	// ReadCh eshte karakteri me rend i lexuar % Numri i Qelesave.
	// dmth. nese NumriQelesave eshte 4, ReadCh mund te kete vlerat 0,1,2,3
	int ch, ch1, ReadCh;
	ReadCh = 0;
	
	while (!feof(inputFile))
	{
		ch = fgetc(inputFile);
		if (ch != EOF)
		{
			// nese karakteri i lexuar i datotekes eshte shkronje
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
			// shkruaj ne datoteken dalese
			fputc(ch1, EncryptedFile);
		}
	}
	// mbyllet datoteken hyrese dhe datoteken e enkriptuar
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