#ifndef VIEW_COSTUMER_DETAILS_H_INCLUDED
#define VIEW_COSTUMER_DETAILS_H_INCLUDED
#include "reservations.h"
#include "rooms.h"
#include "input.h"
void search_costumer(char *number)
{
     putColor(10);
    int i;
    int found = 0;
    loadReservations();
    for (i = 0; i < reservationCount; i++)
    {
        if ((reservations[i].roomNumber) == atoi(number))
        {
            printf("Customer data for Room Number %s is :\n",number);
            printf("Reservation ID: %d\n", reservations[i].reservationID);
            printf("Room Number: %d\n", reservations[i].roomNumber);
            printf("Nights: %s\n", reservations[i].nights);
            printf("Mobile Number: %s\n", reservations[i].mobileNumber);
            printf("National ID: %s\n", reservations[i].nationalID);
            printf("Status: %s\n", reservations[i].status);
            printf("Customer Name: %s\n", reservations[i].customerName);
            printf("Email: %s\n", reservations[i].email);
            printf("Check in Date: %s\n", reservations[i].checkInDate);
            found = 1;
        }
        else if (reservations[i].reservationID == atoi(number))
        {
            printf("Customer data for Reservation ID %s is :\n",number);
            printf("Reservation ID: %d\n", reservations[i].reservationID);
            printf("Room Number: %d\n", reservations[i].roomNumber);
            printf("Nights: %s\n", reservations[i].nights);
            printf("Mobile Number: %s\n", reservations[i].mobileNumber);
            printf("National ID: %s\n", reservations[i].nationalID);
            printf("Status: %s\n", reservations[i].status);
            printf("Customer Name: %s\n", reservations[i].customerName);
            printf("Email: %s\n", reservations[i].email);
            printf("Check in Date: %s\n", reservations[i].checkInDate);
            found = 1;
        }

    }
    if (found==0)
    {
        printf("No reservation found.\n");
    }

}

void view_costumer_details()
{
     putColor(11);
    char number[10];
    while(1){
    printf("Enter Room Number or reservation Id(enter 0 to go back) : \n");
    fgets(number,10,stdin);
    number[strcspn(number,"\n")]='\0';
    if(strcmp(number,"0")==0) break;
    if(is_all_digits(number)==0){
            printf("Invalid input\n");
    }
    else{
            search_costumer(number);
    }
}
}

#endif // VIEW_COSTUMER_DETAILS_H_INCLUDED
