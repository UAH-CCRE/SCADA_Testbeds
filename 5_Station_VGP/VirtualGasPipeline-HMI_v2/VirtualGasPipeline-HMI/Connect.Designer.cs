namespace VirtualGasPipeline_HMI
{
    partial class Connect
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.ipAddressControl1 = new IPAddressControlLib.IPAddressControl();
            this.ipAddressControl2 = new IPAddressControlLib.IPAddressControl();
            this.ipAddressControl3 = new IPAddressControlLib.IPAddressControl();
            this.ipAddressControl4 = new IPAddressControlLib.IPAddressControl();
            this.ipAddressControl5 = new IPAddressControlLib.IPAddressControl();
            this.statusLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(34, 15);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(297, 29);
            this.label1.TabIndex = 0;
            this.label1.Text = "Virtual Gas Pipeline HMI";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 99);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(87, 18);
            this.label2.TabIndex = 1;
            this.label2.Text = "Station 1 IP:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(6, 191);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(87, 18);
            this.label5.TabIndex = 4;
            this.label5.Text = "Station 4 IP:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(6, 161);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(87, 18);
            this.label4.TabIndex = 3;
            this.label4.Text = "Station 3 IP:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 130);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 18);
            this.label3.TabIndex = 2;
            this.label3.Text = "Station 2 IP:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(6, 222);
            this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(87, 18);
            this.label6.TabIndex = 5;
            this.label6.Text = "Station 5 IP:";
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(110, 274);
            this.button1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(148, 41);
            this.button1.TabIndex = 6;
            this.button1.Text = "Connect";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // ipAddressControl1
            // 
            this.ipAddressControl1.AllowInternalTab = false;
            this.ipAddressControl1.AutoHeight = true;
            this.ipAddressControl1.BackColor = System.Drawing.SystemColors.Window;
            this.ipAddressControl1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ipAddressControl1.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.ipAddressControl1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ipAddressControl1.Location = new System.Drawing.Point(96, 100);
            this.ipAddressControl1.MinimumSize = new System.Drawing.Size(99, 21);
            this.ipAddressControl1.Name = "ipAddressControl1";
            this.ipAddressControl1.ReadOnly = false;
            this.ipAddressControl1.Size = new System.Drawing.Size(252, 21);
            this.ipAddressControl1.TabIndex = 8;
            this.ipAddressControl1.Text = "...";
            // 
            // ipAddressControl2
            // 
            this.ipAddressControl2.AllowInternalTab = false;
            this.ipAddressControl2.AutoHeight = true;
            this.ipAddressControl2.BackColor = System.Drawing.SystemColors.Window;
            this.ipAddressControl2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ipAddressControl2.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.ipAddressControl2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ipAddressControl2.Location = new System.Drawing.Point(96, 131);
            this.ipAddressControl2.MinimumSize = new System.Drawing.Size(99, 21);
            this.ipAddressControl2.Name = "ipAddressControl2";
            this.ipAddressControl2.ReadOnly = false;
            this.ipAddressControl2.Size = new System.Drawing.Size(252, 21);
            this.ipAddressControl2.TabIndex = 9;
            this.ipAddressControl2.Text = "...";
            // 
            // ipAddressControl3
            // 
            this.ipAddressControl3.AllowInternalTab = false;
            this.ipAddressControl3.AutoHeight = true;
            this.ipAddressControl3.BackColor = System.Drawing.SystemColors.Window;
            this.ipAddressControl3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ipAddressControl3.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.ipAddressControl3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ipAddressControl3.Location = new System.Drawing.Point(96, 161);
            this.ipAddressControl3.MinimumSize = new System.Drawing.Size(99, 21);
            this.ipAddressControl3.Name = "ipAddressControl3";
            this.ipAddressControl3.ReadOnly = false;
            this.ipAddressControl3.Size = new System.Drawing.Size(252, 21);
            this.ipAddressControl3.TabIndex = 10;
            this.ipAddressControl3.Text = "...";
            // 
            // ipAddressControl4
            // 
            this.ipAddressControl4.AllowInternalTab = false;
            this.ipAddressControl4.AutoHeight = true;
            this.ipAddressControl4.BackColor = System.Drawing.SystemColors.Window;
            this.ipAddressControl4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ipAddressControl4.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.ipAddressControl4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ipAddressControl4.Location = new System.Drawing.Point(96, 192);
            this.ipAddressControl4.MinimumSize = new System.Drawing.Size(99, 21);
            this.ipAddressControl4.Name = "ipAddressControl4";
            this.ipAddressControl4.ReadOnly = false;
            this.ipAddressControl4.Size = new System.Drawing.Size(252, 21);
            this.ipAddressControl4.TabIndex = 11;
            this.ipAddressControl4.Text = "...";
            // 
            // ipAddressControl5
            // 
            this.ipAddressControl5.AllowInternalTab = false;
            this.ipAddressControl5.AutoHeight = true;
            this.ipAddressControl5.BackColor = System.Drawing.SystemColors.Window;
            this.ipAddressControl5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ipAddressControl5.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.ipAddressControl5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ipAddressControl5.Location = new System.Drawing.Point(96, 223);
            this.ipAddressControl5.MinimumSize = new System.Drawing.Size(99, 21);
            this.ipAddressControl5.Name = "ipAddressControl5";
            this.ipAddressControl5.ReadOnly = false;
            this.ipAddressControl5.Size = new System.Drawing.Size(252, 21);
            this.ipAddressControl5.TabIndex = 12;
            this.ipAddressControl5.Text = "...";
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(116, 316);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(128, 13);
            this.statusLabel.TabIndex = 13;
            this.statusLabel.Text = "Establishing connection...";
            this.statusLabel.Visible = false;
            // 
            // Connect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(366, 334);
            this.Controls.Add(this.statusLabel);
            this.Controls.Add(this.ipAddressControl5);
            this.Controls.Add(this.ipAddressControl4);
            this.Controls.Add(this.ipAddressControl3);
            this.Controls.Add(this.ipAddressControl2);
            this.Controls.Add(this.ipAddressControl1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Connect";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button1;
        private IPAddressControlLib.IPAddressControl ipAddressControl1;
        private IPAddressControlLib.IPAddressControl ipAddressControl2;
        private IPAddressControlLib.IPAddressControl ipAddressControl3;
        private IPAddressControlLib.IPAddressControl ipAddressControl4;
        private IPAddressControlLib.IPAddressControl ipAddressControl5;
        private System.Windows.Forms.Label statusLabel;
    }
}

