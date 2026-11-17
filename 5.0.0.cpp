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
bool vis[30][30];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1}; 
void dfs(int x,int y)
{
    for(int i=0;i<4;i++)
    {
        int curx=x+dx[i];
        int cury=y+dy[i];
        if(curx>1 && cury>1 && curx<25 && cury<25 && a[curx][cury]!='#' && !vis[curx][cury])
        {
            vis[curx][cury]=true; 
            dfs(curx,cury);
        }
    }
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
void PRINT_LAST();
void win()
{
    system("color F6");
    cout<<"\n\n\n\n\n\n             你赢了！\n             You win!!\n";
    Sleep(2000);
    PRINT_LAST();
    cout<<"您的路线：\n";
    for(int i=1;i<=25;i++,cout<<endl)
    	for(int j=1;j<=25;j++)
    		cout<<a[i][j];
    cout<<"0:退出 1:再来一局";
    char ch=getch();
    if(ch=='0') exit(0);
    init_game();
}
void all_void()
{
    for(int i=1;i<=25;i++)
        for(int j=1;j<=25;j++)
            if(a[i][j]!='I')
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
bool LS[35][35];
void PRINT_LAST()
{
	for(int i=1;i<=25;i++)
	{
		for(int j=1;j<=25;j++)
		{
			if(LS[i][j])
			{
				if(LS[i-1][j]) a[i][j]='^';
				if(LS[i][j-1]) a[i][j]='<';
				if(LS[i][j+1]) a[i][j]='>';
				if(LS[i+1][j]) a[i][j]='V';
				LS[i][j]=0;
			}
		}
	}
}
void MEMSET_()
{
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	memset(LS,0,sizeof(LS));
	memset(a1,0,sizeof(a1));
}
void game()
{
	MEMSET_();
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
    flag=false;
    int i1,j1;
    for(int x=1;x<=25;x++)
    {
        for(int y=1;y<=25;y++)
        {
            if(a[x][y]=='E')
            {
                i1=x;
                j1=y;
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
    while(vis[i][j]==false)
    {
        memset(vis,false,sizeof(vis));
        random_map();
        flag=false;
        for(int x=1;x<=25;x++)
        {
            for(int y=1;y<=25;y++)
            {
                if(a[x][y]=='E')
                {
                    i1=x;
                    j1=y;
                    flag=true;
                    break;
                }
            }
            if(flag) break;
        }
        flag=false;
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
        dfs(i1,j1);
    }
    printmap();
    memset(LS,0,sizeof(LS));
    while(1)
    {
        char ch;
        ch=getch();
        if((ch=='W' || ch=='w' || ch==72) && a[i-1][j]!='#')
        {
        	LS[i-1][j]=!LS[i-1][j];
            a[i][j]='.';
            i--;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if((ch=='S' || ch=='s' || ch==80) && a[i+1][j]!='#')
        {
        	LS[i+1][j]=!LS[i+1][j];
            a[i][j]='.';
            i++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if((ch=='A' || ch=='a' || ch==75) && a[i][j-1]!='#')
        {
        	LS[i][j-1]=!LS[i][j-1];
            a[i][j]='.';
            j--;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if((ch=='D' || ch=='d' || ch==77) && a[i][j+1]!='#')
        {
        	LS[i][j+1]=!LS[i][j+1];
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
            if(opt=='R' || opt=='r') game();
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
    cout<<"请选择您的皮肤设置："<<endl;
    cout<<"1. Ocean\n";
    cout<<"2. Normal-black\n";
    cout<<"3. White\n";
    cout<<"4. Normal-while\n";
    cout<<"5. Classic\n";
    cout<<"6. Bright\n"; 
    char ch=getch();
    if(ch=='1') system("color 1F");
    else if(ch=='2') system("color 0F");
    else if(ch=='3') system("color 7C");
    else if(ch=='4') system("color 70");
    else if(ch=='5') system("color 0E");
    else if(ch=='6') system("color E8");
    else init_game();
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

