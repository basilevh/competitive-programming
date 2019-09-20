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
                if (n > 0)
                {
                    // Input
                    long[,] money = new long[n, n]; // in [0, 2e3]
                    for (int i = 0; i < n; i++)
                    {
                        long[] row = Console.ReadLine().Split(' ').Select(s => long.Parse(s)).ToArray();
                        for (int j = 0; j < n; j++)
                            money[i, j] = row[j];
                    }
                    int m = int.Parse(Console.ReadLine()); // in [0, 5e3]

                    // Solve
                    if (m == 0)
                    {
                        Console.WriteLine("0 0");
                        continue;
                    }
                    // find max & min next values
                    long[] max_next = new long[n];
                    long[] min_next = new long[n];
                    for (int i = 0; i < n; i++)
                    {
                        long cur_max = -1;
                        long cur_min = long.MaxValue;
                        for (int j = 0; j < n; j++)
                        {
                            if (money[i, j] > cur_max)
                                cur_max = money[i, j];
                            if (money[i, j] < cur_min)
                                cur_min = money[i, j];
                        }
                        max_next[i] = cur_max;
                        min_next[i] = cur_min;
                    }
                    // start from last cycle and work backwards
                    long[,] dp_max = new long[n, m]; // [i, k] -> potentially earn up to this value when we are at room i at turn k
                    long[,] dp_min = new long[n, m]; // [i, k] -> potentially as little as this value when we are at room i at turn k
                    for (int i = 0; i < n; i++)
                    {
                        dp_max[i, m - 1] = max_next[i];
                        dp_min[i, m - 1] = min_next[i];
                    }
                    for (int k = m - 2; k >= 0; k--)
                    {
                        for (int i = 0; i < n; i++) // current room -> [i, k]
                        {
                            dp_max[i, k] = long.MinValue;
                            dp_min[i, k] = long.MaxValue;
                            for (int j = 0; j < n; j++) // next room -> [j, k + 1]
                            {
                                dp_max[i, k] = Math.Max(money[i, j] + dp_max[j, k + 1], dp_max[i, k]);
                                dp_min[i, k] = Math.Min(money[i, j] + dp_min[j, k + 1], dp_min[i, k]);
                            }
                        }
                    }

                    // DEBUG
                    if (false)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            for (int k = 0; k < m; k++)
                            {
                                Console.Write(dp_max[i, k] + " ");
                            }
                            Console.WriteLine();
                        }
                        for (int i = 0; i < n; i++)
                        {
                            for (int k = 0; k < m; k++)
                            {
                                Console.Write(dp_min[i, k] + " ");
                            }
                            Console.WriteLine();
                        }
                    }

                    Console.WriteLine(dp_max[0, 0] + " " + dp_min[0, 0]);
                }
            }
        }
    }
}
