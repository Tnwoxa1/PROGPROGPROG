using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModelingSystems1
{
    internal class Coleb
    {
        private float m;
        private float k;
        private float mu;
        private float v;
        private float x;
        private float speed = 0;
        private float dt = 0.1f;
        private float t=0;
        private int iterator = 0;
        //int F = 40;

        private List<PointF> phas = new List<PointF>();


        public Coleb(float m = 0, float k = 0, float mu = 0, float v = 0, float x= 0) 
        {
            this.m = m;
            this.k = k;
            this.mu = mu;
            this.v = v;
            this.x = x;

        }

        public void Reset(float m, float k, float mu, float v, float x)
        {
            this.m = m;
            this.k = k;
            this.mu = mu;
            this.v = v;
            this.x = x;
            this.iterator = 0;
            this.speed = 0;
            phas.Clear();
        }

        float f(float x)
        {
            return (v - speed) > 0 ? (-k * (x) + mu * m) / m : (-k * (x) - mu * m) / m;
        }

        public void CalcPos()
        {
            float x = this.x;
            float x_ = this.speed;

            float[] kx = new float[4] { 0, 0, 0, 0 };
            t = iterator * dt;

            kx[0] = f(x) * dt;

            kx[1] = f(x + x_ * dt / 2.0f) * dt;

            kx[2] = f(x + x_ * dt / 2.0f + kx[0] * dt / 4.0f) * dt;



            kx[3] = f(x + x_ * dt + kx[1] * dt / 2.0f) * dt;



            this.x = x + x_ * dt + (kx[0] + kx[1] + kx[2]) * dt / 6.0f;
            this.speed = x_ + (kx[0] + 2 * kx[1] + 2 * kx[2] + kx[3]) / 6.0f;

            iterator++;

            PointF point = new PointF(this.x, this.speed);
            phas.Add(point);

            

        }

        public float GetX()
        {
            return (float)this.x;
        }

        public float GetSpeed()
        {
            return (float)this.speed;
        }

        public List<PointF> GetPhas()
        {
            return this.phas;
        }



    }
}
