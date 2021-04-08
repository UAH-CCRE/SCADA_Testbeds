/*********************************************************************************************************************
 ** File: nesl_la.h
 ** Abstract: RTW Implementation of the Linear Algebra Service for deployed NE solver
 **
 ** Copyright 2007 The MathWorks, Inc.
 *********************************************************************************************************************/

#include "rt_matrixlib.h"
#include <math.h>
#include <string.h>

#ifndef pm_allocator_alloc
#define pm_allocator_alloc(_allocator, _m, _n) ((_allocator)->mCallocFcn((_allocator), (_m), (_n)))
#endif

#ifndef pm_allocator_free
#define pm_allocator_free( _allocator, _ptr)   \
{ \
    void *__allocator_pointer = (_ptr); \
    if (__allocator_pointer != 0) { \
      (_allocator)->mFreeFcn(_allocator, __allocator_pointer); \
    } \
}
#endif
/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)  /* do nothing */
# else
/*
 * This is the semi-ANSI standard way of indicating that a
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x) (void) (x)
# endif
#endif

struct McLinearAlgebraDataTag
{
    int32_T mNumRow;
    int32_T mNumCol;
    real_T* mLU;
    real_T* mLinvB;
    int32_T* mPivotIndices;
    PmAllocator* mAllocatorPtr;
    const PmSparsityPattern* mSparsityPatternPtr;
};

/* Populate full column major matrix from sparsity pattern. Memory is NOT allocated here */
PMF_DEPLOY_STATIC void populate_full_matrix_from_sparsitypattern(real_T* A, const PmSparsityPattern* jacobian_pattern_ptr, const real_T* Ax, PmAllocator* allocatorPtr)
{
    int32_T nRow = (int32_T) jacobian_pattern_ptr->mNumRow;
    int32_T nCol = (int32_T) jacobian_pattern_ptr->mNumCol;
    int32_T* Ap = jacobian_pattern_ptr->mJc;
    int32_T* Ai = jacobian_pattern_ptr->mIr;
    int32_T j = 0;
    int32_T nz = 0;
    
    memset(A, 0, sizeof(real_T)*nRow*nCol);  
    for (j = 0; j<nCol; j++) 
    {
        nz = *(Ap+j+1) - (*(Ap+j));
        while(nz)
        {
            *(A + (*Ai) +(j*nRow)) = *Ax;
            Ai++;
            Ax++;
            nz--;
        }
    }
    UNUSED_PARAMETER(allocatorPtr);
}

/*
  Allocate all memory needed right away, to avoid need for allocation during simulation.
 */
PMF_DEPLOY_STATIC McLinearAlgebraData* rtw_linalg_create_data(PmAllocator* allocatorPtr, const PmSparsityPattern*  jacobian_pattern_ptr)
{
    McLinearAlgebraData* ne_la_data = (McLinearAlgebraData*) pm_allocator_alloc(allocatorPtr, sizeof(McLinearAlgebraData), 1);
    ne_la_data->mSparsityPatternPtr = jacobian_pattern_ptr;
    ne_la_data->mNumRow = (int32_T) jacobian_pattern_ptr->mNumRow;
    ne_la_data->mNumCol = (int32_T) jacobian_pattern_ptr->mNumCol;
    ne_la_data->mAllocatorPtr = allocatorPtr;
    ne_la_data->mLU = (real_T*) 
        pm_allocator_alloc(ne_la_data->mAllocatorPtr, 
                           sizeof(real_T), 
                           jacobian_pattern_ptr->mNumRow * 
                           jacobian_pattern_ptr->mNumCol);

    ne_la_data->mLinvB = (real_T*) 
        pm_allocator_alloc(ne_la_data->mAllocatorPtr, 
                           sizeof(real_T), 
                           jacobian_pattern_ptr->mNumRow);

    ne_la_data->mPivotIndices = 
        (int32_T*) pm_allocator_alloc(ne_la_data->mAllocatorPtr, 
                                      sizeof(int32_T), 
                                      ((((int32_T) jacobian_pattern_ptr->mNumRow) < ne_la_data->mNumCol) ? 
                                       ne_la_data->mNumRow : ne_la_data->mNumCol));
    return ne_la_data;
}

PMF_DEPLOY_STATIC McLinearAlgebraStatus rtw_linalg_symbolic(McLinearAlgebraData* ne_la_data)
{
    UNUSED_PARAMETER(ne_la_data);

    return MC_LA_OK;
}



/* Perform the LU factorization */
PMF_DEPLOY_STATIC McLinearAlgebraStatus rtw_linalg_numeric(McLinearAlgebraData* ne_la_data, const real_T* Ax)
{
    populate_full_matrix_from_sparsitypattern(ne_la_data->mLU, ne_la_data->mSparsityPatternPtr, Ax, ne_la_data->mAllocatorPtr);
    rt_lu_real(ne_la_data->mLU, ne_la_data->mNumRow, ne_la_data->mPivotIndices);
    UNUSED_PARAMETER(Ax);

    /* Check for zeros on the main diagonal */
    {
        int32_T diagLen = ((ne_la_data->mNumRow < ne_la_data->mNumCol) ? ne_la_data->mNumRow : ne_la_data->mNumCol);
        int32_T diagSkip = ne_la_data->mNumRow + 1;
        int32_T diagIdx = 0;
        int32_T i = 0;
        for ( i = 0; i < diagLen; i++) {
            if ( ne_la_data->mLU[diagIdx] == 0.0 ) {
                return MC_LA_ERROR;   /* matrix singular */
            }
            diagIdx += diagSkip;
        }
    }

    return MC_LA_OK;
}

/* solve: forward & back substitution */
PMF_DEPLOY_STATIC McLinearAlgebraStatus rtw_linalg_solve(McLinearAlgebraData* ne_la_data, const real_T* Ax/*not used*/, real_T* dy, const real_T* B)
{
    memcpy(dy, B, ne_la_data->mNumRow*sizeof(real_T));
    rt_ForwardSubstitutionRR_Dbl(ne_la_data->mLU, B, ne_la_data->mLinvB, ne_la_data->mNumRow, 1, ne_la_data->mPivotIndices, true);
    rt_BackwardSubstitutionRR_Dbl(ne_la_data->mLU+((ne_la_data->mNumRow*ne_la_data->mNumRow)-1), ne_la_data->mLinvB+(ne_la_data->mNumRow-1), dy, ne_la_data->mNumRow, 1, false);
    UNUSED_PARAMETER(Ax);
    return MC_LA_OK;
} 


PMF_DEPLOY_STATIC void rtw_linalg_symbolic_free(McLinearAlgebraData* ne_la_data)
{
    UNUSED_PARAMETER(ne_la_data);
}

PMF_DEPLOY_STATIC void rtw_linalg_numeric_free(McLinearAlgebraData* ne_la_data)
{
    UNUSED_PARAMETER(ne_la_data);
}


PMF_DEPLOY_STATIC void rtw_linalg_destroy_data(PmAllocator* allocatorPtr, McLinearAlgebraData* ne_la_data)
{
    pm_allocator_free(ne_la_data->mAllocatorPtr, ne_la_data->mLU);
    ne_la_data->mLU = NULL;
    pm_allocator_free(ne_la_data->mAllocatorPtr, ne_la_data->mLinvB);
    ne_la_data->mLinvB = NULL;

    pm_allocator_free(ne_la_data->mAllocatorPtr, ne_la_data->mPivotIndices);
    ne_la_data->mPivotIndices = NULL;

    ne_la_data->mSparsityPatternPtr = NULL;
    pm_allocator_free(allocatorPtr, ne_la_data);
}

/*! 
 * Returns a static pointer to McLinearAlgebra to be used by the client 
 */
PMF_DEPLOY_STATIC const McLinearAlgebra* get_rtw_linear_algebra(void)
{
    static McLinearAlgebra pMcLinearAlgebra;
    pMcLinearAlgebra.mConstructor = &rtw_linalg_create_data;
    pMcLinearAlgebra.mSymbolic = &rtw_linalg_symbolic; 
    pMcLinearAlgebra.mNumeric = &rtw_linalg_numeric;
    pMcLinearAlgebra.mSolve = &rtw_linalg_solve;
    pMcLinearAlgebra.mNumericDestroy = &rtw_linalg_numeric_free;
    pMcLinearAlgebra.mSymbolicDestroy = &rtw_linalg_symbolic_free;
    pMcLinearAlgebra.mDestructor = &rtw_linalg_destroy_data;
    return &pMcLinearAlgebra;
}
