#ifndef RESERVATIONS_H_INCLUDED
#define RESERVATIONS_H_INCLUDED
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "input.h"
#include "rooms.h"

typedef struct
{
    char first[30];
    char last[30];
} name;

typedef struct
{
    int reservationID;
    int roomNumber;
    char nights[10];
    char mobileNumber[30];
    char nationalID[30];
    char status[50];
    char customerName[50];
    char email[50];
    char checkInDate[20];
} Reservation;

int IS_UNIQUE(int id)
{
    FILE *resh;
    resh=fopen("Reservation.txt","r");
    if(resh==NULL)
    {
        printf("error for opening the file");
        exit(1);
    }
    char temp[200];
    char *token;
    while(!feof(resh))
    {
        fgets(temp,200,resh);
        token=strtok(temp,",");
        if(atoi(token)==id) return 0;
    }
    fclose(resh);
    return 1;
}
int generateID()
{
    int ID;
    do
    {
        srand(time(NULL));
        ID=100000+(rand()%900000);
    }
    while(IS_UNIQUE(ID)==0);
    return ID;
}

Reservation reservations[250];

int reservationCount = 0;

void loadReservations()
{
    char line[250];
    FILE* resh = fopen("Reservation.txt", "r");
    if (resh == NULL)
    {
        printf("Error opening the file\n");
        exit(1);
    }
    reservationCount=0;
    while (fgets(line, sizeof(line), resh))
    {
        if (strlen(line) == 1 || line[0] == '\n')
        {
            continue;
        }
        char* token = strtok(line, ",");
        if (token != NULL) reservations[reservationCount].reservationID = atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL) reservations[reservationCount].roomNumber = atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(reservations[reservationCount].status, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(reservations[reservationCount].customerName, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(reservations[reservationCount].nationalID, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(reservations[reservationCount].nights, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(reservations[reservationCount].checkInDate, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(reservations[reservationCount].email, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            int n=strlen(token);
            if(token[n-1]=='\n') token[n-1]='\0';
            strcpy(reservations[reservationCount].mobileNumber, token);
        }
        reservationCount++;
    }
    fclose(resh);
}

void savereservation(char *line)
{
    FILE *addh;
    addh=fopen("Reservation.txt","a");
    if(addh==NULL)
    {
        printf("error for opening the file");
        exit(1);
    }
    fputs(line,addh);
    fclose(addh);
}

void saveEdit()
{
    char line[250];
    int i,len;
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
        snprintf(line,250,"\n%d,%d,%s,%s,%s,%s,%s,%s,%s",reservations[i].reservationID,reservations[i].roomNumber,reservations[i].status,
                 reservations[i].customerName,reservations[i].nationalID,reservations[i].nights,reservations[i].checkInDate,reservations[i].email,reservations[i].mobileNumber);
        fputs(line,sh);
    }
    fclose(sh);
}

#endif // RESERVATIONS_H_INCLUDED
