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
    public partial class StationDetails : Form
    {
        public int station_number;
        public ModbusClient modbusClient;

        private bool pump_state = false;
        private bool valve_state = false;
        private bool isolation_valve_state = false;

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
            station_title.Text = "Station " + station_number.ToString();
            int[] setpoints = modbusClient.ReadHoldingRegisters(1, 2);
            double min_sp = ((float)setpoints[0] - 100) / 100.0;
            double max_sp = ((float)setpoints[1] - 100) / 100.0;

            station_min_sp.Text = min_sp.ToString();
            station_max_sp.Text = max_sp.ToString();
        }

        public StationDetails()
        {
            InitializeComponent();
        }

        private void updateModbus()
        {
            try
            {
                int[] registers = modbusClient.ReadHoldingRegisters(0, 4);
                int[] inputs = modbusClient.ReadInputRegisters(0, 2);
                bool[] coilStatus = modbusClient.ReadCoils(0, 3);

                double pressure = ((float)inputs[0] - 100) / 100.0;
                double flow_rate = inputs[1];
                int mode = registers[3];
                pump_state = coilStatus[0];
                valve_state = coilStatus[1];
                isolation_valve_state = coilStatus[2];

                station_pressure.Text = "Value: " + pressure.ToString() + " bar";
                station_flow.Text = "Rate: " + flow_rate.ToString() + " KL/h";
                station_pump.Image = (pump_state == true) ? Image.FromFile("./sprites/pump_on.png") : Image.FromFile("./sprites/pump_off.png");
                station_valve.Image = (valve_state == true) ? Image.FromFile("./sprites/valve_on_90.png") : Image.FromFile("./sprites/valve_off_90.png");
                station_isolation_valve.Image = (isolation_valve_state == true) ? Image.FromFile("./sprites/valve_on.png") : Image.FromFile("./sprites/valve_off.png");

                pump_switch_btn.BackColor = (stations_data.stationVariables[station_number - 1].man_pump_state == 1) ? Color.LimeGreen : Color.Gainsboro;
                valve_switch_btn.BackColor = (stations_data.stationVariables[station_number - 1].man_valve_state == 1) ? Color.LimeGreen : Color.Gainsboro;
                isolation_valve_switch_btn.BackColor = (stations_data.stationVariables[station_number - 1].man_isolation_valve_state == 1) ? Color.LimeGreen : Color.Gainsboro;
            }

            catch
            {
                station_pump.Image = Image.FromFile("./sprites/pump_offline.png");
                station_valve.Image = Image.FromFile("./sprites/valve_offline_90.png");
                station_isolation_valve.Image = Image.FromFile("./sprites/valve_offline.png");

                station_pressure.Text = "Value: - ";
                station_flow.Text = "Rate: - ";

                pump_switch_btn.Enabled = false;
                valve_switch_btn.Enabled = false;
                isolation_valve_switch_btn.Enabled = false;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            updateModbus();
        }

        private void change_sp_btn_Click_1(object sender, EventArgs e)
        {
            int[] setpoints = new int[2];
            setpoints[0] = Convert.ToInt16((Convert.ToDouble(station_min_sp.Text) * 100) + 100);
            setpoints[1] = Convert.ToInt16((Convert.ToDouble(station_max_sp.Text) * 100) + 100);
            modbusClient.WriteMultipleRegisters(1, setpoints);

            stations_data.stationVariables[station_number - 1].min_sp = setpoints[0];
            stations_data.stationVariables[station_number - 1].max_sp = setpoints[1];
        }

        private void pump_switch_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[station_number - 1].man_pump_state = (stations_data.stationVariables[station_number - 1].man_pump_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(4, stations_data.stationVariables[station_number - 1].man_pump_state);
        }

        private void valve_switch_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[station_number - 1].man_valve_state = (stations_data.stationVariables[station_number - 1].man_valve_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(5, stations_data.stationVariables[station_number - 1].man_valve_state);
        }

        private void isolation_valve_switch_btn_Click(object sender, EventArgs e)
        {
            stations_data.stationVariables[station_number - 1].man_isolation_valve_state = (stations_data.stationVariables[station_number - 1].man_isolation_valve_state == 1) ? 0 : 1;
            modbusClient.WriteSingleRegister(6, stations_data.stationVariables[station_number - 1].man_isolation_valve_state);
        }
    }
}
