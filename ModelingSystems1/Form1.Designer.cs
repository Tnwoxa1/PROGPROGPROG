namespace ModelingSystems1
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.MainPic = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.buttonStart = new System.Windows.Forms.Button();
            this.buttonStop = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.numericUpDown_m = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDown_k = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.numericUpDown_mu = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.numericUpDown_v = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_x = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.MainPic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_m)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_k)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_mu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_v)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_x)).BeginInit();
            this.SuspendLayout();
            // 
            // MainPic
            // 
            this.MainPic.Location = new System.Drawing.Point(0, 0);
            this.MainPic.Name = "MainPic";
            this.MainPic.Size = new System.Drawing.Size(650, 195);
            this.MainPic.TabIndex = 0;
            this.MainPic.TabStop = false;
            this.MainPic.Paint += new System.Windows.Forms.PaintEventHandler(this.MainPic_Paint);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(319, 302);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(102, 44);
            this.buttonStart.TabIndex = 1;
            this.buttonStart.Text = "Старт";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // buttonStop
            // 
            this.buttonStop.Location = new System.Drawing.Point(427, 302);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(102, 44);
            this.buttonStop.TabIndex = 2;
            this.buttonStop.Text = "Стоп";
            this.buttonStop.UseVisualStyleBackColor = true;
            this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Right;
            this.pictureBox1.Location = new System.Drawing.Point(656, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(460, 450);
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
            // 
            // numericUpDown_m
            // 
            this.numericUpDown_m.DecimalPlaces = 1;
            this.numericUpDown_m.Location = new System.Drawing.Point(95, 264);
            this.numericUpDown_m.Name = "numericUpDown_m";
            this.numericUpDown_m.Size = new System.Drawing.Size(77, 20);
            this.numericUpDown_m.TabIndex = 4;
            this.numericUpDown_m.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(74, 266);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(15, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "m";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(74, 292);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "k";
            // 
            // numericUpDown_k
            // 
            this.numericUpDown_k.DecimalPlaces = 1;
            this.numericUpDown_k.Location = new System.Drawing.Point(95, 290);
            this.numericUpDown_k.Name = "numericUpDown_k";
            this.numericUpDown_k.Size = new System.Drawing.Size(77, 20);
            this.numericUpDown_k.TabIndex = 6;
            this.numericUpDown_k.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(74, 318);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(13, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "μ";
            // 
            // numericUpDown_mu
            // 
            this.numericUpDown_mu.DecimalPlaces = 1;
            this.numericUpDown_mu.Location = new System.Drawing.Point(95, 316);
            this.numericUpDown_mu.Name = "numericUpDown_mu";
            this.numericUpDown_mu.Size = new System.Drawing.Size(77, 20);
            this.numericUpDown_mu.TabIndex = 8;
            this.numericUpDown_mu.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(74, 344);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(13, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "v";
            // 
            // numericUpDown_v
            // 
            this.numericUpDown_v.DecimalPlaces = 1;
            this.numericUpDown_v.Location = new System.Drawing.Point(95, 342);
            this.numericUpDown_v.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_v.Name = "numericUpDown_v";
            this.numericUpDown_v.Size = new System.Drawing.Size(77, 20);
            this.numericUpDown_v.TabIndex = 10;
            this.numericUpDown_v.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
            // 
            // numericUpDown_x
            // 
            this.numericUpDown_x.Location = new System.Drawing.Point(95, 369);
            this.numericUpDown_x.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDown_x.Name = "numericUpDown_x";
            this.numericUpDown_x.Size = new System.Drawing.Size(77, 20);
            this.numericUpDown_x.TabIndex = 12;
            this.numericUpDown_x.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(74, 371);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(12, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "x";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1116, 450);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.numericUpDown_x);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.numericUpDown_v);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.numericUpDown_mu);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.numericUpDown_k);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDown_m);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.buttonStop);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.MainPic);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.MainPic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_m)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_k)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_mu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_v)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_x)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox MainPic;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        public System.Windows.Forms.NumericUpDown numericUpDown_m;
        public System.Windows.Forms.NumericUpDown numericUpDown_k;
        public System.Windows.Forms.NumericUpDown numericUpDown_mu;
        public System.Windows.Forms.NumericUpDown numericUpDown_v;
        private System.Windows.Forms.NumericUpDown numericUpDown_x;
        private System.Windows.Forms.Label label5;
    }
}

