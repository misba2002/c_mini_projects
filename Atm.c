#include<stdio.h>

int main()
{
    int balance, depo_money, draw_money, origanlpin=1234, pincount=3, userpin, user_option;
    
    // ASK USER FOR PIN ONLY 3 ATTEMPTS POSSIBLE
    while(pincount>0)
    {
   
    printf("Enter the pin: ");
    scanf("%d", &userpin);
    
     if(userpin!=origanlpin)
    {
        printf("incorrect pin !try again...\n");
        pincount--;
    }
    else
    {
        pincount=-1;
        printf("Login Succesfull!\n");
        balance=1000;
    }


        
    if(pincount==0)
    {
        printf("Too many attempts: exiting\n");
        return 0;
    }

    }

    do
    {
        printf("\n----ATM MENU-----\n");
        printf("1.Check balance\n2.Deposit money\n3.Withdraw money\n4.Exit\n");
        scanf("%d", &user_option);

        switch(user_option)
        {
            case 1:
                  printf("Your current balance is %d\n", balance);
                  break;

            case 2:
                  printf("Enter the money to be deposited: ");
                  scanf("%d", &depo_money);
                  balance=balance+depo_money;
                  printf("\nYour updated balance is : %d\n", balance);
                  break;
                  
            case 3: 
                  printf("Enter the money to be withdrawn :");
                  scanf("%d", &draw_money);
                  if(draw_money>balance)
                  {
                    printf("Insuffienct money, Please check your balance!\n");
                  } 
                  else
                  {
                    balance=balance-draw_money;
                    printf("\nYour updated balance is : %d\n", balance);
                  } 
                  break; 
                  
            case 4:
                  printf("Thank you! please visit again.\n");
                  return 0;
                  break;

            default:
                  printf("Invalid input!\n");
                  break;      

        }

    }while(user_option>0 && user_option<=4);


    

    
      

    


}