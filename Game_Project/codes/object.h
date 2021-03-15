#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <GL/glut.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class CPoint2f {
public:
	vector <float> d{ 0, 0 };
};

class CPoint3f {
public:
	vector <float> d{ 0, 0, 0 };
};

class CPoint3i {
public:
	vector <int> d{ 0, 0, 0 };
};

class CFace {
public:
	vector <CPoint3i> v_pairs;
};

class CObj {
public:
	string name;
	vector <CPoint3f> v;
	vector <CPoint2f> vt;
	vector <CPoint3f> vn;
	vector <CFace> f;
};

class CModel {
public:
	vector <CObj> objs;
};

void display_objs(CModel* model);
void display_objs_texture(CModel* model, int* texture_id, int texture_length);
void loadObj(ifstream& fin, CModel* model);

