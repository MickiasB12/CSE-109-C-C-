/*
 * Course: CSE109
 * Semester and Year: Fall 2019
 * Assignment: cURL
 * File Purpose: a description of this file
 * Author: Bekele, Mickias
 * User ID: mib222
 */
#ifndef PROG2_FUNCS //for header files
#define PROG3_FUNCS

void parseArgs(int, char**, char **, char **, char **, char **, char **, char **, char **); //takes command line args and assign pointers
void *Malloc (size_t); //takes in size_t size and mallocs
FILE *Fopen(const char *, const char *); //takes the filename and mode, and opens the file
void encryptDecrypt(char *, char *, FILE *, FILE *); //parameter: buffer, keybuffer, input file, output file, encrypts/decrypts the file
void readKey(char *, size_t, FILE *); //param: keybuffer, size, keyFile, check if the number of bytes in key is 16
void readKeyData(char *, FILE *); //parameter: keybuffer, keyfile, reads the key
size_t writeData(const void *, size_t, size_t, FILE *);  //parameter: buffer, size, count, file, writes
void calculateValue(FILE *,FILE *); //parameter: first file, result file, calculates value
int ftpDownload(char *, char *, char *, char *, char *); //parameter: serer, userID, directory, password, ifile, returns the CURLcod
int ftpUpload(char *, char *, char *, char *, FILE *, char *); //parameter: server, userID, directory, password, output file, output file name, returns CURLcode
size_t ftpWrite(void *, size_t, size_t, void *);  //parameter: buffer, size, count, filename, returns the number of bytes writen
size_t readfunc(void *, size_t, size_t, void *); //parameter: buffer, size, count, file, returns the number of bytes read
void Fclose(FILE *); //closes file
void bail(int, const char *); //bails
void help(); //prints all information




#endif
