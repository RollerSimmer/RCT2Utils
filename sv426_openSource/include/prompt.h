#ifndef _PROMPT_H_
#define _PROMPT_H_

#define Prompt_YesNo(promptStr,captionStr) \
(	(MessageBox(NULL,promptStr,captionStr,MB_YESNO)==IDYES)?TRUE:FALSE	)
#define Prompt_OK(promptStr,captionStr) \
(	(MessageBox(NULL,promptStr,captionStr,MB_OK)==IDOK)?TRUE:FALSE	)

int Prompt_YesNo_FileOverwrite(char *filename,char *captionStr);

#endif //_PROMPT_H_

