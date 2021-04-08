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
    public partial class FirstStationDetails : Form
    {
        public ModbusClient modbusClient;

        private bool pump_state = false;
        private bool dispatch_valve_state = false;
        private bool relief_valve_state = false;
        private bool return_valve_state = false;

        public const int MANUAL_MODE = 0;
        const int CARGO_TRANSFER_MODE = 1;
        const int RECIRCULATION_MODE = 2;

        public void startTimer()
        {
            timer1.Start();
        }

        public void stopTimer()
        {
            timer1.Stop();
        }

        public void initializeData()
        {
            int[] setpoints = modbusClient.ReadHoldingRegisters(1, 2);
            double min_sp = ((float)setpoints[0] - 100) / 100.0;
            double max_sp = ((float)setpoints[1] - 100) / 100.0;

            station_min_sp.Text = min_sp.ToString();
            station_max_sp.Text = max_sp.ToString();
        }

        public FirstStationDetails()
        {
            InitializeComponent();
        }

        private void change_sp_btn_Click(object sender, EventArgs e)
        {
            int[] setpoints = new int[2];
            setpoints[0] = Convert.ToInt16((Convert.ToDouble(station_min_sp.Text) * 100) + 100);
            setpoints[1] = Convert.ToInt16((Convert.ToDouble(station_max_sp.Text) * 100) + 100);
            modbusClient.WriteMultipleRegisters(1, setpoints);

            stations_data.stationVariables[0].min_sp = setpoints[0];
            stations_data.stationVariables[0].max_sp = setpoints[1];
        }

        private void updateModbus()
        {
            try
            {
                int[] registers = modbusClient.ReadHoldingRegisters(0, 4);
                int[] inputs = modbusClient.ReadInputRegisters(0, 4);
                bool[] coilStatus = modbusClient.ReadCoils(0, 4);

                double pressure = ((float)inputs[0] - 100) / 100.0;
                double tank_lvl = inputs[1] / 10.0;
                double flow_rate = inputs[2];
                double return_flow_rate = inputs[3];
                int mode = registers[3];
                pump_state = coilStatus[0];
                relief_valve_state = coilStatus[1];
                dispatch_valve_state = coilStatus[2];
                return_valve_state = coilStatus[3];

                station_pressure.Text = "Value: " + pressure.ToString() + " bar";
                station_flow.Text = "Rate: " + flow_rate.ToString() + " KL/h";
                station_return_flow.Text = "Rate: " + return_flow_rate.ToString() + " KL/h";
                station_tank_lvl.Text = tank_lvl.ToString() + " KL";
                station_pump.Image = (pump_state == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                relief_valve.Image = (relief_valve_state == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                dispatch_valve.Image = (dispatch_valve_state == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                return_valve.Image = (return_valve_state == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");

                pump_btn.BackColor = (stations_data.stationVariables[0].man_pump_state == 1) ? Color.LimeGreen : Color.Gainsboro;
                relief_valve_btn.BackColor = (stations_data.stationVariables[0].man_valve_state == 1) ? Color.LimeGreen : Color.Gainsboro;
                return_valve_btn.BackColor = (stations_data.stationVariables[0].man_return_valve_state == 1) ? Color.LimeGreen : Color.Gainsboro;
                dispatch_valve_btn.BackColor = (stations_data.stationVariables[0].man_isolation_valve_state == 1) ? Color.LimeGreen : Color.Gainsboro;

                pump_btn.Enabled = true;
                relief_valve_btn.Enabled = true;
                return_valve_btn.Enabled = true;
                dispatch_valve_btn.Enabled = true;
            }

            catch
            {
                dispatch_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                station_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                relief_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                return_valve.Image = Image.FromFile("./sprites/valve_offline.png");

                station_pressure.Text = "Value: - ";
                station_flow.Text = "Rate: - ";
                station_return_flow.Text = "Rate: - ";
                station_tank_lvl.Text = " - ";

                pump_btn.Enabled = false;
                relief_valve_btn.Enabled = false;
                return_valve_btn.Enabled = false;
                dispatch_valve_btn.Enabled = false;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            updateModbus();
        }

        private void dispatch_valve_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[0].man_isolation_valve_state = (stations_data.stationVariables[0].man_isolation_valve_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(6, stations_data.stationVariables[0].man_isolation_valve_state);
        }

        private void pump_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[0].man_pump_state = (stations_data.stationVariables[0].man_pump_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(4, stations_data.stationVariables[0].man_pump_state);
        }

        private void relief_valve_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[0].man_valve_state = (stations_data.stationVariables[0].man_valve_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(5, stations_data.stationVariables[0].man_valve_state);
        }

        private void return_valve_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[0].man_return_valve_state = (stations_data.stationVariables[0].man_return_valve_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(7, stations_data.stationVariables[0].man_return_valve_state);
        }
    }
}
