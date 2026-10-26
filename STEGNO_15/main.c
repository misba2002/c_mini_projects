#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

OperationType check_operation_type(char *);

int main(int argc, char *argv[])             
{
    // step1 -> check  check_operation_type(argv[1]) is returning e_encode or not
     OperationType op_res = check_operation_type(argv[1]);
            // true -> EncodeInfo encInfo;
            if(op_res == e_encode)
            {
                if(argc<4)
                {
                    printf("ERROR:Please provide vailid number of input argummets!\n");
                    return 0;
                }
                EncodeInfo encInfo;
               Status enc_arg = read_and_validate_encode_args(argv, &encInfo);
               if(enc_arg==e_success)
               {
                printf("All input arguments are validated\n");
                printf("\n");
                 if(do_encoding(&encInfo) == e_success)
                 {
                    printf("\nENCODING OPERATION SUCCESSFULLY DONE........ \n");
                    return 0;


                 }
                 else{printf("exiting encoding operation....\n");}
               }
               else
               {
                printf("Input argument validation failed!exiting encoding operation...");
                return 0;
               }

            }
         
            //step 1 -> check read_and_validate_encode_args(argv, &encInfo) is returning e_success or not
                    // e_failure -> print error msg and stop the program
                    // e_success -> print succes msg goto step
                
            //step 2 -> check do_encoding(&encInfo) is success or not
           else if(op_res == e_decode)
            {
                if(argc<3)
                {
                    printf("ERROR:Please provide vailid number of input argummets!\n");
                }
                EncodeInfo encInfo;
                if(read_and_validate_decode_args(argv, &encInfo)==e_failure)
                {
                    return e_failure;
                }
                printf("ALL inputs are validated\n");
                if(do_decoding(&encInfo)==e_failure)
                {
                    printf("Exiting decoding operation..\n");
                    return e_failure;
                }



            }
                    // e_failure -> print error msg and stop the program
                    // e_success -> print success msg and stop
            if(op_res == e_unsupported)
            {
                return 0;
            }
}

OperationType check_operation_type(char *symbol)
{
    // step 1 -> check symbol is -e or not
        // yes -> return e_encode
    // step 2 -> check symbol is -d or not
        //yes -> return e_decode 

        if(strcmp(symbol, "-e") == 0)
        {
            printf("you have selected encoding operation\n");
            return e_encode;
        }
        else if(strcmp(symbol, "-d")==0)    
        {
            printf("you have selected decoding operation\n");
            return e_decode;
        }
        else
        {
            printf("invalid operation! please add option -e for encoding or -d for decoding\n");
            return e_unsupported;
        }
        // step 3 -> return e_unsupported
}

  

    
