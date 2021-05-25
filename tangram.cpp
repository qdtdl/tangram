//Tangram Search 
//�ն��� 1609853d-i011-0019 ����֮ 1609853J-I011-0141 ������ 1609853M-I011-0049
#include<iostream> 
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include<time.h>
using namespace std; 

int puzzle[8][8]={1};//����Ŀ��״̬�ı�	  
char map[24][24];//ͨ��map���������ɵ��ַ�ͼ��,�������û�չʾ��ͬʱȷ�ϸ���Ĺ���

void show(); //����չʾͼ��״̬�ĺ��� 
void initializegoal(int g);//�����û�ѡ���Ŀ��ͼ�γ�ʼ��ͼ�� 
int checkblock(int row,int col,int p);//���ڼ���Ӧ���Ƿ��������ƴͼ 
void fillblock(int row,int col,int p);//��ȷ��ƴͼ���Է���֮�󣬸ı�puzzle 
int placepuzzle(int num, int row, int col, int angle);//�������ɰ壬��Ҫ����Ϊ�����ɰ��ţ�1-7�����������λ�õ��������꣨1-8�������ýǶȣ�0-3��,���ʧ�ܣ��򷵻�ֵΪ0,�ɹ���Ϊ1 
void remove(int t);//��ĳ��ƴͼ�޷����µ�����³�����һ��

int main(){
int t=1;
int g;
int g2; 
int i;
int step;//��¼������ 
cout<<"  Tangram Automatic Search"<<endl; 
cout<<"Developer:�ն��� 1609853d-i011-0019 ����֮ 1609853J-I011-0141 ������ 1609853M-I011-0049"<<endl; 
cout<<"Tell me the convex figure you want to see (1-13)"<<endl;
cin>>g;
g2 = g;
initializegoal(g);
int r[7]={1,1,1,1,1,1,1};//��¼����ƴͼ�������� 
int c[7]={1,1,1,1,1,1,1};//��¼����ƴͼ�ĺ����� 
int p[7]={0,0,0,0,0,0,0};//��¼����ƴͼ�ĽǶ� 
int s[7]={1,2,3,6,7,4,5};
float dur1,dur2;
clock_t start1,end1,start2,end2;
cout << "Depth first search:place as much as I can" << endl;//��������㷨�������ܶ�ط���ƴͼ����ƴͼ�޷�����������һ�� 
start1 = clock();
while(t<=7){//�߿�ƴͼѭ�� 
if(placepuzzle(t,r[t],c[t],p[t])==1)
{
  step+=1; 
  t+=1;}
else//��ʧ�� 
{if(p[t]<3){//�����Գ����µĽǶ�
 p[t]+=1;//������һ���Ƕ� 
	}
 else//�Ƕ���ȫ������
 {p[t]=0;//���ýǶ�
   if(c[t]<8){//�����Խ�ͼ������ 
   c[t]+=1;//����ͼ���ٴγ��� 
	  }
   else//�����ѵ���ͷ 
   {c[t]=1;//���ú�����
   	if(r[t]<8){//�����Խ�ͼ������ 
 	r[t]+=1;//����ͼ���ٴγ���
		}
 	else//���ƴﵽ��ͷ 
 	{r[t]=1;//����������
     t=t-1;//��ƴͼ�޷��ڵ�ǰ״̬�·��ã����˵���һ��
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
cout << "Greedy search:always place the biggest puzzle" << endl;//̰���㷨�����ȷ�����������ƴͼ 
start2 = clock();
while(t<=7){//�߿�ƴͼѭ�� 
if(placepuzzle(s[t],r[t],c[t],p[t])==1)
{ step+=1;
  t+=1;
  //cout<<"step "<<step<<endl;
  //show();
  }
else//��ʧ�� 
{if(p[t]<3){//�����Գ����µĽǶ�
 p[t]+=1;//������һ���Ƕ� 
	}
 else//�Ƕ���ȫ������
 {p[t]=0;//���ýǶ�
   if(c[t]<8){//�����Խ�ͼ������ 
   c[t]+=1;//����ͼ���ٴγ��� 
	  }
   else//�����ѵ���ͷ 
   {c[t]=1;//���ú�����
   	if(r[t]<8){//�����Խ�ͼ������ 
 	r[t]+=1;//����ͼ���ٴγ���
		}
 	else//���ƴﵽ��ͷ 
 	{r[t]=1;//����������
     t=t-1;//��ƴͼ�޷��ڵ�ǰ״̬�·��ã����˵���һ��
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
void show(){//չʾͼ�� 

int i;
int j;
	for(i=24;i>0;i--)//���map��ͼ�� 
	{   if((i+1)%3==0){
		cout<<(i+1)/3<<"  ";//��ֱ������
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
	cout<<"     1     2     3     4     5     6     7     8"<<endl;//ˮƽ������ 
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
		case 14 ://�������ڲ���placepuzzle��ȫ��ͼ�� 
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
	for(i=9;i>0;i--)//����ʹmap��ȡpuzzle�е����ݣ������������� 
	{
		for(j=1;j<9;j++)//������������ 
		{if(puzzle[i][j]==0)//�˸�����ͼ�� 
		 {map[3*i  ][3*j-2]=' ';map[3*i  ][3*j-1]=' ';map[3*i  ][3*j]=' ';
		  map[3*i-1][3*j-2]=' ';map[3*i-1][3*j-1]=' ';map[3*i-1][3*j]=' ';
		  map[3*i-2][3*j-2]=' ';map[3*i-2][3*j-1]=' ';map[3*i-2][3*j]=' ';
		 };
		 if(puzzle[i][j]==1)//�˸��ͼ����ռ��������±ߵ�ֱ��������  
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]=' ';map[3*i  ][3*j]=' ';
		  map[3*i-1][3*j-2]='*';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]=' ';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]='*';map[3*i-2][3*j]='*';
		 };
		 if(puzzle[i][j]==2)//�˸��ͼ����ռ��������ϱߵ�ֱ�������� 
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]='*';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]='*';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]=' ';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]=' ';map[3*i-2][3*j]=' ';
		 };
		 if(puzzle[i][j]==3)//�˸��ͼ����ռ���ұ����±ߵ�ֱ�������� 
		 {map[3*i  ][3*j-2]=' ';map[3*i  ][3*j-1]=' ';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]=' ';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]='*';
		  map[3*i-2][3*j-2]='*';map[3*i-2][3*j-1]='*';map[3*i-2][3*j]='*';
		 };
		 if(puzzle[i][j]==4)//�˸��ͼ����ռ���ұ����ϱߵ�ֱ�������� 
		 {map[3*i  ][3*j-2]='*';map[3*i  ][3*j-1]='*';map[3*i  ][3*j]='*';
		  map[3*i-1][3*j-2]=' ';map[3*i-1][3*j-1]='*';map[3*i-1][3*j]='*';
		  map[3*i-2][3*j-2]=' ';map[3*i-2][3*j-1]=' ';map[3*i-2][3*j]='*';
		 };
		 if(puzzle[i][j]==5)//�˸��ͼ���ǳ���ȫ��������� 
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
	switch(p){//ȷ�ϼ��ı�׼ 
		case 1://����Ƿ��������½������Σ�ȷ�ϴ�3*3�������½�Ϊ'*' 
		if(map[3*row-2][3*col-2]=='*'&&map[3*row-2][3*col]!=' '&&map[3*row][3*col-2]!=' ')
		return 1;
		else
		return 0;
		break;
		case 2://����Ƿ��������Ͻ������Σ�ȷ�ϴ�3*3�������Ͻ�Ϊ'*' 
		if(map[3*row][3*col-2]=='*'&&map[3*row-2][3*col-2]!=' '&&map[3*row][3*col]!=' ')
		return 1;
		else
		return 0;
		break;
		case 3://���½ǣ�ͬ�� 
		if(map[3*row-2][3*col]=='*'&&map[3*row][3*col]!=' '&&map[3*row-2][3*col-2]!=' ')
		return 1;
		else
		return 0;
		break;
		case 4://���Ͻ� 
		if(map[3*row][3*col]=='*'&&map[3*row][3*col-2]!=' '&&map[3*row-2][3*col]!=' ')
		return 1;
		else
		return 0;
		break;
		case 5:
		if(map[3*row-1][3*col-1]=='*'&&map[3*row][3*col]=='*'&&map[3*row][3*col-2]=='*'&&map[3*row-2][3*col]=='*'&&map[3*row-2][3*col-2]=='*')//ȷ��ȫ3*3����Ϊ�� 
		return 1;
		else
		return 0;
		break;
	}
} 
void fillblock(int row,int col,int p,int num){
	char no = char(num+48);//��ƴͼ�ı����map[][]�б�ʾ���� 
	switch(p){//ȷ�������ͼ�� 
		case 1:
		  map[3*row  ][3*col-2]=no ;
		  map[3*row-1][3*col-2]=no ;map[3*row-1][3*col-1]=no ;
		  map[3*row-2][3*col-2]=no ;map[3*row-2][3*col-1]=no ;map[3*row-2][3*col]=no ;//�ı���ʾͼ��map��״̬
		break;
		case 2:
		  map[3*row  ][3*col-2]=no ;map[3*row  ][3*col-1]=no ;map[3*row  ][3*col]=no ;
		  map[3*row-1][3*col-2]=no ;map[3*row-1][3*col-1]=no ;
		  map[3*row-2][3*col-2]=no ;
		break;
		case 3://���½�
		  												      map[3*row  ][3*col]=no ;
		  							map[3*row-1][3*col-1]=no ;map[3*row-1][3*col]=no ;
		  map[3*row-2][3*col-2]=no ;map[3*row-2][3*col-1]=no ;map[3*row-2][3*col]=no ;
		break;
		case 4://���Ͻ� 
		  map[3*row  ][3*col-2]=no ;map[3*row  ][3*col-1]=no ;map[3*row  ][3*col]=no ;
                                    map[3*row-1][3*col-1]=no ;map[3*row-1][3*col]=no ;
                                                              map[3*row-2][3*col]=no ;
		break;
		case 5://ȫ�� 
		  map[3*row  ][3*col-2]=no ;map[3*row  ][3*col-1]=no ;map[3*row  ][3*col]=no ;
		  map[3*row-1][3*col-2]=no ;map[3*row-1][3*col-1]=no ;map[3*row-1][3*col]=no ;
		  map[3*row-2][3*col-2]=no ;map[3*row-2][3*col-1]=no ;map[3*row-2][3*col]=no ;
		break;
	}
}
int placepuzzle(int num, int row, int col, int angle){ 
 if (angle == 4){//�Ƕ������ʧ�� 
 	return 0;
 }
 switch(num){//ȷ��ƴͼ��� 
 	case 1://ռ�����1/4�Ĵ�ֱ�������β��֣���2����1��2������һ�� 
 		switch(angle){//ȷ�ϽǶ� 
 			case 0:
 			if(row+1>8||col+3>8){//ͼ�����ϻ����ҳ�������ϵ,���޷����� 
			return 0; 
			 } 
			if(checkblock(row,col,3)!=1||checkblock(row,col+1,5)!=1||checkblock(row,col+2,5)!=1||checkblock(row,col+3,1)!=1||checkblock(row+1,col+1,3)!=1||checkblock(row+1,col+2,1)!=1){//ȷ��ƴͼ�ڸ�λ�ò�������ƴͼ�ص��� 
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
 	case 2://��1��ͬ�Ĳ��� 
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
 	case 3: //ռ�����1/8���е�ֱ�������� 
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
 	case 4://ռ�����1/16��Сֱ�������Σ���2����4��5������һ�� 
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
 	case 5://ͬ4 
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
 	case 6://���ɰ��е������β��֣���ÿ����ת90�������£��������ʲ�����ı䣬���Բ���Ҫswitch(angle) 
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
 	case 7://���ɰ��е�ƽ���ı��β��֣���ת90����270����ͬ��0����180����ͬ 
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
	for(i=1;i<25;i++)//ʹ��ѭ���Ƴ�������һ��ƴͼ��ȫ���ۼ�����Ҫע�⣬����ÿ��ʹ��3*3�Ĵ�С��Ҫע�⻥������������µĶԽ��ߵĽ������� 
	{char no = char(t+48);//��int���͵�tת���ɶ�Ӧ��char��ʽ 
	 for(j=1;j<25;j++){
	 	if(map[i][j]==no){//�ҵ�Ҫ������ƴͼ��map�еĲ���
		 if(i%3==1&&j%3==1){//�ҵ�λ��3*3�������½ǵĴ��滻�� 
		 if(map[i+1][j+1]==no){//������ƴͼ�����˶Խ��ߣ�Ѱ�ҿɽӹܶԽ��ߵ�ƴͼ 
		  if(map[i+2][j]!=no&&map[i+2][j]!=' '&&map[i+2][j]!='*') {//������ͼ�����������ǣ��������ҵ��ɽӹ�ƴͼ 
			c=map[i+2][j];
			map[i][j]=c;map[i+1][j+1]=c;map[i+2][j+2]=c;//�����������ϵĶԽ��߽��� 
		  }
		  else if(map[i][j+2]!=no&&map[i][j+2]!=' '&&map[i][j+2]!='*') {//������ͼ�����������ǣ��������ҵ��ɽӹ�ƴͼ 
			c=map[i][j+2];
			map[i][j]=c;map[i+1][j+1]=c;map[i+2][j+2]=c;//�����������ϵĶԽ��߽��� 
		  } 
		  else if(map[i+2][j+2]!=no&&map[i+2][j+2]!=' '&&map[i+2][j+2]!='*'){//������ͼ�����������ǣ��������ҵ��ɽӹ�ƴͼ 
		  	c=map[i+2][j+2];
			map[i+2][j]=c;map[i+1][j+1]=c;map[i][j+2]=c;//�����������µĶԽ��߽��� 
		  }
		 }
		 for(m=0;m<3;m++){//��ʱ�Ѳ�����δ���ӵĶԽ��ߣ�����3*3�����ȫ�����Ƴ����滻�ɴ�����  
			for(n=0;n<3;n++){
				if(map[i+m][j+n]==no){
					map[i+m][j+n]='*';
						} 
					};
				}; 
			}
		 else if(j%3==0&&i%3==1){//������ͼ���ǿ����˶Խ��ߵ���������
		 if(map[i][j-2]!=no&&map[i][j-2]!=' '&&map[i][j-2]!='*'){//�������ҵ��ɽӹ�ƴͼ 
			c=map[i][j-2];
			map[i+2][j-2]=c;map[i+1][j-1]=c;map[i][j]=c;//�������ϵ����µĶԽ���			 
		 		}
			for(m=0;m<3;m++){//����3*3�����ȫ�����Ƴ����滻�ɴ�����  
			for(n=2;n>=0;n--){
				if(map[i+m][j-n]==no){
					map[i+m][j-n]='*';
						} 
					};
				}; 
		 	}
		 else //����δ���ƶԽ��ߵ���� 
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
