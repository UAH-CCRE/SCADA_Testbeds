FUNCTION_BLOCK ControllerFunc
  VAR_INPUT
    omega : INT;
    gain : INT;
  END_VAR
  VAR_OUTPUT
    act_com : INT := 0;
    act_com0 : INT := 0;
  END_VAR
  VAR
    U : REAL := 0.0;
    Ga : REAL := 0.0;
    REF : REAL := 1.0;
    ERR : REAL := 0.0;
    X1 : REAL := 0.0;
    X2 : REAL := 0.0;
    Y : REAL := 0.0;
    Y2 : REAL := 0.0;
    Xtemp : REAL := 0.0;
    A11 : REAL := 0.4337;
    A12 : REAL := -36.16;
    A21 : REAL := 0.007232;
    A22 : REAL := 0.7954;
    C1 : REAL := 1000.0;
    C2 : REAL := 5000.0;
    Dd : REAL := 0.0;
    B1 : REAL := 0.007232;
    B2 : REAL := 0.00004093;
    E_k_1 : REAL := 0.0;
    E_k_2 : REAL := 0.0;
    Y_k_1 : REAL := 0.0;
    Y_k_2 : REAL := 0.0;
    tfa0 : REAL := 9.518;
    tfa1 : REAL := -8.448;
    tfb0 : REAL := 1.0;
    tfb1 : REAL := -0.2977;
    tfb2 : REAL := 0.3679;
  END_VAR

  (* Convert the input appropriately to Input *)

  (* Data Dictionary
  E_k_1 = e[k - 1]
  E_k_2 = e[k - 2]
  Y_k_1 = e[k - 1]
  Y_k_2 = e[k - 2]
  *)


  U := INT_TO_REAL(omega); 
  Ga := INT_TO_REAL(Gain);
  U := U - 10000.0; 
  U := U / 10000.0;

  Y := REF - U;
  ERR := REF - U;
  Y2 := 1.0/tfb0 * (tfa0*E_k_1 + tfa1*E_k_2 - b1*Y_k_1 - b2*Y_k_2);
   
  (* Prepare variables for next iteration *)
  E_k_2 := E_k_1;
  E_k_1 := ERR;
  Y_k_2 := Y_k_1;
  Y_k_1 := Y2;



  (* Now the Algorithm Performs an Iteration*)
  (* Y := C1*X1 + C2*X2 + Dd*ERR; *)
  (* Xtemp := X1; *)
  (* X1 := A11*X1 + A12*X2 + B1*ERR; *)
  (* X2 := A21*Xtemp + A22*X2 + B2*ERR; *)

  Y := Y * Ga;
  Y := Y * 10000.0;
  Y := Y + 10000.0;

  Y2 := Y2 * Ga;
  Y2 := Y2 * 10000.0;
  Y2 := Y2 + 10000.0; 

  act_com := REAL_TO_INT(Y);
  act_com0 := REAL_TO_INT(Y2);

  (* act_com := omega; *)
END_FUNCTION_BLOCK

PROGRAM My_Program
  VAR
    act_com AT %QW0 : INT;
    act_com0 AT %QW1 : INT;
    Gain AT %QW2 : INT := 40;
    vrms0 AT %QW3 : INT := 0;
    vrms AT %IW0 : INT;
    Irms AT %IW1 : INT;
    Frequency AT %IW2 : INT;
    RPM AT %IW3 : INT;
    Fuel AT %IW4 : INT;
    Oil AT %IW5 : INT;
    Temp AT %IW6 : INT;
    omega AT %IW7 : INT := 0;
    switch AT %QX0.0 : BOOL := 0;
    onoff AT %QX0.1 : BOOL := 0;
    Override AT %QX0.2 : BOOL := 0;
    Fault AT %QX0.3 : BOOL := 0;
  END_VAR
  VAR
    ControllerFunc0 : ControllerFunc;
    MOVE40_OUT : INT;
    LT43_OUT : BOOL;
    LT1_OUT : BOOL;
    GT11_OUT : BOOL;
    GT22_OUT : BOOL;
  END_VAR

  ControllerFunc0(omega := omega, gain := Gain);
  act_com := ControllerFunc0.act_com;
  act_com0 := ControllerFunc0.act_com0;
  MOVE40_OUT := MOVE(vrms);
  vrms0 := MOVE40_OUT;
  LT43_OUT := LT(Oil, 25);
  IF LT43_OUT THEN
    Fault := TRUE; (*set*)
  END_IF;
  LT1_OUT := LT(Temp, 0);
  GT11_OUT := GT(Temp, 300);
  IF GT11_OUT OR LT1_OUT THEN
    Fault := TRUE; (*set*)
  END_IF;
  GT22_OUT := GT(RPM, 20000);
  IF GT22_OUT THEN
    Fault := TRUE; (*set*)
  END_IF;
  IF NOT(Override) AND Fault THEN
    onoff := TRUE; (*set*)
  END_IF;
END_PROGRAM

FUNCTION_BLOCK Controller
  VAR_INPUT
    omega : INT;
    gain : INT;
  END_VAR
  VAR_OUTPUT
    act_com : INT;
  END_VAR
  VAR
    U : REAL := 0.0;
    Ga : REAL := 0.0;
    REF : REAL := 1.0;
    ERR : REAL := 0.0;
    Y : REAL := 0.0;
    X1 : REAL := 0.0;
    X2 : REAL := 0.0;
    Xtemp : REAL := 0.0;
    A11 : REAL := 0.4337;
    A12 : REAL := -36.16;
    A21 : REAL := 0.007232;
    A22 : REAL := 0.7954;
    C1 : REAL := 1000.0;
    C2 : REAL := 5000.0;
    Dd : REAL := 0.0;
    B1 : REAL := 0.007232;
    B2 : REAL := 0.00004093;
  END_VAR

  (* Convert the input appropriately to Input *)
  U := INT_TO_REAL(omega); 
  Ga := INT_TO_REAL(Gain);
  U := U - 10000.0; 
  U := U / 10000.0;

  ERR := REF - U;


  (* Now the Algorithm Performs an Iteration*)
  Y := C1*X1 + C2*X2 + Dd*ERR;
  Xtemp := X1;
  X1 := A11*X1 + A12*X2 + B1*ERR;
  X2 := A21*Xtemp + A22*X2 + B2*ERR;
  Y := Y * Ga;

  Y := Y * 10000.0;
  Y := Y + 10000.0; 
  act_com := REAL_TO_INT(Y);

  (* act_com := omega; *)
END_FUNCTION_BLOCK


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#200ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION