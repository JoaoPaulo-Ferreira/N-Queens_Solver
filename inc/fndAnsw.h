#ifndef __FIND_ANSWER_H_
#define __FIND_ANSWER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SAT 10
#define UNSAT 11

int tLines, tPropositions;
void topPrincipal(int *, int *);
void topSecondary(int *, int *, int);
void writeHeader();
void writeAndComputeSAT(int);
void updateAndComputeSAT();
int is_SAT();
void writeMatrix(int, int);

#endif // __FIND_ANSWER_H_