using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication1
{
    struct MyVertex
    {
        public double x, y, z, n1, n2, n3;
    }

    struct MyPolygon
    {
        public LinkedList<MyVertex> m_verList;
        public MyPolygon(int y)
        {
            m_verList = new LinkedList<MyVertex>();
        }
    }


    public partial class Form1 : Form
    {
        LinkedList<MyPolygon>  m_myPolygonList = new LinkedList<MyPolygon>();

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(m_openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                m_fileNameTextbox.Text = m_openFileDialog1.FileName;
            }

        }
        private void writeOutputFile()
        {
            string fileName = m_fileNameTextbox.Text+ ".itd";
            System.IO.File.Delete(fileName);
            System.IO.File.Create(fileName).Close();
	//[ptexture \"door3.png\"]
            string fileContent = "[OBJECT MyObj  \n";

            foreach(MyPolygon p in m_myPolygonList){
                fileContent += "\t[POLYGON   [color 4] [PLANE 0 -1 0 0.5] "+p.m_verList.Count.ToString()+"\n";
                foreach (MyVertex v in p.m_verList)
                {
                    fileContent += "\t   [[rgb \"0,0,255\"]  [NORMAL ";
                    fileContent += v.n1.ToString() + " ";
                    fileContent += v.n2.ToString() + " ";
                    fileContent += v.n3.ToString() + "] ";
                    fileContent += v.x.ToString() + " ";
                    fileContent += v.y.ToString() + " ";
                    fileContent += v.z.ToString() +"]\n";
                }
                fileContent += "\t]\n";
            }
            fileContent += "]\n";               


            StreamWriter sw = new StreamWriter(fileName);
            sw.Write(fileContent);
            sw.Close();

            
        }
        private void readInputFile(){
             LinkedList<MyVertex> myVertexList = new LinkedList<MyVertex>();
            LinkedList<MyVertex> myNormalList = new LinkedList<MyVertex>();
            
            StreamReader sr = new StreamReader(m_fileNameTextbox.Text);
            while (sr.Peek() >= 0)
            {
                string sLine = sr.ReadLine();
                sLine = sLine.Replace("  ", " ");
                sLine = sLine.Replace("//", "/");
                string[] list = sLine.Split(' ');
                if (list[0] == "v"){
                    MyVertex v = new MyVertex();
                    v.x = Double.Parse(list[1]);
                    v.y = Double.Parse(list[2]);
                    v.z = Double.Parse(list[3]);
                    myVertexList.AddLast(v);
                }
                else if (list[0] == "vn")
                {
                    MyVertex n = new MyVertex();
                    n.x = Double.Parse(list[1]);
                    n.y = Double.Parse(list[2]);
                    n.z = Double.Parse(list[3]);
                   myNormalList.AddLast(n);
                }
                else if (list[0] == "f")
                {
                    try
                    {
                        MyPolygon p = new MyPolygon(0);
                        for (int i = 1; i < list.Length; i++ )
                        {
                            string f = list[i].Split('/')[0];

                            if (f != "")
                            {
                                MyVertex v = myVertexList.ElementAt(Int32.Parse(f) - 1);
                                
                                    string vn = list[i].Split('/')[2];
                                    MyVertex n = myNormalList.ElementAt(Int32.Parse(vn) -1);
                                    v.n1 = n.x;
                                    v.n2 = n.y;
                                    v.n3 = n.z;
                               
                                p.m_verList.AddLast(v);

                            }
                        }
                            m_myPolygonList.AddLast(p);
                    }
                    catch {MessageBox.Show("error"); 
                    }
                }
            }
            sr.Close();
        }
      
        private void button2_Click(object sender, EventArgs e)
        {
            readInputFile();
            writeOutputFile();
        }
    }
}
