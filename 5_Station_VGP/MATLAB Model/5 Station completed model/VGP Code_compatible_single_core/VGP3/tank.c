/*
 * tank.c
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

#include "tank.h"
#include "tank_private.h"

/* Block signals (auto storage) */
B_tank_T tank_B;

/* Block states (auto storage) */
DW_tank_T tank_DW;

/* Real-time model */
RT_MODEL_tank_T tank_M_;
RT_MODEL_tank_T *const tank_M = &tank_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 * Output and update for action system:
 *    '<S2>/Pump Value Conversion'
 *    '<S3>/Pump Value Conversion'
 *    '<S6>/Pump Value Conversion'
 *    '<S7>/Pump Value Conversion'
 *    '<S8>/Pump Value Conversion'
 */
void tank_PumpValueConversion(uint8_T rtu_P_ASCII, B_PumpValueConversion_tank_T *
  localB, P_PumpValueConversion_tank_T *localP)
{
  /* Sum: '<S13>/Subtract' incorporates:
   *  Constant: '<S13>/'0''
   */
  localB->Subtract = (real_T)rtu_P_ASCII - localP->u_Value;
}

/*
 * Output and update for action system:
 *    '<S2>/Valve Value Conversion'
 *    '<S2>/Valve Value Conversion1'
 *    '<S3>/Valve Value Conversion'
 *    '<S3>/Valve Value Conversion1'
 *    '<S3>/Valve Value Conversion2'
 *    '<S6>/Valve Value Conversion'
 *    '<S6>/Valve Value Conversion1'
 *    '<S7>/Valve Value Conversion'
 *    '<S7>/Valve Value Conversion1'
 *    '<S8>/Valve Value Conversion'
 *    ...
 */
void tank_ValveValueConversion(uint8_T rtu_V_ASCII,
  B_ValveValueConversion_tank_T *localB, P_ValveValueConversion_tank_T *localP)
{
  /* Sum: '<S14>/Subtract' incorporates:
   *  Constant: '<S14>/'0''
   */
  localB->Subtract = (real_T)rtu_V_ASCII - localP->u_Value;
}

/* Model step function for TID0 */
void tank_step0(void)                  /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_TransportDelay8;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.001s, 0.0s] to Sample time: [0.01s, 0.0s]  */
  (tank_M->Timing.RateInteraction.TID1_2)++;
  if ((tank_M->Timing.RateInteraction.TID1_2) > 9) {
    tank_M->Timing.RateInteraction.TID1_2 = 0;
  }

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.001s, 0.0s] to Sample time: [0.1s, 0.0s]  */
  (tank_M->Timing.RateInteraction.TID1_3)++;
  if ((tank_M->Timing.RateInteraction.TID1_3) > 99) {
    tank_M->Timing.RateInteraction.TID1_3 = 0;
  }

  {
    NeslSimulationData *simulationData;
    real_T time;
    boolean_T tmp;
    real_T tmp_0[88];
    int_T tmp_1[23];
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    int32_T tmp_2;
    char *msg;
    real_T time_0;
    int_T tmp_3[24];
    real_T rtb_OUTPUT_1_0[23];
    real_T rtb_Product;
    real_T rtb_Product_ph;
    real_T rtb_Product_g;
    real_T rtb_Product_e;

    /* TransportDelay: '<S1>/Transport Delay3' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay3_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay3_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay3_Delay;
      tank_B.TransportDelay3 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay3_IWORK.CircularBufSize,
        &tank_DW.TransportDelay3_IWORK.Last,
        tank_DW.TransportDelay3_IWORK.Tail,
        tank_DW.TransportDelay3_IWORK.Head,
        tank_P.TransportDelay3_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_1_1_1' */
    tank_B.INPUT_1_1_1[0] = tank_B.TransportDelay3;
    tank_B.INPUT_1_1_1[1] = 0.0;
    tank_B.INPUT_1_1_1[2] = 0.0;
    tank_B.INPUT_1_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay5' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay5_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay5_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay5_Delay;
      tank_B.TransportDelay5 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay5_IWORK.CircularBufSize,
        &tank_DW.TransportDelay5_IWORK.Last,
        tank_DW.TransportDelay5_IWORK.Tail,
        tank_DW.TransportDelay5_IWORK.Head,
        tank_P.TransportDelay5_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_2_1_1' */
    tank_B.INPUT_2_1_1[0] = tank_B.TransportDelay5;
    tank_B.INPUT_2_1_1[1] = 0.0;
    tank_B.INPUT_2_1_1[2] = 0.0;
    tank_B.INPUT_2_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay7' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay7_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay7_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay7_Delay;
      tank_B.TransportDelay7 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay7_IWORK.CircularBufSize,
        &tank_DW.TransportDelay7_IWORK.Last,
        tank_DW.TransportDelay7_IWORK.Tail,
        tank_DW.TransportDelay7_IWORK.Head,
        tank_P.TransportDelay7_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_3_1_1' */
    tank_B.INPUT_3_1_1[0] = tank_B.TransportDelay7;
    tank_B.INPUT_3_1_1[1] = 0.0;
    tank_B.INPUT_3_1_1[2] = 0.0;
    tank_B.INPUT_3_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay15' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay15_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay15_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay15_Delay;
      tank_B.TransportDelay15 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay15_IWORK.CircularBufSize,
        &tank_DW.TransportDelay15_IWORK.Last,
        tank_DW.TransportDelay15_IWORK.Tail,
        tank_DW.TransportDelay15_IWORK.Head,
        tank_P.TransportDelay15_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_4_1_1' */
    tank_B.INPUT_4_1_1[0] = tank_B.TransportDelay15;
    tank_B.INPUT_4_1_1[1] = 0.0;
    tank_B.INPUT_4_1_1[2] = 0.0;
    tank_B.INPUT_4_1_1[3] = 0.0;

    /* ManualSwitch: '<S1>/Destination Inlet Switch' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     */
    if (tank_P.DestinationInletSwitch_CurrentS == 1) {
      tank_B.DestinationInletSwitch = tank_P.Constant_Value_l;
    } else {
      tank_B.DestinationInletSwitch = tank_P.Constant1_Value_j;
    }

    /* End of ManualSwitch: '<S1>/Destination Inlet Switch' */

    /* SimscapeInputBlock: '<S122>/INPUT_5_1_1' */
    tank_B.INPUT_5_1_1[0] = tank_B.DestinationInletSwitch;
    tank_B.INPUT_5_1_1[1] = 0.0;
    tank_B.INPUT_5_1_1[2] = 0.0;
    tank_DW.INPUT_5_1_1_discrete[0] = !(tank_B.INPUT_5_1_1[0] ==
      tank_DW.INPUT_5_1_1_discrete[1]);
    tank_DW.INPUT_5_1_1_discrete[1] = tank_B.INPUT_5_1_1[0];
    tank_B.INPUT_5_1_1[3] = tank_DW.INPUT_5_1_1_discrete[0];

    /* TransportDelay: '<S1>/Transport Delay16' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay16_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay16_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay16_Delay;
      tank_B.TransportDelay16 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay16_IWORK.CircularBufSize,
        &tank_DW.TransportDelay16_IWORK.Last,
        tank_DW.TransportDelay16_IWORK.Tail,
        tank_DW.TransportDelay16_IWORK.Head,
        tank_P.TransportDelay16_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_6_1_1' */
    tank_B.INPUT_6_1_1[0] = tank_B.TransportDelay16;
    tank_B.INPUT_6_1_1[1] = 0.0;
    tank_B.INPUT_6_1_1[2] = 0.0;
    tank_B.INPUT_6_1_1[3] = 0.0;

    /* ManualSwitch: '<S1>/Destination Return Switch' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    if (tank_P.DestinationReturnSwitch_Current == 1) {
      tank_B.DestinationReturnSwitch = tank_P.Constant_Value_d;
    } else {
      tank_B.DestinationReturnSwitch = tank_P.Constant1_Value_d;
    }

    /* End of ManualSwitch: '<S1>/Destination Return Switch' */

    /* SimscapeInputBlock: '<S122>/INPUT_7_1_1' */
    tank_B.INPUT_7_1_1[0] = tank_B.DestinationReturnSwitch;
    tank_B.INPUT_7_1_1[1] = 0.0;
    tank_B.INPUT_7_1_1[2] = 0.0;
    tank_DW.INPUT_7_1_1_discrete[0] = !(tank_B.INPUT_7_1_1[0] ==
      tank_DW.INPUT_7_1_1_discrete[1]);
    tank_DW.INPUT_7_1_1_discrete[1] = tank_B.INPUT_7_1_1[0];
    tank_B.INPUT_7_1_1[3] = tank_DW.INPUT_7_1_1_discrete[0];

    /* Constant: '<S57>/rpm' */
    tank_B.rpm = tank_P.rpm_Value;

    /* TransportDelay: '<S1>/Transport Delay1' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay1_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay1_Delay;
      rtb_TransportDelay8 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay1_IWORK.CircularBufSize,
        &tank_DW.TransportDelay1_IWORK.Last,
        tank_DW.TransportDelay1_IWORK.Tail,
        tank_DW.TransportDelay1_IWORK.Head,
        tank_P.TransportDelay1_InitOutput,
        1,
        0);
    }

    /* Constant: '<S57>/rpm1' */
    tank_B.rpm1 = tank_P.rpm1_Value;

    /* Switch: '<S57>/Switch1' */
    if (rtb_TransportDelay8 >= tank_P.Switch1_Threshold) {
      tank_B.Switch1 = tank_B.rpm;
    } else {
      tank_B.Switch1 = tank_B.rpm1;
    }

    /* End of Switch: '<S57>/Switch1' */

    /* SimscapeInputBlock: '<S122>/INPUT_8_1_1' */
    tank_B.INPUT_8_1_1[0] = tank_B.Switch1;
    tank_B.INPUT_8_1_1[1] = 0.0;
    tank_B.INPUT_8_1_1[2] = 0.0;
    tank_B.INPUT_8_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay17' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay17_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay17_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay17_Delay;
      tank_B.TransportDelay17 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay17_IWORK.CircularBufSize,
        &tank_DW.TransportDelay17_IWORK.Last,
        tank_DW.TransportDelay17_IWORK.Tail,
        tank_DW.TransportDelay17_IWORK.Head,
        tank_P.TransportDelay17_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_9_1_1' */
    tank_B.INPUT_9_1_1[0] = tank_B.TransportDelay17;
    tank_B.INPUT_9_1_1[1] = 0.0;
    tank_B.INPUT_9_1_1[2] = 0.0;
    tank_B.INPUT_9_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay_Delay;
      tank_B.TransportDelay = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay_IWORK.CircularBufSize,
        &tank_DW.TransportDelay_IWORK.Last,
        tank_DW.TransportDelay_IWORK.Tail,
        tank_DW.TransportDelay_IWORK.Head,
        tank_P.TransportDelay_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_10_1_1' */
    tank_B.INPUT_10_1_1[0] = tank_B.TransportDelay;
    tank_B.INPUT_10_1_1[1] = 0.0;
    tank_B.INPUT_10_1_1[2] = 0.0;
    tank_B.INPUT_10_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay11' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay11_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay11_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay11_Delay;
      tank_B.TransportDelay11 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay11_IWORK.CircularBufSize,
        &tank_DW.TransportDelay11_IWORK.Last,
        tank_DW.TransportDelay11_IWORK.Tail,
        tank_DW.TransportDelay11_IWORK.Head,
        tank_P.TransportDelay11_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_11_1_1' */
    tank_B.INPUT_11_1_1[0] = tank_B.TransportDelay11;
    tank_B.INPUT_11_1_1[1] = 0.0;
    tank_B.INPUT_11_1_1[2] = 0.0;
    tank_B.INPUT_11_1_1[3] = 0.0;

    /* ManualSwitch: '<S1>/Source tank return switch' incorporates:
     *  Constant: '<S10>/Constant'
     *  Constant: '<S10>/Constant1'
     */
    if (tank_P.Sourcetankreturnswitch_CurrentS == 1) {
      tank_B.Sourcetankreturnswitch = tank_P.Constant_Value;
    } else {
      tank_B.Sourcetankreturnswitch = tank_P.Constant1_Value;
    }

    /* End of ManualSwitch: '<S1>/Source tank return switch' */

    /* SimscapeInputBlock: '<S122>/INPUT_12_1_1' */
    tank_B.INPUT_12_1_1[0] = tank_B.Sourcetankreturnswitch;
    tank_B.INPUT_12_1_1[1] = 0.0;
    tank_B.INPUT_12_1_1[2] = 0.0;
    tank_DW.INPUT_12_1_1_discrete[0] = !(tank_B.INPUT_12_1_1[0] ==
      tank_DW.INPUT_12_1_1_discrete[1]);
    tank_DW.INPUT_12_1_1_discrete[1] = tank_B.INPUT_12_1_1[0];
    tank_B.INPUT_12_1_1[3] = tank_DW.INPUT_12_1_1_discrete[0];

    /* TransportDelay: '<S1>/Transport Delay10' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay10_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay10_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay10_Delay;
      tank_B.TransportDelay10 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay10_IWORK.CircularBufSize,
        &tank_DW.TransportDelay10_IWORK.Last,
        tank_DW.TransportDelay10_IWORK.Tail,
        tank_DW.TransportDelay10_IWORK.Head,
        tank_P.TransportDelay10_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_13_1_1' */
    tank_B.INPUT_13_1_1[0] = tank_B.TransportDelay10;
    tank_B.INPUT_13_1_1[1] = 0.0;
    tank_B.INPUT_13_1_1[2] = 0.0;
    tank_B.INPUT_13_1_1[3] = 0.0;

    /* ManualSwitch: '<S1>/Source Tank despatch switch' incorporates:
     *  Constant: '<S9>/Constant'
     *  Constant: '<S9>/Constant1'
     */
    if (tank_P.SourceTankdespatchswitch_Curren == 1) {
      tank_B.SourceTankdespatchswitch = tank_P.Constant_Value_a;
    } else {
      tank_B.SourceTankdespatchswitch = tank_P.Constant1_Value_i;
    }

    /* End of ManualSwitch: '<S1>/Source Tank despatch switch' */

    /* SimscapeInputBlock: '<S122>/INPUT_14_1_1' */
    tank_B.INPUT_14_1_1[0] = tank_B.SourceTankdespatchswitch;
    tank_B.INPUT_14_1_1[1] = 0.0;
    tank_B.INPUT_14_1_1[2] = 0.0;
    tank_DW.INPUT_14_1_1_discrete[0] = !(tank_B.INPUT_14_1_1[0] ==
      tank_DW.INPUT_14_1_1_discrete[1]);
    tank_DW.INPUT_14_1_1_discrete[1] = tank_B.INPUT_14_1_1[0];
    tank_B.INPUT_14_1_1[3] = tank_DW.INPUT_14_1_1_discrete[0];

    /* Constant: '<S69>/rpm2' */
    tank_B.rpm2 = tank_P.rpm2_Value;

    /* TransportDelay: '<S1>/Transport Delay2' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay2_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay2_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay2_Delay;
      rtb_TransportDelay8 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay2_IWORK.CircularBufSize,
        &tank_DW.TransportDelay2_IWORK.Last,
        tank_DW.TransportDelay2_IWORK.Tail,
        tank_DW.TransportDelay2_IWORK.Head,
        tank_P.TransportDelay2_InitOutput,
        1,
        0);
    }

    /* Constant: '<S69>/rpm3' */
    tank_B.rpm3 = tank_P.rpm3_Value;

    /* Switch: '<S69>/Switch2' */
    if (rtb_TransportDelay8 >= tank_P.Switch2_Threshold) {
      tank_B.Switch2 = tank_B.rpm2;
    } else {
      tank_B.Switch2 = tank_B.rpm3;
    }

    /* End of Switch: '<S69>/Switch2' */

    /* SimscapeInputBlock: '<S122>/INPUT_15_1_1' */
    tank_B.INPUT_15_1_1[0] = tank_B.Switch2;
    tank_B.INPUT_15_1_1[1] = 0.0;
    tank_B.INPUT_15_1_1[2] = 0.0;
    tank_B.INPUT_15_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay12' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay12_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay12_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay12_Delay;
      tank_B.TransportDelay12 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay12_IWORK.CircularBufSize,
        &tank_DW.TransportDelay12_IWORK.Last,
        tank_DW.TransportDelay12_IWORK.Tail,
        tank_DW.TransportDelay12_IWORK.Head,
        tank_P.TransportDelay12_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_16_1_1' */
    tank_B.INPUT_16_1_1[0] = tank_B.TransportDelay12;
    tank_B.INPUT_16_1_1[1] = 0.0;
    tank_B.INPUT_16_1_1[2] = 0.0;
    tank_B.INPUT_16_1_1[3] = 0.0;

    /* Constant: '<S71>/rpm4' */
    tank_B.rpm4 = tank_P.rpm4_Value;

    /* TransportDelay: '<S1>/Transport Delay4' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay4_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay4_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay4_Delay;
      rtb_TransportDelay8 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay4_IWORK.CircularBufSize,
        &tank_DW.TransportDelay4_IWORK.Last,
        tank_DW.TransportDelay4_IWORK.Tail,
        tank_DW.TransportDelay4_IWORK.Head,
        tank_P.TransportDelay4_InitOutput,
        1,
        0);
    }

    /* Constant: '<S71>/rpm5' */
    tank_B.rpm5 = tank_P.rpm5_Value;

    /* Switch: '<S71>/Switch3' */
    if (rtb_TransportDelay8 >= tank_P.Switch3_Threshold) {
      tank_B.Switch3 = tank_B.rpm4;
    } else {
      tank_B.Switch3 = tank_B.rpm5;
    }

    /* End of Switch: '<S71>/Switch3' */

    /* SimscapeInputBlock: '<S122>/INPUT_17_1_1' */
    tank_B.INPUT_17_1_1[0] = tank_B.Switch3;
    tank_B.INPUT_17_1_1[1] = 0.0;
    tank_B.INPUT_17_1_1[2] = 0.0;
    tank_B.INPUT_17_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay13' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay13_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay13_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay13_Delay;
      tank_B.TransportDelay13 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay13_IWORK.CircularBufSize,
        &tank_DW.TransportDelay13_IWORK.Last,
        tank_DW.TransportDelay13_IWORK.Tail,
        tank_DW.TransportDelay13_IWORK.Head,
        tank_P.TransportDelay13_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_18_1_1' */
    tank_B.INPUT_18_1_1[0] = tank_B.TransportDelay13;
    tank_B.INPUT_18_1_1[1] = 0.0;
    tank_B.INPUT_18_1_1[2] = 0.0;
    tank_B.INPUT_18_1_1[3] = 0.0;

    /* Constant: '<S73>/rpm6' */
    tank_B.rpm6 = tank_P.rpm6_Value;

    /* TransportDelay: '<S1>/Transport Delay6' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay6_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay6_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay6_Delay;
      rtb_TransportDelay8 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay6_IWORK.CircularBufSize,
        &tank_DW.TransportDelay6_IWORK.Last,
        tank_DW.TransportDelay6_IWORK.Tail,
        tank_DW.TransportDelay6_IWORK.Head,
        tank_P.TransportDelay6_InitOutput,
        1,
        0);
    }

    /* Constant: '<S73>/rpm7' */
    tank_B.rpm7 = tank_P.rpm7_Value;

    /* Switch: '<S73>/Switch4' */
    if (rtb_TransportDelay8 >= tank_P.Switch4_Threshold) {
      tank_B.Switch4 = tank_B.rpm6;
    } else {
      tank_B.Switch4 = tank_B.rpm7;
    }

    /* End of Switch: '<S73>/Switch4' */

    /* SimscapeInputBlock: '<S122>/INPUT_19_1_1' */
    tank_B.INPUT_19_1_1[0] = tank_B.Switch4;
    tank_B.INPUT_19_1_1[1] = 0.0;
    tank_B.INPUT_19_1_1[2] = 0.0;
    tank_B.INPUT_19_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay14' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay14_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay14_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay14_Delay;
      tank_B.TransportDelay14 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay14_IWORK.CircularBufSize,
        &tank_DW.TransportDelay14_IWORK.Last,
        tank_DW.TransportDelay14_IWORK.Tail,
        tank_DW.TransportDelay14_IWORK.Head,
        tank_P.TransportDelay14_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_20_1_1' */
    tank_B.INPUT_20_1_1[0] = tank_B.TransportDelay14;
    tank_B.INPUT_20_1_1[1] = 0.0;
    tank_B.INPUT_20_1_1[2] = 0.0;
    tank_B.INPUT_20_1_1[3] = 0.0;

    /* Constant: '<S75>/rpm8' */
    tank_B.rpm8 = tank_P.rpm8_Value;

    /* TransportDelay: '<S1>/Transport Delay8' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay8_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay8_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay8_Delay;
      rtb_TransportDelay8 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay8_IWORK.CircularBufSize,
        &tank_DW.TransportDelay8_IWORK.Last,
        tank_DW.TransportDelay8_IWORK.Tail,
        tank_DW.TransportDelay8_IWORK.Head,
        tank_P.TransportDelay8_InitOutput,
        1,
        0);
    }

    /* Constant: '<S75>/rpm9' */
    tank_B.rpm9 = tank_P.rpm9_Value;

    /* Switch: '<S75>/Switch5' */
    if (rtb_TransportDelay8 >= tank_P.Switch5_Threshold) {
      tank_B.Switch5 = tank_B.rpm8;
    } else {
      tank_B.Switch5 = tank_B.rpm9;
    }

    /* End of Switch: '<S75>/Switch5' */

    /* SimscapeInputBlock: '<S122>/INPUT_21_1_1' */
    tank_B.INPUT_21_1_1[0] = tank_B.Switch5;
    tank_B.INPUT_21_1_1[1] = 0.0;
    tank_B.INPUT_21_1_1[2] = 0.0;
    tank_B.INPUT_21_1_1[3] = 0.0;

    /* TransportDelay: '<S1>/Transport Delay9' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay9_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay9_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      real_T tMinusDelay = simTime - tank_P.TransportDelay9_Delay;
      tank_B.TransportDelay9 = rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        tank_DW.TransportDelay9_IWORK.CircularBufSize,
        &tank_DW.TransportDelay9_IWORK.Last,
        tank_DW.TransportDelay9_IWORK.Tail,
        tank_DW.TransportDelay9_IWORK.Head,
        tank_P.TransportDelay9_InitOutput,
        1,
        0);
    }

    /* SimscapeInputBlock: '<S122>/INPUT_22_1_1' */
    tank_B.INPUT_22_1_1[0] = tank_B.TransportDelay9;
    tank_B.INPUT_22_1_1[1] = 0.0;
    tank_B.INPUT_22_1_1[2] = 0.0;
    tank_B.INPUT_22_1_1[3] = 0.0;

    /* SimscapeExecutionBlock: '<S122>/STATE_1' */
    simulationData = (NeslSimulationData *)tank_DW.STATE_1_SimulationData;
    time = tank_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 163;
    simulationData->mData->mDiscStates.mX = (real_T *)
      &tank_DW.STATE_1_DiscStates;
    simulationData->mData->mModeVector.mN = 962;
    simulationData->mData->mModeVector.mX = (int32_T *)&tank_DW.STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = true;
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_1[0] = 0;
    tmp_0[0] = tank_B.INPUT_1_1_1[0];
    tmp_0[1] = tank_B.INPUT_1_1_1[1];
    tmp_0[2] = tank_B.INPUT_1_1_1[2];
    tmp_0[3] = tank_B.INPUT_1_1_1[3];
    tmp_1[1] = 4;
    tmp_0[4] = tank_B.INPUT_2_1_1[0];
    tmp_0[5] = tank_B.INPUT_2_1_1[1];
    tmp_0[6] = tank_B.INPUT_2_1_1[2];
    tmp_0[7] = tank_B.INPUT_2_1_1[3];
    tmp_1[2] = 8;
    tmp_0[8] = tank_B.INPUT_3_1_1[0];
    tmp_0[9] = tank_B.INPUT_3_1_1[1];
    tmp_0[10] = tank_B.INPUT_3_1_1[2];
    tmp_0[11] = tank_B.INPUT_3_1_1[3];
    tmp_1[3] = 12;
    tmp_0[12] = tank_B.INPUT_4_1_1[0];
    tmp_0[13] = tank_B.INPUT_4_1_1[1];
    tmp_0[14] = tank_B.INPUT_4_1_1[2];
    tmp_0[15] = tank_B.INPUT_4_1_1[3];
    tmp_1[4] = 16;
    tmp_0[16] = tank_B.INPUT_5_1_1[0];
    tmp_0[17] = tank_B.INPUT_5_1_1[1];
    tmp_0[18] = tank_B.INPUT_5_1_1[2];
    tmp_0[19] = tank_B.INPUT_5_1_1[3];
    tmp_1[5] = 20;
    tmp_0[20] = tank_B.INPUT_6_1_1[0];
    tmp_0[21] = tank_B.INPUT_6_1_1[1];
    tmp_0[22] = tank_B.INPUT_6_1_1[2];
    tmp_0[23] = tank_B.INPUT_6_1_1[3];
    tmp_1[6] = 24;
    tmp_0[24] = tank_B.INPUT_7_1_1[0];
    tmp_0[25] = tank_B.INPUT_7_1_1[1];
    tmp_0[26] = tank_B.INPUT_7_1_1[2];
    tmp_0[27] = tank_B.INPUT_7_1_1[3];
    tmp_1[7] = 28;
    tmp_0[28] = tank_B.INPUT_8_1_1[0];
    tmp_0[29] = tank_B.INPUT_8_1_1[1];
    tmp_0[30] = tank_B.INPUT_8_1_1[2];
    tmp_0[31] = tank_B.INPUT_8_1_1[3];
    tmp_1[8] = 32;
    tmp_0[32] = tank_B.INPUT_9_1_1[0];
    tmp_0[33] = tank_B.INPUT_9_1_1[1];
    tmp_0[34] = tank_B.INPUT_9_1_1[2];
    tmp_0[35] = tank_B.INPUT_9_1_1[3];
    tmp_1[9] = 36;
    tmp_0[36] = tank_B.INPUT_10_1_1[0];
    tmp_0[37] = tank_B.INPUT_10_1_1[1];
    tmp_0[38] = tank_B.INPUT_10_1_1[2];
    tmp_0[39] = tank_B.INPUT_10_1_1[3];
    tmp_1[10] = 40;
    tmp_0[40] = tank_B.INPUT_11_1_1[0];
    tmp_0[41] = tank_B.INPUT_11_1_1[1];
    tmp_0[42] = tank_B.INPUT_11_1_1[2];
    tmp_0[43] = tank_B.INPUT_11_1_1[3];
    tmp_1[11] = 44;
    tmp_0[44] = tank_B.INPUT_12_1_1[0];
    tmp_0[45] = tank_B.INPUT_12_1_1[1];
    tmp_0[46] = tank_B.INPUT_12_1_1[2];
    tmp_0[47] = tank_B.INPUT_12_1_1[3];
    tmp_1[12] = 48;
    tmp_0[48] = tank_B.INPUT_13_1_1[0];
    tmp_0[49] = tank_B.INPUT_13_1_1[1];
    tmp_0[50] = tank_B.INPUT_13_1_1[2];
    tmp_0[51] = tank_B.INPUT_13_1_1[3];
    tmp_1[13] = 52;
    tmp_0[52] = tank_B.INPUT_14_1_1[0];
    tmp_0[53] = tank_B.INPUT_14_1_1[1];
    tmp_0[54] = tank_B.INPUT_14_1_1[2];
    tmp_0[55] = tank_B.INPUT_14_1_1[3];
    tmp_1[14] = 56;
    tmp_0[56] = tank_B.INPUT_15_1_1[0];
    tmp_0[57] = tank_B.INPUT_15_1_1[1];
    tmp_0[58] = tank_B.INPUT_15_1_1[2];
    tmp_0[59] = tank_B.INPUT_15_1_1[3];
    tmp_1[15] = 60;
    tmp_0[60] = tank_B.INPUT_16_1_1[0];
    tmp_0[61] = tank_B.INPUT_16_1_1[1];
    tmp_0[62] = tank_B.INPUT_16_1_1[2];
    tmp_0[63] = tank_B.INPUT_16_1_1[3];
    tmp_1[16] = 64;
    tmp_0[64] = tank_B.INPUT_17_1_1[0];
    tmp_0[65] = tank_B.INPUT_17_1_1[1];
    tmp_0[66] = tank_B.INPUT_17_1_1[2];
    tmp_0[67] = tank_B.INPUT_17_1_1[3];
    tmp_1[17] = 68;
    tmp_0[68] = tank_B.INPUT_18_1_1[0];
    tmp_0[69] = tank_B.INPUT_18_1_1[1];
    tmp_0[70] = tank_B.INPUT_18_1_1[2];
    tmp_0[71] = tank_B.INPUT_18_1_1[3];
    tmp_1[18] = 72;
    tmp_0[72] = tank_B.INPUT_19_1_1[0];
    tmp_0[73] = tank_B.INPUT_19_1_1[1];
    tmp_0[74] = tank_B.INPUT_19_1_1[2];
    tmp_0[75] = tank_B.INPUT_19_1_1[3];
    tmp_1[19] = 76;
    tmp_0[76] = tank_B.INPUT_20_1_1[0];
    tmp_0[77] = tank_B.INPUT_20_1_1[1];
    tmp_0[78] = tank_B.INPUT_20_1_1[2];
    tmp_0[79] = tank_B.INPUT_20_1_1[3];
    tmp_1[20] = 80;
    tmp_0[80] = tank_B.INPUT_21_1_1[0];
    tmp_0[81] = tank_B.INPUT_21_1_1[1];
    tmp_0[82] = tank_B.INPUT_21_1_1[2];
    tmp_0[83] = tank_B.INPUT_21_1_1[3];
    tmp_1[21] = 84;
    tmp_0[84] = tank_B.INPUT_22_1_1[0];
    tmp_0[85] = tank_B.INPUT_22_1_1[1];
    tmp_0[86] = tank_B.INPUT_22_1_1[2];
    tmp_0[87] = tank_B.INPUT_22_1_1[3];
    tmp_1[22] = 88;
    simulationData->mData->mInputValues.mN = 88;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 23;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    simulationData->mData->mOutputs.mN = 1125;
    simulationData->mData->mOutputs.mX = &tank_B.STATE_1[0];
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    tmp = 1;
    simulationData->mData->mIsFundamentalSampleHit = tmp;
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method((NeslSimulator *)tank_DW.STATE_1_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(tank_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    /* End of SimscapeExecutionBlock: '<S122>/STATE_1' */

    /* SimscapeExecutionBlock: '<S122>/OUTPUT_1_0' */
    simulationData = (NeslSimulationData *)tank_DW.OUTPUT_1_0_SimulationData;
    time_0 = tank_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = NULL;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = NULL;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = true;
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_3[0] = 0;
    tank_B.dv0[0] = tank_B.INPUT_1_1_1[0];
    tank_B.dv0[1] = tank_B.INPUT_1_1_1[1];
    tank_B.dv0[2] = tank_B.INPUT_1_1_1[2];
    tank_B.dv0[3] = tank_B.INPUT_1_1_1[3];
    tmp_3[1] = 4;
    tank_B.dv0[4] = tank_B.INPUT_2_1_1[0];
    tank_B.dv0[5] = tank_B.INPUT_2_1_1[1];
    tank_B.dv0[6] = tank_B.INPUT_2_1_1[2];
    tank_B.dv0[7] = tank_B.INPUT_2_1_1[3];
    tmp_3[2] = 8;
    tank_B.dv0[8] = tank_B.INPUT_3_1_1[0];
    tank_B.dv0[9] = tank_B.INPUT_3_1_1[1];
    tank_B.dv0[10] = tank_B.INPUT_3_1_1[2];
    tank_B.dv0[11] = tank_B.INPUT_3_1_1[3];
    tmp_3[3] = 12;
    tank_B.dv0[12] = tank_B.INPUT_4_1_1[0];
    tank_B.dv0[13] = tank_B.INPUT_4_1_1[1];
    tank_B.dv0[14] = tank_B.INPUT_4_1_1[2];
    tank_B.dv0[15] = tank_B.INPUT_4_1_1[3];
    tmp_3[4] = 16;
    tank_B.dv0[16] = tank_B.INPUT_5_1_1[0];
    tank_B.dv0[17] = tank_B.INPUT_5_1_1[1];
    tank_B.dv0[18] = tank_B.INPUT_5_1_1[2];
    tank_B.dv0[19] = tank_B.INPUT_5_1_1[3];
    tmp_3[5] = 20;
    tank_B.dv0[20] = tank_B.INPUT_6_1_1[0];
    tank_B.dv0[21] = tank_B.INPUT_6_1_1[1];
    tank_B.dv0[22] = tank_B.INPUT_6_1_1[2];
    tank_B.dv0[23] = tank_B.INPUT_6_1_1[3];
    tmp_3[6] = 24;
    tank_B.dv0[24] = tank_B.INPUT_7_1_1[0];
    tank_B.dv0[25] = tank_B.INPUT_7_1_1[1];
    tank_B.dv0[26] = tank_B.INPUT_7_1_1[2];
    tank_B.dv0[27] = tank_B.INPUT_7_1_1[3];
    tmp_3[7] = 28;
    tank_B.dv0[28] = tank_B.INPUT_8_1_1[0];
    tank_B.dv0[29] = tank_B.INPUT_8_1_1[1];
    tank_B.dv0[30] = tank_B.INPUT_8_1_1[2];
    tank_B.dv0[31] = tank_B.INPUT_8_1_1[3];
    tmp_3[8] = 32;
    tank_B.dv0[32] = tank_B.INPUT_9_1_1[0];
    tank_B.dv0[33] = tank_B.INPUT_9_1_1[1];
    tank_B.dv0[34] = tank_B.INPUT_9_1_1[2];
    tank_B.dv0[35] = tank_B.INPUT_9_1_1[3];
    tmp_3[9] = 36;
    tank_B.dv0[36] = tank_B.INPUT_10_1_1[0];
    tank_B.dv0[37] = tank_B.INPUT_10_1_1[1];
    tank_B.dv0[38] = tank_B.INPUT_10_1_1[2];
    tank_B.dv0[39] = tank_B.INPUT_10_1_1[3];
    tmp_3[10] = 40;
    tank_B.dv0[40] = tank_B.INPUT_11_1_1[0];
    tank_B.dv0[41] = tank_B.INPUT_11_1_1[1];
    tank_B.dv0[42] = tank_B.INPUT_11_1_1[2];
    tank_B.dv0[43] = tank_B.INPUT_11_1_1[3];
    tmp_3[11] = 44;
    tank_B.dv0[44] = tank_B.INPUT_12_1_1[0];
    tank_B.dv0[45] = tank_B.INPUT_12_1_1[1];
    tank_B.dv0[46] = tank_B.INPUT_12_1_1[2];
    tank_B.dv0[47] = tank_B.INPUT_12_1_1[3];
    tmp_3[12] = 48;
    tank_B.dv0[48] = tank_B.INPUT_13_1_1[0];
    tank_B.dv0[49] = tank_B.INPUT_13_1_1[1];
    tank_B.dv0[50] = tank_B.INPUT_13_1_1[2];
    tank_B.dv0[51] = tank_B.INPUT_13_1_1[3];
    tmp_3[13] = 52;
    tank_B.dv0[52] = tank_B.INPUT_14_1_1[0];
    tank_B.dv0[53] = tank_B.INPUT_14_1_1[1];
    tank_B.dv0[54] = tank_B.INPUT_14_1_1[2];
    tank_B.dv0[55] = tank_B.INPUT_14_1_1[3];
    tmp_3[14] = 56;
    tank_B.dv0[56] = tank_B.INPUT_15_1_1[0];
    tank_B.dv0[57] = tank_B.INPUT_15_1_1[1];
    tank_B.dv0[58] = tank_B.INPUT_15_1_1[2];
    tank_B.dv0[59] = tank_B.INPUT_15_1_1[3];
    tmp_3[15] = 60;
    tank_B.dv0[60] = tank_B.INPUT_16_1_1[0];
    tank_B.dv0[61] = tank_B.INPUT_16_1_1[1];
    tank_B.dv0[62] = tank_B.INPUT_16_1_1[2];
    tank_B.dv0[63] = tank_B.INPUT_16_1_1[3];
    tmp_3[16] = 64;
    tank_B.dv0[64] = tank_B.INPUT_17_1_1[0];
    tank_B.dv0[65] = tank_B.INPUT_17_1_1[1];
    tank_B.dv0[66] = tank_B.INPUT_17_1_1[2];
    tank_B.dv0[67] = tank_B.INPUT_17_1_1[3];
    tmp_3[17] = 68;
    tank_B.dv0[68] = tank_B.INPUT_18_1_1[0];
    tank_B.dv0[69] = tank_B.INPUT_18_1_1[1];
    tank_B.dv0[70] = tank_B.INPUT_18_1_1[2];
    tank_B.dv0[71] = tank_B.INPUT_18_1_1[3];
    tmp_3[18] = 72;
    tank_B.dv0[72] = tank_B.INPUT_19_1_1[0];
    tank_B.dv0[73] = tank_B.INPUT_19_1_1[1];
    tank_B.dv0[74] = tank_B.INPUT_19_1_1[2];
    tank_B.dv0[75] = tank_B.INPUT_19_1_1[3];
    tmp_3[19] = 76;
    tank_B.dv0[76] = tank_B.INPUT_20_1_1[0];
    tank_B.dv0[77] = tank_B.INPUT_20_1_1[1];
    tank_B.dv0[78] = tank_B.INPUT_20_1_1[2];
    tank_B.dv0[79] = tank_B.INPUT_20_1_1[3];
    tmp_3[20] = 80;
    tank_B.dv0[80] = tank_B.INPUT_21_1_1[0];
    tank_B.dv0[81] = tank_B.INPUT_21_1_1[1];
    tank_B.dv0[82] = tank_B.INPUT_21_1_1[2];
    tank_B.dv0[83] = tank_B.INPUT_21_1_1[3];
    tmp_3[21] = 84;
    tank_B.dv0[84] = tank_B.INPUT_22_1_1[0];
    tank_B.dv0[85] = tank_B.INPUT_22_1_1[1];
    tank_B.dv0[86] = tank_B.INPUT_22_1_1[2];
    tank_B.dv0[87] = tank_B.INPUT_22_1_1[3];
    tmp_3[22] = 88;
    memcpy(&tank_B.dv0[88], &tank_B.STATE_1[0], 1125U * sizeof(real_T));
    tmp_3[23] = 1213;
    simulationData->mData->mInputValues.mN = 1213;
    simulationData->mData->mInputValues.mX = &tank_B.dv0[0];
    simulationData->mData->mInputOffsets.mN = 24;
    simulationData->mData->mInputOffsets.mX = &tmp_3[0];
    simulationData->mData->mOutputs.mN = 23;
    simulationData->mData->mOutputs.mX = &rtb_OUTPUT_1_0[0];
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    tmp = 1;
    simulationData->mData->mIsFundamentalSampleHit = tmp;
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.OUTPUT_1_0_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method((NeslSimulator *)tank_DW.OUTPUT_1_0_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(tank_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    /* End of SimscapeExecutionBlock: '<S122>/OUTPUT_1_0' */

    /* Product: '<S135>/Product' incorporates:
     *  Constant: '<S135>/Constant'
     */
    rtb_Product = rtb_OUTPUT_1_0[15] * tank_P.Constant_Value_g;

    /* Outputs for Atomic SubSystem: '<S1>/  PLC Station 2' */
    /* RateTransition: '<S2>/Rate Transition' */
    if (tank_M->Timing.RateInteraction.TID1_3 == 1) {
      tank_B.RateTransition_o = rtb_OUTPUT_1_0[16];

      /* RateTransition: '<S2>/Rate Transition1' */
      tank_B.RateTransition1_n = rtb_Product;
    }

    /* End of RateTransition: '<S2>/Rate Transition' */
    /* End of Outputs for SubSystem: '<S1>/  PLC Station 2' */

    /* Product: '<S11>/Product' incorporates:
     *  Constant: '<S11>/Constant'
     */
    rtb_Product = rtb_OUTPUT_1_0[14] * tank_P.Constant_Value_c;

    /* Product: '<S45>/Product' incorporates:
     *  Constant: '<S45>/Constant'
     */
    rtb_Product_ph = rtb_OUTPUT_1_0[4] * tank_P.Constant_Value_n;

    /* Product: '<S43>/Product' incorporates:
     *  Constant: '<S43>/Constant'
     */
    rtb_Product_g = rtb_OUTPUT_1_0[2] * tank_P.Constant_Value_b;

    /* Outputs for Atomic SubSystem: '<S1>/ PLC Station 1' */
    /* RateTransition: '<S3>/Rate Transition' */
    if (tank_M->Timing.RateInteraction.TID1_3 == 1) {
      tank_B.RateTransition_n = rtb_OUTPUT_1_0[9];

      /* RateTransition: '<S3>/Rate Transition1' */
      tank_B.RateTransition1_f = rtb_Product;

      /* RateTransition: '<S3>/Rate Transition2' */
      tank_B.RateTransition2_h = rtb_Product_ph;

      /* RateTransition: '<S3>/Rate Transition3' */
      tank_B.RateTransition3_i = rtb_Product_g;
    }

    /* End of RateTransition: '<S3>/Rate Transition' */
    /* End of Outputs for SubSystem: '<S1>/ PLC Station 1' */

    /* Product: '<S145>/Product' incorporates:
     *  Constant: '<S145>/Constant'
     */
    rtb_Product = rtb_OUTPUT_1_0[17] * tank_P.Constant_Value_ad;

    /* Outputs for Atomic SubSystem: '<S1>/PLC Station 3' */
    /* RateTransition: '<S6>/Rate Transition' */
    if (tank_M->Timing.RateInteraction.TID1_3 == 1) {
      tank_B.RateTransition_e = rtb_OUTPUT_1_0[18];

      /* RateTransition: '<S6>/Rate Transition1' */
      tank_B.RateTransition1_m = rtb_Product;
    }

    /* End of RateTransition: '<S6>/Rate Transition' */
    /* End of Outputs for SubSystem: '<S1>/PLC Station 3' */

    /* Product: '<S155>/Product' incorporates:
     *  Constant: '<S155>/Constant'
     */
    rtb_Product = rtb_OUTPUT_1_0[19] * tank_P.Constant_Value_bp;

    /* Outputs for Atomic SubSystem: '<S1>/PLC Station 4' */
    /* RateTransition: '<S7>/Rate Transition' */
    if (tank_M->Timing.RateInteraction.TID1_3 == 1) {
      tank_B.RateTransition_k = rtb_OUTPUT_1_0[20];

      /* RateTransition: '<S7>/Rate Transition1' */
      tank_B.RateTransition1_k = rtb_Product;
    }

    /* End of RateTransition: '<S7>/Rate Transition' */
    /* End of Outputs for SubSystem: '<S1>/PLC Station 4' */

    /* Product: '<S11>/Product1' incorporates:
     *  Constant: '<S11>/Constant1'
     */
    rtb_Product = rtb_OUTPUT_1_0[0] * tank_P.Constant1_Value_n;

    /* Product: '<S44>/Product' incorporates:
     *  Constant: '<S44>/Constant'
     */
    rtb_Product_ph = rtb_OUTPUT_1_0[3] * tank_P.Constant_Value_dw;

    /* Product: '<S42>/Product' incorporates:
     *  Constant: '<S42>/Constant'
     */
    rtb_Product_g = rtb_OUTPUT_1_0[1] * tank_P.Constant_Value_l4;

    /* Product: '<S165>/Product' incorporates:
     *  Constant: '<S165>/Constant'
     */
    rtb_Product_e = rtb_OUTPUT_1_0[21] * tank_P.Constant_Value_j;

    /* Outputs for Atomic SubSystem: '<S1>/PLC Station 5' */
    /* RateTransition: '<S8>/Rate Transition' */
    if (tank_M->Timing.RateInteraction.TID1_3 == 1) {
      tank_B.RateTransition_g = rtb_OUTPUT_1_0[22];

      /* RateTransition: '<S8>/Rate Transition1' */
      tank_B.RateTransition1_o = rtb_Product;

      /* RateTransition: '<S8>/Rate Transition2' */
      tank_B.RateTransition2_p = rtb_Product_ph;

      /* RateTransition: '<S8>/Rate Transition3' */
      tank_B.RateTransition3_c = rtb_Product_g;

      /* RateTransition: '<S8>/Rate Transition4' */
      tank_B.RateTransition4_i = rtb_Product_e;
    }

    /* End of RateTransition: '<S8>/Rate Transition' */
    /* End of Outputs for SubSystem: '<S1>/PLC Station 5' */

    /* RateTransition: '<S1>/Rate Transition' */
    if (tank_M->Timing.RateInteraction.TID1_2 == 1) {
      tank_B.RateTransition = tank_DW.RateTransition_Buffer0;

      /* RateTransition: '<S1>/Rate Transition1' */
      tank_B.RateTransition1 = tank_DW.RateTransition1_Buffer0;

      /* RateTransition: '<S1>/Rate Transition10' */
      tank_B.RateTransition10 = tank_DW.RateTransition10_Buffer0;

      /* RateTransition: '<S1>/Rate Transition11' */
      tank_B.RateTransition11 = tank_DW.RateTransition11_Buffer0;

      /* RateTransition: '<S1>/Rate Transition12' */
      tank_B.RateTransition12 = tank_DW.RateTransition12_Buffer0;

      /* RateTransition: '<S1>/Rate Transition13' */
      tank_B.RateTransition13 = tank_DW.RateTransition13_Buffer0;

      /* RateTransition: '<S1>/Rate Transition14' */
      tank_B.RateTransition14 = tank_DW.RateTransition14_Buffer0;

      /* RateTransition: '<S1>/Rate Transition15' */
      tank_B.RateTransition15 = tank_DW.RateTransition15_Buffer0;

      /* RateTransition: '<S1>/Rate Transition16' */
      tank_B.RateTransition16 = tank_DW.RateTransition16_Buffer0;

      /* RateTransition: '<S1>/Rate Transition17' */
      tank_B.RateTransition17 = tank_DW.RateTransition17_Buffer0;

      /* RateTransition: '<S1>/Rate Transition2' */
      tank_B.RateTransition2 = tank_DW.RateTransition2_Buffer0;

      /* RateTransition: '<S1>/Rate Transition3' */
      tank_B.RateTransition3 = tank_DW.RateTransition3_Buffer0;

      /* RateTransition: '<S1>/Rate Transition4' */
      tank_B.RateTransition4 = tank_DW.RateTransition4_Buffer0;

      /* RateTransition: '<S1>/Rate Transition5' */
      tank_B.RateTransition5 = tank_DW.RateTransition5_Buffer0;

      /* RateTransition: '<S1>/Rate Transition6' */
      tank_B.RateTransition6 = tank_DW.RateTransition6_Buffer0;

      /* RateTransition: '<S1>/Rate Transition7' */
      tank_B.RateTransition7 = tank_DW.RateTransition7_Buffer0;

      /* RateTransition: '<S1>/Rate Transition8' */
      tank_B.RateTransition8 = tank_DW.RateTransition8_Buffer0;

      /* RateTransition: '<S1>/Rate Transition9' */
      tank_B.RateTransition9 = tank_DW.RateTransition9_Buffer0;
    }

    /* End of RateTransition: '<S1>/Rate Transition' */
  }

  /* Matfile logging */
  rt_UpdateTXYLogVars(tank_M->rtwLogInfo, (tank_M->Timing.t));

  {
    NeslSimulationData *simulationData;
    real_T time;
    boolean_T tmp;
    real_T tmp_0[88];
    int_T tmp_1[23];
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    int32_T tmp_2;
    char *msg;

    /* Update for TransportDelay: '<S1>/Transport Delay3' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay3_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay3_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay3_IWORK.Head = ((tank_DW.TransportDelay3_IWORK.Head <
        (tank_DW.TransportDelay3_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay3_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay3_IWORK.Head ==
          tank_DW.TransportDelay3_IWORK.Tail) {
        tank_DW.TransportDelay3_IWORK.Tail =
          ((tank_DW.TransportDelay3_IWORK.Tail <
            (tank_DW.TransportDelay3_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay3_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay3_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay3_IWORK.Head] = tank_B.RateTransition5;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay5' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay5_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay5_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay5_IWORK.Head = ((tank_DW.TransportDelay5_IWORK.Head <
        (tank_DW.TransportDelay5_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay5_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay5_IWORK.Head ==
          tank_DW.TransportDelay5_IWORK.Tail) {
        tank_DW.TransportDelay5_IWORK.Tail =
          ((tank_DW.TransportDelay5_IWORK.Tail <
            (tank_DW.TransportDelay5_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay5_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay5_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay5_IWORK.Head] = tank_B.RateTransition8;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay7' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay7_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay7_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay7_IWORK.Head = ((tank_DW.TransportDelay7_IWORK.Head <
        (tank_DW.TransportDelay7_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay7_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay7_IWORK.Head ==
          tank_DW.TransportDelay7_IWORK.Tail) {
        tank_DW.TransportDelay7_IWORK.Tail =
          ((tank_DW.TransportDelay7_IWORK.Tail <
            (tank_DW.TransportDelay7_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay7_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay7_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay7_IWORK.Head] = tank_B.RateTransition11;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay15' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay15_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay15_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay15_IWORK.Head =
        ((tank_DW.TransportDelay15_IWORK.Head <
          (tank_DW.TransportDelay15_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay15_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay15_IWORK.Head ==
          tank_DW.TransportDelay15_IWORK.Tail) {
        tank_DW.TransportDelay15_IWORK.Tail =
          ((tank_DW.TransportDelay15_IWORK.Tail <
            (tank_DW.TransportDelay15_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay15_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay15_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay15_IWORK.Head] = tank_B.RateTransition14;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay16' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay16_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay16_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay16_IWORK.Head =
        ((tank_DW.TransportDelay16_IWORK.Head <
          (tank_DW.TransportDelay16_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay16_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay16_IWORK.Head ==
          tank_DW.TransportDelay16_IWORK.Tail) {
        tank_DW.TransportDelay16_IWORK.Tail =
          ((tank_DW.TransportDelay16_IWORK.Tail <
            (tank_DW.TransportDelay16_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay16_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay16_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay16_IWORK.Head] = tank_B.RateTransition16;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay1' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay1_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay1_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay1_IWORK.Head = ((tank_DW.TransportDelay1_IWORK.Head <
        (tank_DW.TransportDelay1_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay1_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay1_IWORK.Head ==
          tank_DW.TransportDelay1_IWORK.Tail) {
        tank_DW.TransportDelay1_IWORK.Tail =
          ((tank_DW.TransportDelay1_IWORK.Tail <
            (tank_DW.TransportDelay1_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay1_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay1_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay1_IWORK.Head] = tank_B.RateTransition1;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay17' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay17_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay17_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay17_IWORK.Head =
        ((tank_DW.TransportDelay17_IWORK.Head <
          (tank_DW.TransportDelay17_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay17_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay17_IWORK.Head ==
          tank_DW.TransportDelay17_IWORK.Tail) {
        tank_DW.TransportDelay17_IWORK.Tail =
          ((tank_DW.TransportDelay17_IWORK.Tail <
            (tank_DW.TransportDelay17_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay17_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay17_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay17_IWORK.Head] = tank_B.RateTransition17;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay_IWORK.Head = ((tank_DW.TransportDelay_IWORK.Head <
        (tank_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay_IWORK.Head == tank_DW.TransportDelay_IWORK.Tail)
      {
        tank_DW.TransportDelay_IWORK.Tail = ((tank_DW.TransportDelay_IWORK.Tail <
          (tank_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
          (tank_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay_IWORK.Head] = tank_B.RateTransition;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay11' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay11_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay11_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay11_IWORK.Head =
        ((tank_DW.TransportDelay11_IWORK.Head <
          (tank_DW.TransportDelay11_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay11_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay11_IWORK.Head ==
          tank_DW.TransportDelay11_IWORK.Tail) {
        tank_DW.TransportDelay11_IWORK.Tail =
          ((tank_DW.TransportDelay11_IWORK.Tail <
            (tank_DW.TransportDelay11_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay11_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay11_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay11_IWORK.Head] = tank_B.RateTransition3;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay10' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay10_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay10_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay10_IWORK.Head =
        ((tank_DW.TransportDelay10_IWORK.Head <
          (tank_DW.TransportDelay10_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay10_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay10_IWORK.Head ==
          tank_DW.TransportDelay10_IWORK.Tail) {
        tank_DW.TransportDelay10_IWORK.Tail =
          ((tank_DW.TransportDelay10_IWORK.Tail <
            (tank_DW.TransportDelay10_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay10_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay10_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay10_IWORK.Head] = tank_B.RateTransition2;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay2' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay2_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay2_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay2_IWORK.Head = ((tank_DW.TransportDelay2_IWORK.Head <
        (tank_DW.TransportDelay2_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay2_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay2_IWORK.Head ==
          tank_DW.TransportDelay2_IWORK.Tail) {
        tank_DW.TransportDelay2_IWORK.Tail =
          ((tank_DW.TransportDelay2_IWORK.Tail <
            (tank_DW.TransportDelay2_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay2_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay2_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay2_IWORK.Head] = tank_B.RateTransition4;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay12' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay12_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay12_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay12_IWORK.Head =
        ((tank_DW.TransportDelay12_IWORK.Head <
          (tank_DW.TransportDelay12_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay12_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay12_IWORK.Head ==
          tank_DW.TransportDelay12_IWORK.Tail) {
        tank_DW.TransportDelay12_IWORK.Tail =
          ((tank_DW.TransportDelay12_IWORK.Tail <
            (tank_DW.TransportDelay12_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay12_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay12_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay12_IWORK.Head] = tank_B.RateTransition6;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay4' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay4_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay4_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay4_IWORK.Head = ((tank_DW.TransportDelay4_IWORK.Head <
        (tank_DW.TransportDelay4_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay4_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay4_IWORK.Head ==
          tank_DW.TransportDelay4_IWORK.Tail) {
        tank_DW.TransportDelay4_IWORK.Tail =
          ((tank_DW.TransportDelay4_IWORK.Tail <
            (tank_DW.TransportDelay4_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay4_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay4_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay4_IWORK.Head] = tank_B.RateTransition7;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay13' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay13_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay13_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay13_IWORK.Head =
        ((tank_DW.TransportDelay13_IWORK.Head <
          (tank_DW.TransportDelay13_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay13_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay13_IWORK.Head ==
          tank_DW.TransportDelay13_IWORK.Tail) {
        tank_DW.TransportDelay13_IWORK.Tail =
          ((tank_DW.TransportDelay13_IWORK.Tail <
            (tank_DW.TransportDelay13_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay13_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay13_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay13_IWORK.Head] = tank_B.RateTransition9;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay6' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay6_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay6_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay6_IWORK.Head = ((tank_DW.TransportDelay6_IWORK.Head <
        (tank_DW.TransportDelay6_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay6_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay6_IWORK.Head ==
          tank_DW.TransportDelay6_IWORK.Tail) {
        tank_DW.TransportDelay6_IWORK.Tail =
          ((tank_DW.TransportDelay6_IWORK.Tail <
            (tank_DW.TransportDelay6_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay6_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay6_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay6_IWORK.Head] = tank_B.RateTransition10;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay14' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay14_PWORK.TUbufferPtrs
        [0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay14_PWORK.TUbufferPtrs
        [1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay14_IWORK.Head =
        ((tank_DW.TransportDelay14_IWORK.Head <
          (tank_DW.TransportDelay14_IWORK.CircularBufSize-1)) ?
         (tank_DW.TransportDelay14_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay14_IWORK.Head ==
          tank_DW.TransportDelay14_IWORK.Tail) {
        tank_DW.TransportDelay14_IWORK.Tail =
          ((tank_DW.TransportDelay14_IWORK.Tail <
            (tank_DW.TransportDelay14_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay14_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay14_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay14_IWORK.Head] = tank_B.RateTransition12;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay8' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay8_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay8_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay8_IWORK.Head = ((tank_DW.TransportDelay8_IWORK.Head <
        (tank_DW.TransportDelay8_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay8_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay8_IWORK.Head ==
          tank_DW.TransportDelay8_IWORK.Tail) {
        tank_DW.TransportDelay8_IWORK.Tail =
          ((tank_DW.TransportDelay8_IWORK.Tail <
            (tank_DW.TransportDelay8_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay8_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay8_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay8_IWORK.Head] = tank_B.RateTransition13;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay9' */
    {
      real_T **uBuffer = (real_T**)&tank_DW.TransportDelay9_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&tank_DW.TransportDelay9_PWORK.TUbufferPtrs[1];
      real_T simTime = tank_M->Timing.t[0];
      tank_DW.TransportDelay9_IWORK.Head = ((tank_DW.TransportDelay9_IWORK.Head <
        (tank_DW.TransportDelay9_IWORK.CircularBufSize-1)) ?
        (tank_DW.TransportDelay9_IWORK.Head+1) : 0);
      if (tank_DW.TransportDelay9_IWORK.Head ==
          tank_DW.TransportDelay9_IWORK.Tail) {
        tank_DW.TransportDelay9_IWORK.Tail =
          ((tank_DW.TransportDelay9_IWORK.Tail <
            (tank_DW.TransportDelay9_IWORK.CircularBufSize-1)) ?
           (tank_DW.TransportDelay9_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[tank_DW.TransportDelay9_IWORK.Head] = simTime;
      (*uBuffer)[tank_DW.TransportDelay9_IWORK.Head] = tank_B.RateTransition15;
    }

    /* Update for SimscapeExecutionBlock: '<S122>/STATE_1' */
    simulationData = (NeslSimulationData *)tank_DW.STATE_1_SimulationData;
    time = tank_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 163;
    simulationData->mData->mDiscStates.mX = (real_T *)
      &tank_DW.STATE_1_DiscStates;
    simulationData->mData->mModeVector.mN = 962;
    simulationData->mData->mModeVector.mX = (int32_T *)&tank_DW.STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = true;
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_1[0] = 0;
    tmp_0[0] = tank_B.INPUT_1_1_1[0];
    tmp_0[1] = tank_B.INPUT_1_1_1[1];
    tmp_0[2] = tank_B.INPUT_1_1_1[2];
    tmp_0[3] = tank_B.INPUT_1_1_1[3];
    tmp_1[1] = 4;
    tmp_0[4] = tank_B.INPUT_2_1_1[0];
    tmp_0[5] = tank_B.INPUT_2_1_1[1];
    tmp_0[6] = tank_B.INPUT_2_1_1[2];
    tmp_0[7] = tank_B.INPUT_2_1_1[3];
    tmp_1[2] = 8;
    tmp_0[8] = tank_B.INPUT_3_1_1[0];
    tmp_0[9] = tank_B.INPUT_3_1_1[1];
    tmp_0[10] = tank_B.INPUT_3_1_1[2];
    tmp_0[11] = tank_B.INPUT_3_1_1[3];
    tmp_1[3] = 12;
    tmp_0[12] = tank_B.INPUT_4_1_1[0];
    tmp_0[13] = tank_B.INPUT_4_1_1[1];
    tmp_0[14] = tank_B.INPUT_4_1_1[2];
    tmp_0[15] = tank_B.INPUT_4_1_1[3];
    tmp_1[4] = 16;
    tmp_0[16] = tank_B.INPUT_5_1_1[0];
    tmp_0[17] = tank_B.INPUT_5_1_1[1];
    tmp_0[18] = tank_B.INPUT_5_1_1[2];
    tmp_0[19] = tank_B.INPUT_5_1_1[3];
    tmp_1[5] = 20;
    tmp_0[20] = tank_B.INPUT_6_1_1[0];
    tmp_0[21] = tank_B.INPUT_6_1_1[1];
    tmp_0[22] = tank_B.INPUT_6_1_1[2];
    tmp_0[23] = tank_B.INPUT_6_1_1[3];
    tmp_1[6] = 24;
    tmp_0[24] = tank_B.INPUT_7_1_1[0];
    tmp_0[25] = tank_B.INPUT_7_1_1[1];
    tmp_0[26] = tank_B.INPUT_7_1_1[2];
    tmp_0[27] = tank_B.INPUT_7_1_1[3];
    tmp_1[7] = 28;
    tmp_0[28] = tank_B.INPUT_8_1_1[0];
    tmp_0[29] = tank_B.INPUT_8_1_1[1];
    tmp_0[30] = tank_B.INPUT_8_1_1[2];
    tmp_0[31] = tank_B.INPUT_8_1_1[3];
    tmp_1[8] = 32;
    tmp_0[32] = tank_B.INPUT_9_1_1[0];
    tmp_0[33] = tank_B.INPUT_9_1_1[1];
    tmp_0[34] = tank_B.INPUT_9_1_1[2];
    tmp_0[35] = tank_B.INPUT_9_1_1[3];
    tmp_1[9] = 36;
    tmp_0[36] = tank_B.INPUT_10_1_1[0];
    tmp_0[37] = tank_B.INPUT_10_1_1[1];
    tmp_0[38] = tank_B.INPUT_10_1_1[2];
    tmp_0[39] = tank_B.INPUT_10_1_1[3];
    tmp_1[10] = 40;
    tmp_0[40] = tank_B.INPUT_11_1_1[0];
    tmp_0[41] = tank_B.INPUT_11_1_1[1];
    tmp_0[42] = tank_B.INPUT_11_1_1[2];
    tmp_0[43] = tank_B.INPUT_11_1_1[3];
    tmp_1[11] = 44;
    tmp_0[44] = tank_B.INPUT_12_1_1[0];
    tmp_0[45] = tank_B.INPUT_12_1_1[1];
    tmp_0[46] = tank_B.INPUT_12_1_1[2];
    tmp_0[47] = tank_B.INPUT_12_1_1[3];
    tmp_1[12] = 48;
    tmp_0[48] = tank_B.INPUT_13_1_1[0];
    tmp_0[49] = tank_B.INPUT_13_1_1[1];
    tmp_0[50] = tank_B.INPUT_13_1_1[2];
    tmp_0[51] = tank_B.INPUT_13_1_1[3];
    tmp_1[13] = 52;
    tmp_0[52] = tank_B.INPUT_14_1_1[0];
    tmp_0[53] = tank_B.INPUT_14_1_1[1];
    tmp_0[54] = tank_B.INPUT_14_1_1[2];
    tmp_0[55] = tank_B.INPUT_14_1_1[3];
    tmp_1[14] = 56;
    tmp_0[56] = tank_B.INPUT_15_1_1[0];
    tmp_0[57] = tank_B.INPUT_15_1_1[1];
    tmp_0[58] = tank_B.INPUT_15_1_1[2];
    tmp_0[59] = tank_B.INPUT_15_1_1[3];
    tmp_1[15] = 60;
    tmp_0[60] = tank_B.INPUT_16_1_1[0];
    tmp_0[61] = tank_B.INPUT_16_1_1[1];
    tmp_0[62] = tank_B.INPUT_16_1_1[2];
    tmp_0[63] = tank_B.INPUT_16_1_1[3];
    tmp_1[16] = 64;
    tmp_0[64] = tank_B.INPUT_17_1_1[0];
    tmp_0[65] = tank_B.INPUT_17_1_1[1];
    tmp_0[66] = tank_B.INPUT_17_1_1[2];
    tmp_0[67] = tank_B.INPUT_17_1_1[3];
    tmp_1[17] = 68;
    tmp_0[68] = tank_B.INPUT_18_1_1[0];
    tmp_0[69] = tank_B.INPUT_18_1_1[1];
    tmp_0[70] = tank_B.INPUT_18_1_1[2];
    tmp_0[71] = tank_B.INPUT_18_1_1[3];
    tmp_1[18] = 72;
    tmp_0[72] = tank_B.INPUT_19_1_1[0];
    tmp_0[73] = tank_B.INPUT_19_1_1[1];
    tmp_0[74] = tank_B.INPUT_19_1_1[2];
    tmp_0[75] = tank_B.INPUT_19_1_1[3];
    tmp_1[19] = 76;
    tmp_0[76] = tank_B.INPUT_20_1_1[0];
    tmp_0[77] = tank_B.INPUT_20_1_1[1];
    tmp_0[78] = tank_B.INPUT_20_1_1[2];
    tmp_0[79] = tank_B.INPUT_20_1_1[3];
    tmp_1[20] = 80;
    tmp_0[80] = tank_B.INPUT_21_1_1[0];
    tmp_0[81] = tank_B.INPUT_21_1_1[1];
    tmp_0[82] = tank_B.INPUT_21_1_1[2];
    tmp_0[83] = tank_B.INPUT_21_1_1[3];
    tmp_1[21] = 84;
    tmp_0[84] = tank_B.INPUT_22_1_1[0];
    tmp_0[85] = tank_B.INPUT_22_1_1[1];
    tmp_0[86] = tank_B.INPUT_22_1_1[2];
    tmp_0[87] = tank_B.INPUT_22_1_1[3];
    tmp_1[22] = 88;
    simulationData->mData->mInputValues.mN = 88;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 23;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method((NeslSimulator *)tank_DW.STATE_1_Simulator,
      NESL_SIM_UPDATE, simulationData, diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(tank_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    /* End of Update for SimscapeExecutionBlock: '<S122>/STATE_1' */
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(tank_M)!=-1) &&
        !((rtmGetTFinal(tank_M)-tank_M->Timing.t[0]) > tank_M->Timing.t[0] *
          (DBL_EPSILON))) {
      rtmSetErrorStatus(tank_M, "Simulation finished");
    }
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++tank_M->Timing.clockTick0)) {
    ++tank_M->Timing.clockTickH0;
  }

  tank_M->Timing.t[0] = tank_M->Timing.clockTick0 * tank_M->Timing.stepSize0 +
    tank_M->Timing.clockTickH0 * tank_M->Timing.stepSize0 * 4294967296.0;

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.001, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  tank_M->Timing.clockTick1++;
  if (!tank_M->Timing.clockTick1) {
    tank_M->Timing.clockTickH1++;
  }
}

/* Model step function for TID2 */
void tank_step2(void)                  /* Sample time: [0.01s, 0.0s] */
{
  char_T *sErr;
  int32_T samplesRead;
  int32_T samplesRead_0;
  int32_T samplesRead_1;
  int32_T samplesRead_2;
  int32_T samplesRead_3;
  int32_T samplesRead_4;
  int32_T samplesRead_5;
  int32_T samplesRead_6;
  int32_T samplesRead_7;
  int32_T samplesRead_8;
  int32_T samplesRead_9;
  int32_T samplesRead_a;
  int32_T samplesRead_b;
  int32_T samplesRead_c;
  int32_T samplesRead_d;
  int32_T samplesRead_e;
  int32_T samplesRead_f;
  int32_T samplesRead_g;

  /* Outputs for Atomic SubSystem: '<S1>/  PLC Station 2' */
  /* S-Function (sdspFromNetwork): '<S2>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_p[0U]);
  samplesRead = 1;
  LibOutputs_Network(&tank_DW.UDPReceive_NetworkLib_p[0U],
                     &tank_B.UDPReceive_o1_b2, &samplesRead);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive_o2_d = (uint16_T)samplesRead;

  /* End of S-Function (sdspFromNetwork): '<S2>/UDP Receive' */

  /* If: '<S2>/Pump If' */
  if (tank_B.UDPReceive_o1_b2 != 0) {
    /* Outputs for IfAction SubSystem: '<S2>/Pump Value Conversion' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    tank_PumpValueConversion(tank_B.UDPReceive_o1_b2,
      &tank_B.PumpValueConversion, (P_PumpValueConversion_tank_T *)
      &tank_P.PumpValueConversion);

    /* End of Outputs for SubSystem: '<S2>/Pump Value Conversion' */
  }

  /* End of If: '<S2>/Pump If' */

  /* S-Function (sdspFromNetwork): '<S2>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
  samplesRead_0 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive1_NetworkLib_ou[0U],
                     &tank_B.UDPReceive1_o1_d, &samplesRead_0);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive1_o2_m = (uint16_T)samplesRead_0;

  /* End of S-Function (sdspFromNetwork): '<S2>/UDP Receive1' */

  /* If: '<S2>/Valve If' */
  if (tank_B.UDPReceive1_o1_d != 0) {
    /* Outputs for IfAction SubSystem: '<S2>/Valve Value Conversion' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive1_o1_d,
      &tank_B.ValveValueConversion, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion);

    /* End of Outputs for SubSystem: '<S2>/Valve Value Conversion' */
  }

  /* End of If: '<S2>/Valve If' */

  /* S-Function (sdspFromNetwork): '<S2>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
  samplesRead_1 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive2_NetworkLib_p[0U],
                     &tank_B.UDPReceive2_o1_p, &samplesRead_1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive2_o2_f = (uint16_T)samplesRead_1;

  /* End of S-Function (sdspFromNetwork): '<S2>/UDP Receive2' */

  /* If: '<S2>/Valve If1' */
  if (tank_B.UDPReceive2_o1_p != 0) {
    /* Outputs for IfAction SubSystem: '<S2>/Valve Value Conversion1' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive2_o1_p,
      &tank_B.ValveValueConversion1, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion1);

    /* End of Outputs for SubSystem: '<S2>/Valve Value Conversion1' */
  }

  /* End of If: '<S2>/Valve If1' */
  /* End of Outputs for SubSystem: '<S1>/  PLC Station 2' */

  /* Outputs for Atomic SubSystem: '<S1>/ PLC Station 1' */
  /* S-Function (sdspFromNetwork): '<S3>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
  samplesRead_2 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive1_NetworkLib_b[0U],
                     &tank_B.UDPReceive1_o1_i, &samplesRead_2);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive1_o2_ku = (uint16_T)samplesRead_2;

  /* End of S-Function (sdspFromNetwork): '<S3>/UDP Receive1' */

  /* If: '<S3>/Valve If' */
  if (tank_B.UDPReceive1_o1_i != 0) {
    /* Outputs for IfAction SubSystem: '<S3>/Valve Value Conversion' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive1_o1_i,
      &tank_B.ValveValueConversion_d, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion_d);

    /* End of Outputs for SubSystem: '<S3>/Valve Value Conversion' */
  }

  /* End of If: '<S3>/Valve If' */

  /* S-Function (sdspFromNetwork): '<S3>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_h[0U]);
  samplesRead_3 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive_NetworkLib_h[0U],
                     &tank_B.UDPReceive_o1_b, &samplesRead_3);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive_o2_l = (uint16_T)samplesRead_3;

  /* End of S-Function (sdspFromNetwork): '<S3>/UDP Receive' */

  /* If: '<S3>/Pump If' */
  if (tank_B.UDPReceive_o1_b != 0) {
    /* Outputs for IfAction SubSystem: '<S3>/Pump Value Conversion' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    tank_PumpValueConversion(tank_B.UDPReceive_o1_b,
      &tank_B.PumpValueConversion_n, (P_PumpValueConversion_tank_T *)
      &tank_P.PumpValueConversion_n);

    /* End of Outputs for SubSystem: '<S3>/Pump Value Conversion' */
  }

  /* End of If: '<S3>/Pump If' */

  /* S-Function (sdspFromNetwork): '<S3>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
  samplesRead_4 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive2_NetworkLib_n[0U],
                     &tank_B.UDPReceive2_o1_c, &samplesRead_4);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive2_o2_m = (uint16_T)samplesRead_4;

  /* End of S-Function (sdspFromNetwork): '<S3>/UDP Receive2' */

  /* If: '<S3>/Valve If1' */
  if (tank_B.UDPReceive2_o1_c != 0) {
    /* Outputs for IfAction SubSystem: '<S3>/Valve Value Conversion1' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive2_o1_c,
      &tank_B.ValveValueConversion1_d, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion1_d);

    /* End of Outputs for SubSystem: '<S3>/Valve Value Conversion1' */
  }

  /* End of If: '<S3>/Valve If1' */

  /* S-Function (sdspFromNetwork): '<S3>/UDP Receive3' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive3_NetworkLib[0U]);
  samplesRead_5 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive3_NetworkLib[0U], &tank_B.UDPReceive3_o1,
                     &samplesRead_5);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive3_o2 = (uint16_T)samplesRead_5;

  /* End of S-Function (sdspFromNetwork): '<S3>/UDP Receive3' */

  /* If: '<S3>/Valve If2' */
  if (tank_B.UDPReceive3_o1 != 0) {
    /* Outputs for IfAction SubSystem: '<S3>/Valve Value Conversion2' incorporates:
     *  ActionPort: '<S20>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive3_o1,
      &tank_B.ValveValueConversion2, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion2);

    /* End of Outputs for SubSystem: '<S3>/Valve Value Conversion2' */
  }

  /* End of If: '<S3>/Valve If2' */
  /* End of Outputs for SubSystem: '<S1>/ PLC Station 1' */

  /* Outputs for Atomic SubSystem: '<S1>/PLC Station 3' */
  /* S-Function (sdspFromNetwork): '<S6>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_g[0U]);
  samplesRead_6 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive_NetworkLib_g[0U],
                     &tank_B.UDPReceive_o1_h, &samplesRead_6);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive_o2_e = (uint16_T)samplesRead_6;

  /* End of S-Function (sdspFromNetwork): '<S6>/UDP Receive' */

  /* If: '<S6>/Pump If' */
  if (tank_B.UDPReceive_o1_h != 0) {
    /* Outputs for IfAction SubSystem: '<S6>/Pump Value Conversion' incorporates:
     *  ActionPort: '<S22>/Action Port'
     */
    tank_PumpValueConversion(tank_B.UDPReceive_o1_h,
      &tank_B.PumpValueConversion_a, (P_PumpValueConversion_tank_T *)
      &tank_P.PumpValueConversion_a);

    /* End of Outputs for SubSystem: '<S6>/Pump Value Conversion' */
  }

  /* End of If: '<S6>/Pump If' */

  /* S-Function (sdspFromNetwork): '<S6>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
  samplesRead_7 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive1_NetworkLib_o[0U],
                     &tank_B.UDPReceive1_o1_n, &samplesRead_7);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive1_o2_k = (uint16_T)samplesRead_7;

  /* End of S-Function (sdspFromNetwork): '<S6>/UDP Receive1' */

  /* If: '<S6>/Valve If' */
  if (tank_B.UDPReceive1_o1_n != 0) {
    /* Outputs for IfAction SubSystem: '<S6>/Valve Value Conversion' incorporates:
     *  ActionPort: '<S23>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive1_o1_n,
      &tank_B.ValveValueConversion_n, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion_n);

    /* End of Outputs for SubSystem: '<S6>/Valve Value Conversion' */
  }

  /* End of If: '<S6>/Valve If' */

  /* S-Function (sdspFromNetwork): '<S6>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
  samplesRead_8 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive2_NetworkLib_a[0U],
                     &tank_B.UDPReceive2_o1_a, &samplesRead_8);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive2_o2_h = (uint16_T)samplesRead_8;

  /* End of S-Function (sdspFromNetwork): '<S6>/UDP Receive2' */

  /* If: '<S6>/Valve If1' */
  if (tank_B.UDPReceive2_o1_a != 0) {
    /* Outputs for IfAction SubSystem: '<S6>/Valve Value Conversion1' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive2_o1_a,
      &tank_B.ValveValueConversion1_p, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion1_p);

    /* End of Outputs for SubSystem: '<S6>/Valve Value Conversion1' */
  }

  /* End of If: '<S6>/Valve If1' */
  /* End of Outputs for SubSystem: '<S1>/PLC Station 3' */

  /* Outputs for Atomic SubSystem: '<S1>/PLC Station 4' */
  /* S-Function (sdspFromNetwork): '<S7>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_m[0U]);
  samplesRead_9 = 1;
  LibOutputs_Network(&tank_DW.UDPReceive_NetworkLib_m[0U],
                     &tank_B.UDPReceive_o1_n, &samplesRead_9);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive_o2_g = (uint16_T)samplesRead_9;

  /* End of S-Function (sdspFromNetwork): '<S7>/UDP Receive' */

  /* If: '<S7>/Pump If' */
  if (tank_B.UDPReceive_o1_n != 0) {
    /* Outputs for IfAction SubSystem: '<S7>/Pump Value Conversion' incorporates:
     *  ActionPort: '<S26>/Action Port'
     */
    tank_PumpValueConversion(tank_B.UDPReceive_o1_n,
      &tank_B.PumpValueConversion_k, (P_PumpValueConversion_tank_T *)
      &tank_P.PumpValueConversion_k);

    /* End of Outputs for SubSystem: '<S7>/Pump Value Conversion' */
  }

  /* End of If: '<S7>/Pump If' */

  /* S-Function (sdspFromNetwork): '<S7>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
  samplesRead_a = 1;
  LibOutputs_Network(&tank_DW.UDPReceive1_NetworkLib_f[0U],
                     &tank_B.UDPReceive1_o1_p, &samplesRead_a);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive1_o2_f = (uint16_T)samplesRead_a;

  /* End of S-Function (sdspFromNetwork): '<S7>/UDP Receive1' */

  /* If: '<S7>/Valve If' */
  if (tank_B.UDPReceive1_o1_p != 0) {
    /* Outputs for IfAction SubSystem: '<S7>/Valve Value Conversion' incorporates:
     *  ActionPort: '<S27>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive1_o1_p,
      &tank_B.ValveValueConversion_g, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion_g);

    /* End of Outputs for SubSystem: '<S7>/Valve Value Conversion' */
  }

  /* End of If: '<S7>/Valve If' */

  /* S-Function (sdspFromNetwork): '<S7>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
  samplesRead_b = 1;
  LibOutputs_Network(&tank_DW.UDPReceive2_NetworkLib_g[0U],
                     &tank_B.UDPReceive2_o1_j, &samplesRead_b);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive2_o2_d = (uint16_T)samplesRead_b;

  /* End of S-Function (sdspFromNetwork): '<S7>/UDP Receive2' */

  /* If: '<S7>/Valve If1' */
  if (tank_B.UDPReceive2_o1_j != 0) {
    /* Outputs for IfAction SubSystem: '<S7>/Valve Value Conversion1' incorporates:
     *  ActionPort: '<S28>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive2_o1_j,
      &tank_B.ValveValueConversion1_m, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion1_m);

    /* End of Outputs for SubSystem: '<S7>/Valve Value Conversion1' */
  }

  /* End of If: '<S7>/Valve If1' */
  /* End of Outputs for SubSystem: '<S1>/PLC Station 4' */

  /* Outputs for Atomic SubSystem: '<S1>/PLC Station 5' */
  /* S-Function (sdspFromNetwork): '<S8>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib[0U]);
  samplesRead_c = 1;
  LibOutputs_Network(&tank_DW.UDPReceive_NetworkLib[0U], &tank_B.UDPReceive_o1,
                     &samplesRead_c);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive_o2 = (uint16_T)samplesRead_c;

  /* End of S-Function (sdspFromNetwork): '<S8>/UDP Receive' */

  /* If: '<S8>/Pump If' */
  if (tank_B.UDPReceive_o1 != 0) {
    /* Outputs for IfAction SubSystem: '<S8>/Pump Value Conversion' incorporates:
     *  ActionPort: '<S30>/Action Port'
     */
    tank_PumpValueConversion(tank_B.UDPReceive_o1, &tank_B.PumpValueConversion_j,
      (P_PumpValueConversion_tank_T *)&tank_P.PumpValueConversion_j);

    /* End of Outputs for SubSystem: '<S8>/Pump Value Conversion' */
  }

  /* End of If: '<S8>/Pump If' */

  /* S-Function (sdspFromNetwork): '<S8>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib[0U]);
  samplesRead_d = 1;
  LibOutputs_Network(&tank_DW.UDPReceive1_NetworkLib[0U], &tank_B.UDPReceive1_o1,
                     &samplesRead_d);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive1_o2 = (uint16_T)samplesRead_d;

  /* End of S-Function (sdspFromNetwork): '<S8>/UDP Receive1' */

  /* If: '<S8>/Valve If' */
  if (tank_B.UDPReceive1_o1 != 0) {
    /* Outputs for IfAction SubSystem: '<S8>/Valve Value Conversion' incorporates:
     *  ActionPort: '<S31>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive1_o1,
      &tank_B.ValveValueConversion_h, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion_h);

    /* End of Outputs for SubSystem: '<S8>/Valve Value Conversion' */
  }

  /* End of If: '<S8>/Valve If' */

  /* S-Function (sdspFromNetwork): '<S8>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib[0U]);
  samplesRead_e = 1;
  LibOutputs_Network(&tank_DW.UDPReceive2_NetworkLib[0U], &tank_B.UDPReceive2_o1,
                     &samplesRead_e);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive2_o2 = (uint16_T)samplesRead_e;

  /* End of S-Function (sdspFromNetwork): '<S8>/UDP Receive2' */

  /* If: '<S8>/Valve If1' */
  if (tank_B.UDPReceive2_o1 != 0) {
    /* Outputs for IfAction SubSystem: '<S8>/Valve Value Conversion1' incorporates:
     *  ActionPort: '<S32>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive2_o1,
      &tank_B.ValveValueConversion1_i, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion1_i);

    /* End of Outputs for SubSystem: '<S8>/Valve Value Conversion1' */
  }

  /* End of If: '<S8>/Valve If1' */

  /* S-Function (sdspFromNetwork): '<S8>/UDP Receive4' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive4_NetworkLib[0U]);
  samplesRead_f = 1;
  LibOutputs_Network(&tank_DW.UDPReceive4_NetworkLib[0U], &tank_B.UDPReceive4_o1,
                     &samplesRead_f);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive4_o2 = (uint16_T)samplesRead_f;

  /* End of S-Function (sdspFromNetwork): '<S8>/UDP Receive4' */

  /* If: '<S8>/Valve If3' */
  if (tank_B.UDPReceive4_o1 != 0) {
    /* Outputs for IfAction SubSystem: '<S8>/Valve Value Conversion3' incorporates:
     *  ActionPort: '<S33>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive4_o1,
      &tank_B.ValveValueConversion3, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion3);

    /* End of Outputs for SubSystem: '<S8>/Valve Value Conversion3' */
  }

  /* End of If: '<S8>/Valve If3' */

  /* S-Function (sdspFromNetwork): '<S8>/UDP Receive5' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive5_NetworkLib[0U]);
  samplesRead_g = 1;
  LibOutputs_Network(&tank_DW.UDPReceive5_NetworkLib[0U], &tank_B.UDPReceive5_o1,
                     &samplesRead_g);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  tank_B.UDPReceive5_o2 = (uint16_T)samplesRead_g;

  /* End of S-Function (sdspFromNetwork): '<S8>/UDP Receive5' */

  /* If: '<S8>/Valve If4' */
  if (tank_B.UDPReceive5_o1 != 0) {
    /* Outputs for IfAction SubSystem: '<S8>/Valve Value Conversion4' incorporates:
     *  ActionPort: '<S34>/Action Port'
     */
    tank_ValveValueConversion(tank_B.UDPReceive5_o1,
      &tank_B.ValveValueConversion4, (P_ValveValueConversion_tank_T *)
      &tank_P.ValveValueConversion4);

    /* End of Outputs for SubSystem: '<S8>/Valve Value Conversion4' */
  }

  /* End of If: '<S8>/Valve If4' */
  /* End of Outputs for SubSystem: '<S1>/PLC Station 5' */

  /* Update for RateTransition: '<S1>/Rate Transition' */
  tank_DW.RateTransition_Buffer0 = tank_B.ValveValueConversion_d.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition1' */
  tank_DW.RateTransition1_Buffer0 = tank_B.PumpValueConversion_n.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition10' */
  tank_DW.RateTransition10_Buffer0 = tank_B.PumpValueConversion_k.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition11' */
  tank_DW.RateTransition11_Buffer0 = tank_B.ValveValueConversion_g.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition12' */
  tank_DW.RateTransition12_Buffer0 = tank_B.ValveValueConversion1_m.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition13' */
  tank_DW.RateTransition13_Buffer0 = tank_B.PumpValueConversion_j.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition14' */
  tank_DW.RateTransition14_Buffer0 = tank_B.ValveValueConversion_h.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition15' */
  tank_DW.RateTransition15_Buffer0 = tank_B.ValveValueConversion1_i.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition16' */
  tank_DW.RateTransition16_Buffer0 = tank_B.ValveValueConversion3.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition17' */
  tank_DW.RateTransition17_Buffer0 = tank_B.ValveValueConversion4.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition2' */
  tank_DW.RateTransition2_Buffer0 = tank_B.ValveValueConversion1_d.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition3' */
  tank_DW.RateTransition3_Buffer0 = tank_B.ValveValueConversion2.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition4' */
  tank_DW.RateTransition4_Buffer0 = tank_B.PumpValueConversion.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition5' */
  tank_DW.RateTransition5_Buffer0 = tank_B.ValveValueConversion.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition6' */
  tank_DW.RateTransition6_Buffer0 = tank_B.ValveValueConversion1.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition7' */
  tank_DW.RateTransition7_Buffer0 = tank_B.PumpValueConversion_a.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition8' */
  tank_DW.RateTransition8_Buffer0 = tank_B.ValveValueConversion_n.Subtract;

  /* Update for RateTransition: '<S1>/Rate Transition9' */
  tank_DW.RateTransition9_Buffer0 = tank_B.ValveValueConversion1_p.Subtract;
}

/* Model step function for TID3 */
void tank_step3(void)                  /* Sample time: [0.1s, 0.0s] */
{
  char_T *sErr;

  /* Outputs for Atomic SubSystem: '<S1>/  PLC Station 2' */
  /* Sum: '<S12>/Add' incorporates:
   *  Constant: '<S12>/Constant'
   *  Constant: '<S12>/Constant1'
   *  Product: '<S12>/Product'
   */
  tank_B.Add_n = tank_B.RateTransition_o * tank_P.Constant_Value_ai +
    tank_P.Constant1_Value_f;

  /* Update for S-Function (sdspToNetwork): '<S2>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_a[0U]);
  LibUpdate_Network(&tank_DW.UDPSend_NetworkLib_a[0U], &tank_B.Add_n, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S2>/UDP Send' */

  /* Update for S-Function (sdspToNetwork): '<S2>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_h[0U]);
  LibUpdate_Network(&tank_DW.UDPSend1_NetworkLib_h[0U],
                    &tank_B.RateTransition1_n, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S2>/UDP Send1' */
  /* End of Outputs for SubSystem: '<S1>/  PLC Station 2' */

  /* Outputs for Atomic SubSystem: '<S1>/ PLC Station 1' */
  /* Sum: '<S16>/Add' incorporates:
   *  Constant: '<S16>/Constant'
   *  Constant: '<S16>/Constant1'
   *  Product: '<S16>/Product'
   */
  tank_B.Add_l = tank_B.RateTransition_n * tank_P.Constant_Value_le +
    tank_P.Constant1_Value_g;

  /* Update for S-Function (sdspToNetwork): '<S3>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_g[0U]);
  LibUpdate_Network(&tank_DW.UDPSend_NetworkLib_g[0U], &tank_B.Add_l, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S3>/UDP Send' */

  /* Update for S-Function (sdspToNetwork): '<S3>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_k[0U]);
  LibUpdate_Network(&tank_DW.UDPSend1_NetworkLib_k[0U],
                    &tank_B.RateTransition1_f, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S3>/UDP Send1' */

  /* Update for S-Function (sdspToNetwork): '<S3>/UDP Send2' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend2_NetworkLib_l[0U]);
  LibUpdate_Network(&tank_DW.UDPSend2_NetworkLib_l[0U],
                    &tank_B.RateTransition2_h, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S3>/UDP Send2' */

  /* Update for S-Function (sdspToNetwork): '<S3>/UDP Send3' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend3_NetworkLib_c[0U]);
  LibUpdate_Network(&tank_DW.UDPSend3_NetworkLib_c[0U],
                    &tank_B.RateTransition3_i, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S3>/UDP Send3' */
  /* End of Outputs for SubSystem: '<S1>/ PLC Station 1' */

  /* Outputs for Atomic SubSystem: '<S1>/PLC Station 3' */
  /* Sum: '<S21>/Add' incorporates:
   *  Constant: '<S21>/Constant'
   *  Constant: '<S21>/Constant1'
   *  Product: '<S21>/Product'
   */
  tank_B.Add_i = tank_B.RateTransition_e * tank_P.Constant_Value_i +
    tank_P.Constant1_Value_c;

  /* Update for S-Function (sdspToNetwork): '<S6>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_o[0U]);
  LibUpdate_Network(&tank_DW.UDPSend_NetworkLib_o[0U], &tank_B.Add_i, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S6>/UDP Send' */

  /* Update for S-Function (sdspToNetwork): '<S6>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_m[0U]);
  LibUpdate_Network(&tank_DW.UDPSend1_NetworkLib_m[0U],
                    &tank_B.RateTransition1_m, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S6>/UDP Send1' */
  /* End of Outputs for SubSystem: '<S1>/PLC Station 3' */

  /* Outputs for Atomic SubSystem: '<S1>/PLC Station 4' */
  /* Sum: '<S25>/Add' incorporates:
   *  Constant: '<S25>/Constant'
   *  Constant: '<S25>/Constant1'
   *  Product: '<S25>/Product'
   */
  tank_B.Add_k = tank_B.RateTransition_k * tank_P.Constant_Value_is +
    tank_P.Constant1_Value_gk;

  /* Update for S-Function (sdspToNetwork): '<S7>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_m[0U]);
  LibUpdate_Network(&tank_DW.UDPSend_NetworkLib_m[0U], &tank_B.Add_k, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S7>/UDP Send' */

  /* Update for S-Function (sdspToNetwork): '<S7>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_d[0U]);
  LibUpdate_Network(&tank_DW.UDPSend1_NetworkLib_d[0U],
                    &tank_B.RateTransition1_k, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S7>/UDP Send1' */
  /* End of Outputs for SubSystem: '<S1>/PLC Station 4' */

  /* Outputs for Atomic SubSystem: '<S1>/PLC Station 5' */
  /* Sum: '<S29>/Add' incorporates:
   *  Constant: '<S29>/Constant'
   *  Constant: '<S29>/Constant1'
   *  Product: '<S29>/Product'
   */
  tank_B.Add = tank_B.RateTransition_g * tank_P.Constant_Value_e +
    tank_P.Constant1_Value_b;

  /* Update for S-Function (sdspToNetwork): '<S8>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib[0U]);
  LibUpdate_Network(&tank_DW.UDPSend_NetworkLib[0U], &tank_B.Add, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S8>/UDP Send' */

  /* Update for S-Function (sdspToNetwork): '<S8>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib[0U]);
  LibUpdate_Network(&tank_DW.UDPSend1_NetworkLib[0U], &tank_B.RateTransition1_o,
                    1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S8>/UDP Send1' */

  /* Update for S-Function (sdspToNetwork): '<S8>/UDP Send2' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend2_NetworkLib[0U]);
  LibUpdate_Network(&tank_DW.UDPSend2_NetworkLib[0U], &tank_B.RateTransition2_p,
                    1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S8>/UDP Send2' */

  /* Update for S-Function (sdspToNetwork): '<S8>/UDP Send3' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend3_NetworkLib[0U]);
  LibUpdate_Network(&tank_DW.UDPSend3_NetworkLib[0U], &tank_B.RateTransition3_c,
                    1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S8>/UDP Send3' */

  /* Update for S-Function (sdspToNetwork): '<S8>/UDP Send5' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend5_NetworkLib[0U]);
  LibUpdate_Network(&tank_DW.UDPSend5_NetworkLib[0U], &tank_B.RateTransition4_i,
                    1);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S8>/UDP Send5' */
  /* End of Outputs for SubSystem: '<S1>/PLC Station 5' */
}

/* Model step wrapper function for compatibility with a static main program */
void tank_step(int_T tid)
{
  switch (tid) {
   case 0 :
    tank_step0();
    break;

   case 2 :
    tank_step2();
    break;

   case 3 :
    tank_step3();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void tank_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)tank_M, 0,
                sizeof(RT_MODEL_tank_T));
  (tank_M)->Timing.TaskCounters.cLimit[0] = 1;
  (tank_M)->Timing.TaskCounters.cLimit[1] = 1;
  (tank_M)->Timing.TaskCounters.cLimit[2] = 10;
  (tank_M)->Timing.TaskCounters.cLimit[3] = 100;

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&tank_M->solverInfo, &tank_M->Timing.simTimeStep);
    rtsiSetTPtr(&tank_M->solverInfo, &rtmGetTPtr(tank_M));
    rtsiSetStepSizePtr(&tank_M->solverInfo, &tank_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&tank_M->solverInfo, (&rtmGetErrorStatus(tank_M)));
    rtsiSetRTModelPtr(&tank_M->solverInfo, tank_M);
  }

  rtsiSetSimTimeStep(&tank_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&tank_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(tank_M, &tank_M->Timing.tArray[0]);
  rtmSetTFinal(tank_M, -1);
  tank_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    tank_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(tank_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(tank_M->rtwLogInfo, (NULL));
    rtliSetLogT(tank_M->rtwLogInfo, "tout");
    rtliSetLogX(tank_M->rtwLogInfo, "");
    rtliSetLogXFinal(tank_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(tank_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(tank_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(tank_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(tank_M->rtwLogInfo, 1);
    rtliSetLogY(tank_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(tank_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(tank_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &tank_B), 0,
                sizeof(B_tank_T));

  {
    int32_T i;
    for (i = 0; i < 1125; i++) {
      tank_B.STATE_1[i] = 0.0;
    }

    tank_B.TransportDelay3 = 0.0;
    tank_B.INPUT_1_1_1[0] = 0.0;
    tank_B.INPUT_1_1_1[1] = 0.0;
    tank_B.INPUT_1_1_1[2] = 0.0;
    tank_B.INPUT_1_1_1[3] = 0.0;
    tank_B.TransportDelay5 = 0.0;
    tank_B.INPUT_2_1_1[0] = 0.0;
    tank_B.INPUT_2_1_1[1] = 0.0;
    tank_B.INPUT_2_1_1[2] = 0.0;
    tank_B.INPUT_2_1_1[3] = 0.0;
    tank_B.TransportDelay7 = 0.0;
    tank_B.INPUT_3_1_1[0] = 0.0;
    tank_B.INPUT_3_1_1[1] = 0.0;
    tank_B.INPUT_3_1_1[2] = 0.0;
    tank_B.INPUT_3_1_1[3] = 0.0;
    tank_B.TransportDelay15 = 0.0;
    tank_B.INPUT_4_1_1[0] = 0.0;
    tank_B.INPUT_4_1_1[1] = 0.0;
    tank_B.INPUT_4_1_1[2] = 0.0;
    tank_B.INPUT_4_1_1[3] = 0.0;
    tank_B.DestinationInletSwitch = 0.0;
    tank_B.INPUT_5_1_1[0] = 0.0;
    tank_B.INPUT_5_1_1[1] = 0.0;
    tank_B.INPUT_5_1_1[2] = 0.0;
    tank_B.INPUT_5_1_1[3] = 0.0;
    tank_B.TransportDelay16 = 0.0;
    tank_B.INPUT_6_1_1[0] = 0.0;
    tank_B.INPUT_6_1_1[1] = 0.0;
    tank_B.INPUT_6_1_1[2] = 0.0;
    tank_B.INPUT_6_1_1[3] = 0.0;
    tank_B.DestinationReturnSwitch = 0.0;
    tank_B.INPUT_7_1_1[0] = 0.0;
    tank_B.INPUT_7_1_1[1] = 0.0;
    tank_B.INPUT_7_1_1[2] = 0.0;
    tank_B.INPUT_7_1_1[3] = 0.0;
    tank_B.rpm = 0.0;
    tank_B.rpm1 = 0.0;
    tank_B.Switch1 = 0.0;
    tank_B.INPUT_8_1_1[0] = 0.0;
    tank_B.INPUT_8_1_1[1] = 0.0;
    tank_B.INPUT_8_1_1[2] = 0.0;
    tank_B.INPUT_8_1_1[3] = 0.0;
    tank_B.TransportDelay17 = 0.0;
    tank_B.INPUT_9_1_1[0] = 0.0;
    tank_B.INPUT_9_1_1[1] = 0.0;
    tank_B.INPUT_9_1_1[2] = 0.0;
    tank_B.INPUT_9_1_1[3] = 0.0;
    tank_B.TransportDelay = 0.0;
    tank_B.INPUT_10_1_1[0] = 0.0;
    tank_B.INPUT_10_1_1[1] = 0.0;
    tank_B.INPUT_10_1_1[2] = 0.0;
    tank_B.INPUT_10_1_1[3] = 0.0;
    tank_B.TransportDelay11 = 0.0;
    tank_B.INPUT_11_1_1[0] = 0.0;
    tank_B.INPUT_11_1_1[1] = 0.0;
    tank_B.INPUT_11_1_1[2] = 0.0;
    tank_B.INPUT_11_1_1[3] = 0.0;
    tank_B.Sourcetankreturnswitch = 0.0;
    tank_B.INPUT_12_1_1[0] = 0.0;
    tank_B.INPUT_12_1_1[1] = 0.0;
    tank_B.INPUT_12_1_1[2] = 0.0;
    tank_B.INPUT_12_1_1[3] = 0.0;
    tank_B.TransportDelay10 = 0.0;
    tank_B.INPUT_13_1_1[0] = 0.0;
    tank_B.INPUT_13_1_1[1] = 0.0;
    tank_B.INPUT_13_1_1[2] = 0.0;
    tank_B.INPUT_13_1_1[3] = 0.0;
    tank_B.SourceTankdespatchswitch = 0.0;
    tank_B.INPUT_14_1_1[0] = 0.0;
    tank_B.INPUT_14_1_1[1] = 0.0;
    tank_B.INPUT_14_1_1[2] = 0.0;
    tank_B.INPUT_14_1_1[3] = 0.0;
    tank_B.rpm2 = 0.0;
    tank_B.rpm3 = 0.0;
    tank_B.Switch2 = 0.0;
    tank_B.INPUT_15_1_1[0] = 0.0;
    tank_B.INPUT_15_1_1[1] = 0.0;
    tank_B.INPUT_15_1_1[2] = 0.0;
    tank_B.INPUT_15_1_1[3] = 0.0;
    tank_B.TransportDelay12 = 0.0;
    tank_B.INPUT_16_1_1[0] = 0.0;
    tank_B.INPUT_16_1_1[1] = 0.0;
    tank_B.INPUT_16_1_1[2] = 0.0;
    tank_B.INPUT_16_1_1[3] = 0.0;
    tank_B.rpm4 = 0.0;
    tank_B.rpm5 = 0.0;
    tank_B.Switch3 = 0.0;
    tank_B.INPUT_17_1_1[0] = 0.0;
    tank_B.INPUT_17_1_1[1] = 0.0;
    tank_B.INPUT_17_1_1[2] = 0.0;
    tank_B.INPUT_17_1_1[3] = 0.0;
    tank_B.TransportDelay13 = 0.0;
    tank_B.INPUT_18_1_1[0] = 0.0;
    tank_B.INPUT_18_1_1[1] = 0.0;
    tank_B.INPUT_18_1_1[2] = 0.0;
    tank_B.INPUT_18_1_1[3] = 0.0;
    tank_B.rpm6 = 0.0;
    tank_B.rpm7 = 0.0;
    tank_B.Switch4 = 0.0;
    tank_B.INPUT_19_1_1[0] = 0.0;
    tank_B.INPUT_19_1_1[1] = 0.0;
    tank_B.INPUT_19_1_1[2] = 0.0;
    tank_B.INPUT_19_1_1[3] = 0.0;
    tank_B.TransportDelay14 = 0.0;
    tank_B.INPUT_20_1_1[0] = 0.0;
    tank_B.INPUT_20_1_1[1] = 0.0;
    tank_B.INPUT_20_1_1[2] = 0.0;
    tank_B.INPUT_20_1_1[3] = 0.0;
    tank_B.rpm8 = 0.0;
    tank_B.rpm9 = 0.0;
    tank_B.Switch5 = 0.0;
    tank_B.INPUT_21_1_1[0] = 0.0;
    tank_B.INPUT_21_1_1[1] = 0.0;
    tank_B.INPUT_21_1_1[2] = 0.0;
    tank_B.INPUT_21_1_1[3] = 0.0;
    tank_B.TransportDelay9 = 0.0;
    tank_B.INPUT_22_1_1[0] = 0.0;
    tank_B.INPUT_22_1_1[1] = 0.0;
    tank_B.INPUT_22_1_1[2] = 0.0;
    tank_B.INPUT_22_1_1[3] = 0.0;
    tank_B.RateTransition = 0.0;
    tank_B.RateTransition1 = 0.0;
    tank_B.RateTransition10 = 0.0;
    tank_B.RateTransition11 = 0.0;
    tank_B.RateTransition12 = 0.0;
    tank_B.RateTransition13 = 0.0;
    tank_B.RateTransition14 = 0.0;
    tank_B.RateTransition15 = 0.0;
    tank_B.RateTransition16 = 0.0;
    tank_B.RateTransition17 = 0.0;
    tank_B.RateTransition2 = 0.0;
    tank_B.RateTransition3 = 0.0;
    tank_B.RateTransition4 = 0.0;
    tank_B.RateTransition5 = 0.0;
    tank_B.RateTransition6 = 0.0;
    tank_B.RateTransition7 = 0.0;
    tank_B.RateTransition8 = 0.0;
    tank_B.RateTransition9 = 0.0;
    tank_B.RateTransition_g = 0.0;
    tank_B.Add = 0.0;
    tank_B.RateTransition1_o = 0.0;
    tank_B.RateTransition2_p = 0.0;
    tank_B.RateTransition3_c = 0.0;
    tank_B.RateTransition4_i = 0.0;
    tank_B.RateTransition_k = 0.0;
    tank_B.Add_k = 0.0;
    tank_B.RateTransition1_k = 0.0;
    tank_B.RateTransition_e = 0.0;
    tank_B.Add_i = 0.0;
    tank_B.RateTransition1_m = 0.0;
    tank_B.RateTransition_n = 0.0;
    tank_B.Add_l = 0.0;
    tank_B.RateTransition1_f = 0.0;
    tank_B.RateTransition2_h = 0.0;
    tank_B.RateTransition3_i = 0.0;
    tank_B.RateTransition_o = 0.0;
    tank_B.Add_n = 0.0;
    tank_B.RateTransition1_n = 0.0;
    tank_B.ValveValueConversion4.Subtract = 0.0;
    tank_B.ValveValueConversion3.Subtract = 0.0;
    tank_B.ValveValueConversion1_i.Subtract = 0.0;
    tank_B.ValveValueConversion_h.Subtract = 0.0;
    tank_B.PumpValueConversion_j.Subtract = 0.0;
    tank_B.ValveValueConversion1_m.Subtract = 0.0;
    tank_B.ValveValueConversion_g.Subtract = 0.0;
    tank_B.PumpValueConversion_k.Subtract = 0.0;
    tank_B.ValveValueConversion1_p.Subtract = 0.0;
    tank_B.ValveValueConversion_n.Subtract = 0.0;
    tank_B.PumpValueConversion_a.Subtract = 0.0;
    tank_B.ValveValueConversion2.Subtract = 0.0;
    tank_B.ValveValueConversion1_d.Subtract = 0.0;
    tank_B.ValveValueConversion_d.Subtract = 0.0;
    tank_B.PumpValueConversion_n.Subtract = 0.0;
    tank_B.ValveValueConversion1.Subtract = 0.0;
    tank_B.ValveValueConversion.Subtract = 0.0;
    tank_B.PumpValueConversion.Subtract = 0.0;
  }

  /* states (dwork) */
  (void) memset((void *)&tank_DW, 0,
                sizeof(DW_tank_T));
  tank_DW.INPUT_1_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_1_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_2_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_2_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_3_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_3_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_4_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_4_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_5_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_5_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_6_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_6_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_7_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_7_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_8_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_8_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_9_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_9_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_10_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_10_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_11_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_11_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_12_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_12_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_13_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_13_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_14_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_14_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_15_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_15_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_16_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_16_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_17_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_17_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_18_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_18_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_19_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_19_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_20_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_20_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_21_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_21_1_1_discrete[1] = 0.0;
  tank_DW.INPUT_22_1_1_discrete[0] = 0.0;
  tank_DW.INPUT_22_1_1_discrete[1] = 0.0;

  {
    int32_T i;
    for (i = 0; i < 163; i++) {
      tank_DW.STATE_1_DiscStates[i] = 0.0;
    }
  }

  tank_DW.RateTransition_Buffer0 = 0.0;
  tank_DW.RateTransition1_Buffer0 = 0.0;
  tank_DW.RateTransition10_Buffer0 = 0.0;
  tank_DW.RateTransition11_Buffer0 = 0.0;
  tank_DW.RateTransition12_Buffer0 = 0.0;
  tank_DW.RateTransition13_Buffer0 = 0.0;
  tank_DW.RateTransition14_Buffer0 = 0.0;
  tank_DW.RateTransition15_Buffer0 = 0.0;
  tank_DW.RateTransition16_Buffer0 = 0.0;
  tank_DW.RateTransition17_Buffer0 = 0.0;
  tank_DW.RateTransition2_Buffer0 = 0.0;
  tank_DW.RateTransition3_Buffer0 = 0.0;
  tank_DW.RateTransition4_Buffer0 = 0.0;
  tank_DW.RateTransition5_Buffer0 = 0.0;
  tank_DW.RateTransition6_Buffer0 = 0.0;
  tank_DW.RateTransition7_Buffer0 = 0.0;
  tank_DW.RateTransition8_Buffer0 = 0.0;
  tank_DW.RateTransition9_Buffer0 = 0.0;

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive1_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive2_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive4_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive5_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend1_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend2_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend3_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend5_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive_NetworkLib_m[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive1_NetworkLib_f[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive2_NetworkLib_g[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend_NetworkLib_m[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend1_NetworkLib_d[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive_NetworkLib_g[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive1_NetworkLib_o[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive2_NetworkLib_a[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend_NetworkLib_o[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend1_NetworkLib_m[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive1_NetworkLib_b[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive_NetworkLib_h[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive2_NetworkLib_n[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive3_NetworkLib[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend_NetworkLib_g[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend1_NetworkLib_k[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend2_NetworkLib_l[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend3_NetworkLib_c[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive_NetworkLib_p[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive1_NetworkLib_ou[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPReceive2_NetworkLib_p[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend_NetworkLib_a[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 137; i++) {
      tank_DW.UDPSend1_NetworkLib_h[i] = 0.0;
    }
  }

  tank_DW.TransportDelay3_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay3_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay5_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay5_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay7_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay7_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay15_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay15_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay16_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay16_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay1_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay1_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay17_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay17_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay11_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay11_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay10_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay10_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay2_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay2_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay12_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay12_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay4_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay4_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay13_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay13_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay6_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay6_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay14_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay14_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay8_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay8_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  tank_DW.TransportDelay9_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 2048; i++) {
      tank_DW.TransportDelay9_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(tank_M->rtwLogInfo, 0.0, rtmGetTFinal(tank_M),
    tank_M->Timing.stepSize0, (&rtmGetErrorStatus(tank_M)));

  {
    NeslSimulator *tmp;
    NeuDiagnosticManager *diagnosticManager;
    real_T modelParameters_mSolverToleranc;
    real_T modelParameters_mFixedStepSize;
    boolean_T modelParameters_mVariableStepSo;
    NeuDiagnosticTree *diagnosticTree;
    int32_T tmp_0;
    char *msg;
    NeslSimulationData *simulationData;
    real_T time;
    real_T time_0;
    char_T *sErr;
    NeModelParameters expl_temp;
    NeParameterBundle expl_temp_0;
    NeModelParameters expl_temp_1;

    /* Start for TransportDelay: '<S1>/Transport Delay3' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay3_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay3_IWORK.Tail = 0;
      tank_DW.TransportDelay3_IWORK.Head = 0;
      tank_DW.TransportDelay3_IWORK.Last = 0;
      tank_DW.TransportDelay3_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay3_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay3_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay3_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay5' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay5_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay5_IWORK.Tail = 0;
      tank_DW.TransportDelay5_IWORK.Head = 0;
      tank_DW.TransportDelay5_IWORK.Last = 0;
      tank_DW.TransportDelay5_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay5_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay5_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay5_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay7' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay7_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay7_IWORK.Tail = 0;
      tank_DW.TransportDelay7_IWORK.Head = 0;
      tank_DW.TransportDelay7_IWORK.Last = 0;
      tank_DW.TransportDelay7_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay7_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay7_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay7_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay15' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay15_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay15_IWORK.Tail = 0;
      tank_DW.TransportDelay15_IWORK.Head = 0;
      tank_DW.TransportDelay15_IWORK.Last = 0;
      tank_DW.TransportDelay15_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay15_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay15_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay15_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay16' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay16_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay16_IWORK.Tail = 0;
      tank_DW.TransportDelay16_IWORK.Head = 0;
      tank_DW.TransportDelay16_IWORK.Last = 0;
      tank_DW.TransportDelay16_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay16_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay16_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay16_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay1' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay1_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay1_IWORK.Tail = 0;
      tank_DW.TransportDelay1_IWORK.Head = 0;
      tank_DW.TransportDelay1_IWORK.Last = 0;
      tank_DW.TransportDelay1_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay1_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay1_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay17' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay17_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay17_IWORK.Tail = 0;
      tank_DW.TransportDelay17_IWORK.Head = 0;
      tank_DW.TransportDelay17_IWORK.Last = 0;
      tank_DW.TransportDelay17_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay17_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay17_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay17_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay_IWORK.Tail = 0;
      tank_DW.TransportDelay_IWORK.Head = 0;
      tank_DW.TransportDelay_IWORK.Last = 0;
      tank_DW.TransportDelay_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay11' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay11_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay11_IWORK.Tail = 0;
      tank_DW.TransportDelay11_IWORK.Head = 0;
      tank_DW.TransportDelay11_IWORK.Last = 0;
      tank_DW.TransportDelay11_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay11_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay11_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay11_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay10' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay10_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay10_IWORK.Tail = 0;
      tank_DW.TransportDelay10_IWORK.Head = 0;
      tank_DW.TransportDelay10_IWORK.Last = 0;
      tank_DW.TransportDelay10_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay10_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay10_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay10_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay2' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay2_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay2_IWORK.Tail = 0;
      tank_DW.TransportDelay2_IWORK.Head = 0;
      tank_DW.TransportDelay2_IWORK.Last = 0;
      tank_DW.TransportDelay2_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay2_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay2_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay2_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay12' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay12_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay12_IWORK.Tail = 0;
      tank_DW.TransportDelay12_IWORK.Head = 0;
      tank_DW.TransportDelay12_IWORK.Last = 0;
      tank_DW.TransportDelay12_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay12_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay12_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay12_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay4' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay4_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay4_IWORK.Tail = 0;
      tank_DW.TransportDelay4_IWORK.Head = 0;
      tank_DW.TransportDelay4_IWORK.Last = 0;
      tank_DW.TransportDelay4_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay4_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay4_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay4_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay13' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay13_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay13_IWORK.Tail = 0;
      tank_DW.TransportDelay13_IWORK.Head = 0;
      tank_DW.TransportDelay13_IWORK.Last = 0;
      tank_DW.TransportDelay13_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay13_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay13_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay13_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay6' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay6_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay6_IWORK.Tail = 0;
      tank_DW.TransportDelay6_IWORK.Head = 0;
      tank_DW.TransportDelay6_IWORK.Last = 0;
      tank_DW.TransportDelay6_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay6_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay6_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay6_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay14' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay14_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay14_IWORK.Tail = 0;
      tank_DW.TransportDelay14_IWORK.Head = 0;
      tank_DW.TransportDelay14_IWORK.Last = 0;
      tank_DW.TransportDelay14_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay14_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay14_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay14_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay8' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay8_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay8_IWORK.Tail = 0;
      tank_DW.TransportDelay8_IWORK.Head = 0;
      tank_DW.TransportDelay8_IWORK.Last = 0;
      tank_DW.TransportDelay8_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay8_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay8_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay8_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for TransportDelay: '<S1>/Transport Delay9' */
    {
      real_T *pBuffer = &tank_DW.TransportDelay9_RWORK.TUbufferArea[0];
      tank_DW.TransportDelay9_IWORK.Tail = 0;
      tank_DW.TransportDelay9_IWORK.Head = 0;
      tank_DW.TransportDelay9_IWORK.Last = 0;
      tank_DW.TransportDelay9_IWORK.CircularBufSize = 1024;
      pBuffer[0] = tank_P.TransportDelay9_InitOutput;
      pBuffer[1024] = tank_M->Timing.t[0];
      tank_DW.TransportDelay9_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
      tank_DW.TransportDelay9_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
    }

    /* Start for SimscapeExecutionBlock: '<S122>/STATE_1' */
    tmp = nesl_lease_simulator(
      "tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1",
      0, 0);
    tank_DW.STATE_1_Simulator = (void *)tmp;
    modelParameters_mVariableStepSo = pointer_is_null(tank_DW.STATE_1_Simulator);
    if (modelParameters_mVariableStepSo) {
      tank_8a2586ff_1_gateway();
      tmp = nesl_lease_simulator(
        "tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1",
        0, 0);
      tank_DW.STATE_1_Simulator = (void *)tmp;
    }

    simulationData = nesl_create_simulation_data();
    tank_DW.STATE_1_SimulationData = (void *)simulationData;
    diagnosticManager = rtw_create_diagnostics();
    tank_DW.STATE_1_DiagnosticManager = (void *)diagnosticManager;
    modelParameters_mSolverToleranc = 0.001;
    modelParameters_mFixedStepSize = 0.001;
    modelParameters_mVariableStepSo = false;
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    expl_temp.mVariableStepSolver = modelParameters_mVariableStepSo;
    expl_temp.mUseSimState = false;
    expl_temp.mStartTime = 0.0;
    expl_temp.mSolverType = NE_SOLVER_TYPE_DISCRETE;
    expl_temp.mSolverTolerance = modelParameters_mSolverToleranc;
    expl_temp.mLoggingMode = SSC_LOGGING_NONE;
    expl_temp.mLoadInitialState = false;
    expl_temp.mLinTrimCompile = false;
    expl_temp.mFixedStepSize = modelParameters_mFixedStepSize;
    tmp_0 = nesl_initialize_simulator((NeslSimulator *)tank_DW.STATE_1_Simulator,
      expl_temp, diagnosticManager);
    if (tmp_0 != 0) {
      modelParameters_mVariableStepSo = error_buffer_is_empty(rtmGetErrorStatus
        (tank_M));
      if (modelParameters_mVariableStepSo) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    expl_temp_0.mRealParameters.mN = 0;
    expl_temp_0.mRealParameters.mX = NULL;
    expl_temp_0.mLogicalParameters.mN = 0;
    expl_temp_0.mLogicalParameters.mX = NULL;
    expl_temp_0.mIntegerParameters.mN = 0;
    expl_temp_0.mIntegerParameters.mX = NULL;
    expl_temp_0.mIndexParameters.mN = 0;
    expl_temp_0.mIndexParameters.mX = NULL;
    nesl_simulator_set_rtps((NeslSimulator *)tank_DW.STATE_1_Simulator,
      expl_temp_0);
    simulationData = (NeslSimulationData *)tank_DW.STATE_1_SimulationData;
    time = tank_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 163;
    simulationData->mData->mDiscStates.mX = (real_T *)
      &tank_DW.STATE_1_DiscStates;
    simulationData->mData->mModeVector.mN = 962;
    simulationData->mData->mModeVector.mX = (int32_T *)&tank_DW.STATE_1_Modes;
    modelParameters_mVariableStepSo = false;
    simulationData->mData->mFoundZcEvents = modelParameters_mVariableStepSo;
    simulationData->mData->mIsMajorTimeStep = true;
    modelParameters_mVariableStepSo = false;
    simulationData->mData->mIsSolverAssertCheck =
      modelParameters_mVariableStepSo;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_0 = ne_simulator_method((NeslSimulator *)tank_DW.STATE_1_Simulator,
      NESL_SIM_INITIALIZEONCE, simulationData, diagnosticManager);
    if (tmp_0 != 0) {
      modelParameters_mVariableStepSo = error_buffer_is_empty(rtmGetErrorStatus
        (tank_M));
      if (modelParameters_mVariableStepSo) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S122>/STATE_1' */

    /* Start for SimscapeExecutionBlock: '<S122>/OUTPUT_1_0' */
    tmp = nesl_lease_simulator(
      "tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1",
      2, 0);
    tank_DW.OUTPUT_1_0_Simulator = (void *)tmp;
    modelParameters_mVariableStepSo = pointer_is_null
      (tank_DW.OUTPUT_1_0_Simulator);
    if (modelParameters_mVariableStepSo) {
      tank_8a2586ff_1_gateway();
      tmp = nesl_lease_simulator(
        "tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1",
        2, 0);
      tank_DW.OUTPUT_1_0_Simulator = (void *)tmp;
    }

    simulationData = nesl_create_simulation_data();
    tank_DW.OUTPUT_1_0_SimulationData = (void *)simulationData;
    diagnosticManager = rtw_create_diagnostics();
    tank_DW.OUTPUT_1_0_DiagnosticManager = (void *)diagnosticManager;
    modelParameters_mSolverToleranc = 0.001;
    modelParameters_mFixedStepSize = 0.001;
    modelParameters_mVariableStepSo = false;
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.OUTPUT_1_0_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    expl_temp_1.mVariableStepSolver = modelParameters_mVariableStepSo;
    expl_temp_1.mUseSimState = false;
    expl_temp_1.mStartTime = 0.0;
    expl_temp_1.mSolverType = NE_SOLVER_TYPE_DISCRETE;
    expl_temp_1.mSolverTolerance = modelParameters_mSolverToleranc;
    expl_temp_1.mLoggingMode = SSC_LOGGING_NONE;
    expl_temp_1.mLoadInitialState = false;
    expl_temp_1.mLinTrimCompile = false;
    expl_temp_1.mFixedStepSize = modelParameters_mFixedStepSize;
    tmp_0 = nesl_initialize_simulator((NeslSimulator *)
      tank_DW.OUTPUT_1_0_Simulator, expl_temp_1, diagnosticManager);
    if (tmp_0 != 0) {
      modelParameters_mVariableStepSo = error_buffer_is_empty(rtmGetErrorStatus
        (tank_M));
      if (modelParameters_mVariableStepSo) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    simulationData = (NeslSimulationData *)tank_DW.OUTPUT_1_0_SimulationData;
    time_0 = tank_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = NULL;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = NULL;
    modelParameters_mVariableStepSo = false;
    simulationData->mData->mFoundZcEvents = modelParameters_mVariableStepSo;
    simulationData->mData->mIsMajorTimeStep = true;
    modelParameters_mVariableStepSo = false;
    simulationData->mData->mIsSolverAssertCheck =
      modelParameters_mVariableStepSo;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    diagnosticManager = (NeuDiagnosticManager *)
      tank_DW.OUTPUT_1_0_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_0 = ne_simulator_method((NeslSimulator *)tank_DW.OUTPUT_1_0_Simulator,
      NESL_SIM_INITIALIZEONCE, simulationData, diagnosticManager);
    if (tmp_0 != 0) {
      modelParameters_mVariableStepSo = error_buffer_is_empty(rtmGetErrorStatus
        (tank_M));
      if (modelParameters_mVariableStepSo) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(tank_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S122>/OUTPUT_1_0' */

    /* Start for Atomic SubSystem: '<S1>/  PLC Station 2' */
    /* Start for S-Function (sdspFromNetwork): '<S2>/UDP Receive' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_p[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive_NetworkLib_p[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive_NetworkLib_p[0U], 0, "0.0.0.0",
                        20001, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive_NetworkLib_p[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_p[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S2>/UDP Receive' */

    /* Start for S-Function (sdspFromNetwork): '<S2>/UDP Receive1' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive1_NetworkLib_ou[0U], 0, "0.0.0.0",
                        20003, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S2>/UDP Receive1' */

    /* Start for S-Function (sdspFromNetwork): '<S2>/UDP Receive2' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive2_NetworkLib_p[0U], 0, "0.0.0.0",
                        20005, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S2>/UDP Receive2' */

    /* Start for S-Function (sdspToNetwork): '<S2>/UDP Send' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_a[0U]);
    CreateUDPInterface(&tank_DW.UDPSend_NetworkLib_a[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend_NetworkLib_a[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 20002, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend_NetworkLib_a[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_a[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S2>/UDP Send' */

    /* Start for S-Function (sdspToNetwork): '<S2>/UDP Send1' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_h[0U]);
    CreateUDPInterface(&tank_DW.UDPSend1_NetworkLib_h[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend1_NetworkLib_h[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 20004, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend1_NetworkLib_h[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_h[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S2>/UDP Send1' */
    /* End of Start for SubSystem: '<S1>/  PLC Station 2' */

    /* Start for Atomic SubSystem: '<S1>/ PLC Station 1' */
    /* Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive1' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive1_NetworkLib_b[0U], 0, "0.0.0.0",
                        10003, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive1' */

    /* Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_h[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive_NetworkLib_h[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive_NetworkLib_h[0U], 0, "0.0.0.0",
                        10001, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive_NetworkLib_h[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_h[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive' */

    /* Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive2' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive2_NetworkLib_n[0U], 0, "0.0.0.0",
                        10007, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive2' */

    /* Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive3' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive3_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive3_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive3_NetworkLib[0U], 0, "0.0.0.0", 10008,
                        "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive3_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive3_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S3>/UDP Receive3' */

    /* Start for S-Function (sdspToNetwork): '<S3>/UDP Send' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_g[0U]);
    CreateUDPInterface(&tank_DW.UDPSend_NetworkLib_g[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend_NetworkLib_g[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 10002, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend_NetworkLib_g[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_g[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S3>/UDP Send' */

    /* Start for S-Function (sdspToNetwork): '<S3>/UDP Send1' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_k[0U]);
    CreateUDPInterface(&tank_DW.UDPSend1_NetworkLib_k[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend1_NetworkLib_k[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 10004, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend1_NetworkLib_k[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_k[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S3>/UDP Send1' */

    /* Start for S-Function (sdspToNetwork): '<S3>/UDP Send2' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend2_NetworkLib_l[0U]);
    CreateUDPInterface(&tank_DW.UDPSend2_NetworkLib_l[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend2_NetworkLib_l[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 10005, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend2_NetworkLib_l[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend2_NetworkLib_l[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S3>/UDP Send2' */

    /* Start for S-Function (sdspToNetwork): '<S3>/UDP Send3' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend3_NetworkLib_c[0U]);
    CreateUDPInterface(&tank_DW.UDPSend3_NetworkLib_c[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend3_NetworkLib_c[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 10006, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend3_NetworkLib_c[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend3_NetworkLib_c[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S3>/UDP Send3' */
    /* End of Start for SubSystem: '<S1>/ PLC Station 1' */

    /* Start for Atomic SubSystem: '<S1>/PLC Station 3' */
    /* Start for S-Function (sdspFromNetwork): '<S6>/UDP Receive' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_g[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive_NetworkLib_g[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive_NetworkLib_g[0U], 0, "0.0.0.0",
                        30001, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive_NetworkLib_g[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_g[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S6>/UDP Receive' */

    /* Start for S-Function (sdspFromNetwork): '<S6>/UDP Receive1' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive1_NetworkLib_o[0U], 0, "0.0.0.0",
                        30003, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S6>/UDP Receive1' */

    /* Start for S-Function (sdspFromNetwork): '<S6>/UDP Receive2' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive2_NetworkLib_a[0U], 0, "0.0.0.0",
                        30005, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S6>/UDP Receive2' */

    /* Start for S-Function (sdspToNetwork): '<S6>/UDP Send' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_o[0U]);
    CreateUDPInterface(&tank_DW.UDPSend_NetworkLib_o[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend_NetworkLib_o[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 30002, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend_NetworkLib_o[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_o[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S6>/UDP Send' */

    /* Start for S-Function (sdspToNetwork): '<S6>/UDP Send1' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_m[0U]);
    CreateUDPInterface(&tank_DW.UDPSend1_NetworkLib_m[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend1_NetworkLib_m[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 30004, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend1_NetworkLib_m[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_m[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S6>/UDP Send1' */
    /* End of Start for SubSystem: '<S1>/PLC Station 3' */

    /* Start for Atomic SubSystem: '<S1>/PLC Station 4' */
    /* Start for S-Function (sdspFromNetwork): '<S7>/UDP Receive' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_m[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive_NetworkLib_m[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive_NetworkLib_m[0U], 0, "0.0.0.0",
                        40001, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive_NetworkLib_m[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_m[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S7>/UDP Receive' */

    /* Start for S-Function (sdspFromNetwork): '<S7>/UDP Receive1' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive1_NetworkLib_f[0U], 0, "0.0.0.0",
                        40003, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S7>/UDP Receive1' */

    /* Start for S-Function (sdspFromNetwork): '<S7>/UDP Receive2' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive2_NetworkLib_g[0U], 0, "0.0.0.0",
                        40005, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S7>/UDP Receive2' */

    /* Start for S-Function (sdspToNetwork): '<S7>/UDP Send' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_m[0U]);
    CreateUDPInterface(&tank_DW.UDPSend_NetworkLib_m[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend_NetworkLib_m[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 40002, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend_NetworkLib_m[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_m[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S7>/UDP Send' */

    /* Start for S-Function (sdspToNetwork): '<S7>/UDP Send1' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_d[0U]);
    CreateUDPInterface(&tank_DW.UDPSend1_NetworkLib_d[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend1_NetworkLib_d[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 40004, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend1_NetworkLib_d[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_d[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S7>/UDP Send1' */
    /* End of Start for SubSystem: '<S1>/PLC Station 4' */

    /* Start for Atomic SubSystem: '<S1>/PLC Station 5' */
    /* Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive_NetworkLib[0U], 0, "0.0.0.0", 50001,
                        "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive' */

    /* Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive1' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive1_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive1_NetworkLib[0U], 0, "0.0.0.0", 50003,
                        "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive1_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive1' */

    /* Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive2' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive2_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive2_NetworkLib[0U], 0, "0.0.0.0", 50008,
                        "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive2_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive2' */

    /* Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive4' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive4_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive4_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive4_NetworkLib[0U], 0, "0.0.0.0", 5009,
                        "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive4_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive4_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive4' */

    /* Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive5' */
    sErr = GetErrorBuffer(&tank_DW.UDPReceive5_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPReceive5_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPReceive5_NetworkLib[0U], 0, "0.0.0.0", 50010,
                        "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPReceive5_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPReceive5_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S8>/UDP Receive5' */

    /* Start for S-Function (sdspToNetwork): '<S8>/UDP Send' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPSend_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 50002, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S8>/UDP Send' */

    /* Start for S-Function (sdspToNetwork): '<S8>/UDP Send1' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPSend1_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend1_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 50004, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend1_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S8>/UDP Send1' */

    /* Start for S-Function (sdspToNetwork): '<S8>/UDP Send2' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend2_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPSend2_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend2_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 50005, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend2_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend2_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S8>/UDP Send2' */

    /* Start for S-Function (sdspToNetwork): '<S8>/UDP Send3' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend3_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPSend3_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend3_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 50006, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend3_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend3_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S8>/UDP Send3' */

    /* Start for S-Function (sdspToNetwork): '<S8>/UDP Send5' */
    sErr = GetErrorBuffer(&tank_DW.UDPSend5_NetworkLib[0U]);
    CreateUDPInterface(&tank_DW.UDPSend5_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&tank_DW.UDPSend5_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "192.168.10.31", 50007, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&tank_DW.UDPSend5_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&tank_DW.UDPSend5_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(tank_M, sErr);
        rtmSetStopRequested(tank_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S8>/UDP Send5' */
    /* End of Start for SubSystem: '<S1>/PLC Station 5' */

    /* Start for RateTransition: '<S1>/Rate Transition' */
    tank_B.RateTransition = tank_P.RateTransition_X0;

    /* Start for RateTransition: '<S1>/Rate Transition1' */
    tank_B.RateTransition1 = tank_P.RateTransition1_X0;

    /* Start for RateTransition: '<S1>/Rate Transition10' */
    tank_B.RateTransition10 = tank_P.RateTransition10_X0;

    /* Start for RateTransition: '<S1>/Rate Transition11' */
    tank_B.RateTransition11 = tank_P.RateTransition11_X0;

    /* Start for RateTransition: '<S1>/Rate Transition12' */
    tank_B.RateTransition12 = tank_P.RateTransition12_X0;

    /* Start for RateTransition: '<S1>/Rate Transition13' */
    tank_B.RateTransition13 = tank_P.RateTransition13_X0;

    /* Start for RateTransition: '<S1>/Rate Transition14' */
    tank_B.RateTransition14 = tank_P.RateTransition14_X0;

    /* Start for RateTransition: '<S1>/Rate Transition15' */
    tank_B.RateTransition15 = tank_P.RateTransition15_X0;

    /* Start for RateTransition: '<S1>/Rate Transition16' */
    tank_B.RateTransition16 = tank_P.RateTransition16_X0;

    /* Start for RateTransition: '<S1>/Rate Transition17' */
    tank_B.RateTransition17 = tank_P.RateTransition17_X0;

    /* Start for RateTransition: '<S1>/Rate Transition2' */
    tank_B.RateTransition2 = tank_P.RateTransition2_X0;

    /* Start for RateTransition: '<S1>/Rate Transition3' */
    tank_B.RateTransition3 = tank_P.RateTransition3_X0;

    /* Start for RateTransition: '<S1>/Rate Transition4' */
    tank_B.RateTransition4 = tank_P.RateTransition4_X0;

    /* Start for RateTransition: '<S1>/Rate Transition5' */
    tank_B.RateTransition5 = tank_P.RateTransition5_X0;

    /* Start for RateTransition: '<S1>/Rate Transition6' */
    tank_B.RateTransition6 = tank_P.RateTransition6_X0;

    /* Start for RateTransition: '<S1>/Rate Transition7' */
    tank_B.RateTransition7 = tank_P.RateTransition7_X0;

    /* Start for RateTransition: '<S1>/Rate Transition8' */
    tank_B.RateTransition8 = tank_P.RateTransition8_X0;

    /* Start for RateTransition: '<S1>/Rate Transition9' */
    tank_B.RateTransition9 = tank_P.RateTransition9_X0;
  }

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition' */
  tank_DW.RateTransition_Buffer0 = tank_P.RateTransition_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition1' */
  tank_DW.RateTransition1_Buffer0 = tank_P.RateTransition1_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition10' */
  tank_DW.RateTransition10_Buffer0 = tank_P.RateTransition10_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition11' */
  tank_DW.RateTransition11_Buffer0 = tank_P.RateTransition11_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition12' */
  tank_DW.RateTransition12_Buffer0 = tank_P.RateTransition12_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition13' */
  tank_DW.RateTransition13_Buffer0 = tank_P.RateTransition13_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition14' */
  tank_DW.RateTransition14_Buffer0 = tank_P.RateTransition14_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition15' */
  tank_DW.RateTransition15_Buffer0 = tank_P.RateTransition15_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition16' */
  tank_DW.RateTransition16_Buffer0 = tank_P.RateTransition16_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition17' */
  tank_DW.RateTransition17_Buffer0 = tank_P.RateTransition17_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition2' */
  tank_DW.RateTransition2_Buffer0 = tank_P.RateTransition2_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition3' */
  tank_DW.RateTransition3_Buffer0 = tank_P.RateTransition3_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition4' */
  tank_DW.RateTransition4_Buffer0 = tank_P.RateTransition4_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition5' */
  tank_DW.RateTransition5_Buffer0 = tank_P.RateTransition5_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition6' */
  tank_DW.RateTransition6_Buffer0 = tank_P.RateTransition6_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition7' */
  tank_DW.RateTransition7_Buffer0 = tank_P.RateTransition7_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition8' */
  tank_DW.RateTransition8_Buffer0 = tank_P.RateTransition8_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition9' */
  tank_DW.RateTransition9_Buffer0 = tank_P.RateTransition9_X0;
}

/* Model terminate function */
void tank_terminate(void)
{
  char_T *sErr;

  /* Terminate for SimscapeExecutionBlock: '<S122>/STATE_1' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    tank_DW.STATE_1_DiagnosticManager);
  nesl_destroy_simulation_data((NeslSimulationData *)
    tank_DW.STATE_1_SimulationData);
  nesl_erase_simulator("tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1");

  /* Terminate for SimscapeExecutionBlock: '<S122>/OUTPUT_1_0' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    tank_DW.OUTPUT_1_0_DiagnosticManager);
  nesl_destroy_simulation_data((NeslSimulationData *)
    tank_DW.OUTPUT_1_0_SimulationData);
  nesl_erase_simulator("tank/Virtual Gas Pipeline /The Gas Pipeline/Primary Pumping station (500 kl//hr)/Solver Configuration_1");

  /* Terminate for Atomic SubSystem: '<S1>/  PLC Station 2' */
  /* Terminate for S-Function (sdspFromNetwork): '<S2>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_p[0U]);
  LibTerminate(&tank_DW.UDPReceive_NetworkLib_p[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive_NetworkLib_p[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_p[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S2>/UDP Receive' */

  /* Terminate for S-Function (sdspFromNetwork): '<S2>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
  LibTerminate(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive1_NetworkLib_ou[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_ou[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S2>/UDP Receive1' */

  /* Terminate for S-Function (sdspFromNetwork): '<S2>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
  LibTerminate(&tank_DW.UDPReceive2_NetworkLib_p[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive2_NetworkLib_p[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_p[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S2>/UDP Receive2' */

  /* Terminate for S-Function (sdspToNetwork): '<S2>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_a[0U]);
  LibTerminate(&tank_DW.UDPSend_NetworkLib_a[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend_NetworkLib_a[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_a[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S2>/UDP Send' */

  /* Terminate for S-Function (sdspToNetwork): '<S2>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_h[0U]);
  LibTerminate(&tank_DW.UDPSend1_NetworkLib_h[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend1_NetworkLib_h[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_h[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S2>/UDP Send1' */
  /* End of Terminate for SubSystem: '<S1>/  PLC Station 2' */

  /* Terminate for Atomic SubSystem: '<S1>/ PLC Station 1' */
  /* Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
  LibTerminate(&tank_DW.UDPReceive1_NetworkLib_b[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive1_NetworkLib_b[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_b[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive1' */

  /* Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_h[0U]);
  LibTerminate(&tank_DW.UDPReceive_NetworkLib_h[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive_NetworkLib_h[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_h[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive' */

  /* Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
  LibTerminate(&tank_DW.UDPReceive2_NetworkLib_n[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive2_NetworkLib_n[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_n[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive2' */

  /* Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive3' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive3_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPReceive3_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive3_NetworkLib[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive3_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S3>/UDP Receive3' */

  /* Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_g[0U]);
  LibTerminate(&tank_DW.UDPSend_NetworkLib_g[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend_NetworkLib_g[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_g[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send' */

  /* Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_k[0U]);
  LibTerminate(&tank_DW.UDPSend1_NetworkLib_k[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend1_NetworkLib_k[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_k[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send1' */

  /* Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send2' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend2_NetworkLib_l[0U]);
  LibTerminate(&tank_DW.UDPSend2_NetworkLib_l[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend2_NetworkLib_l[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend2_NetworkLib_l[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send2' */

  /* Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send3' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend3_NetworkLib_c[0U]);
  LibTerminate(&tank_DW.UDPSend3_NetworkLib_c[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend3_NetworkLib_c[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend3_NetworkLib_c[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S3>/UDP Send3' */
  /* End of Terminate for SubSystem: '<S1>/ PLC Station 1' */

  /* Terminate for Atomic SubSystem: '<S1>/PLC Station 3' */
  /* Terminate for S-Function (sdspFromNetwork): '<S6>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_g[0U]);
  LibTerminate(&tank_DW.UDPReceive_NetworkLib_g[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive_NetworkLib_g[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_g[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S6>/UDP Receive' */

  /* Terminate for S-Function (sdspFromNetwork): '<S6>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
  LibTerminate(&tank_DW.UDPReceive1_NetworkLib_o[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive1_NetworkLib_o[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_o[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S6>/UDP Receive1' */

  /* Terminate for S-Function (sdspFromNetwork): '<S6>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
  LibTerminate(&tank_DW.UDPReceive2_NetworkLib_a[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive2_NetworkLib_a[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_a[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S6>/UDP Receive2' */

  /* Terminate for S-Function (sdspToNetwork): '<S6>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_o[0U]);
  LibTerminate(&tank_DW.UDPSend_NetworkLib_o[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend_NetworkLib_o[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_o[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S6>/UDP Send' */

  /* Terminate for S-Function (sdspToNetwork): '<S6>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_m[0U]);
  LibTerminate(&tank_DW.UDPSend1_NetworkLib_m[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend1_NetworkLib_m[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_m[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S6>/UDP Send1' */
  /* End of Terminate for SubSystem: '<S1>/PLC Station 3' */

  /* Terminate for Atomic SubSystem: '<S1>/PLC Station 4' */
  /* Terminate for S-Function (sdspFromNetwork): '<S7>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib_m[0U]);
  LibTerminate(&tank_DW.UDPReceive_NetworkLib_m[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive_NetworkLib_m[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib_m[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S7>/UDP Receive' */

  /* Terminate for S-Function (sdspFromNetwork): '<S7>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
  LibTerminate(&tank_DW.UDPReceive1_NetworkLib_f[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive1_NetworkLib_f[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib_f[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S7>/UDP Receive1' */

  /* Terminate for S-Function (sdspFromNetwork): '<S7>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
  LibTerminate(&tank_DW.UDPReceive2_NetworkLib_g[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive2_NetworkLib_g[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib_g[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S7>/UDP Receive2' */

  /* Terminate for S-Function (sdspToNetwork): '<S7>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib_m[0U]);
  LibTerminate(&tank_DW.UDPSend_NetworkLib_m[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend_NetworkLib_m[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib_m[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S7>/UDP Send' */

  /* Terminate for S-Function (sdspToNetwork): '<S7>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib_d[0U]);
  LibTerminate(&tank_DW.UDPSend1_NetworkLib_d[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend1_NetworkLib_d[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib_d[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S7>/UDP Send1' */
  /* End of Terminate for SubSystem: '<S1>/PLC Station 4' */

  /* Terminate for Atomic SubSystem: '<S1>/PLC Station 5' */
  /* Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPReceive_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive_NetworkLib[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive' */

  /* Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive1' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive1_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPReceive1_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive1_NetworkLib[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive1_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive1' */

  /* Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive2' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive2_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPReceive2_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive2_NetworkLib[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive2_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive2' */

  /* Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive4' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive4_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPReceive4_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive4_NetworkLib[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive4_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive4' */

  /* Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive5' */
  sErr = GetErrorBuffer(&tank_DW.UDPReceive5_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPReceive5_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPReceive5_NetworkLib[0U], 0);
  DestroyUDPInterface(&tank_DW.UDPReceive5_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S8>/UDP Receive5' */

  /* Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPSend_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend_NetworkLib[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send' */

  /* Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send1' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend1_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPSend1_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend1_NetworkLib[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend1_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send1' */

  /* Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send2' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend2_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPSend2_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend2_NetworkLib[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend2_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send2' */

  /* Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send3' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend3_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPSend3_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend3_NetworkLib[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend3_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send3' */

  /* Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send5' */
  sErr = GetErrorBuffer(&tank_DW.UDPSend5_NetworkLib[0U]);
  LibTerminate(&tank_DW.UDPSend5_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(tank_M, sErr);
    rtmSetStopRequested(tank_M, 1);
  }

  LibDestroy(&tank_DW.UDPSend5_NetworkLib[0U], 1);
  DestroyUDPInterface(&tank_DW.UDPSend5_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S8>/UDP Send5' */
  /* End of Terminate for SubSystem: '<S1>/PLC Station 5' */
}
