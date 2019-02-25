// by 70!

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Problem_A
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathIn = "A-large.in";
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
                    int E = int.Parse(reader.ReadLine());
                    List<int> A = reader.ReadLine().Split(' ').Select(s => int.Parse(s)).ToList(); // permutation of 1:N
                    System.Diagnostics.Debug.Assert(E == A.Count);

                    string res;
                    if (IsOnlyWorstPivot(A))
                        res = "YES";
                    else
                        res = "NO";

                    Console.WriteLine("Case #{0}: {1}", cs, res);
                    writer.WriteLine("Case #{0}: {1}", cs, res);
                }
            }
        }

        private static bool IsOnlyWorstPivot(List<int> A)
        {
            if (A.Count <= 1)
                return true;

            int mid = (int)Math.Round(Math.Floor((A.Count - 1.0) / 2.0));
            int P = A[mid];
            if (P == A.Max() || P == A.Min())
            {
                A.RemoveAt(mid);
                return IsOnlyWorstPivot(A); // recursive call not necessary, but clearer
            }
            return false;
        }
    }
}
