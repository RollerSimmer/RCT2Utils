#pragma once

#define C_STRING_OPS__H

char*operator~(CString s)
{	return(s.GetBuffer(0));	}


