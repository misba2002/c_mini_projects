#include <stdio.h>
#include<string.h>
#include"common.h"
#include "encode.h"
#include "types.h"
#include "decode.h"


// global variable to save decode extension size;
long int size;
char stego_image_fname[256];

/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(char *argv[], EncodeInfo *encInfo)
{
    printf("Validating input arguments.......\n");
    if(strstr(argv[2], ".bmp")==NULL)
    {
        printf("Invalid source file name extension,the filename should end with (.bmp) extension\n");
        return e_failure;
       
    }
    else
    {
         printf("source image file name has correct (.bmp) extension\n");
         encInfo -> src_image_fname = argv[2];
        
    }

    if(argv[3]==NULL)
    {
        strcpy(stego_image_fname,"output");
    }
    else
    {
       char *extr= strrchr(argv[3],'.');
       if(extr!=NULL)
       {
        *extr='\0';
       }
        strcpy(stego_image_fname,argv[3]);   
    }
    return e_success;

   
}
Status open_output_file(EncodeInfo *encInfo)
{
    // output  file


    encInfo->fptr_stego_image = fopen(stego_image_fname, "wb");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", stego_image_fname);

        return e_failure;
    }
   return e_success;
}


Status open_de_files(EncodeInfo *encInfo)
{
    
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    // encInfo->fptr_secret = fopen(encInfo->secret_fname, "wb");
    // // Do Error handling
    // if (encInfo->fptr_secret == NULL)
    // {
    //     perror("fopen");
    //     fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    //     return e_failure;
    // }


    // No failure return e_success
    return e_success;
}
/* Perform the decoding */
Status do_decoding(EncodeInfo *encInfo)
{
    printf("\nDecoding operation started.....\n");
    if(open_de_files(encInfo)==e_failure)
    {
        return e_failure;
    }

    if(decode_magic_string(MAGIC_STRING, encInfo)==e_failure)
    {
        return e_failure;
    }

    if(decode_secret_file_extn_size(encInfo)==e_failure)
    {
        return e_failure;
    }

     if(decode_secret_file_extn(size ,encInfo)==e_failure)
     {
        return e_failure;
     }

     if(open_output_file(encInfo)==e_failure)
     {
        return e_failure;
     }

     if(decode_secret_file_size(encInfo->size_secret_file, encInfo)==e_failure)
     {
        return e_failure;
     }

     if(decode_secret_file_data(encInfo)==e_failure)
     {
       
        return e_failure;
     }


    



}







/* get Magic String */
Status decode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
      fseek(encInfo->fptr_src_image, 54, SEEK_SET);

     char buffer[strlen(MAGIC_STRING)];
        // step 2 -> call decode_byte_to_lsb(magic_string[i], buffer);
            for(int i=0; i<strlen(MAGIC_STRING); i++)
            {
                size_t n=fread(buffer,8,1,encInfo->fptr_src_image);
                if(n!=1)
                {
                    printf("Unable to read[DECODE MAGIC STRING FUNCTION : decode.c file]\n");
                    return e_failure;
                }
                if(decode_magic_byte_to_lsb(MAGIC_STRING[i] , buffer)==e_failure)
                {
                return e_failure;
                }
                

            }
            printf("Magic string decoded and matched succesfully.......\n");
            return e_success;

        
            

          
            
            
          
}

/*decode extension size*/

Status decode_secret_file_extn_size(EncodeInfo *encInfo)
{
    char buffer[32];

   if( fread(buffer,32,1,encInfo->fptr_src_image) !=1)
   {
     printf("Error reading 32 bytes of data function[ decode_secret_file_extn_size :file:decode.c]\n");
     return e_failure;
   }
   if(decode_size_to_lsb(&size, buffer)==e_failure)
   {
    return e_failure;
   }
   return e_success;



}

/* decode secret file extenstion */
Status decode_secret_file_extn(int size, EncodeInfo *encInfo)
{
    char extn_secret_file[5];
    char buffer[8];
    for(int i=0; i<size; i++)
    {
        if(fread(buffer,8,1,encInfo->fptr_src_image)!=1)
        {
            printf("Unable to read 32 bytes function :[decode_secret_file_extn, file:decode.c]\n");
            return e_failure;
        }
        if(decode_byte_to_lsb(&extn_secret_file[i], buffer)==e_failure)
        {
            printf("Unable to decode extension data  function :[decode_secret_file_extn, file:decode.c]\n");
            return e_failure;
        }
    }
    extn_secret_file[4]='\0';
    strcpy(encInfo->extn_secret_file, extn_secret_file);
    printf("extension is %s\n",encInfo->extn_secret_file);
    strcat(stego_image_fname,encInfo->extn_secret_file);
    printf("output file name is %s\n",stego_image_fname);

    return e_success;
}

/* decode secret file size */
Status decode_secret_file_size(long int file_size, EncodeInfo *encInfo)
{
    char buffer[32];

    if(fread(buffer,32,1,encInfo->fptr_src_image)!=1)
    {
        printf("Error in reading 32 bytes function[decode_secret_file_size:file decode.c]\n");
        return e_failure;
    }
    if(decode_size_to_lsb( &file_size, buffer)==e_failure)
    {
        printf("Error in decoding size .function[decode_secret_file_size:file decode.c]\n");
        return e_failure;
    }
    printf("Estimated filesize is %ld\n", file_size);
    encInfo->size_secret_file=file_size;
    return e_success;

    
   
}

/* decode secret file data*/
Status decode_secret_file_data(EncodeInfo *encInfo)
{
    
    char buffer[8];
    char secret_buffer;
    for(int i=0; i<encInfo->size_secret_file; i++)
    {

       if(fread(buffer,8,1,encInfo->fptr_src_image)!=1)
        {
            printf("Error reading secret data function[ decode_secret_file_data]file:decoder.c\n");
            return e_failure;
        }
        
        if(decode_byte_to_lsb(&secret_buffer,buffer)==e_failure)
        {
           
            printf("Error in decoding secret data function[ decode_secret_file_data]file:decoder.c\n");
            return e_failure;
        }
        if(fwrite(&secret_buffer,1,1,encInfo->fptr_stego_image)!=1)
        {
            printf("Error in writing decoded secret data  function[ decode_secret_file_data]file:decoder.c\n");
            return e_failure;
        }
    } 
    printf("\nSECRET DATA DECODED SUCCESSFULLY!\n");
    return e_success;

}

/* decode a byte into LSB of image data array */
Status decode_byte_to_lsb(char *data, char *image_buffer)
{
    
    unsigned char decoded=0;
   
    for(int i=7; i>=0; i--)
    {
        decoded = (decoded | ((image_buffer[i] &(1u))<<i));
       
    }


    *data=decoded;
     return e_success;
        
    
   
   
    
    
    
     
   
    

}
Status decode_magic_byte_to_lsb(char data, char *image_buffer)
{
    unsigned char decoded=0;
    
    for(int i=7; i>=0; i--)
    {
        decoded = (decoded | ((image_buffer[i] &(1u))<<i));
       
    }

    if(data==decoded)
    {
        return e_success;
    }
    printf("Magic string did not match!");
    return e_failure;
     
   
    

}

// decode a size to lsb
Status decode_size_to_lsb(long int *size, char *imageBuffer)
{
    int value=0;
    for(int i=31; i>=0; i--)
    {
        value = value | ((imageBuffer[i] & 1u) << i);

    }
    if(value<=0)
    {
        return e_failure;
    }

        *size=value;
        return e_success;
    
    
}
