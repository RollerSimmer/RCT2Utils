#ifndef _PARRKSTATUS_
#define _PARRKSTATUS_

int IncDate(short dayInc,short monthInc,short yearInc);
int SetDate(short day,short month,short year);
int GetDate(short *day,short *month,short *year);
int SetCurrentAttendance(WORD attendance);
WORD GetCurrentAttendance();
CountRides();
CountMapData();
CountSprites();

#endif //_PARRKSTATUS_

