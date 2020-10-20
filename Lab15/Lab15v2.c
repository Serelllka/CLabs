
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node
{
    int a;
    char *c;
    struct Node *left, *right;
};

int reverse (int x)
{
    int ans = 0;
    for (int i = 0; i < 8; ++i)
    {
        ans = ans * 2 + x % 2;
        //ans = ans * 2 + x % 2;
        x /= 2;
    }
    return ans;
}

int convert (int n)
{
    int k = 0, ans = 0;
    while (n != 1)
    {
        ans = ans * 2 + n % 2;
        n /= 2;
        k++;
    }
    ans += pow(2, k);
    return ans;
}

void bubble_sort(struct Node **mas, int n)
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

void Extract(char* archiveName)
{
    FILE* archive = fopen(archiveName, "rb+wb");
    unsigned long long int  now_position = 0;
    unsigned long long int  start_position = 0;
    unsigned long long int  filesize;
    char filename[128];
    int c;
    while ((c = getc(archive)) != EOF)
    {
        start_position++;
        if (c == '\n')
	        break;
    }
    fseek(archive, 0, SEEK_SET);
    FILE *file;
    while (fscanf(archive, "< %s : %llu >", filename, &filesize) != 0)
    {
        file = fopen(filename, "wb");
        if (file == NULL)
			break;
        now_position = ftell(archive);
        fseek(archive, start_position, SEEK_SET);
        start_position += filesize;
        while (filesize-- > 0)
        {
            putc((c = getc(archive)), file);
        }
        fseek(archive, now_position, SEEK_SET);
        fclose(file);
    }
}

void List(char* archiveName)
{
    FILE* archive = fopen(archiveName, "rb");
    char filename[128] = {0};
    unsigned long long int  filesize;
    printf("File list:\n");
    while (fscanf(archive, "< %s : %llu >", filename, &filesize) != 0)
    {
        printf("%s\n", filename);
    }
    fclose(archive);
}

void Compression (char* inputFileName, char* outputFileName)
{
    FILE* inputFile = fopen (inputFileName, "rb");
    FILE* outputFile = fopen (outputFileName, "wb");

    int* dict = (int*)malloc(10000 * sizeof(int));
    int frequency[10000];
    for (int i = 0; i < 10000; ++i)
        frequency[i] = 0;
    int c;

    struct Node** tree = (struct Node**)malloc(10000 * sizeof(struct Node*));

    while((c = getc(inputFile)) != EOF)
		frequency[(unsigned char)c]++;

    int k = 0;
	for (int i = 0; i < 10000; ++i)
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

    void next(struct Node* vertex, int t)
    {
        if (vertex->right == NULL)
        {
            dict[(int)vertex->c] = t;
            return;
        }
        next (vertex->right, t * 2 + 1);
        next (vertex->left, t * 2);
    }

    next(tree[0], 1);

    fseek (inputFile, 0, SEEK_SET);

    putc (countOfLiters, outputFile);
    for (int i = 0; i < 256; ++i)
    {

        if (frequency[i] != 0)
        {
            putc (i, outputFile);
            putc (dict[i] / 256, outputFile);
            putc (dict[i] % 256, outputFile);
        }
    }

    int sum = 0, count = 0;
    while((c = getc(inputFile)) != EOF)
    {
        int x = convert(dict[c]);
        //printf ("%d\n", x);
        while (x != 1)
        {
            sum += (x % 2) * pow(2, 7 - count);
            x = x >> 1;
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
        putc ((char)sum, outputFile);
    }

	putc (8 - count, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    printf("Compressed\n");
    return;
}

void Decoding (char* archiveName, char* fileNameToDecode)
{
    printf ("%s\n", archiveName);
    FILE* archive = fopen (archiveName, "rb");
    FILE* decodedFile = fopen (fileNameToDecode, "wb");
    int dictionary[100000];
    for (int i = 0; i < 100000; ++i)
        dictionary[i] = 0;
    char* ans[256];
    strcpy (ans, "");
    int n = fgetc(archive);
    for (int i = 0; i < n; ++i)
    {
        int x = getc (archive);
        int y = getc (archive);
        int z = getc (archive);
        dictionary[y * 256 + z] = x;
    }
    int ft[2], t = 1;
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
            t = t*2 + x%2;
            x /= 2;
            if (dictionary[t] != 0)
            {
                char* ch[1];
                ch[0] = (char*)dictionary[t];
                putc (dictionary[t], decodedFile);
                t = 1;
            }
        }
	}

    int x = (unsigned char)ft[0];
    x = reverse(x);
	for (int i = 0; i < 8 - (ft[1] % 8); ++i)
        {
            t = t*2 + x%2;
            x /= 2;
            if (dictionary[t] != 0)
            {
                char* ch[1];
                ch[0] = (char*)dictionary[t];
                putc (dictionary[t], decodedFile);
                t = 1;
            }
        }
    printf("Decoded\n");
    fclose (archive);
    fclose (decodedFile);
    return;
}

int main(int argc, char* argv[])
{
    char *archiveName = "data.arc",
        *fileNameToDecode = "util/output.af",
        *companationFileName = "util/companation.af";

    /**
    Compression (companationFileName, archiveName);
    Decoding (archiveName, fileNameToDecode);
    **/

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
