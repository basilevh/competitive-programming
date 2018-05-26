// by 70!

using System;
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
                    int N = int.Parse(reader.ReadLine());
                    bool[,] hasX = new bool[N,N]; // row,col
                    int[] inRow = new int[N]; // x count
                    int[] inCol = new int[N];
                    bool res = true;

                    for (int i = 0; i < N; i++)
                    {
                        string row = reader.ReadLine();
                        for (int j = 0; j < N; j++)
                        {
                            hasX[i,j] = (row[j] == 'X');
                            if (hasX[i,j])
                                inRow[i]++;
                        }
                    }

                    for (int j = 0; j < N; j++)
                    {
                        for (int i = 0; i < N; i++)
                        {
                            if (hasX[i,j])
                                inCol[j]++;
                        }
                    }

                    if (inRow.Count(i => i == 1) == 1 && inRow.Count(i => i == 2) == N-1
                    && inCol.Count(i => i == 1) == 1 && inCol.Count(i => i == 2) == N-1)
                    {
                        for (int i = 0; i < N && res; i++)
                        {
                            for (int j = 0; j < N && res; j++)
                            {
                                for (int k = 0; k < N && res; k++)
                                {
                                    if (k == i)
                                        continue;
                                    if (hasX[i,j] && hasX[k,j])
                                    {
                                        for (int l = 0; l < N && res; l++)
                                        {
                                            if (l == j)
                                                continue;
                                            if (hasX[i,l])
                                                res = hasX[k,l];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                        res = false;

                    Console.WriteLine("Case #{0}: {1}", cs, res ? "POSSIBLE": "IMPOSSIBLE");
                    writer.WriteLine("Case #{0}: {1}", cs, res ? "POSSIBLE": "IMPOSSIBLE");
                }
            }
        }
    }
}
