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


//main method is where all executions is executed
int main(int argc, char *argv[]) { //parameter: argc, argv[]
    FILE *keyfile = NULL; //file that holds key
    char keybuffer[16]; //char buffer to hold the key from the key file
    char *ifile = NULL; //File that is considered as the input
    char *kfile = NULL; //char that holds command line arg for key file
    char *ofile = NULL; //char that holds command
    char *server = NULL; //char that holds command line arg for server
    char *userID = NULL; //char that holds command line arg for userID
    char *password = NULL; //char that holds command line arg for password
    char *directory = NULL; //char that holds command line arg for directory
    FILE *input = NULL; //input file
    FILE *output = NULL; //output file
    char *buffer = NULL;
    char *block = NULL;
    size_t size = 16;  //to check if the key file has 16 bytes
    FILE *out2 = NULL;
    
    parseArgs(argc, argv, &ifile, &ofile, &kfile, &server, &userID, &password, &directory);    //parses arguments and assign pointers according to the argv
    keyfile = Fopen(kfile, "r"); //opens keyfile with mode r
    
    free(kfile);  //frees the kfile buffer
    char str[128]; //to hold the ifile buffer
    strcpy(str, ifile); //copies the ifile to str
    readKey(keybuffer, size, keyfile);  //reads key and assign it to the buffer
    int ret = ftpDownload(server, userID, directory, password, ifile); //downloads the file from the server to the directory
    if(ret){ //if download is unsuccessful
        char error[256];
        sprintf(error, "Download unsuccesfull - %s", curl_easy_strerror(ret));
        bail(15, error);  //call bail, rc: 15
    }
    
    free(ifile); //frees the ifile
    input = Fopen(str, "r+"); //opens the input file with mode r+
    output = Fopen("result.enc", "w+"); //opens an intermediatery file to hold the result file
    FILE *intermediate = NULL;
    intermediate = Fopen("calculate.enc", "w+");  //opens an intermediatry file to hold the calculated result with mode w+
    FILE *x = Fopen("calculate.enc", "r"); //opens the file to be calculated with mode r
    
    encryptDecrypt(block, keybuffer, input, intermediate);  /* encrypt/decrypt the input file and write to output file */
    Fclose(intermediate); //closes the calculated file
    calculateValue(x, output); //perform the calculation
    Fclose(x); //closes the calculated intermediate file
    Fclose(output); //closes the output file
    out2 = Fopen("result.enc", "r"); //opens the calculated file with mode r
    FILE *final = Fopen(ofile, "w+"); //opens the output file with mode w+
    
    encryptDecrypt(buffer, keybuffer, out2, final); //encrypts the calculated file to the output file
    Fclose(final); //closes the final file
    FILE *y = Fopen(ofile, "r+"); //opens the output file with mode r+
    ret = ftpUpload(server, userID, directory, password, y, ofile); //uploads the output file to the server
    
    if(ret != CURLE_OK){ //if upload is unsuccesfull
        char err[256];
        sprintf(err, "Upload unsuccesfull - %s", curl_easy_strerror(ret));
        bail(16, err); //bail statement,rc: 16
    }
    char command[256];
    memmove(directory, directory+5, strlen(directory)-5 +1);
   sprintf(command, "chmod 644 ~%s/%s", directory, ofile);
  system(command);
    
    Fclose(keyfile); //closes the key file
    Fclose(input); //closes the input file
    
    //Remove all the intermediate, output and inpt files
    int status = remove("calculate.enc");  //removes intermediate
    if(status != 0){ //if not successful
        bail(99, "Unable to delete calculate.enc"); //call bail
    }
    status = remove("result.enc"); //removes intermediate
    if(status != 0){
        bail(99, "Unable to delete result.enc");
    }
    status = remove(ofile); //removes the output file
    if(status != 0){
        char e[256];
        sprintf(e, "Unable to delete %s", ofile);
        bail(99, e); //bail
    }
    status = remove(str); //removes the input file
    if(status != 0){
        char e[256];
        sprintf(e, "Unable to delete %s", str);
        bail(99, e); //bail
    }
    free(ofile); //finally frees the output file character
    if(userID) free((char *)userID); //frees userID
    if(password) free((char *)password); //frees password
    if(directory) free((char *)directory); //frees directory
    if(server) free((char *)server); //frees server
    
    return ret; //if successful, return 0
}

