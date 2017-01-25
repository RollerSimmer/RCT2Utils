#ifndef _TERRBMP_
#define _TERRBMP_

#include <windows.h>

int LoadTerrainBMP(HWND hwnd,HINSTANCE hinstance);
int SaveTerrainBMP(HWND hwnd,HINSTANCE hinstance);
int GenerateRandomTerrain(int avgheight,int incline,int variation);

#endif