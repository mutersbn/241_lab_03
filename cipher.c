#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char ch, int k);

int main(int argc, char* argv[])
{  
	int choice, n;
	char sKey[4];
	int iKey[4], k;
	char ch;
	FILE *fin, *fout;

	if (argc != 5)
	{
		printf ("Usage: cipher option key infile, outfile\n");
		printf ("Option 1 for encryption and 2 for decryption");
		exit(1);
	}
	
	choice = atoi(argv[1]);
	strcpy(sKey, argv[2]);

	// convert input string to group of four integer numbers
	for(int i=0; i<4; i++)
	{
		iKey[i] = sKey[i] - 'A';

		//printf("Integer Array[%d]: %d\n", i, iKey[i]);
		//printf("String Array[%d]: %c\n", i, sKey[i]);
	}

    fin = fopen(argv[3], "r");
	fout = fopen(argv[4], "w");
    
    if (fin ==  NULL || fout == NULL) 
	{
		printf("File could not be opened\n");
		exit(1);
	}

	fseek(fin, 0L, SEEK_END);
	n = ftell(fin);
	fseek(fin, 0L, SEEK_SET);

	while ( fscanf(fin, "%c", &ch) != EOF )
	{
		k = n % 4;
		if(choice == 2)
			k = -k;
		fprintf(fout, "%c", encrypt(ch, k));
		n--;
	}

	fclose(fin);
	fclose(fout);

	return 0;
}

char encrypt(char ch, int k)
{
	if ( k < 0 )
		k = k + 26;

	if ( isupper(ch) )
		return (ch - 'A' + k) % 26 + 'A';
	
	if ( islower(ch) )
		return (ch - 'a' + k) % 26 + 'a';
	
	return ch;
}
