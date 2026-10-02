 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts and display based on the choosen criteria
    if(addressBook->contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }
    else
    {
        int sortCriteria;
                printf("Choose sorting criteria to list the contacts:\n");   
                printf("1. Sort by name\n");
                printf("2. Sort by phone number\n");
                printf("3. Sort by email\n");
                scanf("%d", &sortCriteria);
        switch(sortCriteria) {
            case 1: // Sort by name
                for(int i = 0; i < addressBook->contactCount - 1; i++) {
                    for(int j = 0; j < addressBook->contactCount - i - 1; j++) {
                        if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) {
                            Contact temp = addressBook->contacts[j];
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                            addressBook->contacts[j + 1] = temp;
                        }
                    }
                }
                break;
            case 2: // Sort by phone number
                for(int i = 0; i < addressBook->contactCount - 1; i++) {
                    for(int j = 0; j < addressBook->contactCount - i - 1; j++) {
                        if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0) {
                            Contact temp = addressBook->contacts[j];
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                            addressBook->contacts[j + 1] = temp;
                        }
                    }
                }
                break;
            case 3: // Sort by email
                for(int i = 0; i < addressBook->contactCount - 1; i++) {
                    for(int j = 0; j < addressBook->contactCount - i - 1; j++) {
                        if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0) {
                            Contact temp = addressBook->contacts[j];
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                            addressBook->contacts[j + 1] = temp;
                        }
                    }
                }
                break;
            default:
                printf("Invalid sorting criteria.\n");
                return;
        }
        printf("--- Contact List ---\n");
                    for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                        printf("|%3d|Name: %-20s | Phone: %-15s | Email: %-25s|\n", 
                                i + 1,
                                addressBook->contacts[i].name, 
                                addressBook->contacts[i].phone, 
                                addressBook->contacts[i].email);
                    }
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);// Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Defining the logic to create a Contacts read name from user min of 2 should be alnum or sspace*/
    printf("Enter the name of the contact: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    if(validname(addressBook->contacts[addressBook->contactCount].name, addressBook))
    {
        printf("Enter the phone number of the contact: ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        if(validphone(addressBook->contacts[addressBook->contactCount].phone, addressBook))
        {
            printf("Enter the email of the contact: ");
            scanf(" %s", addressBook->contacts[addressBook->contactCount].email);//email should not have space in it
            if(validemail(addressBook->contacts[addressBook->contactCount].email, addressBook))
            {
                addressBook->contactCount++;
                printf("Contact created successfully!\n");
                return;
            }
            else
            {
                printf("Invalid email format. Contact creation failed.\n");
                return;
            }
        }
        else
        {
            printf("Invalid phone number format. Contact creation failed.\n");
            return;
        }
    }
    else
            {
                printf("Invalid name format. Contact creation failed.\n");
                return;
            }
}
int validname(char *name, AddressBook *addressBook)
    {
        int len = strlen(name);
        if(len < 2)
        {
            printf("Name should be at least 2 characters long.\n");
            return 0; // Name should be at least 2 characters long
        }
        for(int i = 0; i < len; i++)
        {
            if(!isalnum(name[i]) && !isspace(name[i]))
            {
                printf("Name should contain only alphanumeric characters and spaces.\n");
                return 0; // Invalid character in name
            }
        }
        //duplicate name check
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].name, name) == 0)
            {
                printf("Duplicate name found. Contact creation failed.\n");
                return 0; // Duplicate name found
            }
        }

        return 1; // Valid name
    }
    int validphone(char *phone, AddressBook *addressBook)
    {
        int len = strlen(phone);
        if(len < 10 || len > 15)
        {
            printf("Phone number should be between 10 and 15 digits.\n");
            return 0; // Phone number should be between 10 and 15 digits
        }
        if(phone[0] < 6 )
        {
            printf("Phone number should start with a digit between 6 and 9.\n");
            return 0; // Phone number should start with a digit between 6 and 9
        }
        int digitcount=0;
        for(int i = 0; i < len; i++)
        {
            if(!isdigit(phone[i])&&!(isspace(phone[i])))
            {

                printf("Phone number should contain only digits or spaces.\n");
                return 0; // Invalid character in phone number
            }
            if(isdigit(phone[i]))
            {
                digitcount++;
            }
        }
        if(digitcount!=10)
                {
                    printf("Phone number should be 10 digits.\n");
                    return 0; // Phone number should not exceed 10 digits
                }
        //duplicate phone check
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                printf("Duplicate phone number found. Contact creation failed.\n");
                return 0; // Duplicate phone number found
            }
        }
        return 1; // Valid phone number
    }
    int validemail(char *email, AddressBook *addressBook)
    {
        int len=strlen(email);
        int atcount=0;
        if(len<7||!isalnum(email[0]) || strcmp(email+len-4,".com")!=0||email[len - 5] == '@')//
        {
            printf("Invalid email format. Email should be at least 7 characters long, start with an alphanumeric character, contain exactly one '@', and end with '.com'.\n");
            return 0;
        }
        //duplicate email check
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].email, email) == 0)
            {
                printf("Duplicate email found. Contact creation failed.\n");
                return 0; // Duplicate email found
            }
        }
        for(int i=0;email[i]!='\0';i++)
        {
            if(email[i]=='@')
            {
                atcount++;
            }
            if(isupper((unsigned char)email[i]))
            {
                printf("Error: email cannot be in Uppercase");
                return 0;
            }
        }
        if(atcount!=1)
        {
            return 0;
        }
        return 1; // Valid email
    }

void searchContact(AddressBook *addressBook) 
{
    if(addressBook->contactCount==0)
    {
        printf("No contacts available to search\n");
        return ;
    }
    int choice;
    char target[50];
    int found[100];
    int serial=0;
    printf("Enter the choice you want to search the contact\n");
    printf("1.Search by name\n2.Search by phone number\n3.Search by email\n ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1 :
        printf("Enter the name of the contact you want to search\n");
        scanf(" %[^\n]",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].name,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-20s\n",
                        ++serial,
                    addressBook->contacts[i].name);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the name %s\n",target);
                return;
            }
            
        break;
        case 2 :
        printf("Enter the phone number of the contact you want to search\n");
        scanf(" %[^\n]",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].phone,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-15s\n",
                        ++serial,
                    addressBook->contacts[i].phone);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the phone number %s\n",target);
                return;
            }

        break;
        case 3 :
        printf("Enter the email of the contact you want to search\n");
        scanf(" %s",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].email,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-25s\n",
                        ++serial,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the email %s\n",target);
                return;
            }
        break;
        default :
        printf("Invalid Choice\n");
        return;
        break;
    }
    if(serial>0)
    {
        printf("Enter the serial number of the contact you want to view\n");
        int serialchoice;
        scanf("%d",&serialchoice);
        if(serialchoice>0 && serialchoice<=serial)
        {
            int index=found[serialchoice-1];
            printf("Contact Details:\n");
            printf("Name: %s\n",addressBook->contacts[index].name);
            printf("Phone: %s\n",addressBook->contacts[index].phone);
            printf("Email: %s\n",addressBook->contacts[index].email);
        }
        else
        {
            printf("Invalid serial number.\n");
        }
    }
}

void editContact(AddressBook *addressBook)
{
if(addressBook->contactCount==0)
    {
        printf("No contacts available to edit\n");
        return ;
    }
    int choice;
    char target[50];
    int found[100];
    int serial=0;
    printf("Enter the choice you want to search the contact\n");
    printf("1.Search by name\n2.Search by phone number\n3.Search by email\n ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1 :
        printf("Enter the name of the contact you want to edit\n");
        scanf(" %[^\n]",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].name,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-20s %-15s %-25s\n",
                        ++serial,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the name %s\n",target);
            }
            else
            {
                printf("Enter the serial number of the contact you want to edit\n");
                int serialchoice;
                scanf("%d",&serialchoice);
                if(serialchoice>0 && serialchoice<=serial)
                {
                    int index=found[serialchoice-1];
                    printf("What do you want to edit?\n1. Name\n2. Phone\n3. Email\n");
                    int editChoice;
                    scanf("%d",&editChoice);
                    switch(editChoice)
                    {
                        case 1:
                            printf("Enter the new name: ");
                            scanf(" %[^\n]", addressBook->contacts[index].name);
                            if(validname(addressBook->contacts[index].name, addressBook))
                            {
                                printf("Name updated successfully!\n");
                            }
                            else
                            {
                                printf("Invalid name format. Update failed.\n");
                            }
                            break;
                        case 2:
                            printf("Enter the new phone number: ");
                            scanf(" %[^\n]", addressBook->contacts[index].phone);
                            if(validphone(addressBook->contacts[index].phone, addressBook))
                            {
                                printf("Phone number updated successfully!\n");
                            }
                            else
                            {
                                printf("Invalid phone number format. Update failed.\n");
                            }
                            break;
                        case 3:
                            printf("Enter the new email: ");
                            scanf(" %s", addressBook->contacts[index].email);
                            if(validemail(addressBook->contacts[index].email, addressBook))
                            {
                                printf("Email updated successfully!\n");
                            }
                            else
                            {
                                printf("Invalid email format. Update failed.\n");
                            }
                            break;
                        default:
                            printf("Invalid choice. No changes made.\n");
                    }
                    printf("Contact Details after edit:\n");
                    printf("Name: %s\n",addressBook->contacts[index].name);
                    printf("Phone: %s\n",addressBook->contacts[index].phone);
                    printf("Email: %s\n",addressBook->contacts[index].email);
                }
                else
                {
                    printf("Invalid serial number.\n");
                }
            }
            
        break;
        case 2 :
        printf("Enter the phone number of the contact you want to edit\n");
        scanf(" %[^\n]",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].phone,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-20s %-15s %-25s\n",
                        ++serial,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the phone number %s\n",target);
            }
            else
            {
                printf("Enter the serial number of the contact you want to edit\n");
                int serialchoice;
                scanf("%d",&serialchoice);
                if(serialchoice>0 && serialchoice<=serial)
                {
                    int index=found[serialchoice-1];
                    printf("What do you want to edit?\n1. Name\n2. Phone\n3. Email\n");
                    int editChoice;
                    scanf("%d",&editChoice);
                    switch(editChoice)
                    {
                        case 1:
                            printf("Enter the new name: ");
                            scanf(" %[^\n]", addressBook->contacts[index].name);
                            if(validname(addressBook->contacts[index].name, addressBook))
                            {
                                printf("Name updated successfully!\n");
                            }
                            else
                            {
                                printf("Invalid name format. Update failed.\n");
                            }
                            break;
                        case 2:
                            printf("Enter the new phone number: ");
                            scanf(" %[^\n]", addressBook->contacts[index].phone);
                            if(validphone(addressBook->contacts[index].phone, addressBook))
                            {
                                printf("Phone number updated successfully!\n");
                            }
                            else
                            {
                                printf("Invalid phone number format. Update failed.\n");
                            }
                            break;
                        case 3:
                            printf("Enter the new email: ");
                            scanf(" %s", addressBook->contacts[index].email);
                            if(validemail(addressBook->contacts[index].email, addressBook))
                            {
                                printf("Email updated successfully!\n");
                            }
                            else
                            {
                                printf("Invalid email format. Update failed.\n");
                            }
                            break;
                        default:
                            printf("Invalid choice. No changes made.\n");
                    }
                    printf("Contact Details after edit:\n");
                    printf("Name: %s\n",addressBook->contacts[index].name);
                    printf("Phone: %s\n",addressBook->contacts[index].phone);
                    printf("Email: %s\n",addressBook->contacts[index].email);
                }
                else
                {
                    printf("Invalid serial number.\n");
                }
            }

        break;
        case 3 :
        printf("Enter the email of the contact you want to edit\n");
        scanf(" %s",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].email,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-2d %-15s %-15s %-25s\n",
                        ++serial,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the email %s\n",target);
            }
            else
            {
                printf("Enter the serial number of the contact you want to edit\n");
                int serialchoice;
                scanf("%d",&serialchoice);
                if(serialchoice>0 && serialchoice<=serial)
                {
                    int index=found[serialchoice-1];
                    printf("What do you want to edit?\n1. Name\n2. Phone\n3. Email\n");
                    int editChoice; 
                    scanf("%d",&editChoice);
                    switch(editChoice)
                    {
                        case 1:
                            printf("Enter the new name:\n");
                            scanf(" %s",addressBook->contacts[index].name);
                            break;
                        case 2:
                            printf("Enter the new phone number:\n");
                            scanf(" %s",addressBook->contacts[index].phone);
                            break;
                        case 3:
                            printf("Enter the new email:\n");
                            scanf(" %s",addressBook->contacts[index].email);
                            break;
                        default:
                            printf("Invalid choice. No changes made.\n");
                    }
                    printf("Contact Details after edit:\n");
                    printf("Name: %s\n",addressBook->contacts[index].name);
                    printf("Phone: %s\n",addressBook->contacts[index].phone);
                    printf("Email: %s\n",addressBook->contacts[index].email);
                }
                else
                {
                    printf("Invalid serial number.\n");
                }
            }
        break;
        default :
        printf("Invalid Choice\n");
        return;
        break;
    }
    
}

void deleteContact(AddressBook *addressBook)
{
    if(addressBook->contactCount==0)
    {
        printf("No contacts available to delete\n");
        return ;
    }
    int choice;
    char target[50];
    int found[100];
    int serial=0;
    printf("Enter the choice you want to search the contact\n");
    printf("1.Search by name\n2.Search by phone number\n3.Search by email\n ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1 :
        printf("Enter the name of the contact you want to delete\n");
        scanf(" %[^\n]",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].name,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-20s %-15s %-25s\n",
                        ++serial,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the name %s\n",target);
            }
            else
            {
                printf("Enter the serial number of the contact you want to delete\n");
                int serialchoice;
                scanf("%d",&serialchoice);
                if(serialchoice>0 && serialchoice<=serial)
                {
                    int index=found[serialchoice-1];
                    // Shift contacts to remove the selected contact
                    for(int i=index;i<addressBook->contactCount-1;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                else
                {
                    printf("Invalid serial number.\n");
                }
            }
            
        break;
        case 2 :
        printf("Enter the phone number of the contact you want to delete\n");
        scanf(" %[^\n]",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].phone,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-20s %-15s %-25s\n",
                        ++serial,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the phone number %s\n",target);
            }
            else
            {
                printf("Enter the serial number of the contact you want to delete\n");
                int serialchoice;
                scanf("%d",&serialchoice);
                if(serialchoice>0 && serialchoice<=serial)
                {
                    int index=found[serialchoice-1];
                    // Shift contacts to remove the selected contact
                    for(int i=index;i<addressBook->contactCount-1;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                else
                {
                    printf("Invalid serial number.\n");
                }
            }

        break;
        case 3 :
        printf("Enter the email of the contact you want to delete\n");
        scanf(" %s",target);
        printf("Contact Results\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strstr(addressBook->contacts[i].email,target)!=NULL)
                {
                    found[serial]=i;
                    printf("%-3d %-20s %-15s %-25s\n",
                        ++serial,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                }
            }
            if(serial==0)
            {
                printf("No contact found with the email %s\n",target);
            }
            else
            {
                printf("Enter the serial number of the contact you want to delete\n");
                int serialchoice;
                scanf("%d",&serialchoice);
                if(serialchoice>0 && serialchoice<=serial)
                {
                    int index=found[serialchoice-1];
                    // Shift contacts to remove the selected contact
                    for(int i=index;i<addressBook->contactCount-1;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                else
                {
                    printf("Invalid serial number.\n");
                }
            }
        break;
        default :
        printf("Invalid Choice\n");
        return;
        break;
    }
}