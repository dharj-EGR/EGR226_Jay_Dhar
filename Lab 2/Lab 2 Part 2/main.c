#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char title [255], author_name[50], ISBN [10];
    int pages, year_published;
}book;

int parse_file(char filename[], book book_array[]);

int main()
{
    book mybook [360];

    return 0;
}

/*-----------------------------------------------------------
* Function: parse_file
* Description: Sift through a file of books to populate
* an empty book array
* Inputs:
* (char*) filename: file to open and parse
* (book*) book_array: array of book structures to
* populate
* Outputs:
* (int) parse status, 1 if successful, 0 otherwise.
*---------------------------------------------------------*/
int parse_file(char filename[], book book_array[]) {
 FILE* infile = fopen(filename, "r"); // Attempt to open file
 if (infile == NULL) // Return 0 (failure) if file could not open
 return 0;

 char buffer[512]; // Create temporary string buffer variable
 int i = 0; // Indexer for book array

 while (fgets(buffer, 512, infile)) { // Loop collecting each line from the file
 char * ptr = strtok(buffer,","); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].title,ptr);// First parse is title

 ptr = strtok(NULL,",\n");
 // Todo: Validate string
 // Todo: Second parse is author
 // Todo: Handle null value

 ptr = strtok(NULL,",\n");
 // Todo: Validate string
 // Todo: Third parse is ISBN
 // Todo: Handle null value

 ptr = strtok(NULL,",\n");
 // Todo: Validate string
 // Todo: Fourth parse is page count
 // Todo: Handle null value

 ptr = strtok(NULL,",\n");
 // Todo: Validate string
 // Todo: Fifth parse is year published
 // Todo: Handle null value
 i++;
 }

 return 1;
}
