/** This is an example about a lot of cool stuff.
* The comments in this example use a slightly special
* format to make them easy to process into
* doxygen backend stuff.
*/
/* These are the headers that we need to include.
* They are all needed because we say so.
*/
#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>

int main()
{
   /* @exskip 
   * This is ugly stuff to skip for now.
   */
   gmtl::somethingUgly();

   /* @exendskip */
   /** 
   * Example of creating a matrix and doing stuff 
   */
   // Test for allowing this type of comment through.
   gmtl::Matrix44f test_matrix;
   gmtl::invert(test_matrix);
   
   /** Here is an example of creating a Vector */
   gmtl::Vec3f test_vector;
   test_vector += gmtl::Vec3f(1.0, 0.0f, 1.0f);

   /** @subsection multexample Example of multiplication
   * 
   * This is an example of matrix multiplication.
   * We like to do this all the time in the code
   */
   gmtl::Matrix44f mat1, mat2, mat3;
   mat3 = mat1 * mat2;
   // You can do it this way to.
   gmtl::mult(mat3, mat1, mat2);

   return 1;
}
