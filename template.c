/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:48:54 by yosherau          #+#    #+#             */
/*   Updated: 2025/10/11 15:57:26 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glut.h>

// When compiling have to include linkinh to GL libraries, -lglut -lGLU -lGL

void	display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2f(100, 300);
	glVertex2f(100, 100);
	glVertex2f(200, 100);
	glVertex2f(200, 300);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

int	main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 640);
	glutCreateWindow("");
	glutDisplayFunc(display);
	gluOrtho2D(0, 640, 0, 640);
	glClearColor(0.5, 0.7, 0.5, 0);
	glutMainLoop();
	return (0);
}
