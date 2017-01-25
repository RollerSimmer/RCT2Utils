#include"MakeDatList.h"
#include<io.h>
#include<codeshortcuts.h>
#include<rct2lib.h>
#include<img256_lib.h>
#include<bmplib.h>

char*
operator~
(CString&s)
{
	return((char*)s.GetBuffer(0));
}

int GetNumFiles(CString&datMask)
{
	_finddata_t fd;
	long findHndl;
	int numFiles;
	char*path;
	int more;
	
	findHndl=_findfirst(path=~datMask,&fd);
	numFiles=0;

	if(findHndl!=-1)
	{
		++numFiles;
		while(!(more=_findnext(findHndl,&fd))) 
		{	++numFiles;	}
	}
	return(numFiles);
}


CreateCurBitmap
(	int i,OBJDAT_FILE&dat,
	CBitmap*pImg
)
{
	bool bitmapCreated;

	IMG_256 img;

	#define RESZ_HEIGHT 32

	dat.CopyImage(0,img,4);

	if(img.h>RESZ_HEIGHT)
	{
		#if 0
		img.ResizeToHeight(RESZ_HEIGHT);
		#endif
	}
	
	bitmapCreated=
		pImg->CreateBitmap(img.w,img.h,1,8,img.imgData);

	if(bitmapCreated)
	{
		

	}
	#undef id //dat.imageDirectory;
}

#define PREVIEWS__MAX_IMAGES 0x2000
//CBitmap prevImage;
CBitmap pImg[PREVIEWS__MAX_IMAGES];

OBJDAT_FILE dat;

MakeDatList
(	
	CImageList&imageList,
	CListCtrl&datList,
	CString&datFolder,
	CProgressCtrl&progressBar
)
{
	CString datMask,curDatNm;
	_finddata_t fd;
	int numFiles;
	int i;
	int findHndl;
	int more;
	char*path;
	bool bitmapCreated;
	bool listCreated;

	datMask=datFolder;
	datMask+="\\*.dat";
	numFiles=GetNumFiles(datMask);

	progressBar.SetRange32(0,numFiles);
	progressBar.SetPos(0);
	progressBar.SetStep(1);
	progressBar.UpdateWindow();


	listCreated=
	imageList.Create
	(	64,64,
		ILC_COLOR8, 
		0,numFiles 
	);

	findHndl=_findfirst(path=~datMask,&fd);

	i=0;

	if(findHndl!=-1)
	{
		do
		{	
			curDatNm=datFolder;
			curDatNm+="\\";
			curDatNm+=fd.name;

			dat.LoadObjDatFile(~curDatNm);

			pImg[0].DeleteObject();

			CreateCurBitmap(i,dat,&pImg[i]);
			

			imageList.Add(&pImg[i],(CBitmap*)NULL);
			
			++i;

			progressBar.StepIt();
			progressBar.UpdateWindow();

		}
		while(!(more=_findnext(findHndl,&fd)));

		datList.SetImageList(&imageList,LVSIL_NORMAL);

		

		for_i0(i,numFiles)
		{
			datList.DeleteItem(i);
			datList.InsertItem(LVIF_IMAGE,i,"DAT Name",0,0,i,0);
		}
	}

	progressBar.SetPos(0);
	progressBar.UpdateWindow();
}
