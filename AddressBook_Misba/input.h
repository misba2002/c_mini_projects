#ifndef INPUT_H
#define INPUT_H

#include "contact.h"

char * get_input(char str[], int size,char *arr_name ,char * (* validate)(char str[],  AddressBook *addressBook), AddressBook *addressBook);

int get_choice_input(char str[]);



#endif