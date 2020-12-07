FUNCTION ConvertPressure : SINT
  VAR_INPUT
    Pressure_input : UINT;
  END_VAR
  VAR_OUTPUT
    Pressure_output : INT;
  END_VAR
  VAR
    Pressure_real : LREAL;
    UINT_TO_LREAL22_OUT : LREAL;
    SUB5_OUT : LREAL;
    DIV9_OUT : LREAL;
    MUL16_OUT : LREAL;
    LREAL_TO_INT21_OUT : INT;
  END_VAR

  UINT_TO_LREAL22_OUT := UINT_TO_LREAL(Pressure_input);
  Pressure_real := UINT_TO_LREAL22_OUT;
  SUB5_OUT := SUB(Pressure_real, 13106.96);
  Pressure_real := SUB5_OUT;
  DIV9_OUT := DIV(Pressure_real, 372.1356);
  Pressure_real := DIV9_OUT;
  MUL16_OUT := MUL(Pressure_real, 100.0);
  Pressure_real := MUL16_OUT;
  LREAL_TO_INT21_OUT := LREAL_TO_INT(Pressure_real);
  Pressure_output := LREAL_TO_INT21_OUT;
END_FUNCTION

PROGRAM My_Program
  VAR
    pressure AT %IW0 : UINT;
    pressure_psi AT %QW6 : INT;
    min_sp AT %QW1 : INT;
    max_sp AT %QW2 : INT;
  END_VAR
  VAR
    pump_mode : BOOL;
    pm_pump : BOOL;
    pm_valve : BOOL;
    valve_mode : BOOL;
    vm_pump : BOOL;
    vm_valve : BOOL;
    manual_mode : BOOL;
    mm_pump : BOOL;
    mm_valve : BOOL;
  END_VAR
  VAR
    mode_register AT %QW3 : INT;
    pump_register AT %QW4 : INT;
    valve_register AT %QW5 : INT;
  END_VAR
  VAR
    over_pressure : BOOL;
  END_VAR
  VAR
    pump AT %QX0.0 : BOOL;
    valve AT %QX0.1 : BOOL;
  END_VAR
  VAR
    TOF0 : TOF;
    LE4_ENO : BOOL;
    LE4_OUT : BOOL;
    GE11_ENO : BOOL;
    GE11_OUT : BOOL;
    LE22_ENO : BOOL;
    LE22_OUT : BOOL;
    GE29_ENO : BOOL;
    GE29_OUT : BOOL;
    EQ44_ENO : BOOL;
    EQ44_OUT : BOOL;
    EQ50_ENO : BOOL;
    EQ50_OUT : BOOL;
    GE75_OUT : BOOL;
    EQ83_OUT : BOOL;
    EQ88_OUT : BOOL;
    EQ93_OUT : BOOL;
    ConvertPressure99_OUT : SINT;
    ConvertPressure99_Pressure_output : INT;
  END_VAR

  LE4_OUT := LE(EN := pump_mode, IN1 := pressure_psi, IN2 := min_sp, ENO => LE4_ENO);
  IF LE4_OUT THEN
    pm_pump := TRUE; (*set*)
  END_IF;
  GE11_OUT := GE(EN := pump_mode, IN1 := pressure_psi, IN2 := max_sp, ENO => GE11_ENO);
  IF GE11_OUT THEN
    pm_pump := FALSE; (*reset*)
  END_IF;
  IF pump_mode THEN
    pm_valve := FALSE; (*reset*)
  END_IF;
  LE22_OUT := LE(EN := valve_mode, IN1 := pressure_psi, IN2 := min_sp, ENO => LE22_ENO);
  IF LE22_OUT THEN
    vm_valve := FALSE; (*reset*)
  END_IF;
  GE29_OUT := GE(EN := valve_mode, IN1 := pressure_psi, IN2 := max_sp, ENO => GE29_ENO);
  IF GE29_OUT THEN
    vm_valve := TRUE; (*set*)
  END_IF;
  vm_pump := valve_mode;
  EQ44_OUT := EQ(EN := manual_mode, IN1 := pump_register, IN2 := 1, ENO => EQ44_ENO);
  mm_pump := EQ44_OUT;
  EQ50_OUT := EQ(EN := manual_mode, IN1 := valve_register, IN2 := 1, ENO => EQ50_ENO);
  mm_valve := EQ50_OUT;
  pump := mm_pump AND manual_mode OR pm_pump AND pump_mode OR vm_pump AND valve_mode;
  valve := mm_valve AND manual_mode OR pm_valve AND pump_mode OR vm_valve AND valve_mode;
  GE75_OUT := GE(pressure, 6371);
  TOF0(IN := GE75_OUT, PT := T#7000ms);
  over_pressure := TOF0.Q;
  EQ83_OUT := EQ(mode_register, 0);
  manual_mode := EQ83_OUT;
  EQ88_OUT := EQ(mode_register, 1);
  pump_mode := EQ88_OUT;
  EQ93_OUT := EQ(mode_register, 2);
  valve_mode := EQ93_OUT;
  ConvertPressure99_OUT := ConvertPressure(Pressure_input := pressure, Pressure_output => ConvertPressure99_Pressure_output);
  pressure_psi := ConvertPressure99_Pressure_output;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION
