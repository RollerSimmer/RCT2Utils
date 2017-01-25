//messages.h

#ifndef _MESSAGES_
#define _MESSAGES_

int WriteRct2Message
(	char *msgString,short color,
	short icon,short month,short day
);			
int ClearAllMessages();
int CommandMessage(unsigned short cmd);
extern int cmdmsg(char* c);
int ShiftOutMessages();

#endif //_MESSAGES_