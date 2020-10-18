    #include<stdio.h>
    #include<math.h>
    #include<string.h>

    /**
    Lab 9
    **/

    int main()
    {
        int subscriptionFee, convLen, costPerMinute;

        printf ("Enter subscription Fee:\n");
        scanf ("%d", &subscriptionFee);
        printf ("Enter conversation length:\n");
        scanf ("%d", &convLen);
        printf ("Enter cost per minute:\n");
        scanf ("%d", &costPerMinute);
        while (costPerMinute < subscriptionFee / 499)
        {
            printf ("Enter correct cost per minute:\n");
            scanf ("%d", costPerMinute);
        }
        printf ("Your monthly bill: %d\n", subscriptionFee + (convLen - 499) * costPerMinute);
        int n;
        printf ("Enter your numeral:\n");
        scanf ("%d", &n);
        while (n > 9 || n < 0)
        {
            printf ("Enter correct numeral:\n");
            scanf ("%d", &n);
        }
        switch (n)
        {
            case 0:
                printf ("zero");
            break;
            case 1:
                printf ("one");
            break;
            case 2:
                printf ("two");
            break;
            case 3:
                printf ("three");
            break;
            case 4:
                printf ("four");
            break;
            case 5:
                printf ("five");
            break;
            case 6:
                printf ("six");
            break;
            case 7:
                printf ("seven");
            break;
            case 8:
                printf ("eight");
            break;
            case 9:
                printf ("nine");
            break;
        }
    }
