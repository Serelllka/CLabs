#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node //Contains a tree node that contains links to two ancestors
{
    int a;
    unsigned char c;
    struct Node *left, *right;
};

int reverse (int x) //Returns the number mirrored inn binary
{
    int ans = 0;
    for (int i = 0; i < 8; ++i)
    {
        ans = ans * 2 + x % 2;
        x /= 2;
    }
    return ans;
}

void bubble_sort(struct Node **mas, int n) // bubble_sort for special struct
{
    int f = 1;
    while (f)
    {
        f = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            if (mas[i]->a < mas[i + 1]->a)
            {
                struct Node* c = (struct Node*)malloc(sizeof(struct Node));
                c = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = c;
                f = 1;
            }
        }
    }
}

void toch (int x, char* str, int k, int p) // the first bits
{
    for (int i = 0; i < p; ++i)
    {
        str[k + p - 1 - i] = x % 2 + '0';
        x /= 2;
    }
    str[k + p] = '\0';
}

struct Node* join (struct Node* left, struct Node* right)
{
    struct Node* c = (struct Node*)malloc(sizeof(struct Node));
    c->right = right;
    c->left = left;
    c->a = right->a + left->a;
    c->c = -1;
    return c;
};

void Create(char* archiveName, int filecount, char* files[], const int iterator)
{
    int i;
    int temp;
    FILE* archive = fopen(archiveName, "wb");
    FILE* file;
    unsigned long long int nameandsize[128];
    for (i = iterator; i < filecount; i++)
    {
        file = fopen(files[i], "rb");
        if (file == NULL)
            continue;
        fseek(file, 0, SEEK_END);
        nameandsize[i - iterator] = ftell(file);
        fseek(file, 0, SEEK_SET);
        fclose(file);
    }
    for (i = 0; i < filecount - iterator; i++)
    {
        fprintf(archive, "< %s : %llu >", files[i + iterator], nameandsize[i]);
    }
    fprintf(archive, "\n");
    for (i = iterator; i < filecount; i++)
    {
        file = fopen(files[i], "rb");
        while ((temp = getc(file)) != EOF)
            putc(temp, archive);
        fclose(file);
    }
    fclose (archive);

}

void Extract(char* archive){
    FILE* arch = fopen(archive, "rb+wb");
    unsigned long long int  now_position = 0;
    unsigned long long int  start_position = 0;
    int c;
    while ((c = getc(arch)) != EOF) {
        start_position++;
        if (c == '\n')
	        break;
    }
    fseek(arch, 0, SEEK_SET);
    char filename[128] = {0};
    unsigned long long int  filesize;
    FILE *file;
    while (fscanf(arch, "< %s : %llu >", filename, &filesize) != 0) {
        file = fopen(filename, "wb");
        if (file == NULL)
			break;
        now_position = ftell(arch);
        fseek(arch, start_position, SEEK_SET);
        start_position += filesize;
        while (filesize-- > 0)
            putc((c = getc(arch)), file);
        fseek(arch, now_position, SEEK_SET);
        fclose(file);
    }
	printf("\n + Unzipping sucssess + \n");
}

void List(char* archiveName)
{
    FILE* archive = fopen(archiveName, "rb");
    char filename[256] = {0};
    unsigned long long size;
    printf("Files:\n");
    while (fscanf(archive, "< %s : %llu >", filename, &size) != 0)
    {
        printf("%s\n", filename);
    }
    fclose(archive);
}

void Compression (char* inputFileName, char* outputFileName)
{
    FILE* inputFile = fopen (inputFileName, "rb");
    FILE* outputFile = fopen (outputFileName, "wb");

    char** dict = (char**)malloc(256 * sizeof(char*));
    for (int i = 0; i < 256; ++i)
        dict[i] = (char*)malloc(256 * sizeof(char));
    int* frequency = (int*)calloc(256, sizeof(int));

    int c, i, k = 0;

    struct Node** tree = (struct Node**)malloc(256 * sizeof(struct Node*));

    while((c = getc(inputFile)) != EOF)
		frequency[(unsigned char)c]++;

	for (i = 0; i < 256; ++i)
    {
        if (frequency[i] != 0)
        {
            struct Node *p = (struct Node*)malloc(sizeof(struct Node));
            p->c = (unsigned char)i;
            p->a = frequency[i];
            p->right = NULL;
            tree[k] = p;
            k++;
        }
    }

    int countOfLiters = k;
    bubble_sort (tree, k);

    while (k != 1)
    {
        bubble_sort (tree, k);
        tree[k-2] = join(tree[k - 2], tree[k - 1]);
        k--;
    }

    char* string = (char*)calloc(256, sizeof(char));
    int strSize = 0;

    void next(struct Node* vertex, char* string, int strSize)
    {
        if (vertex->right == NULL)
        {
            strcpy(dict[(int)vertex->c], string);
            return;
        }
        string[strSize + 1] = '\0';
        string[strSize] = '1';
        next (vertex->right, string, strSize + 1);
        string[strSize] = '0';
        next (vertex->left, string, strSize + 1);
    }

    next(tree[0], string, strSize);

    fseek (inputFile, 0, SEEK_SET);

    putc (countOfLiters - 1, outputFile);

    for (i = 0; i < 256; ++i)
    {

        if (frequency[i] != 0)
        {
            int count = 0, t = 0;
            putc (i, outputFile);
            int n = strlen(dict[i]);
            putc (n, outputFile);
            for (int j = 0; j < n; ++j)
            {
                t = t * 2 + (dict[i][j] == '0' ? 0 : 1);
                count++;
                if (count == 8)
                {
                    count = 0;
                    putc (t, outputFile);
                    t = 0;
                }
            }
            if (count != 0)
            {
                putc (t, outputFile);
            }
        }
    }
    // Writing alphabet completed


    int sum = 0, count = 0;
    while((c = getc(inputFile)) != EOF)
    {
        for (i = 0; dict[c][i] != '\0'; ++i)
        {
            sum = sum * 2 + (dict[c][i] - '0');
            count += 1;
            if (count == 8)
            {
                putc ((char)sum, outputFile);
                count = 0;
                sum = 0;
            }
        }
	}

    if (count != 0)
    {
        putc ((char)sum << (8 - count), outputFile);
    }

	putc (8 - count, outputFile);


	//-- Compressed! --//
	for (i = 0; i < 256; ++i)
        free(dict[i]);
	free(dict);
    fclose(inputFile);
    fclose(outputFile);
    printf("Compressed\n");
    return;
}

void Decoding (char* archiveName, char* fileNameToDecode)
{
    FILE* archive = fopen (archiveName, "rb");
    FILE* decodedFile = fopen (fileNameToDecode, "wb");
    unsigned char** dict = (unsigned char**)malloc(256 * sizeof(unsigned char*));
    for (int i = 0; i < 256; ++i)
        dict[i] = (unsigned char*)malloc(256 + sizeof(char));
    int n = fgetc(archive);
    n += 1;
    //printf ("--%d", n);
    //reading the alphabet
    for (int i = 0; i < n; ++i)
    {
        int x = getc (archive);
        int y = getc (archive);
        for (int j = 0; j < y / 8; ++j)
        {
            int a = getc (archive);
            toch (a, dict[x], 8 * j, 8);
        }
        if (y % 8 != 0)
        {
            int a = getc (archive);
            toch (a, dict[x], y / 8 * 8, y % 8);
        }
        //  printf ("%c- -%s\n", x, dict[x]);
    }
    //reading the alphabet completed
    printf("Alphabet restored\n");

    unsigned char* str = (unsigned char*)calloc(256, sizeof(char));
    int ft[2], t = 0;
    int c = getc(archive);
    ft[1] = c;
    c = fgetc(archive);
    while(1)
    {
        ft[0] = ft[1];
        ft[1] = c;
        c = getc(archive);
        if (c == EOF) break;
		int x = (unsigned char)ft[0];
		x = reverse(x);
		for (int i = 0; i < 8; ++i)
        {
            str[t] = (x % 2) + '0';
            t++;
            str[t] = '\0';
            x /= 2;

            int q = 0;
            int p = 0;
            for (; p < 256; ++p)
                if (strcmp(dict[p], str) == 0)
                {
                    q = 1;
                    break;
                }

            if (q)
            {
                putc (p, decodedFile);
                t = 0;
                strcpy(str, "");
            }
        }
	}

    int x = (unsigned char)ft[0];
    x = reverse(x);
	for (int i = 0; i < 8 - (ft[1] % 8); ++i)
        {
            str[t] = (x % 2) + '0';
            t++;
            str[t] = '\0';
            x /= 2;

            int p = 0;
            for (; p < 256; ++p)
                if (strcmp(dict[p], str) == 0)
                {
                    putc (p, decodedFile);
                    t = 0;
                }
        }
    printf("Decoded\n");

    //-- Decoded! --//
    fclose (archive);
    fclose (decodedFile);
    return;
}

int main(int argc, char* argv[])
{
    char *archiveName = "data.arc",
        *fileNameToDecode = "util/fileToDecode.of",
        *companationFileName = "util/fileToCompress.txt";

    //Compression (companationFileName, archiveName);
    Decoding (archiveName, fileNameToDecode);
    Extract(fileNameToDecode);

    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp("--file", argv[i]))
        {
            archiveName = argv[i + 1];
        }
        if (!strcmp("--create", argv[i]))
        {
            Create (companationFileName, argc, argv, i + 1);
            Compression (companationFileName, archiveName);
        }
        if(!strcmp("--extract", argv[i]))
        {
            Decoding (archiveName, fileNameToDecode);
            Extract(fileNameToDecode);
        }
        if(!strcmp("--list", argv[i]))
        {
            Decoding (archiveName, fileNameToDecode);
            List(fileNameToDecode);
        }
    }

    return 0;
}
