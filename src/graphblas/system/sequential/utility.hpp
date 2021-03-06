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

#pragma once

#ifndef GB_SEQUENTIAL_UTILITY_HPP
#define GB_SEQUENTIAL_UTILITY_HPP

#include <limits>

namespace graphblas
{
    namespace backend_template_library = std;

namespace backend{
    //************************************************************************
    template <typename MatrixA, typename MatrixB>
    void index_of(MatrixA const        &mat,
                  MatrixB              &indexed_of_mat,
                  graphblas::IndexType  base_index)
    {
        graphblas::IndexType rows, cols;
        mat.get_shape(rows, cols);

        using T = typename MatrixA::ScalarType;

        for (IndexType i = 0; i < rows; ++i)
        {
            for (IndexType j = 0; j < cols; ++j)
            {
                auto mat_ij = mat.get_value_at(i, j);
                if (mat_ij > 0 || mat_ij == std::numeric_limits<T>::max())
                {
                    indexed_of_mat.set_value_at(i, j, i + base_index);
                }
                else
                {
                    // FIXME indexed_of_mat.get_zero()?
                    indexed_of_mat.set_value_at(i, j, mat.get_zero());
                }
            }
        }
    }

    //************************************************************************
    template<typename MatrixT>
    void col_index_of(MatrixT &mat)
    {
        graphblas::IndexType rows, cols;
        mat.get_shape(rows, cols);

        for (IndexType i = 0; i < rows; ++i)
        {
            for (IndexType j = 0; j < cols; ++j)
            {
                auto mat_ij = mat.get_value_at(i, j);
                if (mat_ij != mat.get_zero())
                {
                    mat.set_value_at(i, j, j);
                }
            }
        }
    }

    //************************************************************************
    template<typename MatrixT>
    void row_index_of(MatrixT &mat)
    {
        graphblas::IndexType rows, cols;
        mat.get_shape(rows, cols);

        for (IndexType i = 0; i < rows; ++i)
        {
            for (IndexType j = 0; j < cols; ++j)
            {
                auto mat_ij = mat.get_value_at(i, j);
                if (mat_ij != mat.get_zero())
                {
                    mat.set_value_at(i, j, i);
                }
            }
        }
    }

    /**
     *  @brief Output the matrix in array form.  Mainly for debugging
     *         small matrices.
     *
     *  @param[in] ostr  The output stream to send the contents
     *  @param[in] mat   The matrix to output
     *
     */
    template <typename MatrixT>
    void pretty_print_matrix(std::ostream &ostr, MatrixT const &mat)
    {
        IndexType rows, cols;
        mat.get_shape(rows, cols);
        typename MatrixT::ScalarType zero(mat.get_zero());

        for (IndexType row = 0; row < rows; ++row)
        {
            ostr << ((row == 0) ? "[[" : " [");
            if (cols > 0)
            {
                auto val = mat.get_value_at(row, 0);
                if (val == zero)
                    ostr << " ";
                else
                    ostr << val;
            }

            for (IndexType col = 1; col < cols; ++col)
            {
                auto val = mat.get_value_at(row, col);
                if (val == zero)
                    ostr << ",  ";
                else
                    ostr << ", " << val;
            }
            ostr << ((row == rows - 1) ? "]]\n" : "]\n");
        }
    }

} //backend
} // graphblas

#endif // GB_SEQUENTIAL_UTILITY_HPP
