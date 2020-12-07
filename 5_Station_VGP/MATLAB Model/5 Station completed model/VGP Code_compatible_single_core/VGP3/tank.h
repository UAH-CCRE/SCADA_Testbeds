/*
 * tank.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "tank".
 *
 * Model version              : 1.142
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Tue Jun 28 08:23:50 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_tank_h_
#define RTW_HEADER_tank_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef tank_COMMON_INCLUDES_
# define tank_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "HostLib_Network.h"
#include "nesl_rtw.h"
#include "tank_8a2586ff_1_gateway.h"
#endif                                 /* tank_COMMON_INCLUDES_ */

#include "tank_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmCounterLimit
# define rtmCounterLimit(rtm, idx)     ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals for system '<S2>/Pump Value Conversion' */
typedef struct {
  real_T Subtract;                     /* '<S13>/Subtract' */
} B_PumpValueConversion_tank_T;

/* Block signals for system '<S2>/Valve Value Conversion' */
typedef struct {
  real_T Subtract;                     /* '<S14>/Subtract' */
} B_ValveValueConversion_tank_T;

/* Block signals (auto storage) */
typedef struct {
  real_T dv0[1213];
  real_T TransportDelay3;              /* '<S1>/Transport Delay3' */
  real_T INPUT_1_1_1[4];               /* '<S122>/INPUT_1_1_1' */
  real_T TransportDelay5;              /* '<S1>/Transport Delay5' */
  real_T INPUT_2_1_1[4];               /* '<S122>/INPUT_2_1_1' */
  real_T TransportDelay7;              /* '<S1>/Transport Delay7' */
  real_T INPUT_3_1_1[4];               /* '<S122>/INPUT_3_1_1' */
  real_T TransportDelay15;             /* '<S1>/Transport Delay15' */
  real_T INPUT_4_1_1[4];               /* '<S122>/INPUT_4_1_1' */
  real_T DestinationInletSwitch;       /* '<S1>/Destination Inlet Switch' */
  real_T INPUT_5_1_1[4];               /* '<S122>/INPUT_5_1_1' */
  real_T TransportDelay16;             /* '<S1>/Transport Delay16' */
  real_T INPUT_6_1_1[4];               /* '<S122>/INPUT_6_1_1' */
  real_T DestinationReturnSwitch;      /* '<S1>/Destination Return Switch' */
  real_T INPUT_7_1_1[4];               /* '<S122>/INPUT_7_1_1' */
  real_T rpm;                          /* '<S57>/rpm' */
  real_T rpm1;                         /* '<S57>/rpm1' */
  real_T Switch1;                      /* '<S57>/Switch1' */
  real_T INPUT_8_1_1[4];               /* '<S122>/INPUT_8_1_1' */
  real_T TransportDelay17;             /* '<S1>/Transport Delay17' */
  real_T INPUT_9_1_1[4];               /* '<S122>/INPUT_9_1_1' */
  real_T TransportDelay;               /* '<S1>/Transport Delay' */
  real_T INPUT_10_1_1[4];              /* '<S122>/INPUT_10_1_1' */
  real_T TransportDelay11;             /* '<S1>/Transport Delay11' */
  real_T INPUT_11_1_1[4];              /* '<S122>/INPUT_11_1_1' */
  real_T Sourcetankreturnswitch;       /* '<S1>/Source tank return switch' */
  real_T INPUT_12_1_1[4];              /* '<S122>/INPUT_12_1_1' */
  real_T TransportDelay10;             /* '<S1>/Transport Delay10' */
  real_T INPUT_13_1_1[4];              /* '<S122>/INPUT_13_1_1' */
  real_T SourceTankdespatchswitch;     /* '<S1>/Source Tank despatch switch' */
  real_T INPUT_14_1_1[4];              /* '<S122>/INPUT_14_1_1' */
  real_T rpm2;                         /* '<S69>/rpm2' */
  real_T rpm3;                         /* '<S69>/rpm3' */
  real_T Switch2;                      /* '<S69>/Switch2' */
  real_T INPUT_15_1_1[4];              /* '<S122>/INPUT_15_1_1' */
  real_T TransportDelay12;             /* '<S1>/Transport Delay12' */
  real_T INPUT_16_1_1[4];              /* '<S122>/INPUT_16_1_1' */
  real_T rpm4;                         /* '<S71>/rpm4' */
  real_T rpm5;                         /* '<S71>/rpm5' */
  real_T Switch3;                      /* '<S71>/Switch3' */
  real_T INPUT_17_1_1[4];              /* '<S122>/INPUT_17_1_1' */
  real_T TransportDelay13;             /* '<S1>/Transport Delay13' */
  real_T INPUT_18_1_1[4];              /* '<S122>/INPUT_18_1_1' */
  real_T rpm6;                         /* '<S73>/rpm6' */
  real_T rpm7;                         /* '<S73>/rpm7' */
  real_T Switch4;                      /* '<S73>/Switch4' */
  real_T INPUT_19_1_1[4];              /* '<S122>/INPUT_19_1_1' */
  real_T TransportDelay14;             /* '<S1>/Transport Delay14' */
  real_T INPUT_20_1_1[4];              /* '<S122>/INPUT_20_1_1' */
  real_T rpm8;                         /* '<S75>/rpm8' */
  real_T rpm9;                         /* '<S75>/rpm9' */
  real_T Switch5;                      /* '<S75>/Switch5' */
  real_T INPUT_21_1_1[4];              /* '<S122>/INPUT_21_1_1' */
  real_T TransportDelay9;              /* '<S1>/Transport Delay9' */
  real_T INPUT_22_1_1[4];              /* '<S122>/INPUT_22_1_1' */
  real_T STATE_1[1125];                /* '<S122>/STATE_1' */
  real_T RateTransition;               /* '<S1>/Rate Transition' */
  real_T RateTransition1;              /* '<S1>/Rate Transition1' */
  real_T RateTransition10;             /* '<S1>/Rate Transition10' */
  real_T RateTransition11;             /* '<S1>/Rate Transition11' */
  real_T RateTransition12;             /* '<S1>/Rate Transition12' */
  real_T RateTransition13;             /* '<S1>/Rate Transition13' */
  real_T RateTransition14;             /* '<S1>/Rate Transition14' */
  real_T RateTransition15;             /* '<S1>/Rate Transition15' */
  real_T RateTransition16;             /* '<S1>/Rate Transition16' */
  real_T RateTransition17;             /* '<S1>/Rate Transition17' */
  real_T RateTransition2;              /* '<S1>/Rate Transition2' */
  real_T RateTransition3;              /* '<S1>/Rate Transition3' */
  real_T RateTransition4;              /* '<S1>/Rate Transition4' */
  real_T RateTransition5;              /* '<S1>/Rate Transition5' */
  real_T RateTransition6;              /* '<S1>/Rate Transition6' */
  real_T RateTransition7;              /* '<S1>/Rate Transition7' */
  real_T RateTransition8;              /* '<S1>/Rate Transition8' */
  real_T RateTransition9;              /* '<S1>/Rate Transition9' */
  real_T RateTransition_g;             /* '<S8>/Rate Transition' */
  real_T Add;                          /* '<S29>/Add' */
  real_T RateTransition1_o;            /* '<S8>/Rate Transition1' */
  real_T RateTransition2_p;            /* '<S8>/Rate Transition2' */
  real_T RateTransition3_c;            /* '<S8>/Rate Transition3' */
  real_T RateTransition4_i;            /* '<S8>/Rate Transition4' */
  real_T RateTransition_k;             /* '<S7>/Rate Transition' */
  real_T Add_k;                        /* '<S25>/Add' */
  real_T RateTransition1_k;            /* '<S7>/Rate Transition1' */
  real_T RateTransition_e;             /* '<S6>/Rate Transition' */
  real_T Add_i;                        /* '<S21>/Add' */
  real_T RateTransition1_m;            /* '<S6>/Rate Transition1' */
  real_T RateTransition_n;             /* '<S3>/Rate Transition' */
  real_T Add_l;                        /* '<S16>/Add' */
  real_T RateTransition1_f;            /* '<S3>/Rate Transition1' */
  real_T RateTransition2_h;            /* '<S3>/Rate Transition2' */
  real_T RateTransition3_i;            /* '<S3>/Rate Transition3' */
  real_T RateTransition_o;             /* '<S2>/Rate Transition' */
  real_T Add_n;                        /* '<S12>/Add' */
  real_T RateTransition1_n;            /* '<S2>/Rate Transition1' */
  uint16_T UDPReceive_o2;              /* '<S8>/UDP Receive' */
  uint16_T UDPReceive1_o2;             /* '<S8>/UDP Receive1' */
  uint16_T UDPReceive2_o2;             /* '<S8>/UDP Receive2' */
  uint16_T UDPReceive4_o2;             /* '<S8>/UDP Receive4' */
  uint16_T UDPReceive5_o2;             /* '<S8>/UDP Receive5' */
  uint16_T UDPReceive_o2_g;            /* '<S7>/UDP Receive' */
  uint16_T UDPReceive1_o2_f;           /* '<S7>/UDP Receive1' */
  uint16_T UDPReceive2_o2_d;           /* '<S7>/UDP Receive2' */
  uint16_T UDPReceive_o2_e;            /* '<S6>/UDP Receive' */
  uint16_T UDPReceive1_o2_k;           /* '<S6>/UDP Receive1' */
  uint16_T UDPReceive2_o2_h;           /* '<S6>/UDP Receive2' */
  uint16_T UDPReceive1_o2_ku;          /* '<S3>/UDP Receive1' */
  uint16_T UDPReceive_o2_l;            /* '<S3>/UDP Receive' */
  uint16_T UDPReceive2_o2_m;           /* '<S3>/UDP Receive2' */
  uint16_T UDPReceive3_o2;             /* '<S3>/UDP Receive3' */
  uint16_T UDPReceive_o2_d;            /* '<S2>/UDP Receive' */
  uint16_T UDPReceive1_o2_m;           /* '<S2>/UDP Receive1' */
  uint16_T UDPReceive2_o2_f;           /* '<S2>/UDP Receive2' */
  uint8_T UDPReceive_o1;               /* '<S8>/UDP Receive' */
  uint8_T UDPReceive1_o1;              /* '<S8>/UDP Receive1' */
  uint8_T UDPReceive2_o1;              /* '<S8>/UDP Receive2' */
  uint8_T UDPReceive4_o1;              /* '<S8>/UDP Receive4' */
  uint8_T UDPReceive5_o1;              /* '<S8>/UDP Receive5' */
  uint8_T UDPReceive_o1_n;             /* '<S7>/UDP Receive' */
  uint8_T UDPReceive1_o1_p;            /* '<S7>/UDP Receive1' */
  uint8_T UDPReceive2_o1_j;            /* '<S7>/UDP Receive2' */
  uint8_T UDPReceive_o1_h;             /* '<S6>/UDP Receive' */
  uint8_T UDPReceive1_o1_n;            /* '<S6>/UDP Receive1' */
  uint8_T UDPReceive2_o1_a;            /* '<S6>/UDP Receive2' */
  uint8_T UDPReceive1_o1_i;            /* '<S3>/UDP Receive1' */
  uint8_T UDPReceive_o1_b;             /* '<S3>/UDP Receive' */
  uint8_T UDPReceive2_o1_c;            /* '<S3>/UDP Receive2' */
  uint8_T UDPReceive3_o1;              /* '<S3>/UDP Receive3' */
  uint8_T UDPReceive_o1_b2;            /* '<S2>/UDP Receive' */
  uint8_T UDPReceive1_o1_d;            /* '<S2>/UDP Receive1' */
  uint8_T UDPReceive2_o1_p;            /* '<S2>/UDP Receive2' */
  B_ValveValueConversion_tank_T ValveValueConversion4;/* '<S8>/Valve Value Conversion4' */
  B_ValveValueConversion_tank_T ValveValueConversion3;/* '<S8>/Valve Value Conversion3' */
  B_ValveValueConversion_tank_T ValveValueConversion1_i;/* '<S8>/Valve Value Conversion1' */
  B_ValveValueConversion_tank_T ValveValueConversion_h;/* '<S8>/Valve Value Conversion' */
  B_PumpValueConversion_tank_T PumpValueConversion_j;/* '<S8>/Pump Value Conversion' */
  B_ValveValueConversion_tank_T ValveValueConversion1_m;/* '<S7>/Valve Value Conversion1' */
  B_ValveValueConversion_tank_T ValveValueConversion_g;/* '<S7>/Valve Value Conversion' */
  B_PumpValueConversion_tank_T PumpValueConversion_k;/* '<S7>/Pump Value Conversion' */
  B_ValveValueConversion_tank_T ValveValueConversion1_p;/* '<S6>/Valve Value Conversion1' */
  B_ValveValueConversion_tank_T ValveValueConversion_n;/* '<S6>/Valve Value Conversion' */
  B_PumpValueConversion_tank_T PumpValueConversion_a;/* '<S6>/Pump Value Conversion' */
  B_ValveValueConversion_tank_T ValveValueConversion2;/* '<S3>/Valve Value Conversion2' */
  B_ValveValueConversion_tank_T ValveValueConversion1_d;/* '<S3>/Valve Value Conversion1' */
  B_ValveValueConversion_tank_T ValveValueConversion_d;/* '<S3>/Valve Value Conversion' */
  B_PumpValueConversion_tank_T PumpValueConversion_n;/* '<S3>/Pump Value Conversion' */
  B_ValveValueConversion_tank_T ValveValueConversion1;/* '<S2>/Valve Value Conversion1' */
  B_ValveValueConversion_tank_T ValveValueConversion;/* '<S2>/Valve Value Conversion' */
  B_PumpValueConversion_tank_T PumpValueConversion;/* '<S2>/Pump Value Conversion' */
} B_tank_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T INPUT_1_1_1_discrete[2];      /* '<S122>/INPUT_1_1_1' */
  real_T INPUT_2_1_1_discrete[2];      /* '<S122>/INPUT_2_1_1' */
  real_T INPUT_3_1_1_discrete[2];      /* '<S122>/INPUT_3_1_1' */
  real_T INPUT_4_1_1_discrete[2];      /* '<S122>/INPUT_4_1_1' */
  real_T INPUT_5_1_1_discrete[2];      /* '<S122>/INPUT_5_1_1' */
  real_T INPUT_6_1_1_discrete[2];      /* '<S122>/INPUT_6_1_1' */
  real_T INPUT_7_1_1_discrete[2];      /* '<S122>/INPUT_7_1_1' */
  real_T INPUT_8_1_1_discrete[2];      /* '<S122>/INPUT_8_1_1' */
  real_T INPUT_9_1_1_discrete[2];      /* '<S122>/INPUT_9_1_1' */
  real_T INPUT_10_1_1_discrete[2];     /* '<S122>/INPUT_10_1_1' */
  real_T INPUT_11_1_1_discrete[2];     /* '<S122>/INPUT_11_1_1' */
  real_T INPUT_12_1_1_discrete[2];     /* '<S122>/INPUT_12_1_1' */
  real_T INPUT_13_1_1_discrete[2];     /* '<S122>/INPUT_13_1_1' */
  real_T INPUT_14_1_1_discrete[2];     /* '<S122>/INPUT_14_1_1' */
  real_T INPUT_15_1_1_discrete[2];     /* '<S122>/INPUT_15_1_1' */
  real_T INPUT_16_1_1_discrete[2];     /* '<S122>/INPUT_16_1_1' */
  real_T INPUT_17_1_1_discrete[2];     /* '<S122>/INPUT_17_1_1' */
  real_T INPUT_18_1_1_discrete[2];     /* '<S122>/INPUT_18_1_1' */
  real_T INPUT_19_1_1_discrete[2];     /* '<S122>/INPUT_19_1_1' */
  real_T INPUT_20_1_1_discrete[2];     /* '<S122>/INPUT_20_1_1' */
  real_T INPUT_21_1_1_discrete[2];     /* '<S122>/INPUT_21_1_1' */
  real_T INPUT_22_1_1_discrete[2];     /* '<S122>/INPUT_22_1_1' */
  real_T STATE_1_DiscStates[163];      /* '<S122>/STATE_1' */
  real_T RateTransition_Buffer0;       /* '<S1>/Rate Transition' */
  real_T RateTransition1_Buffer0;      /* '<S1>/Rate Transition1' */
  real_T RateTransition10_Buffer0;     /* '<S1>/Rate Transition10' */
  real_T RateTransition11_Buffer0;     /* '<S1>/Rate Transition11' */
  real_T RateTransition12_Buffer0;     /* '<S1>/Rate Transition12' */
  real_T RateTransition13_Buffer0;     /* '<S1>/Rate Transition13' */
  real_T RateTransition14_Buffer0;     /* '<S1>/Rate Transition14' */
  real_T RateTransition15_Buffer0;     /* '<S1>/Rate Transition15' */
  real_T RateTransition16_Buffer0;     /* '<S1>/Rate Transition16' */
  real_T RateTransition17_Buffer0;     /* '<S1>/Rate Transition17' */
  real_T RateTransition2_Buffer0;      /* '<S1>/Rate Transition2' */
  real_T RateTransition3_Buffer0;      /* '<S1>/Rate Transition3' */
  real_T RateTransition4_Buffer0;      /* '<S1>/Rate Transition4' */
  real_T RateTransition5_Buffer0;      /* '<S1>/Rate Transition5' */
  real_T RateTransition6_Buffer0;      /* '<S1>/Rate Transition6' */
  real_T RateTransition7_Buffer0;      /* '<S1>/Rate Transition7' */
  real_T RateTransition8_Buffer0;      /* '<S1>/Rate Transition8' */
  real_T RateTransition9_Buffer0;      /* '<S1>/Rate Transition9' */
  real_T UDPReceive_NetworkLib[137];   /* '<S8>/UDP Receive' */
  real_T UDPReceive1_NetworkLib[137];  /* '<S8>/UDP Receive1' */
  real_T UDPReceive2_NetworkLib[137];  /* '<S8>/UDP Receive2' */
  real_T UDPReceive4_NetworkLib[137];  /* '<S8>/UDP Receive4' */
  real_T UDPReceive5_NetworkLib[137];  /* '<S8>/UDP Receive5' */
  real_T UDPSend_NetworkLib[137];      /* '<S8>/UDP Send' */
  real_T UDPSend1_NetworkLib[137];     /* '<S8>/UDP Send1' */
  real_T UDPSend2_NetworkLib[137];     /* '<S8>/UDP Send2' */
  real_T UDPSend3_NetworkLib[137];     /* '<S8>/UDP Send3' */
  real_T UDPSend5_NetworkLib[137];     /* '<S8>/UDP Send5' */
  real_T UDPReceive_NetworkLib_m[137]; /* '<S7>/UDP Receive' */
  real_T UDPReceive1_NetworkLib_f[137];/* '<S7>/UDP Receive1' */
  real_T UDPReceive2_NetworkLib_g[137];/* '<S7>/UDP Receive2' */
  real_T UDPSend_NetworkLib_m[137];    /* '<S7>/UDP Send' */
  real_T UDPSend1_NetworkLib_d[137];   /* '<S7>/UDP Send1' */
  real_T UDPReceive_NetworkLib_g[137]; /* '<S6>/UDP Receive' */
  real_T UDPReceive1_NetworkLib_o[137];/* '<S6>/UDP Receive1' */
  real_T UDPReceive2_NetworkLib_a[137];/* '<S6>/UDP Receive2' */
  real_T UDPSend_NetworkLib_o[137];    /* '<S6>/UDP Send' */
  real_T UDPSend1_NetworkLib_m[137];   /* '<S6>/UDP Send1' */
  real_T UDPReceive1_NetworkLib_b[137];/* '<S3>/UDP Receive1' */
  real_T UDPReceive_NetworkLib_h[137]; /* '<S3>/UDP Receive' */
  real_T UDPReceive2_NetworkLib_n[137];/* '<S3>/UDP Receive2' */
  real_T UDPReceive3_NetworkLib[137];  /* '<S3>/UDP Receive3' */
  real_T UDPSend_NetworkLib_g[137];    /* '<S3>/UDP Send' */
  real_T UDPSend1_NetworkLib_k[137];   /* '<S3>/UDP Send1' */
  real_T UDPSend2_NetworkLib_l[137];   /* '<S3>/UDP Send2' */
  real_T UDPSend3_NetworkLib_c[137];   /* '<S3>/UDP Send3' */
  real_T UDPReceive_NetworkLib_p[137]; /* '<S2>/UDP Receive' */
  real_T UDPReceive1_NetworkLib_ou[137];/* '<S2>/UDP Receive1' */
  real_T UDPReceive2_NetworkLib_p[137];/* '<S2>/UDP Receive2' */
  real_T UDPSend_NetworkLib_a[137];    /* '<S2>/UDP Send' */
  real_T UDPSend1_NetworkLib_h[137];   /* '<S2>/UDP Send1' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay3_RWORK;             /* '<S1>/Transport Delay3' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay5_RWORK;             /* '<S1>/Transport Delay5' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay7_RWORK;             /* '<S1>/Transport Delay7' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay15_RWORK;            /* '<S1>/Transport Delay15' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay16_RWORK;            /* '<S1>/Transport Delay16' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay1_RWORK;             /* '<S1>/Transport Delay1' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay17_RWORK;            /* '<S1>/Transport Delay17' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay_RWORK;              /* '<S1>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay11_RWORK;            /* '<S1>/Transport Delay11' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay10_RWORK;            /* '<S1>/Transport Delay10' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay2_RWORK;             /* '<S1>/Transport Delay2' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay12_RWORK;            /* '<S1>/Transport Delay12' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay4_RWORK;             /* '<S1>/Transport Delay4' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay13_RWORK;            /* '<S1>/Transport Delay13' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay6_RWORK;             /* '<S1>/Transport Delay6' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay14_RWORK;            /* '<S1>/Transport Delay14' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay8_RWORK;             /* '<S1>/Transport Delay8' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay9_RWORK;             /* '<S1>/Transport Delay9' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay3_PWORK;             /* '<S1>/Transport Delay3' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay5_PWORK;             /* '<S1>/Transport Delay5' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay7_PWORK;             /* '<S1>/Transport Delay7' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay15_PWORK;            /* '<S1>/Transport Delay15' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay16_PWORK;            /* '<S1>/Transport Delay16' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay1_PWORK;             /* '<S1>/Transport Delay1' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay17_PWORK;            /* '<S1>/Transport Delay17' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S1>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay11_PWORK;            /* '<S1>/Transport Delay11' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay10_PWORK;            /* '<S1>/Transport Delay10' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay2_PWORK;             /* '<S1>/Transport Delay2' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay12_PWORK;            /* '<S1>/Transport Delay12' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay4_PWORK;             /* '<S1>/Transport Delay4' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay13_PWORK;            /* '<S1>/Transport Delay13' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay6_PWORK;             /* '<S1>/Transport Delay6' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay14_PWORK;            /* '<S1>/Transport Delay14' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay8_PWORK;             /* '<S1>/Transport Delay8' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay9_PWORK;             /* '<S1>/Transport Delay9' */

  void* STATE_1_Simulator;             /* '<S122>/STATE_1' */
  void* STATE_1_SimulationData;        /* '<S122>/STATE_1' */
  void* STATE_1_DiagnosticManager;     /* '<S122>/STATE_1' */
  void* STATE_1_Logger;                /* '<S122>/STATE_1' */
  void* STATE_1_SampleTimeIdx;         /* '<S122>/STATE_1' */
  void* OUTPUT_1_0_Simulator;          /* '<S122>/OUTPUT_1_0' */
  void* OUTPUT_1_0_SimulationData;     /* '<S122>/OUTPUT_1_0' */
  void* OUTPUT_1_0_DiagnosticManager;  /* '<S122>/OUTPUT_1_0' */
  void* OUTPUT_1_0_Logger;             /* '<S122>/OUTPUT_1_0' */
  void* OUTPUT_1_0_SampleTimeIdx;      /* '<S122>/OUTPUT_1_0' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay3_IWORK;             /* '<S1>/Transport Delay3' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay5_IWORK;             /* '<S1>/Transport Delay5' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay7_IWORK;             /* '<S1>/Transport Delay7' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay15_IWORK;            /* '<S1>/Transport Delay15' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay16_IWORK;            /* '<S1>/Transport Delay16' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay1_IWORK;             /* '<S1>/Transport Delay1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay17_IWORK;            /* '<S1>/Transport Delay17' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S1>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay11_IWORK;            /* '<S1>/Transport Delay11' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay10_IWORK;            /* '<S1>/Transport Delay10' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay2_IWORK;             /* '<S1>/Transport Delay2' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay12_IWORK;            /* '<S1>/Transport Delay12' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay4_IWORK;             /* '<S1>/Transport Delay4' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay13_IWORK;            /* '<S1>/Transport Delay13' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay6_IWORK;             /* '<S1>/Transport Delay6' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay14_IWORK;            /* '<S1>/Transport Delay14' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay8_IWORK;             /* '<S1>/Transport Delay8' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay9_IWORK;             /* '<S1>/Transport Delay9' */

  int_T STATE_1_Modes[962];            /* '<S122>/STATE_1' */
  boolean_T STATE_1_CallSimulatorOutput;/* '<S122>/STATE_1' */
  boolean_T OUTPUT_1_0_CallSimulatorOutput;/* '<S122>/OUTPUT_1_0' */
} DW_tank_T;

/* Parameters for system: '<S2>/Pump Value Conversion' */
struct P_PumpValueConversion_tank_T_ {
  real_T u_Value;                      /* Expression: 48
                                        * Referenced by: '<S13>/'0''
                                        */
};

/* Parameters for system: '<S2>/Valve Value Conversion' */
struct P_ValveValueConversion_tank_T_ {
  real_T u_Value;                      /* Expression: 48
                                        * Referenced by: '<S14>/'0''
                                        */
};

/* Parameters (auto storage) */
struct P_tank_T_ {
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S10>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S10>/Constant'
                                        */
  real_T Constant1_Value_i;            /* Expression: 0
                                        * Referenced by: '<S9>/Constant1'
                                        */
  real_T Constant_Value_a;             /* Expression: 1
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Constant1_Value_d;            /* Expression: 0
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T Constant_Value_d;             /* Expression: 1
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Constant_Value_l;             /* Expression: 1
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Constant_Value_ai;            /* Expression: 0.001
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant1_Value_f;            /* Expression: 100
                                        * Referenced by: '<S12>/Constant1'
                                        */
  real_T Constant_Value_le;            /* Expression: 0.001
                                        * Referenced by: '<S16>/Constant'
                                        */
  real_T Constant1_Value_g;            /* Expression: 100
                                        * Referenced by: '<S16>/Constant1'
                                        */
  real_T Constant_Value_i;             /* Expression: 0.001
                                        * Referenced by: '<S21>/Constant'
                                        */
  real_T Constant1_Value_c;            /* Expression: 100
                                        * Referenced by: '<S21>/Constant1'
                                        */
  real_T Constant_Value_is;            /* Expression: 0.001
                                        * Referenced by: '<S25>/Constant'
                                        */
  real_T Constant1_Value_gk;           /* Expression: 100
                                        * Referenced by: '<S25>/Constant1'
                                        */
  real_T Constant_Value_e;             /* Expression: 0.001
                                        * Referenced by: '<S29>/Constant'
                                        */
  real_T Constant1_Value_b;            /* Expression: 100
                                        * Referenced by: '<S29>/Constant1'
                                        */
  real_T TransportDelay3_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay3'
                                        */
  real_T TransportDelay3_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay3'
                                        */
  real_T TransportDelay5_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay5'
                                        */
  real_T TransportDelay5_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay5'
                                        */
  real_T TransportDelay7_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay7'
                                        */
  real_T TransportDelay7_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay7'
                                        */
  real_T TransportDelay15_Delay;       /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay15'
                                        */
  real_T TransportDelay15_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay15'
                                        */
  real_T TransportDelay16_Delay;       /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay16'
                                        */
  real_T TransportDelay16_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay16'
                                        */
  real_T rpm_Value;                    /* Expression: 3000
                                        * Referenced by: '<S57>/rpm'
                                        */
  real_T TransportDelay1_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay1'
                                        */
  real_T TransportDelay1_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay1'
                                        */
  real_T rpm1_Value;                   /* Expression: 0
                                        * Referenced by: '<S57>/rpm1'
                                        */
  real_T Switch1_Threshold;            /* Expression: 1
                                        * Referenced by: '<S57>/Switch1'
                                        */
  real_T TransportDelay17_Delay;       /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay17'
                                        */
  real_T TransportDelay17_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay17'
                                        */
  real_T TransportDelay_Delay;         /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay'
                                        */
  real_T TransportDelay_InitOutput;    /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay'
                                        */
  real_T TransportDelay11_Delay;       /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay11'
                                        */
  real_T TransportDelay11_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay11'
                                        */
  real_T TransportDelay10_Delay;       /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay10'
                                        */
  real_T TransportDelay10_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay10'
                                        */
  real_T rpm2_Value;                   /* Expression: 3000
                                        * Referenced by: '<S69>/rpm2'
                                        */
  real_T TransportDelay2_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay2'
                                        */
  real_T TransportDelay2_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay2'
                                        */
  real_T rpm3_Value;                   /* Expression: 0
                                        * Referenced by: '<S69>/rpm3'
                                        */
  real_T Switch2_Threshold;            /* Expression: 1
                                        * Referenced by: '<S69>/Switch2'
                                        */
  real_T TransportDelay12_Delay;       /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay12'
                                        */
  real_T TransportDelay12_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay12'
                                        */
  real_T rpm4_Value;                   /* Expression: 3000
                                        * Referenced by: '<S71>/rpm4'
                                        */
  real_T TransportDelay4_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay4'
                                        */
  real_T TransportDelay4_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay4'
                                        */
  real_T rpm5_Value;                   /* Expression: 0
                                        * Referenced by: '<S71>/rpm5'
                                        */
  real_T Switch3_Threshold;            /* Expression: 1
                                        * Referenced by: '<S71>/Switch3'
                                        */
  real_T TransportDelay13_Delay;       /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay13'
                                        */
  real_T TransportDelay13_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay13'
                                        */
  real_T rpm6_Value;                   /* Expression: 3000
                                        * Referenced by: '<S73>/rpm6'
                                        */
  real_T TransportDelay6_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay6'
                                        */
  real_T TransportDelay6_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay6'
                                        */
  real_T rpm7_Value;                   /* Expression: 0
                                        * Referenced by: '<S73>/rpm7'
                                        */
  real_T Switch4_Threshold;            /* Expression: 1
                                        * Referenced by: '<S73>/Switch4'
                                        */
  real_T TransportDelay14_Delay;       /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay14'
                                        */
  real_T TransportDelay14_InitOutput;  /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay14'
                                        */
  real_T rpm8_Value;                   /* Expression: 3000
                                        * Referenced by: '<S75>/rpm8'
                                        */
  real_T TransportDelay8_Delay;        /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay8'
                                        */
  real_T TransportDelay8_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay8'
                                        */
  real_T rpm9_Value;                   /* Expression: 0
                                        * Referenced by: '<S75>/rpm9'
                                        */
  real_T Switch5_Threshold;            /* Expression: 1
                                        * Referenced by: '<S75>/Switch5'
                                        */
  real_T TransportDelay9_Delay;        /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay9'
                                        */
  real_T TransportDelay9_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay9'
                                        */
  real_T Constant_Value_g;             /* Expression: 3600
                                        * Referenced by: '<S135>/Constant'
                                        */
  real_T Constant_Value_c;             /* Expression: 10
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Constant_Value_n;             /* Expression: 3600
                                        * Referenced by: '<S45>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: 3600
                                        * Referenced by: '<S43>/Constant'
                                        */
  real_T Constant_Value_ad;            /* Expression: 3600
                                        * Referenced by: '<S145>/Constant'
                                        */
  real_T Constant_Value_bp;            /* Expression: 3600
                                        * Referenced by: '<S155>/Constant'
                                        */
  real_T Constant1_Value_n;            /* Expression: 10
                                        * Referenced by: '<S11>/Constant1'
                                        */
  real_T Constant_Value_dw;            /* Expression: 3600
                                        * Referenced by: '<S44>/Constant'
                                        */
  real_T Constant_Value_l4;            /* Expression: 3600
                                        * Referenced by: '<S42>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: 3600
                                        * Referenced by: '<S165>/Constant'
                                        */
  real_T RateTransition_X0;            /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition'
                                        */
  real_T RateTransition1_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition1'
                                        */
  real_T RateTransition10_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition10'
                                        */
  real_T RateTransition11_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition11'
                                        */
  real_T RateTransition12_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition12'
                                        */
  real_T RateTransition13_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition13'
                                        */
  real_T RateTransition14_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition14'
                                        */
  real_T RateTransition15_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition15'
                                        */
  real_T RateTransition16_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition16'
                                        */
  real_T RateTransition17_X0;          /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition17'
                                        */
  real_T RateTransition2_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition2'
                                        */
  real_T RateTransition3_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition3'
                                        */
  real_T RateTransition4_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition4'
                                        */
  real_T RateTransition5_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition5'
                                        */
  real_T RateTransition6_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition6'
                                        */
  real_T RateTransition7_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition7'
                                        */
  real_T RateTransition8_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition8'
                                        */
  real_T RateTransition9_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition9'
                                        */
  uint8_T DestinationInletSwitch_CurrentS;/* Computed Parameter: DestinationInletSwitch_CurrentS
                                           * Referenced by: '<S1>/Destination Inlet Switch'
                                           */
  uint8_T DestinationReturnSwitch_Current;/* Computed Parameter: DestinationReturnSwitch_Current
                                           * Referenced by: '<S1>/Destination Return Switch'
                                           */
  uint8_T Sourcetankreturnswitch_CurrentS;/* Computed Parameter: Sourcetankreturnswitch_CurrentS
                                           * Referenced by: '<S1>/Source tank return switch'
                                           */
  uint8_T SourceTankdespatchswitch_Curren;/* Computed Parameter: SourceTankdespatchswitch_Curren
                                           * Referenced by: '<S1>/Source Tank despatch switch'
                                           */
  P_ValveValueConversion_tank_T ValveValueConversion4;/* '<S8>/Valve Value Conversion4' */
  P_ValveValueConversion_tank_T ValveValueConversion3;/* '<S8>/Valve Value Conversion3' */
  P_ValveValueConversion_tank_T ValveValueConversion1_i;/* '<S8>/Valve Value Conversion1' */
  P_ValveValueConversion_tank_T ValveValueConversion_h;/* '<S8>/Valve Value Conversion' */
  P_PumpValueConversion_tank_T PumpValueConversion_j;/* '<S8>/Pump Value Conversion' */
  P_ValveValueConversion_tank_T ValveValueConversion1_m;/* '<S7>/Valve Value Conversion1' */
  P_ValveValueConversion_tank_T ValveValueConversion_g;/* '<S7>/Valve Value Conversion' */
  P_PumpValueConversion_tank_T PumpValueConversion_k;/* '<S7>/Pump Value Conversion' */
  P_ValveValueConversion_tank_T ValveValueConversion1_p;/* '<S6>/Valve Value Conversion1' */
  P_ValveValueConversion_tank_T ValveValueConversion_n;/* '<S6>/Valve Value Conversion' */
  P_PumpValueConversion_tank_T PumpValueConversion_a;/* '<S6>/Pump Value Conversion' */
  P_ValveValueConversion_tank_T ValveValueConversion2;/* '<S3>/Valve Value Conversion2' */
  P_ValveValueConversion_tank_T ValveValueConversion1_d;/* '<S3>/Valve Value Conversion1' */
  P_ValveValueConversion_tank_T ValveValueConversion_d;/* '<S3>/Valve Value Conversion' */
  P_PumpValueConversion_tank_T PumpValueConversion_n;/* '<S3>/Pump Value Conversion' */
  P_ValveValueConversion_tank_T ValveValueConversion1;/* '<S2>/Valve Value Conversion1' */
  P_ValveValueConversion_tank_T ValveValueConversion;/* '<S2>/Valve Value Conversion' */
  P_PumpValueConversion_tank_T PumpValueConversion;/* '<S2>/Pump Value Conversion' */
};

/* Real-time Model Data Structure */
struct tag_RTM_tank_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    struct {
      uint8_T TID[4];
      uint8_T cLimit[4];
    } TaskCounters;

    struct {
      uint8_T TID1_2;
      uint8_T TID1_3;
    } RateInteraction;

    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[4];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_tank_T tank_P;

/* Block signals (auto storage) */
extern B_tank_T tank_B;

/* Block states (auto storage) */
extern DW_tank_T tank_DW;

/* Model entry point functions */
extern void tank_initialize(void);
extern void tank_step(int_T tid);
extern void tank_terminate(void);

/* Real-time Model object */
extern RT_MODEL_tank_T *const tank_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'tank'
 * '<S1>'   : 'tank/Virtual Gas Pipeline '
 * '<S2>'   : 'tank/Virtual Gas Pipeline /  PLC Station 2'
 * '<S3>'   : 'tank/Virtual Gas Pipeline / PLC Station 1'
 * '<S4>'   : 'tank/Virtual Gas Pipeline /Destination Inlet'
 * '<S5>'   : 'tank/Virtual Gas Pipeline /Destination Return'
 * '<S6>'   : 'tank/Virtual Gas Pipeline /PLC Station 3'
 * '<S7>'   : 'tank/Virtual Gas Pipeline /PLC Station 4'
 * '<S8>'   : 'tank/Virtual Gas Pipeline /PLC Station 5'
 * '<S9>'   : 'tank/Virtual Gas Pipeline /Source Tank despatch'
 * '<S10>'  : 'tank/Virtual Gas Pipeline /Source tank return '
 * '<S11>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline'
 * '<S12>'  : 'tank/Virtual Gas Pipeline /  PLC Station 2/Output Modifier'
 * '<S13>'  : 'tank/Virtual Gas Pipeline /  PLC Station 2/Pump Value Conversion'
 * '<S14>'  : 'tank/Virtual Gas Pipeline /  PLC Station 2/Valve Value Conversion'
 * '<S15>'  : 'tank/Virtual Gas Pipeline /  PLC Station 2/Valve Value Conversion1'
 * '<S16>'  : 'tank/Virtual Gas Pipeline / PLC Station 1/Output Modifier'
 * '<S17>'  : 'tank/Virtual Gas Pipeline / PLC Station 1/Pump Value Conversion'
 * '<S18>'  : 'tank/Virtual Gas Pipeline / PLC Station 1/Valve Value Conversion'
 * '<S19>'  : 'tank/Virtual Gas Pipeline / PLC Station 1/Valve Value Conversion1'
 * '<S20>'  : 'tank/Virtual Gas Pipeline / PLC Station 1/Valve Value Conversion2'
 * '<S21>'  : 'tank/Virtual Gas Pipeline /PLC Station 3/Output Modifier'
 * '<S22>'  : 'tank/Virtual Gas Pipeline /PLC Station 3/Pump Value Conversion'
 * '<S23>'  : 'tank/Virtual Gas Pipeline /PLC Station 3/Valve Value Conversion'
 * '<S24>'  : 'tank/Virtual Gas Pipeline /PLC Station 3/Valve Value Conversion1'
 * '<S25>'  : 'tank/Virtual Gas Pipeline /PLC Station 4/Output Modifier'
 * '<S26>'  : 'tank/Virtual Gas Pipeline /PLC Station 4/Pump Value Conversion'
 * '<S27>'  : 'tank/Virtual Gas Pipeline /PLC Station 4/Valve Value Conversion'
 * '<S28>'  : 'tank/Virtual Gas Pipeline /PLC Station 4/Valve Value Conversion1'
 * '<S29>'  : 'tank/Virtual Gas Pipeline /PLC Station 5/Output Modifier'
 * '<S30>'  : 'tank/Virtual Gas Pipeline /PLC Station 5/Pump Value Conversion'
 * '<S31>'  : 'tank/Virtual Gas Pipeline /PLC Station 5/Valve Value Conversion'
 * '<S32>'  : 'tank/Virtual Gas Pipeline /PLC Station 5/Valve Value Conversion1'
 * '<S33>'  : 'tank/Virtual Gas Pipeline /PLC Station 5/Valve Value Conversion3'
 * '<S34>'  : 'tank/Virtual Gas Pipeline /PLC Station 5/Valve Value Conversion4'
 * '<S35>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve1'
 * '<S36>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve2'
 * '<S37>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve3'
 * '<S38>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve4'
 * '<S39>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve5'
 * '<S40>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve6'
 * '<S41>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve7'
 * '<S42>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)'
 * '<S43>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)1'
 * '<S44>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)2'
 * '<S45>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)3'
 * '<S46>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)4'
 * '<S47>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)5'
 * '<S48>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)6'
 * '<S49>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)7'
 * '<S50>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/PS-Simulink Converter'
 * '<S51>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/PS-Simulink Converter1'
 * '<S52>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor'
 * '<S53>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor1'
 * '<S54>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor2'
 * '<S55>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor3'
 * '<S56>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor4'
 * '<S57>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)'
 * '<S58>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Recirculation valve'
 * '<S59>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Relief Valve 1 '
 * '<S60>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Return line'
 * '<S61>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Return line 1 '
 * '<S62>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Return line1'
 * '<S63>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Return line2'
 * '<S64>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Return line3'
 * '<S65>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Return line body valve'
 * '<S66>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Return line body valve1'
 * '<S67>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Tank Body Valve'
 * '<S68>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Tank Body Valve1'
 * '<S69>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)'
 * '<S70>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 inlet valve'
 * '<S71>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)'
 * '<S72>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 inlet valve'
 * '<S73>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)'
 * '<S74>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 inlet valve'
 * '<S75>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)'
 * '<S76>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 inlet valve'
 * '<S77>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve1/Simulink-PS Converter'
 * '<S78>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve1/Simulink-PS Converter/EVAL_KEY'
 * '<S79>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve2/Simulink-PS Converter'
 * '<S80>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve2/Simulink-PS Converter/EVAL_KEY'
 * '<S81>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve3/Simulink-PS Converter'
 * '<S82>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve3/Simulink-PS Converter/EVAL_KEY'
 * '<S83>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve4/Simulink-PS Converter'
 * '<S84>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve4/Simulink-PS Converter/EVAL_KEY'
 * '<S85>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve5/Simulink-PS Converter'
 * '<S86>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve5/Simulink-PS Converter/EVAL_KEY'
 * '<S87>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve6/Simulink-PS Converter'
 * '<S88>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve6/Simulink-PS Converter/EVAL_KEY'
 * '<S89>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve7/Simulink-PS Converter'
 * '<S90>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Ball Valve7/Simulink-PS Converter/EVAL_KEY'
 * '<S91>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)/PS-Simulink Converter3'
 * '<S92>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)/PS-Simulink Converter3/EVAL_KEY'
 * '<S93>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)1/PS-Simulink Converter3'
 * '<S94>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)1/PS-Simulink Converter3/EVAL_KEY'
 * '<S95>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)2/PS-Simulink Converter3'
 * '<S96>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)2/PS-Simulink Converter3/EVAL_KEY'
 * '<S97>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)3/PS-Simulink Converter3'
 * '<S98>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)3/PS-Simulink Converter3/EVAL_KEY'
 * '<S99>'  : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)4/PS-Simulink Converter3'
 * '<S100>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)4/PS-Simulink Converter3/EVAL_KEY'
 * '<S101>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)5/PS-Simulink Converter3'
 * '<S102>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)5/PS-Simulink Converter3/EVAL_KEY'
 * '<S103>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)6/PS-Simulink Converter3'
 * '<S104>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)6/PS-Simulink Converter3/EVAL_KEY'
 * '<S105>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)7/PS-Simulink Converter3'
 * '<S106>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Flow Measurement (KL//Hr)7/PS-Simulink Converter3/EVAL_KEY'
 * '<S107>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/PS-Simulink Converter/EVAL_KEY'
 * '<S108>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/PS-Simulink Converter1/EVAL_KEY'
 * '<S109>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor/PS-Simulink Converter3'
 * '<S110>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor/PS-Simulink Converter3/EVAL_KEY'
 * '<S111>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor1/PS-Simulink Converter3'
 * '<S112>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor1/PS-Simulink Converter3/EVAL_KEY'
 * '<S113>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor2/PS-Simulink Converter3'
 * '<S114>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor2/PS-Simulink Converter3/EVAL_KEY'
 * '<S115>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor3/PS-Simulink Converter3'
 * '<S116>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor3/PS-Simulink Converter3/EVAL_KEY'
 * '<S117>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor4/PS-Simulink Converter3'
 * '<S118>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Pressure Sensor4/PS-Simulink Converter3/EVAL_KEY'
 * '<S119>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Simulink-PS Converter'
 * '<S120>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration'
 * '<S121>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Simulink-PS Converter/EVAL_KEY'
 * '<S122>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration/EVAL_KEY'
 * '<S123>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Recirculation valve/Simulink-PS Converter'
 * '<S124>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Recirculation valve/Simulink-PS Converter/EVAL_KEY'
 * '<S125>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Relief Valve 1 /Simulink-PS Converter1'
 * '<S126>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Relief Valve 1 /Simulink-PS Converter1/EVAL_KEY'
 * '<S127>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Return line body valve/Simulink-PS Converter'
 * '<S128>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Return line body valve/Simulink-PS Converter/EVAL_KEY'
 * '<S129>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Return line body valve1/Simulink-PS Converter'
 * '<S130>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Return line body valve1/Simulink-PS Converter/EVAL_KEY'
 * '<S131>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Tank Body Valve/Simulink-PS Converter'
 * '<S132>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Tank Body Valve/Simulink-PS Converter/EVAL_KEY'
 * '<S133>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Tank Body Valve1/Simulink-PS Converter'
 * '<S134>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Source Tank Body Valve1/Simulink-PS Converter/EVAL_KEY'
 * '<S135>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Flow Measurement (KL//Hr)'
 * '<S136>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Measurement3'
 * '<S137>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Simulink-PS Converter2'
 * '<S138>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3'
 * '<S139>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3/EVAL_KEY'
 * '<S140>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Measurement3/PS-Simulink Converter3'
 * '<S141>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Measurement3/PS-Simulink Converter3/EVAL_KEY'
 * '<S142>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 (With 3km pipeline)/Simulink-PS Converter2/EVAL_KEY'
 * '<S143>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 inlet valve/Simulink-PS Converter'
 * '<S144>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 2 inlet valve/Simulink-PS Converter/EVAL_KEY'
 * '<S145>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Flow Measurement (KL//Hr)'
 * '<S146>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Measurement2'
 * '<S147>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Simulink-PS Converter3'
 * '<S148>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3'
 * '<S149>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3/EVAL_KEY'
 * '<S150>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Measurement2/PS-Simulink Converter3'
 * '<S151>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Measurement2/PS-Simulink Converter3/EVAL_KEY'
 * '<S152>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 (With 3km pipeline)/Simulink-PS Converter3/EVAL_KEY'
 * '<S153>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 inlet valve/Simulink-PS Converter'
 * '<S154>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 3 inlet valve/Simulink-PS Converter/EVAL_KEY'
 * '<S155>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Flow Measurement (KL//Hr)'
 * '<S156>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Measurement1'
 * '<S157>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Simulink-PS Converter4'
 * '<S158>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3'
 * '<S159>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3/EVAL_KEY'
 * '<S160>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Measurement1/PS-Simulink Converter3'
 * '<S161>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Measurement1/PS-Simulink Converter3/EVAL_KEY'
 * '<S162>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 (With 3km pipeline)/Simulink-PS Converter4/EVAL_KEY'
 * '<S163>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 inlet valve/Simulink-PS Converter'
 * '<S164>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 4 inlet valve/Simulink-PS Converter/EVAL_KEY'
 * '<S165>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Flow Measurement (KL//Hr)'
 * '<S166>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Measurement6'
 * '<S167>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Simulink-PS Converter5'
 * '<S168>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3'
 * '<S169>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Flow Measurement (KL//Hr)/PS-Simulink Converter3/EVAL_KEY'
 * '<S170>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Measurement6/PS-Simulink Converter3'
 * '<S171>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Measurement6/PS-Simulink Converter3/EVAL_KEY'
 * '<S172>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 (With 3km pipeline)/Simulink-PS Converter5/EVAL_KEY'
 * '<S173>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 inlet valve/Simulink-PS Converter'
 * '<S174>' : 'tank/Virtual Gas Pipeline /The Gas Pipeline/Station 5 inlet valve/Simulink-PS Converter/EVAL_KEY'
 */
#endif                                 /* RTW_HEADER_tank_h_ */
