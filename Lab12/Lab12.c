#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    FILE *fp;
    char str[128];
    if ((fp=fopen(argv[1], "r") )==NULL)
    {
        printf("Cannot open file.\n");
        return 0;
    }
    while(!feof (fp))
    {
        if (fgets(str, 126, fp))
            printf("%s", str);
    }
        fclose(fp);
    return 0;
}
