#ifndef VALIDATION_H
#define VALIDATION_H

#include "contact.h"

void removespace_pointer(char str[]);
char * check_valid_length(char str[]);
char * check_valid_characters(char str[]);
char * nameValidation(char str[],  AddressBook *addressBook);
char * email_validation(char str[], AddressBook *addressBook);

char * contact_validation(char str[], AddressBook *addressBook);

char * uniqueness(AddressBook *addressBook, char str[], char arr_name[]);
int find_matches(AddressBook *addressBook, char str[], int *found_match, char data[] );
void clear_buffer();

void choice_sorting(int num, AddressBook *addressBook);
void  sort_by_name(AddressBook *addressBook);
void  sort_by_phone(AddressBook *addressBook);
void  sort_by_email(AddressBook *addressBook);

void Edit_choice(int choice, AddressBook *address);
void edit_contact(AddressBook *addressBook, char arr_name[]);

void  Delete_choice(int choice,AddressBook *addressBook);
void Delete_contact(AddressBook *addressBook, char arr_name[]);

void Search_choice(int choice,AddressBook* addressBook);
void  search_by_name(AddressBook *addressBook);
void  search_by_phone(AddressBook *addressBook);
void  search_by_email(AddressBook *addressBook);




#endif