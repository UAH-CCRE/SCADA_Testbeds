namespace VirtualGasPipeline_HMI
{
    partial class StationDetails
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StationDetails));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.station_pump = new System.Windows.Forms.PictureBox();
            this.station_isolation_valve = new System.Windows.Forms.PictureBox();
            this.station_valve = new System.Windows.Forms.PictureBox();
            this.station_title = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.station_flow = new System.Windows.Forms.Label();
            this.station_pressure = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.change_sp_btn = new System.Windows.Forms.Button();
            this.station_max_sp = new System.Windows.Forms.TextBox();
            this.station_min_sp = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.valve_switch_btn = new System.Windows.Forms.Button();
            this.pump_switch_btn = new System.Windows.Forms.Button();
            this.isolation_valve_switch_btn = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.manual_control = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_pump)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_isolation_valve)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_valve)).BeginInit();
            this.manual_control.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(13, 80);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(708, 350);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // station_pump
            // 
            this.station_pump.Image = ((System.Drawing.Image)(resources.GetObject("station_pump.Image")));
            this.station_pump.Location = new System.Drawing.Point(272, 119);
            this.station_pump.Name = "station_pump";
            this.station_pump.Size = new System.Drawing.Size(89, 83);
            this.station_pump.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.station_pump.TabIndex = 1;
            this.station_pump.TabStop = false;
            // 
            // station_isolation_valve
            // 
            this.station_isolation_valve.Image = ((System.Drawing.Image)(resources.GetObject("station_isolation_valve.Image")));
            this.station_isolation_valve.Location = new System.Drawing.Point(153, 151);
            this.station_isolation_valve.Name = "station_isolation_valve";
            this.station_isolation_valve.Size = new System.Drawing.Size(38, 21);
            this.station_isolation_valve.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.station_isolation_valve.TabIndex = 2;
            this.station_isolation_valve.TabStop = false;
            // 
            // station_valve
            // 
            this.station_valve.Image = ((System.Drawing.Image)(resources.GetObject("station_valve.Image")));
            this.station_valve.Location = new System.Drawing.Point(599, 280);
            this.station_valve.Name = "station_valve";
            this.station_valve.Size = new System.Drawing.Size(21, 38);
            this.station_valve.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.station_valve.TabIndex = 3;
            this.station_valve.TabStop = false;
            // 
            // station_title
            // 
            this.station_title.AutoSize = true;
            this.station_title.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_title.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_title.Location = new System.Drawing.Point(262, 9);
            this.station_title.Name = "station_title";
            this.station_title.Size = new System.Drawing.Size(222, 55);
            this.station_title.TabIndex = 4;
            this.station_title.Text = "Station 1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label2.Location = new System.Drawing.Point(68, 174);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 16);
            this.label2.TabIndex = 5;
            this.label2.Text = "Flow Meter";
            // 
            // station_flow
            // 
            this.station_flow.AutoSize = true;
            this.station_flow.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_flow.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_flow.Location = new System.Drawing.Point(40, 191);
            this.station_flow.Name = "station_flow";
            this.station_flow.Size = new System.Drawing.Size(111, 16);
            this.station_flow.TabIndex = 6;
            this.station_flow.Text = "Rate: 20.4 KL/h";
            // 
            // station_pressure
            // 
            this.station_pressure.AutoSize = true;
            this.station_pressure.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_pressure.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.station_pressure.Location = new System.Drawing.Point(479, 194);
            this.station_pressure.Name = "station_pressure";
            this.station_pressure.Size = new System.Drawing.Size(111, 16);
            this.station_pressure.TabIndex = 8;
            this.station_pressure.Text = "Value: 5.43 bar";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label5.Location = new System.Drawing.Point(467, 177);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(123, 16);
            this.label5.TabIndex = 7;
            this.label5.Text = "Pressure Sensor";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label6.Location = new System.Drawing.Point(257, 270);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(129, 26);
            this.label6.TabIndex = 9;
            this.label6.Text = "    Mechanical pressure\r\nrelief valve set at 10.3 bar";
            // 
            // change_sp_btn
            // 
            this.change_sp_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.change_sp_btn.Location = new System.Drawing.Point(392, 347);
            this.change_sp_btn.Name = "change_sp_btn";
            this.change_sp_btn.Size = new System.Drawing.Size(75, 66);
            this.change_sp_btn.TabIndex = 14;
            this.change_sp_btn.Text = "Set";
            this.change_sp_btn.UseVisualStyleBackColor = true;
            this.change_sp_btn.Click += new System.EventHandler(this.change_sp_btn_Click_1);
            // 
            // station_max_sp
            // 
            this.station_max_sp.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_max_sp.Location = new System.Drawing.Point(284, 384);
            this.station_max_sp.Name = "station_max_sp";
            this.station_max_sp.Size = new System.Drawing.Size(102, 29);
            this.station_max_sp.TabIndex = 13;
            // 
            // station_min_sp
            // 
            this.station_min_sp.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.station_min_sp.Location = new System.Drawing.Point(284, 348);
            this.station_min_sp.Name = "station_min_sp";
            this.station_min_sp.Size = new System.Drawing.Size(102, 29);
            this.station_min_sp.TabIndex = 12;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label1.Location = new System.Drawing.Point(184, 383);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 29);
            this.label1.TabIndex = 11;
            this.label1.Text = "Max SP:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label7.Location = new System.Drawing.Point(189, 347);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(96, 29);
            this.label7.TabIndex = 10;
            this.label7.Text = "Min SP:";
            // 
            // valve_switch_btn
            // 
            this.valve_switch_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.valve_switch_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.valve_switch_btn.Location = new System.Drawing.Point(191, 20);
            this.valve_switch_btn.Name = "valve_switch_btn";
            this.valve_switch_btn.Size = new System.Drawing.Size(81, 56);
            this.valve_switch_btn.TabIndex = 16;
            this.valve_switch_btn.Text = "Pressure Relief Valve";
            this.valve_switch_btn.UseVisualStyleBackColor = true;
            this.valve_switch_btn.Click += new System.EventHandler(this.valve_switch_btn_Click);
            // 
            // pump_switch_btn
            // 
            this.pump_switch_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pump_switch_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.pump_switch_btn.Location = new System.Drawing.Point(99, 20);
            this.pump_switch_btn.Name = "pump_switch_btn";
            this.pump_switch_btn.Size = new System.Drawing.Size(81, 56);
            this.pump_switch_btn.TabIndex = 15;
            this.pump_switch_btn.Text = "Pump";
            this.pump_switch_btn.UseVisualStyleBackColor = true;
            this.pump_switch_btn.Click += new System.EventHandler(this.pump_switch_btn_Click);
            // 
            // isolation_valve_switch_btn
            // 
            this.isolation_valve_switch_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.isolation_valve_switch_btn.ForeColor = System.Drawing.SystemColors.ControlText;
            this.isolation_valve_switch_btn.Location = new System.Drawing.Point(6, 20);
            this.isolation_valve_switch_btn.Name = "isolation_valve_switch_btn";
            this.isolation_valve_switch_btn.Size = new System.Drawing.Size(81, 56);
            this.isolation_valve_switch_btn.TabIndex = 17;
            this.isolation_valve_switch_btn.Text = "Station Isolation Valve";
            this.isolation_valve_switch_btn.UseVisualStyleBackColor = true;
            this.isolation_valve_switch_btn.Click += new System.EventHandler(this.isolation_valve_switch_btn_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label8.Location = new System.Drawing.Point(12, 115);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(73, 39);
            this.label8.TabIndex = 18;
            this.label8.Text = "From previous\r\nstation\r\n<---";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.label9.Location = new System.Drawing.Point(678, 117);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(43, 39);
            this.label9.TabIndex = 19;
            this.label9.Text = "To next\r\nstation\r\n--->";
            // 
            // manual_control
            // 
            this.manual_control.BackColor = System.Drawing.Color.Transparent;
            this.manual_control.Controls.Add(this.valve_switch_btn);
            this.manual_control.Controls.Add(this.pump_switch_btn);
            this.manual_control.Controls.Add(this.isolation_valve_switch_btn);
            this.manual_control.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.manual_control.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.manual_control.Location = new System.Drawing.Point(189, 419);
            this.manual_control.Name = "manual_control";
            this.manual_control.Size = new System.Drawing.Size(278, 84);
            this.manual_control.TabIndex = 20;
            this.manual_control.TabStop = false;
            this.manual_control.Text = "Manual Control";
            // 
            // StationDetails
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(735, 515);
            this.Controls.Add(this.manual_control);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
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
            this.Controls.Add(this.station_title);
            this.Controls.Add(this.station_valve);
            this.Controls.Add(this.station_isolation_valve);
            this.Controls.Add(this.station_pump);
            this.Controls.Add(this.pictureBox1);
            this.Name = "StationDetails";
            this.Text = "StationDetails";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_pump)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_isolation_valve)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.station_valve)).EndInit();
            this.manual_control.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox station_pump;
        private System.Windows.Forms.PictureBox station_isolation_valve;
        private System.Windows.Forms.PictureBox station_valve;
        private System.Windows.Forms.Label station_title;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label station_flow;
        private System.Windows.Forms.Label station_pressure;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button change_sp_btn;
        private System.Windows.Forms.TextBox station_max_sp;
        private System.Windows.Forms.TextBox station_min_sp;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button valve_switch_btn;
        private System.Windows.Forms.Button pump_switch_btn;
        private System.Windows.Forms.Button isolation_valve_switch_btn;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.GroupBox manual_control;
    }
}