/*
 * Course: CSE109
 * Semester and Year: Fall 2019
 * Assignment: cURL
 * File Purpose: a description of this file
 * Author: Bekele, Mickias
 * User ID: mib222
 */



#include <stdio.h>       /* for fprintf, sprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* error handling */
#include <string.h>      /* for string functions */
#include <curl/curl.h> //library for curl operations
#include <sys/stat.h> //for some curl operations
#include <fcntl.h>
#include "ftp_file.h"  //header file that links ftp_file.c struct
#include "prog3_funcs.h"  //header file that declares the functions in prog3_funcs.c


//parseArgs used to parse arguments and assign all the arguments
void parseArgs(int argc, char **argv, char **ifile, char **ofile, char **kfile, char **server, char **userID, char **password, char **directory){
    int length; //for storing the length of file's name and mallocing the ifile, ofile or kfile
    //if the user doesn't input any command line argument or inputs -h
    if(argc <= 1 || (strcasecmp(argv[1], "-h") == 0) || (strcasecmp(argv[1], "--help") == 0)){
        help(); //prints help function
    }
    else if(argc > 15){ //if the argument is greater than 15
        bail(1, "Incorrect/unexpected argument entered, run without any argumentts or with -h|--help for help"); //error return code: 1
    }
    
    if(argc >= 2 && argc <= 14){ //if the number of argument is between 2 to 14
        int i;
        
        for(i = 0; i < argc; i++){ //for loop for each input or argv
            //if the user either inputs the letters or words listed below in the if parameter
            if((strcasecmp(argv[1], "-i") == 0 || strcasecmp(argv[1], "--input") == 0 || strcasecmp(argv[1], "-o") == 0 || strcasecmp(argv[1], "--output") == 0 || strcasecmp(argv[1], "-k") == 0 || strcasecmp(argv[1], "--key") == 0 || strcasecmp(argv[1], "-s") == 0 || strcasecmp(argv[1], "--server") == 0 || strcasecmp(argv[1], "-d") == 0 || strcasecmp(argv[1], "--directory") == 0 || strcasecmp(argv[1], "-u") == 0 || strcasecmp(argv[1], "--userID") == 0 || strcasecmp(argv[1], "-p") == 0 || strcasecmp(argv[1], "--password") == 0) || (strcasecmp(argv[3], "-i") == 0 || strcasecmp(argv[3], "--input") == 0 || strcasecmp(argv[3], "-o") == 0 || strcasecmp(argv[3], "--output") == 0 || strcasecmp(argv[3], "-k") == 0 || strcasecmp(argv[3], "--key") == 0 || strcasecmp(argv[3], "-s") == 0 || strcasecmp(argv[3], "--server") == 0 || strcasecmp(argv[3], "-d") == 0 || strcasecmp(argv[3], "--directory") == 0 || strcasecmp(argv[3], "-u") == 0 || strcasecmp(argv[3], "--userID") == 0 || strcasecmp(argv[3], "-p") == 0 || strcasecmp(argv[3], "--password") == 0) || (strcasecmp(argv[5], "-i") == 0 || strcasecmp(argv[5], "--input") == 0 || strcasecmp(argv[5], "-o") == 0 || strcasecmp(argv[5], "--output") == 0 || strcasecmp(argv[5], "-k") == 0 || strcasecmp(argv[5], "--key") == 0 || strcasecmp(argv[5], "-s") == 0 || strcasecmp(argv[5], "--server") == 0 || strcasecmp(argv[5], "-d") == 0 || strcasecmp(argv[5], "--directory") == 0 || strcasecmp(argv[5], "-u") == 0 || strcasecmp(argv[5], "--userID") == 0 || strcasecmp(argv[5], "-p") == 0 || strcasecmp(argv[5], "--password") == 0) || (strcasecmp(argv[7], "-i") == 0 || strcasecmp(argv[7], "--input") == 0 || strcasecmp(argv[7], "-o") == 0 || strcasecmp(argv[7], "--output") == 0 || strcasecmp(argv[7], "-k") == 0 || strcasecmp(argv[7], "--key") == 0 || strcasecmp(argv[7], "-s") == 0 || strcasecmp(argv[7], "--server") == 0 || strcasecmp(argv[7], "-d") == 0 || strcasecmp(argv[7], "--directory") == 0 || strcasecmp(argv[7], "-u") == 0 || strcasecmp(argv[7], "--userID") == 0 || strcasecmp(argv[7], "-p") == 0 || strcasecmp(argv[7], "--password") == 0) || (strcasecmp(argv[9], "-i") == 0 || strcasecmp(argv[9], "--input") == 0 || strcasecmp(argv[9], "-o") == 0 || strcasecmp(argv[9], "--output") == 0 || strcasecmp(argv[9], "-k") == 0 || strcasecmp(argv[9], "--key") == 0 || strcasecmp(argv[9], "-s") == 0 || strcasecmp(argv[9], "--server") == 0 || strcasecmp(argv[9], "-d") == 0 || strcasecmp(argv[9], "--directory") == 0 || strcasecmp(argv[9], "-u") == 0 || strcasecmp(argv[9], "--userID") == 0 || strcasecmp(argv[9], "-p") == 0 || strcasecmp(argv[9], "--password") == 0) || (strcasecmp(argv[11], "-i") == 0 || strcasecmp(argv[11], "--input") == 0 || strcasecmp(argv[11], "-o") == 0 || strcasecmp(argv[11], "--output") == 0 || strcasecmp(argv[11], "-k") == 0 || strcasecmp(argv[11], "--key") == 0 || strcasecmp(argv[11], "-s") == 0 || strcasecmp(argv[11], "--server") == 0 || strcasecmp(argv[11], "-d") == 0 || strcasecmp(argv[11], "--directory") == 0 || strcasecmp(argv[11], "-u") == 0 || strcasecmp(argv[11], "--userID") == 0 || strcasecmp(argv[11], "-p") == 0 || strcasecmp(argv[11], "--password") == 0) || (strcasecmp(argv[13], "-i") == 0 || strcasecmp(argv[13], "--input") == 0 || strcasecmp(argv[13], "-o") == 0 || strcasecmp(argv[13], "--output") == 0 || strcasecmp(argv[13], "-k") == 0 || strcasecmp(argv[13], "--key") == 0 || strcasecmp(argv[13], "-s") == 0 || strcasecmp(argv[13], "--server") == 0 || strcasecmp(argv[13], "-d") == 0 || strcasecmp(argv[13], "--directory") == 0 || strcasecmp(argv[13], "-u") == 0 || strcasecmp(argv[13], "--userID") == 0 || strcasecmp(argv[13], "-p") == 0 || strcasecmp(argv[13], "--password") == 0)){
                
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
                    //if the user inputs -s and doesn't input anything after that
                    else if(((strcasecmp(argv[i+1], "-s") == 0) || (strcasecmp(argv[i+1], "--server") == 0)) && argv[i+2] == NULL){
                        bail(6, "No argument after '-s|--server'"); //error return code: 6
                    }
                    //if the user inputs -d and doesn't input anything after that
                    else if(((strcasecmp(argv[i+1], "-d") == 0) || (strcasecmp(argv[i+1], "--directory") == 0)) && argv[i+2] == NULL){
                        bail(7, "No argument after '-d|--directory'"); //error return code: 7
                    }
                    //if the user inputs -u and doesn't input anything after that
                    else if(((strcasecmp(argv[i+1], "-u") == 0) || (strcasecmp(argv[i+1], "--userID") == 0)) && argv[i+2] == NULL){
                        bail(8, "No argument after '-u|--userID'"); //error return code: 8
                    }
                    //if the user inputs -p and doesn't input anything after that
                    else if(((strcasecmp(argv[i+1], "-p") == 0) || (strcasecmp(argv[i+1], "--password") == 0)) && argv[i+2] == NULL){
                        bail(9, "No argument after '-p|--password'"); //error return code: 9
                    }
                    //if the user inputs anything after -k
                    if((strcasecmp(argv[i+1], "-k") == 0 || strcasecmp(argv[i+1], "--key") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of string containing kfile
                        *kfile = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*kfile, argv[i+2]); //copies the string to the kfile buffer
                        bail(2, "One or more arguments not specified"); //error return code: 2
                    }
                    //if the user inputs anything after -i
                    else if((strcasecmp(argv[i+1], "-i") == 0 || strcasecmp(argv[i+1], "--input") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of the string containing ifile
                        *ifile = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*ifile, argv[i+2]); //copies the string to the ifile
                        bail(2, "One or more arguments not specified"); //error return code: 2
                    }
                    //if the user inputs anything after -o
                    else if((strcasecmp(argv[i+1], "-o") == 0 || strcasecmp(argv[i+1], "--output") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of the string containing ofile
                        *ofile = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*ofile, argv[i+2]); //copies the string to the file
                        bail(2, "One or more arguments not specified"); //error return code: 2
                    }
                    //if the user inputs anything after -s
                    else if((strcasecmp(argv[i+1], "-s") == 0 || strcasecmp(argv[i+1], "--server") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of the string containing ofile
                        *server = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*server, argv[i+2]); //copies the string to the file
                        bail(2, "One or more arguments not specified"); //error return code: 2
                    }
                    //if the user inputs anything after -d
                    else if((strcasecmp(argv[i+1], "-d") == 0 || strcasecmp(argv[i+1], "--directory") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of the string containing ofile
                        *directory = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*directory, argv[i+2]); //copies the string to the file
                        bail(2, "One or more arguments not specified"); //error return code: 2
                    }
                    //if the user inputs anything after -u
                    else if((strcasecmp(argv[i+1], "-u") == 0 || strcasecmp(argv[i+1], "--userID") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of the string containing ofile
                        *userID = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*userID, argv[i+2]); //copies the string to the file
                        bail(2, "One or more arguments not specified"); //error return code: 2
                    }
                    //if the user inputs anything after -p
                    else if((strcasecmp(argv[i+1], "-p") == 0 || strcasecmp(argv[i+1], "--password") == 0) && argv[i+3] == NULL){
                        length = strlen(argv[i+2]); //takes in the length of the string containing ofile
                        *password = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that is the string's length
                        strcpy(*password, argv[i+2]); //copies the string to the file
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
        for(j = 0; j < argc; j++){ //second for loop
            if(strcasecmp(argv[j], "-k") == 0 || strcasecmp(argv[j], "--key") == 0){ //for the key file
                length = strlen(argv[j+1]); //takes in the length of the string
                *kfile = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*kfile, argv[j+1]); //copies the name to kfile buffer
            }
            else if(strcasecmp(argv[j], "-i") == 0 || strcasecmp(argv[j], "--input") == 0){//for the input file
                length = strlen(argv[j+1]); //takes in the length of the string
                *ifile = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*ifile, argv[j+1]); //copies the name to ifile buffer
            }
            else if(strcasecmp(argv[j], "-o") == 0 || strcasecmp(argv[j], "--output") == 0){ //for the output file
                length = strlen(argv[j+1]); //takes in the length of the string
                *ofile = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*ofile, argv[j+1]); //copies the name to ofile buffer
            }
            else if(strcasecmp(argv[j], "-s") == 0 || strcasecmp(argv[j], "--server") == 0){//for the input file
                length = strlen(argv[j+1]); //takes in the length of the string
                *server = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*server, argv[j+1]); //copies the name to server buffer
            }
            else if(strcasecmp(argv[j], "-d") == 0 || strcasecmp(argv[j], "--directory") == 0){//for the input file
                length = strlen(argv[j+1]); //takes in the length of the string
                *directory = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*directory, argv[j+1]); //copies the name to directory buffer
            }
            else if(strcasecmp(argv[j], "-u") == 0 || strcasecmp(argv[j], "--userID") == 0){//for the input file
                length = strlen(argv[j+1]); //takes in the length of the string
                *userID = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*userID, argv[j+1]); //copies the name to userID buffer
            }
            else if(strcasecmp(argv[j], "-p") == 0 || strcasecmp(argv[j], "--password") == 0){//for the input file
                length = strlen(argv[j+1]); //takes in the length of the string
                *password = (char *)Malloc((length+1)*sizeof(char *)); //mallocs spaces that's the string length
                strcpy(*password, argv[j+1]); //copies the name to password buffer
            }
            
        }//end of the for loop
    }
    
}

//Malloc mallocs space for void *buffer
void *Malloc (size_t size){ //parameter: size
    void *ptr = NULL; //setting a ptr void to NULL
    ptr = malloc(size); //assign the ptr a size length spaces
    char error[100]; //declaring the error array
    if(ptr == NULL){ //if the malloc is not successful
        sprintf(error, "Could not allocate space - %s", strerror(errno)); //concatinating the error to the string and strerror at the errno index
        bail(99, error); //error return code: 99
    }//end of if statemtn
    return ptr; //return ptr
}

//Fopen opens file with the filename
FILE *Fopen(const char *file, const char *mode){ //parameter: filename, mode
    FILE *fp; //declares fp for containing file
    fprintf(stdout, "%s", file);
    fp = fopen(file, mode); //opens the file name stores it in fp
    char error[100]; //declaring the error
    if(fp == NULL){ //if there is no file or unable to open it
        sprintf(error, "Unable to open %s with mode %s - %s", file, mode, strerror(errno)); //concatenating the error with the string and strerror on the errno index
        bail(10, error);//error return code: 13
    }
    //if(file) free((char *)file);//frees the file's name to prin the valgrind memory leak
    return fp; //return the file fp
}

//readKey checks if the key file is greater or equal to 16 bytes
void readKey(char *keyBuffer, size_t size, FILE *keyFile){ //param: keybuffer, size, keyFile
    fseek(keyFile, 0, SEEK_END); //seeks the position of the file
    long length = ftell(keyFile); //stores the length of the file
    fseek(keyFile, 0, SEEK_SET); //at the end of file
    char error[100]; //declaring the error character
    if(length < (long) size){ //if the length of file is less than 16 bytes
        sprintf(error, "Key is fewer bytes than expected"); //concatenating the error string to the string and strerror at the errno index
        bail(20, error); //error return code: 20
    }
    readKeyData(keyBuffer, keyFile); //calls readKeyData
}

//encryptDecrypt encrypts/decrypts files
void encryptDecrypt(char *block, char *buffer, FILE *input, FILE *output){ //parameter: buffer, keybuffer, input file, output file
    ssize_t x; //to hold the value for getline
    char error[256]; //error buffer
    size_t len = 0;
    if(ferror(input)){ //if there is error with th file
        sprintf(error, "Error reading file - %s", strerror(errno));
        bail(11, error); //bail, rc: 11
    }
    x = getline(&block, &len, input); //reads the file line by line
    int a = 0;
    while(x >= 0){ //if there is anything on the line
        printf("\n");
        for(int i = 0; i < (int)x - 1; i++){ //uses for loop to iterate through each character for XOR encryption/decryption
            int x = strlen(buffer);
            if(i > 0 && (i % x == 0)){
                a = 0;
            }
            fprintf(stdout, "(%#04X) ^ (%#04X) = ", block[i], buffer[a]); //prints the XOR operation
            
            block[i] = block[i] ^ buffer[a]; //performs XOR operation
            fprintf(stdout, "(%#04X) \n", block[i]);
            a++;
        }
        writeData(block, sizeof(char), x-1, output); //writes the encrypted/decrypted character to the file
        x = getline(&block, &len, input);
    }
    free(block); //frees buffer
}

//readKeyData reads each character from the key file
void readKeyData(char *buffer, FILE *file){ //parameter: keybuffer, keyfile
    char *read = NULL; //initialize the key buffer to NULL
    ssize_t x;
    size_t size = 0;
    if(ferror(file)){ //if there is error with the file
        char error[256];
        sprintf(error, "Error reading file - %s", strerror(errno));
        bail(11, error); //bail, rc: 11
    }
    x = getline(&read, &size, file); //reads file on each line
    while(x >= 0){ //if there is anything on each line
        sprintf(buffer, "%s", read); //assigns each character to the buffer
        x = getline(&read, &size, file);
    }
    free(read); //free the keybuffer
}

//writeData writes each character to output file
size_t writeData(const void *buffer, size_t size, size_t count, FILE *file){ //parameter: buffer, size, count, file
    size_t rc = fwrite(buffer, size, count, file); //uses fwrite to write
    char error[256]; //to hold the err
    if(ferror(file)){ //if there is error with the file
        sprintf(error, "Error writing file - %s", strerror(errno));
        bail(12, error); //bail, rc: 12
    }
    return rc; //returns the number of bytes written
}

//ftpDownload downloads files from the server to the directory
int ftpDownload(char *server, char *userID, char *directory, char *password, char *ifile){ //parameter: serer, userID, directory, password, ifile
    char string[128]; //to hold the whole URL
    CURLcode rc; //to hold the whole curl_perform
    CURL *ptr = NULL; //pointer for the curl_easy_init()
    ftp_file FTP = {ifile, NULL}; //initialize a new struct
    curl_global_init(CURL_GLOBAL_ALL); //begin the curl operation
    ptr = curl_easy_init(); //assign the pointer to the curl_easy_init
    if(ptr){ //if it is successful
        sprintf(string, "%s:%s", userID, password); //concatenating the userID/password to the string
        curl_easy_setopt(ptr, CURLOPT_USERPWD, string); //authenticates with the credentials
        sprintf(string, "sftp://%s/%s/%s", server, directory, ifile); //concatenates the directory
        curl_easy_setopt(ptr, CURLOPT_URL, string); //authenticates with the URL
        //adds all parameters to the curl_easy_setopt
        curl_easy_setopt(ptr, CURLOPT_WRITEFUNCTION, ftpWrite);
        curl_easy_setopt(ptr, CURLOPT_WRITEDATA, &FTP);
        curl_easy_setopt(ptr, CURLOPT_VERBOSE, 1L);
        rc = curl_easy_perform(ptr); //performs with all the collected data
        curl_easy_cleanup(ptr); //cleans up the pointer
    }
    else{ //if its not successful
        bail(99, "Initialization of curl session/transfer handle was unsuccessful"); //bail, rc: 99
    }
    if(FTP.file){
        Fclose(FTP.file); //close the file
    }
    curl_global_cleanup(); //calls the global cleanup()
    return (int)rc; //returns the casted int rc
    
}

//readfunc is used for the ftpUpload to read all the information from the file
size_t readfunc(void *ptr, size_t size, size_t nmeb, void *stream){ //parameter: buffer, size, count, file
    FILE *f = (FILE *)stream; //cast the stream to FILE
    size_t n;
    n = fread(ptr, size, nmeb, f) * size;  //reads the all the characters
    return n; //return the total number of bytes
}

//ftpUpload uploads the file to the server
int ftpUpload(char *server, char *userID, char *directory, char *password, FILE *output, char *ofile){ //parameter: server, userID, directory, password, output file, output file name
    CURL *ptr; //to hold the curl pointer
    CURLcode rc; //to hold the return code
    char string[128]; //to hold the directory and userID, password
    ptr = curl_easy_init(); //assign the pointer to the curl_easy_init()
    if(ptr){ //if its successful
        curl_easy_setopt(ptr, CURLOPT_UPLOAD, 1L); //adds the UPLOAD parameter to curl_easy_setopt
        sprintf(string, "%s:%s", userID, password); //concatenates the userID:password to string
        curl_easy_setopt(ptr,CURLOPT_USERPWD, string); //autenticates
        sprintf(string, "sftp://%s/%s/%s", server, directory, ofile); //concatenates the directory to the string
        curl_easy_setopt(ptr, CURLOPT_URL,string); //collects the information about the directory
        //adds all information to curl_easy_setopt
        curl_easy_setopt(ptr, CURLOPT_NEW_FILE_PERMS, 0644L);
        curl_easy_setopt(ptr, CURLOPT_READFUNCTION, readfunc);
        curl_easy_setopt(ptr, CURLOPT_READDATA, output);
        curl_easy_setopt(ptr, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(ptr, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(ptr, CURLOPT_APPEND, 1L);
        rc = curl_easy_perform(ptr); //performs the curl operation
        curl_easy_cleanup(ptr); //cleans up the pointer
    }
    else{ //if its unsuccesfull
        bail(99, "Initialization of curl session/transfer handle was unsuccessful"); //bail, rc: 99
    }
//        if(userID) free((char *)userID); //frees userID
//        if(password) free((char *)password); //frees password
//        if(directory) free((char *)directory); //frees directory
//        if(server) free((char *)server); //frees server
    if(output){
        Fclose(output); //closes the output file
    }
    curl_global_cleanup(); //calls the global_cleanup
    return (int)rc; //return the casted int version of rc
}

//ftpWrite writes all the information to file from ftpDownload
size_t ftpWrite(void *buff, size_t size, size_t count, void *file){ //parameter: buffer, size, count, filename
    ftp_file *output = (struct ftpfile *)file; //casts the file to struct
    if(!output->file){
        output->file = Fopen(output->filename, "w+"); //opens the file with mode w+
    }
    return writeData(buff, size, count, output->file); //calls the writeData
}

//calculateValue calculates the value
void calculateValue(FILE *first,FILE *second){ //parameter: first file, result file
    char *buffer = NULL;
    ssize_t x;
    size_t len = 0;
    signed int firstNum; //integer to hold the first number
    signed int secondNum; //integer to hold the second number
    signed int result; //integer to hold the result
    char c; //to hold the operator
    x = getline(&buffer, &len, first); //reads the file line by lin
     char write[128];
    while(x>=0){
        sscanf(buffer, "%d %c %d", &firstNum, &c, &secondNum); //assign the first number, operator, second number
        sprintf(write, "%d %c %d = ", firstNum, c, secondNum);
        if(c == '+'){ //if its addition
            result = firstNum + secondNum; //adds
        }
        else if(c == '*'){ //if it's multiplication
            result = firstNum * secondNum; //multiplies
        }
        else if(c == '-'){ //if it's subtraction
            result = firstNum - secondNum; //subtracts
        }
        else if(c == '/'){ //if division
            result = firstNum/secondNum;
        }
        else if(c == '%'){ //if its remainder
            result = firstNum % secondNum;
        }
        char write[128]; //to hold the result buffer
        sprintf(write, "%d %c %d = %d", firstNum, c, secondNum, result);
        //sprintf(write, "%d", result); //assigns the result to write buffer
        writeData(write, sizeof(char), strlen(write), second); //calls writeData
        x = getline(&buffer, &len, first);
    }
    free(buffer); //frees the buffer
    
}

//Fcloses closes the file
void Fclose(FILE *file){ //parameter: filew
    char error[100]; //declares the error character
    int rc = fclose(file);
    if(rc != 0){ //if there is error in closing file
        sprintf(error, "Unable to close file - %s", strerror(errno)); //concatenating the error with the string and strerror at the errno index
        bail(13, error); //error return codemake: 13
    }//end of if statement
    
}

//bail bails with error
void bail(int errnum, const char *error){ //parameteR: err number, error
    fprintf(stderr, "(%d) %s \n", errnum, error);
    exit(errnum); //exits with the err number
    
}

//help is to print all the information needed
void help(){
    fprintf(stdout, "prog3 securely downloads an encrypted calculation file, decrypts the calculation file using a \n unique key, performs the arithmetic operation in the calculation file, generates a results file \n containing the arithmetic operation and its result, encrypts the results file, and securely uploads \n the encrypted results file. Run program as follows. \n \n prog3 -i|--input <calculation file> -o|--output <results file> -k|--key <key file> -s|--server <server_name> \n -d|--directory <directory_on_server> -u|--userid <userID> -p|--password <password> \n or \n prog3 [-h|--help] \n");
    exit(0); //exits
}


