#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include  "input.h"
#include "validation.h"
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)
    {
        printf("Contact list is empty!\n");
        return;
    }

    int choice = get_choice_input("Sort");

    if(choice == 0)
    {
        return;
    }

     choice_sorting(choice, addressBook);




    
       

       

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount < MAX_CONTACTS)
    {      
        /* Define the logic to create a Contacts */
        int nameSize , phoneSize, emailSize;

        

        nameSize = sizeof(addressBook->contacts[0].name);
        phoneSize = sizeof(addressBook->contacts[0].phone);
        emailSize = sizeof(addressBook->contacts[0].email);

            char *res;

        char temp_name[nameSize], temp_phone[phoneSize], temp_email[emailSize];

        res =  get_input(temp_name, nameSize, "name" , nameValidation, addressBook);

        if(res == NULL) return;
       

        res = get_input(temp_phone, phoneSize, "phone", contact_validation, addressBook);

        if(res == NULL) return;

       
       

        res = get_input(temp_email, emailSize, "email", email_validation, addressBook);

        if(res == NULL) return;


         

      

       


       
    
        strcpy(addressBook->contacts[addressBook->contactCount].name, temp_name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, temp_email);
        
        addressBook->contactCount++;

        printf("Contact saved succesfully!\n");
        return;

    }
    else
    {
        printf("Contact size is already full sorry!\n");
        return;
    }

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
     if(addressBook->contactCount == 0)
    {
        printf("Contact list is empty!\n");
        return;
    }

    int choice = get_choice_input("Search");

    if(choice == 0)
    {
        return;
    }
    Search_choice(choice, addressBook);

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
     if(addressBook->contactCount == 0)
    {
        printf("Contact list is empty!\n");
        return;
    }

    int choice = get_choice_input("Edit");

    if(choice == 0)
    {
        return;
    }

    Edit_choice(choice, addressBook);

    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
     if(addressBook->contactCount == 0)
    {
        printf("Contact list is empty!\n");
        return;
    }

    int choice = get_choice_input("Delete");

    if(choice == 0)
    {
        return;
    }

    Delete_choice(choice, addressBook);
   
}
