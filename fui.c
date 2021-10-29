#include <stdio.h>
#include <string.h>

//Yes, I used global variables.
unsigned char memory[4096];
unsigned char* ptr = memory;
unsigned char var = 0;

FILE* in = NULL;

void interrupt()
{
	switch(var)
	{
		case 0: //>
			ptr++;
			break;
		case 1: //<
			ptr--;
			break;
		case 2: //+
			++*ptr;
			break;
		case 3: //-
			--*ptr;
			break;
		case 4: //.
			putchar(*ptr);
			break;
		case 5: //,
			*ptr = getchar();
			break;
		case 6: //Ignore *(ptr+1) instructions if *ptr == 0
			if(!(*ptr))
			{
				for(unsigned char i = 0 ; i < *(ptr+1) ; i++)
					fgetc(in);
			}
			break;
		case 7: //GOTO >:D
			fseek(in, *ptr, SEEK_SET);
			var = 0;
			break;
	}
}

int main(int argc, char** argv)
{
	if(argc != 2)
		return printf("Usage: fui <file.fu>\r\n")-21;

	in = fopen(argv[1], "rb");

	if(in == NULL)
		return printf("Error opening input file.\r\n")-26;

	while(1)
	{
		switch(fgetc(in))
		{
			case EOF:
				goto end; //Spaghetti forever !
			case 'F': //Add instruction
				var++;
				break;
			case 'U':
				interrupt();
				break;
		}
		continue;
		end:
			break;
	}
}
