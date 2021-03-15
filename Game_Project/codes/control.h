#pragma once
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// 화면 크기
#define _WINDOW_WIDTH 1200
#define _WINDOW_HEIGHT 900

// 화면의 중앙
#define _WINDOW_CENTER_WIDTH _WINDOW_WIDTH / 2
#define _WINDOW_CENTER_HEIGHT _WINDOW_HEIGHT / 2

GLfloat getRadian(GLfloat angle);
void moveMouseEvent(int x, int y);
void pressKeyboardEvent(unsigned char KeyPressed, int X, int Y);
void offKeyboardEvent(unsigned char KeyPressed, int X, int Y);
void MyTimer(int value);

