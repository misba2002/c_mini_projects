#include <stdio.h>
#include<string.h>
#include"common.h"
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

uint get_file_size(FILE *fptr)
{

    // Find the size of secret file data
    uint secret_file_size;
    fseek(fptr,0,SEEK_END);
    secret_file_size=ftell(fptr);
    printf("Secret file size is %u bytes\n", secret_file_size);
    // return secret file size
    rewind(fptr);
    return secret_file_size;
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    printf("\nValidating input arguments ......\n");
    // step 1 -> check argv[2] is having .bmp or not
    
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
            // no -> print error msg and return e_failure
            // yes -> encInfo -> src_image_fname = argv[2]; goto step 2.
    
    // step 2 -> check argv[3] is having extn is there or not
          void *ext_ptr = strchr(argv[3],'.');
          if(ext_ptr!=NULL && (strcmp(ext_ptr,".txt")==0 || strcmp(ext_ptr,".c")==0 || strcmp(ext_ptr,".csv")==0))
          {
            printf("secret file has an  extension \n");
            encInfo->secret_fname=argv[3]; 
            strcpy(encInfo->extn_secret_file, ext_ptr);
             
          }
          else{
             printf("Invalid input , secret file has no extension ,please provide some valid extension\n");
             return e_failure;

          }
        
            // no -> print error msg and return e_failure
            // yes -> encInfo -> secret_fname = argv[3]; and store extn into encInfo -> extn_secret_file goto step 3.

    // step 3 -> check argv[4] is NULL or not
            if(argv[4]==NULL)
            {
                encInfo->stego_image_fname="stego.bmp";
            }
            else
            {
                if(strstr(argv[4], ".bmp")==NULL)
                {
                    printf("Invalid output file name extension,the filename should end with (.bmp) extension\n");
                    return e_failure;
                
                }
                else
                {
                    printf("output image file name has valid (.bmp) extension\n");
                    encInfo -> stego_image_fname = argv[4];
                    
                }

            }

            // yes -> encInfo -> stego_image_fname = "stego.bmp"
            // no -> check argv[4] is having .bmp or not
                        // no -> print error msg and return e_failure
                        // yes -> encInfo -> stego_image_fname = argv[4]

     return e_success;
}

Status open_files(EncodeInfo *encInfo)
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
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status load_secret_data(EncodeInfo *encInfo)
{
    if(encInfo->size_secret_file>=100)
    {
        printf("Secret data is too big\n");
        return e_failure;
    }
    for(int i=0; i<encInfo->size_secret_file; i++)
    {
        if(fread(&encInfo->secret_data[i],1,1,encInfo->fptr_secret)!=1)
        {
            printf("Error loading secret code inside secret array[Function:load_secret_data]\n");
            return e_failure;
        }
    }
    encInfo->secret_data[encInfo->size_secret_file] = '\0';
    return e_success;
  
}

Status check_capacity(EncodeInfo *encInfo)
{
    
    // step 1 -> encInfo -> image_capacity = call get_image_size_for_bmp(encInfo -> fptr_src_image);
    encInfo-> image_capacity= get_image_size_for_bmp(encInfo->fptr_src_image);


    // step 2 -> encInfo -> size_secret_file = call get_file_size(encInfo -> fptr_secret);
    encInfo->size_secret_file= get_file_size(encInfo->fptr_secret);

    

    // step 3 -> check encInfo -> image_capacity > 16 + 32 + (strlen(encInfo -> extn_secret_file)* 8) + 32 + (encInfo -> size_secret_file *8);
      if(encInfo->image_capacity > 16+ 32 + (strlen(encInfo ->extn_secret_file)* 8) + 32 + (encInfo -> size_secret_file *8)) 
      {
        printf("source file has enough capacity to encode the secret data\n");
        return e_success;
      }
      else
      {
        printf("source file doesn't has enough capacity to encode the secret data\n");
        return e_failure;
      }
                // yes -> return e_success;
                // no -> return e_failure;
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    
    char buffer[54];
    char *buffer_ptr=buffer;
    // step 1 -> rewind src file pointer to 0th pos
     rewind(fptr_src_image);

    
    // step 2 -> read 54 bytes of header from src file
    fread(buffer,54,1,fptr_src_image);
    // for(int i=0; i<54; i++)
    // {
    //   printf("\ndata read from the header  is  %x\n", buffer[i]);
    // }
   
    // step 3 -> write 54 bytes of header to dest file
    size_t n= fwrite(buffer_ptr,54,1,fptr_dest_image);
    if(n==1)
    {
        printf("54 bytes of header copied succesfully!\n");
        printf("after header copy source file pointer is pointing to offset %lu\n",ftell(fptr_src_image));
        return e_success;
    }
    else
    {
        printf("Unable to copy 54 bytes of header!\n"); 
        return e_failure;
    }
     // repeat this for strlen(magic_string) from step


}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
   
            char buffer[8];
        // step 2 -> call encode_byte_to_lsb(magic_string[i], buffer);
            for(int i=0; i<strlen(MAGIC_STRING); i++)
            {
                size_t n=fread(buffer,8,1,encInfo->fptr_src_image);
                if(n!=1)
                {
                    printf("Unable to read[ENCODE MAGIC STRING FUNCTION : encode.c file]\n");
                    return e_failure;
                }
                if(encode_byte_to_lsb(MAGIC_STRING[i] , buffer)==e_failure)
            {
                return e_failure;
            }
            if(fwrite(buffer,8,1,encInfo->fptr_stego_image)!=1)
            {
                printf("Error writing encode magic string in output file[Function: encode_magic_string()]\n");
                return e_failure;  

                }

            }
        
            

            // step 3 -> write the 8 bytes of encoded buffer to dest file
            
            
            printf("Magic string encoded succesfully!\n");
                return e_success;

}       

  

           
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char buffer[32];

   
    printf("Before reading 32 byte the source file pointer points to offset %lu\n", ftell(encInfo->fptr_src_image));
    // step 1 -> read 32 bytes from src file
    if(fread(buffer,32,1,encInfo->fptr_src_image)==1)
    {
        printf("32 bytes read from the source file  succesfully \n");
    }
   

    // step 2 -> call encode_size_to_lsb(size, buffer);
    if(encode_size_to_lsb(size, buffer)==e_failure)
    {
        return e_failure;
    }
    
     printf("After reading 32 byte the source file pointer points to offset %lu\n", ftell(encInfo->fptr_src_image));
    

    if(fwrite(buffer,32,1,encInfo->fptr_stego_image)!=1)
    {
        return e_failure;
    }
    else
    {
         printf("After encoding 32 byte ie size of secret extension o/p file pointer points to offset %lu\n", ftell(encInfo->fptr_stego_image));
    
        printf("\nsecret file extension size succesfully encoded in the output file\n");
        e_success;
    }


    // step 3 -> write the 8 bytes of encoded buffer to dest file
}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    
    char buffer[8];

    // step 1 -> read 8 bytes from src file
   

   
    // step 2 -> call encode_byte_to_lsb(file_extn[i], buffer);
     
     for(int i=0; i<strlen(file_extn); i++)
     {
            if(fread(buffer,8,1,encInfo->fptr_src_image)!=1)
            {
                printf("Error while reading data from source file [Function :encode_secret_file_extn]\n");
                return e_failure;
            
            }
         if(encode_byte_to_lsb(file_extn[i], buffer)==e_failure)
         {
            printf("Error while encoding data [FUNCTION : encode_secret_file_extn]\n");
            return e_failure;

         }

        if(fwrite(buffer,8,1,encInfo->fptr_stego_image)!=1)
        {
            printf("error while writing encoded data in output file[FUNCTION :encode_secret_file_extn]\n");
            return e_failure;
        }
        

     }
      printf("encoded secret_file_extn succesfully in output file\n");
      return e_success;

    

    // step 3 -> write the 8 bytes of encoded buffer to dest file

            // repeat this for strlen(file_extn) from step1
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];

    // step 1 -> read 32 bytes from src file
    if(fread(buffer,32,1,encInfo->fptr_src_image)!=1)
    {
        printf("Error in reading data from source file function[encode_secret_file_size]\n");
        return e_failure;
    }

     // step 2 -> call encode_size_to_lsb(size, buffer);
     if(encode_size_to_lsb(file_size,buffer)==e_failure)
     {
        printf("Error in encoding secret file size function[encode_secret_file_size]\n");
        return e_failure;
     }

   
    

    // step 3 -> write the 8 bytes of encoded buffer to dest file
    if(fwrite(buffer,32,1,encInfo->fptr_stego_image)!=1)
    {
        printf("Error in writing  encoding secret file size in output file function[encode_secret_file_size]\n");
        return e_failure;
 
    }
    else
    {
         printf("succesfully encoded secret file size in the output file!\n");
         return e_success;
    }

   
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    // store the secret data into structure mem
     char buffer[8];

     for(int i=0; i<encInfo->size_secret_file; i++)
     {
        if(fread(buffer,8,1,encInfo->fptr_src_image)!=1)
        {
            printf("Error in reading data function[ encode_secret_file_data]\n");
            return e_failure;

        }

         if(encode_byte_to_lsb(encInfo -> secret_data[i], buffer)==e_failure)
         {
             printf("Error in encoding secret data : refrence->function[ encode_secret_file_data]\n");
            return e_failure;


         }

         if(fwrite(buffer,8,1,encInfo->fptr_stego_image)!=1)
         {
             printf("Error in encoding secret data inside output file : refrence->function[ encode_secret_file_data]\n");
             return e_failure;
         }

     }

     printf("SECRET data succesfully encoded in output file\n");
     return e_success;

    // step 1 -> read 8 bytes from src file

    // step 2 -> call encode_byte_to_lsb(encInfo -> secret_data[i], buffer);

    // step 3 -> write the 8 bytes of encoded buffer to dest file

            // repeat this for encInfo -> size_secret_file from step1
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    // logic
     int ch;
      unsigned char byte;
     while((ch=getc(fptr_src))!=EOF)
     {
         byte = (unsigned char)ch;
        if(fwrite(&byte, 1, 1, fptr_dest)!=1)
        {
            printf("Error in copying remaining source data in output file\n");
            return e_failure;
        }

     }
      if (ferror(fptr_src))
    {
        printf("Error reading remaining source image data\n");
        return e_failure;
    }

    printf("Copied remaining source image data successfully\n");
    return e_success;
     
    // return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    // logic
    
    for(int i=0; i<8; i++)
    {
      image_buffer[i] =( image_buffer[i] & (~1u) | (((unsigned char)data >> i) & 1u));
    }

    unsigned char decoded = 0;

    for (int i = 0; i < 8; i++)
    {
        decoded |= (image_buffer[i] & 1u) << i;
    }

    //    printf("Decoded character: %c\n", decoded);
    if(decoded==data)
    {
        // printf("1 byte encoded succesfully!\n");
        return e_success;
    }
    else
    {
        printf("unbale to encode 1 byte !\n");
        return e_failure;
    }

}

Status encode_size_to_lsb(int size, char *imageBuffer)
{
    // logic
   
    for(int i=0; i<32; i++)
    {
       imageBuffer[i]= (imageBuffer[i] & (~1u)) |   (((unsigned int)size >> i) & 1u);
    }

    unsigned int decoded =0;

    for(int i=0; i<32; i++)
    {
        decoded = decoded | ((imageBuffer[i]& 1u) << i);
    }

    if(decoded==size)
    {
        printf("encoded 32 bytes!\n");
        return e_success;
    }
    else
    {
        printf("unable to encode size [FUNCTION :encode_size_to_lsb]\n");
        return e_failure;
    }
}

Status do_encoding(EncodeInfo *encInfo)
{
   // step 1 -> check open_files(encInfo) is returning e_success or not
            // no -> print error msg and return e_failure
            // yes -> print success goto next step 
            if(open_files(encInfo)==e_success)
            {
                printf("All files opened succesfully\n");
            }
            else
            {
               printf("Error in opening files!");
               return e_failure;

            }

    // step 2 -> check check_capacity(encInfo) is returning e_success or not
            // no -> print error msg and return e_failure
            // yes -> print success goto next step
            if(check_capacity(encInfo)==e_failure)
            {
               return e_failure;
            }

    // step 3 -> call copy_bmp_header(encInfo ->fptr_src_image , encInfo -> fptr_stego_image)
            if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
            {
                return e_failure;
            }
               

    // step 4 -> call encode_magic_string(MAGIC_STRING, encInfo)
            if( encode_magic_string(MAGIC_STRING, encInfo) == e_failure)
            {
                return e_failure;
            }

             

    // step 5 -> call encode_secret_file_extn_size(strlen(encInfo -> extn_secret_file), encInfo)
           if(encode_secret_file_extn_size(strlen(encInfo -> extn_secret_file),encInfo)==e_failure)
           {
            return e_failure;
           }
          

    // step 6 -> call encode_secret_file_extn(encInfo -> extn_secret_file, encInfo)
     if( encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_failure)
           {
            return e_failure;
           }

    // step 7 -> call encode_secret_file_size(encInfo -> size_secret_file, encInfo)
      if(encode_secret_file_size(encInfo->size_secret_file, encInfo)==e_failure)
          {
            return e_failure;
          }
    

       //middle man step 
        if(load_secret_data(encInfo)==e_failure)
        {
            return e_failure;
        }

        // step 8 ->  call encode_secret_file_data(encInfo)
       if(encode_secret_file_data(encInfo)==e_failure)
       {
        return e_failure;
       }



    // step 9 -> call copy_remaining_img_data(encInfo -> fptr_src_image, encInfo ->  fptr_stego_image)
    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_failure)
    {
        return e_failure;
    }
            // yes -> print success goto next step

    // return e_success;
}
