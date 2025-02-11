
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include "storage_mgr.h"

FILE *filePointer;

extern void initStorageManager (void)
{
 filePointer=NULL;
 printf("Initializing Storage Manage\n");
}

extern RC createPageFile (char *fileName)
{

 filePointer = fopen(fileName, "w"); 
 //printf("file is created\n");
   // checking if the file is created
    if (filePointer == NULL) {
        printf("The file is not opened. The program will "
               "exit now");
        return RC_FILE_NOT_FOUND;
    }
    else {
        printf("The file is created Successfully\n");
        // Allocate memory for the page 
        SM_PageHandle page_handler = (char *)malloc(PAGE_SIZE);
        if (page_handler == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return RC_FILE_HANDLE_NOT_INIT;
         
        }
        else{
            //memset to fill this single page with ’\0’ bytes
            memset(page_handler , '\0', PAGE_SIZE);
            // Writing  page with \0 to file.
            if(fwrite(page_handler, sizeof(char), PAGE_SIZE,filePointer) != PAGE_SIZE)
            printf("writing to file is not successful \n");
            else
            printf("write to the file is successful \n");
        
            // Closing file stream so free up memory allocated to filePointer.
            fclose(filePointer);
        
        
            // free up memory allocated
            free(page_handler);
}
        }
  

return RC_OK;

}
extern RC openPageFile (char *fileName, SM_FileHandle *fHandle){
        // Open the file in read mode
    
    filePointer=fopen(fileName, "r");
    if (filePointer == NULL) {
        return RC_FILE_NOT_FOUND; // File not found
    }
    else{
    // Updating file handle's filename and set the current position to the start of the page.
    fHandle->fileName = fileName;
    fHandle->curPagePos = 0;
    //fHandle->totalNumPages = 1;
    


    fHandle->totalNumPages = 1;

        // Closing file stream so that all the buffers are flushed. 
    fclose(filePointer);
    return RC_OK;
    fclose(filePointer);
    //printf("File opened successfully\n");
    return RC_OK; // File opened successfully
    }
}

extern RC closePageFile (SM_FileHandle *fHandle){
    //Check if file handle is still not closed then set it to NULL
    if(fHandle!=NULL)
    fHandle=NULL;
    printf("Closed open pages successfully\n");
    return RC_OK;//Return after successfully setting file Handler
    


}

extern RC destroyPageFile (char *fileName)
{
filePointer=fopen(fileName, "r");
    if (filePointer == NULL) {
        return RC_FILE_NOT_FOUND; // File not found
    }
    remove(fileName);
    printf("File destroyed successfully\n");
    return RC_OK;
}
extern RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    filePointer = fopen(fHandle->fileName, "r");
    if (fseek(filePointer, pageNum * PAGE_SIZE, SEEK_SET) != 0) {
        return RC_READ_NON_EXISTING_PAGE; // Seek failed, likely end of file
    }
    else{
        fread(memPage, 1, PAGE_SIZE, filePointer);
    }

    return RC_OK;

}

extern int getBlockPos (SM_FileHandle *fHandle){
    //to find page position from the file handler
    printf("current page position\n");
  return fHandle->curPagePos;
  

}


extern RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
return readBlock(0,fHandle,memPage);
}

extern RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
  int pagepos = getBlockPos(fHandle);
    int pageNum=pagepos/PAGE_SIZE;
    return readBlock(pageNum -1 ,fHandle,memPage);  
}

extern RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage)
{
    int pagepos = getBlockPos(fHandle);
    int pageNum=pagepos/PAGE_SIZE;
    return readBlock(pageNum,fHandle,memPage);
    
}
extern RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
    int pagepos = getBlockPos(fHandle);
    int pageNum=pagepos/PAGE_SIZE;
    return readBlock(pageNum + 1,fHandle,memPage); 
}

extern RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
printf("last page position\n");
  int totalpage = fHandle->totalNumPages;
  int lastpageNum = totalpage-1;
  return readBlock(lastpageNum,fHandle,memPage); 

}

extern RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage){
     filePointer = fopen(fHandle->fileName, "w");
    if (fseek(filePointer, pageNum * PAGE_SIZE, SEEK_SET) != 0) {
        return RC_READ_NON_EXISTING_PAGE; // Seek failed, likely end of file
    }
    else{
        
        size_t bytes_true = fwrite(memPage, 1, PAGE_SIZE, filePointer);
       

    if (bytes_true == 0) {
        fprintf(stderr, "Error writing to file.\n");
        fclose(filePointer);
        return RC_WRITE_FAILED;
    }

    fclose(filePointer);

    }
    

    return RC_OK;


}
extern RC writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
  int pagepos = getBlockPos(fHandle);
    int pageNum=pagepos/PAGE_SIZE;
    return writeBlock(pageNum,fHandle,memPage);  
}

extern RC appendEmptyBlock (SM_FileHandle *fHandle){
    //Increase the number of pages in the file by one. The new last page should be filled with zero bytes.
    //First add 1 page by increasing total number of pages
    fHandle->totalNumPages= fHandle->totalNumPages + 1;
    //Set the current page position to last page
    fHandle->curPagePos=fHandle->totalNumPages;
    filePointer = fopen(fHandle->fileName, "w"); 
 //printf("file is created\n");
   // checking if the file is created
    if (filePointer == NULL) {
        printf("The file is not opened. The program will "
               "exit now");
        return RC_FILE_NOT_FOUND;
    }
    else {
      
        // Allocate memory for the page 
        SM_PageHandle page_handler = (char *)malloc(PAGE_SIZE);
        if (page_handler == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return RC_FILE_HANDLE_NOT_INIT;
         
        }
        else{
            //memset to fill this single page with ’\0’ bytes
            memset(page_handler , '\0', PAGE_SIZE);
            // Writing  page with \0 to file.
            if(fwrite(page_handler, sizeof(char), PAGE_SIZE,filePointer) != PAGE_SIZE)
            printf("writing to file is not successful \n");
            else
            printf("write to the file is successful \n");


}
    }
    return RC_OK;

}

extern RC ensureCapacity (int numberOfPages, SM_FileHandle *fHandle){
//If the file has less than numberOfPages pages then increase the size to numberOfPages
 if (numberOfPages <fHandle->totalNumPages)
 {
    fHandle->totalNumPages=numberOfPages;
 }
 return RC_OK;
}







