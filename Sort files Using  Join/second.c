#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BF.h"
#include "sorted.h"

#define FILENAME_SALARY "Salary_Records.txt"


int main(int argc, char** argv)
{
	int file, size,flag=0;
	char* filename;
	struct Salary salary;
	void* record;
	if(argc!=2)
	{
		fprintf(stderr,"Number of arguments must be 2\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[1], "Salary_records.txt") == 0)
	{
		filename = FILENAME_SALARY;
		size = sizeof(struct Salary);
		record = &salary;
	}
	else
	{
		fprintf(stderr, "Wrong option given.\n");
		exit(EXIT_FAILURE);
	}


	BF_Init();

	/* Create file */
	if(Sorted_CreateFile(filename) < 0)
	{
		fprintf(stderr, "Error creating %s file.\n", filename);
		exit(EXIT_FAILURE);
	}
	/* Open file */
	if ((file = Sorted_OpenFile(filename)) < 0)
	{
		fprintf(stderr, "Error opening %s file.\n", filename);
		exit(EXIT_FAILURE);
	}

	/* Read line, until EOF */
	while (!feof(stdin))
	{
		if(flag==1) break;
		scanf("%d %d %c %d", &salary.id,&salary.salary,&salary.section,&salary.floor);
		if(salary.id==600) flag=1;
		/* Insert record in file */
		if (Sorted_InsertEntry(file, record, size) < 0)
		{
			fprintf(stderr, "Error inserting entry in %s file.\n", filename);
			exit(EXIT_FAILURE);
		}
	}

	Sorted_SortFile(filename,8);
	if(Sorted_CheckSortedFile("Salary_Records.txtSorted8",8)==0)
		printf("File already sorted\n");
	int fd=Sorted_OpenFile("Salary_Records.txtSorted8");
	Sorted_GetAllEntries(fd,"salary",NULL);
	//int fl=5;
	//Sorted_GetAllEntries(fd,"floor",&fl);

	/* Close file */
	if (Sorted_CloseFile(file) < 0)
	{
		fprintf(stderr, "Error closing %s file.\n", filename);
		exit(EXIT_FAILURE);
	}
	 if (Sorted_CloseFile(fd) < 0)
        {
                fprintf(stderr, "Error closing %s file.\n", "Salary_Records.txtSorted8");
                exit(EXIT_FAILURE);
        }

	return EXIT_SUCCESS;
}
