#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BF.h"
#include "sorted.h"

#define FILENAME_YPALLHLOS "Employee_Records.txt"


int main(int argc, char** argv)
{
	int file, size,flag=0;
	char* filename;
	struct Employee employee;
	void* record;
	if(argc!=2)
	{
		fprintf(stderr,"Number of arguments must be 2\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[1], "Employee_records.txt") == 0)
	{
		filename = FILENAME_YPALLHLOS;
		size = sizeof(struct Employee);
		record = &employee;
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
		scanf("%d %14s %19s %c %d %d %d", &employee.id, employee.name, employee.surname, &employee.status, &employee.department, &employee.daysOff, &employee.prevYears);
		/* Insert record in file */
		if(employee.id==269)
			flag=1;
		if (Sorted_InsertEntry(file, record, size) < 0)
		{
			fprintf(stderr, "Error inserting entry in %s file.\n", filename);
			exit(EXIT_FAILURE);
		}
	}
	Sorted_SortFile(filename,1);
	if(Sorted_CheckSortedFile("Employee_Records.txtSorted1", 1)==0)
		printf("File is already sorted\n");
	int fd=Sorted_OpenFile("Employee_Records.txtSorted1");
	Sorted_GetAllEntries(fd,"surname",NULL);
	Sorted_GetAllEntries(fd,"surname","Tsipras");

	/* Close file */
	if (Sorted_CloseFile(file) < 0)
	{
		fprintf(stderr, "Error closing %s file.\n", filename);
		exit(EXIT_FAILURE);
	}
	 if (Sorted_CloseFile(fd) < 0)
        {
                fprintf(stderr, "Error closing %s file.\n", "Employee_Records.txtSorted1");
                exit(EXIT_FAILURE);
        }

	return EXIT_SUCCESS;
}
