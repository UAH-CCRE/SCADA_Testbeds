/*
 * tank_data.c
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

/* Block parameters (auto storage) */
P_tank_T tank_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S10>/Constant1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S10>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S9>/Constant1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S9>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Constant1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S5>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Constant1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S4>/Constant'
                                        */
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<S12>/Constant'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S12>/Constant1'
                                        */
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<S16>/Constant'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S16>/Constant1'
                                        */
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<S21>/Constant'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S21>/Constant1'
                                        */
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<S25>/Constant'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S25>/Constant1'
                                        */
  0.001,                               /* Expression: 0.001
                                        * Referenced by: '<S29>/Constant'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S29>/Constant1'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay3'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay5'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay7'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay7'
                                        */
  0.01,                                /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay15'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay15'
                                        */
  0.01,                                /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay16'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay16'
                                        */
  3000.0,                              /* Expression: 3000
                                        * Referenced by: '<S57>/rpm'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S57>/rpm1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S57>/Switch1'
                                        */
  0.01,                                /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay17'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay17'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay11'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay11'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay10'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay10'
                                        */
  3000.0,                              /* Expression: 3000
                                        * Referenced by: '<S69>/rpm2'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S69>/rpm3'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S69>/Switch2'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay12'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay12'
                                        */
  3000.0,                              /* Expression: 3000
                                        * Referenced by: '<S71>/rpm4'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S71>/rpm5'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S71>/Switch3'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay13'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay13'
                                        */
  3000.0,                              /* Expression: 3000
                                        * Referenced by: '<S73>/rpm6'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S73>/rpm7'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S73>/Switch4'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay14'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay14'
                                        */
  3000.0,                              /* Expression: 3000
                                        * Referenced by: '<S75>/rpm8'
                                        */
  0.01,                                /* Expression: 0.01
                                        * Referenced by: '<S1>/Transport Delay8'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay8'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S75>/rpm9'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S75>/Switch5'
                                        */
  0.01,                                /* Expression: .01
                                        * Referenced by: '<S1>/Transport Delay9'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Transport Delay9'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S135>/Constant'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S11>/Constant'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S45>/Constant'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S43>/Constant'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S145>/Constant'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S155>/Constant'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S11>/Constant1'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S44>/Constant'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S42>/Constant'
                                        */
  3600.0,                              /* Expression: 3600
                                        * Referenced by: '<S165>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition10'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition11'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition12'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition13'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition14'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition15'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition16'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition17'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition4'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition7'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition8'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition9'
                                        */
  1U,                                  /* Computed Parameter: DestinationInletSwitch_CurrentS
                                        * Referenced by: '<S1>/Destination Inlet Switch'
                                        */
  0U,                                  /* Computed Parameter: DestinationReturnSwitch_Current
                                        * Referenced by: '<S1>/Destination Return Switch'
                                        */
  1U,                                  /* Computed Parameter: Sourcetankreturnswitch_CurrentS
                                        * Referenced by: '<S1>/Source tank return switch'
                                        */
  1U,                                  /* Computed Parameter: SourceTankdespatchswitch_Curren
                                        * Referenced by: '<S1>/Source Tank despatch switch'
                                        */

  /* Start of '<S8>/Valve Value Conversion4' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S34>/'0''
                                        */
  }
  /* End of '<S8>/Valve Value Conversion4' */
  ,

  /* Start of '<S8>/Valve Value Conversion3' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S33>/'0''
                                        */
  }
  /* End of '<S8>/Valve Value Conversion3' */
  ,

  /* Start of '<S8>/Valve Value Conversion1' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S32>/'0''
                                        */
  }
  /* End of '<S8>/Valve Value Conversion1' */
  ,

  /* Start of '<S8>/Valve Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S31>/'0''
                                        */
  }
  /* End of '<S8>/Valve Value Conversion' */
  ,

  /* Start of '<S8>/Pump Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S30>/'0''
                                        */
  }
  /* End of '<S8>/Pump Value Conversion' */
  ,

  /* Start of '<S7>/Valve Value Conversion1' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S28>/'0''
                                        */
  }
  /* End of '<S7>/Valve Value Conversion1' */
  ,

  /* Start of '<S7>/Valve Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S27>/'0''
                                        */
  }
  /* End of '<S7>/Valve Value Conversion' */
  ,

  /* Start of '<S7>/Pump Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S26>/'0''
                                        */
  }
  /* End of '<S7>/Pump Value Conversion' */
  ,

  /* Start of '<S6>/Valve Value Conversion1' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S24>/'0''
                                        */
  }
  /* End of '<S6>/Valve Value Conversion1' */
  ,

  /* Start of '<S6>/Valve Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S23>/'0''
                                        */
  }
  /* End of '<S6>/Valve Value Conversion' */
  ,

  /* Start of '<S6>/Pump Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S22>/'0''
                                        */
  }
  /* End of '<S6>/Pump Value Conversion' */
  ,

  /* Start of '<S3>/Valve Value Conversion2' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S20>/'0''
                                        */
  }
  /* End of '<S3>/Valve Value Conversion2' */
  ,

  /* Start of '<S3>/Valve Value Conversion1' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S19>/'0''
                                        */
  }
  /* End of '<S3>/Valve Value Conversion1' */
  ,

  /* Start of '<S3>/Valve Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S18>/'0''
                                        */
  }
  /* End of '<S3>/Valve Value Conversion' */
  ,

  /* Start of '<S3>/Pump Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S17>/'0''
                                        */
  }
  /* End of '<S3>/Pump Value Conversion' */
  ,

  /* Start of '<S2>/Valve Value Conversion1' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S15>/'0''
                                        */
  }
  /* End of '<S2>/Valve Value Conversion1' */
  ,

  /* Start of '<S2>/Valve Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S14>/'0''
                                        */
  }
  /* End of '<S2>/Valve Value Conversion' */
  ,

  /* Start of '<S2>/Pump Value Conversion' */
  {
    48.0                               /* Expression: 48
                                        * Referenced by: '<S13>/'0''
                                        */
  }
  /* End of '<S2>/Pump Value Conversion' */
};
