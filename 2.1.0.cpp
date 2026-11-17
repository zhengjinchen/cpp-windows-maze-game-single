#include <bits/stdc++.h>
#include <conio.h>
#include <Windows.h> 
using namespace std;
char a[30][30]; 
char a1[30][30];
void init_game();
void block(int x,int y){
    HANDLE   hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD   setps;
    setps.X = x;
    setps.Y = y;
    SetConsoleCursorPosition(hCon,setps);  
}
void printgz()
{
    cout<<"欢迎来到本迷宫游戏！"<<endl;
    cout<<"游戏说明：W(w)向上走，S(s)向下走，A(a)向左走，D(d)向右走。"<<endl;
    cout<<"符号标志：I代表你自己，E代表终点。"<<endl;
    cout<<"'F'+op：将某个方向的'#'改为'.'。"<<endl;
    cout<<"'-':把所有位置清空为'.'。"<<endl;
    cout<<"'F'+'Z'：自行探究。"<<endl;
    char op=getchar();
}
void printmap()
{
    for(int i=1;i<=25;i++)
    {
        for(int j=1;j<=25;j++){
            if(a1[i][j] != a[i][j]){
                block(j, i);
                printf("%c",a[i][j]);
                a1[i][j] = a[i][j];
            }
        }
    }
    block(0, 26);
    return;
}
void random_map()
{
    memset(a1, 0, sizeof(a1));
    for(int i=1;i<=25;i++)
    {
        a[i][1]='#';
        a[1][i]='#';
        a[25][i]='#';
        a[i][25]='#';
    }
    for(int i=2;i<=24;i++)
    {
        for(int j=2;j<=24;j++)
        {
            int m=rand()%20;
            if(m==1 || m==4 || m==5 || m==8 || m==14 || m==16 || m==17 ) a[i][j]='#';
            else a[i][j]='.';
        }
    }
    bool flag=false;
    for(int x=1;x<=25;x++)
    {
        for(int y=1;y<=25;y++)
        {
            if(a[x][y]=='.')
            {
                a[x][y]='I';
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
    flag=false;
    for(int x=25;x>=1;x--)
    {
        for(int y=25;y>=1;y--)
        {
            if(a[x][y]=='.')
            {
                a[x][y]='E';
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
}
void win()
{
    system("color F6");
    cout<<"\n\n\n\n\n\n             你赢了！\n             You win!!\n";
    cout<<"0:退出 1:再来一局";
    char ch=getch();
    if(ch=='0') exit(0);
    init_game();
}
void all_void()
{
	for(int i=1;i<=25;i++)
		for(int j=1;j<=25;j++)
			a[i][j]='.';
	return;
}
void fun()
{
	for(int i=1;i<=25;i++)
		for(int j=1;j<=25;j++)
			a[i][j]=rand()%26+97;
	return;
}
void game()
{
    bool flag=false;
    int i,j; 
    for(int x=1;x<=25;x++)
    {
        for(int y=1;y<=25;y++)
        {
            if(a[x][y]=='I')
            {
                i=x;
                j=y;
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
    while(1)
    {
        char ch;
        ch=getch();
        if(ch=='W' || ch=='w' && a[i-1][j]!='#')
        {
            a[i][j]='.';
            i--;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if(ch=='S' || ch=='s' && a[i+1][j]!='#')
        {
            a[i][j]='.';
            i++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if(ch=='A' || ch=='a' && a[i][j-1]!='#')
        {
            a[i][j]='.';
            j--;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if(ch=='D' || ch=='d' && a[i][j+1]!='#')
        {
            a[i][j]='.';
            j++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if(ch=='F' || ch=='f')
        {
            cout<<'F'<<' ';
            char opt;
            cin>>opt;
            if(opt=='W' || opt=='w') a[i-1][j]='.';
            if(opt=='S' || opt=='s') a[i+1][j]='.';
            if(opt=='A' || opt=='a') a[i][j-1]='.';
            if(opt=='D' || opt=='d') a[i][j+1]='.';
            if(opt=='Z' || opt=='z') fun();
        }
        if(ch=='-')
            for(int x=2;x<=24;x++)
                for(int y=2;y<=24;y++)
                    if(a[x][y]!='I' && a[x][y]!='E')
                        a[x][y]='.';
        if(ch=='C' || ch=='c') all_void();
        printmap();
    }
}
void init_game()
{
    system("cls");
    system("color 07");
    printgz();
    random_map();
    system("cls");
    printmap();
    game();
}
int main()
{
    srand(time(0));
    init_game();
    return 0;
}

