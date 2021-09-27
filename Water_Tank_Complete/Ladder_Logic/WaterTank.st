PROGRAM My_Program
  VAR
    Level AT %IW0 : INT;
    Level_filtered AT %QW6 : INT;
    Alarm AT %QX0.5 : BOOL;
    min_sp AT %QW1 : INT;
    max_sp AT %QW2 : INT;
    mode_register AT %QW3 : INT;
    pump_register AT %QW4 : INT;
    valve_register AT %QW5 : INT;
    pump AT %QX0.0 : BOOL;
    valve AT %QX0.1 : BOOL;
    pump_man AT %QX99.0 : BOOL;
    pump_auto AT %QX99.1 : BOOL;
  END_VAR
  VAR
    LE98_OUT : BOOL;
    GE103_OUT : BOOL;
    EQ104_OUT : BOOL;
    EQ33_OUT : BOOL;
    EQ49_OUT : BOOL;
    EQ38_OUT : BOOL;
  END_VAR

  Level_filtered := Level;
  LE98_OUT := LE(Level_filtered, min_sp);
  IF LE98_OUT THEN
    pump_auto := TRUE; (*set*)
  END_IF;
  GE103_OUT := GE(Level_filtered, max_sp);
  IF GE103_OUT THEN
    pump_auto := FALSE; (*reset*)
  END_IF;
  EQ104_OUT := EQ(pump_register, 1);
  pump_man := EQ104_OUT;
  EQ33_OUT := EQ(valve_register, 1);
  valve := EQ33_OUT;
  EQ49_OUT := EQ(mode_register, 1);
  EQ38_OUT := EQ(mode_register, 2);
  pump := pump_auto AND EQ38_OUT OR pump_man AND EQ49_OUT;
END_PROGRAM

FUNCTION_BLOCK Level_Filtering
  VAR_INPUT
    raw_level : INT;
  END_VAR
  VAR
    level_real : REAL;
    avg : LREAL;
    level_array : ARRAY [1..20] OF REAL;
    i : INT;
    current_array_pos : INT := 1;
  END_VAR
  VAR_OUTPUT
    filtered_level : INT;
  END_VAR

  (* Level Conversion *)
  level_real := INT_TO_REAL(raw_level);
  level_real := level_real - 107.0;
  level_real := level_real * 0.483091;
  level_real := level_real * 100.0;

  (* Store value in average array *)
  level_array[current_array_pos] := level_real;
  current_array_pos := current_array_pos + 1;

  (* Prevent array_pos overflow *)
  if current_array_pos > 20 then
    current_array_pos := 1;
  end_if;

  (* Calculate average *)
  avg := 0.0;
  i := 1;
  while (i < 21) do
    avg := avg + REAL_TO_LREAL(level_array[i]);
    i := i + 1;
  end_while;
  avg := avg / 20.0;

  (* Set output value *)
  filtered_level := LREAL_TO_INT(avg);
END_FUNCTION_BLOCK


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION
