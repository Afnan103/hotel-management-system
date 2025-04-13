#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

void printGuestInfo(Reservation r)
{
    putColor(4);
    printf("Costumer Name:\t\t%s\n", r.customerName);
    printf("Costumer National ID:\t%s\n", r.nationalID);
    printf("Costumer Email:\t\t%s\n", r.email);
    printf("Mobile Number:\t\t%s\n-------------\n", r.mobileNumber);
}

void printReservation(Reservation r)
{
    putColor(6);
    printf("---------\n");
    printf("Reservation ID:\t\t%d\n", r.reservationID);
    printf("Room Number:\t\t%d\n", r.roomNumber);
    printf("Reservation Status:\t%s\n", r.status);
    printf("No.of Nights:\t\t%s\n", r.nights);
    printf("Check-in Date:\t\t%s\n", r.checkInDate);
    printGuestInfo(r);
}

void printRoom(Room r)
{
    putColor(3);
    printf("Status:\t\t%s\nCategory:\t%s\nPrice/Night:\t%d\n-------------\n", r.status, r.category, r.price);
}

void displayRoom(Room room) {
     putColor(5);
    printf("Room Number: %d | Status: %s | Category: %s | Price: %d\n",
           room.roomNumber,
           room.status,
           room.category,
           room.price);
}

#endif // PRINT_H_INCLUDED
