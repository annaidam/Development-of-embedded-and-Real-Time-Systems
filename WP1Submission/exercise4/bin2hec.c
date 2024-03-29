// (C) David Schön, Milena Mackowiak, Anna Mäkinen, group: 3 (2024)
// Work package 1
// Exercise 4
// Submission code: XXXXXX (provided by your TA-s)

//includes
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//function declarations
void BinaryToHex(char *binaryData, char *hexData);

#define SET_BIT(buffer, index) ((buffer)[(index) / 8] |= (1 << ((index) % 8)))
#define CLEAR_BIT(buffer, index) ((buffer)[(index) / 8] &= ~(1 << ((index) % 8)))
#define GET_BIT(buffer, index) (((buffer)[(index) / 8] >> ((index) % 8)) & 1)
//main
int main(int argc, char *argv[]) {

    //initializing variables
    const int bufferSize = 1024;
    char *binaryData = malloc(bufferSize);
    char *hexData = malloc(bufferSize/4);
   

    // ---various checks---

    //check that there is an input
    if (!binaryData) {
        perror("Memory allocation failed");
        return 2;//exit with error code 2
    }

    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
    {
        printf("Usage: this program prints the binary form of the number given, give the number as a parameter after the program: decimalToBinary.exe <number>\n");
        printf("note: this program can be used in conjunction with binaryToHex to instead be given the hexadecimal of the number: decimalToBinary.exe <number> | binaryToHex.exe\n");
        return 0;
    } else if (argc == 2)
    {
        binaryData = argv[1];
    }
    else
    {
        // Read binary data from stdin
        if (fgets(binaryData, bufferSize, stdin) == NULL) {
            perror("Error reading binary data");
            return 2;//exit with error code 2
        }
    }

    //check that the input is a number (would only be something other than 1s and 0s if the previous program failed)
    unsigned char *p = binaryData;
    while (*p != '\0') {
        if (!isdigit(*p) && *p != '\n') {
            printf("Invalid input\n");
            return 2;//exit with error code 2
        }
        p++;
    }
    
    // ---the actual program---

    // Convert binary data to hex
    BinaryToHex(binaryData, hexData);

    // Print the hex data
    printf("%s\n", hexData);

    //return 0 to indicate success
    return 0;
}

//functions
void BinaryToHex(char *binaryData, char *hexData){
    int hexIndex = 0;

    while (*binaryData != '\0')
    {
        if (*(binaryData + 1) == '\0' || 
            *(binaryData + 2) == '\0' || 
            *(binaryData + 3) == '\0') {
            break;
        }
        int value = 0;

        // Convert each nibble into a decimal value
        for (int i = 0; i < 4; i++) {
            value <<= 1; // Shift the value left by 1 bit
            if (binaryData[i] == '1') {
                value |= 1; // Set the least significant bit
            }
        }

        // Convert the value to a hexadecimal character
        if (value < 10) {
            hexData[hexIndex++] = '0' + value;
        } else {
            hexData[hexIndex++] = 'A' + (value - 10);
        }

        binaryData += 4; // Move to the next nibble
    }
    hexData[hexIndex++] = '\0'; // Add the null terminator
}