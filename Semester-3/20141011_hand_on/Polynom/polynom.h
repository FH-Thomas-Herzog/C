/*
 * ploynone.h
 *
 * This header file declares the functions used for calculating polynoms.
 * For further details see function doc.
 *
 *  Created on: Oct 1, 2014
 *      Author: Thomas Herzog
 */


#ifndef PLOYNONE_H_
#define PLOYNONE_H_

#include "common.h"

/**
 * Prints a ploynome in the format '1 + 1x + 1x^2 + ... + nx^n' depending on the given array.
 *
 * int n: the count of elements in the array. last index n - 1
 * double p[]: the array representing the Ploynom where the index represents the power and the value the base.
 */
void PrintPoly(int n, double p[]);

/**
 * Evaluates a polynom via the horner shema and calculates the
 *
 * int x: value for x within the ploynom
 * int n: the count for ploynom parts
 * double p[]: the array representing the polynom
 */
double EvalPoly(int x, int n, double p[]);

/**
 * Calculates the summary of two given polynoms
 *
 * int np: the count of the first polynom parts
 * double p[]: the array representing the first polynom
 * int nq: the count of the second polynom parts
 * double q[]: the array representing the second polynom
 * double r[]: the representing calculated sum of the two polynoms
 */
int PolySum(int np, double p[], int nq, double q[], double (*r)[]);

/**
 * Calculates the product of the two given polynoms.
 *
 * int np: the count of the first polynom parts
 * double p[]: the array representing the first polynom
 * int nq: the count of the second polynom parts
 * double q[]: the array representing the second polynom
 * double r[]: the representing calculated product of the two polynoms
 */
int PolyProd(int np, double p[], int nq, double q[], double (*r)[]);

/**
 * Calculates the product of the two given polynoms via an divide & conquer paradigm.
 *
 * int np: the count of the first polynom parts
 * double p[]: the array representing the first polynom
 * int nq: the count of the second polynom parts
 * double q[]: the array representing the second polynom
 * double r[]: the representing calculated product of the two polynoms
 */
int PolyProdFast(int np, double p[], int nq, double q[], double (*r)[]);

/**
 * Splits the ploynom between the low and high border.
 * int low: the low border of the polynom
 * int high: the hig h border of an polynom
 * double p[]: the polynom to split
 *  double (*r)[]: the split ploynom
 */
int PolySplit(int low, int high, double p[], double (*r)[]);

/**
 * This function calculates the product between an polynom part (E.g.: 4x^3)
 * with an complete polynom (E.g.: 1 + 2x + 5x^2). The calculated product
 * is an new polynom.
 *
 * int grade: the grade of the polynom part
 * double polyPart: the coefficient for he polynom part
 * int n: the count of elements of the array representing the polynom to be multiplied by the polynom part
 * double p[]: the array representing the polynom to be multiplied by the polynom part
 * double (*r)[]: the array which will hold the calculated polynom product
 */
int PolyMultiply(int grade, double polyPart, int n, double p[], double (*r)[]);

#endif /* PLOYNONE_H_ */
