#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED

#include "reservations.h"
#include "rooms.h"
#include "print.h"

int findReservByRoom(int room)
{
    int index;
    int found = 0;
    for (int i=0; i<reservationCount; i++)
    {
        if (reservations[i].roomNumber == room)
        {
            index = i;
            found = 1;
            break;
        }
    }
    if (found)
        return index;
    else
        return -1;
}

void showRoomsByStatus(char *status)
{
    for (int i=0; i<loadedRooms; i++)
    {
        if (!strcmp(status, rooms[i].status))
        {
            printRoom(rooms[i]);
        }
    }
}

void searchByRoomStatus()
{
    putColor(8);
    printf("1. Show available rooms\n");
    printf("2. Show reserved rooms\n");
    int s;
    scanf("%d", &s);
    if (s==1)
        showRoomsByStatus("Available");
    else if (s==2)
        showRoomsByStatus("Reserved");
    else
        printf("Invalid input\n");
}

void searchByCostName()
{
    putColor(9);
    char name[50];
    printf("Enter name: ");
    fflush(stdin);
    fgets(name, 50, stdin);
    removeTrailingNewline(name);
    int found = 0;
    for (int i=0; i<reservationCount; i++)
    {
        if (!strcmp(name, reservations[i].customerName))
        {
            printReservation(reservations[i]);
            found = 1;
        }
    }
    if (!found) printf("Name not found\n");
}

void searchByRoomNum()
{
    putColor(10);
    printf("Enter room number: ");
    int roomNum;
    scanf("%d", &roomNum);
    int found = 0;
    for (int i=0; i<loadedRooms; i++)
    {
        if (roomNum==rooms[i].roomNumber)
        {
            if (!strcmp("Available", rooms[i].status))
            {
                printRoom(rooms[i]);
            }
            else
            {
                int resIndex = findReservByRoom(rooms[i].roomNumber);
                if (resIndex==-1)
                    printf("Reservation not found\n");
                else
                {
                    Reservation reservation = reservations[resIndex];
                    printRoom(rooms[i]);
                    printGuestInfo(reservation);
                }
            }
            found = 1;
        }
    }

    if (!found) printf("Room not found\n");
}

void query()
{
    putColor(11);
    loadReservations();
    loadRooms();
    printf("1. Search by costumer name\n");
    printf("2. Search by room number\n");
    printf("3. Search by room status\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        searchByCostName();
        break;
    case 2:
        searchByRoomNum();
        break;
    case 3:
        searchByRoomStatus();
        break;
    default:
        printf("Invalid input\n");
    }
}

void report_by_date()
{
    putColor(12);
    loadReservations();
    char date[20];
    printf("Enter check-in date:\n");
    int d, m, y;
    while(1)
    {
        printf("day:");
        readInt(&d);
        printf("month:");
        readInt(&m);
        printf("year:");
        readInt(&y);
        if(m<1||m>12) printf("enter a valid date.\n");
        else if(m==1||m==3||m==5||
                m==7||m==8||m==10||m==12)
        {
            if(d<1||d>31) printf("enter a valid date.\n");
            else break;
        }
        else if(m==4||m==6||m==9||m==11)
        {
            if(d<1||d>30) printf("enter a valid date.\n");
            else break;
        }
        else if(is_leap(y)&&(m==2&&(d<1||d>29))) printf("enter a valid date.\n");
        else if((is_leap(y)==0)&&(m==2&&(d<1||d>28))) printf("enter a valid date.\n");
        else break;
    }
    snprintf(date,20,"%02d-%02d-%02d",d,m,y);
    int num = 0;
    for (int i=0; i<reservationCount; i++)
    {
        if (!strcmp(date, reservations[i].checkInDate) && !strcmp(reservations[i].status,"confirmed"))
        {
            printGuestInfo(reservations[i]);
            num++;
        }
    }
    if (num==0) printf("No costumers checked-in on that date\n");
}

#endif // QUERY_H_INCLUDED
