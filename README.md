# MatrixMultplicationUsing-multiThreads


##main ():
The main function of the code is this. It requires the filenames of the input files for matrices A, B, and 
C as its 4 command-line arguments. The read inputFile() function is used to read the matrices from the input 
files, and the three different matrix multiplication techniques are then used. The write output file () method is 
used to write the output matrices to different output files

##read_inputFile (char *filename, int flag):
The input file's filename and a flag are the two parameters that this function requires (1 for matrix A and 2 for matrix B). The matrix is stored in a 2D array after being received from the specified input file. Also, based on the matrix's dimensions, it decides the values of the global variables n, m, and k. The function prints an error notice and ends the program if the dimensions of the two matrices are incompatible for multiplication.
