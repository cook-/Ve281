#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "queue.h"
#include "queue.C"

using namespace std;


struct points
{
	int x; //x direction 
	int y; //y direction
	int z; //level in z direction
	char types; //include six types
	int dis;
	char direction;
//	bool occupy; //check occupy
};

points* findpoint(char p, points**** arr, points* current,int size, int level)
{
	if (p=='n')
	{
		if(current->x-1<0) {
			return NULL;
		}else {
			return arr[current->z][current->x-1][current->y];
		}
	}
	else if (p=='s')
	{
		if(current->x+1>=size) {
			return NULL;
		}else {
			return arr[current->z][current->x+1][current->y];
		}
	}
	else if (p=='e')
	{
		if(current->y+1>=size) {
			return NULL;
		}else {
			return arr[current->z][current->x][current->y+1];
		}
	}
	else if (p=='w')
	{
		if(current->y-1<0) {
			return NULL;
		}else {
			return arr[current->z][current->x][current->y-1];
		}
	}
	else if (p=='^')
	{
		if(current->z+1>=level) {
			return NULL;
		}else {
			return arr[current->z+1][current->x][current->y];
		}
	}
	else if (p=='V')
	{
		if(current->z-1<0) {
			return NULL;
		}else {
			return arr[current->z-1][current->x][current->y];
		}
	}else {
		return NULL;
	}
}

int main (int argc, char* argv[])
{
//check error
	try {
		if (argc!=2) throw argc;
	}
	catch (int) {
		cout<<"Error: Missing arguments!"<<"\n"<<"Usage: ./p1 <grid-file>"<<endl;
		return 0;
	}
	string filename=argv[1];
	ifstream ifstr;
	ifstr.open(filename.c_str());
	try {
		if (ifstr==0) throw filename;
	}
	catch (string name) {
		cout<<"Error: Connot open file "<<name<<"!"<<endl;
		return 0;
	}

//declaration of main
	points* start=NULL;
	points* end=NULL;
	Queue<points> q;
	points* current=NULL;
	points* north=NULL;
	points* south=NULL;
	points* east=NULL;
	points* west=NULL;
	points* up=NULL;
	points* down=NULL;
	points* find=NULL;
	char n='n';
	char s='s';
	char e='e';
	char w='w';
	char u='^';
	char d='V';
	//int ch=0;

//input file
	string line;
	getline(ifstr,line);
	int size=atoi(line.c_str());
	getline(ifstr,line);
	int level=atoi(line.c_str());
	points**** arr=new points***[level];
//	cout<<size<<endl<<level<<endl;
	for (int i=0;i<level;i++)
	{
		arr[level-1-i]=new points**[size];
		for (int j=0;j<size;j++)
		{
			getline(ifstr,line);
			if (line[0]=='#')
			{
				getline(ifstr,line);
				while (line[0]=='#')
				{
					getline(ifstr,line);
				}
			}
			arr[level-1-i][j]=new points*[size];
			for (int k=0;k<size;k++)
			{
				arr[level-1-i][j][k]=new points;
				arr[level-1-i][j][k]->x=j;
				arr[level-1-i][j][k]->y=k;
				arr[level-1-i][j][k]->z=level-1-i;
				arr[level-1-i][j][k]->types=line[k];
				arr[level-1-i][j][k]->dis=-10;
				arr[level-1-i][j][k]->direction=' ';
//				cout<<arr[level-1-i][j][k]->types;
				if (line[k]=='S')
				{
					start=arr[level-1-i][j][k];
					start->dis=0;
					start->x=j;
					start->y=k;
					start->z=level-1-i;
					start->types='S';
					start->direction=' ';
				}
                /*
				if (line[k]=='D')
				{
					end=arr[level-1-i][j][k];
					end->x=j;
					end->y=k;
					end->z=level-1-i;
					end->types='D';
					end->direction='D';
				}
                */
			}
		}
	}

//check destination
//	assert(!((end==NULL)||(start==end)));

//establish the queue
	q.enqueue(start);
//	find=end;
	while ((!q.isEmpty())&&(q.front()->types != 'D'))
	{
		current=q.dequeue();
		north=findpoint(n,arr,current,size,level);
		south=findpoint(s,arr,current,size,level);
		east=findpoint(e,arr,current,size,level);
		west=findpoint(w,arr,current,size,level);
		up=findpoint(u,arr,current,size,level);
		down=findpoint(d,arr,current,size,level);
		if ((north!=NULL)&&(north->dis==-10)&&(north->types!='X'))
		{
			north->dis=current->dis+1;
			q.enqueue(north);
		}
		if ((south!=NULL)&&(south->dis==-10)&&(south->types!='X'))
		{
			south->dis=current->dis+1;
			q.enqueue(south);
		}
		if ((east!=NULL)&&(east->dis==-10)&&(east->types!='X'))
		{
			east->dis=current->dis+1;
			q.enqueue(east);
		}
		if ((west!=NULL)&&(west->dis==-10)&&(west->types!='X'))
		{
			west->dis=current->dis+1;
			q.enqueue(west);
		}
		if ((current->types=='^')&&(up!=NULL)&&(up->dis==-10)&&(up->types!='X'))
		{
			up->dis=current->dis+1;
			q.enqueue(up);
		}
		if ((current->types=='V')&&(down!=NULL)&&(down->dis==-10)&&(down->types!='X'))
		{
			down->dis=current->dis+1;
			q.enqueue(down);
		}
	}
	end = q.front();
	find = end;

//find the minimal path
	bool check=q.isEmpty();
	int path=end->dis;
	if (!check)
	{
		printf("Path found!\n");
		printf("The minimal distance is %d\n",path);
		printf("%d\n",size);
		printf("%d\n",level);
		//cout<<"Path found!"<<endl;
		//cout<<"The minimal distance is "<<path<<"."<<endl;
		//cout<<size<<endl;
		//cout<<level<<endl;
		while(find->dis!=0)
		{
			north=findpoint(n,arr,find,size,level);
			south=findpoint(s,arr,find,size,level);
			east=findpoint(e,arr,find,size,level);
			west=findpoint(w,arr,find,size,level);
			up=findpoint(u,arr,find,size,level);
			down=findpoint(d,arr,find,size,level);
			if ((north!=NULL)&&(north->dis==find->dis-1)&&(north->types!='X'))
			{
				find=north;
				north->direction='s';
			}
			if ((south!=NULL)&&(south->dis==find->dis-1)&&(south->types!='X'))
			{
				find=south;
				south->direction='n';
			}
			if ((east!=NULL)&&(east->dis==find->dis-1)&&(east->types!='X'))
			{
				find=east;
				east->direction='w';
			}
			if ((west!=NULL)&&(west->dis==find->dis-1)&&(west->types!='X'))
			{
				find=west;
				west->direction='e';
			}
			if ((up!=NULL)&&(up->dis==find->dis-1)&&(up->types=='V'))
			{
				find=up;
				up->direction='d';
			}
			if ((down!=NULL)&&(down->dis==find->dis-1)&&(down->types=='^'))
			{
				find=down;
				down->direction='u';
			}
		}
	}else {
		printf("No path found!\n");
	}

//cout the result
	int m;
	if (!check)
	{
		for (int i=0;i<level;i++)
		{
			m=level-i-1;
			printf("#level %d\n",m);
			for (int j=0;j<size;j++)
			{
				for (int k=0;k<size;k++)
				{
					if (arr[level-1-i][j][k]->types=='X') {
						printf("X");
					}else if (arr[level-1-i][j][k]->types=='D') {
						printf("D");
					}else if (arr[level-1-i][j][k]->types=='S') {
						printf("%c",arr[level-1-i][j][k]->direction);
					}else if (arr[level-1-i][j][k]->types==' ') {
						printf("%c",arr[level-1-i][j][k]->direction);
					}else if ((arr[level-1-i][j][k]->types=='^')&&(arr[level-1-i][j][k]->direction!=' ')) {
						printf("%c",arr[level-1-i][j][k]->direction);
					}else if ((arr[level-1-i][j][k]->types=='^')&&(arr[level-1-i][j][k]->direction==' ')) {
						printf("^");
					}else if ((arr[level-1-i][j][k]->types=='V')&&(arr[level-1-i][j][k]->direction!=' ')) {
						printf("%c",arr[level-1-i][j][k]->direction);
					}else if ((arr[level-1-i][j][k]->types=='V')&&(arr[level-1-i][j][k]->direction==' ')) {
						printf("V");
					}else {
					}
				}
				printf("\n");
			}
		}
	}

//delete
	for (int i=0;i<level;i++)
	{
		for (int j=0;j<size;j++)
		{
			for (int k=0;k<size;k++)
			{
				delete arr[level-1-i][j][k];
			}
			delete[] arr[level-1-i][j];
		}
		delete[] arr[level-1-i];
	}
	delete[] arr;

	if (!q.isEmpty())
	{
		while (!q.isEmpty())
		{
			q.dequeue();
		}
	}
}
