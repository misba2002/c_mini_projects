#include<stdio.h>

int main()
{
    char game_aff='n',  play_again='n';
    int user_ans=0, correct_count=0, total_question=5;
    char arr[5]={'n','n','n','n','n'};
    

    printf("====QUIZ GAME====");
    printf("\nInstructions:\n1.There are 5 questions\n2.Each questions has 4 options\n3.Enter correct options\n");

    printf("=================");
    printf("\nAre you ready (y/n): ");
    scanf("%c", &game_aff);

    if(game_aff=='n')
    {
        printf("Ok! see you later aligator.\n");
        return 0;
    }

     int question_num=1;

    do
    {
       
        switch(question_num)
        {
            case 1:printf("\nQ1).Which loop is guaranteed to execute at least once?\n");
                   printf("\n1) for 2) while 3) do...while 4) None\n");

                  do
                  {
                   printf("==>");
                   scanf("%d", &user_ans);

                   if(user_ans<=0 || user_ans>=5) printf("Invalid input! please type correct option!: \n");
                   else break;  

                  }while(user_ans<=0 || user_ans>=5);

                  if(user_ans==3)
                  {
                     arr[0]='y';
                     printf("correct answer! good..\n");
                  } 
                  else 
                  {
                    arr[0]='n';
                    printf("wrong answer\n");

                  }
                  

                   question_num++;
                   break;


                   
                  
                  
            
            case 2:printf("\nQ2).Which operator gives the remainder?\n");
                   printf("\n1) '/' 2) '%%'  3) '//'  4) mod\n");

                  do
                  {
                   printf("==>");
                   scanf("%d", &user_ans);

                   if(user_ans<=0 || user_ans>=5) printf("Invalid input! please type correct option!: \n");
                   else break;  

                  }while(user_ans<=0 || user_ans>=5);

                  if(user_ans==2)
                  {
                     arr[1]='y';
                     printf("correct answer! \n");
                  } 
                  else
                  {
                      arr[1]='n';
                     printf("wrong answer\n");
                  }
                  

                   question_num++;
                   break;
            case 3:printf("\nQ3).Which statement immediately exits a loop?\n");
                   printf("\n1) continue 2) exit 3) break 4) return 1\n");

                  do
                  {
                   printf("==>");
                   scanf("%d", &user_ans);

                   if(user_ans<=0 || user_ans>=5) printf("Invalid input! please type correct option!: \n");
                   else break;  

                  }while(user_ans<=0 || user_ans>=5);

                  if(user_ans==3)
                  {
                      arr[2]='y';
                     printf("correct answer! good going\n");
                  } 
                  else 
                  {
                   arr[2]='n';
                  printf("wrong answer\n");
                  }

                   question_num++;
                   break;

            case 4:printf("\nQ4).Which declaration is correct for an array of 10 integers?\n");
                   printf("\n1) int arr[10]; 2) array int[10]; 3) int arr(); 4) int(10) arr;\n");

                  do
                  {
                   printf("==>");
                   scanf("%d", &user_ans);

                   if(user_ans<=0 || user_ans>=5) printf("Invalid input! please type correct option!: \n");
                   else break;  

                  }while(user_ans<=0 || user_ans>=5);

                  if(user_ans==1)
                  {
                      arr[3]='y';
                     printf("correct answer! one more to go!\n");
                  } 
                  else
                  {
                     arr[3]='n';
                    printf("wrong answer\n");
                  } 

                   question_num++;
                   break;

            case 5:printf("\nQ5).What does this print?\nprintf(\"%%d\", 7 / 2);\n");
                   printf("\n1) 3.5 2) 4 3) 5.0 4) 3\n");

                  do
                  {
                   printf("==>");
                   scanf("%d", &user_ans);

                   if(user_ans<=0 || user_ans>=5) printf("Invalid input! please type correct option!: \n");
                   else break;  

                  }while(user_ans<=0 || user_ans>=5);

                  if(user_ans==4)
                  {
                    arr[4]='y';
                    printf("correct answer! Execllent! \n");
                  } 
                  else
                  {
                    arr[4]='n';
                    printf("wrong answer\n");
                  } 

                   question_num++;
                   break;
        
        
            default:
                   for(int i=0; i<5; i++)
                   {
                    if(arr[i]=='y') correct_count++;
                   }
                   printf("\nFinal score is %d/%d\n", correct_count,total_question);
                   printf("Do you want to play again(y/n)?");
                   scanf(" %c", &play_again);
                   if(play_again=='y')
                   {
                     question_num=1;
                     correct_count=0;
                        for(int i=0; i<5; i++)
                        {
                            arr[i]=='n';
                        }
                   } 
                   else 
                   {
                    question_num++;
                    
                    printf("\nOk! Time to take rest ~~ bye!\n");
                    break;
                   }
        }

    }while(question_num<=6);

     


   

}