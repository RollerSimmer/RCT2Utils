i=0;

#ifdef PARSE_SIMPLIFIED
#define ll(a) \
	fprintf(o,"-- String #%02.2d - %s\r\n",i,a);\
	fprintf(o,"\"%s\";\r\n",ste[i].text)
#else
#define ll(a) fprintf(o,"%s=\"%s\";\r\n",a,ste[i].text)
#endif

while(i<RCT2__OBJDAT__STRING_TABLE__ENTRY__NUM_LANGUAGES)
{
	
	
	switch(ste[i].lang)
	{
		case LNG_UKENGLISH:
			ll("english_UK");
			break;
		case LNG_USENGLISH:
			ll("english_USA");
			break;
		case LNG_FRENCH:
			ll("francais");
			break;
		case LNG_DEUTCSH:
			ll("deutsch");
			break;
		case LNG_SPANISH:
			ll("espanol");
			break;
		case LNG_ITALIAN:
			ll("italiano");
			break;
		case LNG_DUTCH:
			ll("nederlands");
			break;
		case LNG_SVERIGE:
			ll("sverige");
			break;
		case LNG_KOREAN:
			ll("korean");
			break;
		case LNG_CHINESE1:
			ll("chinese");
			break;
		case LNG_CHINESE2:
			ll("chinese2");
			break;
		case LNG_PORTUGESE:
			ll("portugese");
			break;
		case BYTE(0xff):
			goto exit_while_stringTable;			
			break;
	};
	ste[i].lang;
	ste[i].text;
	++i;
}
exit_while_stringTable:

#undef ll
	
