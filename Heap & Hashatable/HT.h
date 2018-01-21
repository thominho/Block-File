#include "BF.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define NAME_SIZE       15
#define SURNAME_SIZE        20
#define DATE_OF_BIRTH_SIZE  10
#define FILENAME_HASH_ID "hash_id"


typedef struct {
    int fileDesc;
    char attrType;
    char attrName[30];
    int attrLength;
    int depth;
} HT_info;

int vath;
/*
typedef struct{
    int id;
    char name[15];
    char surname[20];
    char status[1];
    char dateOfBirth[11];
    int salary;
    char section[1];
    int daysOff;
    int prevYears;
} Record; */
extern Record record;
int pow_two(int x)
{
    int i;
    int tot=1;
    for (i=1; i<=x; i++)
        tot=tot*2;
    return tot;
}

int Hash_Function(HT_info* header_info, Record record, int d)
{
    unsigned long int temp=0;
    int res, i;
    if (strcmp(header_info->attrName,"id")==0)
    {
        res=(record.id)%pow_two(d);
    }
    else if (strcmp(header_info->attrName,"name")==0)
    {
        for(i=0; i<strlen(record.name); i++)
        {
            temp=temp+record.name[i];
        }
        res=temp%pow_two(d);
    }
    else if (strcmp(header_info->attrName,"surname")==0)
    {
            for(i=0; i<strlen(record.name); i++)
            {
                    temp=temp+record.surname[i];
            }
            res=temp%pow_two(d);
    }
    else if (strcmp(header_info->attrName,"dateOfBirth")==0)
    {
            for(i=0; i<strlen(record.name); i++)
            {
                    temp=temp+record.dateOfBirth[i];
            }
            res=temp%pow_two(d);
    }
    else if (strcmp(header_info->attrName,"status")==0)
    {
        res=(record.status[0])%pow_two(d);
    }
    else if(strcmp(header_info->attrName,"section")==0)
    {
        res=(record.section[0])%pow_two(d);
    }
    else if(strcmp(header_info->attrName,"salary")==0)
    {
        res=(record.salary)%pow_two(d);
    }
    else if(strcmp(header_info->attrName,"daysOff")==0)
    {
        res=(record.daysOff)%pow_two(d);
    }
    else if(strcmp(header_info->attrName,"prevYears")==0)
    {
        res=(record.prevYears)%pow_two(d);
    }
    return res;
}

int all_same(void* block, HT_info* info)
{
    int i, k, c;
    char str[30];
    Record rec;
    memcpy(&rec, block+3*sizeof(int), sizeof(rec));
    block=block+3*sizeof(int);
    if (strcmp(info->attrName,"id")==0)
    {
        k=rec.id;
        for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
        {
            memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
            if (rec.id!=k)
            {
                return 1;
            }
        }
        return 0;
    }
    if (strcmp(info->attrName,"name")==0)
        {
            strcpy(str,rec.name);
            for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
            {
                memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                if (strcmp(rec.name,str)!=0)
                {
                return 1;
                }
            }
            return 0;
        }
        if (strcmp(info->attrName,"surname")==0)
        {
            strcpy(str,rec.surname);
            for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
            {
                memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                if (strcmp(rec.surname,str)!=0)
                {
                    return 1;
                }
            }
                return 0;
        }
        if (strcmp(info->attrName,"dateOfBirth")==0)
        {
            strcpy(str,rec.dateOfBirth);
            for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
            {
                memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                if (strcmp(rec.dateOfBirth,str)!=0)
                {
                    return 1;
                }
            }
            return 0;
        }
        if (strcmp(info->attrName,"status")==0)
        {
                c=rec.status[0];
                for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
                {
                    memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                    if (rec.status[0]!=c)
                        return 1;
                }
                return 0;
        }
        if(strcmp(info->attrName,"section")==0)
        {
                c=rec.section[0];
                for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
                {
                        memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                        if (rec.section[0]!=c)
                                return 1;
                }
                return 0;
        }
        else if(strcmp(info->attrName,"salary")==0)
        {
                k=rec.salary;
                for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
                {
                        memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                        if (rec.salary!=k)
                                return 1;
                }
                return 0;
        }
        else if(strcmp(info->attrName,"daysOff")==0)
        {
              k=rec.daysOff;
                for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
                {
                        memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                        if (rec.daysOff!=k)
                                return 1;
                }
                return 0;
        }
        else if(strcmp(info->attrName,"prevYears")==0)
        {
              k=rec.prevYears;
                for (i=1; i<((512-3*sizeof(int))/sizeof(rec)); i++)
                {
                        memcpy(&rec,block+i*sizeof(rec), sizeof(rec));
                        if (rec.prevYears!=k)
                                return 1;
                }
                return 0;
        }
}

int HT_CreateIndex(char *filename, char attrType, char* attrName, int attrLength, int depth)
{
    int err=0;
    int type=1;
    int fileDesc, i;
    void* block;
    int siz;
    int* index;
    HT_info data;
    int init=2;
    int rows;
    int num_rec=0;
    int num_ov=0;
    int l_depth=depth;
    vath=depth;
    err=BF_CreateFile(filename);
    if (err!=0)
    {
        BF_PrintError("Error at creating file");
        return -1;
    }
    err=BF_OpenFile(filename);
    fileDesc=err;
    if (err<0)
        {
                BF_PrintError("Error at opening file");
                return -1;
        }
    err=BF_AllocateBlock(fileDesc);
    if (err!=0)
        {
                BF_PrintError("Error at allocating block");
                return -1;
        }
    err=BF_ReadBlock(fileDesc, 0, &block);
    if (err!=0)
    {
        BF_PrintError("Error at reading block");
        return -1;
    }
    data.fileDesc=fileDesc;
    data.attrType=attrType;
    strcpy(data.attrName, attrName);
    data.attrLength=attrLength;
    data.depth=depth;
    memcpy(block, &type, sizeof(int));
    memcpy(block+sizeof(int), &data, sizeof(data));
    err=BF_WriteBlock(fileDesc, 0);
    if (err!=0)
    {
        BF_PrintError("Error at writing block");
        return -1;
    }
    err=BF_AllocateBlock(fileDesc);
    if (err!=0)
        {
                BF_PrintError("Error at allocating block");
                return -1;
        }
        err=BF_ReadBlock(fileDesc, 1, &block);
        if (err!=0)
        {
                BF_PrintError("Error at reading block");
                return -1;
        }
    rows=512/sizeof(int);
    for(i=0; i<pow_two(depth); i++)
    {
        memcpy(block+i*sizeof(int), &init, sizeof(int));
        init++;
    }
    err=BF_WriteBlock(fileDesc, 1);
        if (err!=0)
        {
                BF_PrintError("Error at writing block");
                return -1;
        }
    init=2;
    for (i=0; i<pow_two(depth);i++)
    {
        err=BF_AllocateBlock(fileDesc);
        if (err!=0)
            {
                    BF_PrintError("Error at allocating block");
                    return -1;
            }
        err=BF_ReadBlock(fileDesc, init, &block);
            if (err!=0)
            {
                    BF_PrintError("Error at reading block");
                    return -1;
            }
        memcpy(block,&num_rec, sizeof(int));
        memcpy(block+sizeof(int), &num_ov, sizeof(int));
        memcpy(block+2*sizeof(int), &l_depth, sizeof(int));
        err=BF_WriteBlock(fileDesc, init);
            if (err!=0)
            {
                    BF_PrintError("Error at writing block");
                    return -1;
            }
        init++;
    }
    err=BF_CloseFile(fileDesc);
    if (err!=0)
    {
        BF_PrintError("Error at closing file");
        return -1;
    }
    return err;
}

HT_info* HT_OpenIndex(char* filename)
{
    int err;
    int fileDesc;
    HT_info data;
    HT_info* info;
    void* block;
    int type;
    err=BF_OpenFile(filename);
    fileDesc=err;
    if (err<0)
    {
        BF_PrintError("Error at opening file");
        return NULL;
    }
    err=BF_ReadBlock(fileDesc, 0, &block);
    if (err!=0)
    {
        BF_PrintError("Error at reading 1st block");
        return NULL;
    }
    memcpy(&type, block, sizeof(int));
    memcpy(&data, block+sizeof(int), sizeof(data));
    if (type!=1)
    {
        return NULL;
    }
    info=malloc(sizeof(data));
    info->fileDesc=data.fileDesc;
    info->attrType=data.attrType;
    strcpy(info->attrName,data.attrName);
    info->attrLength=data.attrLength;
    info->depth=data.depth;
    return info;
}

int HT_CloseIndex( HT_info* header_info)
{
   int err;
   err=BF_CloseFile(header_info->fileDesc);
   if (err!=0)
   {
    BF_PrintError("Error at closing file");
    return -1;
   }
}

int HT_InsertEntry(HT_info* header_info, Record record)
{
    int res, rec_num, ov_pos, ldp, des;
    int i, loc, dif, bnt1, bnt2;
    int temp;
    void* block;
    void* mat;
    void* dest;
    int pos;
    int recs;
    Record temp_rec;
    res=Hash_Function(header_info, record, vath);
    BF_ReadBlock(header_info->fileDesc, 1, &mat);
    memcpy(&pos, mat+res*sizeof(int), sizeof(int));
    BF_ReadBlock(header_info->fileDesc, pos, &block);
    memcpy(&recs, block, sizeof(int));
    memcpy(&ldp, block+2*sizeof(int), sizeof(int));
    if ((recs+1)<=((512-3*sizeof(int))/sizeof(record)))
    {
        memcpy(block+3*sizeof(int)+recs*sizeof(record), &record, sizeof(record));
        memcpy(&recs, block, sizeof(int));
        ++recs;
        memcpy(block, &recs, sizeof(int));
    }
    else
    {
        if (all_same(block, header_info)==0 )
        {
            memcpy(&ov_pos, block+sizeof(int), sizeof(int));
            while(ov_pos!=0)
            {
                BF_ReadBlock(header_info->fileDesc, ov_pos, &block);
                memcpy(&ov_pos, block+sizeof(int), sizeof(int));
            }
            memcpy(&rec_num, block, sizeof(int));
            if ((rec_num+1)<=((512-3*sizeof(int))/sizeof(record)))
            {
                memcpy(block+3*sizeof(int)+rec_num*sizeof(record), &record,sizeof(record));
                ++rec_num;
                memcpy(block, &rec_num, sizeof(int));
            }
            else
            {
                rec_num=1;
                BF_AllocateBlock(header_info->fileDesc);
		temp=BF_GetBlockCounter(header_info->fileDesc);
                BF_ReadBlock(header_info->fileDesc, temp-1, &block);
                memcpy(block, &rec_num, sizeof(int));
		rec_num=0;
                memcpy(block+sizeof(int), &rec_num, sizeof(int));
                memcpy(block+3*sizeof(int), &record, sizeof(record));
		BF_WriteBlock(header_info->fileDesc, temp-1);
	    }
        }
        else if(ldp<vath)
        {
            rec_num=0;
            ov_pos=0;
            dif=vath-ldp;
	    ++ldp;
	    BF_AllocateBlock(header_info->fileDesc);
	    temp=BF_GetBlockCounter(header_info->fileDesc);
	    --temp;
	    BF_ReadBlock(header_info->fileDesc, temp, &dest);
	    memcpy(dest, &rec_num, sizeof(int));
	    memcpy(dest+sizeof(int), &rec_num, sizeof(int));
	    memcpy(dest+2*sizeof(int), &ldp, sizeof(int));
            for(i=0; i<pow_two(vath-1); i++)
	    {
		memcpy(&rec_num, mat+i*sizeof(int), sizeof(int));
		if (pos==rec_num)
		{
			memcpy(mat+pow_two(vath-1)*sizeof(int)+i*sizeof(int), &temp, sizeof(int));
		}
	    }
	    rec_num=0;
	    memcpy(block, &rec_num, sizeof(int));
	    memcpy(block+sizeof(int), &rec_num, sizeof(int));
	    memcpy(block+2*sizeof(int), &ldp, sizeof(int));
            for (i=0; i<((512-3*sizeof(int))/sizeof(record)); i++)
            {
                memcpy(&temp_rec, block+3*sizeof(int)+i*sizeof(record), sizeof(record));
                memcpy(&loc, mat+Hash_Function(header_info, temp_rec, vath)*sizeof(int), sizeof(int));
                BF_ReadBlock(header_info->fileDesc, loc, &dest);
                memcpy(&rec_num, dest, sizeof(int));
                ++rec_num;
                memcpy(dest, &rec_num, sizeof(int));
                memcpy(dest+3*sizeof(int)+(rec_num-1)*sizeof(record), &temp_rec,sizeof(record));
            }
            memcpy(&loc, mat+Hash_Function(header_info, record, vath)*sizeof(int), sizeof(int));
            BF_ReadBlock(header_info->fileDesc, loc, &dest);
            memcpy(&rec_num, dest, sizeof(int));
            ++rec_num;
            memcpy(dest, &rec_num, sizeof(int));
            memcpy(dest+3*sizeof(int)+(rec_num-1)*sizeof(record), &record,sizeof(record));
            BF_WriteBlock(header_info->fileDesc, temp-1);
	}
        else if(ldp==vath)
        {
            rec_num=0;
            ov_pos=0;
            if (pow_two(vath+1)>(512/sizeof(int)))
            {
                printf("Cannot insert entry with id %d due to index memory excession\n",record.id);
                return 2;
            }
            BF_ReadBlock(header_info->fileDesc, 1, &mat);
            for (i=0; i<pow_two(vath); i++)
            {
                memcpy(&temp, mat+i*sizeof(int), sizeof(int));
                memcpy(mat+(pow_two(vath)+i)*sizeof(int), &temp, sizeof(int));
            }
            vath++;
            memcpy(block, &rec_num, sizeof(int));
            memcpy(block+sizeof(int), &ov_pos, sizeof(int));
            memcpy(block+2*sizeof(int), &vath, sizeof(int));
            BF_AllocateBlock(header_info->fileDesc);
            loc=BF_GetBlockCounter(header_info->fileDesc)-1;
            BF_ReadBlock(header_info->fileDesc, loc, &dest);
            memcpy(mat+pow_two(vath-1)*sizeof(int)+pos*sizeof(int), &loc, sizeof(int));
	    memcpy(dest, &rec_num, sizeof(int));
            memcpy(dest+sizeof(int), &ov_pos, sizeof(int));
            memcpy(dest+2*sizeof(int), &vath, sizeof(int));
	    BF_WriteBlock(header_info->fileDesc, loc);
            for (i=0; i<((512-3*sizeof(int))/sizeof(record)); i++)
            {
                memcpy(&temp_rec, block+3*sizeof(int)+i*sizeof(record), sizeof(record));
                memcpy(&loc, mat+Hash_Function(header_info, temp_rec, vath)*sizeof(int), sizeof(int));
                BF_ReadBlock(header_info->fileDesc, loc, &dest);
                memcpy(&rec_num, dest, sizeof(int));
                ++rec_num;
                memcpy(dest, &rec_num, sizeof(int));
                memcpy(dest+3*sizeof(int)+(rec_num-1)*sizeof(record), &temp_rec,sizeof(record));
            }
            memcpy(&loc, mat+Hash_Function(header_info, record, vath)*sizeof(int), sizeof(int));
            BF_ReadBlock(header_info->fileDesc, loc, &dest);
            memcpy(&rec_num, dest, sizeof(int));
            ++rec_num;
            memcpy(dest, &rec_num, sizeof(int));
            memcpy(dest+3*sizeof(int)+(rec_num-1)*sizeof(record), &record,sizeof(record));
        }
    }
}


int Hash_in_the_ash1(int id)        //  ;)
{
    return id%pow_two(vath);
}

int Hash_in_the_ash2(char c)        //  ;) ;)
{
	int x, res;
	x=c;
	res=x%pow_two(vath);
	return res;
}

int Hash_in_the_ash3(char* str)	  //   ;) ;) ;)
{
	char cp[30];
	int i, temp, res;
	strcmp(cp,str);
	for(i=0; i<strlen(cp); i++)
	{
		temp=cp[i];
	}
	res=temp%pow_two(vath);
	return res;
}

void HT_GetAllEntries(HT_info* header_info, void* value)
{
    if (value==NULL)
    {
        int i, j, ov_pos, rec_num;
        void* block;
	int cnt=0;
        Record rec;
        for (i=2; i<BF_GetBlockCounter( header_info->fileDesc); i++)
        {
            BF_ReadBlock(header_info->fileDesc, i, &block);
            memcpy(&ov_pos, block+sizeof(int), sizeof(int));
            memcpy(&rec_num, block, sizeof(int));
            for (j=0; j<rec_num; j++)
            {
                memcpy(&rec, block+3*sizeof(int)+j*sizeof(rec), sizeof(rec));
                printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0], rec.daysOff, rec.prevYears);
            }
	   cnt++;
        }
	printf("Total number of blocks read is %d\n", cnt);
    }
    else{
        if (header_info->attrType=='i')
            {
            int id,s=0;
            void* mat;
            void* block;
            int pos, ov_pos, rec_num, i;
	    int cnt=0;
            Record rec;
            memcpy(&id, value, sizeof(int));
            BF_ReadBlock(header_info->fileDesc, 1, &mat);
            memcpy(&pos, mat+Hash_in_the_ash1(id)*(sizeof(int)), sizeof(int));
            BF_ReadBlock(header_info->fileDesc, pos, &block);
            memcpy(&ov_pos, block+sizeof(int), sizeof(int));
            memcpy(&rec_num, block, sizeof(int));
            while(1) {
				cnt++;
				if(ov_pos==0) {
					for (i=0; i<rec_num; i++)
		                	{
		                    		memcpy(&rec, block+3*sizeof(int)+i*sizeof(rec), sizeof(rec));
		                    		printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0], rec.daysOff, rec.prevYears);
		                	}
				break;
				}
				else {
					for (i=0; i<rec_num; i++)
		                        {
		                                memcpy(&rec, block+3*sizeof(int)+i*sizeof(rec), sizeof(rec));
		  				printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0],rec.daysOff, rec.prevYears);
		                        }
					BF_ReadBlock(header_info->fileDesc, ov_pos, &block);
		                	memcpy(&ov_pos, block+sizeof(int), sizeof(int));
		                	memcpy(&rec_num, block, sizeof(int));
				}
	   		}
	printf("Total number of blocks read is %d\n", cnt);
       }
	else
	{
		char str[30];
		int flag=0;
		int i;
		memcpy(str, value, 30*sizeof(char));
		for (i=0; i<30; i++)
		{
			if(str[i]=='\0')
			{
				flag=1;
				break;
			}
		}
		if (flag==0)
		{
			int s=0;
			void* mat;
            		void* block;
           		 int pos, ov_pos, rec_num, i;
			int cnt=0;
           		 Record rec;
           		 BF_ReadBlock(header_info->fileDesc, 1, &mat);
           		 memcpy(&pos, mat+Hash_in_the_ash2(str[0])*(sizeof(int)), sizeof(int));
           		 BF_ReadBlock(header_info->fileDesc, pos, &block);
           		 memcpy(&ov_pos, block+sizeof(int), sizeof(int));
           		 memcpy(&rec_num, block, sizeof(int));
           		 while(1) {
				cnt++;
                                if(ov_pos==0) {
                                        for (i=0; i<rec_num; i++)
                                        {
                                                memcpy(&rec, block+3*sizeof(int)+i*sizeof(rec), sizeof(rec));
                                                printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0], rec.daysOff, rec.prevYears);
                                        }
                                break;
                                }
                                else {
                                        for (i=0; i<rec_num; i++)
                                        {
                                                memcpy(&rec, block+3*sizeof(int)+i*sizeof(rec), sizeof(rec));
                                                printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0],rec.daysOff, rec.prevYears);
                                        }
                                        BF_ReadBlock(header_info->fileDesc, ov_pos, &block);
                                        memcpy(&ov_pos, block+sizeof(int), sizeof(int));
                                        memcpy(&rec_num, block, sizeof(int));
                                }
                        }
			printf("Total number of blocks read is %d\n", cnt);
		}
		else
		{
			int s=0;
                        void* mat;
                        void* block;
                         int pos, ov_pos, rec_num, i;
			int cnt=0;
                         Record rec;
                         BF_ReadBlock(header_info->fileDesc, 1, &mat);
                         memcpy(&pos, mat+Hash_in_the_ash3(str)*(sizeof(int)), sizeof(int));
                         BF_ReadBlock(header_info->fileDesc, pos, &block);
                         memcpy(&ov_pos, block+sizeof(int), sizeof(int));
                         memcpy(&rec_num, block, sizeof(int));
                         while(1) {
				cnt++;
                                if(ov_pos==0) {
                                        for (i=0; i<rec_num; i++)
                                        {
                                                memcpy(&rec, block+3*sizeof(int)+i*sizeof(rec), sizeof(rec));
                                                printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0], rec.daysOff, rec.prevYears);
                                        }
                                break;
                                }
                                else {
                                        for (i=0; i<rec_num; i++)
                                        {
                                                memcpy(&rec, block+3*sizeof(int)+i*sizeof(rec), sizeof(rec));
                                                printf("%d   %s   %s   %c   %s   %d   %c   %d   %d\n", rec.id, rec.name, rec.surname, rec.status[0], rec.dateOfBirth, rec.salary, rec.section[0],rec.daysOff, rec.prevYears);
                                        }
                                        BF_ReadBlock(header_info->fileDesc, ov_pos, &block);
                                        memcpy(&ov_pos, block+sizeof(int), sizeof(int));
                                        memcpy(&rec_num, block, sizeof(int));
				}
			}
			printf("Total number of blocks read is %d\n", cnt);
		}
	}
    }
}




