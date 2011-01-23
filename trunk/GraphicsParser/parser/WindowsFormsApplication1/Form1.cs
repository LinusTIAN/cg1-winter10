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

    struct MyObj
    {
        public LinkedList<MyPolygon> m_PolyList;
        public string m_name;
        public int c1, c2, c3;
        public MyObj(int y)
        {
            m_name = "";
            m_PolyList = new LinkedList<MyPolygon>();
            c1 = c2 = c3 = 0;
        }
    }


    public partial class Form1 : Form
    {
        LinkedList<MyObj> m_myObjList = new LinkedList<MyObj>();

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
            StreamWriter sw = new StreamWriter(fileName);

            string fileContent = "[OBJECT MyObj  \n";           

            foreach (MyObj o in m_myObjList)
            {
                if (0 < o.m_PolyList.Count)
                {
                    fileContent += "[OBJECT [rgb \""+o.c1+","+o.c2+","+o.c3+"\"] "+o.m_name+" \n ";
                    foreach (MyPolygon p in o.m_PolyList)
                    {
                        fileContent += "\t[POLYGON  [PLANE 0 -1 0 0.5] " + p.m_verList.Count.ToString() + "\n";
                        foreach (MyVertex v in p.m_verList)
                        {
                            fileContent += "\t   [ [NORMAL ";
                            fileContent += v.n1.ToString() + " ";
                            fileContent += v.n2.ToString() + " ";
                            fileContent += v.n3.ToString() + "] ";
                            fileContent += v.x.ToString() + " ";
                            fileContent += v.y.ToString() + " ";
                            fileContent += v.z.ToString() + "]\n";
                            sw.Write(fileContent);
                            fileContent = "";
                        }
                        fileContent += "\t]\n";
                    }
                    fileContent += " ] \n";  
                }
            }
            fileContent += " ] \n";               


            sw.Write(fileContent);
            sw.Close();

            
        }
        private void readInputFile(){
            
            StreamReader sr = new StreamReader(m_fileNameTextbox.Text);
            MyObj obj = new MyObj(1);
            LinkedList<MyVertex> myVertexList = new LinkedList<MyVertex>();
            LinkedList<MyVertex> myNormalList = new LinkedList<MyVertex>();
            while (sr.Peek() >= 0)
            {
                string sLine = sr.ReadLine();
                if (sLine.StartsWith("# object "))
                {
                    m_myObjList.AddLast(obj);
                    obj = new MyObj(1);
                    try
                    {
                        obj.m_name = sLine.Split(' ')[2];
                        string[] colors = obj.m_name.Split('_');
                        obj.c1 = Int32.Parse(colors[1]);
                        obj.c2 = Int32.Parse(colors[2]);
                        obj.c3 = Int32.Parse(colors[3]);
                    }
                    catch
                    {
                        MessageBox.Show("Error!! name doesn't contain color");
                    }
                }
                readObj(obj,sLine, myVertexList, myNormalList);
            }
            m_myObjList.AddLast(obj);
            sr.Close();
        }
        private void readObj(MyObj obj, string sLine, LinkedList<MyVertex> myVertexList, LinkedList<MyVertex> myNormalList)
        {
                sLine = sLine.Replace("  ", " ");
                sLine = sLine.Replace("//", "/");
                string[] list = sLine.Split(' ');
                if (0 == list.Length)
                    return;
                if (list[0] == "v")
                {
                    MyVertex v = new MyVertex();
                    v.x = Double.Parse(list[1]);
                    v.y = Double.Parse(list[2]);
                    v.z = Double.Parse(list[3]);
                    myVertexList.AddLast(v);
                }
                else if (list[0] == "vn")
                {
                    try
                    {
                        MyVertex n = new MyVertex();
                        n.x = Double.Parse(list[1]);
                        n.y = Double.Parse(list[2]);
                        n.z = Double.Parse(list[3]);
                        myNormalList.AddLast(n);
                    }
                    catch
                    {
                        MessageBox.Show("MyVertex error " + myNormalList.Count);
                    }
                }
                else if (list[0] == "f")
                {
                    try
                    {
                        MyPolygon p = new MyPolygon(0);
                        for (int i = 1; i < list.Length; i++)
                        {
                            string f = list[i].Split('/')[0];

                            if (f != "")
                            {
                                MyVertex v = myVertexList.ElementAt(Int32.Parse(f) - 1);

                                string vn = list[i].Split('/')[2];
                                MyVertex n = myNormalList.ElementAt(Int32.Parse(vn) - 1);
                                v.n1 = n.x;
                                v.n2 = n.y;
                                v.n3 = n.z;

                                p.m_verList.AddLast(v);

                            }
                        }
                        obj.m_PolyList.AddLast(p);
                    }
                    catch
                    {
                        MessageBox.Show("error in readObj");
                    }
                }
        }
      
        private void button2_Click(object sender, EventArgs e)
        {
            readInputFile();
            writeOutputFile();
        }
    }
}
