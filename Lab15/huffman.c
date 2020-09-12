#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    int a;
    char *c;
    //c = (char*)malloc(256 * sizeof(char));
    struct Node *left, *right;
};

void out(struct Node *t)
{
    printf("%d %c\n",t->a,t->c);
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
    char** dict = (char**)malloc(256 * sizeof(char*));

    char* filename   = "input.txt", c;

    FILE* inputfile;

    struct Node** tree = (struct Node**)malloc(256 * sizeof(struct Node*));

    int frequency[256];
    for (int i = 20; i < 256; ++i)
        frequency[i] = 0;

    if ((inputfile = fopen(filename, "rb")) == NULL)
    {
        printf ("Enter correct filename to read!\n");
        return 0;
    }

    while((c = fgetc(inputfile)) != EOF)
    {
		frequency[(unsigned char)c]++;
	}

    int k = 0;
	for (int i = 20; i < 256; ++i)
    {
        //printf ("%d %d\n",i,frequency[i]);
        if (frequency[i] != 0)
        {
            //printf ("%c %d\n",i,frequency[i]);
            struct Node *p = (struct Node*)malloc(sizeof(struct Node));
            p->c = (unsigned char)i;
            p->a = frequency[i];
            p->right = NULL;
            tree[k] = p;
            //printf ("%c %d\n",tree[k]->c, tree[k]->a);
            k++;
        }
    }

    void next (struct Node* vertex, int t)
    {
        if (vertex->right == NULL)
        {
            printf("%c %d\n", vertex->c, t);
            dict[(int)vertex->c] = t;
            return;
        }
        next (vertex->right, t * 2 + 1);
        next (vertex->left, t * 2);
    }

    bubble_sort (tree, k);
    //printf ("lol");

    for (int i = 0; i < k; ++i)
    {
        out(tree[i]);
    }


    while (k != 1)
    {
        tree[k-2] = join(tree[k - 2], tree[k - 1]);
        k--;
        bubble_sort (tree, k);
    }

    next(tree[0], 1);
    //out(tree[0]);
}
