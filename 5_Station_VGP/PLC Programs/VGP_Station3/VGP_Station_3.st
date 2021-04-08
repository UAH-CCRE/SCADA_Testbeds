FUNCTION Convert_Pressure : BOOL
  VAR_INPUT
    rawPressure : INT;
  END_VAR
  VAR_OUTPUT
    finalPressure : REAL;
  END_VAR
  VAR
    INT_TO_REAL1_OUT : REAL;
    SUB4_OUT : REAL;
    DIV8_OUT : REAL;
  END_VAR

  INT_TO_REAL1_OUT := INT_TO_REAL(rawPressure);
  finalPressure := INT_TO_REAL1_OUT;
  SUB4_OUT := SUB(finalPressure, 100.0);
  finalPressure := SUB4_OUT;
  DIV8_OUT := DIV(finalPressure, 100.0);
  finalPressure := DIV8_OUT;
END_FUNCTION

FUNCTION_BLOCK Verify_Mode_Change
  VAR_INPUT
    mode : INT;
  END_VAR
  VAR
    previous_mode : INT;
  END_VAR
  VAR_OUTPUT
    Q : BOOL;
  END_VAR

  IF mode <> previous_mode THEN
    IF (mode > 0) AND (previous_mode > 0) THEN
      Q := TRUE;
    ELSE
      Q := FALSE;
    END_IF;
  ELSE
    Q := FALSE;
  END_IF;

  previous_mode := mode;
END_FUNCTION_BLOCK

FUNCTION Finish_Intermediate_Mode : BOOL
  VAR_INPUT
    flow_rate1 : INT;
    flow_rate2 : INT;
    flow_limit : INT;
  END_VAR
  VAR
    negative_flow_limit : INT;
  END_VAR
  VAR_OUTPUT
    Q : BOOL;
  END_VAR

  negative_flow_limit := 0 - flow_limit;

  IF (negative_flow_limit < flow_rate1) AND (flow_rate1 < flow_limit) THEN
    IF (negative_flow_limit < flow_rate2) AND (flow_rate2 < flow_limit) THEN
      Q := TRUE;
    ELSE
      Q := FALSE;
    END_IF;
  ELSE
    Q := FALSE;
  END_IF;
END_FUNCTION

PROGRAM VGP
  VAR
    raw_pressure AT %IW0 : INT;
    raw_station_flow AT %IW1 : INT;
    raw_min_sp AT %QW1 : INT;
    raw_max_sp AT %QW2 : INT;
    operation_mode AT %QW3 : INT;
    manual_pump AT %QW4 : INT;
    manual_relief_valve AT %QW5 : INT;
    manual_isolation_valve AT %QW6 : INT;
    source_tank_flow AT %QW20 : INT;
    destination_tank_flow AT %QW21 : INT;
    high_pressure AT %QW51 : INT;
    pump AT %QX0.0 : BOOL;
    isolation_valve AT %QX0.2 : BOOL;
    relief_valve AT %QX0.1 : BOOL;
  END_VAR
  VAR
    pressure : REAL;
    min_sp : REAL;
    max_sp : REAL;
    recirc_mode : BOOL;
    recirc_isolation_valve : BOOL;
    recirc_relief_valve : BOOL;
    recirc_pump : BOOL;
    cargo_mode : BOOL;
    cargo_isolation_valve : BOOL;
    cargo_relief_valve : BOOL;
    cargo_pump : BOOL;
    man_mode : BOOL;
    man_isolation_valve : BOOL;
    man_relief_valve : BOOL;
    man_pump : BOOL;
    intermediate_mode : BOOL;
    intermediate_isolation_valve : BOOL;
    intermediate_relief_valve : BOOL;
    intermediate_pump : BOOL;
    TOF0 : TOF;
    mode_change : Verify_Mode_Change;
    T0 : TON;
    Convert_Pressure152 : BOOL;
    Convert_Pressure152_finalPressure : REAL;
    Convert_Pressure153 : BOOL;
    Convert_Pressure153_finalPressure : REAL;
    Convert_Pressure154 : BOOL;
    Convert_Pressure154_finalPressure : REAL;
    Finish_Intermediate_Mode215 : BOOL;
    Finish_Intermediate_Mode215_Q : BOOL;
    EQ155_OUT : BOOL;
    LE164_ENO : BOOL;
    LE164_OUT : BOOL;
    GE169_ENO : BOOL;
    GE169_OUT : BOOL;
    EQ40_OUT : BOOL;
    ADD177_OUT : REAL;
    GE173_ENO : BOOL;
    GE173_OUT : BOOL;
    LE33_ENO : BOOL;
    LE33_OUT : BOOL;
    GE38_ENO : BOOL;
    GE38_OUT : BOOL;
    EQ42_OUT : BOOL;
    EQ183_ENO : BOOL;
    EQ183_OUT : BOOL;
    EQ49_ENO : BOOL;
    EQ49_OUT : BOOL;
    EQ63_ENO : BOOL;
    EQ63_OUT : BOOL;
    GE197_ENO : BOOL;
    GE197_OUT : BOOL;
  END_VAR

  Convert_Pressure152 := Convert_Pressure(rawPressure := raw_pressure, finalPressure => Convert_Pressure152_finalPressure);
  pressure := Convert_Pressure152_finalPressure;
  Convert_Pressure153 := Convert_Pressure(rawPressure := raw_min_sp, finalPressure => Convert_Pressure153_finalPressure);
  min_sp := Convert_Pressure153_finalPressure;
  Convert_Pressure154 := Convert_Pressure(rawPressure := raw_max_sp, finalPressure => Convert_Pressure154_finalPressure);
  max_sp := Convert_Pressure154_finalPressure;
  mode_change(mode := operation_mode);
  IF mode_change.Q THEN
    intermediate_mode := TRUE; (*set*)
  END_IF;
  IF intermediate_mode THEN
    intermediate_isolation_valve := TRUE; (*set*)
  END_IF;
  IF intermediate_mode THEN
    intermediate_pump := FALSE; (*reset*)
  END_IF;
  T0(IN := intermediate_mode, PT := T#5000ms);
  intermediate_relief_valve := T0.Q;
  Finish_Intermediate_Mode215 := Finish_Intermediate_Mode(flow_rate1 := source_tank_flow, flow_rate2 := destination_tank_flow, flow_limit := 100, Q => Finish_Intermediate_Mode215_Q);
  IF Finish_Intermediate_Mode215_Q THEN
    intermediate_mode := FALSE; (*reset*)
  END_IF;
  EQ155_OUT := EQ(operation_mode, 2);
  recirc_mode := NOT(intermediate_mode) AND EQ155_OUT;
  IF recirc_mode THEN
    recirc_isolation_valve := TRUE; (*set*)
  END_IF;
  IF recirc_mode THEN
    recirc_relief_valve := FALSE; (*reset*)
  END_IF;
  LE164_OUT := LE(EN := recirc_mode, IN1 := pressure, IN2 := min_sp, ENO => LE164_ENO);
  IF LE164_OUT THEN
    recirc_pump := TRUE; (*set*)
  END_IF;
  GE169_OUT := GE(EN := recirc_mode, IN1 := pressure, IN2 := max_sp, ENO => GE169_ENO);
  IF GE169_OUT THEN
    recirc_pump := FALSE; (*reset*)
  END_IF;
  EQ40_OUT := EQ(operation_mode, 1);
  cargo_mode := NOT(intermediate_mode) AND EQ40_OUT;
  IF cargo_mode THEN
    cargo_isolation_valve := TRUE; (*set*)
  END_IF;
  ADD177_OUT := ADD(max_sp, 1.0);
  GE173_OUT := GE(EN := cargo_mode, IN1 := pressure, IN2 := ADD177_OUT, ENO => GE173_ENO);
  TOF0(IN := GE173_OUT, PT := T#1000ms);
  cargo_relief_valve := TOF0.Q;
  LE33_OUT := LE(EN := cargo_mode, IN1 := pressure, IN2 := min_sp, ENO => LE33_ENO);
  IF LE33_OUT THEN
    cargo_pump := TRUE; (*set*)
  END_IF;
  GE38_OUT := GE(EN := cargo_mode, IN1 := pressure, IN2 := max_sp, ENO => GE38_ENO);
  IF GE38_OUT THEN
    cargo_pump := FALSE; (*reset*)
  END_IF;
  EQ42_OUT := EQ(operation_mode, 0);
  man_mode := EQ42_OUT;
  IF EQ42_OUT THEN
    intermediate_mode := FALSE; (*reset*)
  END_IF;
  EQ183_OUT := EQ(EN := man_mode, IN1 := manual_isolation_valve, IN2 := 1, ENO => EQ183_ENO);
  man_isolation_valve := EQ183_OUT;
  EQ49_OUT := EQ(EN := man_mode, IN1 := manual_relief_valve, IN2 := 1, ENO => EQ49_ENO);
  man_relief_valve := EQ49_OUT;
  EQ63_OUT := EQ(EN := man_mode, IN1 := manual_pump, IN2 := 1, ENO => EQ63_ENO);
  man_pump := EQ63_OUT;
  GE197_OUT := GE(EN := cargo_pump AND cargo_mode OR intermediate_pump AND intermediate_mode OR man_pump AND man_mode OR recirc_pump AND recirc_mode, IN1 := pressure, IN2 := 1.0, ENO => GE197_ENO);
  pump := GE197_OUT;
  isolation_valve := cargo_isolation_valve AND cargo_mode OR intermediate_isolation_valve AND intermediate_mode OR man_isolation_valve AND man_mode OR recirc_isolation_valve AND recirc_mode;
  relief_valve := cargo_relief_valve AND cargo_mode OR intermediate_relief_valve AND intermediate_mode OR man_relief_valve AND man_mode OR recirc_relief_valve AND recirc_mode;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : VGP;
  END_RESOURCE
END_CONFIGURATION
