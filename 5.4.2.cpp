#include <bits/stdc++.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

int mxs,CNMDSB[9][9],curxxx,curyyy;
const int MAXN=60;

char a[MAXN][MAXN]; 
char a1[MAXN][MAXN];
void init_game();
void block(int x,int y)
{
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD setps;
    setps.X=x;
    setps.Y=y;
    SetConsoleCursorPosition(hCon,setps);  
}
bool vis[MAXN][MAXN];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1}; 
void dfs(int x,int y)
{
    for(int i=0;i<4;i++)
    {
        int curx=x+dx[i];
        int cury=y+dy[i];
        if(curx>1 && cury>1 && curx<mxs && cury<mxs && a[curx][cury]!='#' && !vis[curx][cury])
        {
            vis[curx][cury]=true; 
            dfs(curx,cury);
        }
    }
}
void clearr()
{
    int cnt=CNMDSB[curxxx][curyyy];
    while(cnt) printf("\b \b"),cnt/=10;
    printf("\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b\b \b");
}
void putstep(){printf("\n当前步数：%d",CNMDSB); Sleep(2000); clearr();}
void printgz()
{
    system("cls");
    printf("欢迎来到本迷宫游戏！\n");
    printf("游戏说明：W(w)向上走，S(s)向下走，A(a)向左走，D(d)向右走。\n");
    printf("符号标志：I代表你自己，E代表终点。\n");
    printf("'F'+op：将某个方向的'#'改为'.'。\n");
    printf("'-':把所有位置清空为'.'。\n");
    printf("'C':完全清空地图。\n");
    printf("'F'+'Z'：自行探究。\n");
    char op=getchar();
}
void printmap()
{
    for(int i=1;i<=mxs;i++)
    {
        for(int j=1;j<=mxs;j++)
        {
            if(a1[i][j]!=a[i][j])
            {
                block(j,i);
                printf("%c",a[i][j]);
                a1[i][j]=a[i][j];
            }
        }
    }
    block(0,mxs+1);
    return;
}
int diff;
void random_map()
{
    memset(a1,0,sizeof(a1));
    for(int i=1;i<=mxs;i++)
    {
        a[i][1]='#';
        a[1][i]='#';
        a[mxs][i]='#';
        a[i][mxs]='#';
    }
    for(int i=2;i<=mxs-1;i++)
    {
        for(int j=2;j<=mxs-1;j++)
        {
            int m=rand()%diff;
            if(m==1 || m==4 || m==5 || m==8 || m==14 || m==16 || m==17 ) a[i][j]='#';
            else a[i][j]='.';
        }
    }
    bool flag=false;
    for(int x=1;x<=mxs;x++)
    {
        for(int y=1;y<=mxs;y++)
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
    for(int x=mxs;x>=1;x--)
    {
        for(int y=mxs;y>=1;y--)
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
int tmp[9][9];
void win()
{
    system("color 0F");
    printf("\n\n\n     你赢了！\n\n\n     You win!!\n");
    Sleep(2000);
    PRINT_LAST();
    printf("您的路线：\n");
    for(int i=1;i<=mxs;i++,putchar('\n'))
        for(int j=1;j<=mxs;j++)
            printf("%c",a[i][j]);

    ifstream fin;
    fin.open("data.txt");
    for(int i=1;i<=6;i++)
    	for(int j=1;j<=5;j++)
    		fin>>tmp[i][j];
    if(tmp[curxxx][curyyy]>CNMDSB[curxxx][curyyy])
		tmp[curxxx][curyyy]=CNMDSB[curxxx][curyyy],printf("打破记录：该大小、该难度的地图的新的最佳步数为 %d 步！\n",tmp[curxxx][curyyy]);
    fin.close();
    ofstream fout;
    fout.open("data.txt");
    for(int i=1;i<=6;i++,fout<<endl)
    	for(int j=1;j<=5;j++)
    		fout<<tmp[i][j]<<" ";
    fout.close();

    cout<<"0:退出 1:再来一局";
    char ch=getch();
    if(ch=='0') exit(0);
    init_game();
}
void all_void()
{
    for(int i=1;i<=mxs;i++)
        for(int j=1;j<=mxs;j++)
            if(a[i][j]!='I')
                a[i][j]='.';
    return;
}
void fun()
{
    for(int i=1;i<=mxs;i++)
        for(int j=1;j<=mxs;j++)
            a[i][j]=rand()%26+97;
    return;
}
bool LS[35][35];
void PRINT_LAST()
{
    for(int x=2;x<=mxs-1;x++)
        for(int y=2;y<=mxs-1;y++)
            if(a[x][y]!='E')
                a[x][y]='.';
    for(int i=1;i<=mxs;i++)
        for(int j=1;j<=mxs;j++)
            if(LS[i][j]) a[i][j]='O';
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
    for(int x=1;x<=mxs;x++)
    {
        for(int y=1;y<=mxs;y++)
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
    for(int x=1;x<=mxs;x++)
    {
        for(int y=1;y<=mxs;y++)
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
        for(int x=1;x<=mxs;x++)
        {
            for(int y=1;y<=mxs;y++)
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
        for(int x=1;x<=mxs;x++)
        {
            for(int y=1;y<=mxs;y++)
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
    LS[i][j]=1; CNMDSB[curxxx][curyyy]=0; 
    while(1)
    {
        char ch;
        ch=getch();
        if(ch=='?') putstep();
        if((ch=='W' || ch=='w' || ch==72) && a[i-1][j]!='#')
        {
            LS[i-1][j]=1;
            a[i][j]='.';
            i--; CNMDSB[curxxx][curyyy]++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if((ch=='S' || ch=='s' || ch==80) && a[i+1][j]!='#')
        {
            LS[i+1][j]=1;
            a[i][j]='.';
            i++; CNMDSB[curxxx][curyyy]++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if((ch=='A' || ch=='a' || ch==75) && a[i][j-1]!='#')
        {
            LS[i][j-1]=1;
            a[i][j]='.';
            j--; CNMDSB[curxxx][curyyy]++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if((ch=='D' || ch=='d' || ch==77) && a[i][j+1]!='#')
        {
            LS[i][j+1]=1;
            a[i][j]='.';
            j++; CNMDSB[curxxx][curyyy]++;
            if(a[i][j]=='E') win();
            a[i][j]='I';
        }
        if(ch=='F' || ch=='f')
        {
            printf("F ");
            char opt;
            scanf("%d",&opt);
            if(opt=='W' || opt=='w') a[i-1][j]='.';
            if(opt=='S' || opt=='s') a[i+1][j]='.';
            if(opt=='A' || opt=='a') a[i][j-1]='.';
            if(opt=='D' || opt=='d') a[i][j+1]='.';
            if(opt=='Z' || opt=='z') fun();
            if(opt=='R' || opt=='r') game();
        }
        if(ch=='-')
            for(int x=2;x<=mxs-1;x++)
                for(int y=2;y<=mxs-1;y++)
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
    printf("请选择您的皮肤设置：\n");
    printf("1. Ocean\n");
    printf("2. Normal-black\n");
    printf("3. White\n");
    printf("4. Normal-while\n");
    printf("5. Classic\n");
    printf("6. Bright\n");
    char ch=getch();
    if(ch=='1') system("color 1F");
    else if(ch=='2') system("color 0F");
    else if(ch=='3') system("color 7C");
    else if(ch=='4') system("color 70");
    else if(ch=='5') system("color 0E");
    else if(ch=='6') system("color E8");
    else init_game();
    printf("\n\n请选择您的难度设置：\n");
    printf("1. easy\n");
    printf("2. normal\n");
    printf("3. hard\n");
    ch=getch(); curxxx=ch^48;
    if(ch=='1') diff=25;
    else if(ch=='2') diff=20;
    else if(ch=='3') diff=18;
    else{cout<<"自动设定为normal!";diff=20;}
    printf("\n\n请选择您的地图大小：\n");
    printf("1. 15x15\n");
    printf("2. 20x20\n");
    printf("3. 25x25\n");
    printf("4. 30x30\n");
    printf("5. 40x40\n");
    printf("6. 45x45\n");
    printf("7. 50x50\n");
    printf("8. 55x55\n");
    ch=getch(); curyyy=ch^48;
    if(ch=='1') mxs=15;
    if(ch=='2') mxs=20;
    if(ch=='3') mxs=25;
    if(ch=='4') mxs=30;
    if(ch=='5') mxs=40;
    if(ch=='6') mxs=45;
    if(ch=='7') mxs=50;
    if(ch=='8') mxs=55;
    printf("请问您有无历史存档？如果没有打 1，否则打 0。\n");
    ch=getch();
    if(ch=='1')
    {
        ofstream fout;
        fout.open("data.txt");
        for(int i=1;i<=6;i++,fout<<endl)
        	for(int j=1;j<=5;j++)
        		fout<<2147483647<<" ";
        fout.close();
    }
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

