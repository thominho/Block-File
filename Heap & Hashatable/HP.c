#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HP.h"
#include "BF.h"

typedef struct{
int type;} special;

int HP_CreateFile(char *fileName)
{int i,fd,a,b,c;
 void *block;
 int d=0;
 special ta;
 ta.type=1;
 i=BF_CreateFile(fileName);
 if(i==0)
 {fd=BF_OpenFile(fileName);
 BF_AllocateBlock(fd);
 BF_ReadBlock(fd,0,&block);
 memcpy(block,&d,sizeof(d));
 BF_WriteBlock(fd,0);
 BF_AllocateBlock(fd);
 BF_ReadBlock(fd,1,&block);
 memcpy(block,&ta,sizeof(ta));
 BF_WriteBlock(fd,1);
 BF_AllocateBlock(fd);
 BF_CloseFile(fd);
 return i;}
 else
 {return -1;}
}

int HP_OpenFile(char *fileName)
{int fd,i,a;
 void *block;
 int ta;
 fd=BF_OpenFile(fileName);
 if(fd>0)
 {BF_ReadBlock(fd,0,&block);
  memcpy(&ta,block,sizeof(ta));
 if(a==0)
 {return fd;}
 else
 {return -1;}}
}

int HP_CloseFile(int fileDesc)
{int i;
 i=BF_CloseFile(fileDesc);
 return i;
}

int HP_InsertEntry(int fileDesc,Record record)
{int a,b,c;
 void *block;
 special t;
 BF_ReadBlock(fileDesc,1,&block);
 memcpy(&t,block,sizeof(t));
 if(t.type%8==0)
 {BF_AllocateBlock(fileDesc);
  a=BF_GetBlockCounter(fileDesc);
  BF_ReadBlock(fileDesc,a-2,&block);
  memcpy(block+8*sizeof(record),&record,sizeof(record));
  BF_WriteBlock(fileDesc,a-2);
 }
 else
 {a=BF_GetBlockCounter(fileDesc);
  BF_ReadBlock(fileDesc,a-1,&block);
  if(t.type%8==1)
  {memcpy(block,&record,sizeof(record));}
  else
  {memcpy(block+(t.type%8)*sizeof(record),&record,sizeof(record));}
  BF_WriteBlock(fileDesc,a-1);
 }
 t.type=t.type+1;
 BF_ReadBlock(fileDesc,1,&block);
 memcpy(block,&t,sizeof(t));
 return b;
}

void HP_GetAllEntries(int fileDesc,char *fieldName,void *value)
{int i=0,max=BF_GetBlockCounter(fileDesc),j=2,k=1,op;
 void *block;
 Record record;
 special t;
 BF_ReadBlock(fileDesc,1,&block);
 memcpy(&t,block,sizeof(t));
 BF_ReadBlock(fileDesc,j,&block);
 if(fieldName==NULL && value==NULL)
 {for(i=1;i<t.type-1;i++)
  {if(i%9==0)
   {j=j+1;
    BF_ReadBlock(fileDesc,j,&block);
    k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);
   k=k+1;
  }
 }
 else
 {if(value==NULL)
  {printf("Sorry but the value is NULL i cannot print something {QQ} i am so sad \n");}
  else
  {if(strcmp(fieldName,"id")==0)
   {
   for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(atoi(value)==record.id)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"name")==0)
   {
   for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(strcmp(value,record.name)==0)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"surname")==0)
   {
    for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(strcmp(value,record.surname)==0)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"status")==0)
   {
   for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(strncmp(record.status,value,1)==0)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"dateOfBirth")==0)
   {
   for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(strcmp(value,record.dateOfBirth)==0)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"salary")==0)
   {
    for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(atoi(value)==record.salary)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"section")==0)
   {
    for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(strncmp(record.section,value,1)==0)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"daysOff")==0)
   {
    for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(atoi(value)==record.daysOff)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else if(strcmp(fieldName,"prevYears")==0)
   {
    for(i=1;i<t.type-1;i++)
    {if(i%9==0)
     {j=j+1;
      BF_ReadBlock(fileDesc,j,&block);
      k=1;}
   if(k==1)
   {memcpy(&record,block,sizeof(record));}
   else
   {memcpy(&record,block+k*sizeof(record),sizeof(record));}
   if(atoi(value)==record.prevYears)
   {printf("%d ",record.id);
   printf("%s ",record.name);
   printf("%s ",record.surname);
   printf("%c ",record.status[0]);
   printf("%s ",record.dateOfBirth);
   printf("%d ",record.salary);
   printf("%c ",record.section[0]);
   printf("%d ",record.daysOff);
   printf("%d \n",record.prevYears);}
   k=k+1;
  }
   }
   else
   {printf("there is not such a fieldName\n");}
  }
 }
 printf("I have read %d Blocks\n",(t.type-2)/8);
}
