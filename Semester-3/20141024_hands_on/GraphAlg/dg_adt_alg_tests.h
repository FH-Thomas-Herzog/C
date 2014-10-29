/*
 * dg_adt_alg_tests.h
 *
 *	This header file specifies the tests for the dg_adt_alg.h specification
 *
 *  Created on: Oct 19, 2014
 *      Author: cchet
 */

#ifndef DG_ADT_ALG_TESTS_H_
#define DG_ADT_ALG_TESTS_H_

#include "dg_adt.h"

/* ############## Invalid tests ############## */

/* Context control  */
void case1_initContext_null_graph();

void case2_initContext_invalid_size1();

void case3_initContext_invalid_size2();

void case4_initContext_existing_context();

void case5_initContext_graph_not_in_conjunction();

void case6_destroyContext_non_existing_context();

/* isReflexive */
void case7_isReflexive_no_context();

/* isSymetric */
void case8_isSymetric_no_context();

/* isAsymetric */
void case9_isAsymetric_no_context();

/* isTransitiv */
void case10_isTransitiv_no_context();

/* invertGraph */
void case11_invertGraph_null_graph();

void case12_invertGraph_existing_context();

void case13_invertGraph_invalid_size1();

void case14_invertGraph_invalid_size2();

void case15_invertGraph_invalid_size3();

/* printGraphProperties */
void case16_printGraphProperties_null_graph();

/* ############## Valid tests ############## */
void case17_initContext_destroyContext();

void case18_isReflexive_true();

void case19_isSymetric_true();

void case20_isAsymetric_true();

void case21_isTransitive_true();

void case22_isReflexive_false();

void case23_isSymetric_false();

void case24_isAsymetric_false();

void case25_isTransitive_false();

void case26_invertGraph();

void case27_printGraphProperties();

#endif /* DG_ADT_ALG_TESTS_H_ */
