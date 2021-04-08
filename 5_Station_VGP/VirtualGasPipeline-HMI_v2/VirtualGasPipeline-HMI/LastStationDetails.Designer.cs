namespace VirtualGasPipeline_HMI
{
    partial class LastStationDetails
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LastStationDetails));
            this.station_tank_flow = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.station_tank_lvl = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.manual_control = new System.Windows.Forms.GroupBox();
            this.return_valve_btn = new System.Windows.Forms.Button();
            this.relief_valve_btn = new System.Windows.Forms.Button();
            this.inlet_valve_btn = new System.Windows.Forms.Button();
            this.pump_btn = new System.Windows.Forms.Button();
            this.isolation_valve_btn = new System.Windows.Forms.Button();
            this.change_sp_btn = new System.Windows.Forms.Button();
            this.station_max_sp = new System.Windows.Forms.TextBox();
            this.station_min_sp = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.station_pressure = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.station_flow = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.inlet_valve = new System.Windows.Forms.PictureBox();
            this.relief_valve = new System.Windows.Forms.PictureBox();
            this.isolation_valve = new System.Windows.Forms.PictureBox();
            this.station_pump = new System.Windows.Forms.PictureBox();
            this.station_title = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.return_valve = new System.Windows.Forms.PictureBox();
            this.station_return_flow = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.manual_control.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.inlet_valve)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.relief_valve)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.isolation_valve)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_pump)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.return_valve)).BeginInit();
            this.SuspendLayout();
            // 
            // station_tank_flow
            // 
            this.station_tank_flow.AutoSize = true;
            this.station_tank_flow.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_tank_flow.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_tank_flow.Location = new System.Drawing.Point(762, 199);
            this.station_tank_flow.Name = "station_tank_flow";
            this.station_tank_flow.Size = new System.Drawing.Size(111, 16);
            this.station_tank_flow.TabIndex = 152;
            this.station_tank_flow.Text = "Rate: 20.4 KL/h";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label8.Location = new System.Drawing.Point(790, 182);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(83, 16);
            this.label8.TabIndex = 151;
            this.label8.Text = "Flow Meter";
            // 
            // station_tank_lvl
            // 
            this.station_tank_lvl.AutoSize = true;
            this.station_tank_lvl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_tank_lvl.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_tank_lvl.Location = new System.Drawing.Point(904, 624);
            this.station_tank_lvl.Name = "station_tank_lvl";
            this.station_tank_lvl.Size = new System.Drawing.Size(53, 16);
            this.station_tank_lvl.TabIndex = 150;
            this.station_tank_lvl.Text = "103 KL";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label3.Location = new System.Drawing.Point(821, 624);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(85, 16);
            this.label3.TabIndex = 149;
            this.label3.Text = "Tank level:";
            // 
            // manual_control
            // 
            this.manual_control.BackColor = System.Drawing.Color.Transparent;
            this.manual_control.Controls.Add(this.return_valve_btn);
            this.manual_control.Controls.Add(this.relief_valve_btn);
            this.manual_control.Controls.Add(this.inlet_valve_btn);
            this.manual_control.Controls.Add(this.pump_btn);
            this.manual_control.Controls.Add(this.isolation_valve_btn);
            this.manual_control.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.manual_control.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.manual_control.Location = new System.Drawing.Point(126, 445);
            this.manual_control.Name = "manual_control";
            this.manual_control.Size = new System.Drawing.Size(443, 84);
            this.manual_control.TabIndex = 148;
            this.manual_control.TabStop = false;
            this.manual_control.Text = "Manual Control";
            // 
            // return_valve_btn
            // 
            this.return_valve_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.return_valve_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.return_valve_btn.Location = new System.Drawing.Point(355, 20);
            this.return_valve_btn.Name = "return_valve_btn";
            this.return_valve_btn.Size = new System.Drawing.Size(81, 56);
            this.return_valve_btn.TabIndex = 157;
            this.return_valve_btn.Text = "Return Body Valve";
            this.return_valve_btn.UseVisualStyleBackColor = true;
            this.return_valve_btn.Click += new System.EventHandler(this.return_valve_btn_Click);
            // 
            // relief_valve_btn
            // 
            this.relief_valve_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.relief_valve_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.relief_valve_btn.Location = new System.Drawing.Point(181, 20);
            this.relief_valve_btn.Name = "relief_valve_btn";
            this.relief_valve_btn.Size = new System.Drawing.Size(81, 56);
            this.relief_valve_btn.TabIndex = 30;
            this.relief_valve_btn.Text = "Pressure Relief Valve";
            this.relief_valve_btn.UseVisualStyleBackColor = true;
            this.relief_valve_btn.Click += new System.EventHandler(this.relief_valve_btn_Click);
            // 
            // inlet_valve_btn
            // 
            this.inlet_valve_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.inlet_valve_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.inlet_valve_btn.Location = new System.Drawing.Point(268, 20);
            this.inlet_valve_btn.Name = "inlet_valve_btn";
            this.inlet_valve_btn.Size = new System.Drawing.Size(81, 56);
            this.inlet_valve_btn.TabIndex = 34;
            this.inlet_valve_btn.Text = "Inlet Body Valve";
            this.inlet_valve_btn.UseVisualStyleBackColor = true;
            this.inlet_valve_btn.Click += new System.EventHandler(this.inlet_valve_btn_Click);
            // 
            // pump_btn
            // 
            this.pump_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pump_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.pump_btn.Location = new System.Drawing.Point(94, 20);
            this.pump_btn.Name = "pump_btn";
            this.pump_btn.Size = new System.Drawing.Size(81, 56);
            this.pump_btn.TabIndex = 32;
            this.pump_btn.Text = "Pump";
            this.pump_btn.UseVisualStyleBackColor = true;
            this.pump_btn.Click += new System.EventHandler(this.pump_btn_Click);
            // 
            // isolation_valve_btn
            // 
            this.isolation_valve_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.isolation_valve_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.isolation_valve_btn.Location = new System.Drawing.Point(7, 20);
            this.isolation_valve_btn.Name = "isolation_valve_btn";
            this.isolation_valve_btn.Size = new System.Drawing.Size(81, 56);
            this.isolation_valve_btn.TabIndex = 33;
            this.isolation_valve_btn.Text = "Station Isolation Valve";
            this.isolation_valve_btn.UseVisualStyleBackColor = true;
            this.isolation_valve_btn.Click += new System.EventHandler(this.isolation_valve_btn_Click);
            // 
            // change_sp_btn
            // 
            this.change_sp_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.change_sp_btn.Location = new System.Drawing.Point(409, 366);
            this.change_sp_btn.Name = "change_sp_btn";
            this.change_sp_btn.Size = new System.Drawing.Size(75, 66);
            this.change_sp_btn.TabIndex = 146;
            this.change_sp_btn.Text = "Set";
            this.change_sp_btn.UseVisualStyleBackColor = true;
            this.change_sp_btn.Click += new System.EventHandler(this.change_sp_btn_Click);
            // 
            // station_max_sp
            // 
            this.station_max_sp.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_max_sp.Location = new System.Drawing.Point(301, 403);
            this.station_max_sp.Name = "station_max_sp";
            this.station_max_sp.Size = new System.Drawing.Size(102, 29);
            this.station_max_sp.TabIndex = 145;
            // 
            // station_min_sp
            // 
            this.station_min_sp.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_min_sp.Location = new System.Drawing.Point(301, 367);
            this.station_min_sp.Name = "station_min_sp";
            this.station_min_sp.Size = new System.Drawing.Size(102, 29);
            this.station_min_sp.TabIndex = 144;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label1.Location = new System.Drawing.Point(201, 402);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 29);
            this.label1.TabIndex = 143;
            this.label1.Text = "Max SP:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label7.Location = new System.Drawing.Point(206, 366);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(96, 29);
            this.label7.TabIndex = 142;
            this.label7.Text = "Min SP:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label6.Location = new System.Drawing.Point(290, 286);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(129, 26);
            this.label6.TabIndex = 141;
            this.label6.Text = "    Mechanical pressure\r\nrelief valve set at 10.3 bar";
            // 
            // station_pressure
            // 
            this.station_pressure.AutoSize = true;
            this.station_pressure.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_pressure.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_pressure.Location = new System.Drawing.Point(541, 200);
            this.station_pressure.Name = "station_pressure";
            this.station_pressure.Size = new System.Drawing.Size(111, 16);
            this.station_pressure.TabIndex = 140;
            this.station_pressure.Text = "Value: 5.43 bar";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label5.Location = new System.Drawing.Point(529, 183);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(123, 16);
            this.label5.TabIndex = 139;
            this.label5.Text = "Pressure Sensor";
            // 
            // station_flow
            // 
            this.station_flow.AutoSize = true;
            this.station_flow.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_flow.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_flow.Location = new System.Drawing.Point(50, 197);
            this.station_flow.Name = "station_flow";
            this.station_flow.Size = new System.Drawing.Size(111, 16);
            this.station_flow.TabIndex = 138;
            this.station_flow.Text = "Rate: 20.4 KL/h";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label2.Location = new System.Drawing.Point(78, 180);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 16);
            this.label2.TabIndex = 137;
            this.label2.Text = "Flow Meter";
            // 
            // inlet_valve
            // 
            this.inlet_valve.Image = ((System.Drawing.Image)(resources.GetObject("inlet_valve.Image")));
            this.inlet_valve.Location = new System.Drawing.Point(883, 269);
            this.inlet_valve.Name = "inlet_valve";
            this.inlet_valve.Size = new System.Drawing.Size(21, 38);
            this.inlet_valve.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.inlet_valve.TabIndex = 136;
            this.inlet_valve.TabStop = false;
            // 
            // relief_valve
            // 
            this.relief_valve.Image = ((System.Drawing.Image)(resources.GetObject("relief_valve.Image")));
            this.relief_valve.Location = new System.Drawing.Point(668, 269);
            this.relief_valve.Name = "relief_valve";
            this.relief_valve.Size = new System.Drawing.Size(21, 38);
            this.relief_valve.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.relief_valve.TabIndex = 135;
            this.relief_valve.TabStop = false;
            // 
            // isolation_valve
            // 
            this.isolation_valve.Image = ((System.Drawing.Image)(resources.GetObject("isolation_valve.Image")));
            this.isolation_valve.Location = new System.Drawing.Point(172, 154);
            this.isolation_valve.Name = "isolation_valve";
            this.isolation_valve.Size = new System.Drawing.Size(38, 21);
            this.isolation_valve.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.isolation_valve.TabIndex = 134;
            this.isolation_valve.TabStop = false;
            // 
            // station_pump
            // 
            this.station_pump.Image = ((System.Drawing.Image)(resources.GetObject("station_pump.Image")));
            this.station_pump.Location = new System.Drawing.Point(307, 124);
            this.station_pump.Name = "station_pump";
            this.station_pump.Size = new System.Drawing.Size(89, 83);
            this.station_pump.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.station_pump.TabIndex = 133;
            this.station_pump.TabStop = false;
            // 
            // station_title
            // 
            this.station_title.AutoSize = true;
            this.station_title.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_title.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_title.Location = new System.Drawing.Point(363, 9);
            this.station_title.Name = "station_title";
            this.station_title.Size = new System.Drawing.Size(222, 55);
            this.station_title.TabIndex = 132;
            this.station_title.Text = "Station 5";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 74);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(943, 549);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 131;
            this.pictureBox1.TabStop = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label4.Location = new System.Drawing.Point(16, 117);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(73, 39);
            this.label4.TabIndex = 153;
            this.label4.Text = "From previous\r\nstation\r\n<---";
            // 
            // return_valve
            // 
            this.return_valve.Image = ((System.Drawing.Image)(resources.GetObject("return_valve.Image")));
            this.return_valve.Location = new System.Drawing.Point(742, 557);
            this.return_valve.Name = "return_valve";
            this.return_valve.Size = new System.Drawing.Size(38, 21);
            this.return_valve.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.return_valve.TabIndex = 154;
            this.return_valve.TabStop = false;
            // 
            // station_return_flow
            // 
            this.station_return_flow.AutoSize = true;
            this.station_return_flow.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_return_flow.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_return_flow.Location = new System.Drawing.Point(718, 458);
            this.station_return_flow.Name = "station_return_flow";
            this.station_return_flow.Size = new System.Drawing.Size(111, 16);
            this.station_return_flow.TabIndex = 156;
            this.station_return_flow.Text = "Rate: 20.4 KL/h";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label10.Location = new System.Drawing.Point(718, 442);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(83, 16);
            this.label10.TabIndex = 155;
            this.label10.Text = "Flow Meter";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // LastStationDetails
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(972, 650);
            this.Controls.Add(this.station_return_flow);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.return_valve);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.station_tank_flow);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.station_tank_lvl);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.manual_control);
            this.Controls.Add(this.change_sp_btn);
            this.Controls.Add(this.station_max_sp);
            this.Controls.Add(this.station_min_sp);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.station_pressure);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.station_flow);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.inlet_valve);
            this.Controls.Add(this.relief_valve);
            this.Controls.Add(this.isolation_valve);
            this.Controls.Add(this.station_pump);
            this.Controls.Add(this.station_title);
            this.Controls.Add(this.pictureBox1);
            this.Name = "LastStationDetails";
            this.Text = "LastStationDetails";
            this.manual_control.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.inlet_valve)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.relief_valve)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.isolation_valve)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_pump)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.return_valve)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label station_tank_flow;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label station_tank_lvl;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox manual_control;
        private System.Windows.Forms.Button relief_valve_btn;
        private System.Windows.Forms.Button inlet_valve_btn;
        private System.Windows.Forms.Button pump_btn;
        private System.Windows.Forms.Button isolation_valve_btn;
        private System.Windows.Forms.Button change_sp_btn;
        private System.Windows.Forms.TextBox station_max_sp;
        private System.Windows.Forms.TextBox station_min_sp;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label station_pressure;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label station_flow;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox inlet_valve;
        private System.Windows.Forms.PictureBox relief_valve;
        private System.Windows.Forms.PictureBox isolation_valve;
        private System.Windows.Forms.PictureBox station_pump;
        private System.Windows.Forms.Label station_title;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PictureBox return_valve;
        private System.Windows.Forms.Label station_return_flow;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button return_valve_btn;
        private System.Windows.Forms.Timer timer1;
    }
}