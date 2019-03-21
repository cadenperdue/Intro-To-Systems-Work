#include <stdio.h>
#include <string.h>

#define LIMIT 10000
#define LINE_SIZE 128

int getOriginValue(char[]);
int processOrigin(FILE*, int*);
void removeAllSpaces(char[]);
void toUpperCase(char[]);
int firstPass(FILE*, int[]);
int secondPass(FILE*, int[]);
void printLabels(int[]);
void printAdd(char[]);
void printAnd(char[]);
void printNot(char[]);
void printTrap(char[]);
void printLdr(char[]);
void printStr(char[]);
void printLd(char[], int[], int);
void printSt(char[], int[], int);
void printBr(char[], int[], int);


void assemble(char filename[])
{
	FILE *infile = fopen( filename , "r" );
	
	
	int labels[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	
	
	if (!firstPass(infile, labels))
	{
		secondPass(infile, labels);
	}
	
	fclose(infile);	
}

void printLabels(int labels[])
{
	printf("labels = {%d", labels[0]);
	for (int i =1; i < 10; i++)
	{
		printf(", %d", labels[i]);
	}
	printf("}\n");
}

int firstPass(FILE *infile, int labels[])
{
	char line[LINE_SIZE];
	int lineCount = 0;
	int lc = 0;
	int endFound = 0;
	char c;

	if (infile == NULL) 
	{
		printf("Can't open input file.\n");
		return 5;
	}
  
	int err = processOrigin(infile, &lc);
	
	if (err) return err;
		
	
	while (!endFound && fscanf(infile, "%[^\n]s", line) != EOF && lineCount < LIMIT)
	{ 
		removeAllSpaces(line);
		
		toUpperCase(line);
		

		fscanf(infile, "%c", &c);	
		
		
		lineCount++;  

		if (line[0] != 0 && line[0] != ';')  
		{
		
			if (line[0] == 'L' && line[1] != 'D')  
			{
				int v = line[1] - 48;
				labels[v] = lc;
				
				if (strlen(line) > 2) {
					lc++;
				}
			}
			else if (strncmp(".END", line, 4) == 0)
			{
				endFound = 1;
				lc++;
			}
			else
			{
				lc++;
			}
		}

		
		line[0] = 0;
	}
	
	//Baring an infinite loop, the only way out of the above loop is
	//by hitting an end or hitting an EOF.  If you hit the EOF it
	//means .end was never found.
	if (!endFound)
	{
		printf("ERROR 4: Missing end directive.\n");
		return 4;
	}
	return 0;
}


int secondPass(FILE *infile, int labels[])
{
    rewind(infile);
	char line[LINE_SIZE];
	int lineCount = 0;
	int lc = 0;
	int endFound = 0;
	char c;

	//Read first line.  Should be origin line. 
	//The lc should contain the origin address afterward assuming no error..  
	int err = processOrigin(infile, &lc);
	
	if (err) return err;
	printf("%04X\n", lc);	
	while (!endFound && fscanf(infile, "%[^\n]s", line) != EOF && lineCount < LIMIT)
	{ 
	

		removeAllSpaces(line);
		
		
		toUpperCase(line);
		
		
		fscanf(infile, "%c", &c);	
		
		lineCount++;  

		if (line[0] != 0 && line[0] != ';')
        
        {
			if (line[0] == 'L' && line[1] != 'D')  
	        {
				if (strlen(line) > 2) {
					printf("0000\n");
                    lc++;
				}
			}
			else if (strncmp(".END", line, 4) == 0)
			{
				return 0;
			}
			else
			{
				lc++;
                if (line[0] == 'A')
                {
                    if (line[1] == 'D')
                    {
                        printAdd(line);
                    }
                    else
                    {
                        printAnd(line);
                    }
                }
                else if (line[0] =='N')
                {
                    printNot(line);
                }
                else if (line[0] == 'L' && line[1] == 'D')
                {
                    if (line[3] == 'R' && line[1] == 'D')
                    {
                        printLdr(line);
                    }
                    else if (line[1] == 'D')
                    {
                        printLd(line, labels, lc);
                    }
                }
                else if (line[0] == 'S' && line[1] == 'T')
                {
                    if (line[3] == 'R')
                    {
                        printStr(line);
                    }
                    else
                    {
                        printSt(line, labels, lc);
                    }
                }
                else if (line[0] == 'B')
                {
                    printBr(line, labels, lc);
                }
                else if (line[0] == 'T')
                {
                    printTrap(line);

                }
			}
		}

		//Clear out line string.  Needed for blank lines.
		line[0] = 0;
	}
	return 0;
}

//Convert all characters to uppercase.
void toUpperCase(char line[])
{
	for (int i = 0; line[i] != 0; i++)
	{
		if (line[i] >= 'a' && line[i] <= 'z') 
			line[i] -= 32;
	}
}

//Remove ALL spaces from the line
void removeAllSpaces(char line[])
{
	//Go through all of the characters in the line string.
	for (int i = 0; line[i] != 0; i++)
	{
		//If this character is a space
		if (line[i] == ' ' || line[i] == '\t')
		{
			//Move every single character after this space up one position
			for (int j = i; line[j] != 0; j++)
			{
				line[j] = line[j + 1];
			}
			
			//Need to back up and recheck the space just overwritten
			//Will miss two spaces in a row if you don't do this.
			i--;  
		}
	}
}

int processOrigin(FILE *infile, int *lc)
{
	char line[LINE_SIZE];
	int lineCount = 0;
	char c;
	
	*lc = 0;
	
	//Just check to make sure the file is open.  Not really required by the project
	//but a good idea anyway.
	if (infile == NULL) 
	{
		printf("Can't open input file.\n");
		return 5;
	}

	//Read lines until EOF reached or LIMIT lines read.  Limit prevent infinite loop.
	while (fscanf(infile, "%[^\n]s", line) != EOF && lineCount < LIMIT)
	{
		lineCount++;
		fscanf(infile, "%c", &c);  //Get rid of extra newline.
		removeAllSpaces(line);  //Remove all spaces from this line
		toUpperCase(line); //Convert all characters in this line to upper case
		
		if (line[0] != 0 && line[0] != ';')  //If not a blank line
		{
			//It can't be a blank line or a comment so it HAS to be a .ORIG or it is an error
			if (strncmp(line, ".ORIG", 5) != 0)  
			{
				printf("ERROR 1: Missing origin directive. Origin must be first line in program.\n");
				return 1;
			}
			else
			{
				//It is a .ORIG so figure out the address
				int val;
				if (line[5] == 'X')
					sscanf(&line[6],"%x" ,&val);
				else
					sscanf(&line[5],"%d" ,&val);
				
				if (val > 0xFFFF || val < 0)
				{
					printf("ERROR 2: Bad origin address. Address too big for 16 bits.\n");
					return 2;
				}
				*lc = val;
				return 0;
			}
		}
		
		//Set the line to empty string 
		line[0] = 0;
	}
	
	//We ran out of file and never found an origin
	printf("ERROR 1: Missing origin directive. Origin must be first line in program.\n");
	return 1;
}

void printAdd(char array[])
{
    int base = 0x1000;
    int dr = 0;
    int sr1 = 0;
    int sr2 = 0;
    int imm5 = 0;
    int finalNum = 0;
    if (array[9] == 'R')
    {
        dr = (array[4] - 48);
        sr1 = (array[7] - 48);
        sr2 = (array[10] - 48);

        dr = dr<<9;
        sr1 = sr1<<6;

        finalNum = base | dr | sr1 | sr2;
    }
    else
    {
        int whatever = 0x1;
        whatever = whatever << 5;
        dr = (array[4] - 48);
        sr1 = (array[7] - 48);
        sscanf(&array[10], "%d", &imm5);
        imm5 = imm5 & 0x1F;
        dr = dr << 9;
        sr1 = sr1 <<6;
        finalNum = base | dr | sr1 | imm5 | whatever;
    }
    printf("%04X\n", finalNum);
}

void printAnd(char arr[])
{ 
    int b = 0x5000;
    int dr = 0;
    int sr1 = 0;
    int sr2 = 0;
    int imm5 = 0;
    int finalNum = 0;
    if (arr[9] == 'R')
    {
        dr = (arr[4] - 48);
        sr1 = (arr[7] - 48);
        sr2 = (arr[10] - 48);

        dr = dr<<9;
        sr1 = sr1<<6;

        finalNum = b | dr | sr1 | sr2;
    }
    else
    {
        int b = 0x1;
        b = b << 5;
        dr = (arr[4] - 48);
        sr1 = (arr[7] - 48);
        sscanf(&arr[10], "%d", &imm5);
        imm5 = imm5 & 0x1F;
        dr = dr << 9;
        sr1 = sr1 <<6;
        finalNum = b | dr | sr1 | imm5 | b;
    }
    printf("%04X\n", finalNum);
}

void printNot(char array[])
{
    int base = 0x903F;
    int dr = 0;
    int sr = 0;
    int finalNum = 0;
    dr = (array[4] - 48);
    sr = (array[7] - 48);
    dr = dr<<9;
    sr = sr<<6;
    finalNum = base | dr | sr;
    printf("%04X\n", finalNum);
}

void printTrap(char array[])
{
    int base = 0xF000;
    int digit1 = 0;
    int digit2 = 0;
    int trapvect8 = 0;
    int finalNum = 0;
    digit1 = (array[5] - 48);
    digit2 = (array[6] - 48);
    digit1 = digit1 * 16;
    trapvect8 = digit1 + digit2;
    finalNum = base | trapvect8;
    printf("%04X\n", finalNum);

}

void printLdr(char arr[])
{
    int b = 0x6000;
    int dr = 0;
    int br = 0;
    int o6 = 0;
    int finalNum = 0;
    dr = (arr[4] - 48);
    br = (arr[7] - 48);
    sscanf(&arr[10], "%d", &o6);
    o6 = o6  & 0x3F;
    dr = dr<<9;
    br = br<<6;
    finalNum = b | dr | br | o6;
    printf("%04X\n", finalNum);
}

void printStr(char arr[])
{
    int b = 0x7000;
    int dr = 0;
    int br = 0;
    int o6 = 0;
    int finalNum = 0;
    dr = (arr[4] - 48);
    br = (arr[7] - 48);
    sscanf(&arr[10], "%d", &o6);
    o6 = o6  & 0x3F;
    dr = dr<<9;
    br = br<<6;
    finalNum = b | dr | br | o6;
    printf("%04X\n", finalNum);
}

void printLd(char arr[], int label[], int lc)
{
    int r1 = 0;
    int meme = 0;
    int b = 0;
    b = b | 0x2000;
    r1 = (arr[3] -48);
    meme = (arr[6] - 48);
    b = b | (r1 << 9);
    int pc = (label[meme] - lc);
    b = b | (pc & 0x1FF);
    printf("%04X\n", b);
}

void printSt(char arr[], int label[], int lc)
{
    int base = 0x3000;
    int sr = 0;
    int meme = 0;
    int fin = 0;
    sr = arr[3]  - 48;
    meme = arr[6] - 48;
    sr = sr <<9;
    int pc = (label[meme] - lc);
    pc = pc & 0x1FF;
    fin = base | sr | pc;
    printf("%04X\n", fin);
}

void printBr(char array[], int labels[], int lc)
{
    int output = 0;
    int current = 0;
    while (array[current] != '\n' && array[current] != '\0')
    {
        current++;
        if (array[current] == 'N')
        {
            output |= 0x800;
        }
        else if (array[current] == 'Z')
        {
            output |= 0x400;
        }
        else if (array[current] == 'P')
        {
            output |= 0x200;
        }
        else if (array[current] == 'L')
        {
            current++;
            output += (labels[array[current] - '0'] - lc) & 0x1FF;
        }
    }
    printf("%04X\n", output);
}
