#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aggregate.h"

/* The individual aggregates functions are made static so that 
they remain hidden and not externally visible as per the requirements.
The link to individual aggregate functions is done via an internal array
(both pointer and string array implemented as reuqired)*/

static double _count(double* row, int size);
static double _min(double* row, int size);
static double _max(double* row, int size);
static double _sum(double* row, int size);
static double _avg(double* row, int size);
static double _pavg(double* row, int size);

typedef double (*aggregate_func)(double*, int);

static const char* funcNames[] = {
    "COUNT", "MIN", "MAX", "SUM", "AVG", "PAVG"
};

static aggregate_func funcPtrs[] = {
    &_count, &_min, &_max, &_sum, &_avg, &_pavg
};

double aggregate(const char* func, double* row, int size) {
    int numFuncs = sizeof(funcNames) / sizeof(funcNames[0]);
    int index = -1;

    for (int i = 0; i < numFuncs; i++) {
        if (strcasecmp(func, funcNames[i]) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        fprintf(stderr, "FATAL ERROR: Invalid function name\n");
        exit(1);
    }

    aggregate_func operation = funcPtrs[index];
    return operation(row, size);
}

static double _count(double* row, int size) {
    return (double)size;
}

static double _min(double* row, int size) {
    double min = row[0];
    for (int i = 1; i < size; i++) {
        if (row[i] < min) {
            min = row[i];
        }
    }
    return min;
}

static double _max(double* row, int size) {
    double max = row[0];
    for (int i = 1; i < size; i++) {
        if (row[i] > max) {
            max = row[i];
        }
    }
    return max;
}

static double _sum(double* row, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += row[i];
    }
    return sum;
}

static double _avg(double* row, int size) {
    double sum = _sum(row, size);
    return sum / size;
}

static double _pavg(double* row, int size) {
    double min = _min(row, size);
    double max = _max(row, size);
    return (min + max) / 2.0;
}
