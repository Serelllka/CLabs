#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NumberOfNeighbors (int **generation, int n, int m, int x, int y)
{
    int k = 0;
    k += generation[(x - 1 + n) % n][(y + 1 + m) % m];
    k += generation[(x - 1 + n) % n][(y - 1 + m) % m];
    k += generation[(x + 1 + n) % n][(y - 1 + m) % m];
    k += generation[(x + 1 + n) % n][(y + 1 + m) % m];
    k += generation[(x - 1 + n) % n][y];
    k += generation[(x + 1 + n) % n][y];
    k += generation[x][(y - 1 + m) % m];
    k += generation[x][(y + 1 + m) % m];

    return k;
}

void NextGeneration (int **generation, int n, int m)
{
    int matr[n][m];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int k = NumberOfNeighbors(generation, n, m, i, j);
            matr[i][j] = generation[i][j];
            if (k == 3) matr[i][j] = 1;
            if (k != 2 && k != 3) matr[i][j] = 0;
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            generation[i][j] = matr[i][j];


}

void toImage (int **generation, int n, int m, char* output, char header[54])
{
    FILE *outputfile;
    outputfile = fopen (output, "w");
    for (int i = 0; i < 54; ++i)
        fprintf(outputfile, "%c", header[i]);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (generation[i][j] == 0)
                fprintf(outputfile, "%c%c%c", -1, -1, -1);
            if (generation[i][j] == 1)
                fprintf(outputfile, "%c%c%c", 0, 0, 0);

        }
    }
    fclose (outputfile);

}

int main(int argc, char* argv[])
{
    FILE *inputfile;
    char filename[256], header[256];
    char* dirname = "out";
    int height, width, countofgenerations = 100, dumpfreq = 1;

    for(int i = 0; i < argc; i++)
    {
        if(!strcmp("--input", argv[i]))
        {
            while ((inputfile = fopen(argv[i + 1], "r")) == NULL)
            {
                printf ("Enter correct filename to read!\n");
                return 0;
            }
        }

        if(!strcmp("--max_iter", argv[i]))
            countofgenerations = strtol(argv[i + 1], 0, 10);

        if(!strcmp("--output", argv[i]))
        {
            dirname = argv[i + 1];
            mkdir(dirname);
        }

        if(!strcmp("--dump_freq", argv[i]))
            dumpfreq = strtol(argv[i + 1], 0, 10);
    }

    /**
    while ((inputfile = fopen(filename, "r")) == NULL)
        scanf ("%s", filename );
    **/

    fread (header, 1, 54, inputfile);

    width = header[18] + header[19] * 256 + header[20] * 256 * 256 + header[21] * 256 * 256 * 256;
    height = header[22] + header[23] * 256 + header[24] * 256 * 256 + header[25] * 256 * 256 * 256;

    int** generation = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; ++i)
        generation[i] = (int*)malloc(width * sizeof(int));

    for (int i = width - 1; i >= 0; --i)
    {
        for (int j = 0; j < height; ++j)
        {
            char rgb[3];
            fread (rgb, 1, 3, inputfile);
            if (rgb[0] == -1)
                generation[i][j] = 0;
            else
                generation[i][j] = 1;
        }
    }


    for (int i = 0; i < countofgenerations; ++i)
    {
        NextGeneration(generation, height, width);
        char outputname[40];
        strcpy (outputname, dirname);
        strcat(strcat(outputname, "\\"), strcat(itoa(i, filename, 10), ".bmp"));
        if (i % dumpfreq == 0)
            toImage (generation, height, width, outputname, header);
    }

    fclose (inputfile);
    fee(generation);
}
