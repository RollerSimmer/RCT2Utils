#pragma once


typedef struct
{
	char*name;  
	long FieldCount;  
	long Capacity;  
	long RecordCount;  
	long DeletedCount;  
	long NextDeletedRecord;  
	bool Flag0;  
	bool Flag1;  
	bool Flag2;  
	bool Flag3;  
	bool nonAllocated;   
}
TtdbTableProperties;

typedef enum
{ 
	tdbString	=0, 
	tdbBinary	=1, 
	tdbSInt		=2,
	tdbUInt		=3, 
	tdbFloat	=4,  
	tdbInt		=0x2CE
}
TtdbFieldType;

typedef struct
{
	char*name;
	long size;
	TtdbFieldType dataType;
}
TtdbFieldProperties;

bool __stdcall TDBClose(long DBIndex); 
bool __stdcall TDBDatabaseCompact(long DBIndex);  
bool __stdcall TDBDatabaseGetTableCount(long DBIndex);  
bool __stdcall TDBFieldGetProperties(long DBIndex,char*TableName,long FieldIndex,TtdbFieldProperties&FieldProperties);
bool __stdcall TDBFieldGetValueAsBinary(long DBIndex,char*TableName,char*FieldName,long RecNo,char*&OutBuffer);
long __stdcall TDBFieldGetValueAsInteger(long DBIndex,char*TableName,char*FieldName,long RecNo);
float __stdcall TDBFieldGetValueAsFloat(long DBIndex,char*TableName,char*FieldName,long RecNo);
bool __stdcall TDBFieldGetValueAsString(long DBIndex,char*TableName,char*FieldName,long RecNo,char*&OutBuffer);
bool __stdcall TDBFieldSetValueAsFloat(long DBIndex,char*TableName,char*FieldName,long RecNo,float NewValue);
bool __stdcall TDBFieldSetValueAsInteger(long DBIndex,char*TableName,char*FieldName,long RecNo,long NewValue);
bool __stdcall TDBFieldSetValueAsString(long DBIndex,char*TableName,char*FieldName,long RecNo,char*NewValue);
long __stdcall TDBOpen(char*FileName);
long __stdcall TDBQueryGetResult(long Index);
long __stdcall TDBQueryGetResultSize();
bool __stdcall TDBSave(long DBIndex);
bool __stdcall TDBTableGetProperties(long DBIndex,long TableIndex,TtdbTableProperties&TableProperties);
bool __stdcall TDBTableGetProperties(long DBIndex,char*TableName,TtdbTableProperties&TableProperties);
long __stdcall TDBTableRecordAdd(long DBIndex,char*TableName,bool AllowExpand);
bool __stdcall TDBTableRecordChangeDeleted(long DBIndex,char*TableName,long RecNo,bool Deleted);
bool __stdcall TDBTableRecordDeleted(long DBIndex,char*TableName,long RecNo);
bool __stdcall TDBTableRecordRemove(long DBIndex,char*TableName,long RecNo);

TDBInit();
TDBDone();
