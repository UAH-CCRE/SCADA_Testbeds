using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using EasyModbus;

namespace VirtualGasPipeline_HMI
{
    public partial class MainView : Form
    {
        public ModbusClient[] modbusClients;
        public string[] stationIP = new string[5];

        public const int MANUAL_MODE = 0;
        const int CARGO_TRANSFER_MODE = 1;
        const int RECIRCULATION_MODE = 2;
        const int HIGH_PRESSURE = 300;

        bool warningMsgOn = false;
        int timerTicks = 0;
        
        public MainView()
        {
            InitializeComponent();
        }

        public void startVariables()
        {
            for (int i = 0; i < modbusClients.Length; i++)
            {
                if (modbusClients[i] != null)
                {
                    try
                    {
                        int[] registers = modbusClients[i].ReadHoldingRegisters(1, 6);
                        stations_data.stationVariables[i].min_sp = registers[0];
                        stations_data.stationVariables[i].max_sp = registers[1];
                        stations_data.stationVariables[i].mode = registers[2];
                        stations_data.stationVariables[i].man_pump_state = registers[3];
                        stations_data.stationVariables[i].man_valve_state = registers[4];
                        stations_data.stationVariables[i].man_isolation_valve_state = registers[5];
                    }
                    catch
                    {
                        //error reading from station
                    }
                }
            }

            if (stations_data.stationVariables[0].mode == MANUAL_MODE)
            {
                manual_mode_btn.BackColor = Color.LimeGreen;
                cargo_transfer_mode_btn.BackColor = Color.Gainsboro;
                recirculation_mode_btn.BackColor = Color.Gainsboro;
            }
            else if (stations_data.stationVariables[0].mode == CARGO_TRANSFER_MODE)
            {
                manual_mode_btn.BackColor = Color.Gainsboro;
                cargo_transfer_mode_btn.BackColor = Color.LimeGreen;
                recirculation_mode_btn.BackColor = Color.Gainsboro;
            }
            else if (stations_data.stationVariables[0].mode == RECIRCULATION_MODE)
            {
                manual_mode_btn.BackColor = Color.Gainsboro;
                cargo_transfer_mode_btn.BackColor = Color.Gainsboro;
                recirculation_mode_btn.BackColor = Color.LimeGreen;
            }
        }

        public void startTimer()
        {
            timer1.Start();
            timer2.Start();
        }
        public void stopTimer()
        {
            timer1.Stop();
            timer2.Stop();
        }

        private delegate void displayErrorCallback();
        private void displayError()
        {
            if (this.s1_pump.InvokeRequired) //this is not the UI thread
            {
                displayErrorCallback d = new displayErrorCallback(displayError);
                Invoke(d, new object[] { });
            }

            else
            {
                MessageBox.Show("Unable to connect to station. Please verify the IP address and check if the station is turned on.", "Connection Error");
            }
        }

        private void reconnectStation(int station_number)
        {
            modbusClients[station_number] = new ModbusClient(stationIP[station_number], 502);
            try
            {
                modbusClients[station_number].Connect();
                int[] registers = modbusClients[station_number].ReadHoldingRegisters(1, 5);
                stations_data.stationVariables[station_number].min_sp = registers[0];
                stations_data.stationVariables[station_number].max_sp = registers[1];
                stations_data.stationVariables[station_number].mode = registers[2];
                stations_data.stationVariables[station_number].man_pump_state = registers[3];
                stations_data.stationVariables[station_number].man_valve_state = registers[4];
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                modbusClients[station_number] = null; //remove the actual modbus client from the list
                displayError();
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
                        //Reading data
                        int[] registers = modbusClients[i].ReadHoldingRegisters(0, 3);
                        int[] inputs = modbusClients[i].ReadInputRegisters(0, 5);
                        bool[] coilStatus = modbusClients[i].ReadCoils(0, 5);

                        //Setting data
                        int[] setting_registers = new int[8];
                        setting_registers[0] = stations_data.stationVariables[i].min_sp;
                        setting_registers[1] = stations_data.stationVariables[i].max_sp;
                        setting_registers[2] = stations_data.stationVariables[i].mode;
                        setting_registers[3] = stations_data.stationVariables[i].man_pump_state;
                        setting_registers[4] = stations_data.stationVariables[i].man_valve_state;
                        setting_registers[5] = (i != 4) ? (stations_data.stationVariables[i].man_isolation_valve_state) : (stations_data.stationVariables[i].man_inlet_valve_state);
                        setting_registers[6] = stations_data.stationVariables[i].man_return_valve_state;
                        setting_registers[7] = stations_data.stationVariables[i].man_isolation_valve_state;
                        modbusClients[i].WriteMultipleRegisters(1, setting_registers);

                        //High Pressure scenario
                        if (warningMsgOn)
                        {
                            modbusClients[2].WriteSingleRegister(51, 0x84);
                        }
                        else
                        {
                            modbusClients[2].WriteSingleRegister(51, 0x00);
                        }

                        double pressure, tank_lvl, flow_rate, return_flow_rate, tank_flow_rate, recirculation_flow_rate, min_sp, max_sp;
                        bool pump, valve, isolation_valve, return_valve, tank_valve;

                        pressure = ((float)inputs[0] - 100) / 100.0;
                        return_flow_rate = inputs[3];
                        min_sp = ((float)registers[1] - 100) / 100.0;
                        max_sp = ((float)registers[2] - 100) / 100.0;
                        pump = coilStatus[0];
                        valve = coilStatus[1];
                        isolation_valve = coilStatus[2];
                        return_valve = coilStatus[3];

                        tank_lvl = 0;
                        flow_rate = 0;
                        tank_flow_rate = 0;
                        recirculation_flow_rate = 0;
                        tank_valve = false;

                        if (i == 0) //station 1
                        {
                            tank_lvl = inputs[1] / 10.0;
                            flow_rate = inputs[2];
                            stations_data.return_flow_rate = Convert.ToInt32(return_flow_rate);
                        }
                        else if (i == 4) //station 5
                        {
                            valve = coilStatus[4];
                            isolation_valve = coilStatus[2];
                            tank_valve = coilStatus[1];
                            return_valve = coilStatus[3];

                            tank_lvl = inputs[1] / 10.0;
                            flow_rate = inputs[4];
                            tank_flow_rate = inputs[3];
                            recirculation_flow_rate = inputs[2];

                            stations_data.tank_flow_rate = Convert.ToInt32(tank_flow_rate);
                        }
                        else
                        {
                            flow_rate = inputs[1];
                        }

                        //sending the flow rate to all stations
                        int[] flow_rates = new int[2];
                        flow_rates[0] = stations_data.return_flow_rate;
                        flow_rates[1] = stations_data.tank_flow_rate;
                        modbusClients[i].WriteMultipleRegisters(20, flow_rates);

                        switch (i)
                        {
                            case 0:
                                s1_pump.Image = (pump == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                                s1_valve.Image = (valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s1_tank_body_valve.Image = (isolation_valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s1_return_body_valve.Image = (return_valve == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");
                                s1_pressure.Text = pressure.ToString() + " bar";
                                s1_min_sp.Text = min_sp.ToString() + " bar";
                                s1_max_sp.Text = max_sp.ToString() + " bar";
                                s1_tank_lvl.Text = tank_lvl.ToString() + " KL";
                                s1_flow.Text = flow_rate.ToString() + " KL/h";
                                s1_return_flow.Text = "Rate: " + return_flow_rate.ToString() + " KL/h";
                                s1_reconnect.Visible = false;

                                if (pressure > HIGH_PRESSURE) //high pressure situation
                                {
                                    warningMsgOn = true;
                                }
                                else
                                {
                                    warningMsgOn = false;
                                }
                                break;
                            case 1:
                                s2_pump.Image = (pump == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                                s2_valve.Image = (valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s2_isolation_valve.Image = (isolation_valve == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");
                                s2_pressure.Text = pressure.ToString() + " bar";
                                s2_min_sp.Text = min_sp.ToString() + " bar";
                                s2_max_sp.Text = max_sp.ToString() + " bar";
                                s2_flow.Text = flow_rate.ToString() + " KL/h";
                                s2_reconnect.Visible = false;
                                break;
                            case 2:
                                s3_pump.Image = (pump == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                                s3_valve.Image = (valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s3_isolation_valve.Image = (isolation_valve == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");
                                s3_pressure.Text = pressure.ToString() + " bar";
                                s3_min_sp.Text = min_sp.ToString() + " bar";
                                s3_max_sp.Text = max_sp.ToString() + " bar";
                                s3_flow.Text = flow_rate.ToString() + " KL/h";
                                s3_reconnect.Visible = false;
                                break;
                            case 3:
                                s4_pump.Image = (pump == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                                s4_valve.Image = (valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s4_isolation_valve.Image = (isolation_valve == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");
                                s4_pressure.Text = pressure.ToString() + " bar";
                                s4_min_sp.Text = min_sp.ToString() + " bar";
                                s4_max_sp.Text = max_sp.ToString() + " bar";
                                s4_flow.Text = flow_rate.ToString() + " KL/h";
                                s4_reconnect.Visible = false;
                                break;
                            case 4:
                                s5_pump.Image = (pump == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                                s5_recirculation_valve.Image = (valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s5_isolation_valve.Image = (isolation_valve == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");
                                s5_tank_valve.Image = (tank_valve == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                                s5_return_valve.Image = (return_valve == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");
                                s5_pressure.Text = pressure.ToString() + " bar";
                                s5_min_sp.Text = min_sp.ToString() + " bar";
                                s5_max_sp.Text = max_sp.ToString() + " bar";
                                s5_tank_lvl.Text = tank_lvl.ToString() + " KL";
                                s5_flow.Text = flow_rate.ToString() + " KL/h";
                                s5_recirculation_flow.Text = "Rate: " + recirculation_flow_rate.ToString() + " KL/h";
                                s5_tank_flow.Text = "Rate: " + tank_flow_rate.ToString() + " KL/h";
                                s5_reconnect.Visible = false;
                                break;
                            default:
                                break;
                        }
                    }
                    catch (Exception e)
                    {
                        modbusClients[i] = null;
                    }
                }

                else
                {
                    switch (i)
                    {
                        case 0:
                            s1_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                            s1_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s1_tank_body_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s1_return_body_valve.Image = Image.FromFile("./sprites/valve_offline.png");
                            s1_pressure.Text = " - ";
                            s1_flow.Text = " - ";
                            s1_min_sp.Text = " - ";
                            s1_max_sp.Text = " - ";
                            s1_return_flow.Text = " - ";
                            s1_tank_lvl.Text = " - ";
                            s1_reconnect.Visible = true;
                            break;
                        case 1:
                            s2_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                            s2_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s2_isolation_valve.Image = Image.FromFile("./sprites/valve_offline.png");
                            s2_pressure.Text = " - ";
                            s1_flow.Text = " - ";
                            s2_min_sp.Text = " - ";
                            s2_max_sp.Text = " - ";
                            s2_reconnect.Visible = true;
                            break;
                        case 2:
                            s3_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                            s3_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s3_isolation_valve.Image = Image.FromFile("./sprites/valve_offline.png");
                            s3_pressure.Text = " - ";
                            s3_flow.Text = " - ";
                            s3_min_sp.Text = " - ";
                            s3_max_sp.Text = " - ";
                            s3_reconnect.Visible = true;
                            break;
                        case 3:
                            s4_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                            s4_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s4_isolation_valve.Image = Image.FromFile("./sprites/valve_offline.png");
                            s4_pressure.Text = " - ";
                            s4_flow.Text = " - ";
                            s4_min_sp.Text = " - ";
                            s4_max_sp.Text = " - ";
                            s4_reconnect.Visible = true;
                            break;
                        case 4:
                            s5_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                            s5_recirculation_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s5_isolation_valve.Image = Image.FromFile("./sprites/valve_offline.png");
                            s5_tank_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                            s5_return_valve.Image = Image.FromFile("./sprites/valve_offline.png");
                            s5_pressure.Text = " - ";
                            s5_flow.Text = " - ";
                            s5_min_sp.Text = " - ";
                            s5_max_sp.Text = " - ";
                            s5_tank_flow.Text = " - ";
                            s5_recirculation_flow.Text = " - ";
                            s5_tank_lvl.Text = " - ";
                            s5_reconnect.Visible = true;
                            break;
                        default:
                            break;
                    }
                }
            }

            if (stations_data.stationVariables[0].mode == MANUAL_MODE)
            {
                manual_mode_btn.BackColor = Color.LimeGreen;
                cargo_transfer_mode_btn.BackColor = Color.Gainsboro;
                recirculation_mode_btn.BackColor = Color.Gainsboro;
            }
            else if (stations_data.stationVariables[0].mode == CARGO_TRANSFER_MODE)
            {
                manual_mode_btn.BackColor = Color.Gainsboro;
                cargo_transfer_mode_btn.BackColor = Color.LimeGreen;
                recirculation_mode_btn.BackColor = Color.Gainsboro;
            }
            else if (stations_data.stationVariables[0].mode == RECIRCULATION_MODE)
            {
                manual_mode_btn.BackColor = Color.Gainsboro;
                cargo_transfer_mode_btn.BackColor = Color.Gainsboro;
                recirculation_mode_btn.BackColor = Color.LimeGreen;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            updateModbus();
        }

        private void reconnectStationThreadStart(int station)
        {
            Thread connectThread = new Thread(() => reconnectStation(station));
            connectThread.SetApartmentState(ApartmentState.STA);
            connectThread.Start();
        }

        private void control_center_btn_Click(object sender, EventArgs e)
        {
            ControlCenter control_center = new ControlCenter();

            //this.stopTimer();
            control_center.modbusClients = modbusClients;
            control_center.initializeSetpoints();
            control_center.startTimer();
            control_center.Show();
            control_center_btn.Enabled = false;
            //this.Hide();
            control_center.Closed += (s, args) => control_center_btn.Enabled = true;
        }

        private void s1_details_btn_Click(object sender, EventArgs e)
        {
            if (modbusClients[0] != null)
            {
                FirstStationDetails station_details = new FirstStationDetails();
                station_details.modbusClient = modbusClients[0];
                station_details.initializeData();
                station_details.startTimer();
                station_details.Show();
                s1_details_btn.Enabled = false;
                station_details.Closed += (s, args) => s1_details_btn.Enabled = true;
            }
            else
            {
                DialogResult result = MessageBox.Show("The station is offline. Do you want to reconnect?", "Station 1", MessageBoxButtons.YesNo);
                if (result == System.Windows.Forms.DialogResult.Yes)
                {
                    reconnectStationThreadStart(0);
                }
            }
        }

        private void s2_details_btn_Click(object sender, EventArgs e)
        {
            if (modbusClients[1] != null)
            {
                StationDetails station_details = new StationDetails();
                station_details.station_number = 2;
                station_details.modbusClient = modbusClients[1];
                station_details.initializeData();
                station_details.startTimer();
                station_details.Show();
                s2_details_btn.Enabled = false;
                station_details.Closed += (s, args) => s2_details_btn.Enabled = true;
            }
            else
            {
                DialogResult result = MessageBox.Show("The station is offline. Do you want to reconnect?", "Station 2", MessageBoxButtons.YesNo);
                if (result == System.Windows.Forms.DialogResult.Yes)
                {
                    reconnectStationThreadStart(1);
                }
            }
        }

        private void s3_details_btn_Click(object sender, EventArgs e)
        {
            if (modbusClients[2] != null)
            {
                StationDetails station_details = new StationDetails();
                station_details.station_number = 3;
                station_details.modbusClient = modbusClients[2];
                station_details.initializeData();
                station_details.startTimer();
                station_details.Show();
                s3_details_btn.Enabled = false;
                station_details.Closed += (s, args) => s3_details_btn.Enabled = true;
            }
            else
            {
                DialogResult result = MessageBox.Show("The station is offline. Do you want to reconnect?", "Station 3", MessageBoxButtons.YesNo);
                if (result == System.Windows.Forms.DialogResult.Yes)
                {
                    reconnectStationThreadStart(2);
                }
            }
        }

        private void s4_details_btn_Click(object sender, EventArgs e)
        {
            if (modbusClients[3] != null)
            {
                StationDetails station_details = new StationDetails();
                station_details.station_number = 4;
                station_details.modbusClient = modbusClients[3];
                station_details.initializeData();
                station_details.startTimer();
                station_details.Show();
                s4_details_btn.Enabled = false;
                station_details.Closed += (s, args) => s4_details_btn.Enabled = true;
            }
            else
            {
                DialogResult result = MessageBox.Show("The station is offline. Do you want to reconnect?", "Station 4", MessageBoxButtons.YesNo);
                if (result == System.Windows.Forms.DialogResult.Yes)
                {
                    reconnectStationThreadStart(3);
                }
            }
        }

        private void s5_details_btn_Click(object sender, EventArgs e)
        {
            if (modbusClients[4] != null)
            {
                LastStationDetails station_details = new LastStationDetails();
                station_details.modbusClient = modbusClients[4];
                station_details.initializeData();
                station_details.startTimer();
                station_details.Show();
                s5_details_btn.Enabled = false;
                station_details.Closed += (s, args) => s5_details_btn.Enabled = true;
            }
            else
            {
                DialogResult result = MessageBox.Show("The station is offline. Do you want to reconnect?", "Station 5", MessageBoxButtons.YesNo);
                if (result == System.Windows.Forms.DialogResult.Yes)
                {
                    reconnectStationThreadStart(4);
                }
            }
        }

        private void cargo_transfer_mode_btn_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < modbusClients.Length; i++)
            {
                if (modbusClients[i] != null)
                {
                    try
                    {
                        modbusClients[i].WriteSingleRegister(3, CARGO_TRANSFER_MODE);
                        stations_data.stationVariables[i].mode = CARGO_TRANSFER_MODE;
                    }
                    catch
                    {

                    }
                }
            }
        }

        private void recirculation_mode_btn_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < modbusClients.Length; i++)
            {
                if (modbusClients[i] != null)
                {
                    try
                    {
                        modbusClients[i].WriteSingleRegister(3, RECIRCULATION_MODE);
                        stations_data.stationVariables[i].mode = RECIRCULATION_MODE;
                    }
                    catch
                    {

                    }
                }
            }
        }

        private void manual_mode_btn_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < modbusClients.Length; i++)
            {
                if (modbusClients[i] != null)
                {
                    try
                    {
                        modbusClients[i].WriteSingleRegister(3, MANUAL_MODE);
                        stations_data.stationVariables[i].mode = MANUAL_MODE;
                    }
                    catch
                    {

                    }
                }
            }
        }

        private void s1_reconnect_Click(object sender, EventArgs e)
        {
            reconnectStationThreadStart(0);
        }

        private void s2_reconnect_Click(object sender, EventArgs e)
        {
            reconnectStationThreadStart(1);
        }

        private void s3_reconnect_Click(object sender, EventArgs e)
        {
            reconnectStationThreadStart(2);
        }

        private void s4_reconnect_Click(object sender, EventArgs e)
        {
            reconnectStationThreadStart(3);
        }

        private void s5_reconnect_Click(object sender, EventArgs e)
        {
            reconnectStationThreadStart(4);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (warningMsgOn)
            {
                timerTicks = (timerTicks + 1) % 10;

                if (timerTicks < 8)
                    warning_msg.Visible = true;
                else
                    warning_msg.Visible = false;
            }
            else
            {
                timerTicks = 0;
                warning_msg.Visible = false;
            }
        }
    }
}
