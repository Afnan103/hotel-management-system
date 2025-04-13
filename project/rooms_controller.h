#ifndef ROOMS_CONTROLLER_H_INCLUDED
#define ROOMS_CONTROLLER_H_INCLUDED
#include "rooms.h"
#include "print.h"


int UpdateRoomStatus(int roomnum)
{
    loadRooms();
    int numberofrooms=loadedRooms;
    int i,a=1;
    char line[100];
    for(i=0; i<numberofrooms; i++)
    {
        if(rooms[i].roomNumber==roomnum)
        {
            a=0;
            break;
        }
    }
    if(a!=0) return 0;
    else
    {
        if(strcmp(rooms[i].status,"Available")==0) strcpy(rooms[i].status,"Reserved");
        else if(strcmp(rooms[i].status,"Reserved")==0) strcpy(rooms[i].status,"Available");

        FILE *sh;
        sh=fopen("rooms.txt","w");
        if (sh == NULL)
        {
            printf("Error opening the file\n");
            exit(1);
        }
        for(i=0; i<numberofrooms; i++)
        {
            snprintf(line,100,"%d %s %s %d\n",rooms[i].roomNumber,rooms[i].status,rooms[i].category,rooms[i].price);
            fputs(line,sh);
        }
        fclose(sh);
    }
    return 1;
}

void checkRoomAvailability()
{
     putColor(12);
    loadRooms();
    char category[20];
    int number ;
    int found = 0;
    int choice ;
    printf("\nChoose how to check availability \n1: SeaView  \n2: GardenView \n3: LakeView \n4: all \n5: Check by room number\n");
    scanf("%d",&choice );
    switch (choice)
    {
    case 1:
        strcpy(category,"SeaView");
        printf("\n=== Available Rooms ===\n");
        for (int i = 0; i < loadedRooms; i++)
        {
            if (strcmp(rooms[i].status, "Available") == 0)
            {
                if (strcmp(rooms[i].category, category) == 0)
                {
                    displayRoom(rooms[i]);
                    found = 1;
                }
            }
        }
        break;
    case 2:
        memset(category,0,sizeof(category));  // dy 34an ams7 ay 7aga fel array 34an lw e5tar all w hya mktoob fyha 7aga akbr hatbwzha
        strcpy(category,"GardenView");
        printf("\n=== Available Rooms ===\n");
        for (int i = 0; i < loadedRooms; i++)
        {
            if (strcmp(rooms[i].status, "Available") == 0)
            {
                if (strcmp(rooms[i].category, category) == 0)
                {
                    displayRoom(rooms[i]);
                    found = 1;
                }
            }

        }
        break;
    case 3:
        memset(category,0,sizeof(category));
        strcpy(category,"LakeView");
        printf("\n=== Available Rooms ===\n");
        for (int i = 0; i < loadedRooms; i++)
        {
            if (strcmp(rooms[i].status, "Available") == 0)
            {
                if (strcmp(rooms[i].category, category) == 0)
                {
                    displayRoom(rooms[i]);
                    found = 1;
                }
            }

        }
        break;
    case 4:
        memset(category,0,sizeof(category));
        strcpy(category,"all");
        printf("\n=== Available Rooms ===\n");
        for (int i = 0; i < loadedRooms; i++)
        {
            if (strcmp(rooms[i].status, "Available") == 0)
            {
                if (strcmp(category, "all") == 0)
                {
                    displayRoom(rooms[i]);
                    found = 1;
                }
            }

        }
        break;
    case 5:
        printf("Enter room number :");
        scanf("%d",&number);
        printf("\n=== Available Rooms ===\n");
        for (int i = 0; i < loadedRooms; i++)
        {
            if (strcmp(rooms[i].status, "Available") == 0)
            {
                if (rooms[i].roomNumber==number)
                {
                    displayRoom(rooms[i]);
                    found = 1;
                }
            }

        }
        break;

    default:
        printf("Invalid choice! Please try again.\n");
    }

    if (found==0)
    {
        printf("No rooms found matching the criteria.\n");
    }
}

int Assignroom(char *type)
{
    FILE *rh;
    rh = fopen("rooms.txt", "r");
    if (rh == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    char temp[100];
    char *token;
    int room_number = 0;
    while (fgets(temp, sizeof(temp), rh) != NULL)
    {
        token = strtok(temp, " ");
        if (token != NULL) room_number = atoi(token);
        token = strtok(NULL, " ");
        if (token != NULL && strcmp(token, "Reserved") == 0) continue;
        token = strtok(NULL, " ");
        if (token != NULL && strcmp(token, type) == 0)
        {
            fclose(rh);
            return room_number;
        }
    }
    fclose(rh);
    return 0;
}

#endif // ROOMS_CONTROLLER_H_INCLUDED
