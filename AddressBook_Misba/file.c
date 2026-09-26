#include <stdio.h>
#include "file.h"

// ---------------##[   SAVE CONTACTS TO FILE FUNCTION  ]##------------
void saveContactsToFile(AddressBook *AddressBook)
{
    int count = AddressBook->contactCount;

    if(count == 0)
    {
        printf("No contacts to save!\n");
        return;
    }
    FILE *fptr =fopen("contacts.csv", "w");

    if (fptr == NULL)
    {
    printf("Error opening file!\n");
    return;
     }

    fprintf(fptr, "#%d\n", count);

    for(int i=0; i<count; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", AddressBook->contacts[i].name, AddressBook->contacts[i].phone, AddressBook->contacts[i].email);
    }

    fclose(fptr);

 



}



// ---------------##[   LOAD CONTACTS FROM FILE FUNCTION  ]##------------
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "r");
    int count;

    if(fptr != NULL)
    {
        fscanf(fptr, "#%d", &count);
       

        if(count >=0 && count <=100)
        {
            addressBook->contactCount = count;
            for(int i=0; i<count; i++)
            {
            fscanf(fptr, " %[^,],%[^,],%[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
            
        }
        else
        {
            fclose(fptr);
            return;

        }
    }
    fclose(fptr);

}