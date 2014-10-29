/*
 * polynome.c
 *
 * This program handles polynoms with different algorithms.
 *
 *  Created on: Oct 1, 2014
 *      Author: Thomas Herzog
 */
#include "polynom.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

int main(int argc, char** argv) {
	double r1[100], r2[100], r3[100];
	double result;
	int n;

	/* The following tests the PrintPoly function */
	printf("---------------------------------------------\n");
	printf("Tests for the printPoly function\n");
	printf("---------------------------------------------\n");

	printf("\nCase 1: { 0, 0, 0 }\n");
	r1[0] = 0.0;
	r1[1] = 0.0;
	r1[2] = 0.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 2: { 1, 0, 0 }\n");
	r1[0] = 1.0;
	r1[1] = 0.0;
	r1[2] = 0.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 3: { 0, 1, 0 }\n");
	r1[0] = 0.0;
	r1[1] = 1.0;
	r1[2] = 0.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 4: { 0, 0, 1 }\n");
	r1[0] = 0.0;
	r1[1] = 0.0;
	r1[2] = 1.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 5: { -1, 0, 0 }\n");
	r1[0] = -1.0;
	r1[1] = 0.0;
	r1[2] = 0.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 6: { 0, -1, 0 }\n");
	r1[0] = 0.0;
	r1[1] = -1.0;
	r1[2] = 0.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 7: { 0, 0, -1 }\n");
	r1[0] = 0.0;
	r1[1] = 0.0;
	r1[2] = -1.0;
	printf("p = ");
	PrintPoly(2, r1);

	printf("\nCase 8: { -12, 0.0, -10.65, -1, 0, -89.25 }\n");
	r1[0] = -12;
	r1[1] = 0.0;
	r1[2] = -10.65;
	r1[3] = -1;
	r1[4] = 0;
	r1[5] = -89.25;
	printf("p = ");
	PrintPoly(5, r1);

	printf("\nCase 9: { 12, 0.0, -10.65, -1, 0, -89.25 }\n");
	r1[0] = 12;
	r1[1] = 0.0;
	r1[2] = -10.65;
	r1[3] = -1;
	r1[4] = 0;
	r1[5] = -89.25;
	printf("p = ");
	PrintPoly(5, r1);

	printf("\nCase 10: { 0.0, 0.0, -10.65, -1, 0, -89.25 }\n");
	r1[0] = 0.0;
	r1[1] = 0.0;
	r1[2] = -10.65;
	r1[3] = -1;
	r1[4] = 0;
	r1[5] = -89.25;
	printf("p = ");
	PrintPoly(5, r1);

	printf("\nCase 11: { 0.0, 0.0, -10.65, 0, -1, 0.0 }\n");
	r1[0] = 0.0;
	r1[1] = 0.0;
	r1[2] = -10.65;
	r1[3] = 0;
	r1[4] = -1;
	r1[5] = 0;
	printf("p = ");
	PrintPoly(5, r1);

	printf("\n\n---------------------------------------------\n");
	printf("Tests for the EvalPoly function\n");
	printf("---------------------------------------------\n");

	printf("\nCase 1:\n");
	r1[0] = 0;
	r1[1] = 0;
	r1[2] = 0;
	n = 2;
	printf("p(%d) = ", n);
	PrintPoly(2, r1);
	result = EvalPoly(n, 2, r1);
	printf("Evaluated to %3.2f\n", result);

	printf("\nCase 2:\n");
	r1[0] = -1;
	r1[1] = 0;
	r1[2] = 0;
	n = 2;
	printf("p(%d) = ", n);
	PrintPoly(2, r1);
	result = EvalPoly(n, 2, r1);
	printf("Evaluated to %3.2f\n", result);

	printf("\nCase 3:\n");
	r1[0] = 0;
	r1[1] = -1;
	r1[2] = 0;
	n = 2;
	printf("p(%d) = ", n);
	PrintPoly(2, r1);
	result = EvalPoly(n, 2, r1);
	printf("Evaluated to %3.2f\n", result);

	printf("\nCase 4:\n");
	r1[0] = 0;
	r1[1] = 0;
	r1[2] = -1;
	n = 2;
	printf("p(%d) = ", n);
	PrintPoly(2, r1);
	result = EvalPoly(n, 2, r1);
	printf("Evaluated to %3.2f\n", result);

	printf("\nCase 5:\n");
	r1[0] = 11;
	r1[1] = 7;
	r1[2] = -5;
	r1[3] = -4;
	r1[4] = 2;
	n = 2;
	printf("p(%d) = ", n);
	PrintPoly(4, r1);
	result = EvalPoly(n, 4, r1);
	printf("Evaluated to %3.2f\n", result);

	printf("\n\n---------------------------------------------\n");
	printf("Tests for the PolySum function\n");
	printf("---------------------------------------------\n");

	printf("\nCase 1: \n");
	r1[0] = 0;
	r1[1] = 0;
	printf("p = ");
	PrintPoly(1, r1);
	r2[0] = 0;
	r2[1] = 0;
	printf("q = ");
	PrintPoly(1, r2);
	printf("p + q = ");
	PrintPoly((PolySum(1, r1, 1, r2, &r3)), r3);

	printf("\nCase 2: \n");
	r1[0] = 0;
	r1[1] = 0;
	printf("p = ");
	PrintPoly(1, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p + q = ");
	PrintPoly((PolySum(1, r1, 3, r2, &r3)), r3);

	printf("\nCase 3: \n");
	r1[0] = 1;
	r1[1] = 2;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 0;
	r2[1] = 0;
	printf("q = ");
	PrintPoly(1, r2);
	printf("p + q = ");
	PrintPoly((PolySum(3, r1, 1, r2, &r3)), r3);

	printf("\nCase 4: \n");
	r1[0] = 1;
	r1[1] = 2;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p + q = ");
	PrintPoly((PolySum(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 5: \n");
	r1[0] = 1;
	r1[1] = 1;
	r1[2] = 3;
	r1[3] = -4;
	r1[4] = 6;
	printf("p = ");
	PrintPoly(4, r1);
	r2[0] = 1;
	r2[1] = 6;
	r2[2] = 6;
	r2[3] = -3;
	r2[4] = 2;
	printf("q = ");
	PrintPoly(4, r2);
	printf("p + q = ");
	PrintPoly((PolySum(4, r1, 4, r2, &r3)), r3);

	printf("\n\n---------------------------------------------\n");
	printf("Tests for the PolyProd function\n");
	printf("---------------------------------------------\n");
	printf("\nCase 1: \n");
	r1[0] = 0;
	r1[1] = 0;
	printf("p = ");
	PrintPoly(1, r1);
	r2[0] = 0;
	r2[1] = 0;
	printf("q = ");
	PrintPoly(1, r2);
	printf("p * q = ");
	PrintPoly((PolyProd(1, r1, 1, r2, &r3)), r3);

	printf("\nCase 2: \n");
	r1[0] = 0;
	r1[1] = 0;
	printf("p = ");
	PrintPoly(1, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p * q = ");
	PrintPoly((PolyProd(1, r1, 3, r2, &r3)), r3);

	printf("\nCase 3: \n");
	r1[0] = 1;
	r1[1] = 2;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 0;
	r2[1] = 0;
	printf("q = ");
	PrintPoly(1, r2);
	printf("p * q = ");
	PrintPoly((PolyProd(3, r1, 1, r2, &r3)), r3);

	printf("\nCase 4: \n");
	r1[0] = 1;
	r1[1] = 2;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p * q = ");
	PrintPoly((PolyProd(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 5: \n");
	r1[0] = 1;
	r1[1] = 1;
	r1[2] = 6;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 6;
	r2[2] = 6;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p + q = ");
	PrintPoly((PolyProd(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 6: \n");
	r1[0] = 1;
	r1[1] = 1;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p + q = ");
	PrintPoly((PolyProd(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 7: \n");
	double p0[16] = { 7, 0, -4, 3, 1, 0, -1, 3, 7, 0, -4, 3, 1, 0, -1, 3 };
	double q0[16] = { -1, 3, -2, 3, 2, -1, 1, -2, 7, 0, -4, 3, 1, 0, -1, 3 };
	printf("p = ");
	PrintPoly(15, p0);
	printf("q = ");
	PrintPoly(15, q0);
	printf("p + q = ");
	PrintPoly((PolyProdFast(15, p0, 15, q0, &r3)), r3);

	printf("\n\n---------------------------------------------\n");
	printf("Tests for the PolyProdFast function\n");
	printf("---------------------------------------------\n");

	printf("\nCase 1: \n");
	r1[0] = 1;
	r1[1] = 2;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p * q = ");
	PrintPoly((PolyProdFast(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 2: \n");
	r1[0] = 1;
	r1[1] = 1;
	r1[2] = 6;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 6;
	r2[2] = 6;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p + q = ");
	PrintPoly((PolyProdFast(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 3: \n");
	r1[0] = 1;
	r1[1] = 1;
	r1[2] = 3;
	r1[3] = -4;
	printf("p = ");
	PrintPoly(3, r1);
	r2[0] = 1;
	r2[1] = 2;
	r2[2] = -5;
	r2[3] = -3;
	printf("q = ");
	PrintPoly(3, r2);
	printf("p + q = ");
	PrintPoly((PolyProdFast(3, r1, 3, r2, &r3)), r3);

	printf("\nCase 4: \n");
	double p[16] = { 7, 0, -4, 3, 1, 0, -1, 3, 7, 0, -4, 3, 1, 0, -1, 3 };
	double q[16] = { -1, 3, -2, 3, 2, -1, 1, -2, 7, 0, -4, 3, 1, 0, -1, 3 };
	printf("p = ");
	PrintPoly(15, p);
	printf("q = ");
	PrintPoly(15, q);
	printf("p + q = ");
	PrintPoly((PolyProdFast(15, p, 15, q, &r3)), r3);

	return EXIT_SUCCESS;

}

void PrintPoly(int n, double p[]) {
	int i;
	double coefficient;
	bool firstPrinted = false;

	for (i = 0; i <= n; ++i) {
		coefficient = p[i];

		/* Need to print part */
		if (coefficient != 0) {
			/* Add correct algebraic sign */
			if ((firstPrinted)) {
				if (coefficient < 0) {
					printf(" - ");
				} else if (firstPrinted) {
					printf(" + ");
				} /* if */
			} /* if */
			/* Print coefficient */
			if ((i == 0) || (fabs(coefficient) != 1)) {
				printf("%g", (!firstPrinted) ? coefficient : fabs(coefficient)); /* only need to consider algebraic sign on first coefficient a0 */
				firstPrinted = true;
			} /* if */
			/* Add exponent */
			if (i > 0) {
				if ((i > 0) && (!firstPrinted) && (coefficient == -1)) {
					printf("-");
				}
				printf("x");
				if (i > 1) {
					printf("^%d", i);
				} /* if */
				firstPrinted = true;
			} /* if */
		} /* if */
	} /* for */

	printf("\n");
}

double EvalPoly(int x, int n, double p[]) {
	int i;
	double result = 0;
	bool firstUsed = false;

	if (n > 0) {
		for (i = (n); i > 0; --i) {
			/* Set result to first coefficient */
			if (!firstUsed) {
				result = p[i];
				firstUsed = true;
			} /* if */
			/* calculate via horner schema */
			result *= x;
			result += p[i - 1];
		} /* for */
	} /* if */

	return result;
}

int PolySum(int np, double p[], int nq, double q[], double (*r)[]) {
	int i, pval, qval, border, grade;

	/* Even result is 0 still valid grade */
	grade = -1;
	/* Border is array with highest grade */
	border = ((np > nq) ? np : nq);
	for (i = 0; i <= border; ++i) {
		/* consider array borders */
		pval = (i <= np) ? p[i] : 0;
		qval = (i <= nq) ? q[i] : 0;
		/* set sum on result */
		(*r)[i] = pval + qval;
		/* Increase grade if no a0 and value on index i != 0 */
		if ((*r)[i] != 0) {
			grade = i;
		} /* if */
	} /* for */

	return grade;
}

int PolyProd(int np, double p[], int nq, double q[], double (*r)[]) {
	int i, rGrade, r1Grade;
	double r1[100];

	rGrade = -1;
	for (i = 0; i <= nq; ++i) {
		r1Grade = PolyMultiply(i, q[i], np, p, &r1);
		rGrade = PolySum(r1Grade, r1, rGrade, *r, r);
	} /* for */

	return rGrade;
}

int PolyProdFast(int np, double p[], int nq, double q[], double (*r)[]) {
	int i, half, grml, grmh, grm, grl, grh, n, gSum;
	double rml[100], rmh[100], rm[100], rl[100], rh[100], rlInv[100],
			rhInv[100], rSum[100];
	/* np and nq are grade */
	n = (np + 1);
	half = (n / 2) - 1;

	grml = PolySum(half, p, half, (p + half + 1), &rml);
	grmh = PolySum(half, q, half, (q + half + 1), &rmh);

	if (n > 4) {
		grl = PolyProdFast(half, p, half, q, &rl);
		grh = PolyProdFast(half, (p + half + 1), half, (q + half + 1), &rh);
		grm = PolyProdFast(grml, rml, grmh, rmh, &rm);
	} else {
		grl = PolyProd(half, p, half, q, &rl);
		grh = PolyProd(half, (p + half + 1), half, (q + half + 1), &rh);
		grm = PolyProd(grml, rml, grmh, rmh, &rm);
	} /* if */

	PolyMultiply(0, -1, grl, rl, &rlInv);
	PolyMultiply(0, -1, grh, rh, &rhInv);
	gSum = PolySum(grl, rlInv, grh, rhInv, &rSum);
	gSum = PolySum(gSum, rSum, grm, rm, &rSum);

	/* Init the result */
	for (i = 0; i <= (n * 2 - 1); i++) {
		(*r)[i] = 0;
	} /* for */

	/* Set the result on the proper index */
	for (i = 0; i <= grl; i++) {
		(*r)[i] = rl[i];
	} /* for */
	for (i = 0; i <= gSum; i++) {
		(*r)[n / 2 + i] += rSum[i];
	} /* for */
	for (i = 0; i <= grh; i++) {
		(*r)[n + i] += rh[i];
	} /* for */
	return n * 2 - 1;
}

int PolySplit(int low, int high, double p[], double (*r)[]) {
	int i, j;
	j = -1;
	for (i = low; i <= high; ++i) {
		j++;
		(*r)[j] = p[i];
	} /* for */
	return j;
}

int PolyMultiply(int grade, double polyPart, int n, double p[], double (*r)[]) {
	int rOldGrade, rGrade, i, j;
	rGrade = 0;
	rOldGrade = -1;

	if (n > 0) {
		for (i = 0; i <= n; ++i) {
			rGrade = i + grade;
			j = rOldGrade + 1;
			/* Need to fill space between parts with 0
			 * E.g.: x^4 + 4x^5
			 * Therefore -> 0x^0, 0x^1, 0x^2, 0x^3 need to be set to 0
			 */
			while (j < rGrade) {
				(*r)[j] = 0;
				++j;
			} /* while */
			rOldGrade = rGrade;
			(*r)[rGrade] = p[i] * polyPart;
		} /* for */
	} /* if */

	return rGrade;
}
