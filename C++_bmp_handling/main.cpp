

#include<fstream>
#include<iostream>
#include<stdio.h>

int main()
{
  FILE* pFile;
  pFile = fopen("white_test_image.bmp","r");
  if (pFile!=NULL)
  {
    //printf("", *pFile)

    fclose (pFile);
  }
  return 0;
}



