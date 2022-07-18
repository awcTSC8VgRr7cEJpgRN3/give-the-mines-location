#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define max 33

struct ArrayMine{char mine;int color;};

void LetsDoThis(int Height,int Width,int Mine,ArrayMine Array[][max],int count)
{
	void LetsDigThisMain(int Height,int Width,int Mine,ArrayMine Array[][max]);
	
	if(count<Mine)
	{
		int x=rand()%Height;
		int y=rand()%Width;
		
		if(Array[x][y].mine==00)
		{
			Array[x][y].mine=42;
			LetsDoThis(Height,Width,Mine,Array,count+1);
		}
		else
		{
			LetsDoThis(Height,Width,Mine,Array,count);
		}
		
		return;
	}
	else
	{
		for(int i=0;i<Height;i++)
		{
			for(int j=0;j<Width;j++)
			{
				if((i+j)%2==0)
				{
					Array[i][j].color=255;
				}
				else
				{
					Array[i][j].color=0;
				}
			}
		}
	}
	
	LetsDigThisMain(Height,Width,Mine,Array);
	
	return;
}

void MinesPrinting(int Height,int Width,ArrayMine Array[][max])
{
	system("cls");
	
	for(int j=0;j<=Width;j++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		printf("%2d",j);
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
	printf("\n");
	
	for(int i=0;i<Height;i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		printf("%2d",i+1);
		
		for(int j=0;j<Width;j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Array[i][j].color);
			printf("%2c",Array[i][j].mine);
		}
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
		printf("\n");
	}
	
	return;
}

void LetsDigThisMain(int Height,int Width,int Mine,ArrayMine Array[][max])
{
	void LetsDigThisSub(int Height,int Width,int Mine,ArrayMine Array[][max],int x,int y);
	void MinesPrinting(int Height,int Width,ArrayMine Array[][max]);
	
	MinesPrinting(Height,Width,Array);
	
	int x,y,z=0;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("Enter the location of mines (type to 'XXYY') : ");
	scanf("%2d%2d",&y,&x);
	x--;
	y--;
	
	if(Array[x][y].mine==00)
	{
		LetsDigThisSub(Height,Width,Mine,Array,x,y);
		
		for(int i=0;i<Height;i++)
		{
			for(int j=0;j<Width;j++)
			{
				if(Array[i][j].color==0 || Array[i][j].color==255)
				{
					z++;
				}
			}
		}
		
		if(z==Mine)
		{
			for(int i=0;i<Height;i++)
			{
				for(int j=0;j<Width;j++)
				{
					if(Array[i][j].mine==42)
					{
						Array[i][j].color=224;
					}
				}
			}
			
			MinesPrinting(Height,Width,Array);
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			printf("YOU WIN");
		}
		else
		{
			LetsDigThisMain(Height,Width,Mine,Array);
		}
	}
	else if(Array[x][y].mine==42)
	{
		for(int i=0;i<Height;i++)
		{
			for(int j=0;j<Width;j++)
			{
				if((i+j)%2==0 && Array[i][j].mine==42)
				{
					Array[i][j].color=240;
				}
				else if((i+j)%2==1 && Array[i][j].mine==42)
				{
					Array[i][j].color=15;
				}
			}
		}
		
		Array[x][y].color=192;
		
		MinesPrinting(Height,Width,Array);
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
		printf("GAME OVER");
	}
	else
	{
		LetsDigThisMain(Height,Width,Mine,Array);
	}
	
	return;
}

void LetsDigThisSub(int Height,int Width,int Mine,ArrayMine Array[][max],int x,int y)
{
	void LetsDigThisMain(int Height,int Width,int Mine,ArrayMine Array[][max]);
	
	int f[8]={-1,-1,-1,0,0,1,1,1};
	int g[8]={-1,0,1,-1,1,-1,0,1};
	int h=0;
	
	for(int i=0;i<8;i++)
	{
		if(Array[x+f[i]][y+g[i]].mine==42 && x+f[i]>=0 && x+f[i]<Height && y+g[i]>=0 && y+g[i]<Width)
		{
			h++;
		}
	}
	
	if(h==0)
	{
		Array[x][y].mine=46;
		if((x+y)%2==0)
		{
			Array[x][y].color=240;
		}
		else
		{
			Array[x][y].color=15;
		}
		
		for(int i=0;i<8;i++)
		{
			if(Array[x+f[i]][y+g[i]].mine==00 && x+f[i]>=0 && x+f[i]<Height && y+g[i]>=0 && y+g[i]<Width)
			{
				LetsDigThisSub(Height,Width,Mine,Array,x+f[i],y+g[i]);
			}
		}
	}
	else
	{
		if((x+y)%2==0)
		{
			Array[x][y].color=240;
		}
		else
		{
			Array[x][y].color=15;
		}
		Array[x][y].mine=h+48;
	}
	
	return;
}

int main(void)
{
	int InputHeight,InputWidth,InputMine;
	ArrayMine InputArrayMine[max][max]={0};
	
	srand(time(NULL));
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("Enter height: ");
	scanf("%d",&InputHeight);
	printf("Enter width: ");
	scanf("%d",&InputWidth);
	printf("Enter the number of mines: ");
	scanf("%d",&InputMine);
	
	LetsDoThis(InputHeight,InputWidth,InputMine,InputArrayMine,0);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
	return 0;
}
