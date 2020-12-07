FUNCTION_BLOCK close_angle
  VAR_INPUT
    current_ang1 : INT;
    current_ang2 : INT;
    ang1 : INT;
    ang2 : INT;
  END_VAR
  VAR
    window : INT := 2;
  END_VAR
  VAR_OUTPUT
    boolean : BOOL := false;
  END_VAR

  IF (current_ang1 >= (ang1 - window)) AND (current_ang1 <= (ang1 + window)) THEN
    IF (current_ang2 >= (ang2 - window)) AND (current_ang2 <= (ang2 + window)) THEN
      boolean := true;
    ELSE
      boolean := false;
    END_IF;
  ELSE
    boolean := false;
  END_IF;
END_FUNCTION_BLOCK

PROGRAM My_Program
  VAR
    Tau1 AT %IW0 : INT;
    Tau2 AT %IW1 : INT;
    Theta1 AT %IW2 : INT;
    Theta2 AT %IW3 : INT;
    Theta1_out AT %QW0 : INT;
    Theta2_out AT %QW1 : INT;
    Theta1_sp AT %QW2 : INT;
    Theta2_sp AT %QW3 : INT;
    Length1 AT %QW4 : UINT := 100;
    Length2 AT %QW5 : UINT := 50;
    count AT %QW6 : INT := 0;
    auto_start1 AT %QW7 : INT := 10;
    auto_start2 AT %QW8 : INT := 20;
    auto_end1 AT %QW9 : INT := 20;
    auto_end2 AT %QW10 : INT := 30;
    completed AT %QW11 : INT := 0;
    remaining AT %QW12 : INT := 0;
    mode AT %QX0.0 : BOOL := 0;
    start AT %QX0.1 : BOOL := 0;
    oscillator AT %QX0.2 : BOOL := 0;
    switch AT %QX0.3 : BOOL := 0;
  END_VAR
  VAR
    CTU0 : CTU;
    TP0 : TP;
    close_angle0 : close_angle;
    close_angle1 : close_angle;
    TON0 : TON;
    TON1 : TON;
    NOT70_OUT : BOOL;
    AND117_OUT : BOOL;
    AND118_OUT : BOOL;
    NOT103_OUT : BOOL;
    MOVE90_ENO : BOOL;
    MOVE90_OUT : INT;
    R_TRIG1 : R_TRIG;
    F_TRIG1 : F_TRIG;
    R_TRIG2 : R_TRIG;
    MUL76_OUT : INT;
    MOD28_ENO : BOOL;
    MOD28_OUT : INT;
    MUX30_OUT : INT;
    MOVE61_ENO : BOOL;
    MOVE61_OUT : INT;
    DIV84_OUT : INT;
    MUX4_OUT : INT;
    MOVE60_ENO : BOOL;
    MOVE60_OUT : INT;
    SUB83_OUT : INT;
    MOVE3_ENO : BOOL;
    MOVE3_OUT : INT;
    MOVE2_ENO : BOOL;
    MOVE2_OUT : INT;
    NOT44_OUT : BOOL;
    MOVE42_ENO : BOOL;
    MOVE42_OUT : INT;
  END_VAR

  NOT70_OUT := NOT(switch);
  close_angle0(EN := NOT70_OUT, current_ang1 := Theta1, current_ang2 := Theta2, ang1 := auto_start1, ang2 := auto_start2);
  AND117_OUT := AND(start, close_angle0.boolean);
  TON0(IN := AND117_OUT, PT := T#2s);
  IF TON0.Q THEN
    oscillator := TRUE; (*set*)
  END_IF;
  IF TON0.Q THEN
    switch := TRUE; (*set*)
  END_IF;
  close_angle1(EN := switch, current_ang1 := Theta1, current_ang2 := Theta2, ang1 := auto_end1, ang2 := auto_end2);
  AND118_OUT := AND(start, close_angle1.boolean);
  TON1(IN := AND118_OUT, PT := T#2s);
  IF TON1.Q THEN
    oscillator := FALSE; (*reset*)
  END_IF;
  IF TON1.Q THEN
    switch := FALSE; (*reset*)
  END_IF;
  NOT103_OUT := NOT(mode);
  MOVE90_OUT := MOVE(EN := NOT103_OUT, IN := 0, ENO => MOVE90_ENO);
  IF MOVE90_ENO THEN
      count := MOVE90_OUT;
  END_IF;
  R_TRIG1(CLK := oscillator);
  F_TRIG1(CLK := oscillator);
  R_TRIG2(CLK := (F_TRIG1.Q OR R_TRIG1.Q) AND start AND mode);
  TP0(IN := start AND mode, PT := T#250ms);
  MUL76_OUT := MUL(count, 2);
  CTU0(CU := R_TRIG2.Q, R := TP0.Q, PV := MUL76_OUT);
  MOD28_OUT := MOD(EN := start, IN1 := CTU0.CV, IN2 := 2, ENO => MOD28_ENO);
  MUX30_OUT := MUX(MOD28_OUT, auto_start1, auto_end1);
  MOVE61_OUT := MOVE(EN := mode, IN := MUX30_OUT, ENO => MOVE61_ENO);
  IF MOVE61_ENO THEN
      Theta1_out := MOVE61_OUT;
  END_IF;
  IF CTU0.Q THEN
    start := FALSE; (*reset*)
  END_IF;
  DIV84_OUT := DIV(CTU0.CV, 2);
  completed := DIV84_OUT;
  MUX4_OUT := MUX(MOD28_OUT, auto_start2, auto_end2);
  MOVE60_OUT := MOVE(EN := mode, IN := MUX4_OUT, ENO => MOVE60_ENO);
  IF MOVE60_ENO THEN
      Theta2_out := MOVE60_OUT;
  END_IF;
  SUB83_OUT := SUB(MUL76_OUT, completed);
  remaining := SUB83_OUT;
  IF NOT(mode) THEN
    start := FALSE; (*reset*)
  END_IF;
  MOVE3_OUT := MOVE(EN := NOT(mode), IN := Theta1_sp, ENO => MOVE3_ENO);
  IF MOVE3_ENO THEN
      Theta1_out := MOVE3_OUT;
  END_IF;
  MOVE2_OUT := MOVE(EN := NOT(mode), IN := Theta2_sp, ENO => MOVE2_ENO);
  IF MOVE2_ENO THEN
      Theta2_out := MOVE2_OUT;
  END_IF;
  NOT44_OUT := NOT(start);
  IF NOT44_OUT THEN
    switch := FALSE; (*reset*)
  END_IF;
  IF NOT44_OUT THEN
    oscillator := FALSE; (*reset*)
  END_IF;
  MOVE42_OUT := MOVE(EN := NOT44_OUT, IN := 0, ENO => MOVE42_ENO);
  IF MOVE42_ENO THEN
      completed := MOVE42_OUT;
  END_IF;
  IF MOVE42_ENO THEN
      remaining := MOVE42_OUT;
  END_IF;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION
