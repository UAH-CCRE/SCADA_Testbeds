PROGRAM My_Program
  VAR
    flow_in AT %IW0 : INT;
    flow_out AT %IW1 : INT;
    ug_opcmd AT %QX0.0 : BOOL;
    ug_clcmd AT %QX0.1 : BOOL;
    ug_val AT %IW2 : INT;
    lg_opcmd AT %QX0.2 : BOOL;
    lg_clcmd AT %QX0.3 : BOOL;
    lg_val AT %IW3 : INT;
    uv_opcmd AT %QX0.4 : BOOL;
    uv_clcmd AT %QX0.5 : BOOL;
    uv_val AT %IW4 : INT;
    lv_opcmd AT %QX0.6 : BOOL;
    lv_clcmd AT %QX0.7 : BOOL;
    lv_val AT %IW5 : INT;
    dp_chmbr AT %IW6 : INT;
    dp_rsvr AT %IW7 : INT := 4200;
    dp_tlwtr AT %IW8 : INT;
    warn_btn AT %QX1.0 : BOOL;
    em_gt AT %QX1.1 : BOOL;
    em_vlv AT %QX1.2 : BOOL;
    ht_still AT %IW9 : INT := 21500;
    dprel_rsvr AT %QW0 : INT;
    rsrvr_eq AT %QX1.3 : BOOL;
    tlwtr_eq AT %QX1.4 : BOOL;
  END_VAR
  VAR
    TP0 : TP;
    TP1 : TP;
    TP2 : TP;
    XOR35_OUT : BOOL;
    AND60_OUT : BOOL;
    AND62_OUT : BOOL;
    INT_TO_REAL143_OUT : REAL;
    DIV140_OUT : REAL;
    LT12_OUT : BOOL;
    GT19_OUT : BOOL;
    XOR28_OUT : BOOL;
    AND36_OUT : BOOL;
    AND42_OUT : BOOL;
    INT_TO_REAL22_OUT : REAL;
    DIV17_OUT : REAL;
    LT15_OUT : BOOL;
    GT46_OUT : BOOL;
    XOR57_OUT : BOOL;
    AND67_OUT : BOOL;
    AND69_OUT : BOOL;
    OR106_OUT : BOOL;
    INT_TO_REAL145_OUT : REAL;
    DIV144_OUT : REAL;
    LT49_OUT : BOOL;
    GT71_OUT : BOOL;
    XOR83_OUT : BOOL;
    AND89_OUT : BOOL;
    AND91_OUT : BOOL;
    OR117_OUT : BOOL;
    INT_TO_REAL147_OUT : REAL;
    DIV79_OUT : REAL;
    LT76_OUT : BOOL;
    GT93_OUT : BOOL;
    ADD153_OUT : INT;
    EQ155_OUT : BOOL;
    EQ149_OUT : BOOL;
  END_VAR

  TP0(IN := warn_btn, PT := T#3000ms);
  warn_btn := TP0.Q;
  XOR35_OUT := XOR(NOT(em_gt) AND ug_opcmd, NOT(em_gt) AND ug_clcmd);
  AND60_OUT := AND(NOT(em_gt) AND ug_opcmd, XOR35_OUT);
  ug_opcmd := AND60_OUT;
  AND62_OUT := AND(XOR35_OUT, NOT(em_gt) AND ug_clcmd);
  ug_clcmd := AND62_OUT;
  INT_TO_REAL143_OUT := INT_TO_REAL(ug_val);
  DIV140_OUT := DIV(INT_TO_REAL143_OUT, 100.0);
  LT12_OUT := LT(DIV140_OUT, 90.0);
  ug_opcmd := ug_opcmd AND LT12_OUT;
  GT19_OUT := GT(DIV140_OUT, 7.0);
  ug_clcmd := ug_clcmd AND GT19_OUT;
  XOR28_OUT := XOR(NOT(em_gt) AND lg_opcmd, NOT(em_gt) AND lg_clcmd);
  AND36_OUT := AND(NOT(em_gt) AND lg_opcmd, XOR28_OUT);
  lg_opcmd := AND36_OUT;
  AND42_OUT := AND(XOR28_OUT, NOT(em_gt) AND lg_clcmd);
  lg_clcmd := AND42_OUT;
  INT_TO_REAL22_OUT := INT_TO_REAL(lg_val);
  DIV17_OUT := DIV(INT_TO_REAL22_OUT, 100.0);
  LT15_OUT := LT(DIV17_OUT, 90.0);
  lg_opcmd := lg_opcmd AND LT15_OUT;
  GT46_OUT := GT(DIV17_OUT, 7.0);
  lg_clcmd := lg_clcmd AND GT46_OUT;
  XOR57_OUT := XOR(NOT(em_vlv) AND uv_opcmd, NOT(em_vlv) AND uv_clcmd);
  AND67_OUT := AND(NOT(em_vlv) AND uv_opcmd, XOR57_OUT);
  uv_opcmd := AND67_OUT;
  AND69_OUT := AND(XOR57_OUT, NOT(em_vlv) AND uv_clcmd);
  OR106_OUT := OR(AND69_OUT, em_vlv);
  uv_clcmd := OR106_OUT;
  INT_TO_REAL145_OUT := INT_TO_REAL(uv_val);
  DIV144_OUT := DIV(INT_TO_REAL145_OUT, 100.0);
  LT49_OUT := LT(DIV144_OUT, 100.0);
  uv_opcmd := uv_opcmd AND LT49_OUT;
  GT71_OUT := GT(DIV144_OUT, 0.0);
  uv_clcmd := uv_clcmd AND GT71_OUT;
  XOR83_OUT := XOR(NOT(em_vlv) AND lv_opcmd, NOT(em_vlv) AND lv_clcmd);
  AND89_OUT := AND(NOT(em_vlv) AND lv_opcmd, XOR83_OUT);
  lv_opcmd := AND89_OUT;
  AND91_OUT := AND(XOR83_OUT, NOT(em_vlv) AND lv_clcmd);
  OR117_OUT := OR(AND91_OUT, em_vlv);
  lv_clcmd := OR117_OUT;
  INT_TO_REAL147_OUT := INT_TO_REAL(lv_val);
  DIV79_OUT := DIV(INT_TO_REAL147_OUT, 100.0);
  LT76_OUT := LT(DIV79_OUT, 100.0);
  lv_opcmd := lv_opcmd AND LT76_OUT;
  GT93_OUT := GT(DIV79_OUT, 0.0);
  lv_clcmd := lv_clcmd AND GT93_OUT;
  TP1(IN := em_gt, PT := T#3000ms);
  em_gt := TP1.Q;
  TP2(IN := em_vlv, PT := T#3000ms);
  em_vlv := TP2.Q;
  ADD153_OUT := ADD(dp_rsvr, ht_still);
  dprel_rsvr := ADD153_OUT;
  EQ155_OUT := EQ(dprel_rsvr, dp_chmbr);
  rsrvr_eq := EQ155_OUT;
  EQ149_OUT := EQ(dp_chmbr, dp_tlwtr);
  tlwtr_eq := EQ149_OUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK TaskMain(INTERVAL := T#50ms,PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : My_Program;
  END_RESOURCE
END_CONFIGURATION
