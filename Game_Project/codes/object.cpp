#include "object.h"

vector<float> my_strtok_f(char* str, char* delimeter) {
	vector <float> v;
	char* context;
	char* tok = strtok_s(str, delimeter, &context);

	while (tok != NULL) {
		v.push_back(atof(tok));
		tok = strtok_s(NULL, delimeter, &context);
	}
	return v;
}

vector<string> my_strtok_s(char* str, char* delimeter) {
	vector <string> v;
	char* context;
	char* tok = strtok_s(str, delimeter, &context);

	while (tok != NULL) {
		v.push_back(tok);
		tok = strtok_s(context, delimeter, &context);
	}
	return v;
}

vector<int> my_strtok_i(char* str, char* delimeter) {
	vector <int> v;
	char* context;
	char* tok = strtok_s(str, delimeter, &context);

	while (tok != NULL) {
		v.push_back(atoi(tok));
		tok = strtok_s(context, delimeter, &context);
	}
	return v;
}

// object를 display 하는 함수
void display_objs(CModel* model) {
	GLfloat x, y, z, nx, ny, nz;
	int v_id, vt_id, vn_id;
	glDisable(GL_TEXTURE_2D);

	for (int o = 0; o < model->objs.size(); o++) {
		int nFaces = model->objs[o].f.size();

		for (int k = 0; k < nFaces; k++) {
			int nPoints = model->objs[o].f[k].v_pairs.size();
			glBegin(GL_POLYGON);
			for (int i = 0; i < nPoints; i++) {
				v_id = model->objs[o].f[k].v_pairs[i].d[0];
				vt_id = model->objs[o].f[k].v_pairs[i].d[1];
				vn_id = model->objs[o].f[k].v_pairs[i].d[2];

				x = model->objs[o].v[v_id - 1].d[0];
				y = model->objs[o].v[v_id - 1].d[1];
				z = model->objs[o].v[v_id - 1].d[2];

				nx = model->objs[o].vn[vn_id - 1].d[0];
				ny = model->objs[o].vn[vn_id - 1].d[1];
				nz = model->objs[o].vn[vn_id - 1].d[2];
				glNormal3f(nx, ny, nz);
				glVertex3f(x, y, z);
			}
			glEnd();
		}
	}
}

extern Mat image[6];
// object에 texture를 입혀서 display 하는 함수
void display_objs_texture(CModel* model, int* texture_id, int texture_length) {
	GLfloat x, y, z, nx, ny, nz, tx, ty;
	int v_id, vt_id, vn_id, tex_id;
	int texture_Index;
	glEnable(GL_TEXTURE_2D);

	if (texture_length > 0)
		texture_Index = 0;

	for (int o = 0; o < model->objs.size(); o++) {
		if (texture_Index < texture_length)
			tex_id = texture_id[texture_Index++];

		glBindTexture(GL_TEXTURE_2D, texture_id[tex_id]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[tex_id - 1].cols, image[tex_id - 1].rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image[tex_id - 1].data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		int nFaces = model->objs[o].f.size();

		for (int k = 0; k < nFaces; k++) {
			int nPoints = model->objs[o].f[k].v_pairs.size();
			glBegin(GL_POLYGON);
			for (int i = 0; i < nPoints; i++) {
				v_id = model->objs[o].f[k].v_pairs[i].d[0];
				vt_id = model->objs[o].f[k].v_pairs[i].d[1];
				vn_id = model->objs[o].f[k].v_pairs[i].d[2];

				x = model->objs[o].v[v_id - 1].d[0];
				y = model->objs[o].v[v_id - 1].d[1];
				z = model->objs[o].v[v_id - 1].d[2];

				nx = model->objs[o].vn[vn_id - 1].d[0];
				ny = model->objs[o].vn[vn_id - 1].d[1];
				nz = model->objs[o].vn[vn_id - 1].d[2];

				tx = model->objs[o].vt[vt_id - 1].d[0];
				ty = model->objs[o].vt[vt_id - 1].d[1];

				glNormal3f(nx, ny, nz);
				glTexCoord2f(tx, ty);
				glVertex3f(x, y, z);
			}
			glEnd();
		}
	}
}

// object load 하기
void loadObj(ifstream& fin, CModel* model) {
	string line;
	CObj obj_tmp;
	int cnt = 0;

	// 이전 obj까지의 누적 벡터수
	int cnt_prev_vertex = 0;
	int cnt_prev_texture = 0;
	int cnt_prev_normal = 0;

	while (getline(fin, line)) {
		int len = line.length();
		vector<float> vf;
		vector<string> s;
		vector<int> vi;
		CPoint3f p3;
		CPoint2f p2;
		CPoint3i p3i;

		if (line[0] == 'o' && line[1] == ' ') {
			obj_tmp.name = line.substr(2, len - 2);
			model->objs.push_back(obj_tmp);
			if (cnt > 0) {
				cnt_prev_vertex += model->objs[cnt - 1].v.size();
				cnt_prev_texture += model->objs[cnt - 1].vt.size();
				cnt_prev_normal += model->objs[cnt - 1].vn.size();
			}
			cnt += 1;
		}

		if (line[0] == 'v' && line[1] == ' ') {
			vf = my_strtok_f((char*)line.substr(2, len - 2).c_str(), (char*)" ");
			p3.d = { vf[0], vf[1], vf[2] };
			model->objs[cnt - 1].v.push_back(p3);
		}
		else if (line[0] == 'v' && line[1] == 't') {
			vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
			p2.d = { vf[0], vf[1] };
			model->objs[cnt - 1].vt.push_back(p2);
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
			p3.d = { vf[0], vf[1], vf[2] };
			model->objs[cnt - 1].vn.push_back(p3);
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			s = my_strtok_s((char*)line.substr(2, len - 2).c_str(), (char*)" ");
			int nVertexes = s.size();
			CFace face_tmp;
			for (int i = 0; i < nVertexes; i++) {
				vi = my_strtok_i((char*)s[i].c_str(), (char*)"/");
				p3i.d = {
					vi[0] - cnt_prev_vertex,
					vi[1] - cnt_prev_texture,
					vi[2] - cnt_prev_normal
				};
				face_tmp.v_pairs.push_back(p3i);
			}
			model->objs[cnt - 1].f.push_back(face_tmp);
		}
	}
}

/*
// display 하는 함수들
display_objs();

// 파일 불러오는 함수들
string filepath = "D:/CG/Blender/man.obj";
ifstream fin(filepath);
m.loadObj(fin);
fin.close();
*/
