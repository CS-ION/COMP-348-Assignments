#include <stdio.h>
#include <stdlib.h>
#include "singular.h"

/* Created a new static variable called precision and 
   a setter method called setPrec to set the precision 
   provided via mathpipe.c which will be used in printing. 
*/

static int precision;

void setPrec(int p){
    precision = p;
}

void print(const double* row, size_t size) {
    if (size!=0){
    for (size_t i = 0; i < size; i++) {
        printf("%.*f ",precision, row[i]);
    }
    printf("\n");}
}

void shift(double* row, size_t size, double s) {
    for (size_t i = 0; i < size; i++) {
        row[i] += s;
    }print(row,size);
}

size_t filter(double* row, size_t count, enum filter_type t, double threshold) {
    size_t newSize = 0;

    for (size_t i = 0; i < count; i++) {
        double value = row[i];
        int condition;

        switch (t) {
            case EQ:
                condition = (value == threshold);
                break;
            case NEQ:
                condition = (value != threshold);
                break;
            case GEQ:
                condition = (value >= threshold);
                break;
            case LEQ:
                condition = (value <= threshold);
                break;
            case LESS:
                condition = (value < threshold);
                break;
            case GREATER:
                condition = (value > threshold);
                break;
            default:
                fprintf(stderr, "FATAL ERROR: Invalid filter type\n");
                return count;
        }

        if (condition) {
            row[newSize] = value;
            newSize++;
        }
    }
    
    return newSize;
}