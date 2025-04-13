#include <ctype.h>
#include <string.h>
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

int isValidNumber(const char *str)
{
    if (str == NULL || *str == '\n')
    {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            break;
        }
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+')
        {
            return 0;
        }
    }
    return 1;
}

void readstring(char rr[],int n)
{
    char p;
    int i=0;
    p=getchar();
    while(p!='\n'&&i<n-1)
    {
        rr[i++]=p;
        p=getchar();
    }
    rr[i]='\0';
}

void readInt(int *choice)
{
     putColor(13);
    while(1)
    {
        char input[100];
        fflush(stdin);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (isValidNumber(input))
        {
            *choice = atoi(input);
            break;
        }
        else
        {
            putColor(4);
            printf("Invalid input. Try again. \n");
            continue;
        }
    }
}

int is_all_letters(char *name)
{
    int i;
    for(i=0; name[i]!='\0'; i++)
    {
        if(isalpha(name[i])==0) return 0;
    }
    return 1;
}
int is_all_digits(char *num)
{
    int i;
    for(i=0; num[i]!='\0'; i++)
    {
        if(isdigit(num[i])==0) return 0;
    }
    return 1;
}

int is_leap(int year)
{
    if((year%4==0&&year%100!=0)||(year%400==0)) return 1;
    return 0;
}
int email_valid(char *email)
{
     putColor(2);
    int n=strlen(email),i;
    int a,count=0,count2=0;
    for(i=0; i<n; i++)
    {
        if(email[i]==' ') return 0;
        if(email[i]=='@')
        {
            a=i;
            count++;
        }
    }
    if(a==0||a==(n-1)||count!=1) return 0;
    if(email[a+1]==' ') return 0;
    if(email[a+1]=='.') return 0;
    for(i=(n-1); i>a; i--)
    {
        if(email[i]=='.') count2++;
    }
    if(count2==0) return 0;
    if(email[n-2]=='.'||email[n-1]=='.') return 0;
    return 1;
}

void removeTrailingNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

#endif // INPUT_H_INCLUDED
