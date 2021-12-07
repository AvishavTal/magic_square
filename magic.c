
#include <stdio.h>
#include <stdlib.h>

#define N 3 /*dimension of the matrix*/

#define NOT_INT_CODE -1



/*return 0 iff not all the numbers in the matrix are in the range 1-N^2*/
int all_numbers_in_range(int matrix[N][N]) {
    int result=1,i,j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; j++) {
            if(matrix[i][j]<1||matrix[i][j]>N*N){
                result=0;
            }
        }
    }
    return result;
}


/*calculates the sum of the numbers in the given row in the given matrix*/
int row_sum(int matrix[N][N],int row_idx){
    int i=0, result=0;
    while (i < N){
        result += matrix[row_idx][i];
        ++i;
    }
    return result;
}

/*calculates the sum of the numbers in the given column in the given matrix*/
int column_sum(int matrix[N][N],int column_idx){
    int i=0, result=0;
    while (i <N) {
        result += matrix[i][column_idx];
        ++i;
    }
    return result;
}

/*calculates the sum of the primary diagonal in the matrix*/
int primary_diagonal_sum(int matrix[N][N]){
    int i=0,result=0;
    while (i<N){
        result += matrix[i][i];
        ++i;
    }
    return result;
}

/*calculates the sum of the secondary diagonal in the matrix*/
int secondary_diagonal_sum(int matrix[N][N]){
    int  row_idx = 0, column_idx = N-1, result = 0;
    while (row_idx<N){
        result += matrix[row_idx][column_idx];
        --column_idx;
        ++row_idx;
    }
    return result;
}


/*copy the values of the matrix to one dimension array*/
void copy_to_1d_array(int matrix[N][N], int array[]) {
    int i,j,k=0;
    for ( i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            array[k]=matrix[i][j];
            k++;
        }
    }

}

/*get a NxN matrix and return 0 iff not all the values are unique*/
int all_values_unique(int matrix[N][N]) {
    int array_size=N*N,i,j,result=1;
    int matrix_as_array[N*N];
    copy_to_1d_array(matrix, matrix_as_array);
    for (i = 0; i < array_size; ++i) {
        for (j = i+1; j < array_size ; ++j) {
            if (matrix_as_array[i]==matrix_as_array[j]){
                result=0;
            }
        }
    }
    return result;
}

/*get a NxN matrix and check if it is a magic square. return 0 iff it is not*/
int is_magic_square(int matrix[N][N]){
    int result=1,sum=0,i=0;
    if (!all_numbers_in_range(matrix) || !all_values_unique(matrix)){
        result=0;
    }
    sum = primary_diagonal_sum(matrix);
    if (sum!= secondary_diagonal_sum(matrix)){
        result=0;
    }
    while (result && i<N){
        if (sum != row_sum(matrix,i) || sum != column_sum(matrix,i)){
            result=0;
        }
        i++;
    }
    return result;
}

/*get n^2 values of NxN matrix and put them in matrix in the correct order.
 * return the number of values if all the values are integers, NOT_INT_CODE otherwise*/
int get_input(int matrix[N][N]) {
    int size=0,row_idx=0,column_idx=0,num;
    int c;/*the output of scanf*/
    printf("\nplease enter matrix:\n");
    while ((c=scanf(" %d",&num))==1){
        if (size<=N*N){/*there is space in the matrix for another number*/
            matrix[row_idx][column_idx++]=num;
            if (column_idx==N){
                row_idx++;
                column_idx=0;
            }

        }
        size++;
    }
    if (c!=EOF){
        size=NOT_INT_CODE;
    }
    return size;
}

/*print NxN matrix*/
void print_matrix(int matrix[N][N]) {
    int i,j;
    printf("the matrix received is:\n");
    for (i = 0; i < N; ++i) {
        printf("\n");
        for (j = 0; j < N; ++j) {
            printf("%d\t",matrix[i][j]);
        }
    }
    printf("\n");

}

/*check validity of the input. exit the program if the input is not valid*/
void check_input(int matrix_size) {
    if (matrix_size != N*N){
        if (matrix_size>=0){    /*not a special code*/
            if (matrix_size>N*N){
                printf("\n too many values\n");
            }
            if (matrix_size<N*N){
                printf("\n not enough values\n");
            }
        }

        if (matrix_size == NOT_INT_CODE){
            printf("\n at least one of the values is not an integer\n");
        }
        exit(0);
    }
}

/*print if the matrix is a magic square*/
void print_result(int is_magic) {
    printf("\n this matrix is ");
    if (!is_magic){
        printf("not ");
    }
    printf("a magic square");

}

int main() {
    int matrix[N][N],is_magic;
    int matrix_size=get_input(matrix);
    check_input(matrix_size);
    print_matrix(matrix);
    is_magic= is_magic_square(matrix);
    print_result(is_magic);
    return 0;
}


