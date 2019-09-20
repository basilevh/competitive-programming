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
                string[] split = line.Split(' ');
                int n = int.Parse(split[0]);
                if (n > 0)
                {
                    long[] input = split.Skip(1).Select(s => long.Parse(s)).ToArray();

                    // i, j represents best subsequence of length j+1 after handling input number i
                    // we store the value representing the last number in the subsequence
                    // the preceding number is on the upperleft (?)
                    long[,] dp = new long[n, n];
                    int[,] prev = new int[n, n]; // 0 = root, 1 = up (copy), 2 = upperleft (continue)
                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                        {
                            dp[i, j] = long.MaxValue;
                            prev[i, j] = 0;
                        }
                    int longest = 1;

                    dp[0, 0] = input[0];
                    for (int i = 1; i < n; i++) // loop over input (vertical)
                    {
                        for (int j = 0; j < n; j++) // loop over subsequence length (horizontal)
                        {
                            if (j == 0 && input[i] < dp[i - 1, j])
                            {
                                dp[i, j] = input[i]; // better root
                                prev[i, j] = 0;
                            }
                            else if (j > 0 && dp[i - 1, j - 1] < input[i] && input[i] < dp[i - 1, j])
                            {
                                dp[i, j] = input[i]; // better path
                                longest = Math.Max(j + 1, longest);
                                prev[i, j] = 2;
                            }
                            else
                            {
                                dp[i, j] = dp[i - 1, j]; // copy
                                prev[i, j] = 1;
                            }
                        }
                    }

                    // DEBUG
                    if (false)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            for (int j = 0; j < n; j++)
                                if (dp[i, j] < long.MaxValue)
                                    Console.Write(dp[i, j] + " ");
                            Console.WriteLine();
                        }
                        for (int i = 0; i < n; i++)
                        {
                            for (int j = 0; j < n; j++)
                                Console.Write(prev[i, j] + " ");
                            Console.WriteLine();
                        }
                    }

                    // solution = diagonal (we can't use too recent values)
                    int sol_i = n - 1;
                    int sol_j = longest - 1;
                    int sol_prev = prev[sol_i, sol_j];
                    var solution = new List<long>();
                    while (sol_prev > 0)
                    {
                        if (sol_prev == 2)
                            solution.Add(dp[sol_i, sol_j]);
                        sol_i--;
                        if (sol_prev == 2)
                            sol_j--;
                        sol_prev = prev[sol_i, sol_j];
                    }
                    solution.Add(dp[sol_i, sol_j]);
                    solution.Reverse();
                    Console.WriteLine(solution.Count + " " + string.Join(" ", solution));
                }
            }
        }
    }
}
