//Tangram Search 
//陶都乐 1609853d-i011-0019 任佩之 1609853J-I011-0141 黄亮凡 1609853M-I011-0049
#include<iostream> 
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include<time.h>
using namespace std; 

int puzzle[8][8]={1};//代表目标状态的表	  
char map[24][24];//通过map的数据生成的字符图像,用于向用户展示，同时确认各格的归属

void show(); //用于展示图像状态的函数 
void initializegoal(int g);//根据用户选择的目标图形初始化图像 
int checkblock(int row,int col,int p);//用于检查对应格是否允许放置拼图 
void fillblock(int row,int col,int p);//在确定拼图可以放置之后，改变puzzle 
int placepuzzle(int num, int row, int col, int angle);//放置七巧板，需要参数为：七巧板编号（1-7），代表放置位置的两个坐标（1-8），放置角度（0-3）,如果失败，则返回值为0,成功则为1 
void remove(int t);//在某块拼图无法放下的情况下撤销上一步

int main(){
int t=1;
int g;
int g2; 
int i;
int step;//记录步骤数 
cout<<"  Tangram Automatic Search"<<endl; 
cout<<"Developer:陶都乐 1609853d-i011-0019 任佩之 1609853J-I011-0141 黄亮凡 1609853M-I011-0049"<<endl; 
cout<<"Tell me the convex figure you want to see (1-13)"<<endl;
cin>>g;
g2 = g;
initializegoal(g);
int r[7]={1,1,1,1,1,1,1};//记录各个拼图的纵坐标 
int c[7]={1,1,1,1,1,1,1};//记录各个拼图的横坐标 
int p[7]={0,0,0,0,0,0,0};//记录各个拼图的角度 
int s[7]={1,2,3,6,7,4,5};
float dur1,dur2;
clock_t start1,end1,start2,end2;
cout << "Depth first search:place as much as I can" << endl;//深度优先算法：尽可能多地放置拼图，若拼图无法放置则撤销上一步 
start1 = clock();
while(t<=7){//七块拼图循环 
if(placepuzzle(t,r[t],c[t],p[t])==1)
{
  step+=1; 
  t+=1;}
else//若失败 
{if(p[t]<3){//若可以尝试新的角度
 p[t]+=1;//尝试下一个角度 
	}
 else//角度已全部尝试
 {p[t]=0;//重置角度
   if(c[t]<8){//若可以将图像右移 
   c[t]+=1;//右移图像，再次尝试 
	  }
   else//右移已到尽头 
   {c[t]=1;//重置横坐标
   	if(r[t]<8){//若可以将图像上移 
 	r[t]+=1;//上移图像，再次尝试
		}
 	else//上移达到尽头 
 	{r[t]=1;//重置纵坐标
     t=t-1;//此拼图无法在当前状态下放置，回退到上一步
     p[t]+=1;
     remove(t);
 	} 
   } 
 } 
}
};
end1 = clock();
dur1 = (float)(end1 - start1);
show();
cout<<"After "<<step<<" steps, DFS got the goal"<<endl;
cout<<"time used(ms): "<<setprecision(10)<<dur1<<endl;
initializegoal(g2);
step=0;
t=0;
for(i=1;i<8;i++){
	r[i]=1;
	c[i]=1;
	p[i]=0;
}
cout << "Greedy search:always place the biggest puzzle" << endl;//贪心算法：优先放置面积更大的拼图 
start2 = clock();
while(t<=7){//七块拼图循环 
if(placepuzzle(s[t],r[t],c[t],p[t])==1)
{ step+=1;
  t+=1;
  //cout<<"step "<<step<<endl;
  //show();
  }
else//若失败 
{if(p[t]<3){//若可以尝试新的角度
 p[t]+=1;//尝试下一个角度 
	}
 else//角度已全部尝试
 {p[t]=0;//重置角度
   if(c[t]<8){//若可以将图像右移 
   c[t]+=1;//右移图像，再次尝试 
	  }
   else//右移已到尽头 
   {c[t]=1;//重置横坐标
   	if(r[t]<8){//若可以将图像上移 
 	r[t]+=1;//上移图像，再次尝试
		}
 	else//上移达到尽头 
 	{r[t]=1;//重置纵坐标
     t=t-1;//此拼图无法在当前状态下放置，回退到上一步
     p[t]+=1;
     remove(s[t]);
 	} 
   } 
 } 
}
};
end2 = clock();
dur2 = (float)(end2 - start2);
show();
cout<<"After "<<step<<" steps, Greedy got the goal"<<endl;
cout<<"time used(ms): "<<setprecision(10)<<dur2<<endl;
for (;;);
return 0;
}
void show(){//展示图形 

int i;
int j;
	for(i=24;i>0;i--)//输出map的图像 
	{   if((i+1)%3==0){
		cout<<(i+1)/3<<"  ";//垂直坐标轴
	    }
	    else
	    {
	    cout<<"   ";
		}
		for(j=1;j<25;j++)
		{cout<<map[i][j];
		 cout<<" ";
		 //cout<<i<<j;
		};
		cout<<"\n"; 
	};
	cout<<"     1     2     3     4     5     6     7     8"<<endl;//水平坐标轴 
}
void initializegoal(int g){
	int i;
	int j;
	switch(g){
		case 1 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=0;puzzle[4][3]=0;puzzle[4][4]=3;puzzle[4][5]=1;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=0;puzzle[3][2]=0;puzzle[3][3]=3;puzzle[3][4]=5;puzzle[3][5]=5;puzzle[3][6]=1;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=0;puzzle[2][2]=3;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=5;puzzle[2][6]=5;puzzle[2][7]=1;puzzle[2][8]=0;
		puzzle[1][1]=3;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=5;puzzle[1][6]=5;puzzle[1][7]=5;puzzle[1][8]=1;
		break;
		case 2 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=0;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=0;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=5;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=5;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 3 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=3;puzzle[6][5]=1;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=3;puzzle[5][4]=5;puzzle[5][5]=5;puzzle[5][6]=1;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=3;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=5;puzzle[4][6]=2;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=3;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=2;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=4;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=2;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=0;puzzle[1][2]=4;puzzle[1][3]=2;puzzle[1][4]=0;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 4 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=0;puzzle[4][3]=0;puzzle[4][4]=3;puzzle[4][5]=5;puzzle[4][6]=5;puzzle[4][7]=5;puzzle[4][8]=2;
        puzzle[3][1]=0;puzzle[3][2]=0;puzzle[3][3]=3;puzzle[3][4]=5;puzzle[3][5]=5;puzzle[3][6]=5;puzzle[3][7]=2;puzzle[3][8]=0;
        puzzle[2][1]=0;puzzle[2][2]=3;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=5;puzzle[2][6]=2;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=3;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=2;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 5 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=3;puzzle[6][3]=5;puzzle[6][4]=5;puzzle[6][5]=5;puzzle[6][6]=2;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=3;puzzle[5][2]=5;puzzle[5][3]=5;puzzle[5][4]=5;puzzle[5][5]=2;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=5;puzzle[4][4]=2;puzzle[4][5]=0;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=2;puzzle[3][4]=0;puzzle[3][5]=0;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=5;puzzle[2][2]=2;puzzle[2][3]=0;puzzle[2][4]=0;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=2;puzzle[1][2]=0;puzzle[1][3]=0;puzzle[1][4]=0;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 6 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=3;puzzle[7][4]=1;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=3;puzzle[6][3]=5;puzzle[6][4]=5;puzzle[6][5]=1;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=3;puzzle[5][2]=5;puzzle[5][3]=5;puzzle[5][4]=5;puzzle[5][5]=2;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=5;puzzle[4][4]=2;puzzle[4][5]=0;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=2;puzzle[3][4]=0;puzzle[3][5]=0;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=5;puzzle[2][2]=2;puzzle[2][3]=0;puzzle[2][4]=0;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=2;puzzle[1][2]=0;puzzle[1][3]=0;puzzle[1][4]=0;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 7 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=1;puzzle[4][4]=0;puzzle[4][5]=0;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=1;puzzle[3][5]=0;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=5;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=1;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=5;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=5;puzzle[1][6]=1;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 8 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=0;puzzle[4][3]=0;puzzle[4][4]=0;puzzle[4][5]=0;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=0;puzzle[3][2]=0;puzzle[3][3]=3;puzzle[3][4]=5;puzzle[3][5]=5;puzzle[3][6]=5;puzzle[3][7]=5;puzzle[3][8]=0;
        puzzle[2][1]=0;puzzle[2][2]=3;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=5;puzzle[2][6]=5;puzzle[2][7]=5;puzzle[2][8]=0;
		puzzle[1][1]=3;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=5;puzzle[1][6]=5;puzzle[1][7]=2;puzzle[1][8]=0;
		break;
		case 9 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=5;puzzle[5][2]=5;puzzle[5][3]=5;puzzle[5][4]=5;puzzle[5][5]=1;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=2;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=2;puzzle[3][5]=0;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=5;puzzle[2][2]=5;puzzle[2][3]=2;puzzle[2][4]=0;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=4;puzzle[1][2]=2;puzzle[1][3]=0;puzzle[1][4]=0;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 10 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=3;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=1;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=3;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=5;puzzle[3][6]=1;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=4;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=5;puzzle[2][6]=2;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=0;puzzle[1][2]=4;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=2;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 11 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=0;puzzle[5][4]=0;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=0;puzzle[4][3]=0;puzzle[4][4]=0;puzzle[4][5]=0;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=0;puzzle[3][2]=3;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=5;puzzle[3][6]=5;puzzle[3][7]=1;puzzle[3][8]=0;
        puzzle[2][1]=3;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=5;puzzle[2][6]=5;puzzle[2][7]=2;puzzle[2][8]=0;
		puzzle[1][1]=4;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=5;puzzle[1][6]=2;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 12 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=3;puzzle[5][2]=5;puzzle[5][3]=5;puzzle[5][4]=1;puzzle[5][5]=0;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=1;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=2;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=4;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=2;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=0;puzzle[1][2]=4;puzzle[1][3]=2;puzzle[1][4]=0;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 13 :
		puzzle[8][1]=0;puzzle[8][2]=0;puzzle[8][3]=0;puzzle[8][4]=0;puzzle[8][5]=0;puzzle[8][6]=0;puzzle[8][7]=0;puzzle[8][8]=0;
		puzzle[7][1]=0;puzzle[7][2]=0;puzzle[7][3]=0;puzzle[7][4]=0;puzzle[7][5]=0;puzzle[7][6]=0;puzzle[7][7]=0;puzzle[7][8]=0;
		puzzle[6][1]=0;puzzle[6][2]=0;puzzle[6][3]=0;puzzle[6][4]=0;puzzle[6][5]=0;puzzle[6][6]=0;puzzle[6][7]=0;puzzle[6][8]=0;
		puzzle[5][1]=0;puzzle[5][2]=0;puzzle[5][3]=3;puzzle[5][4]=5;puzzle[5][5]=5;puzzle[5][6]=0;puzzle[5][7]=0;puzzle[5][8]=0;
		puzzle[4][1]=0;puzzle[4][2]=3;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=5;puzzle[4][6]=0;puzzle[4][7]=0;puzzle[4][8]=0;
        puzzle[3][1]=3;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=2;puzzle[3][6]=0;puzzle[3][7]=0;puzzle[3][8]=0;
        puzzle[2][1]=5;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=2;puzzle[2][5]=0;puzzle[2][6]=0;puzzle[2][7]=0;puzzle[2][8]=0;
		puzzle[1][1]=5;puzzle[1][2]=5;puzzle[1][3]=2;puzzle[1][4]=0;puzzle[1][5]=0;puzzle[1][6]=0;puzzle[1][7]=0;puzzle[1][8]=0;
		break;
		case 14 ://仅仅用于测试placepuzzle的全满图形 
		puzzle[8][1]=5;puzzle[8][2]=5;puzzle[8][3]=5;puzzle[8][4]=5;puzzle[8][5]=5;puzzle[8][6]=5;puzzle[8][7]=5;puzzle[8][8]=5;
		puzzle[7][1]=5;puzzle[7][2]=5;puzzle[7][3]=5;puzzle[7][4]=5;puzzle[7][5]=5;puzzle[7][6]=5;puzzle[7][7]=5;puzzle[7][8]=5;
		puzzle[6][1]=5;puzzle[6][2]=5;puzzle[6][3]=5;puzzle[6][4]=5;puzzle[6][5]=5;puzzle[6][6]=5;puzzle[6][7]=5;puzzle[6][8]=5;
		puzzle[5][1]=5;puzzle[5][2]=5;puzzle[5][3]=5;puzzle[5][4]=5;puzzle[5][5]=5;puzzle[5][6]=5;puzzle[5][7]=5;puzzle[5][8]=5;
		puzzle[4][1]=5;puzzle[4][2]=5;puzzle[4][3]=5;puzzle[4][4]=5;puzzle[4][5]=5;puzzle[4][6]=5;puzzle[4][7]=5;puzzle[4][8]=5;
        puzzle[3][1]=5;puzzle[3][2]=5;puzzle[3][3]=5;puzzle[3][4]=5;puzzle[3][5]=5;puzzle[3][6]=5;puzzle[3][7]=5;puzzle[3][8]=5;
        puzzle[2][1]=5;puzzle[2][2]=5;puzzle[2][3]=5;puzzle[2][4]=5;puzzle[2][5]=5;puzzle[2][6]=5;puzzle[2][7]=5;puzzle[2][8]=5;
		puzzle[1][1]=5;puzzle[1][2]=5;puzzle[1][3]=5;puzzle[1][4]=5;puzzle[1][5]=5;puzzle[1][6]=5;puzzle[1][7]=5;puzzle[1][8]=5;
		break;
		default:
		cout<<"Convex figure not found"<<endl;
		break; 
	}
	for(i=9;i>0;i--)//首先使map获取puzzle中的数据，纵轴自下向上 
	{
		for(j=1;j<9;j++)//横轴自左向右 
		{if(puzzle[i][j]==0)//此格中无图形 
		 {map[3*i  ][3*j-2]=' ';map[3*i  ][3*j-1]=' ';map[3*i  ][3*j]=' ';
		  map[3*i-1][3*j-2]=' ';map[3*i-1][3*j-1]=' ';map[3*i-1][3*j]=' ';
		  map[3*i-2][3*j-2]=' ';map[3*i-2][3*j-1]=' ';map[3*i-2][3*j]=' ';
		 };
		 if(puzzle[i][j]==1)//此格的图形是占据左边与下边的直角三角形  
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]=' ';map[3*i  ][3*j]=' ';
		  map[3*i-1][3*j-2]='*';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]=' ';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]='*';map[3*i-2][3*j]='*';
		 };
		 if(puzzle[i][j]==2)//此格的图形是占据左边与上边的直角三角形 
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]='*';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]='*';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]=' ';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]=' ';map[3*i-2][3*j]=' ';
		 };
		 if(puzzle[i][j]==3)//此格的图形是占据右边与下边的直角三角形 
		 {map[3*i  ][3*j-2]=' ';map[3*i  ][3*j-1]=' ';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]=' ';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]='*';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]='*';map[3*i-2][3*j]='*';
		 };
		 if(puzzle[i][j]==4)//此格的图形是占据右边与上边的直角三角形 
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]='*';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]=' ';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]='*';
		  map[3*i-2][3*j-2]=' ';map[3*i-2][3*j-1]=' ';map[3*i-2][3*j]='*';
		 };
		 if(puzzle[i][j]==5)//此格的图形是充满全格的正方形 
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]='*';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]='*';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]='*';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]='*';map[3*i-2][3*j]='*';
		 };
//		 cout<<"puzzle["<<i<<"]["<<j<<"]:"<<puzzle[i][j]<<"\n";
//		 cout<<"map["<<3*i  <<"]["<<3*j-2<<"]:"<<map[3*i  ][3*j-2]<<"map["<<3*i  <<"]["<<3*j-1<<"]:"<<map[3*i  ][3*j-1]<<"map["<<3*i  <<"]["<<3*j<<"]:"<<map[3*i  ][3*j]<<"\n";
//		 cout<<"map["<<3*i-1<<"]["<<3*j-2<<"]:"<<map[3*i-1][3*j-2]<<"map["<<3*i-1<<"]["<<3*j-1<<"]:"<<map[3*i-1][3*j-1]<<"map["<<3*i-1<<"]["<<3*j<<"]:"<<map[3*i-1][3*j]<<"\n";
//		 cout<<"map["<<3*i-2<<"]["<<3*j-2<<"]:"<<map[3*i-2][3*j-2]<<"map["<<3*i-2<<"]["<<3*j-1<<"]:"<<map[3*i-2][3*j-1]<<"map["<<3*i-2<<"]["<<3*j<<"]:"<<map[3*i-2][3*j]<<"\n";
		};
	};
}
int checkblock(int row,int col,int p){
	switch(p){//确认检查的标准 
		case 1://检查是否容纳左下角三角形，确认此3*3方阵左下角为'*' 
		if(map[3*row-2][3*col-2]=='*'&&map[3*row-2][3*col]!=' '&&map[3*row][3*col-2]!=' ')
		return 1;
		else
		return 0;
		break;
		case 2://检查是否容纳左上角三角形，确认此3*3方阵左上角为'*' 
		if(map[3*row][3*col-2]=='*'&&map[3*row-2][3*col-2]!=' '&&map[3*row][3*col]!=' ')
		return 1;
		else
		return 0;
		break;
		case 3://右下角，同上 
		if(map[3*row-2][3*col]=='*'&&map[3*row][3*col]!=' '&&map[3*row-2][3*col-2]!=' ')
		return 1;
		else
		return 0;
		break;
		case 4://右上角 
		if(map[3*row][3*col]=='*'&&map[3*row][3*col-2]!=' '&&map[3*row-2][3*col]!=' ')
		return 1;
		else
		return 0;
		break;
		case 5:
		if(map[3*row-1][3*col-1]=='*'&&map[3*row][3*col]=='*'&&map[3*row][3*col-2]=='*'&&map[3*row-2][3*col]=='*'&&map[3*row-2][3*col-2]=='*')//确认全3*3方阵为空 
		return 1;
		else
		return 0;
		break;
	}
} 
void fillblock(int row,int col,int p,int num){
	char no = char(num+48);//用拼图的编号在map[][]中表示归属 
	switch(p){//确认填入的图形 
		case 1:
		  map[3*row  ][3*col-2]=no ;
		  map[3*row-1][3*col-2]=no ;map[3*row-1][3*col-1]=no ;
		  map[3*row-2][3*col-2]=no ;map[3*row-2][3*col-1]=no ;map[3*row-2][3*col]=no ;//改变显示图形map的状态
		break;
		case 2:
		  map[3*row  ][3*col-2]=no ;map[3*row  ][3*col-1]=no ;map[3*row  ][3*col]=no ;
		  map[3*row-1][3*col-2]=no ;map[3*row-1][3*col-1]=no ;
		  map[3*row-2][3*col-2]=no ;
		break;
		case 3://右下角
		  												      map[3*row  ][3*col]=no ;
		  							map[3*row-1][3*col-1]=no ;map[3*row-1][3*col]=no ;
		  map[3*row-2][3*col-2]=no ;map[3*row-2][3*col-1]=no ;map[3*row-2][3*col]=no ;
		break;
		case 4://右上角 
		  map[3*row  ][3*col-2]=no ;map[3*row  ][3*col-1]=no ;map[3*row  ][3*col]=no ;
                                    map[3*row-1][3*col-1]=no ;map[3*row-1][3*col]=no ;
                                                              map[3*row-2][3*col]=no ;
		break;
		case 5://全部 
		  map[3*row  ][3*col-2]=no ;map[3*row  ][3*col-1]=no ;map[3*row  ][3*col]=no ;
		  map[3*row-1][3*col-2]=no ;map[3*row-1][3*col-1]=no ;map[3*row-1][3*col]=no ;
		  map[3*row-2][3*col-2]=no ;map[3*row-2][3*col-1]=no ;map[3*row-2][3*col]=no ;
		break;
	}
}
int placepuzzle(int num, int row, int col, int angle){ 
 if (angle == 4){//角度溢出，失败 
 	return 0;
 }
 switch(num){//确认拼图编号 
 	case 1://占总面积1/4的大直角三角形部分，共2个，1与2各代表一个 
 		switch(angle){//确认角度 
 			case 0:
 			if(row+1>8||col+3>8){//图形向上或向右超出坐标系,则无法放置 
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,5)!=1||checkblock(row,col+2,5)!=1||checkblock(row,col+3,1)!=1||checkblock(row+1,col+1,3)!=1||checkblock(row+1,col+2,1)!=1){//确认拼图在该位置不与其他拼图重叠。 
			return 0;
			}
			fillblock(row,col,3,num);
			fillblock(row,col+1,5,num);
			fillblock(row,col+2,5,num);
			fillblock(row,col+3,1,num);
			fillblock(row+1,col+1,3,num);
			fillblock(row+1,col+2,1,num);
 			break;
 			case 1:
 			if(row+3>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,2)!=1||checkblock(row+1,col,5)!=1||checkblock(row+2,col,5)!=1||checkblock(row+3,col,1)!=1||checkblock(row+1,col+1,2)!=1||checkblock(row+2,col+1,1)!=1){
			return 0;
			}
			fillblock(row,col,2,num);
			fillblock(row+1,col,5,num);
			fillblock(row+2,col,5,num);
			fillblock(row+3,col,1,num);
			fillblock(row+1,col+1,2,num);
			fillblock(row+2,col+1,1,num);
 			break;
 			case 2:
 			if(row+1>8||col+3>8){
			return 0; 
			 } 
			if(checkblock(row,col+1,4)!=1||checkblock(row,col+2,2)!=1||checkblock(row+1,col,4)!=1||checkblock(row+1,col+1,5)!=1||checkblock(row+1,col+2,5)!=1||checkblock(row+1,col+3,2)!=1){ 
			return 0;
			}
			fillblock(row,col+1,4,num);
			fillblock(row,col+2,2,num);
			fillblock(row+1,col,4,num);
			fillblock(row+1,col+1,5,num);
			fillblock(row+1,col+2,5,num);
			fillblock(row+1,col+3,2,num);
 			break;
 			case 3:
 			if(row+3>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col+1,4)!=1||checkblock(row+1,col,4)!=1||checkblock(row+1,col+1,5)!=1||checkblock(row+2,col,3)!=1||checkblock(row+2,col+1,5)!=1||checkblock(row+3,col+1,3)!=1){
			return 0;
			}
			fillblock(row,col+1,4,num);
			fillblock(row+1,col,4,num);
			fillblock(row+1,col+1,5,num);
			fillblock(row+2,col,3,num);
			fillblock(row+2,col+1,5,num);
			fillblock(row+3,col+1,3,num);
 			break;
		 }
 	break;
 	case 2://与1相同的部分 
 		switch(angle){
 			case 0:
 			if(row+1>8||col+3>8){
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,5)!=1||checkblock(row,col+2,5)!=1||checkblock(row,col+3,1)!=1||checkblock(row+1,col+1,3)!=1||checkblock(row+1,col+2,1)!=1){ 
			return 0;
			}
			fillblock(row,col,3,num);
			fillblock(row,col+1,5,num);
			fillblock(row,col+2,5,num);
			fillblock(row,col+3,1,num);
			fillblock(row+1,col+1,3,num);
			fillblock(row+1,col+2,1,num);
 			break;
 			case 1:
 			if(row+3>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,2)!=1||checkblock(row+1,col,5)!=1||checkblock(row+2,col,5)!=1||checkblock(row+3,col,1)!=1||checkblock(row+1,col+1,2)!=1||checkblock(row+2,col+1,1)!=1){
			return 0;
			}
			fillblock(row,col,2,num);
			fillblock(row+1,col,5,num);
			fillblock(row+2,col,5,num);
			fillblock(row+3,col,1,num);
			fillblock(row+1,col+1,2,num);
			fillblock(row+2,col+1,1,num);
 			break;
 			case 2:
 			if(row+1>8||col+3>8){
			return 0; 
			 } 
			if(checkblock(row,col+1,4)!=1||checkblock(row,col+2,2)!=1||checkblock(row+1,col,4)!=1||checkblock(row+1,col+1,5)!=1||checkblock(row+1,col+2,5)!=1||checkblock(row+1,col+3,2)!=1){ 
			return 0;
			}
			fillblock(row,col+1,4,num);
			fillblock(row,col+2,2,num);
			fillblock(row+1,col,4,num);
			fillblock(row+1,col+1,5,num);
			fillblock(row+1,col+2,5,num);
			fillblock(row+1,col+3,2,num);
 			break;
 			case 3:
 			if(row+3>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col+1,4)!=1||checkblock(row+1,col,4)!=1||checkblock(row+1,col+1,5)!=1||checkblock(row+2,col,3)!=1||checkblock(row+2,col+1,5)!=1||checkblock(row+3,col+1,3)!=1){
			return 0;
			}
			fillblock(row,col+1,4,num);
			fillblock(row+1,col,4,num);
			fillblock(row+1,col+1,5,num);
			fillblock(row+2,col,3,num);
			fillblock(row+2,col+1,5,num);
			fillblock(row+3,col+1,3,num);
 			break;
		 }
 	break;
 	case 3: //占总面积1/8的中等直角三角形 
 		switch(angle){
 			case 0:
 			if(row+1>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,5)!=1||checkblock(row+1,col+1,3)!=1){
			return 0;
			}
			fillblock(row,col,3,num);
			fillblock(row,col+1,5,num);
			fillblock(row+1,col+1,3,num);
 			break;
 			case 1:
 			if(row+1>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,5)!=1||checkblock(row,col+1,1)!=1||checkblock(row+1,col,1)!=1){
			return 0;
			}
			fillblock(row,col,5,num);
			fillblock(row,col+1,1,num);
			fillblock(row+1,col,1,num);
 			break;
 			case 2:
 			if(row+1>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,2)!=1||checkblock(row+1,col+1,2)!=1||checkblock(row+1,col,5)!=1){
			return 0;
			}
			fillblock(row,col,2,num);
			fillblock(row+1,col,5,num);
			fillblock(row+1,col+1,2,num);
 			break;
 			case 3:
 			if(row+1>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col+1,4)!=1||checkblock(row+1,col,4)!=1||checkblock(row+1,col+1,5)!=1){
			return 0;
			}
			fillblock(row,col+1,4,num);
			fillblock(row+1,col,4,num);
			fillblock(row+1,col+1,5,num);
 			break;
		 }
 	break;
 	case 4://占总面积1/16的小直角三角形，共2个，4与5各代表一个 
 		switch(angle){
 			case 0:
 			if(row>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,1)!=1){
			return 0;
			}
			fillblock(row,col,3,num);
			fillblock(row,col+1,1,num);
 			break;
 			case 1:
 			if(row+1>8||col>8){
			return 0; 
			 } 
			if(checkblock(row,col,2)!=1||checkblock(row+1,col,1)!=1){
			return 0;
			}
			fillblock(row,col,2,num);
			fillblock(row+1,col,1,num);
 			break;
 			case 2:
 			if(row>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,4)!=1||checkblock(row,col+1,2)!=1){
			return 0;
			}
			fillblock(row,col,4,num);
			fillblock(row,col+1,2,num);
 			break;
 			case 3:
 			if(row+1>8||col>8){
			return 0; 
			 } 
			if(checkblock(row,col,4)!=1||checkblock(row+1,col,3)!=1){
			return 0;
			}
			fillblock(row,col,4,num);
			fillblock(row+1,col,3,num);
 			break;
		 }
 	break;
 	case 5://同4 
 		switch(angle){
 			case 0:
 			if(row>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,1)!=1){
			return 0;
			}
			fillblock(row,col,3,num);
			fillblock(row,col+1,1,num);
 			break;
 			case 1:
 			if(row+1>8||col>8){
			return 0; 
			 } 
			if(checkblock(row,col,2)!=1||checkblock(row+1,col,1)!=1){
			return 0;
			}
			fillblock(row,col,2,num);
			fillblock(row+1,col,1,num);
 			break;
 			case 2:
 			if(row>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,4)!=1||checkblock(row,col+1,2)!=1){
			return 0;
			}
			fillblock(row,col,4,num);
			fillblock(row,col+1,2,num);
 			break;
 			case 3:
 			if(row+1>8||col>8){
			return 0; 
			 } 
			if(checkblock(row,col,4)!=1||checkblock(row+1,col,3)!=1){
			return 0;
			}
			fillblock(row,col,4,num);
			fillblock(row+1,col,3,num);
 			break;
		 }
 	break;
 	case 6://七巧板中的正方形部分，在每次旋转90°的情况下，几何性质并不会改变，所以不需要switch(angle) 
 		if(row+1>8||col+1>8){
			return 0; 
			 } 
			if(checkblock(row,col,4)!=1||checkblock(row,col+1,2)!=1||checkblock(row+1,col,3)!=1||checkblock(row+1,col+1,1)!=1){
			return 0;
			}
			fillblock(row,col,4,num);
			fillblock(row,col+1,2,num);
			fillblock(row+1,col,3,num);
			fillblock(row+1,col+1,1,num);
 	break;
 	case 7://七巧板中的平行四边形部分，旋转90°与270°相同，0°与180°相同 
 		switch(angle%2){
 			case 0:
 			if(row>8||col+2>8){
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,5)!=1||checkblock(row,col+2,2)!=1){
			return 0;
			}
			fillblock(row,col,3,num);
			fillblock(row,col+1,5,num);
			fillblock(row,col+2,2,num);
 			break;
 			case 1:
 			if(row+2>8||col>8){
			return 0; 
			 } 
			if(checkblock(row,col,4)!=1||checkblock(row+1,col,5)!=1||checkblock(row+2,col,1)!=1){
			return 0;
			}
			fillblock(row,col,4,num);
			fillblock(row+1,col,5,num);
			fillblock(row+2,col,1,num);
 			break; 
		 }
 	break;
 } 
	return 1;
} 
void remove(int t){ 
	int i;
	int j;
	int m;
	int n; 
	char c;
	for(i=1;i<25;i++)//使用循环移除属于上一块拼图的全部痕迹，但要注意，由于每格使用3*3的大小，要注意互补三角形情况下的对角线的交接问题 
	{char no = char(t+48);//将int类型的t转换成对应的char形式 
	 for(j=1;j<25;j++){
	 	if(map[i][j]==no){//找到要撤销的拼图在map中的部分
		 if(i%3==1&&j%3==1){//找到位于3*3方阵左下角的待替换点 
		 if(map[i+1][j+1]==no){//待撤销拼图控制了对角线，寻找可接管对角线的拼图 
		  if(map[i+2][j]!=no&&map[i+2][j]!=' '&&map[i+2][j]!='*') {//待撤销图形是右下三角，在左上找到可接管拼图 
			c=map[i+2][j];
			map[i][j]=c;map[i+1][j+1]=c;map[i+2][j+2]=c;//将左下至右上的对角线交接 
		  }
		  else if(map[i][j+2]!=no&&map[i][j+2]!=' '&&map[i][j+2]!='*') {//待撤销图形是左上三角，在右下找到可接管拼图 
			c=map[i][j+2];
			map[i][j]=c;map[i+1][j+1]=c;map[i+2][j+2]=c;//将左下至右上的对角线交接 
		  } 
		  else if(map[i+2][j+2]!=no&&map[i+2][j+2]!=' '&&map[i+2][j+2]!='*'){//待撤销图形是左下三角，在右上找到可接管拼图 
		  	c=map[i+2][j+2];
			map[i+2][j]=c;map[i+1][j+1]=c;map[i][j+2]=c;//将左上至右下的对角线交接 
		  }
		 }
		 for(m=0;m<3;m++){//此时已不存在未交接的对角线，将该3*3方阵的全部待移除格替换成待填充格  
			for(n=0;n<3;n++){
				if(map[i+m][j+n]==no){
					map[i+m][j+n]='*';
						} 
					};
				}; 
			}
		 else if(j%3==0&&i%3==1){//待撤销图形是控制了对角线的右上三角
		 if(map[i][j-2]!=no&&map[i][j-2]!=' '&&map[i][j-2]!='*'){//在左下找到可接管拼图 
			c=map[i][j-2];
			map[i+2][j-2]=c;map[i+1][j-1]=c;map[i][j]=c;//交接左上到右下的对角线			 
		 		}
			for(m=0;m<3;m++){//将该3*3方阵的全部待移除格替换成待填充格  
			for(n=2;n>=0;n--){
				if(map[i+m][j-n]==no){
					map[i+m][j-n]='*';
						} 
					};
				}; 
		 	}
		 else //其他未控制对角线的情况 
		 {
		    for(m=0;m<3;m++){ 
			for(n=0;n<3;n++){
				if(map[(i/3)*3+m][(j/3)*3+n]==no){
					map[(i/3)*3+m][(j/3)*3+n]='*';
						} 
					};
				}; 
		 	
		 }
		 }
			
		};
	};
} 
