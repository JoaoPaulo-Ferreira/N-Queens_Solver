/*=============================================================================
 |   Assignment:  N-Queens_Solver
 |       Author:  João Paulo Soares (joaopaulof.soares@gmail.com)
 |       Grader:  Projec of AI to apply CNF 
 |
 |  Description:  A solver for the problem of arranging N queens on an NxN 
 |              chessboard without one attacking the other.
 |
 |     Language:  It's used C to build the input files of minisat and to plot 
 |              the chessboard it's used Shell.
 |
 | Ex. Packages:  Minisat
 |                
 | Deficiencies:  It may be some effitient way to write the headder of the CNF file.
 *===========================================================================*/

#include <stdio.h>
#include "fndAnsw.h"

#define SAT 10
#define UNSAT 11
#define TRUE 1
#define FALSE 0


int getAnswer(){
    char op;
    while(1){
        scanf("%c",&op);
        if(op == 'y')
            return TRUE;    
        else if(op == 'n')
            return FALSE;
    }
}

int main(){
    int n, solut_Index=1;
    char *op;
    char shell[100];
    printf("Number of Queens: \n");
    scanf("%d",&n);

    writeAndComputeSAT(n);
    while(TRUE){    
        if(is_SAT() == SAT){
            printf("Done\nSolution number %d:\n", solut_Index);
            writeMatrix(n,solut_Index);
            
            printf("Draw text-mode result? y|n \n");
            if(getAnswer()){ //CASE 'y'
                sprintf(shell,"cat solutions/FMatrix%d.txt",solut_Index);
                system(shell);
            } 
                
            
            printf("Draw ChessBoard? y|n \n");
            if(getAnswer())
                sprintf(shell,"./src/drawChessBoard.sh %d",solut_Index);
                system(shell);

            printf("Try another solution? y|n \n");
            if(getAnswer()){ //CASE 'y'
                solut_Index +=1;
                updateAndComputeSAT();
            }else{  //CASE 'n'
                system("rm solutions/*");
                system("rm temp/*");
                break;
            }
            
        }else{
            printf("Couldnt find.\nBye!\n\n");
            break;
        }
    }
    return 0;
}











