using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Media;
using LiveCharts.WinForms;
namespace WindowsFormsApp1
{
    public
    partial class Form1 : Form
    {
        const int maxN = 100 + 7;
        int[] color = new int[maxN];
        int[] colorFinal = new int[maxN];
        static int[] deg = new int[maxN];
        static int[] arrSorted = new int[maxN];
        static int n, m;
        static int maxNum = 0;
        static int MIN = 100;
        static int[,] g = new int[maxN, maxN];
        int checkNumberColor()
        {
            bool[] rt = new bool[maxNum + 1];
            for (int i = 0; i <= maxNum; i++) rt[i] = false;
            for (int i = 1; i <= n; i++)
            {
                if(color[i] != -1) rt[color[i]] = true;
            }
            int ans = 0;
            for (int i = 0; i <= maxNum; i++)
            {
                if (rt[i] == true) ans++;
            }
            return ans;
        }

        int change = 0;
        void graphColoring(int k)
        {
            int nF = 0;
            int s = arrSorted[k];
            if (k == n + 1)
            {
                int ch = checkNumberColor();
                if (ch < MIN)
                {
                    MIN = ch;
                    maxNum = MIN - 1;
                    for (int i = 1; i <= n; i++) colorFinal[i] = color[i];
                }
                return;
            }
            for (int i = 0; i <= maxNum; i++)
            {
                if (change != 0)
                {
                    if (g[s, change] == 1)
                    {
                        change = 0;
                    }
                    else
                    {
                        return;
                    }
                }
                color[s] = i;
                bool isok = true;
                bool isokmin = checkNumberColor() < MIN;
                for (int u = 1; u <= n; u++)
                {
                    if (g[s, u] == 1 && color[u] == color[s])
                    {
                        isok = false;
                        break;
                    }
                }
                if (isok == false) { nF++; }
                if (isok == true && isokmin == true)
                {
                    graphColoring(k + 1);
                }
            }
            if (nF == maxNum + 1)
            {
                change = s;
            }
            color[s] = -1;
        }
        class compare : IComparer<int>
        {
            public int Compare(int x, int y)
            {
                return deg[y].CompareTo(deg[x]);
            }

        }
        void inp()
        {
            string[] a = File.ReadAllLines("input.txt");
            string[] mid = a[0].Split(' ');
            n = Convert.ToInt32(mid[0]);
            m = Convert.ToInt32(mid[1]);
            for (int i = 1; i <= m; i++)
            {
                mid = a[i].Split(' ');
                int u = Convert.ToInt32(mid[0]);
                int v = Convert.ToInt32(mid[1]);
                g[u, v] = 1;
                g[v, u] = 1;
                deg[u]++;
                deg[v]++;
            }
            for(int i = 1; i <= n; i++)
            {
                arrSorted[i] = i;
                color[i] = -1;
            }
            compare cmp = new compare();
            Array.Sort(arrSorted, 1, n + 1, cmp);
            for (int i = 1; i <= n; i++)
            {
                if(maxNum < deg[i] + 1) maxNum = deg[i] + 1;
            }
            graphColoring(1);
        }
        public
         Form1()
        { InitializeComponent(); }

        private
         void Form1_Load(object sender, EventArgs e)
        {
            GeoMap geoMap = new GeoMap();
            Random random = new Random();
            // gives value
            Dictionary<string, double> values = new Dictionary<string, double>();

            // creat province
            inp();
            
            for (int i = 1; i <= n; i++)
            {
                String x = i.ToString();
                values[x] = colorFinal[i];
            }

            // change default color
            // geoMap.DefaultLandFill = new SolidColorBrush(Colors.Transparent);

            // change heat color
            GradientStopCollection collection = new GradientStopCollection();
            collection.Add(new GradientStop()
            {
                Color = System.Windows.Media.Color.FromArgb(64, 64, 64, 0),
                Offset = 0
            });
            collection.Add(new GradientStop()
            {
                Color = System.Windows.Media.Color.FromArgb(128, 128, 128, 0),
                Offset = 0.5
            });
            collection.Add(new GradientStop()
            {
                Color = System.Windows.Media.Color.FromArgb(255, 255, 255, 0),
                Offset = 1
            });

            geoMap.GradientStopCollection = collection;
            // geoMap.map
            // change boundary color
            // geoMap.LandStroke = new SolidColorBrush(Colors.Black);

            geoMap.HeatMap = values;
            geoMap.Hoverable = true;
            geoMap.Source = $"{Application.StartupPath}//china.xml" ;
            this.Controls.Add(geoMap);
            geoMap.Dock = DockStyle.Fill;
        }
    }
}
