File system Part 1 

This is my project for this week's class assignment. 

 

Building the project 

Command line: 

‘make’ we'll just build the project normally without any tests active. 

‘make clean’ will just clean up all the .o files 

‘make clean pristine’ will clean up all compiled files related to the code. 

‘make test’ will recompile the code to include all the tests and run it. 

 

Files 

testfs.c Has the main file in it and it is where all the tests are located. 

block.c Lets us read and write to memory using our blocks. 

block.h is header for block.c 

image.c lets us open and close a file. 

image.h is a header image.c 

 

Data 

Data is stored in blocks in this program in each block is 4096 in size 

 

Functions 

Main is it the main one 

image_open you open a file that you can now store data within 

image_close you close the file that you could put data in so it's no longer accessible 

bread you read from the file you opened from which block and how much data. 

wread You write to the file that you opened within that block. 

 