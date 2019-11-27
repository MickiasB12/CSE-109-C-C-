
/*
 * Course: CSE109
 * Semester and Year: Fall 2019
 * Assignment: cURL
 * File Purpose: a description of this file
 * Author: Bekele, Mickias
 * User ID: mib222
 */
#ifndef FTP_FILE //for the headerfile
#define FTP_FILE

struct ftpfile{
    const char *filename; //to hold the filename
    FILE *file; //FILE
};
typedef struct ftpfile ftp_file; //for not repeating struct ftpfile

#endif
