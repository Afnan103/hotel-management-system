#ifndef ROOMS_H_INCLUDED
#define ROOMS_H_INCLUDED
#include <string.h>

typedef struct
{
    int roomNumber ;
    char status[10];
    char category[15];
    int price ;
} Room;

int loadedRooms=0;

Room rooms[100];

void loadRooms()
{
    char line[100];
    FILE *froom = fopen("rooms.txt","r");
    if(froom== NULL)
    {
        printf("error opening file");
        exit(1);
    }
    loadedRooms=0;
    while (fgets(line, sizeof(line), froom))
    {
        if (strlen(line) == 1 || line[0] == '\n')
        {
            continue;
        }
        char* token = strtok(line, " ");
        if (token != NULL) rooms[loadedRooms].roomNumber = atoi(token);
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            strcpy(rooms[loadedRooms].status, token);
        }
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            strcpy(rooms[loadedRooms].category, token);
        }
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            rooms[loadedRooms].price = atoi(token);
        }
        loadedRooms++;
    }
    fclose(froom);
}

void saveRooms()
{
    FILE *file = fopen("rooms.txt", "w");
    if (file == NULL)
    {
        printf("Error: Could not open file \n");
        return;
    }

    for (int i = 0; i < loadedRooms; i++)
    {
        fprintf(file, "%d %s %s %d\n",
                rooms[i].roomNumber,
                rooms[i].status,
                rooms[i].category,
                rooms[i].price);
    }

    fclose(file);
    printf("Room data saved to \n");
}

#endif // ROOMS_H_INCLUDED
