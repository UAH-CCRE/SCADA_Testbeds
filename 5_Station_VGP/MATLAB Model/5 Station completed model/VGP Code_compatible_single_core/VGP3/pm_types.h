#ifndef pm_types_h
#define pm_types_h
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct PmSparsityPatternTag PmSparsityPattern; typedef struct
PmRealVectorTag PmRealVector; typedef struct PmIntVectorTag PmIntVector; typedef
struct PmBoolVectorTag PmBoolVector; typedef struct PmCharVectorTag PmCharVector;
struct PmSparsityPatternTag { size_t mNumCol; size_t mNumRow; int32_T *mJc;
int32_T *mIr; }; struct PmRealVectorTag { size_t mN; real_T *mX; }; struct
PmIntVectorTag { size_t mN; int32_T *mX; }; struct PmBoolVectorTag { size_t mN;
boolean_T *mX; }; struct PmCharVectorTag { size_t mN; char *mX; }; typedef struct
PmAllocatorTag PmAllocator; typedef void *(*PmCallocFcn)(PmAllocator *, size_t,
size_t); typedef void (*PmFreeFcn) (PmAllocator *, void *); struct PmAllocatorTag
{ PmCallocFcn mCallocFcn; PmFreeFcn mFreeFcn; };
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* pm_types_h */
