// by 70!

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Problem_B
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathIn = "B-large.in";
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
                    int E = int.Parse(info[0]);
                    int H = 0;
                    int N = int.Parse(info[1]);
                    List<int> S = reader.ReadLine().Split(' ').Select(s => int.Parse(s)).ToList(); // we can delay any time so queue is not necessary
                    Debug.Assert(N == S.Count);

                    List<int> posHon = new List<int>(); // honors at possible endpoints (when we start trucing everyone)

                    bool retry = true;

                    while (retry)
                    {
                        while (S.Count > 0 && S.Min() < E)
                        {
                            // Dance worst rival
                            E -= S.Min();
                            H++;
                            S.Remove(S.Min());
                        }

                        // Can't dance anymore
                        // Add possible endpoint
                        posHon.Add(H);

                        if (S.Count > 0 && H > 0)
                        {
                            // Recruit best rival
                            E += S.Max();
                            H--;
                            S.Remove(S.Max());
                        }

                        retry = (S.Count > 0 && S.Min() < E);
                    }

                    int res = posHon.Max();

                    Console.WriteLine("Case #{0}: {1}", cs, res);
                    Console.WriteLine(string.Join(", ", posHon));
                    writer.WriteLine("Case #{0}: {1}", cs, res);
                }
            }
        }
    }
}
