#include "fndAnsw.h"

 /*---------------------------------------------------------------------
        |  Method: topPrincipal
        |
        |  Purpose: To find the index of the top-left element in the diagonal of a given element.
        |
        |  Parameters:
	    |	a       -- row of the element
	    |	b       -- column of the element
        |
        |  Returns: None
*-------------------------------------------------------------------*/

void topPrincipal(int * a, int * b){
    int aux = *a;
    *a = *a - *b;
    *b = *b - aux;
    if(*a < 0)
        *a = 0;
    if(*b < 0)
        *b = 0;
}

/*---------------------------------------------------------------------
        |  Method: topSecondary
        |
        |  Purpose: To find the index of the top-right element in the diagonal of a given element.
        |
        |  Parameters:
	    |	a       -- row of the element
	    |	b       -- column of the element
        |
        |  Returns: None
*-------------------------------------------------------------------*/
void topSecondary(int *a, int *b, int n){
    while(*a != 0 && *b != (n - 1)){
        *a = (*a - 1);
        *b = (*b + 1);
    }
}


/*---------------------------------------------------------------------
        |  Method: writeHeader
        |
        |  Purpose: Create a new file with the header needded for minisat. 
        |       The header is based on the number of variables and number of lines 
        |        in sat.txt
        |
        |  Returns: None
*-------------------------------------------------------------------*/
void writeHeader(){
    FILE *final, *sat;
    char  aux;
    int controle;
    final = fopen("temp/final.txt","w+");
    sat = fopen("temp/sat.txt", "r");
    fprintf(final, "p cnf %d %d\n",tPropositions,tLines);
    while (1) {
       controle = fscanf(sat,"%c", &aux);
       if (controle != 1)
           break;
       fprintf(final, "%c", aux);
    }
    fclose(sat);
    fclose(final);
}

/*---------------------------------------------------------------------
        |  Method: writeAndComputeSAT
        |
        |  Purpose: Create a sat.txt file with all CNF sentences.
        |           Upadte de Header needed for minisat.
        |           Compute a solution.
        |
        |  Parameters:
	    |	n       -- number of Queens
        |
        |  Returns: None
*-------------------------------------------------------------------*/
void writeAndComputeSAT(int n){
    FILE *sat;
    sat = fopen("temp/sat.txt","w+");
    int i,j,k;
    int cont = 1;
    tPropositions = n*n;
    //MATRIZ DE PROPOSIÇOES
    int matriz[n][n];
    for (i = 0; i < n; i ++){
        for(j = 0; j < n; j++){
            matriz[i][j] = cont++;
        }
    }

    for (i = 0; i < n; i ++){
        for(j = 0; j < n; j++){
            fprintf(sat, "%d ",matriz[i][j]);
        }
        fprintf(sat, "0\n");
        tLines++;
        for(j = 0; j < n; j++){
            fprintf(sat, "%d ",matriz[j][i]);
        }
        fprintf(sat, "0\n");
        tLines++;
    }
    
    for (i = 0; i < n; i ++){
        for(j = 0; j < n; j++){
            for (k = 0; k < n; k++) {
                if (k != i){
                    tLines++;
                    fprintf(sat, "-%d -%d 0\n",matriz[i][j], matriz[k][j] );
                }
            }

            for (k = 0; k < n; k++) {
                if (k != j){
                    tLines++;
                    fprintf(sat, "-%d -%d 0\n",matriz[i][j], matriz[i][k] );
                }
            }
        }
    }

    //RESOLUÇÃO PARA AS DIAGONAIS
    for (i = 0; i < n; i ++){
        for(j = 0; j < n; j++){
            int a = i,b = j;
            //IF ESTÁ NO TOPO DA DIAGONAL PRINCIPAL
            if(j == 0 || i == 0){
                while (a < n && b < n) {
                    if(a != i || b != j){
                        fprintf(sat,"-%d -%d 0\n",matriz[i][j], matriz[a][b]);
                        tLines++;
                    }
                    a++;b++;
                }
            }else{
                topPrincipal(&a, &b);
                while (a < n && b < n) {
                    if(a != i || b != j){
                        fprintf(sat,"-%d -%d 0\n",matriz[i][j], matriz[a][b]);
                        tLines++;
                }
                    a++;b++;
                }
            }
            //DIAGONAL SECUNDARIA
            a = i;b = j;
            if(i == 0 || j == n-1){
                while (b >= 0 && a < n) {
                    if(a != i || b != j){
                        fprintf(sat,"-%d -%d 0\n",matriz[i][j], matriz[a][b]);
                        tLines++;
                        }
                    a++;b--;
                }
            }else{
                 topSecondary(&a, &b, n);
                 while (a <= (n-1) && b >= 0) {
                     if(a != i || b != j){
                        fprintf(sat,"-%d -%d 0\n",matriz[i][j], matriz[a][b]);
                        tLines++;
                        }
                        a++;b--;
                 }
             }
        }
    }
    fclose(sat);
    writeHeader();
    system("minisat  -cpu-lim=10 -verb=0 ./temp/final.txt ./temp/result.txt > /dev/null");
}


/*---------------------------------------------------------------------
        |  Method: updateAndComputeSAT
        |
        |  Purpose: Add a new sentence in sat.txt to force minisat to find
        |      another solution.
        |           Upadte de Header.
        |           Compute a new solution.
        |
        |  Returns: None
*-------------------------------------------------------------------*/
void updateAndComputeSAT(){
    FILE *result, *final;
    result = fopen("temp/result.txt", "r");
    final = fopen("temp/sat.txt", "a");
    char  aux[10];
    int controle;

    controle = fscanf(result,"%s", aux);
    while (1) {
       controle = fscanf(result,"%s", aux);
       if (controle != 1)
           break;
         if ( aux[0] == '0' ){
            fprintf(final, "%s", "0\n");
            tLines+=1;
            break;
        }

        if(aux[0] == '-'){
            fprintf(final, "%s ", aux+1);
        }else
            fprintf(final, "-%s ", aux);
        
    }
    fclose(result);
    fclose(final);
    writeHeader();
    system("minisat  -cpu-lim=10 -verb=0 ./temp/final.txt ./temp/result.txt > /dev/null");
}

/*---------------------------------------------------------------------
        |  Method: is_SAT
        |
        |  Purpose: Check in the output of minisat (result.txt) if a solution was found.
        |
        |  Returns: An Int to represent if a solution was found.
*-------------------------------------------------------------------*/
int is_SAT(){
    int controle, output;
    char aux;
    FILE * stemp;
    stemp = fopen("temp/result.txt", "r");
    controle = fscanf(stemp,"%c", &aux);
    if(aux == 'S')
        output = SAT;
    else
        output = UNSAT;
    fclose(stemp);
    return output;
}


/*---------------------------------------------------------------------
        |  Method: writeMatrix
        |
        |  Purpose: Create a file based on the solution given by
        |   minisat. The solution is written in a chessboard-like format.
        |
        |  Parameters:
	    |	n       -- number of Queens and dimentions of the matrix
        |   index   -- number of solution found for this n
        |
        |  Returns: None.
*-------------------------------------------------------------------*/
void writeMatrix(int N, int index){
    FILE *f1, *matrix;
    char  aux[10];
    char title[100];
    int controle, cont=1;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    sprintf(title, "solutions/FMatrix%d.txt", index);
    f1 = fopen("temp/result.txt", "r");
    matrix = fopen(title,"w+");
    read = getline(&line, &len, f1);
    while (1) {
       controle = fscanf(f1,"%s", aux);
       if (controle != 1 || *aux == '0')
           break;
        if(aux[0] == '-'){
            fprintf(matrix, "%s", " 1 ");
        }else
            fprintf(matrix, "%s", " 0 ");

        if(cont == N){
            fprintf(matrix, "%c", '\n');
            cont = 0;
        }
        cont++;
    }
    fclose(f1);
    fclose(matrix);
}
