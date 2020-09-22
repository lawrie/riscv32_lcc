#include<stdio.h>
#include<stdlib.h>

int main()
{
    int ch;
    FILE *fp;
    fp = fopen("myfile.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    printf("Press Ctrl+Z in DOS and Ctrl+D\n\
    in Linux to stop reading more characters\n\n");

    printf("Enter text: ");

    while( (ch=getchar()) != EOF )
    {
        fputc(ch, fp);
    }

    fclose(fp);

    return 0;

}

