#include<stdio.h>
#include "input.h"
#include "contact.h"

char * get_input(char data[], int size, char *arr_name, char * (* validate) (char str[],AddressBook *addressBook),AddressBook *addressBook)
{
    int count = 0;
    char format[20];
    char * res = NULL;

    sprintf(format, "%%%d[^\n]" , size-1);

    do
    {
        printf("Enter your %s : ", arr_name);

        if((scanf(format, data) == 0))
        {
            getchar();
            printf("Invalid input , %s can't be empty.\n", arr_name);
            res = NULL;
            count++;
            continue;
        }
        else
        {
            int ch = getchar();
            if(ch != '\n')
            {
                printf("Invalid input , %s is too long.\n", arr_name);
                while( ch != '\n')
                {
                    ch = getchar();
                }
                count++;
                res= NULL;
            }
            else
            {
                res = validate(data, addressBook);
                count++;

            }
        }
    }while(res == NULL && count < 3);

    if( res!= NULL)
    {
        printf("Valid %s\n", arr_name);
        return res;
    }
    else
    {
        printf("Too many attempts\n");
        return NULL;
    }
    
}


  int get_choice_input(char str[])
  {
    int res, count=0;
    do
    {
        printf("\n0. Exit\n1.%s by name\n2.%s by phone\n3.%s by email\nEnter your choice (1 to 3 or 0 to exit): ", str, str, str);
        scanf("%d", &res);
        int ch = getchar();
        
        while(ch != '\n')
        {

            ch = getchar();
        }
        
        if(res == 0)
        {
            return 0;
            
        }
        if(res <=3 && res >= 0)
        {
             count++;
            return res;
           
        }
        else
        {
            printf("Invalid choice! please enter choice between 1 to 3 or 0 to exit\n");
            count++;

        }
    }while(count < 3);

    if(count == 3 )
    {
        printf("Too many attempts!\n");
        return 0;
    }
    
  }

  
