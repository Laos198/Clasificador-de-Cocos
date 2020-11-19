using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Seleccionador_Cocos
{
    public partial class Form1 : Form
    {
        char separador = ',';
        string sms;

        int n = 0, n_C = 0, n_G = 0;

        List<Cocos> Lista_Cocos =new List<Cocos> () ;
        Cocos coco = new Cocos();

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Enabled = true;
            button2.Enabled = false;

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Close();
                button2.Enabled = false;
                button1.Enabled = true;

            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                serialPort1.Close();
            }
            catch (Exception error)
            {

                MessageBox.Show(error.Message);
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            sms = serialPort1.ReadLine();
            this.BeginInvoke(new EventHandler(ProcessData));

        }

        private void ProcessData(object sender, EventArgs e)
        {
            if (sms != null)
            {
                string[] sms_s = sms.Split(separador);
                coco.R = Convert.ToInt32(sms_s[0]);
                coco.G = Convert.ToInt32(sms_s[1]);
                coco.B = Convert.ToInt32(sms_s[2]);
                coco.Tamaño = Convert.ToInt32(sms_s[3]);
                coco.C = sms_s[4];
                CheckForIllegalCrossThreadCalls = false;
                label_Tamaño.Text = sms_s[3];
                if (coco.C == "C")
                {
                    label_Color.Text = "Canelo";
                    n_C++;
                    labelCC.Text = Convert.ToString(n_C);
                }
                else if (coco.C.Equals("G") == true)
                {
                    label_Color.Text = "Güero";
                    n_G++;
                    labelCG.Text = Convert.ToString(n_G);
                }
                n++;
                Lista_Cocos.Add(coco);
                dataGridView1.DataSource = null;



            }
            CheckForIllegalCrossThreadCalls = false;
            labelContador.Text = Convert.ToString(n);
            dataGridView1.DataSource = Lista_Cocos;

        }

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = "COM3";
                serialPort1.BaudRate = 9600;
                serialPort1.Open();

                button1.Enabled = false;
                button2.Enabled = true; 
            }
            catch(Exception error)
            {
                MessageBox.Show(error.Message); 
            }
        }
    }
}
