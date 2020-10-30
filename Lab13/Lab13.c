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
	fread(frame.buffer, sizeof(char), 10, input);

	long long title = *(frame.buffer + 9) + *(frame.buffer + 8) * 256 + *(frame.buffer + 7) * 256 * 256 + *(frame.buffer + 6) * 256 * 256 * 256;

	while (ftell(input) < title + 10)
	{
		fread(frame.buffer, sizeof(char), 10, input);

		unsigned int size = *(frame.buffer + 7) + *(frame.buffer + 6) * 256 + *(frame.buffer + 5) * 256 * 256 + *(frame.buffer + 4) * 256 * 256 * 256;

        int f = 1;
        for (int i = 0; i < 4; ++i)
            if (prop_name[i] != *(frame.buffer + i)) f = 0;

		if (f)
		{
			printf("%s: ", prop_name);

			unsigned char* frameContent;
			frameContent = malloc(sizeof(char) * size + 1);
			fread(frameContent, sizeof(char), size, input);
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

void set (char* inputFileName, char prop_name[4], char* prop_value)
{
    FILE* input = fopen(inputFileName, "rb");
    FILE* output = fopen("output.txt", "wb");

    FRAME frame;

    fread (frame.buffer, sizeof(byte), 10, input);
    fwrite (frame.buffer, sizeof(byte), 10, output);

    long long title = *(frame.buffer + 9) + *(frame.buffer + 8) * 256 + *(frame.buffer + 7) * 256 * 256 + *(frame.buffer + 6) * 256 * 256 * 256;

    unsigned int framePos = 0;
    unsigned int frameSize = 0;

    while (ftell(input) < title + 10)
	{
		fread(frame.buffer, sizeof(char), 10, input);
		//unsigned int size = *(frame.buffer + 7) + *(frame.buffer + 6) * 256 + *(frame.buffer + 5) * 256 * 256 + *(frame.buffer + 4) * 256 * 256 * 256;

        int f = 1;
        for (int i = 0; i < 4; ++i)
            if (prop_name[i] != *(frame.buffer + i)) f = 0;

		if (f)
		{
		    framePos = ftell(input) - 10;
		    frameSize = *(frame.buffer + 7) + *(frame.buffer + 6) * 256 + *(frame.buffer + 5) * 256 * 256 + *(frame.buffer + 4) * 256 * 256 * 256;
		    break;
		}

		fseek(input, size, SEEK_CUR);
	}

    title = title - frameSize + strlen(prop_value) + 10;
    if (!framePos)
    {
        title -= 10;
        framePos = ftell(input) - 10;
    }

    fseek (input, 0, SEEK_SET);
    fseek (output, 0, SEEK_SET);
    copyFile (input, output);

    for (int i = 0; i < 4; ++i)
        fwrite("%c", *(frame.buffer + i));

}

int main()
{
    FRAME frame;
    char *inputFileName = "input.mp3";
    //printf ("%d %d", frame.buffer);
    //show (inputFileName);
    get (inputFileName, "TIT2");
    set (inputFileName)
}
