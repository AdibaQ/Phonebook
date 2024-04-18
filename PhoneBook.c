/*****************************************************************************
Phone Book:
Should have several records (at least 10 people in the contact list to start).
Phonebook features must include adding, updating, and deleting a number.
There should be a find function that could be used to find a number by the 
person’s name, or a find person to find the name of the person to whom this 
number belongs. Sort by name is required.
****************************************************************************/
#include <stdio.h>
#include <string.h>

//prototypes
void find_person(char phone_number[]);
void find_number(char name[]); 
void sort_file(char file_name[]);

int main(void)
{ 
    FILE *cfPtr; //file pointer for PhoneNumbers.txt
    FILE *tempPtr; //file pointer for temp.txt
    if ((cfPtr = fopen("PhoneNumbers.txt", "a+")) == NULL) //opens a file for reading and
                                                          //appends the writing at the end
    {
        puts("File could not be opened"); 
    } 

    else 
    {
        //print statements so its user friendly
        printf("Phonebook\n\n");
        printf("Type:\n");
        printf("1 - to add a number\n");
        printf("2 - to update a number\n");
        printf("3 - to delete a number\n");
        printf("4 - to find a person\n");
        printf("5 - to find a number\n");
        printf("6 - to close the Phoneboook \n");
        printf("\nEnter: ");
        unsigned int request; //initialize variable for user input
        scanf("%u", &request);
    
        while (request != 6) //process user's request
        {  
            char name[30]; //variable for person's name
            char given_name[30]; //variable for comparing names
            char phone_number[11]; //variable for phone numbers
            char new_phone_number[11]; //variable for an updated phone number
            int found = 0;
    
        switch (request) 
        { 
            case 1:
            puts("\nWhat is their name? (First letter only should be capitilized) ");
            scanf("%29s", name);
            puts("\nWhat is their phone number? (No dashes) ");
            scanf("%10s", phone_number);
            //prints statments and asks for user input
            fprintf(cfPtr, "%10s %-10s\n", name, phone_number);
            //prints the info into PhoneNumbers.txt
            break;
    
            case 2:
            puts("Whose number would you like to update? (First letter only should be capitilized) ");
            scanf("%10s", given_name);
            puts("What is the new number? (No dashes) ");
            scanf("%10s", new_phone_number);
            //prints statements and asks for user input
            if ((tempPtr = fopen("temp.txt", "w")) == NULL) //opens a temp file for writing
            {
                puts("Temporary file could not be created");
            } 
            else 
            {
                while (fscanf(cfPtr, "%29s %10s", name, phone_number) != EOF) //reads name and phone number 
                                                                          //in file until eof
                { 
                    if (strcmp(name, given_name) == 0) //if statement to compare each name in the file to user's input
                    {
                        fprintf(tempPtr, "%10s %-10s\n", name, new_phone_number); //if user's name is found, it prints into the
                                                                                //temp.txt the name along with the new number
                        found = 1;
                    } 
                    else 
                    {
                        fprintf(tempPtr, "%10s %-10s\n", name, phone_number); //otherwise it prints in the original lines
                    }
                }
                //closes both text files
                fclose(tempPtr);
                fclose(cfPtr);
                
                if (found == 0)
                {
                    printf("%s not found", given_name);
                }
                
                if (remove("PhoneNumbers.txt") != 0) //deletes PhoneNumbers.txt
                {
                    puts("Error deleting file");
                }
                if (rename("temp.txt", "PhoneNumbers.txt") != 0) //renames the temp.txt file as PhoneNumbers.txt
                {
                    puts("Error renaming file");
                }
                if ((cfPtr = fopen("PhoneNumbers.txt", "a+")) == NULL) //opens a file for reading and
                                                                       //appends the writing at the end
                {
                    puts("File could not be opened");
                } 
            }
            break;
            
            case 3:
            puts("Whose number would you like to delete? (First letter only should be capitilized) ");
            scanf("%29s", given_name);
            //prints and asks for user input
            if ((tempPtr = fopen("temp.txt", "w")) == NULL) //opens a temp file for writing
                    {
                        puts("Temporary file could not be created");
                    } 
                    else 
                    {
                        while (fscanf(cfPtr, "%29s %10s", name, phone_number) != EOF) //reads name and phone number 
                                                                                      //in file until eof
                        { 
                            if (strcmp(name, given_name) != 0) //for every name in the file that doesn't match with the user input
                            {
                                fprintf(tempPtr, "%10s %-10s\n", name, phone_number); //prints the name and number
                            } 
                        }
                        //closes both text files
                        fclose(tempPtr);
                        fclose(cfPtr);

                        if (remove("PhoneNumbers.txt") != 0) //deletes PhoneNumbers.txt
                        {
                            puts("Error deleting file");
                        }
                        if (rename("temp.txt", "PhoneNumbers.txt") != 0) //renames the temp.txt file to PhoneNumbers.txt
                        {
                            puts("Error renaming file");
                        }
                        if ((cfPtr = fopen("PhoneNumbers.txt", "a+")) == NULL) //opens a file for reading and
                                                                               //appends the writing at the end
                        {
                            puts("File could not be opened");
                        }
                    }
            break;
            
            case 4:
            puts("What is the number of the person you're trying to find? (No dashes) ");
            scanf("%10s", phone_number);
            //prints and asks for user input
            find_person(phone_number); //calls find_person function
            break;
            
            
            case 5:
            puts("What is the name of the person's number you're trying to find? (First letter only should be capitilized) ");
            scanf("%s", given_name);
            //prints and asks for user input
            find_number(given_name); //calls find_number function
            break;
        }
        
        rewind(cfPtr); //return cfPtr to beginning of file
        printf("%s", "\n? ");
        scanf("%d", &request);
        //prints and asks for user input
        } 
        sort_file("PhoneNumbers.txt"); //calls sort_file function
        puts("End of run."); //prints to let user know end of run
    }
}

void find_person(char phone_number[]) //function to find a person through their phone number
{
    FILE *cfPtr; //file pointer for PhoneNumbers.txt
    char name[30]; //variable for name
    char number[11]; //variable to compare phone numbers
    int found = 0; //variable to check if found
    
    if ((cfPtr = fopen("PhoneNumbers.txt", "r")) == NULL) //opens a file for reading
    {
        puts("File could not be opened");
    }

    while (fscanf(cfPtr, "%29s %10s", name, number) != EOF) //reads name and phone number 
                                                            //in file until eof
    {
        if (strcmp(number, phone_number) == 0) //if statement to compare each number in the file to user's input from case
        {
            printf("%s's phone number is %s\n", name, number); //prints information to the user
            found = 1; //changes variable found if it's a match
        }
    }

    if (found == 0) //if there is no match found, lets the user know
    {
        printf("No person found with phone number %s\n", phone_number);
    }
    fclose(cfPtr); //closes the text file
}

void find_number(char given_name[]) //function to find a person's number through their name
{
    FILE *cfPtr; //file pointer for PhoneNumbers.txt
    char name[30]; //variable for person's name
    char phone_number[11]; //variable for person's number
    int found = 0; //variable to check if found
    
    if ((cfPtr = fopen("PhoneNumbers.txt", "r")) == NULL) //opens a file for reading
    {
        puts("File could not be opened");
    } 
    
    while (fscanf(cfPtr, "%29s %10s", name, phone_number) != EOF) //reads name and phone number 
                                                                  //in file until eof
    { 
        if (strcmp(name, given_name) == 0) //if statement to compare each name in the file to user's input from case
        {
            printf("The phone number of %s is %s\n", name, phone_number);
            found = 1;
        } 
    }
    
    if (found == 0) //if there is no match found, lets the user know
    {
        printf("No number found for %s\n", given_name);
    }
    fclose(cfPtr); //closes the text file
}

void sort_file(char file_name[]) //function to sort lines in a file by name
{ 
    FILE *cfPtr; //file pointer for PhoneNumbers.txt
    char name[30]; //variable for person's name
    char phone_number[11]; //variable for person's phone number
    char hold_name[30]; //variable to hold name while swapping  
    char hold_phone_number[11]; //variable to hold phone number while swapping  
    int number_of_lines = 0; //variable for the number of lines
    
    if ((cfPtr = fopen(file_name, "r")) == NULL) //opens a file for reading
    {
        puts("File could not be opened");
    } 
    while (fscanf(cfPtr, "%29s %10s", name, phone_number) != EOF) //reads name and phone number 
                                                                  //in file until eof
    {
        number_of_lines++; //count the number of lines in the file
    }
    fclose(cfPtr); //close the text file
    
    if ((cfPtr = fopen(file_name, "r")) == NULL) //opens a file for reading
    {
        puts("File could not be opened");
    } 

    char phonebook[number_of_lines][2][30]; //array to store names and phone numbers
    for (int i = 0; i < number_of_lines; i++) 
    {
        fscanf(cfPtr, "%29s %10s", phonebook[i][0], phonebook[i][1]); //read the lines into the array
    }
    fclose(cfPtr); //close the text file
    
    //compare adjacent elements and swap them if first element is greater than the second element 
    for (int i = 0; i < number_of_lines - 1; i++)
    {
        for (int j = i + 1; j < number_of_lines; j++) 
        {
            if (strcmp(phonebook[i][0], phonebook[j][0]) > 0) 
            {
                strcpy(hold_name, phonebook[i][0]);
                strcpy(hold_phone_number, phonebook[i][1]);
                strcpy(phonebook[i][0], phonebook[j][0]);
                strcpy(phonebook[i][1], phonebook[j][1]);
                strcpy(phonebook[j][0], hold_name);
                strcpy(phonebook[j][1], hold_phone_number);
            }
        }
    }
    
    if ((cfPtr = fopen(file_name, "w")) == NULL) //opens a file for writing
    {
        puts("File could not be opened");
    } 
    for (int i = 0; i < number_of_lines; i++) //write the sorted array back to the file
    {
        fprintf(cfPtr, "%10s %-10s\n", phonebook[i][0], phonebook[i][1]);
    }
    fclose(cfPtr); //close the text file
}


