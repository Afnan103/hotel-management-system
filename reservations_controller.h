#ifndef RESERVATIONS_CONTROLLER_H_INCLUDED
#define RESERVATIONS_CONTROLLER_H_INCLUDED
#include "reservations.h"
#include "sort_res_by_date.h"
#include "rooms_controller.h"
void create_reservation()
{
     putColor(7);
    Reservation info;
    char type[20],typen[10],choice[10],ans[10];
    char line[250];
    name client;
    date checkin;
    int RES_ID,ROOM,b=1,c=1;
    printf("Please,enter the reservation details:\n");
    printf("Customer name:\n");
    while(1)
    {
        printf("First name:");
        fgets(client.first,50,stdin);
        client.first[strcspn(client.first,"\n")]='\0';
        if(is_all_letters(client.first)==0) printf("Please,enter a valid name.\n");
        else if(strlen(client.first)<3) printf("Name should be at least 3 letters.\n");
        else break;
    }
    while(1)
    {
        printf("Last name:");
        fgets(client.last,50,stdin);
        client.last[strcspn(client.last,"\n")]='\0';
        if(is_all_letters(client.last)==0) printf("Please,enter a valid name.\n");
        else if(strlen(client.last)<3) printf("Name should be at least 3 letters.\n");
        else break;
    }
    snprintf(info.customerName,50,"%s %s",client.first,client.last);
    printf("Contact information:\n");
    while(1)
    {
        printf("National ID:");
        fgets(info.nationalID,30,stdin);
        info.nationalID[strcspn(info.nationalID,"\n")]='\0';
        if(is_all_digits(info.nationalID)==0) printf("Please,enter a valid ID.\n");
        else if(strlen(info.nationalID)!=14) printf("ID should be 14 digits.\n");
        else if((info.nationalID[0]!='3'&&info.nationalID[0]!='2')) printf("Please,enter a valid ID.\n");
        else break;
    }
    while(1)
    {
        printf("Email:");
        fgets(info.email,50,stdin);
        info.email[strcspn(info.email,"\n")]='\0';
        if(email_valid(info.email)) break;
        else printf("Please,enter a valid email.\n");
    }
    while(1)
    {
        printf("Phone number(mobile):");
        fgets(info.mobileNumber,30,stdin);
        info.mobileNumber[strcspn(info.mobileNumber,"\n")]='\0';
        if(is_all_digits(info.mobileNumber)==0) printf("Please,enter a valid phone number.\n");
        else if(strlen(info.mobileNumber)!=11) printf("Phone number should be 11 digits.\n");
        else if(info.mobileNumber[0]!='0'||info.mobileNumber[1]!='1'||
                (info.mobileNumber[2]!='0'&&info.mobileNumber[2]!='1'&&info.mobileNumber[2]!='2'&&info.mobileNumber[2]!='5'))
            printf("Please enter a valid number.\n");
        else break;
    }
    printf("Check in date(it has to be in the future):\n");
    while(1)
    {
        printf("day:");
        fgets(checkin.day,10,stdin);
        checkin.day[strcspn(checkin.day,"\n")]='\0';
        int d=atoi(checkin.day);
        printf("month:");
        fgets(checkin.month,10,stdin);
        checkin.month[strcspn(checkin.month,"\n")]='\0';
        int m=atoi(checkin.month);
        printf("year:");
        fgets(checkin.year,10,stdin);
        checkin.year[strcspn(checkin.year,"\n")]='\0';
        int y=atoi(checkin.year);
        if (is_all_digits(checkin.day)==0||is_all_digits(checkin.month)==0||is_all_digits(checkin.year)==0)
            printf("enter a valid date.\n");
        else if(m<1||m>12) printf("enter a valid date.\n");
        else if(y<2024) printf("enter a valid date.\n");
        else if(y==2024&&(m<12||(m==12&&d<29))) printf("enter a valid date.\n");
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
    if((atoi(checkin.day)<10) && (strlen(checkin.day)==1)) snprintf(checkin.day,10,"0%d",atoi(checkin.day));
    if((atoi(checkin.month)<10) && (strlen(checkin.month)==1)) snprintf(checkin.month,10,"0%d",atoi(checkin.month));
    snprintf(info.checkInDate,20,"%s-%s-%s",checkin.day,checkin.month,checkin.year);
    while(1)
    {
        printf("Number of nights(max 30 nights):");
        fgets(info.nights,10,stdin);
        info.nights[strcspn(info.nights,"\n")]='\0';
        int n=atoi(info.nights);
        if(is_all_digits(info.nights)==0) printf("Please,enter a valid number.\n");
        else if(n<1||n>30) printf("Please,enter a valid number.\n");
        else break;
    }
    printf("The room type:\n");
    printf("1.SeaView\n2.LakeView\n3.GardenView\n");
    while(1)
    {
        printf("select your choice(1,2,3):");
        fgets(typen,20,stdin);
        typen[strcspn(typen,"\n")]='\0';
        if(strcmp(typen,"1")==0)
        {
            strcpy(type,"SeaView");
            if(Assignroom(type)==0)
            {
                printf("NO AVAILABLE ROOMS OF THIS CHOICE.\n");
                printf("======================\nDo you want to\n1.choose another room\n2.EXIT\n");
                while(1)
                {
                    printf("enter your choice:");
                    fgets(choice,10,stdin);
                    choice[strcspn(choice,"\n")]='\0';
                    if(strcmp(choice,"1")==0) break;
                    else if(strcmp(choice,"2")==0)
                    {
                        b=0;
                        break;
                    }
                    else printf("enter a valid choice.\n");
                }
            }
            else
            {
                c=0;
                break;
            }
            if(b==0) break;
        }
        else if(strcmp(typen,"2")==0)
        {
            strcpy(type,"LakeView");
            if(Assignroom(type)==0)
            {
                printf("NO AVAILABLE ROOMS OF THIS CHOICE.\n");
                printf("======================\nDo you want to\n1.choose another room\n2.EXIT\n");
                while(1)
                {
                    printf("enter your choice:");
                    fgets(choice,10,stdin);
                    choice[strcspn(choice,"\n")]='\0';
                    if(strcmp(choice,"1")==0) break;
                    else if(strcmp(choice,"2")==0)
                    {
                        b=0;
                        break;
                    }
                    else printf("enter a valid choice.\n");
                }
            }
            else
            {
                c=0;
                break;
            }
            if(b==0) break;
        }
        else if(strcmp(typen,"3")==0)
        {
            strcpy(type,"GardenView");
            if(Assignroom(type)==0)
            {
                printf("NO AVAILABLE ROOMS OF THIS CHOICE.\n");
                printf("======================\nDo you want to\n1.choose another room\n2.go back\n");
                while(1)
                {
                    printf("enter your choice:");
                    fgets(choice,10,stdin);
                    choice[strcspn(choice,"\n")]='\0';
                    if(strcmp(choice,"1")==0) break;
                    else if(strcmp(choice,"2")==0)
                    {
                        b=0;
                        break;
                    }
                    else printf("enter a valid choice.\n");
                }
            }
            else
            {
                c=0;
                break;
            }
            if(b==0) break;
        }
        else printf("enter a valid choice.\n");
    }
    if(c==0)
    {
        while(1)
        {
            printf("Do you want to save this reservtion?(yes/no):");
            fgets(ans,20,stdin);
            ans[strcspn(ans,"\n")]='\0';
            if(strcmp(ans,"yes")==0)
            {
                printf("DONE.\n");
                RES_ID=generateID();
                ROOM=Assignroom(type);
                printf("Your reservation ID is:%d\n",RES_ID);
                printf("Your room number is:%d\n",ROOM);
                strcpy(info.status,"unconfirmed");
                info.reservationID=RES_ID;
                info.roomNumber=ROOM;
                snprintf(line,250,"%d,%d,%s,%s,%s,%s,%s,%s,%s\n",info.reservationID,info.roomNumber,info.status,info.customerName,info.nationalID,info.nights,info.checkInDate,info.email,info.mobileNumber);
                savereservation(line);
                UpdateRoomStatus(ROOM);
                sortbydate();
                break;
            }
            else if(strcmp(ans,"no")==0)
            {
                printf("Reservation not saved.\n");
                break;
            }
            else printf("enter a valid answer.\n");
        }
    }
}

void edit_reservation()
{
     putColor(1);
    char ID[50],choice[10],choice2[10];
    int i,d=0;
    Reservation info;
    loadReservations();
    while(1)
    {
        printf("Please enter your reservation ID or room number(enter 0 to go back):");
        fgets(ID,50,stdin);
        ID[strcspn(ID,"\n")]='\0';
        if(strcmp(ID,"0")==0){
            d=1;
            break;
        }
        int a;
        int len=reservationCount;
        for(i=0; i<len; i++)
        {
            if(atoi(ID)==reservations[i].reservationID || atoi(ID)==reservations[i].roomNumber)
            {
                a=1;
                break;
            }
        }
        if(a!=1) printf("Please enter a valid reservation ID.\n");
        else break;
    }
    char typen[10],type[20];
    date checkin;
    name client;
    if(d!=1){
    while(1)
    {
        int b=1;
        printf("1.The name.\n2.The mobile number.\n3.The email.\n4.The checkin date.\n5.The Room category\n6.The number of nights.\n");
        while(1)
        {
            printf("select what you want to edit:");
            fgets(choice,10,stdin);
            choice[strcspn(choice,"\n")]='\0';
            if(strcmp(choice,"1")==0)
            {
                printf("Enter the new name.\n");
                while(1)
                {
                    printf("First:");
                    fgets(client.first,50,stdin);
                    client.first[strcspn(client.first,"\n")]='\0';
                    if(is_all_letters(client.first)==0) printf("Please,enter a valid name.\n");
                    else if(strlen(client.first)<3) printf("Name should be at least 3 letters.\n");
                    else break;
                }
                while(1)
                {
                    printf("Last name:");
                    fgets(client.last,50,stdin);
                    client.last[strcspn(client.last,"\n")]='\0';
                    if(is_all_letters(client.last)==0) printf("Please,enter a valid name.\n");
                    else if(strlen(client.last)<3) printf("Name should be at least 3 letters.\n");
                    else break;
                }
                snprintf(info.customerName,50,"%s %s",client.first,client.last);
                break;
            }
            else if(strcmp(choice,"2")==0)
            {
                while(1)
                {
                    printf("Phone number(mobile):");
                    fgets(info.mobileNumber,100,stdin);
                    info.mobileNumber[strcspn(info.mobileNumber,"\n")]='\0';
                    if(is_all_digits(info.mobileNumber)==0) printf("Please,enter a valid phone number.\n");
                    else if(strlen(info.mobileNumber)!=11) printf("Phone number should be 11 digits.\n");
                    else if(info.mobileNumber[0]!='0'||info.mobileNumber[1]!='1'||
                            (info.mobileNumber[2]!='0'&&info.mobileNumber[2]!='1'&&info.mobileNumber[2]!='2'&&info.mobileNumber[2]!='5'))
                        printf("Please enter a valid number.\n");
                    else break;
                }
                break;
            }
            else if(strcmp(choice,"3")==0)
            {
                while(1)
                {
                    printf("Email:");
                    fgets(info.email,50,stdin);
                    info.email[strcspn(info.email,"\n")]='\0';
                    if(email_valid(info.email)) break;
                    else printf("Please,enter a valid email.\n");
                }
                break;
            }
            else if(strcmp(choice,"4")==0)
            {
                printf("Check in date(it has to be in the future):\n");
                while(1)
                {
                    printf("day:");
                    fgets(checkin.day,10,stdin);
                    checkin.day[strcspn(checkin.day,"\n")]='\0';
                    int d=atoi(checkin.day);
                    printf("month:");
                    fgets(checkin.month,10,stdin);
                    checkin.month[strcspn(checkin.month,"\n")]='\0';
                    int m=atoi(checkin.month);
                    printf("year:");
                    fgets(checkin.year,10,stdin);
                    checkin.year[strcspn(checkin.year,"\n")]='\0';
                    int y=atoi(checkin.year);
                    if ((is_all_digits(checkin.day)==0)||(is_all_digits(checkin.month)==0)||(is_all_digits(checkin.year)==0))
                        printf("enter a valid date.\n");
                    else if(m<1||m>12) printf("enter a valid date.\n");
                    else if(y<2024) printf("enter a valid date.\n");
                    else if((y==2024)&&((m<12)||(m==12&&d<29))) printf("enter a valid date.\n");
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
                if((atoi(checkin.day)<10) && (strlen(checkin.day)==1)) snprintf(checkin.day,10,"0%d",atoi(checkin.day));
                if((atoi(checkin.month)<10) && (strlen(checkin.month)==1)) snprintf(checkin.month,10,"0%d",atoi(checkin.month));
                snprintf(info.checkInDate,20,"%s-%s-%s",checkin.day,checkin.month,checkin.year);
                break;
            }
            else if(strcmp(choice,"5")==0)
            {
                printf("The room type:\n");
                printf("1.SeaView\n2.LakeView\n3.GardenView\n");
                while(1)
                {
                    printf("select your choice(1,2,3):");
                    fgets(typen,20,stdin);
                    typen[strcspn(typen,"\n")]='\0';
                    if(is_all_digits(typen)==0) printf("Please,enter a valid choice.\n");
                    else if(strlen(typen)!=1) printf("Please,enter a valid choice.\n");
                    else if(typen[0]!='1'&&typen[0]!='2'&&typen[0]!='3') printf("Please,enter a valid choice.\n");
                    else break;
                }
                if(typen[0]=='1') strcpy(type,"SeaView");
                else if(typen[0]=='2') strcpy(type,"LakeView");
                else if(typen[0]=='3') strcpy(type,"GardenView");
                if(Assignroom(type)==0)
                {
                    printf("no available room.\n");
                    b=0;
                    break;
                }
                else
                {
                    printf("Your new room number would be %d\n",Assignroom(type));
                    break;
                }
            }
            else if(strcmp(choice,"6")==0)
            {
                while(1)
                {
                    printf("Number of nights(max 30 nights):");
                    fgets(info.nights,10,stdin);
                    info.nights[strcspn(info.nights,"\n")]='\0';
                    int n=atoi(info.nights);
                    if(is_all_digits(info.nights)==0) printf("Please,enter a valid number.\n");
                    else if(n<1||n>30) printf("Please,enter a valid number.\n");
                    else break;
                }
                break;
            }
            else printf("enter a valid choice\n");
        }
        if(b!=0)
        {
            printf("============================\nDo you want to:\n1.save\n2.discard\n");
            while(1)
            {
                printf("enter your choice:");
                fgets(choice2,10,stdin);
                choice2[strcspn(choice2,"\n")]='\0';
                if(strcmp(choice2,"1")==0)
                {
                    if(strcmp(choice,"1")==0) strcpy(reservations[i].customerName,info.customerName);
                    else if(strcmp(choice,"2")==0) strcpy(reservations[i].mobileNumber,info.mobileNumber);
                    else if(strcmp(choice,"3")==0) strcpy(reservations[i].email,info.email);
                    else if(strcmp(choice,"4")==0) strcpy(reservations[i].checkInDate,info.checkInDate);
                    else if(strcmp(choice,"5")==0)
                    {
                        UpdateRoomStatus(reservations[i].roomNumber);
                        reservations[i].roomNumber=Assignroom(type);
                        UpdateRoomStatus(reservations[i].roomNumber);
                    }
                    else if(strcmp(choice,"6")==0) strcpy(reservations[i].nights,info.nights);
                    saveEdit();
                    printf("SAVED.\n");
                    sortbydate();
                    break;
                }
                else if(strcmp(choice2,"2")==0) break;
                else printf("Please enter a valid choice.\n");
            }
        }
        printf("======================\nDo you want to:\n1.Make another edit\n2.leave\n");
        while(1)
        {
            printf("enter your choice:");
            fgets(choice2,10,stdin);
            choice2[strcspn(choice2,"\n")]='\0';
            if(strcmp(choice2,"1")!=0 && strcmp(choice2,"2")!=0) printf("Please,enter a valid choice.\n");
            else break;
        }
        if(strcmp(choice2,"1")==0){
            loadReservations();
        int len=reservationCount;
        for(i=0; i<len; i++)
        {
            if(atoi(ID)==reservations[i].reservationID || atoi(ID)==reservations[i].roomNumber) break;
        }
    }
        else if(strcmp(choice2,"2")==0) break;
    }
    }
}

int o_cancel_res(int resID)
{
     putColor(2);
    loadReservations();
    int numberofres=reservationCount;
    int i,a=1;
    char line[250];
    for(i=0; i<numberofres; i++)
    {
        if(reservations[i].reservationID==resID || reservations[i].roomNumber==resID)
        {
            a=0;
            break;
        }

    }
    if(a!=0) return 0;
    else if(strcmp(reservations[i].status,"confirmed")==0) return -1;
    else
    {
        UpdateRoomStatus(reservations[i].roomNumber);
        for(i=i; i<reservationCount; i++) reservations[i]=reservations[i+1];
        reservationCount--;
        FILE *sh;
        sh=fopen("Reservation.txt","w");
        if (sh == NULL)
        {
            printf("Error opening the file\n");
            exit(1);
        }
        for(i=0; i<reservationCount; i++)
        {
            snprintf(line,250,"%d,%d,%s,%s,%s,%s,%s,%s,%s\n",reservations[i].reservationID,reservations[i].roomNumber,reservations[i].status,
                     reservations[i].customerName,reservations[i].nationalID,reservations[i].nights,reservations[i].checkInDate,reservations[i].email,reservations[i].mobileNumber);
            fputs(line,sh);
        }
        fclose(sh);
    }
    return 1;
}

void cancel_reservation()
{
     putColor(8);
    char Num[20];
    int n;
    while(1)
    {
        printf("Please enter the room number or reservation id(enter 0 to go back):");
        fgets(Num,20,stdin);
        Num[strcspn(Num,"\n")]='\0';
        if(strcmp(Num,"0")==0) break;
        n=atoi(Num);
        if(o_cancel_res(n)==0) printf("reservation doesn't exist\n");
        else if(o_cancel_res(n)==-1) printf("can't cancel a confirmed reservation\n");
        else if(o_cancel_res(n)==1) printf("Cancellation is done.\n");
        else break;
            }
}

#endif // RESERVATIONS_CONTROLLER_H_INCLUDED
