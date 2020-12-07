using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirtualGasPipeline_HMI
{
    public struct station_variables
    {
        public int min_sp;
        public int max_sp;
        public int mode;
        public int man_pump_state;
        public int man_valve_state;
        public int man_isolation_valve_state;
        public int man_return_valve_state;
        public int man_inlet_valve_state;
    }

    public class stations_data
    {
        public static station_variables[] stationVariables = new station_variables[5];
        public static int return_flow_rate;
        public static int tank_flow_rate;
    }
}
