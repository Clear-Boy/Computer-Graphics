#define _WCHAR_T_DEFINED
#define _STDCALL_SUPPORTED
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int choice;
int a[1000];
int X1,Y1,X2,Y2;
int n;

void dda_line(int x0,int y0,int x1,int y1)//DDA�㷨
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
        glBegin(GL_POINTS);//���㺯��,ֻ����������,
        glVertex2i(int(x+0.5),int(y+0.5));//����x,y���л���
        glEnd();
        x+=xIn;
        y+=yIn;
    }
}

void midpoint_line(int x1,int y1,int x2,int y2)//�е㻭�߷�
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
	glBegin(GL_POINTS);//���㺯��,ֻ����������,
    glVertex2i(xNext,yNext);//����x,y���л���
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
			glBegin(GL_POINTS);//���㺯��,ֻ����������,
    		glVertex2i(xNext,yNext);//����x,y���л���
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
			glBegin(GL_POINTS);//���㺯��,ֻ����������,
    		glVertex2i(xNext,yNext);//����x,y���л���
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
			glBegin(GL_POINTS);//���㺯��,ֻ����������,
    		glVertex2i(xNext,yNext);//����x,y���л���
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
			glBegin(GL_POINTS);//���㺯��,ֻ����������,
    		glVertex2i(xNext,yNext);//����x,y���л���
    		glEnd();
	 	}
	}
}

void bresenham_line(int x1,int y1,int x2,int y2)//Bresenham�㷨
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
	if(y>x)//б��k>1
    {
        e=-y;
        xNext=x1;
        yNext=y1;
        for(int i=0;i<=y;i++)
        {
            glBegin(GL_POINTS);//���㺯��,ֻ����������,
            glVertex2i(xNext,yNext);//����x,y���л���
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
    else if(y>=0)//б��0<k<=1
    {
        e=-x;
        xNext=x1;
        yNext=y1;
        for(int i=0;i<=x;i++)
        {
            glBegin(GL_POINTS);//���㺯��,ֻ����������,
            glVertex2i(xNext,yNext);//����x,y���л���

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
            glBegin(GL_POINTS);//���㺯��,ֻ����������,
            glVertex2i(xNext,yNext);//����x,y���л���

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
            glBegin(GL_POINTS);//���㺯��,ֻ����������,
            glVertex2i(xNext,yNext);//����x,y���л���
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

void display( void )//����һ��û�в����ĺ�����������һ������
{
    glClear(GL_COLOR_BUFFER_BIT); //ˢ�»���,�ڴ����г���
    if(choice==1)
    {
        for(int i=0;i<4*n;i+=4)
            dda_line(a[i],a[i+1],a[i+2],a[i+3]);
    }
    else if(choice==2)
    {
        for(int i=0;i<4*n;i+=4)
            midpoint_line(a[i],a[i+1],a[i+2],a[i+3]);//�е㻭�߷�����
    }
    else if(choice==3)
    {
        for(int i=0;i<4*n;i+=4)
            bresenham_line(a[i],a[i+1],a[i+2],a[i+3]);
    }
    glFlush();//��������������
 }

int main(int argc, char* argv[])
{
    printf("�����㷨�˵����£�\n");
    printf("1.DDA�����㷨\n2.�е㻭���㷨\n3.Bresenham�����㷨\n");
    printf("��ѡ��");
    while(1)
    {
        scanf("%d",&choice);
        if(choice!=1&&choice!=2&&choice!=3)
        {
            printf("����������������룺");
            continue;
        }
        break;
    }
    while(1)
    {
        int j=1;
        printf("������Ŀ��ͼ�αߵĸ�����");
        scanf("%d",&n);
        for(int i=0;i<4*n;i+=4)
        {
            printf("�������%d���ߵ���ʼ���������յ����꣬������0 0 600 600!\n",j);
            scanf("%d%d%d%d",&a[i],&a[i+1],&a[i+2],&a[i+3]);
            while(a[i]<0||a[i+1]<0||a[i+2]<0||a[i+3]<0)
            {
                printf("�����������������:\n");
                scanf("%d%d%d%d",&a[i],&a[i+1],&a[i+2],&a[i+3]);
                continue;
            }
            j++;
        }
        break;

    }
    glutInit(&argc,argv);//glut�ĳ�ʼ��
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);//���ڵĴ�С500x500
    glutInitWindowPosition(0,0);//���崰�ڵ�λ��,����Ļ�����0����,��Ļ��������0����
    if(choice==1)
    {
        glutCreateWindow("DDA�����㷨");//��Ļ�Ϸ���ʾ������
    }
    else if(choice==2)
    {
        glutCreateWindow("�е㻭���㷨");
    }
    else if(choice==3)
    {
        glutCreateWindow("Bresenham�����㷨");
    }
    glClearColor(1.0, 1.0, 1.0, 0.0); //����1.0�ǰ�ɫ����,����0.0�Ǻ�ɫ����
    glColor3f(1, 0, 0); //����
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);//�ڴ����ڽ�����άֱ������ϵ,x1,x2,y1,y2
    glutDisplayFunc(display);//�ڴ�������ʾdiaplay
    glutMainLoop();
}
