#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *file=fopen("contacts.csv","w");
    if(file==NULL) {
        perror("Unable to open file");
        return;
    }
    fprintf(file,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(file,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
  fclose(file);
}

void loadContactsFromFile(AddressBook *addressBook) { 
    FILE *file = fopen("contacts.csv","r");
    if(file==NULL) {
        perror("Unable to open file");
        return;
    }
    fscanf(file,"#%d\n", &addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++) {
        fscanf(file,"%[^,],%[^,],%[^\n]", 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
    }
    fclose(file);
}
