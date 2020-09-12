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

int convert (int n, int t)
{
    int k = 0;
    int ans = 0;
    while (n != t)
    {
        ans = ans * 2 + n % 2;
        n /= 2;
        k++;
    }
    if (t) ans += pow(2, k);
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


int main()
{
    char* dict = (char*)malloc(256 * sizeof(char));
    int set[256];
    for (int i = 0; i < 256; ++i)
        set[i] = 0;
    //int setsize = 0;

    char *inputfilename = "input.txt", *outputfilename = "output.txt", c;

    FILE* inputfile;
    FILE* outputfile;

    struct Node** tree = (struct Node**)malloc(256 * sizeof(struct Node*));

    int frequency[256];
    for (int i = 20; i < 256; ++i)
        frequency[i] = 0;

    if ((inputfile = fopen(inputfilename, "rb")) == NULL)
    {
        printf ("Enter correct filename to read!\n");
        return 0;
    }
    outputfile = fopen(outputfilename, "wb");

    while((c = fgetc(inputfile)) != EOF)
    {
		frequency[(unsigned char)c]++;
	}

    int k = 0;
	for (int i = 20; i < 256; ++i)
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

    int size_of_pair_mas = 0;

    while (k != 1)
    {
        tree[k-2] = join(tree[k - 2], tree[k - 1]);
        k--;
        bubble_sort (tree, k);
    }

    void next (struct Node* vertex, int t)
    {
        if (vertex->right == NULL)
        {
            dict[(int)vertex->c] = t;
            printf("%c %d %d\n", vertex->c, dict[(int)vertex->c], (int)vertex->c);
            set[t] = (int)vertex->c;
            size_of_pair_mas++;
            return;
        }
        next (vertex->right, t * 2 + 1);
        next (vertex->left, t * 2);
    }

    next(tree[0], 1);

    fseek (inputfile, 0, SEEK_SET);

    int count = 0, number = 1, overall = 0;
    char* str = (char*)malloc(8 * sizeof(char));
    strcpy(str, "");

    while((c = fgetc(inputfile)) != EOF)
    {
        int x = convert(dict[c], 1);
        //printf ("%d", x);
        while (x != 1)
        {
            if (x % 2 == 1)
                strcat(str, "1");
            else
                strcat(str, "0");
            x = x >> 1;
            count += 1;
            overall += 1;
            if (count == 8)
            {
                int sum = 0;
                for (int i = 0; i < 8; ++i)
                    sum += (str[i] - '0') * pow(2, 7 - i);
                printf ("%s\n", str);
                fprintf (outputfile, "%c", (char)sum);
                count = 0;
                //printf ("%s\n", str);
                strcpy(str, "");
            }
        }
        //printf("%d\n", x);
	}

	for (int i = 0; i < 256; ++i)
    {
        if (set[i]) printf ("%d\n", i);
    }

    fprintf (outputfile, "%d", overall);

    fclose(inputfile);
    fclose(outputfile);

    char *filenametoopen = "output.txt";
    FILE* openfile;

    openfile = fopen (filenametoopen, "rb");
    int t = 1;
    char* ans[256];
    strcpy (ans, "");
    while((c = fgetc(inputfile)) != EOF)
    {
		int x = (unsigned char)c;
		//printf("%d|\n", x);
		x = convert(x, 0);
		//printf("%d|\n", x);
		for (int i = 0; i < 8; ++i)
        {
            t = t*2 + x%2;
            x /= 2;
            if (set[t]!=0)
            {
                char* ch[1];
                ch[0] = (char)set[t];
                strcat (ans, ch);
                t = 1;
            }
        }
	}
	printf("%s\n", ans);

}
