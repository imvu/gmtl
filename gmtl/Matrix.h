// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATRIX_H_
#define _GMTL_MATRIX_H_

#include <gmtl/Defines.h>
#include <gmtl/Math.h>
#include <gmtl/Util/Assert.h>
#include <gmtl/Util/StaticAssert.h>
#include <gmtl/VecBase.h>

namespace gmtl
{

   // Helper to let us define constructors that don't initialize.
   enum Initialization
   {
      Uninitialized
   };

/**
 * NxM dimensional Matrix (ordered in memory by Column)
 *
 * <b>Memory mapping:</b>
 *
 * gmtl::Matrix stores its elements in column major order.
 * That is, it stores each column end-to-end in memory.
 *
 * Typically, for 3D transform matrices, the 3x3 rotation is
 * in the first three columns, while the translation is in the last column.
 *
 * This memory alignment is chosen for compatibility with the OpenGL graphics
 * API and others, which take matrices in this specific column major ordering
 * described above.
 *
 * See the interfaces for operator[r][c] and operator(r,c) for how to iterate
 * over columns and rows for a GMTL Matrix.
 *
 * <b>NOTES on Matrix memory layout and [][] accessors:</b>
 * <ul>
 * <li> gmtl Matrix memory is "column major" ordered, where columns are end
 *      to end in memory, while a C/C++ Matrix accessed the same way
 *      (using operator[][]) as a gmtl Matrix is "row major" ordered.
 *
 * <li> As a result, a gmtl matrix stores elements in memory transposed from
 *      the equivelent matrix defined using an array in the C/C++
 *      language, assuming they are accessed the same way (see example).
 * <ul>
 *    <li> Illustrative Example:                                           <br>
 *         Given two flavors of matrix, C/C++, and gmtl:                   <br>
 *             float cmat[n][m];   and    gmtl::Matrix<float, n, m> mat;   <br>
 *         Writing values into each, while accessing them the same:        <br>
 *             cmat[row][col] = mat[row][col] = some_values[x];            <br>
 *         Then reading values from the matrix array:                      <br>
 *             ((float*)cmat)   and    mat.getData()                       <br>
 *         <i>Will yield pointers to memory containing matrices that are the transpose of each other.</i>
 * </ul>
 * <li> In practice, the differences between GMTL and C/C++ defined matrices
 *      all depends how you iterate over your matrix.                                              <br>
 *      If gmtl is accessed mat[row][col] and C/C++ is accessed mat[col][row], then
 *      memory-wise, these two will yield the same memory mapping (column major as described above),
 *      thus, are equivelent and can both be used interchangably in many popular graphics APIs
 *      such as OpenGL, DirectX, and others.
 *
 * <li> In C/C++ access of a matrix via mat[row][col] yields this memory mapping after using ((float*)mat) to return it:<br>
 *  <pre>
 *    (0,0) (0,1) (0,2) (0,3)   <=== Contiguous memory arranged by row
 *    (1,0) (1,1) (1,2) (1,3)   <=== Contiguous
 *    (2,0) (2,1) (2,2) (2,3)   <=== Contiguous
 *    (3,0) (3,1) (3,2) (3,3)   <=== Contiguous
 *
 *  or linearly if you prefer:
 *    (0,0) (0,1) (0,2) (0,3) (1,0) (1,1) (1,2) (1,3) (2,0) (2,1) (2,2) (2,3) (3,0) (3,1) (3,2) (3,3)
 *  </pre>
 *
 * <li> In gmtl, access of a matrix via mat[row][col] yields this memory mapping after using getData() to return it:<br>
 *  <pre>
 *    (0,0) (0,1) (0,2) (0,3)
 *    (1,0) (1,1) (1,2) (1,3)
 *    (2,0) (2,1) (2,2) (2,3)
 *    (3,0) (3,1) (3,2) (3,3)
 *      ^     ^     ^     ^
 *    --1-----2-----3-----4---- Contiguous memory arranged by column
 *
 *  or linearly if you prefer:
 *    (0,0) (1,0) (2,0) (3,0) (0,1) (1,1) (2,1) (3,1) (0,2) (1,2) (2,2) (3,2) (0,3) (1,3) (2,3) (3,3)
 *  </pre>
 * </ul>
 *
 * @see Matrix44f
 * @see Matrix44d
 * @ingroup Types
 */
template <typename DATA_TYPE, unsigned ROWS, unsigned COLS>
class Matrix
{
public:
   /** use this to declare single value types of the same type as this matrix.
    */
   typedef DATA_TYPE DataType;
   enum Params
   {
      Rows = ROWS, Cols = COLS
   };

   /** Helper class for Matrix op[].
   * This class encapsulates the row that the user is accessing
   * and implements a new op[] that passes the column to use
   */
   class RowAccessor
   {
   public:
      typedef DATA_TYPE DataType;

      GMTL_ALWAYS_INLINE
      RowAccessor(Matrix<DATA_TYPE,ROWS,COLS>* mat, const unsigned row)
         : mMat(mat), mRow(row)
      {
         gmtlASSERT(row < ROWS);
         gmtlASSERT(NULL != mat);
      }

      GMTL_ALWAYS_INLINE
      DATA_TYPE& operator[](const unsigned column)
      {
         gmtlASSERT(column < COLS);
         return (*mMat)(mRow,column);
      }

      Matrix<DATA_TYPE,ROWS,COLS>*  mMat;
      unsigned                      mRow;    /** The row being accessed */
   };

   /** Helper class for Matrix op[] const.
   * This class encapsulates the row that the user is accessing
   * and implements a new op[] that passes the column to use
   */
   class ConstRowAccessor
   {
   public:
      typedef DATA_TYPE DataType;

      GMTL_ALWAYS_INLINE
      ConstRowAccessor( const Matrix<DATA_TYPE,ROWS,COLS>* mat,
                        const unsigned row )
         : mMat( mat ), mRow( row )
      {
         gmtlASSERT( row < ROWS );
         gmtlASSERT( NULL != mat );
      }

      GMTL_ALWAYS_INLINE
      const DATA_TYPE& operator[](const unsigned column) const
      {
         gmtlASSERT(column < COLS);
         return (*mMat)(mRow,column);
      }

      const Matrix<DATA_TYPE,ROWS,COLS>*  mMat;
      unsigned                      mRow;    /** The row being accessed */
   };

   /** Default Constructor (Identity constructor) */
   Matrix()
   {
      for (unsigned int r = 0; r < ROWS; ++r)
      {
         for (unsigned int c = 0; c < COLS; ++c)
         {
            this->operator()(r, c) = static_cast<DATA_TYPE>(0.0);
         }
      }

      for (unsigned int x = 0; x < Math::Min(COLS, ROWS); ++x)
      {
         this->operator()(x, x) = static_cast<DATA_TYPE>(1.0);
      }
   }

   /** constructor that lets us have an uninitialized matrix */
   Matrix( Initialization init )
   {
      gmtlASSERT(init == Uninitialized);
      // Don't need to do anything!
   }

   /** copy constructor */
   Matrix( const Matrix<DATA_TYPE, ROWS, COLS>& matrix )
   {
      this->set( matrix.getData() );
   }

   /** element wise setter for 2x2.
    * @note variable names specify the row,column number to put the data into
    *  @todo needs mp!!
    */
   void set( DATA_TYPE v00, DATA_TYPE v01,
             DATA_TYPE v10, DATA_TYPE v11 )
   {
      GMTL_STATIC_ASSERT( (ROWS == 2 && COLS == 2), Set_called_when_Matrix_not_of_size_2_2 );
      columns[0].set( v00, v10 );
      columns[1].set( v01, v11 );
   }

   /** element wise setter for 2x3.
    * @todo needs mp!!
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12  )
   {
      GMTL_STATIC_ASSERT( (ROWS == 2 && COLS == 3), Set_called_when_Matrix_not_of_size_2_3 );
      getData()[0] = v00;
      getData()[1] = v10;
      getData()[2] = v01;
      getData()[3] = v11;
      getData()[4] = v02;
      getData()[5] = v12;
   }

   /** element wise setter for 3x3.
    * @todo needs mp!!
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12,
             DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22)
   {
      GMTL_STATIC_ASSERT( (ROWS == 3 && COLS == 3), Set_called_when_Matrix_not_of_size_3_3 );
      getData()[0] = v00;
      getData()[1] = v10;
      getData()[2] = v20;

      getData()[3] = v01;
      getData()[4] = v11;
      getData()[5] = v21;

      getData()[6] = v02;
      getData()[7] = v12;
      getData()[8] = v22;
   }

   /** element wise setter for 3x4.
    * @todo needs mp!!  currently no way for a 4x3, ....
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02, DATA_TYPE v03,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12, DATA_TYPE v13,
             DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22, DATA_TYPE v23)
   {
      GMTL_STATIC_ASSERT( (ROWS == 3 && COLS == 4), Set_called_when_Matrix_not_of_size_3_4 );
      getData()[0] = v00;
      getData()[1] = v10;
      getData()[2] = v20;
      getData()[3] = v01;
      getData()[4] = v11;
      getData()[5] = v21;
      getData()[6] = v02;
      getData()[7] = v12;
      getData()[8] = v22;

      // right row
      getData()[9]  = v03;
      getData()[10] = v13;
      getData()[11] = v23;
   }

   /** element wise setter for 4x4.
    * @todo needs mp!!  currently no way for a 4x3, ....
    */
   void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02, DATA_TYPE v03,
             DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12, DATA_TYPE v13,
             DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22, DATA_TYPE v23,
             DATA_TYPE v30, DATA_TYPE v31, DATA_TYPE v32, DATA_TYPE v33 )
   {
      GMTL_STATIC_ASSERT( (ROWS == 4 && COLS == 4), Set_called_when_Matrix_not_of_size_4_4 );
      getData()[0]  = v00;
      getData()[1]  = v10;
      getData()[2]  = v20;
      getData()[4]  = v01;
      getData()[5]  = v11;
      getData()[6]  = v21;
      getData()[8]  = v02;
      getData()[9]  = v12;
      getData()[10] = v22;

      // right row
      getData()[12] = v03;
      getData()[13] = v13;
      getData()[14] = v23;

      // bottom row
      getData()[3]  = v30;
      getData()[7]  = v31;
      getData()[11] = v32;
      getData()[15] = v33;
   }

   /** comma operator
    *  @todo implement this!
    */
   //void operator,()( DATA_TYPE b ) {}

   /** set the matrix to the given data.
    *  This function is useful to copy matrix data from another math library.
    *
    * <h3> "Example (to a matrix using an external math library):" </h3>
    * \code
    *    pfMatrix other_matrix;
    *    other_matrix.setRot( 90, 1, 0, 0 );
    *
    *    gmtl::Matrix44f mat;
    *    mat.set( other_matrix.getFloatPtr() );
    * \endcode
    *
    *  WARNING: this isn't really safe, size and datatype are not enforced by
    *           the compiler.
    * @pre data is in the native format of the gmtl::Matrix class, if not,
    *      then you might be able to use the setTranspose function.
    * @pre i.e. in a 4x4 data[0-3] is the 1st column, data[4-7] is 2nd, etc...
    */
   void set( const DATA_TYPE* data )
   {
      /** @todo mp */
      for (unsigned int x = 0; x < ROWS * COLS; ++x)
         getData()[x] = data[x];
   }

   /** set the matrix to the transpose of the given data.
    * normally set() takes raw matrix data in column by column order,
    * this function allows you to pass in row by row data.
    *
    * Normally you'll use this function if you want to use a float array
    * to init the matrix (see code example).
    *
    * <h3> "Example (to set a [15 -4 20] translation using float array):" </h3>
    * \code
    *    float data[] = { 1, 0, 0, 15,
    *                     0, 1, 0, -4,
    *                     0, 0, 1, 20,
    *                     0, 0, 0, 1   };
    *    gmtl::Matrix44f mat;
    *    mat.setTranspose( data );
    * \endcode
    *
    *  WARNING: this isn't really safe, size and datatype are not enforced by
    *           the compiler.
    * @pre ptr is in the transpose of the native format of the Matrix class
    * @pre i.e. in a 4x4 data[0-3] is the 1st row, data[4-7] is 2nd, etc...
    */
   void setTranspose( const DATA_TYPE* data )
   {
      /** @todo metaprog */
      for (unsigned int r = 0; r < ROWS; ++r)
      for (unsigned int c = 0; c < COLS; ++c)
         this->operator()( r, c ) = data[(r * COLS) + c];
   }

   /** access [row, col] in the matrix
    */
   GMTL_ALWAYS_INLINE
   DATA_TYPE& operator()( const unsigned row, const unsigned column )
   {
      gmtlASSERT( (row < ROWS) && (column < COLS) );
      return columns[column][row];
   }

   /** access [row, col] in the matrix (const version) */
   GMTL_ALWAYS_INLINE
   const DATA_TYPE&  operator()( const unsigned row, const unsigned column ) const
   {
      gmtlASSERT( (row < ROWS) && (column < COLS) );
      return columns[column][row];
   }

   /** bracket operator
    */
   GMTL_ALWAYS_INLINE
   RowAccessor operator[]( const unsigned row )
   {
      return RowAccessor(this, row);
   }

   /** bracket operator (const version) */
   GMTL_ALWAYS_INLINE
   ConstRowAccessor operator[]( const unsigned row ) const
   {
      return ConstRowAccessor( this, row );
   }

   /** Gets a DATA_TYPE pointer to the matrix data.
    * @return Returns a pointer to the head of the matrix data.
    */
   const DATA_TYPE* getData() const
   {
      return columns[0].mData;
   }

   // Unsafe data accessor. See set(), operator[]() for direct access caveats.
   DATA_TYPE* getData()
   {
      return columns[0].mData;
   }

public:
   VecBase<DATA_TYPE, ROWS> columns[COLS];
};

typedef Matrix<float, 2, 2> Matrix22f;
typedef Matrix<double, 2, 2> Matrix22d;
typedef Matrix<float, 2, 3> Matrix23f;
typedef Matrix<double, 2, 3> Matrix23d;
typedef Matrix<float, 3, 3> Matrix33f;
typedef Matrix<double, 3, 3> Matrix33d;
typedef Matrix<float, 3, 4> Matrix34f;
typedef Matrix<double, 3, 4> Matrix34d;
typedef Matrix<float, 4, 4> Matrix44f;
typedef Matrix<double, 4, 4> Matrix44d;

/** 32bit floating point 2x2 identity matrix */
extern const Matrix22f MAT_IDENTITY22F;

/** 64bit floating point 2x2 identity matrix */
extern const Matrix22d MAT_IDENTITY22D;

/** 32bit floating point 2x2 identity matrix */
extern const Matrix23f MAT_IDENTITY23F;

/** 64bit floating point 2x2 identity matrix */
extern const Matrix23d MAT_IDENTITY23D;

/** 32bit floating point 3x3 identity matrix */
extern const Matrix33f MAT_IDENTITY33F;

/** 64bit floating point 3x3 identity matrix */
extern const Matrix33d MAT_IDENTITY33D;

/** 32bit floating point 3x4 identity matrix */
extern const Matrix34f MAT_IDENTITY34F;

/** 64bit floating point 3x4 identity matrix */
extern const Matrix34d MAT_IDENTITY34D;

/** 32bit floating point 4x4 identity matrix */
extern const Matrix44f MAT_IDENTITY44F;

/** 64bit floating point 4x4 identity matrix */
extern const Matrix44d MAT_IDENTITY44D;

} // end namespace gmtl



#endif
