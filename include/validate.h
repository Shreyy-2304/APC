#ifndef VALIDATE_H
#define VALIDATE_H

#include "dll.h"

int validate_arguments(int argc, char *argv[]);
int validate_operand(char *operand);
int validate_operator(char *operator);
int validate_divisor(char *divisor);

#endif