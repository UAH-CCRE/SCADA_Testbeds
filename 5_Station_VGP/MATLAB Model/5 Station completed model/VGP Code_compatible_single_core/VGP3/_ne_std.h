#ifndef _ne_std_h
#define _ne_std_h
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct NeDynamicSystemTag NeDynamicSystem; typedef uint32_T
NeChecksum[4]; typedef struct NeLoggerBuilderTag NeLoggerBuilder; typedef enum
NeVariabilityTypeTag { NE_INVALID_VARIABILITY = -1 ,NE_CONSTANT_VARIABILITY
,NE_PARAMETRIC_VARIABILITY ,NE_MODAL_VARIABILITY ,NE_FULL_VARIABILITY }
NeVariabilityType; typedef struct NeSystemInputTag { PmIntVector mQ; PmIntVector
mM; PmRealVector mT; PmRealVector mU; PmRealVector mV; PmRealVector mX;
PmRealVector mD; PmIntVector mE; PmIntVector mC; } NeSystemInput; typedef enum
NeSystemInputIdTag { NE_INVALID_SYSTEM_INPUT_ID = -1, NE_SYSTEM_INPUT_ID_Q,
NE_SYSTEM_INPUT_ID_M, NE_SYSTEM_INPUT_ID_T, NE_SYSTEM_INPUT_ID_U,
NE_SYSTEM_INPUT_ID_V, NE_SYSTEM_INPUT_ID_X, NE_SYSTEM_INPUT_ID_D,
NE_SYSTEM_INPUT_ID_E, NE_SYSTEM_INPUT_ID_C, NE_NUM_SYSTEM_INPUT_ID }
NeSystemInputId; typedef struct NeSystemInputSizesTag { size_t mSizes[
NE_NUM_SYSTEM_INPUT_ID ]; } NeSystemInputSizes; typedef struct
NeDynamicSystemInputTag { PmIntVector mQ; PmIntVector mM; PmRealVector mT;
PmRealVector mU; PmRealVector mV; PmRealVector mX; PmRealVector mD; PmIntVector
mE; PmIntVector mC; PmRealVector mW; PmRealVector mS; PmIntVector mP_L;
PmIntVector mP_I; PmIntVector mP_J; PmRealVector mP_R; PmIntVector mDP_L;
PmIntVector mDP_I; PmIntVector mDP_J; PmRealVector mDP_R; } NeDynamicSystemInput;
typedef enum NeDynamicSystemInputIdTag { NE_INVALID_DYNAMIC_SYSTEM_INPUT_ID = -1,
NE_DYNAMIC_SYSTEM_INPUT_ID_Q, NE_DYNAMIC_SYSTEM_INPUT_ID_M,
NE_DYNAMIC_SYSTEM_INPUT_ID_T, NE_DYNAMIC_SYSTEM_INPUT_ID_U,
NE_DYNAMIC_SYSTEM_INPUT_ID_V, NE_DYNAMIC_SYSTEM_INPUT_ID_X,
NE_DYNAMIC_SYSTEM_INPUT_ID_D, NE_DYNAMIC_SYSTEM_INPUT_ID_E,
NE_DYNAMIC_SYSTEM_INPUT_ID_C, NE_DYNAMIC_SYSTEM_INPUT_ID_W,
NE_DYNAMIC_SYSTEM_INPUT_ID_S, NE_DYNAMIC_SYSTEM_INPUT_ID_P_L,
NE_DYNAMIC_SYSTEM_INPUT_ID_P_I, NE_DYNAMIC_SYSTEM_INPUT_ID_P_J,
NE_DYNAMIC_SYSTEM_INPUT_ID_P_R, NE_DYNAMIC_SYSTEM_INPUT_ID_DP_L,
NE_DYNAMIC_SYSTEM_INPUT_ID_DP_I, NE_DYNAMIC_SYSTEM_INPUT_ID_DP_J,
NE_DYNAMIC_SYSTEM_INPUT_ID_DP_R, NE_NUM_DYNAMIC_SYSTEM_INPUT_ID }
NeDynamicSystemInputId; typedef struct NeDynamicSystemInputSizesTag { size_t
mSizes[ NE_NUM_DYNAMIC_SYSTEM_INPUT_ID ]; } NeDynamicSystemInputSizes; typedef
enum NeInitModeTag { NE_INIT_MODE_INVALID = -1, NE_INIT_MODE_DEFAULT,
NE_INIT_MODE_NONE, NE_INIT_MODE_OPTIONAL, NE_INIT_MODE_MANDATORY,
NE_INIT_MODE_NUM } NeInitMode;
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* _ne_std_h */
