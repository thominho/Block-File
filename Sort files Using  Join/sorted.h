#include "BF.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
	int id;
	char name[15];
	char surname[20];
	char status;
	int department;
        int daysOff;
        int prevYears;
};

struct Salary
{
	int id;
	int salary;
	char section;
	int floor;
};

struct integer
{
	int field;
	int pos;
};

struct string
{
	char field[30];
	int pos;
};


void bin_search_emp(struct Employee* emp, int length, int tar)
{
	int a, b, c, pos;
	a=0;
	b=length-1;
	c=(b+a)/2;
	while (a<=b)
	{
		if (tar>emp[c].id)
		{
			a=c+1;
		}
		else if (tar<emp[c].id)
		{
			b=c-1;
		}
		else
		{
			break;
		}
		c=(b+a)/2;
	}
	if (a>b)
		printf("No such employee\n");
	else
		printf("%d %s %s %c %d %d %d\n",emp[c].id,emp[c].name,emp[c].surname,emp[c].status,emp[c].department,emp[c].daysOff,emp[c].prevYears);
}

void bin_search_sal(struct Salary* sal, int length, int tar)
{
	int a, b, c, pos;
	a=0;
	b=length-1;
	c=(b+a)/2;
	while (a<=b)
	{
		if (tar>sal[c].id)
		{
			a=c+1;
		}
		else if (tar<sal[c].id)
		{
			b=c-1;
		}
		else
		{
			break;
		}
		c=(b+a)/2;
	}
	if (a>b)
		printf("No such salary\n");
	else
		printf("%d %d %c %d\n",sal[c].id,sal[c].salary,sal[c].section,sal[c].floor);
}


void bin_search_mer(struct Employee* emp, struct Salary* sal, int length, int tar)
{
	int a, b, c, pos;
	a=0;
	b=length-1;
	c=(b+a)/2;
	while (a<=b)
	{
		if (tar>emp[c].id)
		{
			a=c+1;
		}
		else if (tar<emp[c].id)
		{
			b=c-1;
		}
		else
		{
			break;
		}
		c=(b+a)/2;
	}
	if (a>b)
		printf("No such employee\n");
	else
		printf("%d %s %s %c %d %d %d %d %d %c %d\n",emp[c].id,emp[c].name,emp[c].surname,emp[c].status,emp[c].department,emp[c].daysOff,emp[c].prevYears,sal[c].id,sal[c].salary,sal[c].section,sal[c].floor);
}

//quick Sort function to Sort Integer array list
void quicksort_int(struct integer array[], int firstIndex, int lastIndex)
{
    //declaaring index variables
    int pivotIndex, index1, index2;
    struct integer temp;
    if(firstIndex < lastIndex)
    {
        //assigninh first element index as pivot element
        pivotIndex = firstIndex;
        index1 = firstIndex;
        index2 = lastIndex;

        //Sorting in Ascending order with quick sort
        while(index1 < index2)
        {
            while(array[index1].field <= array[pivotIndex].field && index1 < lastIndex)
            {
                index1++;
            }
            while(array[index2].field>array[pivotIndex].field)
            {
                index2--;
            }

            if(index1<index2)
            {
                //Swapping opertation
                temp.field=array[index1].field;
                temp.pos=array[index1].pos;
                array[index1].field = array[index2].field;
                array[index1].pos = array[index2].pos;
                array[index2].field = temp.field;
		array[index2].pos=temp.pos;

            }
        }

        //At the end of first iteration, swap pivot element with index2 element
	 temp.field=array[pivotIndex].field;
         temp.pos=array[pivotIndex].pos;
         array[pivotIndex].field = array[index2].field;
         array[pivotIndex].pos = array[index2].pos;
         array[index2].field = temp.field;
         array[index2].pos=temp.pos;
        //Recursive call for quick sort, with partiontioning
        quicksort_int(array, firstIndex, index2-1);
        quicksort_int(array, index2+1, lastIndex);
    }

}







void quicksort_str(struct string array[], int firstIndex, int lastIndex)
{
    //declaaring index variables
    int pivotIndex, index1, index2;
    struct string temp;
    if(firstIndex < lastIndex)
    {
        //assigninh first element index as pivot element
        pivotIndex = firstIndex;
        index1 = firstIndex;
        index2 = lastIndex;

        //Sorting in Ascending order with quick sort
        while(index1 < index2)
        {
            while(strcmp(array[index1].field,array[pivotIndex].field)<=0 && index1 < lastIndex)
            {
                index1++;
            }
            while(strcmp(array[index2].field,array[pivotIndex].field)>0)
            {
                index2--;
            }

            if(index1<index2)
            {
                //Swapping opertation
                strcpy(temp.field,array[index1].field);
                temp.pos=array[index1].pos;
                strcpy(array[index1].field,array[index2].field);
                array[index1].pos = array[index2].pos;
                strcpy(array[index2].field,temp.field);
                array[index2].pos=temp.pos;

            }
        }
	//At the end of first iteration, swap pivot element with index2 element
         strcpy(temp.field,array[pivotIndex].field);
         temp.pos=array[pivotIndex].pos;
         strcpy(array[pivotIndex].field,array[index2].field);
         array[pivotIndex].pos = array[index2].pos;
         strcpy(array[index2].field ,temp.field);
         array[index2].pos=temp.pos;
        //Recursive call for quick sort, with partiontioning
        quicksort_str(array, firstIndex, index2-1);
        quicksort_str(array, index2+1, lastIndex);
    }

}



int Sorted_InsertEntry(int fileDesc, void* ptr, int length)
{
        int cnt, num_rec=1, info;
        void* block;
        cnt=BF_GetBlockCounter(fileDesc);
        if (cnt==0)
        {
                if (length==sizeof(struct Employee))
                        info=1;
		else if (length==sizeof(struct Salary))
			info=2;
		else
			printf("no such size\n");
		BF_AllocateBlock(fileDesc);
	        BF_ReadBlock(fileDesc, 0, &block);
		memcpy(block,&info,sizeof(int));
                BF_WriteBlock(fileDesc, 0);
                if (BF_AllocateBlock(fileDesc)<0)
                        return -1;
                if (BF_ReadBlock(fileDesc, 1, &block)<0)
                        return -1;
                memcpy(block, &num_rec, sizeof(int));
                memcpy(block+sizeof(int), ptr, length);
                if (BF_WriteBlock(fileDesc, 1)<0)
                        return -1;
        }
        else
        {
        		BF_ReadBlock(fileDesc, 0, &block);
	        	memcpy(&info, block, sizeof(int));
	        	if (info==1 && length==sizeof(struct Salary))
	        	{
	        		info=3;
	        		memcpy(block, &info, sizeof(int));
				BF_WriteBlock(fileDesc, 0);
	        	}
	        	else if (info==2 && length==sizeof(struct Employee))
	        	{
	        		info=3;
	        		memcpy(block, &info, sizeof(int));
				BF_WriteBlock(fileDesc, 0);
	        	}
                   if (BF_ReadBlock(fileDesc, cnt-1, &block)<0)
                        return -1;
		memcpy(&num_rec,block,sizeof(int));
		if (info==3)
		{
			if (length==sizeof(struct Employee))
			{
				if (((sizeof(struct Employee)+sizeof(struct Salary))*(num_rec+1)+sizeof(int))<=1024)
				{
					memcpy(block+sizeof(int)+num_rec*(sizeof(struct Employee)+sizeof(struct Salary)), ptr,  sizeof(struct Employee));
					++num_rec;
					memcpy(block, &num_rec, sizeof(int));
					BF_WriteBlock(fileDesc, cnt-1);
				}
				else
				{
					BF_AllocateBlock(fileDesc);
					BF_ReadBlock(fileDesc,cnt,&block);
					num_rec=1;
					memcpy(block,&num_rec,sizeof(int));
					memcpy(block+sizeof(int), ptr, sizeof(struct Employee));
					BF_WriteBlock(fileDesc, cnt);
				}
			}
			else if (length==sizeof(struct Salary))
			{
				memcpy(block+sizeof(int)+(num_rec)*sizeof(struct Employee)+(num_rec-1)*sizeof(struct Salary), ptr, sizeof(struct Salary));
				BF_WriteBlock(fileDesc, cnt-1);
			}
		}
                else if ((sizeof(int)+length*(num_rec+1))<=1024)
                {
                        memcpy(block+sizeof(int)+num_rec*length, ptr, length);
                        ++num_rec;
                        memcpy(block, &num_rec, sizeof(int));
                        if (BF_WriteBlock(fileDesc, cnt-1)<0)
                                return -1;
                }
                else
                {
                        if (BF_AllocateBlock(fileDesc)<0)
                                return -1;
                        if (BF_ReadBlock(fileDesc, cnt, &block)<0)
                                return -1;
			num_rec=1;
                        memcpy(block, &num_rec, sizeof(int));
                        memcpy(block+sizeof(int), ptr, length);
                        if (BF_WriteBlock(fileDesc, cnt)<0)
                                return -1;
                }
        }
        return 0;
}




int Sorted_CreateFile(char *fileName)
{
	if(BF_CreateFile(fileName)<0)
	{
		return -1;
	}
	return 0;
}


int Sorted_OpenFile(char *fileName)
{
	int fileDesc;
	fileDesc=BF_OpenFile(fileName);
	if(fileDesc<0)
	{
		return -1;
	}
	return fileDesc;
}


int Sorted_CloseFile(int fileDesc)
{
	int err;
	if(BF_CloseFile(fileDesc)<0)
	{
		return -1;
	}
	return 0;
}



int Sorted_SortFile(const char* fileName,int fieldNo)
{
	void *block;
	int fileDesc=BF_OpenFile(fileName);
	int cnt=BF_GetBlockCounter(fileDesc);
	int i,rec_cnt=0,temp=0,j,k=0,flag;
	BF_ReadBlock(fileDesc,cnt-1,&block);
	memcpy(&temp,block,sizeof(int));
	rec_cnt=rec_cnt+temp;
	if(cnt==1)
	{
		printf("Cannot sort!!File is empty!\n");
		return -1;
	}
	else
	{
		BF_ReadBlock(fileDesc, 0, &block);
		memcpy(&temp, block, sizeof(int));
		if (temp==1)
			j=(1024-sizeof(int))/sizeof(struct Employee);
		else if (temp==2)
			j=(1024-sizeof(int))/sizeof(struct Salary);
		else
			j=(1024-sizeof(int))/(sizeof(struct Employee)+sizeof(struct Salary));
		rec_cnt=rec_cnt + (cnt-2)*j;
	}
	struct integer* emp;
        emp=malloc(rec_cnt*sizeof(struct integer));
        struct string *emp_str;
        emp_str=malloc(rec_cnt*sizeof(struct string));
	if(temp==1)
	{
		struct Employee *employee;
		employee=malloc(rec_cnt*sizeof(struct Employee));
        	for(i=1;i<cnt;i++)
        	{
        	    BF_ReadBlock(fileDesc,i,&block);
        	    memcpy(&temp,block,sizeof(int));
        	    for(j=0;j<temp;j++)
        	    {
        	        memcpy(&employee[k],block + sizeof(int) + j*sizeof(struct Employee),sizeof(struct Employee));
        	        k++;
        	    }
        	}
		if(fieldNo==1 || fieldNo==5 || fieldNo==6 || fieldNo==7)
		{
			flag=1;
			if(fieldNo==1)
			{
				for(i=0;i<rec_cnt;i++)
				{
					emp[i].field=employee[i].id;
					emp[i].pos=i;
				}
			}
			else if (fieldNo==5)
			{
				for(i=0;i<rec_cnt;i++)
				{
					emp[i].field=employee[i].department;
					emp[i].pos=i;
				}
			}
			else if (fieldNo==6)
			{
				for(i=0;i<rec_cnt;i++)
				{
					emp[i].field=employee[i].daysOff;
					emp[i].pos=i;
				}
			}
			else if (fieldNo==7)
			{
				for(i=0;i<rec_cnt;i++)
				{
					emp[i].field=employee[i].prevYears;
					emp[i].pos=i;
				}
			}
			quicksort_int(emp,0,rec_cnt-1);
		}
		else if (fieldNo==2 || fieldNo==3 || fieldNo==4)
		{
			flag=2;
			if(fieldNo==2)
			{
				for(i=0;i<rec_cnt;i++)
				{
					strcpy(emp_str[i].field,employee[i].name);
					emp_str[i].pos=i;
				}
			}
			else if (fieldNo==3)
			{
				for(i=0;i<rec_cnt;i++)
				{
					strcpy(emp_str[i].field,employee[i].surname);
					emp_str[i].pos=i;
				}
			}
			else if (fieldNo==4)
			{
				for(i=0;i<rec_cnt;i++)
				{
					emp_str[i].field[0]=employee[i].status;
					emp_str[i].pos=i;
					emp_str[i].field[1]='\0';
				}
			}
			quicksort_str(emp_str,0,k-1);
		}
		else
		{
			printf("Wrong fieldNo\n");
			return -1;
		}
		char *name=malloc(50*sizeof(char));
		char a[2];
		sprintf(a,"%d",fieldNo);
		strcpy(name,fileName);
		strcat(name,"Sorted");
		strcat(name,a);
		if(Sorted_CreateFile(name)<0)
			return -1;
		fileDesc=Sorted_OpenFile(name);
		if(fileDesc<0)
			return -1;
		struct Employee e;
		int val;
		for(i=0;i<rec_cnt;i++)
		{
			if (flag==1)
				e=employee[emp[i].pos];
			else
				e=employee[emp_str[i].pos];
			Sorted_InsertEntry(fileDesc, &e, sizeof(e));
		}
	free(employee);
	free(name);
	Sorted_CloseFile(fileDesc);
    }
    else if (temp==2)
    {
        struct Salary *salary;
	salary=malloc(rec_cnt*sizeof(struct Salary));
        for(i=1;i<cnt;i++)
        {
            BF_ReadBlock(fileDesc,i,&block);
            memcpy(&temp,block,sizeof(int));
            for(j=0;j<temp;j++)
            {
                memcpy(&salary[k],block + sizeof(int) + j*sizeof(struct Salary),sizeof(struct Salary));
                k++;
            }
	}
	if(fieldNo==8 || fieldNo==9 || fieldNo==11)
	{
		flag=1;
		if(fieldNo==8)
		{
			for(i=0;i<rec_cnt;i++)
			{
				emp[i].field=salary[i].id;
				emp[i].pos=i;
			}
		}
		else if (fieldNo==9)
		{
			for(i=0;i<rec_cnt;i++)
			{
				emp[i].field=salary[i].salary;
				emp[i].pos=i;
			}
		}
		else if (fieldNo==11)
		{
			for(i=0;i<rec_cnt;i++)
			{
				emp[i].field=salary[i].floor;
				emp[i].pos=i;
			}
		}
		quicksort_int(emp,0,rec_cnt-1);
	}
	else if (fieldNo==10)
	{
		flag=2;
		for(i=0;i<rec_cnt;i++)
		{
			emp_str[i].field[0]=salary[i].section;
			emp_str[i].pos=i;
			emp_str[i].field[1]='\0';
		}
		quicksort_str(emp_str,0,rec_cnt-1);
	}
	else
	{
		printf("Wrong fieldNo!\n");
		return -1;
	}
		char *name=malloc(50*sizeof(char));
                char a[2];
                sprintf(a,"%d",fieldNo);
                strcpy(name,fileName);
                strcat(name,"Sorted");
                strcat(name,a);
                if(Sorted_CreateFile(name)<0)
                        return -1;
                fileDesc=Sorted_OpenFile(name);
                if(fileDesc<0)
                        return -1;
                struct Salary e;
                int val;
                for(i=0;i<rec_cnt;i++)
                {
			if (flag==1)
 	                      	e=salary[emp[i].pos];
			else
				e=salary[emp_str[i].pos];
                        Sorted_InsertEntry(fileDesc, &e, sizeof(e));
                }
	Sorted_CloseFile(fileDesc);
	free(salary);
	free(name);
    }
    free(emp);
    free(emp_str);
    return 0;
}


void Sorted_GetAllEntries(int fileDesc,char* fieldName,void *value)
{
	int cnt,i,num,j,info;
	void *block;
	BF_ReadBlock(fileDesc,0,&block);
	memcpy(&info,block,sizeof(int));
	if(value==NULL)
	{
		cnt=BF_GetBlockCounter(fileDesc);
		if(info==1)
		{
			struct Employee e;
			for(i=1;i<cnt;i++)
			{
				BF_ReadBlock(fileDesc,i,&block);
				memcpy(&num,block,sizeof(int));
				for(j=0;j<num;j++)
				{
					memcpy(&e,block+j*sizeof(struct Employee)+sizeof(int),sizeof(struct Employee));
					printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				}
			}
		}
		else if(info==2)
                {
                        struct Salary s;
                        for(i=1;i<cnt;i++)
                        {
                                BF_ReadBlock(fileDesc,i,&block);
                                memcpy(&num,block,sizeof(int));
                                for(j=0;j<num;j++)
                                {
                                        memcpy(&s,block+j*sizeof(struct Salary)+sizeof(int),sizeof(struct Salary));
                                        printf("%d %d %c %d\n",s.id,s.salary,s.section,s.floor);
                                }
                        }
                }
		if(info==3)
                {
                        struct Employee e;
			struct Salary s;
                        for(i=1;i<cnt;i++)
                        {
                                BF_ReadBlock(fileDesc,i,&block);
                                memcpy(&num,block,sizeof(int));
                                for(j=0;j<num;j++)
                                {
                                        memcpy(&e,block+j*(sizeof(struct Employee)+sizeof(struct Salary))+sizeof(int),sizeof(struct Employee));
					memcpy(&s, block+sizeof(int)+(j+1)*sizeof(struct Employee)+j*sizeof(struct Salary), sizeof(struct Salary));
                                        printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
                                }
                        }
                }
	}
	else
    {
        int fieldNo;
	int rec_cnt=0,siz;
        if (strcmp("id", fieldName)==0)
        {
                if (info==2)
                        fieldNo=8;
                else
                        fieldNo=1;
        }
        else if (strcmp("name", fieldName)==0)
                fieldNo=2;
        else if (strcmp("surname", fieldName)==0)
                fieldNo=3;
        else if (strcmp("status", fieldName)==0)
                fieldNo=4;
        else if (strcmp("depatment", fieldName)==0)
                fieldNo=5;
        else if (strcmp("daysOff", fieldName)==0)
                fieldNo=6;
        else if (strcmp("prevYears", fieldName)==0)
                fieldNo=7;
        else if (strcmp("salary", fieldName)==0)
                fieldNo=9;
        else if (strcmp("section", fieldName)==0)
                fieldNo=10;
		else if (strcmp("floor", fieldName)==0)
                        fieldNo=11;
			cnt=BF_GetBlockCounter(fileDesc);
			BF_ReadBlock(fileDesc, 1, &block);
			memcpy(&j, block, sizeof(int));
			BF_ReadBlock(fileDesc, cnt-1, &block);
			memcpy(&rec_cnt, block, sizeof(int));
			rec_cnt=rec_cnt+j*(cnt-2);
			siz=rec_cnt;
			if(info==1)
			{
				int temp_int;
				char temp_str[30];
				char temp_char;
				struct Employee e;
				if (strcmp("id", fieldName)==0)
				{
					int k=0;
					struct Employee* emp;
					emp=malloc(rec_cnt*sizeof(struct Employee));
					for(i=1;i<cnt-1;i++)
					{
						BF_ReadBlock(fileDesc,i,&block);
						memcpy(&rec_cnt,block,sizeof(int));
						for(j=0;j<rec_cnt;j++)
						{
							memcpy(&emp[k],block+sizeof(int)+j*sizeof(struct Employee),sizeof(struct Employee));
							k++;	
						}
					}
					memcpy(&temp_int, value, sizeof(int));
					bin_search_emp(emp, siz, temp_int);
				free(emp);
				}
				else
				{
					for(i=1;i<cnt;i++)
				    {
		                BF_ReadBlock(fileDesc,i,&block);
		                memcpy(&num,block,sizeof(int));
		                for(j=0;j<num;j++)
		                {
		                        memcpy(&e,block+j*sizeof(struct Employee)+sizeof(int),sizeof(struct Employee));
				            	if (strcmp("name", fieldName)==0)
				            	{
				            		memcpy(temp_str, value, 30*sizeof(char));
				            		if (strcmp(temp_str, e.name)==0)
				            			printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				            	}
				            	else if (strcmp("surname", fieldName)==0)
				            	{
				            		memcpy(temp_str, value, 30*sizeof(char));
				            		if (strcmp(temp_str, e.surname)==0)
				            			printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				            	}
				            	else if (strcmp("status", fieldName)==0)
				            	{
				          			memcpy(&temp_char, value, sizeof(char));
				          			if (temp_char==e.status)
				          				printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				          		}
				            	else if (strcmp("depatment", fieldName)==0)
				            	{
				          			memcpy(&temp_int, value, sizeof(int));
				          			if (temp_int==e.department)
				          				printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				          		}
				            	else if (strcmp("daysOff", fieldName)==0)
				            	{
				          			memcpy(&temp_int, value, sizeof(int));
				          			if (temp_int==e.daysOff)
				          				printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				          		}
				            	else if (strcmp("prevYears", fieldName)==0)
				            	{
				          			memcpy(&temp_int, value, sizeof(int));
				          			if (temp_int==e.prevYears)
				          				printf("%d %s %s %c %d %d %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears);
				          		}
		                }	
					}
				}
			}
			else if(info==2)
			{
				int temp_int;
				char temp_str[30];
				char temp_char;
				struct Salary s;
				if (strcmp("id", fieldName)==0)
				{
					int k=0;
					struct Salary* sal;
					sal=malloc(rec_cnt*sizeof(struct Salary));
					for(i=1;i<cnt-1;i++)
					{
						BF_ReadBlock(fileDesc,i,&block);
						memcpy(&rec_cnt,block,sizeof(int));
						for(j=0;j<rec_cnt;j++)
						{
							memcpy(&sal[k],block+sizeof(int)+j*sizeof(struct Salary),sizeof(struct Salary));
							k++;	
						}
					}
					memcpy(&temp_int, value, sizeof(int));
					bin_search_sal(sal, siz, temp_int);
					free(sal);
				}
				else
				{
					for(i=1;i<cnt;i++)
			        {
			                BF_ReadBlock(fileDesc,i,&block);
			                memcpy(&num,block,sizeof(int));
			                for(j=0;j<num;j++)
			                {
			                        memcpy(&s,block+j*sizeof(struct Salary)+sizeof(int),sizeof(struct Salary));
			                        if (strcmp("salary", fieldName)==0)
					          		{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==s.salary)
					          				printf("%d %d %c %d\n",s.id,s.salary,s.section,s.floor);
					          		}
					          		else if (strcmp("section", fieldName)==0)
					            	{
					          			memcpy(&temp_char, value, sizeof(char));
					          			if (temp_char==s.section)
					          				printf("%d %d %c %d\n",s.id,s.salary,s.section,s.floor);
					          		}
					          		else if (strcmp("floor", fieldName)==0)
					          		{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==s.floor)
					          				printf("%d %d %c %d\n",s.id,s.salary,s.section,s.floor);
					          		}
			                }
			        }
				}
			}
			else if(info==3)				//Gia to id 8a kanoume pinaka apo deiktes se void
			{
				int temp_int;
				char temp_str[30];
				char temp_char;
				struct Employee e;
				struct Salary s;
				if (strcmp("id", fieldName)==0)
				{
					struct Employee *emp;
					struct Salary* sal;
					int k=0;
					emp=malloc(rec_cnt*sizeof(struct Employee));
					sal=malloc(rec_cnt*sizeof(sizeof(struct Salary)));
					for(i=1;i<cnt-1;i++)
					{
						BF_ReadBlock(fileDesc,i,&block);
						memcpy(&rec_cnt,block,sizeof(int));
						for(j=0;j<rec_cnt;j++)
						{
							memcpy(&emp[k],block+sizeof(int)+j*(sizeof(struct Employee)+sizeof(struct Salary)),sizeof(struct Employee));
							memcpy(&sal[k], block+sizeof(int)+(j+1)*sizeof(struct Employee)+j*sizeof(struct Salary), sizeof(struct Salary));
							k++;	
						}
					}
					memcpy(&temp_int, value, sizeof(int));
					bin_search_mer(emp, sal, siz, temp_int);
					free(emp);
					free(sal);
				}
				else
				{
					for(i=1;i<cnt;i++)
			        {
			                BF_ReadBlock(fileDesc,i,&block);
			                memcpy(&num,block,sizeof(int));
			                for(j=0;j<num;j++)
			                {
			                        memcpy(&e,block+j*(sizeof(struct Employee)+sizeof(struct Salary))+sizeof(int),sizeof(struct Employee));
			                        memcpy(&s, block+sizeof(int)+(j+1)*sizeof(struct Employee)+j*sizeof(struct Salary), sizeof(struct Salary));
					            	if (strcmp("name", fieldName)==0)
					            	{
					            		memcpy(temp_str, value, 30*sizeof(char));
					            		if (strcmp(temp_str, e.name)==0)
					            			printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					            	}
					            	else if (strcmp("surname", fieldName)==0)
					            	{
					            		memcpy(temp_str, value, 30*sizeof(char));
					            		if (strcmp(temp_str, e.surname)==0)
					            			printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					            	}
					            	else if (strcmp("status", fieldName)==0)
					            	{
					          			memcpy(&temp_char, value, sizeof(char));
					          			if (temp_char==e.status)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
					            	else if (strcmp("department", fieldName)==0)
					            	{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==e.department)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
					            	else if (strcmp("daysOff", fieldName)==0)
					            	{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==e.daysOff)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
					            	else if (strcmp("prevYears", fieldName)==0)
					            	{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==e.prevYears)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
			                        else if (strcmp("salary", fieldName)==0)
					          		{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==s.salary)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
					          		else if (strcmp("section", fieldName)==0)
					            	{
					          			memcpy(&temp_char, value, sizeof(char));
					          			if (temp_char==s.section)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
					          		else if (strcmp("floor", fieldName)==0)
					          		{
					          			memcpy(&temp_int, value, sizeof(int));
					          			if (temp_int==s.floor)
					          				printf("%d %s %s %c %d %d %d %d %d %c %d\n",e.id,e.name,e.surname,e.status,e.department,e.daysOff,e.prevYears,s.id,s.salary,s.section,s.floor);
					          		}
			                }
			        }
				}
			}
    }
}

int Sorted_joinSortMerge(const char* file1, const char* file2, int fieldNo1, int fieldNo2)
{
	if (Sorted_CheckSortedFile(file1, fieldNo1))
		return -1;
	if (Sorted_CheckSortedFile(file2, fieldNo2))
		return -1;
	struct Employee* emp;
	struct Salary* sal;
	int rec_cnt1=0, cnt1, rec_cnt2=0, cnt2, fileDesc1, fileDesc2, i, j, k=0, mat_siz1, mat_siz2;
	void* block1;
	void* block2;
	fileDesc1=BF_OpenFile(file1);
	fileDesc2=BF_OpenFile(file2);
	cnt1=BF_GetBlockCounter(fileDesc1);
	cnt2=BF_GetBlockCounter(fileDesc2);
	BF_ReadBlock(fileDesc1, 1, &block1);
	BF_ReadBlock(fileDesc2, 1, &block2);
	memcpy(&i, block1, sizeof(int));
	memcpy(&j, block2, sizeof(int));
	rec_cnt1=(cnt1-2)*i;
	rec_cnt2=(cnt2-2)*j;
	BF_ReadBlock(fileDesc1, cnt1-1, &block1);
	BF_ReadBlock(fileDesc2, cnt2-1, &block2);
	memcpy(&i, block1, sizeof(int));
	memcpy(&j, block2, sizeof(int));
	rec_cnt1=rec_cnt1+i;
	mat_siz1=rec_cnt1;
	rec_cnt2=rec_cnt2+j;
	mat_siz2=rec_cnt2;
	emp=malloc(rec_cnt1*sizeof(struct Employee));
	sal=malloc(rec_cnt2*sizeof(struct Salary));
	for(i=1; i<cnt1; i++)
	{
		BF_ReadBlock(fileDesc1, i, &block1);
		memcpy(&rec_cnt1, block1, sizeof(int));
		for (j=0; j<rec_cnt1; j++)
		{
			memcpy(&emp[k], block1+sizeof(int)+j*sizeof(struct Employee),sizeof(struct Employee));
			k++;
		}
	}
	k=0;
	for(i=1; i<cnt2; i++)
	{
		BF_ReadBlock(fileDesc2, i, &block2);
		memcpy(&rec_cnt2, block2, sizeof(int));
		for (j=0; j<rec_cnt2; j++)
		{
			memcpy(&sal[k], block2+sizeof(int)+j*sizeof(struct Salary),sizeof(struct Salary));
			k++;
		}
	}
	struct integer* mat_int1;
	struct integer* mat_int2;
	struct string* mat_str1;
	struct string* mat_str2;
	char *name1=malloc(50*sizeof(char));
	char *name2=malloc(50*sizeof(char));
	char a[2];
	char b[2];
	sprintf(a,"%d",fieldNo1);
	sprintf(b,"%d",fieldNo2);
	strcpy(name1,file1);
	strcpy(name2,file2);
	strcat(name1,name2);
	strcat(name1,a);
	strcat(name1,"=");
	strcat(name1,b);
	if(Sorted_CreateFile(name1)<0)
		return -1;
	int fileDesc=Sorted_OpenFile(name1);
	if(fileDesc<0)
		return -1;
	if (fieldNo1==1 || fieldNo1==5 || fieldNo1==6 || fieldNo1==7 || fieldNo2==8 || fieldNo2==9 || fieldNo2==11)
	{
		mat_int1=malloc(mat_siz1*sizeof(struct integer));
		mat_int2=malloc(mat_siz2*sizeof(struct integer));
		if (fieldNo1==1 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==1 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==1 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		for (i=0; i<mat_siz1; i++)
		{
			for (j=0; j<mat_siz2; j++)
			{
				if (mat_int1[i].field==mat_int2[j].field)
				{
					Sorted_InsertEntry(fileDesc, &emp[mat_int1[i].pos],sizeof(struct Employee));
					Sorted_InsertEntry(fileDesc, &sal[mat_int2[j].pos],sizeof(struct Salary));
				}
			}
		}
	free(mat_int1);
	free(mat_int2);
	}
	else
	{
		mat_str1=malloc(mat_siz1*sizeof(struct string));
		mat_str2=malloc(mat_siz2*sizeof(struct string));
		if(fieldNo1==2 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				strcpy(mat_str1[i].field,emp[i].name);
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		else if(fieldNo1==3 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				strcpy(mat_str1[i].field,emp[i].surname);
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		else if(fieldNo1==4 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_str1[i].field[0]=emp[i].status;
				mat_str1[i].field[1]='\0';
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		for (i=0; i<mat_siz1; i++)
		{
			for (j=0; j<mat_siz2; j++)
			{
				if (strcmp(mat_str1[i].field,mat_str2[j].field)==0)
				{
					Sorted_InsertEntry(fileDesc, &emp[mat_str1[i].pos],sizeof(struct Employee));
					Sorted_InsertEntry(fileDesc, &sal[mat_str2[j].pos],sizeof(struct Salary));
				}
			}
		}
	free(mat_str1);
	free(mat_str2);
	}
	free(emp);
	free(sal);
	return 0;
}

int Sorted_CheckSortedFile(const char* filename, int fieldNo)
{void *block;
 int a,b,c,d,i,j,fd,counter=0;
 struct Employee Employee;
 struct Employee Employee2;
 struct Salary Salary;
 struct Salary Salary2;
 fd=BF_OpenFile(filename);
 BF_ReadBlock(fd,0,&block);
 printf("");
 memcpy(&a,block,sizeof(a));
 b=BF_GetBlockCounter(fd)-1;
 if(a==1)
 {for(i=1;i<=b;i++)
  {BF_ReadBlock(fd,i,&block);
   memcpy(&c,block,sizeof(int));
   for(j=0;j<c-1;j++)
   {if(fieldNo==1)
    {memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
     if(Employee.id>Employee2.id)
     {counter=counter+1;}
    }
    else if(fieldNo==2)
    {
     memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
      if(strcmp(Employee.name,Employee2.name)>0)
      {counter=counter+1;}
    }
    else if(fieldNo==3)
    {
     memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
      if(strcmp(Employee.surname,Employee2.surname)>0)
      {counter=counter+1;}
    }
    else if(fieldNo==4)
    {
     memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
      if(Employee.status>Employee2.status)
      {counter=counter+1;}
    }
    else if(fieldNo==5)
    {
     memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
     if(Employee.department>Employee2.department)
     {counter=counter+1;}
    }
    else if(fieldNo==6)
    {
     memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
     if(Employee.daysOff>Employee2.daysOff)
     {counter=counter+1;}
    }
    else if(fieldNo==7)
    {
     memcpy(&Employee,block+sizeof(int)+j*sizeof(Employee),sizeof(Employee));
     memcpy(&Employee2,block+sizeof(int)+(j+1)*sizeof(Employee2),sizeof(Employee2));
     if(Employee.prevYears>Employee2.prevYears)
     {counter=counter+1;}
    }
   }
  }
 }
 else if(a==2)
 {
  for(i=1;i<=b;i++)
  {BF_ReadBlock(fd,i,&block);
   memcpy(&c,block,sizeof(int));
   for(j=0;j<c-1;j++)
   {
    if(fieldNo==8)
    {
     memcpy(&Salary,block+sizeof(int)+j*sizeof(Salary),sizeof(Salary));
     memcpy(&Salary2,block+sizeof(int)+(j+1)*sizeof(Salary2),sizeof(Salary2));
     if(Salary.id>Salary2.id)
     {counter=counter+1;}
    }
    else if(fieldNo==9)
    {
     memcpy(&Salary,block+sizeof(int)+j*sizeof(Salary),sizeof(Salary));
     memcpy(&Salary2,block+sizeof(int)+(j+1)*sizeof(Salary2),sizeof(Salary2));
     if(Salary.salary>Salary2.salary)
     {counter=counter+1;}
    }
    else if(fieldNo==10)
    {
     memcpy(&Salary,block+sizeof(int)+j*sizeof(Salary),sizeof(Salary));
     memcpy(&Salary2,block+sizeof(int)+(j+1)*sizeof(Salary2),sizeof(Salary2));
     if(Salary.section>Salary2.section)
     {counter=counter+1;}
    }
    else if(fieldNo==11)
    {
     memcpy(&Salary,block+sizeof(int)+j*sizeof(Salary),sizeof(Salary));
     memcpy(&Salary2,block+sizeof(int)+(j+1)*sizeof(Salary2),sizeof(Salary2));
     if(Salary.floor>Salary2.floor)
     {counter=counter+1;}
    }
   }
  }
 }
 else
 {      printf("error5\n");
	return -1;
 }
 BF_CloseFile(fd);
 if(counter!=0)
 {printf("error6 %d\n",counter);
  return -1;
 }
 else 
 {return  0;}
}


int Sorted_NestedLoops(const char* filename1, const char* filename2, int fieldNo1, int fieldNo2,const char* operand)
{
if(strcmp(operand,">")==0)
	{struct Employee* emp;
	struct Salary* sal;
	int rec_cnt1=0, cnt1, rec_cnt2=0, cnt2, fileDesc1, fileDesc2, i, j, k=0, mat_siz1, mat_siz2;
	void* block1;
	void* block2;
	fileDesc1=BF_OpenFile(filename1);
	fileDesc2=BF_OpenFile(filename2);
	cnt1=BF_GetBlockCounter(fileDesc1);
	cnt2=BF_GetBlockCounter(fileDesc2);
	BF_ReadBlock(fileDesc1, 1, &block1);
	BF_ReadBlock(fileDesc2, 1, &block2);
	memcpy(&i, block1, sizeof(int));
	memcpy(&j, block2, sizeof(int));
	rec_cnt1=(cnt1-2)*i;
	rec_cnt2=(cnt2-2)*j;
	BF_ReadBlock(fileDesc1, cnt1-1, &block1);
	BF_ReadBlock(fileDesc2, cnt2-1, &block2);
	memcpy(&i, block1, sizeof(int));
	memcpy(&j, block2, sizeof(int));
	rec_cnt1=rec_cnt1+i;
	mat_siz1=rec_cnt1;
	rec_cnt2=rec_cnt2+j;
	mat_siz2=rec_cnt2;
//	printf("mat_siz1 = %d and mat_siz2 = %d \n",mat_siz1,mat_siz2);
	emp=malloc(rec_cnt1*sizeof(struct Employee));
	sal=malloc(rec_cnt2*sizeof(struct Salary));
	for(i=1; i<cnt1; i++)
	{
		BF_ReadBlock(fileDesc1, i, &block1);
		memcpy(&rec_cnt1, block1, sizeof(int));
		for (j=0; j<rec_cnt1; j++)
		{
			memcpy(&emp[k], block1+sizeof(int)+j*sizeof(struct Employee),sizeof(struct Employee));
			k++;
		}
	}
	k=0;
	for(i=1; i<cnt2; i++)
	{
		BF_ReadBlock(fileDesc2, i, &block2);
		memcpy(&rec_cnt2, block2, sizeof(int));
		for (j=0; j<rec_cnt2; j++)
		{
			memcpy(&sal[k], block2+sizeof(int)+j*sizeof(struct Salary),sizeof(struct Salary));
			k++;
		}
	}
	struct integer* mat_int1;
	struct integer* mat_int2;
	struct string* mat_str1;
	struct string* mat_str2;
	char *name1=malloc(50*sizeof(char));
	char *name2=malloc(50*sizeof(char));
	char a[2];
	char b[2];
	sprintf(a,"%d",fieldNo1);
	sprintf(b,"%d",fieldNo2);
	strcpy(name1,filename1);
	strcpy(name2,filename2);
	strcat(name1,name2);
	strcat(name1,a);
	strcat(name1,">");
	strcat(name1,b);
	if(Sorted_CreateFile(name1)<0)
		return -1;
	int fileDesc=Sorted_OpenFile(name1);
	if(fileDesc<0)
		return -1;
	if (fieldNo1==1 || fieldNo1==5 || fieldNo1==6 || fieldNo1==7 || fieldNo2==8 || fieldNo2==9 || fieldNo2==11)
	{
		mat_int1=malloc(mat_siz1*sizeof(struct integer));
		mat_int2=malloc(mat_siz2*sizeof(struct integer));
		if (fieldNo1==1 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==1 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==1 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		for (i=0; i<mat_siz1; i++)
		{
			for (j=0; j<mat_siz2; j++)
			{
				if (mat_int1[i].field>mat_int2[j].field)
				{	//printf("%d joins %d \n",mat_int1[i].field,mat_int2[j].field);
					Sorted_InsertEntry(fileDesc, &emp[mat_int1[i].pos],sizeof(struct Employee));
					Sorted_InsertEntry(fileDesc, &sal[mat_int2[j].pos],sizeof(struct Salary));
				}
			}
		}
	}
	else
	{
		mat_str1=malloc(mat_siz1*sizeof(struct string));
		mat_str2=malloc(mat_siz2*sizeof(struct string));
		if(fieldNo1==2 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				strcpy(mat_str1[i].field,emp[i].name);
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		else if(fieldNo1==3 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				strcpy(mat_str1[i].field,emp[i].surname);
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		else if(fieldNo1==4 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_str1[i].field[0]=emp[i].status;
				mat_str1[i].field[1]='\0';
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		for (i=0; i<mat_siz1; i++)
		{
			for (j=0; j<mat_siz2; j++)
			{
				if (strcmp(mat_str1[i].field,mat_str2[j].field)>0)
				{       //printf("%s joins %s \n",mat_str1[i].field,mat_str2[j].field);
					Sorted_InsertEntry(fileDesc, &emp[mat_str1[i].pos],sizeof(struct Employee));
					Sorted_InsertEntry(fileDesc, &sal[mat_str2[j].pos],sizeof(struct Salary));
				}
			}
		}

	}
//Sorted_GetAllEntries(fileDesc,"id",NULL);
}
else
{
        struct Employee* emp;
	struct Salary* sal;
	int rec_cnt1=0, cnt1, rec_cnt2=0, cnt2, fileDesc1, fileDesc2, i, j, k=0, mat_siz1, mat_siz2;
	void* block1;
	void* block2;
	fileDesc1=BF_OpenFile(filename1);
	fileDesc2=BF_OpenFile(filename2);
	cnt1=BF_GetBlockCounter(fileDesc1);
	cnt2=BF_GetBlockCounter(fileDesc2);
	BF_ReadBlock(fileDesc1, 1, &block1);
	BF_ReadBlock(fileDesc2, 1, &block2);
	memcpy(&i, block1, sizeof(int));
	memcpy(&j, block2, sizeof(int));
	rec_cnt1=(cnt1-2)*i;
	rec_cnt2=(cnt2-2)*j;
	BF_ReadBlock(fileDesc1, cnt1-1, &block1);
	BF_ReadBlock(fileDesc2, cnt2-1, &block2);
	memcpy(&i, block1, sizeof(int));
	memcpy(&j, block2, sizeof(int));
	rec_cnt1=rec_cnt1+i;
	mat_siz1=rec_cnt1;
	rec_cnt2=rec_cnt2+j;
	mat_siz2=rec_cnt2;
	//printf("mat_siz1 = %d and mat_siz2 = %d \n",mat_siz1,mat_siz2);
	emp=malloc(rec_cnt1*sizeof(struct Employee));
	sal=malloc(rec_cnt2*sizeof(struct Salary));
	for(i=1; i<cnt1; i++)
	{
		BF_ReadBlock(fileDesc1, i, &block1);
		memcpy(&rec_cnt1, block1, sizeof(int));
		for (j=0; j<rec_cnt1; j++)
		{
			memcpy(&emp[k], block1+sizeof(int)+j*sizeof(struct Employee),sizeof(struct Employee));
			k++;
		}
	}
	k=0;
	for(i=1; i<cnt2; i++)
	{
		BF_ReadBlock(fileDesc2, i, &block2);
		memcpy(&rec_cnt2, block2, sizeof(int));
		for (j=0; j<rec_cnt2; j++)
		{
			memcpy(&sal[k], block2+sizeof(int)+j*sizeof(struct Salary),sizeof(struct Salary));
			k++;
		}
	}
	struct integer* mat_int1;
	struct integer* mat_int2;
	struct string* mat_str1;
	struct string* mat_str2;
	char *name1=malloc(50*sizeof(char));
	char *name2=malloc(50*sizeof(char));
	char a[2];
	char b[2];
	sprintf(a,"%d",fieldNo1);
	sprintf(b,"%d",fieldNo2);
	strcpy(name1,filename1);
	strcpy(name2,filename2);
	strcat(name1,name2);
	strcat(name1,a);
	strcat(name1,"<");
	strcat(name1,b);
	if(Sorted_CreateFile(name1)<0)
		return -1;
	int fileDesc=Sorted_OpenFile(name1);
	if(fileDesc<0)
		return -1;
	if (fieldNo1==1 || fieldNo1==5 || fieldNo1==6 || fieldNo1==7 || fieldNo2==8 || fieldNo2==9 || fieldNo2==11)
	{
		mat_int1=malloc(mat_siz1*sizeof(struct integer));
		mat_int2=malloc(mat_siz2*sizeof(struct integer));
		if (fieldNo1==1 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==1 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==1 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].id;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==5 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].department;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==6 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].daysOff;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==8)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].id;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==9)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].salary;
				mat_int2[i].pos=i;
			}
		}
		else if(fieldNo1==7 && fieldNo2==11)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_int1[i].field=emp[i].prevYears;
				mat_int1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_int2[i].field=sal[i].floor;
				mat_int2[i].pos=i;
			}
		}
		for (i=0; i<mat_siz1; i++)
		{
			for (j=0; j<mat_siz2; j++)
			{
				if (mat_int1[i].field<mat_int2[j].field)
				{	//printf("%d joins %d \n",mat_int1[i].field,mat_int2[j].field);
					Sorted_InsertEntry(fileDesc, &emp[mat_int1[i].pos],sizeof(struct Employee));
					Sorted_InsertEntry(fileDesc, &sal[mat_int2[j].pos],sizeof(struct Salary));
				}
			}
		}
	}
	else
	{
		mat_str1=malloc(mat_siz1*sizeof(struct string));
		mat_str2=malloc(mat_siz2*sizeof(struct string));
		if(fieldNo1==2 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				strcpy(mat_str1[i].field,emp[i].name);
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		else if(fieldNo1==3 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				strcpy(mat_str1[i].field,emp[i].surname);
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		else if(fieldNo1==4 && fieldNo2==10)
		{
			for(i=0;i<mat_siz1;i++)
			{
				mat_str1[i].field[0]=emp[i].status;
				mat_str1[i].field[1]='\0';
				mat_str1[i].pos=i;
			}
			for(i=0;i<mat_siz2;i++)
			{
				mat_str2[i].field[0]=sal[i].section;
				mat_str2[i].field[1]='\0';
				mat_str2[i].pos=i;
			}
		}
		for (i=0; i<mat_siz1; i++)
		{
			for (j=0; j<mat_siz2; j++)
			{
				if (strcmp(mat_str1[i].field,mat_str2[j].field)<0)
				{       //printf("%s joins %s \n",mat_str1[i].field,mat_str2[j].field);
					Sorted_InsertEntry(fileDesc, &emp[mat_str1[i].pos],sizeof(struct Employee));
					Sorted_InsertEntry(fileDesc, &sal[mat_str2[j].pos],sizeof(struct Salary));
				}
			}
		}
	}
//Sorted_GetAllEntries(fileDesc,"id",NULL);
}
return 0;
}






int Sorted_MergeFiles(const char* filename1, const char* filename2, const char* operand, int fieldNo1, int fieldNo2)
{
 if(strcmp(operand,"=")==0)
 {
  if(Sorted_joinSortMerge(filename1,filename2,fieldNo1,fieldNo2)==0)
  {return 0;}
  else
  {return -1;}
 }
 else if(strcmp(operand,">")==0 || strcmp(operand,"<")==0)
 {if(strcmp(operand,">")==0)
  {if(Sorted_NestedLoops(filename1,filename2,fieldNo1,fieldNo2,operand)==0)
   {return 0;}
   else
   {return -1;}
  }
  else if(strcmp(operand,"<")==0)
  {if(Sorted_NestedLoops(filename1,filename2,fieldNo1,fieldNo2,operand)==0)
   {return 0;}
   else
   {return -1;}
  }
 }
}
