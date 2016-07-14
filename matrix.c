#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix {
	float* buf;
	int r;
	int c;
	int s;
};

typedef struct matrix Matrix;

Matrix* allocMatrix (int r, int c) {
	Matrix* m = malloc (sizeof (Matrix));

	m->r = r;
	m->c = c; 
	m->s = r * c;
	m->buf = malloc (sizeof (double) * m->s);
	 
	return m;
}

void freeMatrix (Matrix* m) {
	free (m->buf);
	free (m);
}

float i2[] = {
	1,0,
	0,1
};

float i3[] = {
	1,0,0,
	0,1,0,
	0,0,1
};

float i4[] = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

void setToZero (Matrix* m) {
	memset (m->buf, 0, sizeof (float) * m->s); 
}

int setToIdentity (Matrix* m) {
	if (m->r != m->c) {
		return 0;
	}

	switch (m->r) {
		case 2:
			memcpy (m->buf, i2, sizeof (float) * m->s);
			break;
		case 3:
			memcpy (m->buf, i3, sizeof (float) * m->s);
			break;
		case 4:
			memcpy (m->buf, i4, sizeof (float) * m->s);
			break;
		default:
			return 0;
	}

	return 1;	
}

Matrix* addMatrix (Matrix* m1, Matrix* m2) {
	if (m1->r != m2->r || m1->c != m2->c) {
		return NULL;
	}

	Matrix* n = allocMatrix (m1->r, m1->c);
	for (int i = 0; i < m1->s; ++i) {
		n->buf[i] = m1->buf[i] + m2->buf[i];
	}

	return n;
}

Matrix* subtractMatrix (Matrix* m1, Matrix* m2) {
	if (m1->r != m2->r || m1->c != m2->c) {
		return NULL;
	}

	Matrix* n = allocMatrix (m1->r, m1->c);
	for (int i = 0; i < m1->s; ++i) {
		n->buf[i] = m1->buf[i] - m2->buf[i];
	}

	return n;
}

Matrix* multiplyMatrix (Matrix* m1, Matrix* m2) {
	if (m1->c != m2->r) {
		return NULL;
	}

	Matrix* n = allocMatrix (m1->r, m2->c);

	int pos = 0;
	for (int i = 0; i < m1->r; ++i) {
		for (int j = 0; j < m2->c; ++j) {
			n->buf[pos] = m1->buf[i] * m2->buf[j];
			++pos;
		}
	}

	return n;
}

Matrix* multiplyScalar (Matrix* m, float s) {
	Matrix* n = allocMatrix (m->r, m->c);

	for (int i = 0; i < m->s; ++i) {
		n->buf[i] = m->buf[i] * s;
	}

	return n;
}

int setValue (Matrix* m, int r, int c, float val) {
	if (r >= m->r || c >= m->c) {
		return 0;
	}

	int pos = (r * 4) + c;  
	m->buf[pos] = val;

	return 1;
};

void setValues (Matrix* m, float* vals) {
	memcpy (m->buf, vals, sizeof (float) * m->s);
}

void printMatrix (Matrix* m) {
	int pos = 0;
	for (int i = 0; i < m->r; ++i) {
		for (int j = 0; j < m->c; ++j) {
			printf ("%f%c", m->buf[pos], j == m->c - 1 ? '\n' : ' ');
			++pos;
		}
	}
	puts ("\n");
}

int main (int argc, char* argv[]) {
	Matrix* m1 = allocMatrix (4,4);
	
	setToIdentity (m1);

	printMatrix (m1);

	Matrix* m2 = allocMatrix (4,4);
	float vals[] = {
		3.5, -3.5, 0.1, 2.2, 
		3.5, -3.5, 0.1, 2.2, 
		3.5, -3.5, 0.1, 2.2, 
		3.5, -3.5, 0.1, 2.2 
	};

	int pos = 0;
	for (int i = 0; i < m2->r; ++i) {
		for (int j = 0; j < m2->c; ++j) {
			setValue(m2, i, j, vals[pos]);
			++pos;
		}
	}

	printMatrix (m2);

	Matrix* m3 = addMatrix (m1, m2);
	printMatrix (m3);
	
	Matrix* m4 = subtractMatrix (m3, m1);
	printMatrix (m4);

	Matrix* m5 = multiplyMatrix (m3, m4);
	printMatrix (m5);

	Matrix* m6 = multiplyMatrix (m5, m1);
	printMatrix (m6);

	Matrix* m7 = allocMatrix (2, 3);
	Matrix* m8 = allocMatrix (3, 2);
	
	float vals7[] = {
		1,-1,0,
		-1,1,0
	};
	setValues (m7, vals7);
	printMatrix (m7);

	float vals8[] = {
		1,-1,
		-1,1,
		2,2
	};
	setValues (m8, vals8);
	printMatrix (m8);

	Matrix* m9 = multiplyMatrix (m7, m8);
	printMatrix (m9);

	freeMatrix (m9);
	freeMatrix (m8);
	freeMatrix (m7);
	freeMatrix (m6);
	freeMatrix (m5);
	freeMatrix (m4);
	freeMatrix (m3);
	freeMatrix (m2);
	freeMatrix (m1);

	return EXIT_SUCCESS;
}
 
 
