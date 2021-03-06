/*
 * Copyright (c) 2015 Carnegie Mellon University and The Trustees of Indiana
 * University.
 * All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS," WITH NO WARRANTIES WHATSOEVER. CARNEGIE
 * MELLON UNIVERSITY AND THE TRUSTEES OF INDIANA UNIVERSITY EXPRESSLY DISCLAIM
 * TO THE FULLEST EXTENT PERMITTED BY LAW ALL EXPRESS, IMPLIED, AND STATUTORY
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT OF PROPRIETARY RIGHTS.
 *
 * This Program is distributed under a BSD license.  Please see LICENSE file or
 * permission@sei.cmu.edu for more information.  DM-0002659
 */

#include <functional>
#include <iostream>
#include <vector>

#include <graphblas/graphblas.hpp>

using namespace graphblas;

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE ewiseaddmult_suite

#include <boost/test/included/unit_test.hpp>

static ArithmeticSemiring<double> sr;

BOOST_AUTO_TEST_SUITE(ewiseaddmult_suite)

//****************************************************************************
BOOST_AUTO_TEST_CASE(ewiseadd_bad_dimensions)
{
    graphblas::IndexArrayType i_m1    = {0, 0, 1, 1, 2, 2, 3};
    graphblas::IndexArrayType j_m1    = {0, 1, 1, 2, 2, 3, 3};
    std::vector<double> v_m1 = {1, 2, 2, 3, 3, 4, 4};
    Matrix<double, DirectedMatrixTag> m1(4, 4);
    buildmatrix(m1, i_m1, j_m1, v_m1);

    graphblas::IndexArrayType i_m2    = {0, 0, 1, 1, 1, 2, 2, 3};
    graphblas::IndexArrayType j_m2    = {0, 1, 0, 1, 2, 1, 2, 2};
    std::vector<double> v_m2 = {2, 2, 1, 4, 4, 4, 6, 6};
    Matrix<double, DirectedMatrixTag> m2(3, 4);
    buildmatrix(m1, i_m2, j_m2, v_m2);

    Matrix<double, DirectedMatrixTag> m3(4, 4);

    BOOST_CHECK_THROW(
        ewiseadd(m1, m2, m3, graphblas::PlusMonoid<double>()),
        graphblas::DimensionException);
}

//****************************************************************************
BOOST_AUTO_TEST_CASE(ewiseadd_normal)
{
    // Build some sparse matrices.
    graphblas::IndexArrayType i_mat    = {0, 0, 1, 1, 1, 2, 2, 2, 3, 3};
    graphblas::IndexArrayType j_mat    = {0, 1, 0, 1, 2, 1, 2, 3, 2, 3};
    std::vector<double> v_mat = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4};
    Matrix<double, DirectedMatrixTag> mat(4, 4);
    buildmatrix(mat, i_mat, j_mat, v_mat);

    Matrix<double, DirectedMatrixTag> m3(4, 4);

    graphblas::IndexArrayType i_answer    = {0, 0, 1, 1, 1, 2, 2, 2, 3, 3};
    graphblas::IndexArrayType j_answer    = {0, 1, 0, 1, 2, 1, 2, 3, 2, 3};
    std::vector<double> v_answer = {2, 2, 2, 4, 4, 4, 6, 6, 6, 8};
    Matrix<double, DirectedMatrixTag> answer(4, 4);
    buildmatrix(answer, i_answer, j_answer, v_answer);

    // Now try simple's ewiseapply.
    ewiseadd(mat, mat, m3, graphblas::PlusMonoid<double>());

    BOOST_CHECK_EQUAL(m3, answer);
}

//****************************************************************************
BOOST_AUTO_TEST_CASE(ewisemult_bad_dimensions)
{
    graphblas::IndexArrayType i_m1    = {0, 0, 1, 1, 2, 2, 3};
    graphblas::IndexArrayType j_m1    = {0, 1, 1, 2, 2, 3, 3};
    std::vector<double> v_m1 = {1, 2, 2, 3, 3, 4, 4};
    Matrix<double, DirectedMatrixTag> m1(4, 4);
    buildmatrix(m1, i_m1, j_m1, v_m1);

    graphblas::IndexArrayType i_m2    = {0, 0, 1, 1, 1, 2, 2, 3};
    graphblas::IndexArrayType j_m2    = {0, 1, 0, 1, 2, 1, 2, 2};
    std::vector<double> v_m2 = {2, 2, 1, 4, 4, 4, 6, 6};
    Matrix<double, DirectedMatrixTag> m2(3, 4);
    buildmatrix(m1, i_m2, j_m2, v_m2);

    Matrix<double, DirectedMatrixTag> m3(4, 4);

    BOOST_CHECK_THROW(
        ewisemult(m1, m2, m3, graphblas::TimesMonoid<double>()),
        graphblas::DimensionException);
}

//****************************************************************************
BOOST_AUTO_TEST_CASE(ewisemult_normal)
{
    graphblas::IndexArrayType i_mat    = {0, 0, 1, 1, 1, 2, 2, 2, 3, 3};
    graphblas::IndexArrayType j_mat    = {0, 1, 0, 1, 2, 1, 2, 3, 2, 3};
    std::vector<double> v_mat = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4};
    Matrix<double, DirectedMatrixTag> mat(4, 4);
    buildmatrix(mat, i_mat, j_mat, v_mat);

    Matrix<double, DirectedMatrixTag> m3(4, 4);

    graphblas::IndexArrayType i_answer    = {0, 0, 1, 1, 1, 2, 2, 2, 3, 3};
    graphblas::IndexArrayType j_answer    = {0, 1, 0, 1, 2, 1, 2, 3, 2, 3};
    std::vector<double> v_answer = {1, 1, 1, 4, 4, 4, 9, 9, 9, 16};
    Matrix<double, DirectedMatrixTag> answer(4, 4);
    buildmatrix(answer, i_answer, j_answer, v_answer);

    ewisemult(mat, mat, m3, graphblas::TimesMonoid<double>());

    BOOST_CHECK_EQUAL(m3, answer);
}

BOOST_AUTO_TEST_SUITE_END()
