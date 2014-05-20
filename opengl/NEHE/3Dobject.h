#if !defined(_3DOBJECT_H_)
#define _3DOBJECT_H_

#include <stdio.h>

//  3D����ṹ
struct sPoint{
	float x, y, z;
};

// ƽ�淽��Ϊ: ax + by + cz + d = 0
struct sPlaneEq{
	float a, b, c, d;
};

// ����һ��ģ�ͱ���Ľṹ
struct sPlane{
	unsigned int p[3];
	sPoint normals[3];
	unsigned int neigh[3];
	sPlaneEq PlaneEq;
	bool visible;
};

// ����һ��������Ӱ������
struct glObject{
	GLuint nPlanes, nPoints;
	sPoint points[100];
	sPlane planes[200];
};

// ��ȡģ��
inline int ReadObject(char *st, glObject *o){
  FILE *file;
  unsigned int i;

  file = fopen(st, "r");
  if (!file) return FALSE;
  //��ȡ����
  fscanf(file, "%d", &(o->nPoints));
  for (i=1;i<=o->nPoints;i++){
    fscanf(file, "%f", &(o->points[i].x));
    fscanf(file, "%f", &(o->points[i].y));
    fscanf(file, "%f", &(o->points[i].z));
  }
  //��ȡ��������
  fscanf(file, "%d", &(o->nPlanes));
  for (i=0;i<o->nPlanes;i++){
    fscanf(file, "%d", &(o->planes[i].p[0]));
    fscanf(file, "%d", &(o->planes[i].p[1]));
    fscanf(file, "%d", &(o->planes[i].p[2]));
	//��ȡÿ������ķ���
    fscanf(file, "%f", &(o->planes[i].normals[0].x));
    fscanf(file, "%f", &(o->planes[i].normals[0].y));
    fscanf(file, "%f", &(o->planes[i].normals[0].z));
    fscanf(file, "%f", &(o->planes[i].normals[1].x));
    fscanf(file, "%f", &(o->planes[i].normals[1].y));
    fscanf(file, "%f", &(o->planes[i].normals[1].z));
    fscanf(file, "%f", &(o->planes[i].normals[2].x));
    fscanf(file, "%f", &(o->planes[i].normals[2].y));
    fscanf(file, "%f", &(o->planes[i].normals[2].z));
  }
  return TRUE;
}

// �������ڶ�����Ϣ
inline void SetConnectivity(glObject *o){
	unsigned int p1i, p2i, p1j, p2j;
	unsigned int P1i, P2i, P1j, P2j;
	unsigned int i,j,ki,kj;

	//����ģ���е�ÿһ����A
	for(i=0;i<o->nPlanes-1;i++)
	{
		//���ڳ��˴������������B
		for(j=i+1;j<o->nPlanes;j++)
		{
			//������A�е�ÿһ�����ڵĶ���
			for(ki=0;ki<3;ki++)
			{
				//���������ڵĶ���û�б�����
				if(!o->planes[i].neigh[ki])
				{
					for(kj=0;kj<3;kj++)
					{
						p1i=ki;
						p1j=kj;
						p2i=(ki+1)%3;
						p2j=(kj+1)%3;

						p1i=o->planes[i].p[p1i];
						p2i=o->planes[i].p[p2i];
						p1j=o->planes[j].p[p1j];
						p2j=o->planes[j].p[p2j];
				
						//�����A�ı�P1i->P1j����B�ı�P2i->P2jΪͬһ���ߣ���������Ĺ�ʽ��P1i=P1j������P2i=P2j
						P1i=((p1i+p2i)-abs(int(p1i-p2i)))/2;
						P2i=((p1i+p2i)+abs(int(p1i-p2i)))/2;
						P1j=((p1j+p2j)-abs(int(p1j-p2j)))/2;
						P2j=((p1j+p2j)+abs(int(p1j-p2j)))/2;

						//��¼����������ڵ��������
						if((P1i==P1j) && (P2i==P2j))
						{
							o->planes[i].neigh[ki] = j+1;	  
							o->planes[j].neigh[kj] = i+1;	  
						}
					}
				}
			}
		}
	}
}

// ����ƽ��ķ��̲���
inline void CalcPlane(glObject o, sPlane *plane){
	sPoint v[4];
	int i;

	for (i=0;i<3;i++){
		v[i+1].x = o.points[plane->p[i]].x;
		v[i+1].y = o.points[plane->p[i]].y;
		v[i+1].z = o.points[plane->p[i]].z;
	}
	plane->PlaneEq.a = v[1].y*(v[2].z-v[3].z) + v[2].y*(v[3].z-v[1].z) + v[3].y*(v[1].z-v[2].z);
	plane->PlaneEq.b = v[1].z*(v[2].x-v[3].x) + v[2].z*(v[3].x-v[1].x) + v[3].z*(v[1].x-v[2].x);
	plane->PlaneEq.c = v[1].x*(v[2].y-v[3].y) + v[2].x*(v[3].y-v[1].y) + v[3].x*(v[1].y-v[2].y);
	plane->PlaneEq.d =-( v[1].x*(v[2].y*v[3].z - v[3].y*v[2].z) +
					  v[2].x*(v[3].y*v[1].z - v[1].y*v[3].z) +
					  v[3].x*(v[1].y*v[2].z - v[2].y*v[1].z) );
}

// ����ģ��
void DrawGLObject(glObject o)
{
	unsigned int i, j;

	glBegin(GL_TRIANGLES);
	for (i=0; i<o.nPlanes; i++){
		for (j=0; j<3; j++){
			glNormal3f(o.planes[i].normals[j].x,
					o.planes[i].normals[j].y,
					o.planes[i].normals[j].z);
			glVertex3f(o.points[o.planes[i].p[j]].x,
					o.points[o.planes[i].p[j]].y,
					o.points[o.planes[i].p[j]].z);
		}
	}
	glEnd();
}

void doShadowPass(glObject *o, float *lp)
{
	unsigned int	i, j, k, jj;
	unsigned int	p1, p2;
	sPoint			v1, v2;

	//��ģ���е�ÿһ����
	for (i=0; i<o->nPlanes;i++)
	{	
		//������ڵƹ��ǰ��
		if (o->planes[i].visible)
		{
			//���ڱ��ƹ���������ÿһ�����ڵ���
			for (j=0;j<3;j++)
			{
				k = o->planes[i].neigh[j];
				//����治���ڣ��򲻱��ƹ����䣬��ô������Ǳ߽�
				if ((!k) || (!o->planes[k-1].visible))
				{
					// ��������������
					p1 = o->planes[i].p[j];
					jj = (j+1)%3;
					p2 = o->planes[i].p[jj];

					//����ߵĶ��㵽�ƹ�ķ��򣬲��Ŵ�100��
					v1.x = (o->points[p1].x - lp[0])*100;
					v1.y = (o->points[p1].y - lp[1])*100;
					v1.z = (o->points[p1].z - lp[2])*100;

					v2.x = (o->points[p2].x - lp[0])*100;
					v2.y = (o->points[p2].y - lp[1])*100;
					v2.z = (o->points[p2].z - lp[2])*100;
					
					//���ƹ�����Ӱ��߽����
					glBegin(GL_TRIANGLE_STRIP);
						glVertex3f(o->points[p1].x,
									o->points[p1].y,
									o->points[p1].z);
						glVertex3f(o->points[p1].x + v1.x,
									o->points[p1].y + v1.y,
									o->points[p1].z + v1.z);

						glVertex3f(o->points[p2].x,
									o->points[p2].y,
									o->points[p2].z);
						glVertex3f(o->points[p2].x + v2.x,
									o->points[p2].y + v2.y,
									o->points[p2].z + v2.z);
					glEnd();
				}
			}
		}
	}

}

//������Ӱ
void  CastShadow(glObject *o, float *lp)
{
	float			side;

	//����ƽ�淽�̣�������Щ�ڵƹ��ǰ����ƽ��Ϊ�ɼ�
	for (int i=0;i<o->nPlanes;i++)
	{
		side =	o->planes[i].PlaneEq.a*lp[0]+
				o->planes[i].PlaneEq.b*lp[1]+
				o->planes[i].PlaneEq.c*lp[2]+
				o->planes[i].PlaneEq.d*lp[3];
		if (side >0) o->planes[i].visible = TRUE;
				else o->planes[i].visible = FALSE;
	}

	glDisable( GL_LIGHTING );					// �رյƹ�
	
	glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );		// �ر���ɫ�����д��	
	
	glDepthFunc( GL_LEQUAL );					// ������ȱȽϺ���
	glDepthMask( GL_FALSE );					// �ر���Ȼ����д��	
	
	glEnable( GL_STENCIL_TEST );				// ʹ���ɰ建��
	glStencilFunc( GL_ALWAYS, 1, 0xFFFFFFFFL );	// �����ɰ庯��


	// �������ʱ�루�������ӵ㣩�Ķ���Σ�ͨ�����ɰ����Ȳ��ԣ�����ɰ��ֵ����1
	glFrontFace(GL_CCW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	doShadowPass(o,lp);

	// �����˳ʱ�루�������ӵ㣩�Ķ���Σ�ͨ�����ɰ����Ȳ��ԣ�����ɰ��ֵ����1
	glFrontFace(GL_CW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	doShadowPass(o,lp);

	glFrontFace(GL_CCW);
	glColorMask(1, 1, 1, 1);

	//����Ӱ��������ɫ
	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-0.1f, 0.1f,-0.10f);
		glVertex3f(-0.1f,-0.1f,-0.10f);
		glVertex3f( 0.1f, 0.1f,-0.10f);
		glVertex3f( 0.1f,-0.1f,-0.10f);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
	glShadeModel(GL_SMOOTH);
}

#endif // _3DOBJECT_H_