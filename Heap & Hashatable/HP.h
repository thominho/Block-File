
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
} Record;


int HP_CreateFile(char *fileName);
int HP_OpenFile(char *fileName);
int HP_CloseFile(int fileDesc);
int HP_InsertEntry(int fileDessc,Record record);
void HP_GetAllEntries(int fileDesc,char *fieldName,void *value);
