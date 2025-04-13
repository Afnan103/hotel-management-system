#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <string.h>

int checkthepass(char *line,char *n,char *pa)
{
    int i=1,j=1;
    char *p;
    p=strtok(line," ");
    i=strcmp(p,n);
    p=strtok(NULL,"\n");
    j=strcmp(p,pa);
    if(i==0&&j==0)
        return 1;
    else
        return 0;
}

int loginsystem()
{
    putColor(4);
    int flag=1,kk;
    char input[100];
    while(1)
    {
        char username[50],password[50],line[101];
        while(1)
        {
            flag=1;
            printf("enter the username with no space please\n");
            readstring(username,50);
            if(username[0]=='\0')
            {
                printf("you entered nothing!!!!\n");
                continue;
            }
            for(int i=0; username[i]!='\0'; i++)
                if(username[i]==' ')
                {
                    printf("it must has no space please\n");
                    flag=0;
                }
            if(flag==1)
                break;
            //while(getchar()!='\n');
        }
        while(1)
        {
            flag=1;
            printf("enter the password with no space please\n");
            //while(getchar()!='\n');
            readstring(password,50);
            if(password[0]=='\0')
            {
                printf("you entered nothing!!!!\n");
                continue;
            }
            for(int i=0; password[i]!='\0'; i++)
                if(password[i]==' ')
                {
                    printf("it must has no space please\n");
                    flag=0;
                }
            if(flag==1)
                break;
            //while(getchar()!='\n');
        }
        FILE *user;
        user=fopen("users.txt","r");
        if(user==NULL)
        {
            printf("some wrong with users file");
            return 0;
        }
        while(fgets(line,100,user)!=NULL)
        {
            if(checkthepass(line,username,password)==1)
            {
                return 1;
            }
        }
        printf("wrong inputs\n");
        putColor(7);
        printf("if you want to exit send 0 and if you want to enter new inputs send 1\n");
        putColor(4);
        while(1)
        {
            fgets(input, sizeof(input), stdin);
            if(input[0]=='\n')
            {
                printf("pleas enter valid input and not enter a space at first\n");
                continue;
            }
            input[strcspn(input, "\n")] = '\0';
            if (isValidNumber(input))
            {
                kk = atoi(input);
            }
            else
            {
                printf("wrong input.please enter a 1 or 0\n");
                continue;
            }
            if(kk==0)
                return 0;
            else if(kk==1)
                break;
            else
            {
                printf("please enter 1 or 0 not something else\n");
            }
        }


    }
}

#endif // LOGIN_H_INCLUDED
