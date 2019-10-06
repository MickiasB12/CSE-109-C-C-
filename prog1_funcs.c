/*
 Name: Mickias Bekele
 CSE109
 Assignment: Prog1
 Purpose: We are creating a program that performs xor encrypting and decrypting files
 using fread, fwrite and other standard file functions.
 
 */
#include<stdio.h> //standard output for I/O operations
#include<stdlib.h> //header for standard library
#include<errno.h> //header for error strings and errno
#include<string.h> //header for string functions such as strcpy(), strcmp()....
#include "prog1_funcs.h" //header that links prog1_funcs.c and prog1.c for running
//DEBUG macro setup for both DEBUG and NODEBUG running
#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

//ParseArgs is for parsing command line arguments and check for errors in the command line
void parseArgs(int argc, char **argv, char **ifile, char **ofile, char **kfile){
    int length; //for storing the length of file's name and mallocing the ifile, ofile or kfile
    //if the user doesn't input any command line argument or inputs -h
    if(argc <= 1 || (strcasecmp(argv[1], "-h") == 0) || (strcasecmp(argv[1], "--help") == 0)){
        help(); //prints help function
    }
    else if(argc > 7){ //if the argument is greater than 7
        bail(1, "Incorrect/unexpected argument entered, run without any argumentts or with -h|--help for help"); //error return code: 1
    }
    
    if(argc >= 2 && argc <= 6){ //if the number of argument is between 2 to 6
        int i;
        
        for(i = 0; i < argc; i++){ //for loop for each input or argv
        //if the user either inputs the letters or words listed below in the if parameter
        if((strcasecmp(argv[1], "-i") == 0 || strcasecmp(argv[1], "--input") == 0 || strcasecmp(argv[1], "-o") == 0 || strcasecmp(argv[1], "--output") == 0 || strcasecmp(argv[i+1], "-k") == 0 || strcasecmp(argv[1], "--key") == 0) || (strcasecmp(argv[3], "-i") == 0 || strcasecmp(argv[3], "--input") == 0 || strcasecmp(argv[3], "-o") == 0 || strcasecmp(argv[3], "--output") == 0 || strcasecmp(argv[3], "-k") == 0 || strcasecmp(argv[3], "--key") == 0) || (strcasecmp(argv[5], "-i") == 0 || strcasecmp(argv[5], "--input") == 0 || strcasecmp(argv[5], "-o") == 0 || strcasecmp(argv[5], "--output") == 0 || strcasecmp(argv[5], "-k") == 0 || strcasecmp(argv[5], "--key") == 0)){
            //if the user doesn't input anything after -i
            if(((strcasecmp(argv[i+1], "-i") == 0) || (strcasecmp(argv[i+1], "--input") == 0)) && argv[i+2] == NULL){
                bail(3, "No argument after '-i|--input'"); //error return code: 3
                
            }
            //if the user inputs -o and doesn't input anyting after that
            else if(((strcasecmp(argv[i+1], "-o") == 0) || (strcasecmp(argv[i+1], "--output") == 0)) && argv[i+2] == NULL){
                bail(4, "No argument after '-o|--output'"); //error return code: 4
                
            }
            //if the user inputs -k and doesn't input anything after that
            else if(((strcasecmp(argv[i+1], "-k") == 0) || (strcasecmp(argv[i+1], "--key") == 0)) && argv[i+2] == NULL){
                bail(5, "No argument after '-k|--key'"); //error return code: 5
            }
            //if the user inputs anything after -k
            if((strcasecmp(argv[i+1], "-k") == 0 || strcasecmp(argv[i+1], "--key") == 0) && argv[i+3] == NULL){
                length = strlen(argv[i+2]); //takes in the length of string containing kfile
                *kfile = Malloc((length+1)*sizeof(char*)); //mallocs spaces that is the string's length
                strcpy(*kfile, argv[i+2]); //copies the string to the kfile buffer
                bail(2, "One or more arguments not specified"); //error return code: 2
            }
            //if the user inputs anything after -i
            else if((strcasecmp(argv[i+1], "-i") == 0 || strcasecmp(argv[i+1], "--input") == 0) && argv[i+3] == NULL){
                length = strlen(argv[i+2]); //takes in the length of the string containing ifile
                *ifile = Malloc((length+1)*sizeof(char*)); //mallocs spaces that is the string's length
                strcpy(*ifile, argv[i+2]); //copies the string to the ifile
                bail(2, "One or more arguments not specified"); //error return code: 2
            }
            else if((strcasecmp(argv[i+1], "-o") == 0 || strcasecmp(argv[i+1], "--output") == 0) && argv[i+3] == NULL){
                length = strlen(argv[i+2]); //takes in the length of the string containing ofile
                *ofile = Malloc((length+1)*sizeof(char*)); //mallocs spaces that is the string's length
                strcpy(*ofile, argv[i+2]); //copies the string to the file
                bail(2, "One or more arguments not specified"); //error return code: 2
            }
        }//end of the first if statement
        //if the user doesn't input anything similar to the earlier one
        else{
            bail(1, "Incorrect/unexpected argument entered, run without any argumentts or with -h|--help for help"); //error return code: 1
            }
        }
        
    }//end of the for loop
    else{ //if the user succesfully inputs everything
        int j;
        for(j = 0; j < 6; j++){ //second for loop
            if(strcasecmp(argv[j], "-k") == 0 || strcasecmp(argv[j], "--key") == 0){ //for the key file
                length = strlen(argv[j+1]); //takes in the length of the string
                *kfile = Malloc((length+1)*sizeof(char*)); //mallocs spaces that's the string length
                strcpy(*kfile, argv[j+1]); //copies the name to kfile buffer
            }
            else if(strcasecmp(argv[j], "-i") == 0 || strcasecmp(argv[j], "--input") == 0){//for the input file
                length = strlen(argv[j+1]); //takes in the length of the string
                *ifile = Malloc((length+1)*sizeof(char*)); //mallocs spaces that's the string length
                strcpy(*ifile, argv[j+1]); //copies the name to ifile buffer
            }
            else if(strcasecmp(argv[j], "-o") == 0 || strcasecmp(argv[j], "--output") == 0){ //for the output file
                length = strlen(argv[j+1]); //takes in the length of the string
                *ofile = Malloc((length+1)*sizeof(char*)); //mallocs spaces that's the string length
                strcpy(*ofile, argv[j+1]); //copies the name to ofile buffer
        }
    }//end of the for loop
}
                               
}//end of parseArgs method

//Malloc method is uses for mallocing and allocating spaces
void *Malloc(size_t size){ //paramater size for the allocation space
    void *ptr = NULL; //setting a ptr void to NULL
    ptr = malloc(size); //assign the ptr a size length spaces
    char error[100]; //declaring the error array
    if(ptr == NULL){ //if the malloc is not successful
        sprintf(error, "Could not allocate space - %s", strerror(errno)); //concatinating the error to the string and strerror at the errno index
        bail(99, error); //error return code: 99
    }//end of if statemtn
    return ptr; //return ptr
}//end of Malloc

//Fopen method is is used for opening files
FILE *Fopen(const char *file, const char *mode){ //parameter containing file name and with mode
    FILE *fp; //declares fp for containing file
    fp = fopen(file, mode); //opens the file name stores it in fp
    char error[100]; //declaring the error
    if(fp == NULL){ //if there is no file or unable to open it
        sprintf(error, "Unable to open %s with mode %s - %s", file, mode, strerror(errno)); //concatenating the error with the string and strerror on the errno index
        bail(13, error);//error return code: 13
    }
    free(file);//frees the file's name to fix the valgrind memory leak
    return fp; //return the file fp
}

//readKey method to read all the strings in key.bin
void readKey(unsigned char *buffer, size_t size, FILE *fkp){ //parameter: key buffer, size of keyfile, keyfile
    fseek(fkp, 0, SEEK_END); //seeks the position of the file
    long length = ftell(fkp); //stores the length of the file
    fseek(fkp, 0, SEEK_SET); //at the end of file
    char error[100]; //declaring the error character
    if(length < (long) size){ //if the length of file is less than 16 bytes
        sprintf(error, "Key is fewer bytes than expected"); //concatenating the error string to the string and strerror at the errno index
        bail(20, error); //error return code: 20
    }
    Fread(buffer, sizeof(char), size, fkp); //reads the file name and stores it in a buffer
} //end of the readKey method

//encryptDecrypt method to encrypt and decrypt files
void encryptDecrypt(unsigned char *block, unsigned char *buffer, size_t size, FILE *fip, FILE *fop){//parameter: block characters from input and output file, key buffer, size, input file fip, output file fop
    size_t length; //length for storing the length of the input file
    int i; //for the for loop
    char error[100]; //declaring the error character
    while(!feof(fip)){ //runs until the end of file
        length = Fread(block, sizeof(char), size, fip); //reads the input file and returns the number of bytes
        for(i = 0; i < (int) length - 1; i++){ //for loop iterating through each character in the buffer and xor encrypting/decrypting file
            if(DEBUG){
                fprintf(stdout, "%c (%#04X) ^ %c (%#04X) = ", block[i], block[i], buffer[i], buffer[i]); //prints the hexadecimal of of input characters and key characters
            }
            block[i] = block[i] ^ buffer[i]; //xor encryption
            if(DEBUG){
                fprintf(stdout, "%c (%#04X) \n", block[i], block[i]);
            }//prints the result of xor encryption
            }//end of for loop
        Fwrite(block, sizeof(char), length, fop); //writes the xor'ed character to the output file
        memset(block, 0, size); //setting the block buffer to empty
    } //end of while loop
    fseek(fip, 0, SEEK_END); //positions till the end of file
    long len = ftell(fip); //takes in the length of input file
    fseek(fip, 0, SEEK_SET); //positions at the end of file
    fseek(fop, 0, SEEK_END); //positions till end of output file
    long len2 = ftell(fop); //takes in the length of output file
    fseek(fop, 0, SEEK_SET); //positions at the end of output
    
    if(len2<len){ //if the length of output file is less than input file
        //char *error = NULL;
        sprintf(error, "Unable to write all items read"); //concatenating error with the string and strerror at the errno index
        bail(30, error); //error return code: 30
    }//end of if statement
    
} //end of encryptDecrypt method

//Fread method is reading the file and storing it in the buffer
size_t Fread(void *ptr, size_t size, size_t count, FILE *file){
    size_t x = 0; //initializing the size to 0
    x = fread(ptr, size, count, file); //reads the file and stores it in the buffer
    char error[100]; //declaring error character
    if(ferror(file)){ //if there is error in reading the file
        sprintf(error, "Error reading file - %s", strerror(errno)); //concatenating the error with the string and strerror at the errno index
        bail(11, error); //error return code: 11
    }//end of if statemtent
    return x; //return the size
}//end of Fread method
//Fwrite is used to write the xor characters to output file
size_t Fwrite(const void *buffer, size_t size, size_t count, FILE *file){ //parameter: buffer pointer, size , count, file stream
    size_t x = fwrite(buffer, size, count, file); //writes to the output and returns the number of bytes
    char error[100]; //declaring the error character
       if(ferror(file)){ //if there is an error writing output
           sprintf(error, "Error writing file - %s", strerror(errno)); //concatenating the error with the string and sterror at errno index
           bail(12, error); //error return code: 12
       }//end of if
    return x; //return the size
    
}//end of Fwrite

//Fclose closes the file
void Fclose(FILE *file){ //parameter: file stream
    char error[100]; //declares the error character
    if(fclose(file) != 0){ //if there is error in closing file
        sprintf(error, "Unable to close file - %s", strerror(errno)); //concatenating the error with the string and strerror at the errno index
        bail(13, error); //error return code: 13
    }//end of if statement
} //end of Fclose
//bail method for printing the error
void bail(int num, const char *error){ //parameter: errno, error string
    fprintf(stderr, "(%d) %s \n", num, error); //prints to the standard error
    exit(num); //exits
    
}//end of bail method

//help method used for displaying information
void help(){ //no parameter
    fprintf(stdout, "prog1 performs an XOR-based encryption/decryption on the specified input file using the \n specified key file to produce the specified output file. \n \n prog1 -i|--input <input file> -o|--output <output file> -k|--key <key file> \n or \n prog1 [-h|--help] \n \n "); //prints out to stdout
    exit(0); //exits
    
}//end of help
