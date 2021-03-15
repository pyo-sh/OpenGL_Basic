#pragma once
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <time.h>

#define BRICK_SCALE 2
#define BRICK_SIZE 0.275f
#define BRICK_X BRICK_SIZE * BRICK_SCALE

#define HOUSE_SCALE 5
#define HOUSE_HEIGHT 10

// 사다리는 60도
#define LADDER_PLATFORM_WIDTH 0.16f
#define LADDER_PLATFORM_HEIGHT (GLfloat)2 * BRICK_SIZE / sqrt(3)
#define LADDER_HEIGHT LADDER_PLATFORM_HEIGHT * HOUSE_HEIGHT

void initBlow();
void drawHouse(int blow);
void drawShovel();
void drawBrick(GLfloat moveX, GLfloat moveY, GLfloat moveZ, GLfloat angle);
void drawChair();
void drawLadder(int blow);
void drawBase();