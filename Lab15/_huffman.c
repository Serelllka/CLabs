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
        ans = ans*2 + x%2;
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

void Compression (char *inputFileName, char *outputFileName)
{
    FILE* inputFile;
    FILE* outputFile;
}

int main(int argc, char* argv[])
{
    char* dict = (char*)malloc(256 * sizeof(char));
    int set[256];
    for (int i = 0; i < 256; ++i)
        set[i] = 0;

    char *inputFileName = "input.txt",
        *outputFileName = "output.txt",
        *archiveName = "output.txt",
        *filenametodecode = "input1.txt";
    int c;

    FILE* inputFile;
    FILE* outputFile;
    FILE* archive;
    FILE* decodedFile;

    struct Node** tree = (struct Node**)malloc(256 * sizeof(struct Node*));

    int frequency[256];
    for (int i = 0; i < 256; ++i)
        frequency[i] = 0;

    //for (int i = 0; i < argc; ++i)
    //{
        if ((inputFile = fopen(inputFileName, "rb")) == NULL)
        {
            printf ("Enter correct filename to read!\n");
            return 0;
        }
    //}
    outputFile = fopen(outputFileName, "wb");

    while((c = getc(inputFile)) != EOF)
    {
		frequency[(unsigned char)c]++;
	}

    int k = 0;
	for (int i = 0; i < 256; ++i)
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
            set[t] = (int)vertex->c;
            return;
        }
        next (vertex->right, t * 2 + 1);
        next (vertex->left, t * 2);
    }

    next(tree[0], 1);

    fseek (inputFile, 0, SEEK_SET);

    int count = 0, number = 1;
    char* str = (char*)malloc(8 * sizeof(char));
    strcpy(str, "");

    while((c = getc(inputFile)) != EOF)
    {
        int x = convert(dict[c]);
        while (x != 1)
        {
            if (x % 2 == 1)
                strcat(str, "1");
            else
                strcat(str, "0");
            x = x >> 1;
            count += 1;
            if (count == 8)
            {
                int sum = 0;
                for (int i = 0; i < 8; ++i)
                    sum += (str[i] - '0') * pow(2, 7 - i);
                putc ((char)sum, outputFile);
                count = 0;
                strcpy(str, "");
            }
        }
	}

    int sum = 0;
    if (count != 0)
    {
        for (int i = 0; i < count; ++i)
            sum += (str[i] - '0') * pow(2, 7 - i);
        putc ((char)sum, outputFile);
    }

	putc (8 - count, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    archive = fopen (archiveName, "rb");
    decodedFile = fopen (filenametodecode, "wb");

    int t = 1;
    char* ans[256];
    strcpy (ans, "");
    c = getc(inputFile);
    int ft[2];
    ft[1] = c;
    c = fgetc(inputFile);
    while(1)
    {
        ft[0] = ft[1];
        ft[1] = c;
        c = getc(inputFile);
        if (c == EOF) break;
		int x = (unsigned char)ft[0];
		x = reverse(x);
		for (int i = 0; i < 8; ++i)
        {
            t = t*2 + x%2;
            x /= 2;
            if (set[t] != 0)
            {
                char* ch[1];
                ch[0] = (char*)set[t];
                strcat (ans, ch);
                putc (set[t], decodedFile);
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
            if (set[t] != 0)
            {
                char* ch[1];
                ch[0] = (char*)set[t];
                strcat (ans, ch);
                putc (set[t], decodedFile);
                t = 1;
            }
        }
}
