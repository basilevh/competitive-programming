// by 70!

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Problem_D
{
    class Program
    {
        static void Main(string[] args)
        {
            const int maxN = 10000;
            var dict = createDict(maxN);

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
                    int N = int.Parse(reader.ReadLine());

                    int res = dict[N];

                    Console.WriteLine("Case #{0}: {1}", cs, res);
                    writer.WriteLine("Case #{0}: {1}", cs, res);
                }
            }
        }

        private static int squaresNeeded(int N, Dictionary<int, int> solved)
        {
            double sq = Math.Sqrt(N);
            if (sq % 1.0 == 0.0)
                return 1;

            int res = 10000;
            for (int L = (int)Math.Floor(sq); L >= 1; L--)
            {
                int rem = N - L * L;
                int curRes;

                if (solved.ContainsKey(rem))
                    curRes = 1 + solved[rem];
                else
                    curRes = 1 + squaresNeeded(rem, solved);

                if (curRes < res)
                    res = curRes;
            }

            solved[N] = res;
            return res;
        }

        private static Dictionary<int, int> createDict(int maxN)
        {
            int maxL = (int)Math.Ceiling(Math.Sqrt(maxN)); // 10^2
            var res = new Dictionary<int, int>();
            res[1] = 1;
            for (int N = 1; N <= maxN; N++)
                if (!res.ContainsKey(N))
                    res[N] = squaresNeeded(N, res);
            return res;

            // incomplete and slow solution:
            /*
            for (N = 1; N <= maxN; N++)
                res[N] = maxN;

            // 10^2
            for (int a = 1; a <= maxL; a++)
            {
                N = a * a;
                if (N <= maxN)
                    res[N] = 1;
            }

            // 10^4
            for (int a = 1; a <= maxL; a++)
                for (int b = 1; b <= a; b++)
                {
                    N = a * a + b * b;
                    if (N <= maxN)
                        res[N] = Math.Min(2, res[N]);
                }

            // 10^6
            for (int a = 1; a <= maxL; a++)
                for (int b = 1; b <= a; b++)
                    for (int c = 1; c <= b; c++)
                    {
                        N = a * a + b * b + c * c;
                        if (N <= maxN)
                            res[N] = Math.Min(3, res[N]);
                    }

            // 10^8
            for (int a = 1; a <= maxL; a++)
                for (int b = 1; b <= a; b++)
                    for (int c = 1; c <= b; c++)
                        for (int d = 1; d <= c; d++)
                        {
                            N = a * a + b * b + c * c + d * d;
                            if (N <= maxN)
                                res[N] = Math.Min(4, res[N]);
                        }

            return res;
            */
        }
    }
}
