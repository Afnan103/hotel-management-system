#ifndef SORT_RES_BY_DATE_H_INCLUDED
#define SORT_RES_BY_DATE_H_INCLUDED
#include "reservations.h"

typedef struct
{
    char day[10];
    char month[10];
    char year[10];
} date;

date dates[250];

int storeddates=0;

void dividedate()
{
    char line[100];
    char copy[20];
    FILE *fdate = fopen("Reservation.txt","r");
    if(fdate== NULL)
    {
        printf("error opening file");
        exit(1);
    }
    storeddates=0;
    while (fgets(line, sizeof(line), fdate))
    {
        if (strlen(line) == 1 || line[0] == '\n')
        {
            continue;
        }
        strcpy(copy,reservations[storeddates].checkInDate);
        char *token = strtok(copy,"-");
        if (token != NULL)
        {
            strcpy(dates[storeddates].day,token);
        }
        token = strtok(NULL, "-");
        if (token != NULL)
        {
            strcpy(dates[storeddates].month,token);
        }
        token = strtok(NULL, "-");
        if (token != NULL)
        {
            strcpy(dates[storeddates].year,token);
        }
        storeddates++;
    }
    fclose(fdate);
}

void sortbydate()
{
    loadReservations();
    int numberofres=reservationCount;
    int i,j;
    Reservation temp;
    for(i=0; i<numberofres-1; i++) //(numberofres-1) 3lashan howa bycompare kol element beli ba3do w a5er element mafish ba3do 7aga(msh m7tag ybos 3la a5er element w howa by3ml sort).
    {
        dividedate(reservations[i].checkInDate,i);
        for(j=0; j<numberofres-1; j++)
        {
            if(atoi(dates[j].year)>atoi(dates[j+1].year))
            {
                temp=reservations[j];
                reservations[j]=reservations[j+1];
                reservations[j+1]=temp;
            }
            else if((atoi(dates[j].year)==atoi(dates[j+1].year))&&(atoi(dates[j].month)>atoi(dates[j+1].month)))
            {
                temp=reservations[j];
                reservations[j]=reservations[j+1];
                reservations[j+1]=temp;
            }
            else if((atoi(dates[j].year)==atoi(dates[j+1].year))&&(atoi(dates[j].month)==atoi(dates[j+1].month))&&(atoi(dates[j].day)>atoi(dates[j+1].day)))
            {
                temp=reservations[j];
                reservations[j]=reservations[j+1];
                reservations[j+1]=temp;
            }
        }
    }
    char line[250];
    int len;
    len=reservationCount;
    FILE *sh;
    sh=fopen("Reservation.txt","w");
    if (sh == NULL)
    {
        printf("Error opening the file\n");
        exit(1);
    }
    for(i=0; i<len; i++)
    {
        snprintf(line,250,"%d,%d,%s,%s,%s,%s,%s,%s,%s\n",reservations[i].reservationID,reservations[i].roomNumber,reservations[i].status,
                 reservations[i].customerName,reservations[i].nationalID,reservations[i].nights,reservations[i].checkInDate,reservations[i].email,reservations[i].mobileNumber);
        fputs(line,sh);
    }
    fclose(sh);
}

#endif // SORT_RES_BY_DATE_H_INCLUDED
