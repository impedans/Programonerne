// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================

#ifndef _LUT_H_
#define _LUT_H_

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

struct TVector {
	long x;
	long y;
};

void printFix(long i);
long expand(long i);
signed short sin(int a);
signed short cos(int a);
void initVector(struct TVector *v, int angle);

#endif	// LUT_H


