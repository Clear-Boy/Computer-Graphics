#define _WCHAR_T_DEFINED
#define _STDCALL_SUPPORTED
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int choice;
int a[1000];
int X1,Y1,X2,Y2;
int n;

void dda_line(int x0,int y0,int x1,int y1)//DDA算法
{
    int dx,dy,maxx,i;
    float x,y,xIn,yIn;
    dx=x1-x0;
    dy=y1-y0;
    x=x0;
    y=y0;
    if(abs(dx)>abs(dy))
        maxx=dx;
    else
        maxx=dy;
    xIn=(float)dx/(float)maxx;
    yIn=(float)dy/(float)maxx;
    for(i=0;i<=maxx;i++)
    {
        glBegin(GL_POINTS);//画点函数,只有两个参数,
        glVertex2i(int(x+0.5),int(y+0.5));//根据x,y进行划线
        glEnd();
        x+=xIn;
        y+=yIn;
    }
}

void midpoint_line(int x1,int y1,int x2,int y2)//中点画线法
{
	int x,y,d1,d2,d0,xNext,yNext;
	float m;
	if (x2<x1)
	{
		d0=x1,x1=x2,x2=d0;
		d0=y1,y1=y2,y2=d0;
	}
	x=y1-y2,y=x2-x1;//x==a y==b
	if (y==0)
		m=-1*x*100;
	else
		m=(float)x/(x1-x2);
	xNext=x1,yNext=y1;
	glBegin(GL_POINTS);//画点函数,只有两个参数,
    glVertex2i(xNext,yNext);//根据x,y进行划线
    glEnd();
	if (m>=0 && m<=1)
	{
		d0=2*x+y;d1=2*x,d2=2*(x+y);
	 	while (xNext<x2)
	 	{
	 		if (d0<=0)
	 		{
	 			xNext++,yNext++,d0+=d2;
	 		}
			else
			{
				xNext++,d0+=d1;
			}
			glBegin(GL_POINTS);//画点函数,只有两个参数,
    		glVertex2i(xNext,yNext);//根据x,y进行划线
    		glEnd();
	 	}
	}
	else if (m<=0 && m>=-1)
	{
		d0=2*x-y;d1=2*x-2*y,d2=2*x;
   	 	while (xNext<x2)
	 	{
	 		if (d0>0)
	 		{
	 			xNext++,yNext--,d0+=d1;
	 		}
			else
			{
				xNext++,d0+=d2;
			}
			glBegin(GL_POINTS);//画点函数,只有两个参数,
    		glVertex2i(xNext,yNext);//根据x,y进行划线
    		glEnd();
	 	}
	}
	else if (m>1)
	{
		d0=x+2*y;d1=2*(x+y),d2=2*y;
	 	while (yNext<y2)
	 	{
	 		if (d0>0)
	 		{
	 			xNext++,yNext++,d0+=d1;
	 		}
			else
			{
				yNext++,d0+=d2;
			}
			glBegin(GL_POINTS);//画点函数,只有两个参数,
    		glVertex2i(xNext,yNext);//根据x,y进行划线
    		glEnd();
	 	}
	}
	else
	{
		d0=x-2*y;
		d1=-2*y,d2=2*(x-y);
	 	while (yNext>y2)
	 	{
	 		if (d0<=0)
	 		{
	 			xNext++,yNext--,d0+=d2;
	 		}
			else
			{
				yNext--,d0+=d1;
			}
			glBegin(GL_POINTS);//画点函数,只有两个参数,
    		glVertex2i(xNext,yNext);//根据x,y进行划线
    		glEnd();
	 	}
	}
}

void bresenham_line(int x1,int y1,int x2,int y2)//Bresenham算法
{
	int x,y,xNext,yNext,e;
	if((x2<x1&&y2<y1)||(x2<x1&&y2>y1))
    {
        int change=x2;
        x2=x1;
        x1=change;
        change=y2;
        y2=y1;
        y1=change;
    }
	x=x2-x1;
	y=y2-y1;
	if(y>x)//斜率k>1
    {
        e=-y;
        xNext=x1;
        yNext=y1;
        for(int i=0;i<=y;i++)
        {
            glBegin(GL_POINTS);//画点函数,只有两个参数,
            glVertex2i(xNext,yNext);//根据x,y进行划线
            glEnd();
            yNext++;
            e=e+2*x;
            if(e>=0)
            {
                xNext++;
                e=e-2*y;
            }
        }
    }
    else if(y>=0)//斜率0<k<=1
    {
        e=-x;
        xNext=x1;
        yNext=y1;
        for(int i=0;i<=x;i++)
        {
            glBegin(GL_POINTS);//画点函数,只有两个参数,
            glVertex2i(xNext,yNext);//根据x,y进行划线

            glEnd();
            xNext++;
            e=e+2*y;
            if(e>=0)
            {
                yNext++;
                e=e-2*x;
            }
        }
    }
    else if(x+y>0)//-1<k<0
    {
        e=-x;
        xNext=x1;
        yNext=y1;
        for(int i=0;i<=x;i++)
        {
            glBegin(GL_POINTS);//画点函数,只有两个参数,
            glVertex2i(xNext,yNext);//根据x,y进行划线

            glEnd();
            xNext++;
            e=e-2*y;
            if(e>=0)
            {
                yNext--;
                e=e-2*x;
            }
        }
    }
    else//k<-1
    {
        e=-y;
        xNext=x1;
        yNext=y1;
        for(int i=0;i<=-y;i++)
        {
            glBegin(GL_POINTS);//画点函数,只有两个参数,
            glVertex2i(xNext,yNext);//根据x,y进行划线
            glEnd();
            yNext--;
            e=e+2*x;
            if(e>=0)
            {
                xNext++;
                e=e+2*y;
            }
        }
    }

}

void display( void )//创建一个没有参数的函数来调用上一个函数
{
    glClear(GL_COLOR_BUFFER_BIT); //刷新缓存,在窗口中出现
    if(choice==1)
    {
        for(int i=0;i<4*n;i+=4)
            dda_line(a[i],a[i+1],a[i+2],a[i+3]);
    }
    else if(choice==2)
    {
        for(int i=0;i<4*n;i+=4)
            midpoint_line(a[i],a[i+1],a[i+2],a[i+3]);//中点画线法调用
    }
    else if(choice==3)
    {
        for(int i=0;i<4*n;i+=4)
            bresenham_line(a[i],a[i+1],a[i+2],a[i+3]);
    }
    glFlush();//清理缓存来处理函数
 }

int main(int argc, char* argv[])
{
    printf("画线算法菜单如下：\n");
    printf("1.DDA画线算法\n2.中点画线算法\n3.Bresenham画线算法\n");
    printf("请选择：");
    while(1)
    {
        scanf("%d",&choice);
        if(choice!=1&&choice!=2&&choice!=3)
        {
            printf("输入错误，请重新输入：");
            continue;
        }
        break;
    }
    while(1)
    {
        int j=1;
        printf("请输入目标图形边的个数：");
        scanf("%d",&n);
        for(int i=0;i<4*n;i+=4)
        {
            printf("请输入第%d条边的起始点坐标与终点坐标，如输入0 0 600 600!\n",j);
            scanf("%d%d%d%d",&a[i],&a[i+1],&a[i+2],&a[i+3]);
            while(a[i]<0||a[i+1]<0||a[i+2]<0||a[i+3]<0)
            {
                printf("输入错误，请重新输入:\n");
                scanf("%d%d%d%d",&a[i],&a[i+1],&a[i+2],&a[i+3]);
                continue;
            }
            j++;
        }
        break;

    }
    glutInit(&argc,argv);//glut的初始化
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);//窗口的大小500x500
    glutInitWindowPosition(0,0);//定义窗口的位置,在屏幕向左边0像素,屏幕上面向下0像素
    if(choice==1)
    {
        glutCreateWindow("DDA画线算法");//屏幕上方显示的内容
    }
    else if(choice==2)
    {
        glutCreateWindow("中点画线算法");
    }
    else if(choice==3)
    {
        glutCreateWindow("Bresenham画线算法");
    }
    glClearColor(1.0, 1.0, 1.0, 0.0); //三个1.0是白色背景,三个0.0是黑色背景
    glColor3f(1, 0, 0); //红线
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);//在窗口内建立二维直角坐标系,x1,x2,y1,y2
    glutDisplayFunc(display);//在窗口中显示diaplay
    glutMainLoop();
}
