/* Name: Mickias Bekele
 Course: CSE 109
 Assignment: Prog0
 Purpose: It is implemented to require the user input their first and last names and their favorite integers, which
 the program calculates the sum-of-products or product-of-sums of the ASCII value of each characters and integer.
 */
#include<stdio.h> //importing stdio library
#include<stddef.h>
#include<stdlib.h> //importing the standard library
#include<string.h> //importing the string library
#include<limits.h>
//#ifndef PROG0_FUNCS
//#define PROG0_FUNCS

char parseArgs(int x, char *y[]); //declaring the parseArgs method for parsing the command line argument
void collectInput(char **a, int *b); //declaring the collectInput method for collecting the information
size_t calcValue(char c, char **d, int e, long *f); //declaring calcValue method for calculating the values
void printResult(char g, long h, size_t i); //declaring this method for printing the result
void bail(int j, const char* k); //declaring for bailing an error

void help(); //declaring for help information

//every C program starts with the main method
//int main(int argc, char *argv[]){
//    char *name = NULL; //array of strings that hold the names
//    int number; //for the favourite integer
//    size_t unrep; //to show whether it is representable or unrepresentable
//    char op; //for parsing
//    long result; //holds the result value
//
//    op = parseArgs(argc, argv); //calling the parseArgs method for parsing the command line
//    collectInput(&name, &number);  //collect the input of the user
//
//    unrep = calcValue(op, &name, number, &result); //storing the value of size_t
//    printResult(op, result, unrep); //printing the result
//
//
//    if (name) free(name); //fixes the memory leak
//    return 0; //returns 0 as the final execution
//}

//this method is used to print out the help information
void help(){
    printf("prog0 prompts the user for their first and last name and their favorite integer and calculates the sum-of-products or product-of-sums based on the integer entered and the ASCII value of each character in the first and last name entered. Note that non-alphabetical characters, except for hyphen and apostrophe, are ignored. \n");
    printf("* If the user enters 'sop' or 'pos' (case-insensitive) as the only argument, the user will be prompted to enter their first and last name and their favorite integer, and the program will calculate the sum-of-products or product-of-sums, respectively. * If the user enters '-h' (case-insensitive) as the only argument, this help message will be displayed on stdout \n");
    printf(" * If the user does not provide any arguments or provides too many arguments, an error message is printed to stderr and the return code will be 1. \n* If the user does not provide any arguments or provides too many arguments, an error message is printed to stderr and the return code will be 1. \n* If the user enters an invalid single argument, an error message is printed to stderr and the return code will be 2. \n* If the calculation results in an overflow/underflow, the program will continue to run and operate normally, but the return code will be 3. \n* The user can expect prompts on stdout as follows: \n Enter favorite integer (Cntl+D to exit): \n Enter favorite integer (Cntl+D to exit): \n * The user can expect outputs on stdout as follows, where 'mode' is either 'sop' or 'pos' and 'value' is the calculated result based on the mode: \n* Except for the conditions specified above, the return code is 0.");
    printf("\n");
    exit(0); //exits as soon as it displays the information
}
//this method is used to parsing the values of command line arguments
char parseArgs(int num, char *name[]){
    char op = 'l'; //initialize the op character
    if(num <= 1){ //if the command line argument is less than 1 or no argument
        
        bail(1, "Enter a single argument of either 'sop', 'pos', or '-h'");
    }
    
    else{ //if it has command line arguments
        if(strcasecmp(name[1], "sop") == 0){ //for sum-of-products
            op = '0';
        }
        else if(strcasecmp(name[1], "pos") == 0){ //for product-of-sums
            op = '1';
        }
        else if(strcasecmp(name[1], "-h") == 0){ //for help
            help();
         
        }
        else{//if it has more than one command line argument
            bail(2, "Enter a single argument of either 'sop', 'pos', or '-h'");
            
        }
    }
    return op;
}
//this method collects the names and number the user enters
void collectInput(char **name, int *number){
    char in[1000]; //declare an array of char with size of 50
    printf("Enter first and last name (Cntl+D to exit): ");
    fgets(in, 1000, stdin);
    //scanf("%s", in); //limits the user to enter only 50 characters
    while(isspace(in[0])){
        printf("Enter first and last name (Cntl+D to exit): ");
        //scanf("%s", in);
          fgets(in, 1000, stdin);
    }
    *name = in; //allocates the memory of name to in
    printf("Enter favorite integer (Cntl+D to exit): ");
    //scanf("%d", number);
    while(scanf("%d",number)!=1){
        
        printf("Enter favorite integer (Cntl+D to exit): ");
        scanf("%d", number);
        while(getchar() != '\n');
        
    }; //scans the integer
    
    
    
}
//this method calculates the sum-of-products or product-of-sums from the given values

size_t calcValue(char op, char  **name, int num, long *result){
    size_t unrep = 0;//initializes the unrep to 0
    
    int j;
    int a;
    int length = strlen(*name); //gets the length of the string name
    
    int temp;
    int sum = 0;
    int product = 1;
    //char* name1 = (char*) malloc(sizeof(char) * (1 + length));
    char name1[1000];
    char alpha;
    long temp1;
    long product1 = 1;
    
    strncpy(name1, *name, length); //the array copies all the characters from the pointer name
   
    if(op == '0'){ //if it is sum-of-products
        
        
        
        for(j = 0; j < length; j++){
//            if(result > LONG_MAX || result < LONG_MIN){ //if it is unrepresentable or overflow or underflow occurs
//                unrep = 1; //assigns the unrep to 1
//            }
          
            while(isspace(name1[j])){
                j++;
            }
            
            temp = num * (int) name1[j];
            //printf("%d \n", temp);
            sum += temp;
            
        
         result[0] = (long)sum;
        }
         //stores all the sum of products of the integer and character
       
    }
    
    else if(op == '1'){ //if it is product-of-sums
        
        for(a = 0; a < length; a++){
//            if(result > LONG_MAX || result < LONG_MIN){ //if it is unrepresentable or overflow or underflow occurs
//                unrep = 1; //assigns the unrep to 1
//            }
            alpha = name1[a];
            if(isspace(alpha)){
                //temp = 1;
                continue;
            }
            

            //temp =  num + (int)alpha;
            temp1 = (long) num + (long) alpha;
            //printf("%d \n", temp);
            //printf("%d \n", temp1);
            
    
//            product *= temp ;
//            printf("= %d \n", product);
            product1 *= temp1;
            //printf("= %d \n", product1);
           // result[0] = product1;
            // result[0] = (long) product;
        }
        result[0] = product1;
         //stores all the product-of-sums of the integer and character
    }
    
    
   // printf("%ld %ld %ld\n",result[0], LONG_MAX, LONG_MIN);
   
    
    if(result > LONG_MAX || result < LONG_MIN){ //if it is unrepresentable or overflow or underflow occurs
        unrep = 1; //assigns the unrep to 1
    }
//    else{
//        unrep = 1;
//    }

    return unrep;
}
//This method is used to print out the result
void printResult(char op, long result, size_t unrep){
    if(op== '0'){ //if it is the sum-of-products
        printf("sop\n%ld \n", result);
    }
    else if(op == '1'){ //if it is the product-of-sums
        printf("pos\n%ld \n", result);
    }
    
    if(unrep==1){ //if it is unrepresentable
        bail(3, "overflow or underflow occured \n"); //bails out with the code 3
    }
    
}
//This method is used to bail out if error occurs
void bail(int accept, const char* error){
    printf("(%d) %s \n \n", accept,error); //prints out the error
    exit (accept);
}
