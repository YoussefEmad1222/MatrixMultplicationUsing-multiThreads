# MatrixMultplicationUsing-multiThreads
this program how to make user level threads and understands the pros and cons of using threads  


## 1.main ():
The main function of the code is this. It requires the filenames of the input files for matrices A, B, and 
C as its 4 command-line arguments. The read inputFile() function is used to read the matrices from the input 
files, and the three different matrix multiplication techniques are then used. The write output file () method is 
used to write the output matrices to different output files


## 2.read_inputFile (char *filename, int flag):
The input file's filename and a flag are the two parameters that this function requires (1 for matrix A and 2 for matrix B). The matrix is stored in a 2D array after being received from the specified input file. Also, based on the matrix's dimensions, it decides the values of the global variables n, m, and k. The function prints an error notice and ends the program if the dimensions of the two matrices are incompatible for multiplication.


##  3.write_output_file (char *filename, int num):
The filename of the output file and a number indicating the multiplication method used are the two parameters this function accepts (1 for matrix method, 2 for row method, and 3 for element method). It saves the generated matrix to the output file that has been provided


## 4.matrixMultiplication ():
Using the matrix approach, this function multiplies matrices. Each element is calculated by multiplying the corresponding row of matrix A with the corresponding column of matrix B as it goes through the rows and columns of the resulting matrix C. The resulting value is kept in the appropriate matrix C element.


## 5.void *matrixMultiByRow (void *args_row): 
The row approach is used by this function to multiply matrices. The function only requires one parameter, a pointer to a struct args_row that contains the row number of matrix C that needs to be calculated. By multiplying the appropriate row from matrix A with the corresponding column from matrix B, it determines each element of the specified row. The resulting value is kept in the C matrix's corresponding element



## 6.void *matrixMultipyByElement (void *args_element): 
Using the element approach, this function multiplies matrices. The function only requires a single parameter, a pointer to a struct args element that contains the row and column values of matrix C that must be calculated. By multiplying the appropriate row of the matrix, A with the corresponding column of matrix B, it determines the value of the specified element in matrix C. The resulting value is kept in the appropriate matrix C element


## 7.Free_memory():
This function named "free_memory" releases the memory allocated for matrices A, B, C1, C2, and C3, which are assumed to be square matrices of size n x k. It first frees the memory allocated for each column of the matrices and then frees the memory allocated for the rows. This is an important step to prevent memory leaks and to release the resources allocated during the program execution


# comparison between the 3 types of multiplication

## Matrix multiplication:
The traditional method of matrix multiplication involves sequential computation, where each component of the final matrix is calculated one at a time.__ 
•This method is simple to use and understand, however it is ineffective for huge matrices.__ 
•it use Only one thread make the matrix mutiplication.__
•it is Simple to implement and Easy to understand.__
•Not efficient for large matrices Computation time increases as the size of the matrix increases.__


## Matrix multiplication usign thread for each Row :
•his method divides the computation of the products of each row of the first matrix with each column of the second matrix among each thread.__ 
•This method allows for the row-wise multiplication to be computed in parallel.__
•which can increase the performance of matrix multiplication for bigger matrices.__ 
•it use N threads Allows for parallel computation of row-wise multiplication.__
•Can improve performance for larger matrice Limited to the number of rows in the matrix.__ 
•Uneven workload distribution among threads.__

## Matrix multiplication usign thread for each element :
•In this approach, each thread is responsible for computing the product of a single element of the resulting matrix.\ 
•This approach can be useful for very large matrices.\
•it allows for parallel computation of each individual multiplication.\
• N x K number of threads.\
• Allows for parallel computation of each individual multiplication.\
• Can be useful for very large matrices.\
• Requires more complex implementation.\
• Can result in many threads, which can lead to inefficiencies.\

## conclusion
The size of the matrices being multiplied, the technology that is available, and the needs of the application will all have an impact on the strategy that is chosen. The conventional method might be adequate for smaller matrices, but for larger matrices, row-wise or element-wise parallelization might be required for improved performance
