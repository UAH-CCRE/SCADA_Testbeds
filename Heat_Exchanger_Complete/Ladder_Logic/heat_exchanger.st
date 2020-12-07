FUNCTION_BLOCK PID_Conversion
  VAR_INPUT
    IN : REAL;
  END_VAR
  VAR_OUTPUT
    OUT : UINT;
  END_VAR

  IF IN >= 65535.0 THEN
    OUT := 65535;

  ELSIF IN <= 0.0 THEN
    OUT := 0;

  ELSE
    OUT := REAL_TO_UINT(IN);

  END_IF;
    
    
    
END_FUNCTION_BLOCK

PROGRAM My_Program
  VAR
    Hot_Temp_Out AT %IW0 : UINT;
    Cold_Temp_In AT %IW1 : UINT;
    Hot_Temp_In AT %IW2 : UINT;
    Hot_Mass_Flow_In AT %IW3 : UINT;
    Cold_Temp_Out AT %IW4 : UINT;
    Tube_Side_Pressure_Drop AT %IW5 : UINT;
    Shell_Side_Pressure_Drop AT %IW6 : UINT;
    Setpoint AT %QW1 : UINT := 5000;
    Flow AT %QW0 : UINT;
  END_VAR
  VAR
    PID0 : PID;
  END_VAR
  VAR
    pid_kp AT %MD0 : REAL := 0.4;
    pid_tr AT %MD1 : REAL := 0.1;
    pid_td AT %MD2 : REAL := 0.0;
    PID_out AT %MD3 : REAL;
  END_VAR
  VAR
    PID_Conversion0 : PID_Conversion;
    UINT_TO_REAL6_OUT : REAL;
    UINT_TO_REAL4_OUT : REAL;
  END_VAR

  UINT_TO_REAL6_OUT := UINT_TO_REAL(Hot_Temp_Out);
  UINT_TO_REAL4_OUT := UINT_TO_REAL(Setpoint);
  PID0(AUTO := TRUE, PV := UINT_TO_REAL6_OUT, SP := UINT_TO_REAL4_OUT, KP := pid_kp, TR := pid_tr, TD := pid_td, CYCLE := T#50ms);
  PID_Conversion0(IN := PID0.XOUT);
  Flow := PID_Conversion0.OUT;
  PID_out := PID0.XOUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION
