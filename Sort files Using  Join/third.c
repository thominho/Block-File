#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BF.h"
#include "sorted.h"

#define FILENAME_YPALLHLOS "Employee_Records.txt"
#define FILENAME_MISTHOS   "Salary_Records.txt"


int main(int argc, char** argv)
{
	int fd1,fd2,fd3;
	BF_Init();
	fd1=Sorted_OpenFile("Employee_Records.txtSorted1");
	fd2=Sorted_OpenFile("Salary_Records.txtSorted8");

	if(Sorted_MergeFiles("Employee_Records.txtSorted1", "Salary_Records.txtSorted8", "=", 1, 8)<0)
	{
		fprintf(stderr,"Error at merging files\n");
	}
	fd3=Sorted_OpenFile("Employee_Records.txtSorted1Salary_Records.txtSorted81=8");
//	fd3=Sorted_OpenFile("Employee_Records.txtSorted1Salary_Records.txtSorted81>8");
	int temp=1780;
	Sorted_GetAllEntries(fd3,"id",NULL);
	Sorted_GetAllEntries(fd3,"surname","Larios");
	/* Close file */
	if (Sorted_CloseFile(fd1) < 0)
	{
		fprintf(stderr, "Error closing %s file.\n", "Employee_Records.txtSorted1");
		exit(EXIT_FAILURE);
	}
	 if (Sorted_CloseFile(fd2) < 0)
        {
                fprintf(stderr, "Error closing %s file.\n", "Salary_Records.txtSorted8");
                exit(EXIT_FAILURE);
        }
	if (Sorted_CloseFile(fd3) < 0)
        {
                fprintf(stderr, "Error closing %s file.\n", "Employee_Records.txtSorted1Salary_Records.txtSorted81=8");
                exit(EXIT_FAILURE);
        }

	return EXIT_SUCCESS;
}
