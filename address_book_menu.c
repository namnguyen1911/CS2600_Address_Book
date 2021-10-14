#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"
#include "address_book_menu.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 
	int number = 0;

	if(*msg != '\0')
		printf("%s", msg);

	if(type == NUM) {
		number = checkIntChar();

		switch(number) {
			case 0: return e_exit;
			case 1: return e_add_contact;
			case 2: return e_search_contact;
			case 3: return e_edit_contact;
			case 4: return e_delete_contact;
			case 5: return e_list_contacts;
			case 6: return e_save;
			default: return e_exit;
		}
	}
	else if (type == CHAR) {
		bool check = checkChar();
		if(check == false)
			return 'N';
		else 
			return 'Y';
	}
	else {
		return e_back;
	}
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		//main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");


		if(option == e_exit) 
			break;
		else if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			//continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				displayList(address_book);
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	//Have to find out some way to be able to search the contact first
	int editInput;
	while(editInput != 0) //looping so that user can keep editing many times using the menu
	{
		printf("0. Exit\n");
		printf("1. Edit by name\n");
		printf("2. Edit by phone number\n");
		printf("3. Edit by email\n");
		printf("\n");
		printf("Please select an option: ");
		scanf("%d", editInput);
		
		if(editInput == 1) //by name
		{	
			printf("Current name is %s\n", address_book -> list[address_book -> count].name);
			printf("Please enter new name: ");
			scanf("%s", address_book -> list[address_book -> count].name);
			printf("\n");
		}
		else if(editInput == 2)//by phone number
		{	
			printf("Current phone number is %s\n", address_book -> list[address_book -> count].phone_numbers);
			printf("Please enter new phone number: ");
			scanf("%s", address_book -> list[address_book -> count].phone_numbers);
			printf("\n");
		}
		else if(editInput == 3) //by email
		{	
			printf("Current email address is %s\n", address_book -> list[address_book -> count].email_addresses);
			printf("Please enter new email address: ");
			scanf("%s", address_book -> list[address_book -> count].email_addresses);
			printf("\n");
		}
	}
	return e_success; //I think this allows the information to be saved
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}

void displayList(AddressBook *address_book) {
	printf("=================================================================================================================\n");
	printf("%c %-10s %c %-30s %c %-30s %c %-30s %c\n",':',"S.No",':', "Name", ':', "Phone No", ':', "Email ID",':');
	printf("=================================================================================================================\n");
	for(int j = 0; j < address_book->count;j++) {
		printf("%c %-10d %c %-30s %c %-30s %c %-30s %c\n",':',address_book->list[j].si_no,':', address_book->list[j].name[0], ':', address_book->list[j].phone_numbers[0], ':', address_book->list[j].email_addresses[0], ':');
		for(int i = 1; i < PHONE_NUMBER_COUNT; i++) {
			printf("%c %-10s %c %-30s %c %-30s %c %-30s %c\n",':',"",':', "", ':', ((strcmp(address_book->list[j].phone_numbers[i],"[empty]") == 0) ? "" : address_book->list[j].phone_numbers[i]), ':', ((strcmp(address_book->list[j].email_addresses[i],"[empty]") == 0) ? "" : address_book->list[j].email_addresses[i]),':');
		}
		printf("=================================================================================================================\n");
	}
}

int checkIntChar() {
    int number = 0, buffer = 0;

    while(true) {
        if((scanf("%d", &number)) != 1) {
            printf("Invalid input!\n");
            while((number = getchar()) != EOF && number != '\n');
        }
        else if(number < 0) {
            printf("Invalid input!\n");
            //clear buffer
            while((number = getchar()) != EOF && number != '\n');
        }
        else {
            break;
        }
    }
    //clear buffer
    while((buffer = getchar()) != EOF && buffer != '\n');
    return number;
}

bool checkChar() {
    int number = 0;

    //Clear the buffer if the inputs are wrong
    while(true) {
        number = getchar();
        if(number == 'y' || number == 'Y') {
            return true;
        }
        else if(number == 'n' || number == 'N') {
            return false;
        }
    }
}
