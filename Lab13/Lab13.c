#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef unsigned char byte;

typedef union frame
{
	byte buffer[10];

	struct
	{
		byte data[10];
		// 0,1,2 ID3 3,4 (sub)version 5 flags 6,7,8,9 size | for main frame
		// 0,1,2,3 title 4,5,6,7 size 8,9 flags | for other frames
	} data;
} FRAME;

void show (char* inputFileName)
{
    FILE* input = fopen(inputFileName, "rb");

    if (input == NULL) return;

    FRAME frame;

    fread(frame.buffer, sizeof(byte), 10, input);
    printf ("Version: ");
    for (int i = 0; i < 3; ++i)
        printf ("%c", *(frame.buffer + i));
    printf ("v%d.%d\n", *(frame.buffer + 3), *(frame.buffer + 4));

    long long title = *(frame.buffer + 9) + *(frame.buffer + 8) * 256 + *(frame.buffer + 7) * 256 * 256 + *(frame.buffer + 6) * 256 * 256 * 256;

    printf ("Meta information:\n");
    while (ftell(input) < title + 10)
	{
		fread(frame.buffer, sizeof(char), 10, input);
		if (*frame.buffer == 0)
			break;
        for (int i = 0; i < 4; ++i)
            printf("%c", *(frame.buffer + i));
        printf(": ");

		unsigned int size = *(frame.buffer + 7) + *(frame.buffer + 6) * 256 + *(frame.buffer + 5) * 256 * 256 + *(frame.buffer + 4) * 256 * 256 * 256;

		unsigned char* frameContent;
		frameContent = malloc(sizeof(byte) * size + 1 );
		fread(frameContent, sizeof(byte), size, input);
		unsigned int i;
		for (int i = 0; i < size; ++i)
			printf("%c", frameContent[i]);
		printf("\n");
		free(frameContent);
	}

    fclose(input);
}

void get(char* inputFileName, char prop_name[4])
{
	FILE* input = fopen(inputFileName, "rb");

	FRAME frame;
	fread(frame.buffer, sizeof(byte), 10, input);

	long long title = *(frame.buffer + 9) + *(frame.buffer + 8) * 256 + *(frame.buffer + 7) * 256 * 256 + *(frame.buffer + 6) * 256 * 256 * 256;

	while (ftell(input) < title + 10)
	{
		fread(frame.buffer, sizeof(byte), 10, input);

		unsigned int size = *(frame.buffer + 7) + *(frame.buffer + 6) * 256 + *(frame.buffer + 5) * 256 * 256 + *(frame.buffer + 4) * 256 * 256 * 256;

        int f = 1;
        for (int i = 0; i < 4; ++i)
            if (prop_name[i] != *(frame.buffer + i)) f = 0;

		if (f)
		{
			printf("%s: ", prop_name);

			unsigned char* frameContent;
			frameContent = malloc(sizeof(byte) * size + 1);
			fread(frameContent, sizeof(byte), size, input);
			unsigned int i;
			for (i = 0; i < size; ++i)
			{
				printf("%c", frameContent[i]);
			}
			printf("\n");
			free(frameContent);
			fclose(input);
			return;
		}

		fseek(input, size, SEEK_CUR);
	}
	fclose(input);
}

void set (char* inputFileName, char prop_name[4], char* prop_value, int flag)
{
    FILE* input = fopen (inputFileName, "rb");
    FILE* output = fopen("output.mp3", "w");
    fclose (output);
    output = fopen("output.mp3", "r+b");

    FRAME frame;
    fread (frame.buffer, sizeof(byte), 10, input);

    long long title = *(frame.buffer + 9) + *(frame.buffer + 8) * 256 + *(frame.buffer + 7) * 256 * 256 + *(frame.buffer + 6) * 256 * 256 * 256;

    for (int i = 0; i < 10; ++i)
        putc(*(frame.buffer + i), output);

    unsigned int newSize = 0;
    long long newTitle = title;

    while (ftell(input) < title + 10)
	{
		fread(frame.buffer, sizeof(byte), 10, input);

		unsigned int size = *(frame.buffer + 7) + *(frame.buffer + 6) * 256 + *(frame.buffer + 5) * 256 * 256 + *(frame.buffer + 4) * 256 * 256 * 256;

        int f = 0;
        for (int i = 0; i < 4; ++i)
            if (prop_name[i] == *(frame.buffer + i)) f++;

		if (f != 4)
		{
		    for (int i = 0; i < 10; ++i)
                putc(*(frame.buffer + i), output);

			char c;
			for (int i = 0; i < size; ++i)
			{
			    c = getc(input);
				putc(c, output);
			}
		}
		else
        {
            newSize = strlen(prop_value);
            newTitle = title + newSize - size;
            *(frame.buffer + 7) = newSize % 256;
            *(frame.buffer + 6) = newSize / 256 % 256;
            *(frame.buffer + 5) = newSize / 256 / 256 % 256;
            *(frame.buffer + 4) = newSize / 256 / 256 / 256 % 256;
            for (int i = 0; i < 10; ++i)
                putc(*(frame.buffer + i), output);

			char c;
			for (int i = 0; i < size; ++i)
			{
			    c = getc(input);
			}
			for (int i = 0; i < newSize; ++i)
                putc(prop_value[i], output);
			break;
        }
	}

    int c;
	while ((c = getc(input)) != EOF)
    {
       putc(c, output);
    }

    fseek (input, 0, SEEK_SET);
    fread (frame.buffer, sizeof(byte), 10, input);
    *(frame.buffer + 9) = newTitle % 256;
    *(frame.buffer + 8) = newTitle / 256 % 256;
    *(frame.buffer + 7) = newTitle / 256 / 256 % 256;
    *(frame.buffer + 6) = newTitle / 256 / 256 % 256;
    fseek (output, 0, SEEK_SET);
    fwrite (frame.buffer, sizeof(byte), 10, output);


    fclose (output);
    fclose (input);

    input = fopen ("output.mp3", "rb");
    output = fopen(inputFileName, "wb");
    while ((c = getc(input)) != EOF)
            putc(c, output);
    fclose(input);
    fclose(output);
}

int main(int argc, char* argv[])
{
    FRAME frame;
    int flag = 0;
    char *inputFileName = "input.mp3";
    char* prop_name;
	char* prop_value;
    //printf ("%d %d", frame.buffer);
    //show (inputFileName);
    //get (inputFileName, "TIT2");
    //set (inputFileName, "TIT2", "lirooooooooooooooooooy");

    for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--show") == 0) {
			show(inputFileName);
			continue;
		}
		if (argv[i][2] == 'c')
		{
			if (argv[i][7] == "T")
                flag = 1;
		}
		if (argv[i][2] == 'g') {
			prop_name = strpbrk(argv[i], "=") + 1;
			get(inputFileName, prop_name);
			continue;
		}
		if (argv[i][2] == 's') {
			prop_name = strpbrk(argv[i], "=") + 1;
			continue;
		}
		if (argv[i][2] == 'v') {
			prop_value = strpbrk(argv[i], "=") + 1;
			set(inputFileName, prop_name, prop_value, flag);
			continue;
		}
	}
}
