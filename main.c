#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 10
#define MAX_COLUMN_LENGTH 50


struct Node {
    char columns[MAX_COLUMNS][MAX_COLUMN_LENGTH];  // Array of strings to store column values
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;
struct Node* selected = NULL;
char columnNames[MAX_COLUMNS][MAX_COLUMN_LENGTH];  // Array to store column names
int columnCount = 0;  // Number of columns in the CSV
void manipulate();

void remove_last_char(char *str) {
    int len = strlen(str);
    if (len > 0) {
        str[len - 1] = '\0';  // Replace the last character with a null terminator
    }
}



void createLinkedList(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL) {
        // File doesn't exist
        printf("Error: Unable to open file!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int i;

    // Read the first line to determine the number of columns and store column names
    if (fgets(line, sizeof(line), file) != NULL) {
        // Count the number of commas to get the number of columns
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == ',') {
                columnCount++;
            }
        }
        columnCount++; // Number of columns = commas + 1

        // Tokenize the line to get column names
        char *token = strtok(line, ",");
        int currentColumn = 0;
        while (token != NULL && currentColumn < columnCount) {
            strncpy(columnNames[currentColumn], token, MAX_COLUMN_LENGTH - 1);
            columnNames[currentColumn][MAX_COLUMN_LENGTH - 1] = '\0'; // Ensure null termination
            currentColumn++;
            token = strtok(NULL, ",");
        }
        remove_last_char(columnNames[columnCount-1]);
    }

    // Process each line and populate linked list nodes
    while (fgets(line, sizeof(line), file) != NULL) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        memset(new_node, 0, sizeof(struct Node)); // Initialize all fields to NULL

        // Tokenize the line based on commas
        char *token = strtok(line, ",");
        int currentColumn = 0;

        // Assign values to the linked list node based on the number of columns
        while (token != NULL && currentColumn < columnCount) {
            if(currentColumn==columnCount-1){
            	remove_last_char(token);
            	remove_last_char(token);
            	strncpy(new_node->columns[currentColumn], token, MAX_COLUMN_LENGTH - 1);
			}else{
				strncpy(new_node->columns[currentColumn], token, MAX_COLUMN_LENGTH - 1);
			}
			
            new_node->columns[currentColumn][MAX_COLUMN_LENGTH - 1] = '\0'; // Ensure null termination
			currentColumn++;
            token = strtok(NULL, ",");
        }

        // Add node to the doubly circular linked list
        if(head==NULL) {
			head = new_node;
		}else {
				if(tail==NULL){
			   	new_node->prev=head;
				new_node->next=NULL;
		 		tail=new_node;
		  		head->next=tail;
				} else {
					tail->next=new_node;
			   		new_node->next=NULL;
		    		new_node->prev=tail;
			   		tail=new_node;
				}
		}
    }

    fclose(file);
}

void printList() {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* temp = head;
    int i;
    while (temp != NULL){
        printf("row");
        for (i = 0; i < columnCount; i++) {
            printf("%s ", temp->columns[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}



void save(const char *filename) {
    FILE *file = fopen(filename, "w");
    int i;
    if (file == NULL) {
        // File doesn't exist, create a new one
        file = fopen(filename, "w"); // Open file in write mode
        if (file == NULL) {
            printf("Error: Unable to create file!\n");
            exit(1);
        }

        printf("File created and header added.\n");
    }

    // Write the data from the linked list
    struct Node* temp = head;
    int rowNum = 1; // Starting serial number for rows
    for (i = 0; i < columnCount; i++) {
                fprintf(file, "%s",columnNames[i]);
                if (i < columnCount - 1) {
                    fprintf(file, ",");
                }else{
                	fprintf(file, "\n");
				}
    }

    if (temp != NULL) {
        while (temp != NULL){
            for (i = 0; i < columnCount; i++) {
                fprintf(file, "%s", temp->columns[i]);
                if (i < columnCount - 1) {
                    fprintf(file, ",");
                }
                else{
                	fprintf(file, "\n");
				}
            }
            temp = temp->next;
            rowNum++;
        } // Loop until you return to the head of the list

        printf("File saved successfully!!\n");
    }

    fclose(file);
}

void printColumnNames() {
    printf("Column Names: ");
    int i;
    for (i = 0; i < columnCount; i++) {
        printf("columnNames[%d]=%s \n",i, columnNames[i]);
    }
    printf("\n");
}


void insert(){
    char value[columnCount-1][MAX_LINE_LENGTH];
    int i;
    printf("enter detail");
    for(i=0;i<columnCount;i++){
    	printf("enter %s=",columnNames[i]);
    	scanf(" %[^\n]s",&value[i]);
	}
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    for(i=0;i<columnCount;i++){
    	
        strcpy(new_node->columns[i],value[i]);
	}
		new_node->next=NULL;
		new_node->prev=NULL;


        // Add node to the doubly circular linked list
        if(head==NULL) {
			head = new_node;
		}else {
				if(tail==NULL){
			   	new_node->prev=head;
				new_node->next=NULL;
		 		tail=new_node;
		  		head->next=tail;
				} else {
					tail->next=new_node;
		    		new_node->prev=tail;
			   		tail=new_node;
				}
		}
		printf("insert complete;");
}


//remove white space in str
void remove_spaces(char *str) {
    char *i = str;
    char *j = str;
    while(*j != '\0') {
        if(*j != ' ') {
            *i = *j;
            i++;
        }
        j++;
    }
    *i = '\0'; // Null-terminate the modified string
}

// Function to convert a string to lowercase
void to_lowercase(char *str) {
	int i;
    for(i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void find(){
    int option, seat, found = 0;
    char search[50],str[50];
    int i=0;

    printf("Choose search criteria:\nfind by\n");
    while(i<columnCount){
		printf("%d.%s,",i,columnNames[i]);
		i++;
	}
	scanf("%d", &option);

    struct Node* temp = head;
    printf("Enter to find: ");
    scanf(" %[^\n]s", &search);
    // Remove spaces and convert to lowercase for search string
    remove_spaces(search);
    to_lowercase(search);
    
    while(temp!=NULL){
    	strcpy(str, temp->columns[option]); // Copy the name from the node
        remove_spaces(str);
        to_lowercase(str);
	        if(strcmp(str,search)==0){
	     		printf("Found name %s",temp->columns[option]);
	     		found =1;
	     		selected=temp;
	    		break;
	    	}
	    	temp=temp->next;
    }
    if(found==1){
    	
    manipulate();
	}
}

void manipulate(){
	struct Node* temp =NULL;
	int option,option2;
	char value[50];
    int i=0;
    printf("Choice:\n");
	printf("1.delete 2.Edit 3.close ");
	scanf("%d",&option);
	printf("%s",selected->columns[i]);
	switch(option){
		case 1:
			if(selected==head){
				head=selected->next;
				head->prev=NULL;
			}else{
			temp =selected->prev;
			temp->next=selected->next;
			temp=selected->next;
			temp->prev=selected->prev;
	     	}
			free(selected);
			selected=NULL;
			printf("deleted\n");
			break;
		case 2:
			printf("Choice: \n");
			while(i<columnCount){
				printf("%d.%s,",i,columnNames[i]);
				i++;
			}
        	printf("%d.All",columnCount);
	        scanf("%d",&option2);
	        if(option2==columnCount){
	        	i=0;
	        	while(i<columnCount){
	        		printf("Enter %s=",columnNames[i]);
	        		scanf(" %[^\n]s",&value);
	        	    strcpy(selected->columns[i],value);
	        	    i++;
				}
			}else{
	        printf("Enter value=");
	        scanf(" %[^\n]s",value);
	        strcpy(selected->columns[option2],value);
	        printf("done");
	        }
}

}


void capitalizeFirstLetter(char* str) {
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - 32; // Convert first character to uppercase
    }
}

void toUpperCase(char* str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // Convert to uppercase
        }
    }
}

int isNumeric(const char* str) {
    int i;
	for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Return false if any character is non-numeric
        }
    }
    return 1; // Return true if the string contains only digits
}

void sort(char squ[50], char column[50]) {
    if (head == NULL || head->next == NULL) {
        return; // Empty list or only one node
    }

    int i;
    // Find the index of the column to be sorted
    int colIndex = -1;
    for (i = 0; i < columnCount; i++) {
        if (strcmp(columnNames[i], column) == 0) {
            colIndex = i;
            break;
        }
    }

    if (colIndex == -1) {
        printf("Error: Column not found!\n");
        return;
    }

    int ascending = strcmp(squ, "as") == 0 ? 1 : 0;

    // Perform bubble sort (or any sorting algorithm) on the doubly linked list
    struct Node* iNode;
    struct Node* jNode;
    int swapped;
    int k;
    do {
        swapped = 0;
        iNode = head;

        while (iNode->next != NULL) {
            jNode = iNode->next;

            // Get the values to compare
            char iValue[MAX_COLUMN_LENGTH];
            char jValue[MAX_COLUMN_LENGTH];

            strcpy(iValue, iNode->columns[colIndex]);
            strcpy(jValue, jNode->columns[colIndex]);

            // If the values are not numeric, capitalize first letter or convert to uppercase for case-insensitive comparison
            if (!isNumeric(iValue) && !isNumeric(jValue)) {
                // Alternatively, just capitalize the first letter:
                capitalizeFirstLetter(iValue);
                capitalizeFirstLetter(jValue);
            }

            // Compare values in the specified column
            if ((ascending && strcmp(iValue, jValue) > 0) ||
                (!ascending && strcmp(iValue, jValue) < 0)) {
                // Swap the node data
                for (k = 0; k < columnCount; k++) {
                    char temp[MAX_COLUMN_LENGTH];
                    strcpy(temp, iNode->columns[k]);
                    strcpy(iNode->columns[k], jNode->columns[k]);
                    strcpy(jNode->columns[k], temp);
                }
                swapped = 1;
            }
            iNode = iNode->next;
        }
    } while (swapped);
}


void display() {
    struct Node* temp = head;
    int i;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Print table header
    printf("+");
    for (i = 0; i < columnCount; i++) {
        printf(" %-14s |", columnNames[i]);
    }
    printf("\n+");
    for (i = 0; i < columnCount; i++) {
        printf("----------------+");
    }
    printf("\n");

    // Traverse and display the nodes
    while (temp != NULL) {
        printf("|");
        for (i = 0; i < columnCount; i++) {
            printf(" %-14s |", temp->columns[i]);
        }
        printf("\n");
        temp = temp->next;
    }

    // Print table footer
    printf("+");
    for (i = 0; i < columnCount; i++) {
        printf("----------------+");
    }
    printf("\n");
}







int main() {
	int option,exit=0;
	char args0[50],args1[50],args2[50];
	printf("enter file name(eg:- abc.csv):\n");
	scanf(" %[^\n]s",&args0);
    createLinkedList(args0);
	struct Node* temp = head;
		while(exit==0){
		printf("Choice: \n");
        printf("1.insert 2.find and delete/edit 3.Sort 4.display 5.save 6.exit \n");
    	scanf("%d",&option);
    	system("cls");
		switch(option){
			case 1:
				printf("insert: \n");
				insert();
				break;
			case 2:
				printf("find and delete\edit: \n");
				find();
				break;
			case 3:
				printf("choice sort by column:\n");
				printColumnNames();
    	        scanf(" %[^\n]s",&args1);
    	        printf("sort type(as/ds):\n");
    	        scanf(" %[^\n]s",&args2);
				sort(args2,args1);
				break;	
			
			case 4:
				display();
				break;
			case 5:
				save("new2.csv");
				break;
			case 6:
	            while(temp!=tail){
		            temp=temp->next;
    		        free(temp->prev);
    	        }
    	        free(temp);
				exit=1;
				break;
			default:
				printf("invalid choise!!\n");
			
		}
	}
    return 0;
}




