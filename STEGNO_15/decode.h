#ifndef DECODE_H
#define DECODE_H
#include <stdio.h>



/* decoding function prototype */

/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(char *argv[], EncodeInfo *encInfo);

Status open_de_files(EncodeInfo *encInfo);

/* Perform the encoding */
Status do_decoding(EncodeInfo *encInfo);

Status decode_magic_byte_to_lsb(char data, char *image_buffer);

     
   
    






/* get Magic String */
Status decode_magic_string(const char *magic_string, EncodeInfo *encInfo);

/*decode extension size*/
Status decode_secret_file_extn_size( EncodeInfo *encInfo);

/* decode secret file extenstion */
Status decode_secret_file_extn(int size, EncodeInfo *encInfo);

// open output file in read mode
Status open_output_file(EncodeInfo *encInfo);

/* decode secret file size */
Status decode_secret_file_size(long file_size, EncodeInfo *encInfo);

/* decode secret file data*/
Status decode_secret_file_data(EncodeInfo *encInfo);

/* decode a byte into LSB of image data array */
Status decode_byte_to_lsb(char *data, char *image_buffer);

// decode a size to lsb
Status decode_size_to_lsb(long int *size, char *imageBuffer);



#endif
