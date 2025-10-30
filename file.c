 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Hotel
{
    int room_no;
    char name[30];
    char address[50];
    char phone[15];
};

// Function to add booking
void addBooking()
{
    FILE *fp;
    struct Hotel customer;

    fp = fopen("hotel.dat", "ab"); // append binary
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter room number: ");
    scanf("%d", &customer.room_no);
    printf("Enter name: ");
    scanf("%s", customer.name);
    printf("Enter address: ");
    scanf("%s", customer.address);
    printf("Enter phone number: ");
    scanf("%s", customer.phone);

    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);

    printf("\nBooking saved successfully!\n");
}

// Function to display all records
void displayAll()
{
    FILE *fp;
    struct Hotel customer;

    fp = fopen("hotel.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Customer Records ---\n");
    while (fread(&customer, sizeof(customer), 1, fp))
    {
        printf("Room No: %d\n", customer.room_no);
        printf("Name: %s\n", customer.name);
        printf("Address: %s\n", customer.address);
        printf("Phone: %s\n", customer.phone);
        printf("------------------------\n");
    }
    fclose(fp);
}

// Function to search by room number
void searchBooking()
{
    FILE *fp;
    struct Hotel customer;
    int room, found = 0;

    fp = fopen("hotel.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter room number to search: ");
    scanf("%d", &room);

    while (fread(&customer, sizeof(customer), 1, fp))
    {
        if (customer.room_no == room)
        {
            printf("\nBooking found!\n");
            printf("Room No: %d\n", customer.room_no);
            printf("Name: %s\n", customer.name);
            printf("Address: %s\n", customer.address);
            printf("Phone: %s\n", customer.phone);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nNo booking found for this room number.\n");

    fclose(fp);
}

// Function to delete booking
void deleteBooking()
{
    FILE *fp, *temp;
    struct Hotel customer;
    int room, found = 0;

    fp = fopen("hotel.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    printf("\nEnter room number to delete: ");
    scanf("%d", &room);

    while (fread(&customer, sizeof(customer), 1, fp))
    {
        if (customer.room_no != room)
        {
            fwrite(&customer, sizeof(customer), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("hotel.dat");
    rename("temp.dat", "hotel.dat");

    if (found)
        printf("\nBooking deleted successfully!\n");
    else
        printf("\nNo booking found with this room number.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--- Hotel Management System ---\n");
        printf("1. Add Booking\n");
        printf("2. Display All Records\n");
        printf("3. Search Booking\n");
        printf("4. Delete Booking\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBooking();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchBooking();
            break;
        case 4:
            deleteBooking();
            break;
        case 5:
            exit(0);
        default:
            printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}