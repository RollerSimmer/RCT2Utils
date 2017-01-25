#pragma once

#define WIN32_LEAN_AND_MEAN 
#include<windows.h>

int ReadResource(HMODULE hModule,char*type,int id,void*buf,int bufSz);
