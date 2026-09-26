#include<string.h>
#include<stdio.h>
#include "validation.h"
#include "contact.h"
#include "input.h"

// ---------------**CLEARING BUFFER FUNCTION**--------
void clear_buffer()
{
    int ch = getchar();
    while(ch!='\n' && ch != EOF)
    {
       ch = getchar();   
    }
}






// -----------------VALID LENGTH AND CHARCATER FUNCTIONS------------------
char * check_valid_length(char str[])
{
     if(strlen(str) == 0)
    {
        printf("Invalid input! your input is empty \n");
        return NULL;
    }
    else if(strlen(str) < 4)
    {
        printf("Invalid input! name must contain at least 4 characters. \n");
        return NULL;

    }
    else return str;

}

char * check_valid_characters(char str[])
{
    
     if((str[0] <'A' || str[0] >'Z') &&
        (str[0] < 'a' || str[0] > 'z'))
    {
        printf("Invalid input! your input should start from alphabets \n");
        return NULL;
    }
    int i=1;
    while(str[i]!='\0')
    {
        if((str[i] >= 'A' && str[i] <= 'Z') || 
           (str[i] >= 'a' && str[i] <= 'z') ||
           (str[i] == ' '))
        {
            i++;
        }
        else
        {
            printf("Invalid input! name should contain only alphabets \n");
            return NULL;
        }

    }

    return str;

}
// -------------------------UNIQUENEES-FUCNTION------------------
char * uniqueness(AddressBook *addressBook, char str[], char arr_name[])
{
    if((strcmp(arr_name, "phone"))== 0)
    {
        for(int i=0; i< addressBook->contactCount; i++)
       {
        if((strcmp(addressBook->contacts[i].phone, str))==0)
        {
            printf("Invalid contact !phone number  already exist.\n");
            return NULL;
            
        }
        
    
       }
       return str;



    }
    else if( (strcmp(arr_name, "email")) == 0)
    {  
        for(int i=0; i< addressBook->contactCount; i++)
       {
            if((strcmp(addressBook->contacts[i].email, str))==0)
            {
                 printf("Invalid email ! email  already exist.\n");
                return NULL;
                
            }
       }
       return str;

    }

    return NULL;
    
   
}


//-------------------------- REMOVE SPACE FUNCTION------------
void removespace_pointer(char str[])
{
    int read=0, write=0, space=0;

    while(str[read]!='\0')
    {
        if(str[read] == ' ' || str[read] == '\t')
        {
            space++;
            read++;
        }
        else
        {
            if(space > 0 )
            {
                if(write > 0)
                {
                str[write++] = ' ';
                
                }
                space = 0;
                
            }
           
            
                str[write++] = str[read++];
            
        }
       
    }
     str[write] = '\0';
    
   

}
// -----------------VALIDATION FUNCTIONS------------------------
char * nameValidation(char str[], AddressBook *addressBook)
{
    removespace_pointer(str);

    if(check_valid_length(str) == NULL)
        return NULL;


    if(check_valid_characters(str) == NULL)
        return NULL;

   
    return str;
    
}

// ------------------------CONTACT-VALIDATION--------------
char * contact_validation(char contact[], AddressBook* addressBook)
{
   
    if(strlen(contact) != 10)
    {
        printf("Invalid contact, 10 digits needed\n");
        return NULL;
    }
    int i=0;
        while(contact[i] != '\0')
        {
            if(!(contact[i] >= '0' && contact[i] <= '9'))
            {
                printf("Invalid input, Phone number must contain only digits\n");
                return NULL;
            }
            else i++;
        }

    if(contact[0] < '6' || contact[0] > '9')
    {
       printf("Invalid phone number! First digit must be between 6 and 9.\n");
       return NULL;
    }
    else
    {
        
         if(uniqueness(addressBook, contact, "phone") == NULL)
         return NULL;    

        
    }
    return contact;

}


// --------------EMAIL-VALIDATION---------------
char * email_validation(char email[], AddressBook *addressBook)
{
      int i=0;
      if(!(email[i] >= 'a' && email[i] <= 'z'))
      {
        printf("Invalid input , first character must be lowercase alphabet\n");
        return NULL;
      }
      i=1;
      while(email[i] !='\0')
      {

        if(! ((email[i]>='a' && email[i] <='z') ||
             (email[i] >= '0' && email[i] <= '9') ||
              (email[i] == '@') || 
              (email[i] == '.') ))
           {
            printf("Invalid input, invalid characters in email\n");
            return NULL;
           }
        i++;

      }
        
         int len = strlen(email);

        if(len < 4 || strcmp(&email[len - 4], ".com") != 0)
        {
            printf("Invalid input, email must end with .com\n");
            return NULL;
        }
      int adt_cout=0, dot_count=0, adt_first=0, dot_first = 0;
      i=0;
      while(email[i]!='\0')
      {
        if(adt_cout > 1 || dot_count > 1)
        {
            printf("Invalid input , @ and .(dot) can only be present once!\n");
            return NULL;
        }
        if(email[i] == '@')
        {
            adt_first = i;
            adt_cout++;
        }
        if(email[i] == '.')
        {
            dot_first = i;
            dot_count++;
        }
        i++;
      }

      if(adt_cout != 1 || dot_count != 1)
        {
            printf("Invalid input, exactly one @ and one . required\n");
            return NULL;
        }

        if(adt_first > dot_first  )
        {
            printf("Invalid input @ should come first!\n");
            return NULL;
        }



      if((((dot_first - adt_first) - 1 ) < 1))
      {
        printf("Invalid input there should minimun 1 characters between @ and  .(dot)\n");
        return NULL;
      }

      if(email[dot_first + 1] == '\0')
      {
           printf("Invalid input, characters required after .\n");
           return NULL;
      }

       if(uniqueness(addressBook, email, "email") == NULL)
         return NULL; 

      return email;

}

// --------------------SORTING FUNCTIONS---------------------
  void choice_sorting(int num, AddressBook *addressBook)
  {
    if(num < 0 || num >3)
    {
        printf("Invalid choice\n");
        return;
    }
    if(num == 1)
    {
        sort_by_name(addressBook);
    }
    else if(num == 2)
    {
        sort_by_phone(addressBook);
    }
    else sort_by_email(addressBook);

  }
  void sort_by_email(AddressBook *addressBook)
  {

    int size = addressBook->contactCount;
    Contact temp_arr[size];
     Contact *ptr= addressBook->contacts;

    for(int i=0; i<size; i++)
    {
        temp_arr[i]=ptr[i];
    }

    for(int i=0; i<size ; i++)
    {
        for(int j=0; j<size-i-1; j++)
        {
            if(( strcmp(temp_arr[j].email, temp_arr[j+1].email) > 0))
            {
                Contact temp = temp_arr[j];
                temp_arr[j] = temp_arr[j+1];
                temp_arr[j+1] = temp; 
            }
        }
    }

    printf("\nAfter sorting  by email :\n");
    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
     for(int i=0; i<size; i++)
     {
        printf("%-5d %-15s %-15s %-25s\n",i+1, temp_arr[i].name, temp_arr[i].phone, temp_arr[i].email);

     }





  }

  void  sort_by_phone(AddressBook *addressBook)
  {
    int size = addressBook->contactCount;
    Contact temp_arr[size];
     Contact *ptr= addressBook->contacts;

    for(int i=0; i<size; i++)
    {
        temp_arr[i]=ptr[i];
    }

    for(int i=0; i<size ; i++)
    {
        for(int j=0; j<size-i-1; j++)
        {
            if(( strcmp(temp_arr[j].phone, temp_arr[j+1].phone) > 0))
            {
                Contact temp = temp_arr[j];
                temp_arr[j] = temp_arr[j+1];
                temp_arr[j+1] = temp; 
            }
        }
    }

    printf("\nAfter sorting  by phone :\n");
    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
     for(int i=0; i<size; i++)
     {
        printf("%-5d %-15s %-15s %-25s\n",i+1, temp_arr[i].name, temp_arr[i].phone, temp_arr[i].email);

     }



  }

  void  sort_by_name(AddressBook *addressBook)
  {
  
    int size = addressBook->contactCount;
    Contact *ptr = addressBook->contacts;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size-i-1; j++)
        {
            if((strcmp(ptr[j].name , ptr[j+1].name) > 0))
            {
               Contact temp = ptr[j];
               ptr[j] = ptr[j+1];
               ptr[j+1] = temp;  
            }
        }
    }

     printf("After sorting by name :\n");
     printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
     for(int i=0; i<size; i++)
     {
        printf("%-5d %-15s %-15s %-25s\n",i+1, ptr[i].name, ptr[i].phone, ptr[i].email);

     }
  }

// --------------------  DELETE FUNCTIONS    --------------------
void Delete_choice(int num, AddressBook *addressBook)
{
     if(num < 0 || num >3)
    {
        printf("Invalid choice\n");
        return;
    }
    if(num == 1)
    {
        Delete_contact(addressBook , "name");
    }
    else if(num == 2)
    {
        Delete_contact(addressBook , "phone");
    }
    else Delete_contact(addressBook, "email");

}

void Delete_contact(AddressBook *addressBook, char arr_name[])
{
    int dataSize;
     if(strcmp(arr_name, "name") == 0)
     {
        dataSize = sizeof(addressBook->contacts[0].name);
     }
     else if(strcmp(arr_name, "phone") == 0)
     {
        dataSize = sizeof(addressBook->contacts[0].phone);
     }
     else if(strcmp(arr_name, "email") == 0)
     {
        dataSize = sizeof(addressBook->contacts[0].email);
     }
    char data[dataSize];
    int match_count=0;
    int found_match[MAX_CONTACTS];

     printf("Enter the %s:", arr_name);
    scanf("%[^\n]", data);

    clear_buffer();

    match_count = find_matches(addressBook, arr_name , found_match, data);

    if(match_count == 0)
    {
        printf("No contact found!\n");
        return;
    }
    else
    {
        printf("\n-------Found %d matching contacts-------\n", match_count);
    }

    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
    for(int i=0; i<match_count; i++)
    {
        printf("%-5d %-15s %-15s %-25s\n", i+1, addressBook->contacts[found_match[i]].name, addressBook->contacts[found_match[i]].phone, addressBook->contacts[found_match[i]].email);
    }

    printf("Enter the S.No of the contact you want to delete (1 to %d, or 0 to Exit):\n", match_count);
    int delete_index=-1;
    scanf("%d", &delete_index);
    clear_buffer();

    if(delete_index == 0)
    {
        return;
    }

    if(delete_index <1 || delete_index > match_count)
    {
        printf("Invalid S.no\n");
        return;
    }

    printf("Are you sure you want to delete contact details of %s  %s %s :",addressBook->contacts[found_match[delete_index-1]].name, addressBook->contacts[found_match[delete_index-1]].phone, addressBook->contacts[found_match[delete_index-1]].email);
    printf("\nEnter Y(yes) or N(no)\n");
    char ans;
    scanf("%c", &ans);
    clear_buffer();

    if(ans == 'y' || ans == 'Y')
        {
            for(int i = found_match[delete_index-1]; i<addressBook->contactCount-1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i+1];
            }
            addressBook->contactCount--;
            printf("Deleted contact succesfully!\n");
        }
        else if(ans == 'n' || ans == 'N')
        {
            printf("Deletion cancelled!\n");
        }
        else
        {
            printf("Invalid answer!\n");
            printf("Deletion cancelled!\n");
        }
   
    






    
}


// -------------------- EDIT FUNCTIONS   --------------------
void Edit_choice(int num, AddressBook *addressBook)
{
     if(num < 0 || num >3)
    {
        printf("Invalid choice\n");
        return;
    }
    if(num == 1)
    {
        edit_contact(addressBook , "name");
    }
    else if(num == 2)
    {
        edit_contact(addressBook , "phone");
    }
    else edit_contact(addressBook, "email");

}
void  edit_contact(AddressBook *addressBook, char arr_name[])
{
      int nameSize , phoneSize, emailSize;

    

        

    nameSize = sizeof(addressBook->contacts[0].name);
    phoneSize = sizeof(addressBook->contacts[0].phone);
    emailSize = sizeof(addressBook->contacts[0].email);
   
    char temp_name[nameSize];
    char temp_phone[phoneSize];
    char temp_email[emailSize];

    int match_count=0;
    int found_match[MAX_CONTACTS];
    
    if(strcmp(arr_name, "name") == 0)
    {
     printf("Enter the name:");
    scanf("%[^\n]", temp_name);

    clear_buffer();

    match_count = find_matches(addressBook, "name" , found_match, temp_name);

    }
    else if(strcmp(arr_name, "phone")==0)
    {
    printf("Enter the  phone number:");
    scanf("%[^\n]", temp_phone);

    clear_buffer();

    match_count = find_matches(addressBook, "phone" , found_match, temp_phone);

    }
    else if(strcmp(arr_name, "email")==0)
    {
    printf("Enter the  email:");
    scanf("%[^\n]", temp_email);

    clear_buffer();

    match_count = find_matches(addressBook, "email" , found_match, temp_email);

    }

    

    if(match_count == 0)
    {
        printf("No contact found!\n");
        return;
    }
    else
    {
        printf("\n-------Found %d matching contacts-------\n", match_count);
    }

    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
    for(int i=0; i<match_count; i++)
    {
        printf("%-5d %-15s %-15s %-25s\n", i+1, addressBook->contacts[found_match[i]].name, addressBook->contacts[found_match[i]].phone, addressBook->contacts[found_match[i]].email);
    }

    printf("Enter the S.No of the contact you want to edit (1 to %d, or 0 to Exit):\n", match_count);
    int edit_index=-1;
    scanf("%d", &edit_index);
    clear_buffer();

    if(edit_index == 0)
    {
        return;
    }

    if(edit_index <1 || edit_index > match_count)
    {
        printf("Invalid S.no\n");
        return;
    }

    printf("Enter what you want to edit:\n");

    int choice = get_choice_input("Edit");

    if(choice == 0)
    {
        return;
    }
    else if(choice == 1)
    {
            char new_name[nameSize];

        char * res = get_input(new_name,  nameSize,  "name" , nameValidation, addressBook);

        if(res == NULL) return;
        else
        {
            strcpy(addressBook->contacts[found_match[edit_index-1]].name , new_name);
            printf("Name updated sucessfully!\n");
        }


    }
    else if(choice == 2)
    {
        char new_phone[phoneSize];
           

        char * res = get_input(new_phone,  phoneSize,  "phone" , contact_validation, addressBook);

        if(res == NULL) return;
        else
        {
            strcpy(addressBook->contacts[found_match[edit_index-1]].phone , new_phone);
            printf("Phone No. updated sucessfully!\n");
            return;
        }

    }
    else if(choice == 3)
    {
         char new_email[emailSize];
           

        char * res = get_input(new_email,  emailSize,  "email" , email_validation, addressBook);

        if(res == NULL) return;
        else
        {
            strcpy(addressBook->contacts[found_match[edit_index-1]].email , new_email);
            printf("Email. updated sucessfully!\n");
            return;
        }

    }



    
  
     




}



//  --------------------  SEARCH FUNCTION  + MATCH FUNCTION  --------------------
void Search_choice(int num,AddressBook* addressBook)
{
     if(num < 0 || num >3)
    {
        printf("Invalid choice\n");
        return;
    }
    if(num == 1)
    {
        search_by_name(addressBook);
    }
    else if(num == 2)
    {
        search_by_phone(addressBook);
    }
    else search_by_email(addressBook);

}



int find_matches(AddressBook *addressBook, char str[], int *found_match, char data[] )
{
    int size = addressBook->contactCount;
    int count=0;

    if(strcmp(str, "name") == 0)
    {
        for(int i=0; i<size; i++)
      {
        if((strcmp(addressBook->contacts[i].name, data)) == 0)
        {
            found_match[count] = i;
            count++;
        }
      }
    }
    else if(strcmp(str, "phone") == 0)
    {
         for(int i=0; i<size; i++)
       {
        if((strcmp(addressBook->contacts[i].phone, data)) == 0)
        {
            found_match[count] = i;
            count++;
        }
       }

    }
    else 
    {
         for(int i=0; i<size; i++)
      {
        if((strcmp(addressBook->contacts[i].email, data)) == 0)
        {
            found_match[count] = i;
            count++;
        }
      }
    }
    

    return count;
}

void  search_by_name(AddressBook *addressBook)
{
    int  nameSize = sizeof(addressBook->contacts[0].name);
    
    char temp_name[nameSize];
    int match_count=0;
    int found_match[MAX_CONTACTS];

    printf("Enter the name:");
    scanf("%[^\n]", temp_name);

    clear_buffer();

    match_count = find_matches(addressBook, "name" , found_match, temp_name);

    if(match_count == 0)
    {
        printf("No contact found!\n");
        return;
    }
    else
    {
        printf("\n-------Found %d matching contacts-------\n", match_count);
    }

    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
    for(int i=0; i<match_count; i++)
    {
        printf("%-5d %-15s %-15s %-25s\n", i+1, addressBook->contacts[found_match[i]].name, addressBook->contacts[found_match[i]].phone, addressBook->contacts[found_match[i]].email);
    }

    


    






}

void  search_by_phone(AddressBook *addressBook)
{
     int  phoneSize = sizeof(addressBook->contacts[0].phone);
   
    char temp_phone[phoneSize];
    int match_count=0;
    int found_match[MAX_CONTACTS];

    printf("Enter the phone:");
    scanf("%[^\n]", temp_phone);

    clear_buffer();

    match_count = find_matches(addressBook, "phone" , found_match, temp_phone);

    if(match_count == 0)
    {
        printf("No contact found!\n");
        return;
    }
    else
    {
        printf("\n-------Found %d matching contacts-------\n", match_count);
    }

    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
    for(int i=0; i<match_count; i++)
    {
        printf("%-5d %-15s %-15s %-25s\n", i+1, addressBook->contacts[found_match[i]].name, addressBook->contacts[found_match[i]].phone, addressBook->contacts[found_match[i]].email);
    }

}

void  search_by_email(AddressBook *addressBook)
{
     int  emailSize = sizeof(addressBook->contacts[0].email);
   
    char temp_email[emailSize];
    int match_count=0;
    int found_match[MAX_CONTACTS];

    printf("Enter the email:");
    scanf("%[^\n]", temp_email);

    clear_buffer();

    match_count = find_matches(addressBook, "email" , found_match, temp_email);

    if(match_count == 0)
    {
        printf("No contact found!\n");
        return;
    }
    else
    {
        printf("\n-------Found %d matching contacts-------\n", match_count);
    }

    printf("%-5s %-15s %-15s %-25s\n","S.No", "Name", "Phone", "Email");
    for(int i=0; i<match_count; i++)
    {
        printf("%-5d %-15s %-15s %-25s\n", i+1, addressBook->contacts[found_match[i]].name, addressBook->contacts[found_match[i]].phone, addressBook->contacts[found_match[i]].email);
    }

}

  

           
    

