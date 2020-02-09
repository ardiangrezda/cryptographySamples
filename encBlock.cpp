/* Shembull i shifrimit te blloqeve te bajtave
	Algoritmi i enkriptimit si file hyres e merr file-in origjinal
	si text file, ndersa ne dalje fitohet file i enkriptuar
	Ndersa algoritmi i dekriptimit si hyrje e merr file-in e enkriptuar 
	dhe pas dekriptimit fitohet file-i i dekriptuar
	File origjinal (si file hyres i algoritmit te enkriptuar) duhet te jete
	i identik me file-in dales te dekriptuar (file-i dales i 
	algoritmit te dekriptuar)
	File i enkriptuar do te kete ekstenzionin .enc, ndersa 
	file i dekriptuar do te kete ekstensionin .dcp

  	Sintaksa:	shembulli_27 encBllok inputFile 
				shembulli_27 decBllok inputFile 
	
	Ketu merret nje bllok prej n bajtave dhe bajti 0 zevendesohet me 
	bajtin n-1, bajti 1 me n-2, bajti 2 me n-3, etj

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// funksioni i enkriptimit i cili si argumente hyrese ka pointerin ne FILE, 
// emrin e datotekes dhe numrin e blloqeve. Ky funksion kthen 0 nese 
// qdo gje perfundon ne rregull, perndryshe nese ka ndonje 
// gabim ky funksion kthen 1
int encBllok(FILE *inputFile, char *FileName, int bllok);

// funksioni i dekriptimit i cili si argumente hyrese ka pointerin ne FILE ,
// emrin e datotekes dhe numrin e blloqeve. Ky funksion kthen 0 nese 
// qdo gje perfundon ne rregull, perndryshe nese ka ndonje gabim 
// ky funksion kthen 1
int decBllok(FILE *inputFile, char *FileNameEncrypted, int bllok);

int CheckIfNumber();

void SwapBytes(char *szBuffer, int numread);

int main( int argc, char *argv[])
{
	// numri i argumenteve duhet te jete 3
	if (argc != 4)
	{
		printf("Numri i argumenteve te dhena nga shfrytezuesi duhet te jete 4. \n");
		printf("Sintaksa\t: shembulli_27 encBllok inputFile bllok\n");
		printf("ose\t\t: shembulli_27 decBllok inputFile bllok\n");
		exit(1);
	}
	// argumentet 1 dhe 2 konvertohen ne shkronja te medha
	argv[1] = strupr(argv[1]);
	argv[2] = strupr(argv[2]);

	// nese argumenti i dyte nuk eshte ENCBLLOK ose DECBLLOK, 
	// programi perfundon
	if ((strcmp(argv[1], "ENCBLLOK") != 0 ) && (strcmp(argv[1], "DECBLLOK") != 0))
	{
		printf("Argumenti i dyte duhet te jete ENCBLLOK ose DECBLLOK\n");
		exit(1);
	}
	
	// verifikojme a ekziston datoteka e cila eshte marre si parametri i dyte (argv[2])
	FILE *inputFile;
	if((inputFile = fopen( argv[2], "r+b" )) == NULL )
	{
		printf("Datoteka %s nuk mund te hapet apo nuk ekziston!\n", argv[2]);
		exit(1);		
	}
	long fileSize;
	// percakto madhesine e file-it
	fseek(inputFile, 0, SEEK_END);
	fileSize = ftell(inputFile);
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
	// ekstrakto bllokun nga argumenti i katert
	int bllok;
	sscanf(argv[3], "%d", &bllok);
	if (fileSize < bllok)
	{
		printf("Madhesia e file-it eshte me e madhe se blloku i bajtave\n");
		exit(1);
	}
	// Nese argumenti i dyte eshte ENCBLLOK, atehere thirret funksioni encBllok
	if (!strcmp(argv[1], "ENCBLLOK"))
	{
		if (encBllok(inputFile, argv[2], bllok))
		{
			printf("Kemi nje gabim ne enkriptim!\n");
			exit(1);
		}
	}
	// Nese argumenti i dyte eshte DECBLLOK, atehere thirret funksioni decBllok
	else if (!strcmp(argv[1], "DECBLLOK"))
	{
		if (decBllok(inputFile, argv[2], bllok))
		{
			printf("Kemi nje gabim ne decriptim!\n");
			exit(1);
		}
	}
	
	return 0;

}

int encBllok(FILE *inputFile, char *FileName, int bllok)
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
	
	int numread, numwritten;
	char *szBuffer = new char [bllok];

	while (!feof(inputFile))
	{
		numread = fread(szBuffer, sizeof(char), bllok, inputFile);
		szBuffer[numread] = '\0';
		SwapBytes(szBuffer, numread);
		numwritten = fwrite(szBuffer, sizeof(char), numread, EncryptedFile);
	}
	// mbyllet datoteken hyrese dhe datoteken e enkriptuar
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