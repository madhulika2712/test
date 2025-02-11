// This is read me file

/********************************************************/
                   Team Information:
/********************************************************/
Group No : 19
Members:
1) Deepali Budhiraja
2) Mandakini
3) Rishith Reddy

#Code Structure

storage_mgr.c 

initStorageManager()
This function is used to initialize storage initStorageManager

createPageFile()
It is responsible for creating a new page file 
It allocates PAGE_SIZE bytes of memory for a page usig malloc()
It fills the allocated memory using meset()

openPageFile()
It is responsible for opening an eisting page file in read mode
if the filePointer is not equal to NULL then it will give file not found


closePageFile()
We will check if file pointer is still not closed then it set to NULL
then it will close the file

destroyPageFile()
This function is responsible to delete a page file
If the file pointer is null then RC_FILE_NOT_FOUND error message passed

readBlock()
In this function it will use fopen to open file using read mode
There will be fseek to seek to the specified page if fseek()fails it returns RC_READ_NON_EXISTING_PAGE
If everything executes correctly it returns RC_OK

getBlockPos()
This function will give the currentPage position

readFirstBlock()
This function calls the function readBlock() function with firstBlock 

readPreviousBlock()
In this function we have to calculate the pageNume by using getBlockPos function
which will calculate pagePos 
Then it will call readBlock() function with previous block

readCurrentBlock()
here again first calculate the current page number by diving current page position

readNextBlock()
In this function we will calculate the current page number by dividing current page position with PAGE_SIZE
This will call to readBlock() function and calculate pageNum = currPagPos+1

readLastBlock()
It will calculate the lastPageNum = totalPage -1
It will call lastBlock to readBlock()

writeBlock()
This is responsible to open the existing file using fopen in write mode
Then if fseek filepointer is not equal to zero then it will return RC_READ_NON_EXISTING_PAGE
If is pass using fwrite() is successful and RC_OK is returned

writeCurrentBlock()
In this we calculate pagePos using getBlockPos function
Then we will calculate the pageNum by pagepos divided by page PAGE_SIZE
then we will call the writeBlock()

appendEmptyBlock()
This function appends an empty page (filled with \0 bytes) to an existing file.
It increases the total number of pages in the file by one.
if filePointer is equal to null then the file is not opened and the program will exit and return the error Code
RC_FILE_NOT_FOUND.
Next we will allocate memory for the page using malloc()
The new page is filled with \0 bytes and fwrite will Writes the empty page to the file.

ensureCapacity()
If the file has less number of pages we will then increase the size 
If it's executes then we will return the error messge RC_OK


---->>>References>>>---

https://www.geeksforgeeks.org/basics-file-handling-c/

https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

https://ioflood.com/blog/gcc-linux-command/#:~:text=The%20gcc%20command%20in%20Linux%20is%20used%20to%20compile%20C,This%20command%20compiles%20the%20'filename
