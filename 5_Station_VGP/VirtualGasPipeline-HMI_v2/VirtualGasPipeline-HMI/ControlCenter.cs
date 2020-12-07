using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using EasyModbus;

namespace VirtualGasPipeline_HMI
{
    public partial class ControlCenter : Form
    {
        public ModbusClient[] modbusClients;

        public ControlCenter()
        {
            InitializeComponent();
        }

        public void startTimer()
        {
            timer1.Start();
        }

        public void stopTimer()
        {
            timer1.Stop();
        }

        public void initializeSetpoints()
        {
            for (int i = 0; i < modbusClients.Length; i++)
            {
                if (modbusClients[i] != null)
                {
                    int[] setpoints = modbusClients[i].ReadHoldingRegisters(1, 2);
                    double min_sp = ((float)setpoints[0] - 100) / 100.0;
                    double max_sp = ((float)setpoints[1] - 100) / 100.0;

                    switch (i)
                    {
                        case 0:
                            s1_min_sp.Text = min_sp.ToString();
                            s1_max_sp.Text = max_sp.ToString();
                            break;
                        case 1:
                            s2_min_sp.Text = min_sp.ToString();
                            s2_max_sp.Text = max_sp.ToString();
                            break;
                        case 2:
                            s3_min_sp.Text = min_sp.ToString();
                            s3_max_sp.Text = max_sp.ToString();
                            break;
                        case 3:
                            s4_min_sp.Text = min_sp.ToString();
                            s4_max_sp.Text = max_sp.ToString();
                            break;
                        case 4:
                            s5_min_sp.Text = min_sp.ToString();
                            s5_max_sp.Text = max_sp.ToString();
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void updateModbus()
        {
            for (int i = 0; i < modbusClients.Length; i++)
            {
                if (modbusClients[i] != null)
                {
                    try
                    {
                        int[] registers = modbusClients[i].ReadHoldingRegisters(0, 4);
                        int[] inputs = modbusClients[i].ReadInputRegisters(0, 1);
                        bool[] coilStatus = modbusClients[i].ReadCoils(0, 2);

                        double pressure = ((float)inputs[0] - 100) / 100.0;
                        double min_sp = ((float)registers[1] - 100) / 100.0;
                        double max_sp = ((float)registers[2] - 100) / 100.0;
                        int mode = registers[3];
                        bool pump = coilStatus[0];
                        bool valve = coilStatus[1];

                        switch (i)
                        {
                            case 0:
                                s1_pressure.Text = pressure.ToString();
                                s1_pump_state.Text = (pump == true) ? "on" : "off";
                                s1_valve_state.Text = (valve == true) ? "on" : "off";
                                switch (mode)
                                {
                                    case 0:
                                        s1_manual_btn.BackColor = Color.LimeGreen;
                                        s1_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s1_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s1_manual_pump_btn.BackColor = (pump == true) ? Color.LimeGreen : Color.Gainsboro;
                                        s1_manual_valve_btn.BackColor = (valve == true) ? Color.LimeGreen : Color.Gainsboro;
                                        break;
                                    case 1:
                                        s1_manual_btn.BackColor = Color.Gainsboro;
                                        s1_pump_mode_btn.BackColor = Color.LimeGreen;
                                        s1_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s1_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s1_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    case 2:
                                        s1_manual_btn.BackColor = Color.Gainsboro;
                                        s1_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s1_valve_mode_btn.BackColor = Color.LimeGreen;
                                        s1_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s1_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 1:
                                s2_pressure.Text = pressure.ToString();
                                s2_pump_state.Text = (pump == true) ? "on" : "off";
                                s2_valve_state.Text = (valve == true) ? "on" : "off";
                                switch (mode)
                                {
                                    case 0:
                                        s2_manual_btn.BackColor = Color.LimeGreen;
                                        s2_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s2_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s2_manual_pump_btn.BackColor = (pump == true) ? Color.LimeGreen : Color.Gainsboro;
                                        s2_manual_valve_btn.BackColor = (valve == true) ? Color.LimeGreen : Color.Gainsboro;
                                        break;
                                    case 1:
                                        s2_manual_btn.BackColor = Color.Gainsboro;
                                        s2_pump_mode_btn.BackColor = Color.LimeGreen;
                                        s2_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s2_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s2_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    case 2:
                                        s2_manual_btn.BackColor = Color.Gainsboro;
                                        s2_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s2_valve_mode_btn.BackColor = Color.LimeGreen;
                                        s2_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s2_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 2:
                                s3_pressure.Text = pressure.ToString();
                                s3_pump_state.Text = (pump == true) ? "on" : "off";
                                s3_valve_state.Text = (valve == true) ? "on" : "off";
                                switch (mode)
                                {
                                    case 0:
                                        s3_manual_btn.BackColor = Color.LimeGreen;
                                        s3_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s3_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s3_manual_pump_btn.BackColor = (pump == true) ? Color.LimeGreen : Color.Gainsboro;
                                        s3_manual_valve_btn.BackColor = (valve == true) ? Color.LimeGreen : Color.Gainsboro;
                                        break;
                                    case 1:
                                        s3_manual_btn.BackColor = Color.Gainsboro;
                                        s3_pump_mode_btn.BackColor = Color.LimeGreen;
                                        s3_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s3_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s3_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    case 2:
                                        s3_manual_btn.BackColor = Color.Gainsboro;
                                        s3_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s3_valve_mode_btn.BackColor = Color.LimeGreen;
                                        s3_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s3_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 3:
                                s4_pressure.Text = pressure.ToString();
                                s4_pump_state.Text = (pump == true) ? "on" : "off";
                                s4_valve_state.Text = (valve == true) ? "on" : "off";
                                switch (mode)
                                {
                                    case 0:
                                        s4_manual_btn.BackColor = Color.LimeGreen;
                                        s4_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s4_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s4_manual_pump_btn.BackColor = (pump == true) ? Color.LimeGreen : Color.Gainsboro;
                                        s4_manual_valve_btn.BackColor = (valve == true) ? Color.LimeGreen : Color.Gainsboro;
                                        break;
                                    case 1:
                                        s4_manual_btn.BackColor = Color.Gainsboro;
                                        s4_pump_mode_btn.BackColor = Color.LimeGreen;
                                        s4_valve_mode_btn.BackColor = Color.Gainsboro;
                                        s4_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s4_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    case 2:
                                        s4_manual_btn.BackColor = Color.Gainsboro;
                                        s4_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s4_valve_mode_btn.BackColor = Color.LimeGreen;
                                        s4_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s4_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 4:
                                s5_pressure.Text = pressure.ToString();
                                s5_pump_state.Text = (pump == true) ? "on" : "off";
                                s5_valve_state.Text = (valve == true) ? "on" : "off";
                                switch (mode)
                                {
                                    case 0:
                                        s5_manual_btn.BackColor = Color.LimeGreen;
                                        s5_pump_mode_btn.BackColor = Color.Gainsboro;
                                        s5_manual_pump_btn.BackColor = (pump == true) ? Color.LimeGreen : Color.Gainsboro;
                                        s5_manual_valve_btn.BackColor = (valve == true) ? Color.LimeGreen : Color.Gainsboro;
                                        break;
                                    case 1:
                                        s5_manual_btn.BackColor = Color.Gainsboro;
                                        s5_pump_mode_btn.BackColor = Color.LimeGreen;
                                        s5_manual_pump_btn.BackColor = Color.Gainsboro;
                                        s5_manual_valve_btn.BackColor = Color.Gainsboro;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    catch
                    {
                        modbusClients[i] = null;
                    }
                }

                else
                {
                    switch (i)
                    {
                        case 0:
                            s1_pressure.Text = " - ";
                            s1_pump_state.Text = " - ";
                            s1_valve_state.Text = " - ";
                            s1_manual_btn.Enabled = false;
                            s1_pump_mode_btn.Enabled = false;
                            s1_valve_mode_btn.Enabled = false;
                            s1_manual_pump_btn.Enabled = false;
                            s1_manual_valve_btn.Enabled = false;
                            s1_set_min_sp_btn.Enabled = false;
                            s1_set_max_sp_btn.Enabled = false;
                            break;
                        case 1:
                            s2_pressure.Text = " - ";
                            s2_pump_state.Text = " - ";
                            s2_valve_state.Text = " - ";
                            s2_manual_btn.Enabled = false;
                            s2_pump_mode_btn.Enabled = false;
                            s2_valve_mode_btn.Enabled = false;
                            s2_manual_pump_btn.Enabled = false;
                            s2_manual_valve_btn.Enabled = false;
                            s2_set_min_sp_btn.Enabled = false;
                            s2_set_max_sp_btn.Enabled = false;
                            break;
                        case 2:
                            s3_pressure.Text = " - ";
                            s3_pump_state.Text = " - ";
                            s3_valve_state.Text = " - ";
                            s3_manual_btn.Enabled = false;
                            s3_pump_mode_btn.Enabled = false;
                            s3_valve_mode_btn.Enabled = false;
                            s3_manual_pump_btn.Enabled = false;
                            s3_manual_valve_btn.Enabled = false;
                            s3_set_min_sp_btn.Enabled = false;
                            s3_set_max_sp_btn.Enabled = false;
                            break;
                        case 3:
                            s4_pressure.Text = " - ";
                            s4_pump_state.Text = " - ";
                            s4_valve_state.Text = " - ";
                            s4_manual_btn.Enabled = false;
                            s4_pump_mode_btn.Enabled = false;
                            s4_valve_mode_btn.Enabled = false;
                            s4_manual_pump_btn.Enabled = false;
                            s4_manual_valve_btn.Enabled = false;
                            s4_set_min_sp_btn.Enabled = false;
                            s4_set_max_sp_btn.Enabled = false;
                            break;
                        case 4:
                            s5_pressure.Text = " - ";
                            s5_pump_state.Text = " - ";
                            s5_valve_state.Text = " - ";
                            s5_manual_btn.Enabled = false;
                            s5_pump_mode_btn.Enabled = false;
                            s5_manual_pump_btn.Enabled = false;
                            s5_manual_valve_btn.Enabled = false;
                            s5_set_min_sp_btn.Enabled = false;
                            s5_set_max_sp_btn.Enabled = false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void changeSetpoint(int station, double value, int minMax)
        {
            if (modbusClients[station - 1] != null)
            {
                int intValue = Convert.ToInt16((value * 100) + 100);
                if (minMax == 0) //set min_sp
                {
                    modbusClients[station - 1].WriteSingleRegister(1, intValue);
                    stations_data.stationVariables[station - 1].min_sp = intValue;
                }
                else if (minMax == 1) //set max_sp
                {
                    modbusClients[station - 1].WriteSingleRegister(2, intValue);
                    stations_data.stationVariables[station - 1].max_sp = intValue;
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            updateModbus();
        }

        //Change setpoints
        private void s1_set_min_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(1, Convert.ToDouble(s1_min_sp.Text), 0);
        }
        private void s2_set_min_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(2, Convert.ToDouble(s2_min_sp.Text), 0);
        }
        private void s3_set_min_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(3, Convert.ToDouble(s3_min_sp.Text), 0);
        }
        private void s4_set_min_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(4, Convert.ToDouble(s4_min_sp.Text), 0);
        }
        private void s5_set_min_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(5, Convert.ToDouble(s5_min_sp.Text), 0);
        }
        private void s1_set_max_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(1, Convert.ToDouble(s1_max_sp.Text), 1);
        }
        private void s2_set_max_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(2, Convert.ToDouble(s2_max_sp.Text), 1);
        }
        private void s3_set_max_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(3, Convert.ToDouble(s3_max_sp.Text), 1);
        }
        private void s4_set_max_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(4, Convert.ToDouble(s4_max_sp.Text), 1);
        }
        private void s5_set_max_sp_btn_Click(object sender, EventArgs e)
        {
            changeSetpoint(5, Convert.ToDouble(s5_max_sp.Text), 1);
        }

        //Change auto mode (pump or valve mode)
        private void s1_pump_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[0].WriteSingleRegister(3, 1);
            stations_data.stationVariables[0].mode = 1;
        }
        private void s1_valve_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[0].WriteSingleRegister(3, 2);
            stations_data.stationVariables[0].mode = 2;
        }
        private void s2_pump_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[1].WriteSingleRegister(3, 1);
            stations_data.stationVariables[1].mode = 1;
        }
        private void s2_valve_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[1].WriteSingleRegister(3, 2);
            stations_data.stationVariables[1].mode = 2;
        }
        private void s3_pump_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[2].WriteSingleRegister(3, 1);
            stations_data.stationVariables[2].mode = 1;
        }
        private void s3_valve_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[2].WriteSingleRegister(3, 2);
            stations_data.stationVariables[2].mode = 2;
        }
        private void s4_pump_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[3].WriteSingleRegister(3, 1);
            stations_data.stationVariables[3].mode = 1;
        }
        private void s4_valve_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[3].WriteSingleRegister(3, 2);
            stations_data.stationVariables[3].mode = 2;
        }
        private void s5_pump_mode_btn_Click(object sender, EventArgs e)
        {
            modbusClients[4].WriteSingleRegister(3, 1);
            stations_data.stationVariables[4].mode = 1;
        }

        //set manual mode
        private void s1_manual_btn_Click(object sender, EventArgs e)
        {
            modbusClients[0].WriteSingleRegister(3, 0);
            stations_data.stationVariables[0].mode = 0;
        }
        private void s1_manual_pump_btn_Click(object sender, EventArgs e)
        {
            int state = (s1_pump_state.Text == "on") ? 0 : 1;
            modbusClients[0].WriteSingleRegister(4, state);
            stations_data.stationVariables[0].man_pump_state = state;
        }
        private void s1_manual_valve_btn_Click(object sender, EventArgs e)
        {
            int state = (s1_valve_state.Text == "on") ? 0 : 1;
            modbusClients[0].WriteSingleRegister(5, state);
            stations_data.stationVariables[0].man_valve_state = state;
        }
        private void s2_manual_btn_Click(object sender, EventArgs e)
        {
            modbusClients[1].WriteSingleRegister(3, 0);
            stations_data.stationVariables[1].mode = 0;
        }
        private void s2_manual_pump_btn_Click(object sender, EventArgs e)
        {
            int state = (s2_pump_state.Text == "on") ? 0 : 1;
            modbusClients[1].WriteSingleRegister(4, state);
            stations_data.stationVariables[1].man_pump_state = state;
        }
        private void s2_manual_valve_btn_Click(object sender, EventArgs e)
        {
            int state = (s2_valve_state.Text == "on") ? 0 : 1;
            modbusClients[1].WriteSingleRegister(5, state);
            stations_data.stationVariables[1].man_valve_state = state;
        }
        private void s3_manual_btn_Click(object sender, EventArgs e)
        {
            modbusClients[2].WriteSingleRegister(3, 0);
            stations_data.stationVariables[2].mode = 0;
        }
        private void s3_manual_pump_btn_Click(object sender, EventArgs e)
        {
            int state = (s3_pump_state.Text == "on") ? 0 : 1;
            modbusClients[2].WriteSingleRegister(4, state);
            stations_data.stationVariables[2].man_pump_state = state;
        }
        private void s3_manual_valve_btn_Click(object sender, EventArgs e)
        {
            int state = (s3_valve_state.Text == "on") ? 0 : 1;
            modbusClients[2].WriteSingleRegister(5, state);
            stations_data.stationVariables[2].man_valve_state = state;
        }
        private void s4_manual_btn_Click(object sender, EventArgs e)
        {
            modbusClients[3].WriteSingleRegister(3, 0);
            stations_data.stationVariables[3].mode = 0;
        }
        private void s4_manual_pump_btn_Click(object sender, EventArgs e)
        {
            int state = (s4_pump_state.Text == "on") ? 0 : 1;
            modbusClients[3].WriteSingleRegister(4, state);
            stations_data.stationVariables[3].man_pump_state = state;
        }
        private void s4_manual_valve_btn_Click(object sender, EventArgs e)
        {
            int state = (s4_valve_state.Text == "on") ? 0 : 1;
            modbusClients[3].WriteSingleRegister(5, state);
            stations_data.stationVariables[3].man_valve_state = state;
        }
        private void s5_manual_btn_Click(object sender, EventArgs e)
        {
            modbusClients[4].WriteSingleRegister(3, 0);
            stations_data.stationVariables[4].mode = 0;
        }
        private void s5_manual_pump_btn_Click(object sender, EventArgs e)
        {
            int state = (s5_pump_state.Text == "on") ? 0 : 1;
            modbusClients[4].WriteSingleRegister(4, state);
            stations_data.stationVariables[4].man_pump_state = state;
        }
        private void s5_manual_valve_btn_Click(object sender, EventArgs e)
        {
            int state = (s5_valve_state.Text == "on") ? 0 : 1;
            modbusClients[4].WriteSingleRegister(5, state);
            stations_data.stationVariables[4].man_valve_state = state;
        }
    }
}
