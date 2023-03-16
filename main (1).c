#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
int n = 0;                  // number of rows of A
int m = 0;                  // nimber of colomns of A and rows of B
int k = 0;                  // number of coloumns of B
typedef struct args_element // struct for passing arguments to threads
{
    int row;
    int col;
} idx;
int row1, col1, row2, col2;
int **A;
int **B;
int **C1;
int **C2;
int **C3;
// function perfroms matrix multiplication by matrix method
void matrixMultiplication()
{

    for (int i = 0; i < n; i++) // i is the row of C
    {
        for (int j = 0; j < k; j++) // j is the column of C
        {
            C1[i][j] = 0;
            for (int l = 0; l < m; l++) // l is the column of A and row of B
            {
                C1[i][j] += A[i][l] * B[l][j];
            }
        }
    }
}
// function perfroms matrix multiplication by row method
void *matrixMultiByRow(void *args_row)
{

    int row = ((int *)args_row); // row of C2 after casting
    for (int j = 0; j < k; j++)
    {
        C2[row][j] = 0;
        for (int l = 0; l < m; l++) // l is the column of A and row of B
        {
            C2[row][j] += A[row][l] * B[l][j];
        }
    }
}
// function perfroms matrix multiplication by element method
void *matrixMultipyByElement(void *args_element)
{
    int row = (*(struct args_element *)args_element).row; // row of C3 after casting
    int col = (*(struct args_element *)args_element).col; // column of C3 after casting
    C3[row][col] = 0;
    for (int l = 0; l < m; l++) // l is the column of A and row of B
    {
        C3[row][col] += A[row][l] * B[l][col];
    }
}
// function reads input file
void read_inputFile(char *filename, int flag)
{
    FILE *fp;               // file pointer
    char temp[100];         // temp string
    strcpy(temp, filename); // copy filename to temp
    strcat(temp, ".txt");   // add .txt to temp
    fp = fopen(temp, "r");  // open file in read mode
    if (fp == NULL)         // check if file is opened successfully
    {
        printf("Error: File not found");
        exit(1);
    }
    if (flag == 1) // if flag is 1 then read matrix A
    {
        fscanf(fp, "row=%d col=%d", &row1, &col1); // read number of rows and columns of A
        n = row1;
        m = col1;
        A = (int **)malloc(n * sizeof(int *)); // allocate memory rows for A
        for (int i = 0; i < n; i++)
        {
            A[i] = (int *)malloc(m * sizeof(int)); // allocate memory columns for A
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                fscanf(fp, "%d", &A[i][j]); // read elements of A
            }
        }
    }
    else if (flag == 2) // if flag is 2 then read matrix B
    {
        fscanf(fp, "row=%d col=%d", &row2, &col2); // read number of rows and columns of B
        if (col1 != row2)                          // check if matrix A and B can be multiplied
        {
            printf("Error: Matrix A and B cannot be multiplied");
            exit(1);
        }

        k = col2;
        B = (int **)malloc(m * sizeof(int *)); // allocate memory rows for B
        for (int i = 0; i < m; i++)
        {
            B[i] = (int *)malloc(k * sizeof(int)); // allocate memory columns for B
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < k; j++)
            {
                fscanf(fp, "%d", &B[i][j]); // read elements of B
            }
        }
    }
    fclose(fp);
}
void write_output_file(char *filename, int num)
{
    FILE *fp;
    char temp[100];
    strcpy(temp, filename);
    if (num == 1) /// if num is 1 then write the result matrix of matrix multiplication by matrix method
    {
        strcat(temp, "_per_matrix.txt");
    }
    else if (num == 2) // if num is 2 then write the result matrix of matrix multiplication by row method
    {
        strcat(temp, "_per_row.txt");
    }
    else if (num == 3) // if num is 3 then write the result matrix of matrix multiplication by element method
    {
        strcat(temp, "_per_element.txt");
    }
    fp = fopen(temp, "w"); // open file in write mode
    if (num == 1)
    {
        fprintf(fp, "row=%d col=%d\n", n, k); // write number of rows and columns of result of matrix multiplication by matrix method
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {

                fprintf(fp, "%d ", C1[i][j]); // write elements of result of matrix multiplication
            }
            fprintf(fp, "\n");
        }
    }
    else if (num == 2)
    {
        fprintf(fp, "row=%d col=%d\n", n, k); // write number of rows and columns of result of matrix multiplication by row method
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                fprintf(fp, "%d ", C2[i][j]); // write elements of result of matrix multiplication
            }
            fprintf(fp, "\n");
        }
    }
    else if (num == 3)
    {
        fprintf(fp, "row=%d col=%d\n", n, k); // write number of rows and columns of result of matrix multiplication by element method
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                fprintf(fp, "%d ", C3[i][j]); // write elements of result of matrix multiplication
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp); // close file
}
void free_memory() // function to free memory allocated to matrices A, B, C1, C2, C3
{
    for (int i = 0; i < n; i++) // free memory allocated for the columns of A, B, C1, C2, C3
    {
        free(A[i]);
        free(C1[i]);
        free(C2[i]);
        free(C3[i]);
    }
    for (int i = 0; i < m; i++) // free memory allocated for the columns of B
    {
        free(B[i]);
    }
    free(A);  // free memory allocated for the rows of A
    free(B);  // free memory allocated for the rows of B
    free(C1); // free memory allocated for the rows of C1
    free(C2); // free memory allocated for the rows of C2
    free(C3); // free memory allocated for the rows of C3
}
int main(int argc, char *argv[])
{
    if (argc == 4) // if number of arguments is 4 then read input files from command line
    {
        read_inputFile(argv[1], 1);
        read_inputFile(argv[2], 2);
    }
    else
    { // if number of arguments is not 4 then read input files from default files
        read_inputFile("a", 1);
        read_inputFile("b", 2);
    }
    C1 = (int **)malloc(n * sizeof(int *)); // allocate memory rows for C1
    C2 = (int **)malloc(n * sizeof(int *)); // allocate memory rows for C2
    C3 = (int **)malloc(n * sizeof(int *)); // allocate memory rows for C3
    for (int i = 0; i < n; i++)
    {
        C1[i] = (int *)malloc(k * sizeof(int)); // allocate memory columns for C1
        C2[i] = (int *)malloc(k * sizeof(int)); // allocate memory columns for C2
        C3[i] = (int *)malloc(k * sizeof(int)); // allocate memory columns for C3
    }
    struct timeval p1, p2;                                                                                              // declare start and end time
    gettimeofday(&p1, NULL);                                                                                            // get start time
    matrixMultiplication();                                                                                             // matrix multiplication
    gettimeofday(&p2, NULL);                                                                                            // get end time
    printf("the time taken by matrix multiplication by matrix method is %lu micro seconds\n", p2.tv_usec - p1.tv_usec); // print the time taken by matrix multiplication by matrix method
    struct timeval start, end;                                                                                          // declare start and end time
    gettimeofday(&start, NULL);                                                                                         // get start time
    pthread_t threads[n];                                                                                               // array of threads
    for (int i = 0; i < n; i++)
    {
        // create threads , threads call matrixMultiByRow function,pass i as argument then check if it is created successfully
        if (pthread_create(&threads[i], NULL, matrixMultiByRow, (void *)i))
        {
            printf("Error creating thread %d\n", i + 1);
        }
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL); // wait for threads to finish the multiplication of each row
    }
    gettimeofday(&end, NULL);                                                                                            // get end time
    printf("the time taken by matrix multiplication by row method is %lu micro seconds\n", end.tv_usec - start.tv_usec); // print the time taken by matrix multiplication by row method

    idx args[n][k];              // 2D array of structs
    struct timeval start2, end2; // declare start and end time
    gettimeofday(&start2, NULL); // get start time
    pthread_t threads2[n][k];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            args[i][j].row = i; // pass row of element to struct
            args[i][j].col = j; // pass column of element to struct
            // create threads , threads call matrixMultipyByElement function,pass args[i][j] as argument then check if it is created successfully
            if (pthread_create(&threads2[i][j], NULL, matrixMultipyByElement, (void *)&args[i][j]))
            {
                printf("Error creating thread %d\n", j + i + 1);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            pthread_join(threads2[i][j], NULL); // wait for threads to finish the multiplication of each element
        }
    }
    gettimeofday(&end2, NULL);                                                                                                 // get end time
    printf("the time taken by matrix multiplication by element method is %lu micro seconds\n", end2.tv_usec - start2.tv_usec); // print the time taken by matrix multiplication by element method
    if (argc == 4)
    {
        write_output_file(argv[3], 1); // write the result matrix of matrix multiplication by matrix method
        write_output_file(argv[3], 2); // write the result matrix of matrix multiplication by row method
        write_output_file(argv[3], 3); // write result of matrix multiplication by element method to output file
    }
    else
    {
        write_output_file("c", 1); // write the result matrix of matrix multiplication by matrix method
        write_output_file("c", 2); // write the result matrix of matrix multiplication by row method
        write_output_file("c", 3); // write result of matrix multiplication by element method to output file
    }
    free_memory(); // free memory allocated to matrices A, B, C1, C2, C3
    return 0;
}