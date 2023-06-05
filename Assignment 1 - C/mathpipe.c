#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aggregate.h"
#include "singular.h"

#define MAX_COLUMNS 256

/* COMP 348 AB - Assignment 1
   Done By: Syed Ayaan Jilani

   Citations :-
   1) Slides and Lecture notes 
   2) Stack Overflow (debugging)
   3) w3schools (syntax)
   4) IBM Documentation (documentation)
   5) Chat GPT (generating repetitive and easy functions like max, min, etc.)
*/

/* This method takes in the array to be processed along with the 
   function (and its parameters) to be performed on the array. It
   also take the size (default or determined by user) and the precision
   (default or determined by the user)
*/
void processRow(const char* func, double* row, int size, int precision, int *isShift) {
    double result;

    if (strcasecmp(func, "COUNT") == 0) {
        printf("%d ", size);
    } else if (strcasecmp(func, "MIN") == 0) {
        result = aggregate("MIN", row, size);
        printf("%.*f ", precision, result);
    } else if (strcasecmp(func, "MAX") == 0) {
        result = aggregate("MAX", row, size);
        printf("%.*f ", precision, result);
    } else if (strcasecmp(func, "SUM") == 0) {
        result = aggregate("SUM", row, size);
        printf("%.*f ", precision, result);
    } else if (strcasecmp(func, "AVG") == 0) {
        result = aggregate("AVG", row, size);
        printf("%.*f ", precision, result);
    } else if (strcasecmp(func, "PAVG") == 0) {
        result = aggregate("PAVG", row, size);
        printf("%.*f ", precision, result);
    } else if (strcasecmp(func, "PRINT") == 0) {
        print(row, size);
    } else if (strncasecmp(func, "FILTER", 6) == 0) {
        char type[10];
        double threshold;
        sscanf(func + 6, " %s %lf", type, &threshold);       // reads and separates the different parameters of FILTER
        enum filter_type f_type;

        if (strcasecmp(type, "EQ") == 0) {
            f_type = EQ;
        } else if (strcasecmp(type, "NEQ") == 0) {
            f_type = NEQ;
        } else if (strcasecmp(type, "GEQ") == 0) {
            f_type = GEQ;
        } else if (strcasecmp(type, "LEQ") == 0) {
            f_type = LEQ;
        } else if (strcasecmp(type, "LESS") == 0) {
            f_type = LESS;
        } else if (strcasecmp(type, "GREATER") == 0) {
            f_type = GREATER;
        } else {
            fprintf(stderr, "ERROR: Invalid filter type\n");
            exit(1);
        }
       
        size_t new_size = filter(row, size, f_type, threshold);
        print(row, new_size);
    } else if (strncasecmp(func, "SHIFT", 5) == 0) {
        double shift_value;
        sscanf(func + 5, " %lf", &shift_value);           // reads and separates the different parameters of SHIFT
        shift(row, size, shift_value);
        *isShift = 1;
    } else {
        fprintf(stderr, "ERROR: Invalid function name\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    int size = 0;
    int precision = 6;     // default precision
    char func[20];
    double* row = NULL;
    int row_size = 0;
    int row_capacity = 0;
    int isAggregate = 1;    // used for outputting as required
    int isShift = 0;        // used for extreme shift cases
    
    for (int i = 1; i < argc; i++) {
        if (strncasecmp(argv[i], "-size=", 6) == 0) {                // checks if user provided size
            sscanf(argv[i] + 6, "%d", &size);
        } else if (strncasecmp(argv[i], "-prec=", 6) == 0) {         // checks if user provided precision
            sscanf(argv[i] + 6, "%d", &precision);                   // also uses setPrec to set the precision
            setPrec(precision);                                      // required for printing the arrays
        } else if (strncasecmp(argv[i], "SHIFT", 5) == 0) {     
            strcpy(func, argv[i]);                                   // special cases for SHIFT & FILTER
            strcpy(func + 5, argv[i+1]);                             // as they contain other parameters
            i=i+1;                                                   // along with the fucntion name
            isAggregate = 0;
        } else if (strncasecmp(argv[i], "FILTER", 6) == 0) {
            strcpy(func, argv[i]);
            strcpy(func + 6, argv[i+1]);
            strcpy(func + 6 + strlen(argv[i+1]), " ");
            strcpy(func + 7 + strlen(argv[i+1]), argv[i+2]);
            i=i+2;
            isAggregate = 0;
        } else if (strncasecmp(argv[i], "PRINT", 5) == 0) {
            strcpy(func, argv[i]);
            isAggregate = 0;
        } else {
            strcpy(func, argv[i]);
        }
    }

    if (size==0){size=MAX_COLUMNS;}       // default size
   
    while (1) {
        if (row_size == row_capacity) {                                            // Memory Allocation of the row/array
            row_capacity = (row_capacity == 0) ? 1 : 2 * row_capacity;             // Using realloc as we will routinely
            row = realloc(row, row_capacity * sizeof(double));                     // keep resizing the array/row
            if (row == NULL) {
                fprintf(stderr, "ERROR: Memory allocation failed\n");
                exit(1);
            }
        }

        double num;                                                   // Attempting to read the input matrix and ending at 
        int count = scanf("%lf", &num);                               // either a new line or the size defined by user. 
        
        if (count == EOF) {                                           // Finally terminating when EOF encountered
            if (row_size != 0) {
                processRow(func, row, row_size, precision, &isShift);
                row_size = 0;
            }if (isAggregate){printf("\n");}
            break;
        } 

        row[row_size++] = num;
        
        int c = getchar();                                            
        if (c == '\n') {
            processRow(func, row, row_size, precision, &isShift);
            row_size = 0;
        }else{                                                                // The nested if-else is because the raw string output
            c = getc(stdin);                                                  // of "cat sample.txt | mathpipe -size=1 FILTER GEQ 10"
            if (c=='\n'){                                                     // is "12 \n13 \n". There are some whitespaces generated
                processRow(func, row, row_size, precision, &isShift);         // due to the required formatting that is accounted for
                row_size = 0;                                                 // by this nested if-else block
            }else{ungetc(c,stdin);}
        }
        if (row_size == size) {
            processRow(func, row, row_size, precision, &isShift);
            row_size = 0;
        }

        if (isShift && size!=MAX_COLUMNS){
            break;                                                            // terminating for extreme case of shift
        }
    }

    free(row);          // Deallocation of memory
    return 0;
}
