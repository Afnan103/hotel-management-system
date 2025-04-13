#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "login.h"
#include "quit.h"
#include "reservations_controller.h"
#include "checkin_checkout.h"
#include "rooms_controller.h"
#include "view_costumer_details.h"
#include "query.h"
#include<windows.h>
void putColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


void navigate(int choice);

void mainMenu()
{
    putColor(1);
    printf("0. Back to Login interface\n");
    printf("1. Reserve a Room\n");
    printf("2. Check-in\n");
    printf("3. Cancel Reservation\n");
    printf("4. Check-out\n");
    printf("5. Check Room Availability\n");
    printf("6. View Customer Details\n");
    printf("7. Edit Reservation Details\n");
    printf("8. Query(search)\n");
    printf("9. Reservation Report\n");
    printf("10. Exit\n");
    int choice;
    readInt(&choice);
    navigate(choice);
}

void askToCont()
{
    putColor(1);
    printf("1. Get back to the main menu\n2. Exit\n");
    int selected;
    readInt(&selected);
    if (selected == 1)
        mainMenu();
    else if (selected == 2)
        quit();
    else
    {
        printf("Invalid input\n");
        askToCont();
    }
}

void navigate(int choice)
{
    switch (choice)
    {
    case 0:
        loginsystem();
        mainMenu();
        break;
    case 1:
        create_reservation();
        askToCont();
        break;
    case 2:
        check_in();
        askToCont();
        break;
    case 3:
        cancel_reservation();
        askToCont();
        break;
    case 4:
        check_out();
        askToCont();
        break;
    case 5:
        checkRoomAvailability();
        askToCont();
        break;
    case 6:
        view_costumer_details();
        askToCont();
        break;
    case 7:
        edit_reservation();
        askToCont();
        break;
    case 8:
        query();
        askToCont();
        break;
    case 9:
        report_by_date();
        askToCont();
        break;
    case 10:
        quit();
        break;
    default:
        putColor(4);
        printf("Invalid input\n");
        mainMenu();
    }
}

char input[100];

int main()
{

    putColor(2);
    int choice,gett;
    printf("1. Login\n");
    printf("2. Exit\n");

    while(1)
    {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (isValidNumber(input))
        {
            choice = atoi(input);
        }
        else
        {
            printf("wrong input.please enter a 1 or 2 \n");
            continue;
        }

        if(choice==1)
        {
            gett=loginsystem();
            break;
        }
        else if(choice==2)
        {
            quit();
            return 1;
            break;
        }
        printf("please enter 1 or 2\n");
    }
    if(gett==1)
    {
        mainMenu();
    }
    else if(gett==0)
        return 1;

    putColor(7);
    return 0;
}


