#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

// test name
char *testName;

/* test output files */
#define TESTPF "test_pagefile.bin"


/* main function running all tests */
int
main (void)
{
  testName = "";
  
  initStorageManager();
  createPageFile(TESTPF);
  SM_FileHandle fh;
  openPageFile (TESTPF, &fh);
  closePageFile (&fh);
  destroyPageFile (TESTPF);

return 0;
}