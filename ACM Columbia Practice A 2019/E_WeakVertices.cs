// 2019-09-14, BVH

using System;
using System.Collections.Generic;
using System.Linq;

namespace Practice1A
{
    class Program
    {
        static void Main(string[] args)
        {
            string line;
            while ((line = Console.ReadLine()) != null)
            {
                int n = int.Parse(line);
                if (n >= 0)
                {
                    bool[,] adjadency = new bool[n, n];
                    for (int i = 0; i < n; i++)
                    {
                        int[] adj = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();
                        for (int j = 0; j < n; j++)
                        {
                            adjadency[i, j] = (adj[j] == 1);
                        }
                    }

                    var weak = new List<int>();
                    for (int i = 0; i < n; i++)
                    {
                        bool cur_weak = true;
                        for (int j1 = 0; j1 < n; j1++)
                            for (int j2 = 0; j2 < n; j2++)
                                if (i != j1 && i != j2 && adjadency[i, j1] && adjadency[i, j2] && adjadency[j1, j2])
                                { 
                                    cur_weak = false;
                                }
                        if (cur_weak)
                            weak.Add(i);
                    }

                    Console.WriteLine(string.Join(" ", weak));
                }
            }
        }
    }
}
