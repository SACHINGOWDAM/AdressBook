 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the choosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    int validname(char *name);
    int validphone(char *phone);
    int validemail(char *email);
	/* Defining the logic to create a Contacts read name from user min of 2 should be alnum or sspace*/
    printf("Enter the name of the contact: ");
    scanf(" %[^\n]s", addressBook->contacts[addressBook->contactCount].name);
    if(validname(addressBook->contacts[addressBook->contactCount].name))
    {
        printf("Enter the phone number of the contact: ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        if(validphone(addressBook->contacts[addressBook->contactCount].phone))
        {
            printf("Enter the email of the contact: ");
            scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
            if(validemail(addressBook->contacts[addressBook->contactCount].email))
            {
                addressBook->contactCount++;
                printf("Contact created successfully!\n");
            }
            else
            {
                printf("Invalid email format. Contact creation failed.\n");
            }
        }
        else
        {
            printf("Invalid phone number format. Contact creation failed.\n");
        }
    }
    int validname(char *name)
    {
        int len = strlen(name);
        if(len < 2)
        {
            return 0; // Name should be at least 2 characters long
        }
        for(int i = 0; i < len; i++)
        {
            if(!isalnum(name[i]) && !isspace(name[i]))uus
            {
                return 0; // Invalid character in name
            }
        }
        return 1; // Valid name
    }
    int validphone(char *phone)
    {
        int len = strlen(phone);
        if(len < 10 || len > 15)
        {
            return 0; // Phone number should be between 10 and 15 digits
        }
        for(int i = 0; i < len; i++)
        {
            if(!isdigit(phone[i]))
            {
                return 0; // Invalid character in phone number
            }
        }
        return 1; // Valid phone number
    }
    int validemail(char *email)
    {
        int len = strlen(email);
        char *at = strchr(email, '@');
        char *dot = strrchr(email, '.');
        if(!at || !dot || at >= dot)
        {
            return 0; // Invalid email format
        }
        return 1; // Valid email
    }

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}