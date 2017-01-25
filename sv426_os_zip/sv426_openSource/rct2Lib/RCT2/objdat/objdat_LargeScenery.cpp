#define OBJDAT_ALL__CPP

#include"../rct2.h"
#include"objdat.h"
#include<codeshortcuts.h>

enum{I=0,J=1};

dllPort 
OBJDAT_FILE::
SortLScenTiles()
{
	int i,j,k,jTileCount;
	struct{union{DWORD absCol;struct{WORD col,row;};};}
		ac[2]; 

	WORD imgI[2];
	DATGRAPHINFOSTRUCT
		tmpImgDir[4],*id;
	#define szId (sz(tmpImgDir))

	LARGE_SCENERY__POS_STRUCT*tp[2],tmpPos;
	#define szTp (sz(tmpPos))

	id=imageDirectory;

	GetNumTiles();
	if(numTiles>1)
	{
		for_i0(i,numTiles-1)
		{
		jTileCount=numTiles-(i+1);	
		tp[I]=&optional.largeScenery.tilePos[i];
		for_i_base(j,i+1,jTileCount)
		{
			tp[J]=&optional.largeScenery.tilePos[j];
			for_i0(k,2)
			{	
				ac[k].col=tp[k]->x;
				ac[k].row=tp[k]->y;
			}
			if(ac[J].absCol<ac[I].absCol)
			{
				imgI[I]=i*4+4;
				imgI[J]=j*4+4;

				memcpy(&tmpImgDir,&id[imgI[I]],szId);
				memcpy(&id[imgI[I]],&id[imgI[J]],szId);
				memcpy(&id[imgI[J]],&tmpImgDir,szId);

				memcpy(&tmpPos,tp[I],szTp);
				memcpy(tp[I],tp[J],szTp);
				memcpy(tp[J],&tmpPos,szTp);
			}
		}
		}
	}




	

}

dllPort 
GetTileCenterXYZ
(	WORD view,long&x,long&y,long&z,
	WORD numCols,WORD numRows,
	WORD col,WORD row,WORD baseHeight,
	WORD imgWidth,WORD imgHeight
)
{
	//WORD col,row;
	WORD diagSpan,baseTop_y;
	WORD imgHeight_Flip,baseTop_x;
			
	imgWidth=(diagSpan=__max(numCols,numRows))*64;
	imgHeight_Flip=diagSpan*32;
	baseTop_y=imgHeight-imgHeight_Flip;

	switch(view)
	{
	case VIEW_SE:
		isoOrigin.Set
		(imgWidth/2,baseTop_y+TILE_YSTEP);
		break;
	case VIEW_NE:
		isoOrigin.Set
		(imgWidth-TILE_XSTEP,baseTop_y+imgHeight_Flip/2);
		break;
	case VIEW_NW:
		isoOrigin.Set
		(imgWidth/2,imgHeight-TILE_YSTEP);
		break;
	case VIEW_SW:
		isoOrigin.Set
		(TILE_XSTEP,baseTop_y+imgHeight_Flip/2);
		break;
	}
	//col=(i%numCols);
	//row=(i/numCols)%numRows;

	isoOrigin+=isoColInc[view]*col;
	isoOrigin+=isoRowInc[view]*row;
	z=isoOrigin.y;
	isoOrigin.y-=baseHeight;
	isoOrigin.y-=TILE_YSTEP;

	x=isoOrigin.x%imgWidth;
	y=isoOrigin.y%imgHeight;
};  


dllPort 
TranslatePos
(	WORD view,short&retCol,short&retRow,
	WORD numCols,WORD numRows,
	WORD col,WORD row
)
{
	//WORD col,row;
	WORD diagSpan,baseTop_y;
	WORD imgHeight_Flip,baseTop_x;
	WORD tileSpan=__max(numCols,numRows),edgeTile=tileSpan-1;


	switch(view)
	{
	case VIEW_SE:
		rotOrigin.Set(0,0);
		break;
	case VIEW_NE:
		rotOrigin.Set(edgeTile,0);
		break;
	case VIEW_NW:
		rotOrigin.Set(edgeTile,edgeTile);
		break;
	case VIEW_SW:
		rotOrigin.Set(0,edgeTile);
		break;
	}
	//col=(i%numCols);
	//row=(i/numCols)%numRows;

	rotOrigin+=rotColInc[view]*col;
	rotOrigin+=rotRowInc[view]*row;

	retCol=rotOrigin.x%tileSpan;
	retRow=rotOrigin.y%tileSpan;
}

dllPort 
TranslatePos
(	WORD view,ISOMETRIC_TILE_VECTOR&pos,
	WORD numCols,WORD numRows,
	WORD col,WORD row
)
{
	//pos.Set(col,row);
	TranslatePos
	(	view,pos.x,pos.y,
		numCols,numRows,
		col,row
	);
}
