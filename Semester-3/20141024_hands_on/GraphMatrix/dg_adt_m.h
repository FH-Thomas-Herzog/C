/*
 * dg_adt_m.h
 *
 *	This header file defines the Graph type which is used in the implementation and tests,
 *	therefore defined here and not in the implementation itself.
 *
 *  Created on: Oct 17, 2014
 *      Author: cchet
 */

#ifndef DG_ADT_M_H_
#define DG_ADT_M_H_

#include "dg_adt.h"

/* The definition of the graph used in this application */
struct Graph {
	double** matrix;
	int size;
};

#endif /* DG_ADT_M_H_ */
