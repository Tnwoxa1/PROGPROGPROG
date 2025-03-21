using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ToolBar;


namespace ModelingSystems1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent(); 
            timer1.Enabled = false;
            this.MouseWheel += Form_MouseWheel;

        }
        int _totalDelta = 100;
        void Form_MouseWheel(object sender, MouseEventArgs e)
        {
            if (_totalDelta+ e.Delta / 10 < 100) return;
            _totalDelta = _totalDelta + e.Delta/10;

        }

        Coleb col = new Coleb();
 

        private void MainPic_Paint(object sender, PaintEventArgs e)
        {
            Graphics gr = e.Graphics;
          
            
            float top = 2;
            float bottom = -2;
            float left = -100;
            float right = 100;

            float HeightRectagdle = 0.5f * (top-bottom);
            float WidthRectangle = 0.2f * (right-left);


            float xPadding = (right - left) / 10;
            float yPadding = (top - bottom) / 10;

            float xScale = MainPic.Width / (right + xPadding - (left - xPadding));
            float yScale = MainPic.Height / (top + yPadding - (bottom - yPadding));

            gr.ScaleTransform(xScale, -yScale);
            gr.TranslateTransform(xPadding-left, -(top + yPadding - (bottom - yPadding)) / 2);

            float x = col.GetX();


            LinearGradientBrush brush = new LinearGradientBrush(new PointF(x - WidthRectangle / 2, -HeightRectagdle / 2), 
                                new PointF(x + WidthRectangle / 2, HeightRectagdle / 2), Color.Aqua, Color.Purple);
            Pen pen = new Pen(Color.Black,0.3f);
            Pen pen1 = new Pen(brush, 0.3f);

            gr.FillRectangle(brush, x - WidthRectangle/2, bottom, WidthRectangle, HeightRectagdle);
            gr.DrawLine(pen, new PointF(left,bottom), new PointF(right,bottom));
            gr.DrawLine(pen1, new PointF(0, 0), new PointF(x, 0));


            //gr.DrawRectangle(pen, 0, 0, 100, 2);

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            col.CalcPos();
            MainPic.Invalidate();
            pictureBox1.Invalidate();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            float m = (float)numericUpDown_m.Value;
            float k = (float)numericUpDown_k.Value;
            float mu =(float)numericUpDown_mu.Value;
            float v=(float)numericUpDown_v.Value;
            float x=(float)numericUpDown_x.Value;
            col.Reset(m, k, mu, v, x);
            timer1.Enabled = true;
            numericUpDown_k.Enabled = false;
            numericUpDown_mu.Enabled = false;
            numericUpDown_v.Enabled = false;
            numericUpDown_m.Enabled = false;
            numericUpDown_x.Enabled = false;
            buttonStart.Enabled = false;
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            numericUpDown_k.Enabled = true;
            numericUpDown_mu.Enabled = true;
            numericUpDown_v.Enabled = true;
            numericUpDown_m.Enabled = true;
            numericUpDown_x.Enabled = true;
            buttonStart.Enabled = true;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics gr = e.Graphics;

            Pen pen = new Pen(Color.Black, 1);
            Pen BackGroundPen = new Pen(Color.Gray, 0.01f);
            Pen GraphPen = new Pen(Color.Indigo, _totalDelta/100);
            Brush br= new SolidBrush(Color.Black);
            Font font = new Font(new FontFamily("Arial"), 3);

            float top = _totalDelta;
            float bottom = -_totalDelta;
            float left = -_totalDelta;
            float right = _totalDelta;
            float xPadding = (right - left) / 10;
            float yPadding = (top - bottom) / 10;

            float xScale = pictureBox1.Width / (right + xPadding - (left - xPadding));
            float yScale = pictureBox1.Height / (top + yPadding - (bottom - yPadding));

            float steplenY = (top - bottom) / 10;
            float steplenX = (right - left) / 10;

            gr.ScaleTransform(xScale, -yScale);
            gr.TranslateTransform((right + xPadding - (left-xPadding))/2, -(top + yPadding - (bottom - yPadding)) / 2);

            PointF p1=new PointF(), p2=new PointF();
            PointF []p_strx=new PointF[11];
            PointF[] p_stry = new PointF[11];


            for (int i = 0; i < 11; i++)
            {
                p1.X = left;
                p1.Y = top - i * steplenY;

                p2.X = right;
                p2.Y = top - i * steplenY;

                p_strx[i]=new PointF(0, top - i * steplenY);
                gr.DrawLine(BackGroundPen, p1, p2);
       


                p1.X = right - i * steplenX;
                p1.Y = top;

                p2.X = right - i * steplenX;
                p2.Y = bottom;

                p_stry[i] = new PointF(right - i * steplenX, 0);

                //PointF p_str2 = new PointF(right - i * steplenX, 0);
                gr.DrawLine(BackGroundPen, p1, p2);

            }

           
            

            p1 = new PointF(0, top);
            p2 = new PointF(0, bottom);

            gr.DrawLine(pen, p1, p2);
            p1=new PointF(left,0);
            p2 = new PointF(right, 0);
            gr.DrawLine(pen, p1, p2);

           
            if (col.GetPhas().Count < 1)
                return;

            p1 = col.GetPhas()[0];

            for(int i=1;i<col.GetPhas().Count;i++)
            {
                p2 = col.GetPhas()[i];
                gr.DrawLine(GraphPen, p1, p2);
                p1 = p2;
            }


        }
    }

   
}
