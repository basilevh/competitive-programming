// by 70!

using System;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Problem_D
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathIn = "D-large.in";
            string pathOut = "out.txt";
            var fsIn = new FileStream(pathIn, FileMode.Open);
            var fsOut = new FileStream(pathOut, FileMode.Create);
            using (var reader = new StreamReader(fsIn))
            using (var writer = new StreamWriter(fsOut))
            {
                string line = reader.ReadLine();
                int cases = int.Parse(line);
                for (int cs = 1; cs <= cases; cs++)
                {
                    string[] info = reader.ReadLine().Split(' ');
                    int min = int.Parse(info[0]);
                    int max = int.Parse(info[1]);
                    int mean = int.Parse(info[2]);
                    int med = int.Parse(info[3]);

                    int res = solve(min,max,mean,med);

                    Console.WriteLine("Case #{0}: {1}", cs, res > 0 ? res + "" : "IMPOSSIBLE");
                    writer.WriteLine("Case #{0}: {1}", cs, res > 0 ? res + "" : "IMPOSSIBLE");
                }
            }
        }

        static int solve(int min, int max, int mean, int med)
        {
            if (min > max || mean > max || med > max || mean < min || med < min)
                return -1;

            for (int res = 1; res <= 10*max; res++)
            {
                if (poss(min,max,mean,med,res))
                    return res;
            }
            return -1;
        }

        static bool poss(int min, int max, int mean, int med, int deps)
        {
            if (deps == 1)
            {
                return (min == max && min == mean && min == med);
            }
            if (deps == 2)
            {
                return (min + max == 2*mean && min + max == 2*med);
            }
            if (deps == 3)
            {
                return (med == 3*mean - min - max);
            }
            if (deps == 4)
            {
                return (2*med == 4*mean - min - max);
            }

            int sum = deps * mean - min - max - med;
            int extr = (deps - 3) / 2;
            int meds = (deps - 2) / 2;
            Debug.Assert(extr + meds == deps - 3);
            return (extr * min + meds * med <= sum && sum <= meds * med + extr * max);
        }
    }
}
