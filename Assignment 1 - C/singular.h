#ifndef SINGULAR_H
#define SINGULAR_H

enum filter_type { EQ = 0, NEQ = 1, GEQ = 2, LEQ = 3, LESS = 4, GREATER = 5 };
void setPrec(int p);
void print(const double* row, size_t size);
void shift(double* row, size_t size, double by);
size_t filter(double* row, size_t count, enum filter_type t, double threshold);

#endif