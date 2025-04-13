#ifndef CHECKIN_CHECKOUT_H_INCLUDED
#define CHECKIN_CHECKOUT_H_INCLUDED
#include "reservations.h"
#include "rooms.h"
#include "input.h"
#include <stdlib.h>
#include "print.h"

int execute_check_out(int Numroom)
{
    loadReservations();
    loadRooms();

    char line[250];
    int i;
    long int bill;

    for (i = 0; i < reservationCount; i++)
    {
        if (reservations[i].roomNumber == Numroom)
        {
            if (strcmp(reservations[i].status, "confirmed") == 0)
            {
                for (int j = 0; j < loadedRooms; j++)
                {
                    if (rooms[j].roomNumber == Numroom)
                    {
                        bill = atoi(reservations[i].nights) * rooms[j].price;
                        break;
                    }
                }
                printf("The Total Bill = %ld\n", bill);

                UpdateRoomStatus(reservations[i].roomNumber);
                for (int k= i; k< reservationCount - 1; k++)
                {
                    reservations[k] = reservations[k+ 1];
                }
                reservationCount--;

                FILE *sh = fopen("Reservation.txt", "w");
                if (sh == NULL)
                {
                    printf("Error opening the file\n");
                    exit(1);
                }
                for (int k = 0;  k< reservationCount; k++)
                {
                    snprintf(line, sizeof(line), "%d,%d,%s,%s,%s,%s,%s,%s,%s\n",
                             reservations[k].reservationID, reservations[k].roomNumber,
                             reservations[k].status, reservations[k].customerName,
                             reservations[k].nationalID, reservations[k].nights,
                             reservations[k].checkInDate, reservations[k].email,
                             reservations[k].mobileNumber);
                    fputs(line, sh);
                }
                fclose(sh);

                return 0;
            }
            else
            {
                return 2;
            }
        }
    }

    return 1;
}

void check_out()
{
     putColor(9);
    int Num ;
    while (1)
    {
        printf("Enter the Room Number(enter 0 to go back): ");
        readInt(&Num);
        if(Num==0) break;
        int res = execute_check_out(Num);
        if (res != 0)
        {
            if (res == 1)
                printf("The Room number not found.\n");
            else
                printf("This Room is unconfirmed.\n");
        }
        else
        {
            printf("Check-out has succeeded.\n");
            break;
        }
    }
}

int checkdate(int d,int m,int y,char s[])
{
    loadReservations();
    char date[20] ;
    strcpy(date,s);
    char *token;
    int day, month, year;
    token = strtok(date, "-");
    if(token!=NULL) day = atoi(token);
    token = strtok(NULL, "-");
    if(token!=NULL)  month = atoi(token);
    token = strtok(NULL, "-");
    if(token!=NULL)  year = atoi(token);
    if (year<y) return 1;
    else if (year==y&&month<m) return 1;
    else if (year==y&&month==m&&day<=d) return 1;
    else return 0;
}

int execute_check_in(int resID,int d,int m,int y)
{
    loadReservations();
    int i;
    for (i = 0; i < reservationCount; i++)
    {
        if (reservations[i].reservationID == resID || reservations[i].roomNumber == resID)
        {

            if (checkdate(d,m,y,reservations[i].checkInDate))
            {


                strcpy(reservations[i].status, "confirmed");

                FILE *f = fopen("Reservation.txt", "w");
                if (f == NULL)
                {
                    printf("Error opening the file\n");
                    exit(1);
                }

                int  j;

                for (j = 0; j < reservationCount; j++)
                {
                    fprintf(f, "%d,%d,%s,%s,%s,%s,%s,%s,%s\n",
                            reservations[j].reservationID, reservations[j].roomNumber, reservations[j].status,
                            reservations[j].customerName, reservations[j].nationalID, reservations[j].nights,
                            reservations[j].checkInDate, reservations[j].email, reservations[j].mobileNumber);

                }

                fflush(f);
                fclose(f);
                return 2;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

void check_in()
{
     putColor(9);
    time_t currtime;
    time(&currtime);
    struct tm *t = localtime(&currtime);
    int d=t->tm_mday;
    int m=t->tm_mon+1;
    int y=t->tm_year+1900;
    int ResID;
    int a=0;
    while (1)
    {
        printf("Enter the Reservation ID or room number(enter 0 to go back): ");

        readInt(&ResID);
        if(ResID==0){
            a=1;
            break;
        }
        int res = execute_check_in(ResID,d,m,y);
        if (res == 0)
        {
            printf("The Reservation ID is not correct.\n");

        }
        else break;
    }
        int res = execute_check_in(ResID,d,m,y);
        if (res == 1)
        {
            printf("Today date is before check-In date.\n");
        }
        else if(a!=1)
        {
            printf("Check-in has succeeded.\n");

        }
}

#endif // CHECKIN_CHECKOUT_H_INCLUDED
