/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:48:54 by yosherau          #+#    #+#             */
/*   Updated: 2025/10/21 15:28:40 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3 * PI / 2
#define DR 0.0174533

float	px, py, pdx, pdy, pa;

int		mapX = 8, mapY = 8, mapS = 64;
int		map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

void	drawPlayer()
{
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px, py);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(px, py);
	glVertex2i(px + pdx * 5, py + pdy * 5);
	glEnd();
}

void	drawMap2D()
{
	int	x, y, xo, yo;
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			if (map[y * mapX + x] == 1)
				glColor3f(1, 1, 1);
			else
				glColor3f(0, 0, 0);
			xo = x * mapS;
			yo = y * mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo + 1, yo + 1);
			glVertex2i(xo + 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + 1);
			glEnd();
		}
	}
}

float	dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw3DRays()
{
	int		rays, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, disT;

	ra = pa - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (rays = 0; rays < 60; rays++)
	{
		dof = 0;
		float	disH = 1000000, hx = px, hy = py;
		float	aTan = -1/tan(ra);
		if (ra > PI)
		{
			// Rounding rays y position to nearest 64th value?
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			// Rounding rays y position to nearest 64th value?
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				hx = rx, hy = ry;
				disH = dist(px, py, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		dof = 0;
		float	disV = 10000000, vx = px, vy = py;
		float	nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			// Rounding rays y position to nearest 64th value?
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			// Rounding rays y position to nearest 64th value?
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				vx = rx, vy = ry;
				disV = dist(px, py, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
			rx = vx, ry = vy, disT = disV, glColor3f(0.9, 0, 0);
		else
			rx = hx, ry = hy, disT = disH, glColor3f(0.7, 0, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(px, py);
		glVertex2i(rx, ry);
		glEnd();
		float ca = pa - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(ca);
		float lineH = (mapS * 320) / disT;
		float lineO = 160 - lineH / 2;
		if (lineH > 320)
			lineH = 320;
		glLineWidth(8); glBegin(GL_LINES); glVertex2i(rays * 8 + 530, lineO), glVertex2i(rays * 8 + 530, lineH + lineO);
		glEnd();
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawPlayer();
	draw3DRays();
	glutSwapBuffers();
}

void	buttons(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (key == 'd')
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (key == 'w')
	{
		px += pdx;
		py += pdy;
	}
	if (key == 's')
	{
		px -= pdx;
		py -= pdy;
	}
	glutPostRedisplay();
}

void	init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
	px = 300, py = 300, pdx = cos(pa) * 5, pdy= sin(pa) * 5;
}

void	resize(int w, int h)
{
	glutReshapeWindow(1024, 512);
}

int	main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 640);
	glutCreateWindow("");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(buttons);
	glutMainLoop();
	return (0);
}
