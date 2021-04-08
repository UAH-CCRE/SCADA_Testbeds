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
    public partial class Connect : Form
    {
        ModbusClient[] modbusClients = new ModbusClient[5];
        string[] stationIP = new string[5];
        bool[] threadFinished = new bool[5];

        public Connect()
        {
            InitializeComponent();
            ipAddressControl1.Text = Properties.Settings.Default.Station1_ip;
            ipAddressControl2.Text = Properties.Settings.Default.Station2_ip;
            ipAddressControl3.Text = Properties.Settings.Default.Station3_ip;
            ipAddressControl4.Text = Properties.Settings.Default.Station4_ip;
            ipAddressControl5.Text = Properties.Settings.Default.Station5_ip;
        }

        private delegate void startMainHMICallback();
        private void startMainHMI()
        {
            bool endLoop = false;
            while (!endLoop)
            {
                endLoop = true;
                for (int i = 0; i < 5; i++)
                {
                    if (!threadFinished[i])
                    {
                        endLoop = false;
                    }
                }
                Thread.Sleep(500);
            }

            if (this.button1.InvokeRequired) //this is not the UI thread
            {
                startMainHMICallback d = new startMainHMICallback(startMainHMI);
                Invoke(d, new object[] { });
            }

            else
            {
                MainView hmi = new MainView();

                hmi.modbusClients = modbusClients;
                hmi.stationIP = this.stationIP;
                hmi.startVariables();
                hmi.startTimer();
                hmi.Show();
                this.Hide();
                hmi.Closed += (s, args) => this.Close();
            }
        }

        private void startModbusConnections(int station)
        {
            modbusClients[station] = new ModbusClient(stationIP[station], 502);
            try
            {
                modbusClients[station].Connect();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                modbusClients[station] = null; //remove the actual modbus client from the list
            }

            threadFinished[station] = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;
            statusLabel.Visible = true;

            Properties.Settings.Default.Station1_ip = ipAddressControl1.Text;
            stationIP[0] = ipAddressControl1.Text;
            Properties.Settings.Default.Station2_ip = ipAddressControl2.Text;
            stationIP[1] = ipAddressControl2.Text;
            Properties.Settings.Default.Station3_ip = ipAddressControl3.Text;
            stationIP[2] = ipAddressControl3.Text;
            Properties.Settings.Default.Station4_ip = ipAddressControl4.Text;
            stationIP[3] = ipAddressControl4.Text;
            Properties.Settings.Default.Station5_ip = ipAddressControl5.Text;
            stationIP[4] = ipAddressControl5.Text;
            Properties.Settings.Default.Save();

            Thread connectThread1 = new Thread(() => startModbusConnections(0));
            connectThread1.SetApartmentState(ApartmentState.STA);
            connectThread1.Start();
            Thread connectThread2 = new Thread(() => startModbusConnections(1));
            connectThread2.SetApartmentState(ApartmentState.STA);
            connectThread2.Start();
            Thread connectThread3 = new Thread(() => startModbusConnections(2));
            connectThread3.SetApartmentState(ApartmentState.STA);
            connectThread3.Start();
            Thread connectThread4 = new Thread(() => startModbusConnections(3));
            connectThread4.SetApartmentState(ApartmentState.STA);
            connectThread4.Start();
            Thread connectThread5 = new Thread(() => startModbusConnections(4));
            connectThread5.SetApartmentState(ApartmentState.STA);
            connectThread5.Start();

            Thread startHMI = new Thread(() => startMainHMI());
            startHMI.SetApartmentState(ApartmentState.STA);
            startHMI.Start();
        }
    }
}
