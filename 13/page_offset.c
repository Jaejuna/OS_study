#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096   // Define the size of a page to be 4KB

int main(int argc, char *argv[]) {

    // Check for correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: ./address_translation <virtual address>\n");
        return -1;
    }

    // Convert command line argument to a number
    unsigned int address = atoi(argv[1]);

    // Calculate the page number and offset for a 4KB page size
    // The page number is the quotient of the division operation
    unsigned int page_number = address / PAGE_SIZE;

    // The offset is the remainder of the division operation
    unsigned int offset = address % PAGE_SIZE;

    // Print the results
    printf("The address %d contains:\n", address);
    printf("page number = %d\n", page_number);
    printf("offset = %d\n", offset);

    return 0;
}
