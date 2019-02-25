// by 70!

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Problem_C
{
    class Program
    {
        static void Main(string[] args)
        {
            string pathIn = "C-large.in";
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
                    int N = int.Parse(info[0]);
                    int M = int.Parse(info[1]);
                    int P = int.Parse(info[2]);
                    int[] U = new int[M];
                    int[] V = new int[M];
                    int[] D = new int[M];
                    for (int i = 0; i < M; i++)
                    {
                        info = reader.ReadLine().Split(' ');
                        U[i] = int.Parse(info[0]);
                        V[i] = int.Parse(info[1]);
                        D[i] = int.Parse(info[2]);
                    }

                    // Create graph
                    int[,] graph = new int[N, N];
                    for (int i = 0; i < M; i++)
                        graph[U[i] - 1, V[i] - 1] = graph[V[i] - 1, U[i] - 1] = D[i];

                    // Fill in all total times
                    int[,] times = new int[N, N];
                    for (int i = 0; i < N; i++)
                    {
                        int[] here = Dijkstra(graph, i, N); // time N^2
                        for (int j = 0; j < N; j++)
                            times[i, j] = here[j];
                    }

                    /*print2D(graph);
                    print2D(times);*/

                    // Verify
                    for (int i = 0; i < N; i++)
                        for (int j = 0; j < N; j++)
                        {
                            Debug.Assert(times[i, j] == times[j, i]);
                            // NOT always:
                            /*if (graph[i, j] != 0)
                                Debug.Assert(graph[i, j] == times[i, j]);*/
                        }

                    // Setup
                    double[] p1 = new double[N]; // prob I'm at location i
                    double[] p2 = new double[N]; // prob codejamon is at location i (avg, not conditional on p1!)
                    p1[0] = 1.0;
                    for (int i = 1; i < N; i++)
                        p1[i] = 0.0;
                    p2[0] = 0.0;
                    for (int i = 1; i < N; i++)
                        p2[i] = 1.0 / (N - 1.0);

                    double res = 0.0;

                    double resSST = double.NaN;
                    int sst = 500;
                    
                    // Loop
                    for (int i = 0; i < P; i++)
                    {
                        if (i == sst)
                            resSST = res;
                        else if (i == 2 * sst)
                        {
                            Console.WriteLine("Extrapolating...");
                            Console.WriteLine(string.Join(", ", p1));
                            Console.WriteLine(string.Join(", ", p2));
                            res += (double)(P - 2.0 * sst) / sst * (res - resSST); // iterations 500-1000 are assumed to be steady-state
                            break;
                        }

                        /*Console.WriteLine(string.Join(", ", p1));
                        Console.WriteLine(string.Join(", ", p2));
                        Console.WriteLine();*/

                        for (int j = 0; j < N; j++)
                            for (int k = 0; k < N; k++)
                            {
                                // Do NOT use p2 here as it's the average of all p2|p1, while we should actually use p2|p1 to start with
                                // res += p1[j] * p2[k] * times[j, k];
                                res += p1[j] * times[j, k] / (N - 1.0);
                            }

                        // Update probs
                        p1 = p2; // do use p2 here
                        double[] newP2 = new double[N];
                        for (int j = 0; j < N; j++)
                        {
                            newP2[j] = 0.0;
                            for (int k = 0; k < N; k++)
                                if (j != k)
                                    newP2[j] += p2[k] / (N - 1.0);
                        }
                        p2 = newP2;
                    }

                    Debug.Assert(!double.IsNaN(res));

                    Console.WriteLine("Case #{0}: {1}", cs, res);
                    writer.WriteLine("Case #{0}: {1}", cs, res);
                }
            }
        }

        private static void print2D(int[,] arr)
        {
            int rowLength = arr.GetLength(0);
            int colLength = arr.GetLength(1);

            for (int i = 0; i < rowLength; i++)
            {
                for (int j = 0; j < colLength; j++)
                {
                    Console.Write(string.Format("{0} ", arr[i, j]));
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        // DISCLAIMER
        // The code below (for Dijkstra) was copied (and modified) from:
        // https://www.programmingalgorithms.com/algorithm/dijkstra%27s-algorithm
        // This is not with the intent to break any rules, but to save time by not having to write "trivial" code.

        private static int MinimumDistance(int[] distance, bool[] shortestPathTreeSet, int verticesCount)
        {
            int min = int.MaxValue;
            int minIndex = 0;

            for (int v = 0; v < verticesCount; ++v)
            {
                if (shortestPathTreeSet[v] == false && distance[v] <= min)
                {
                    min = distance[v];
                    minIndex = v;
                }
            }

            return minIndex;
        }

        private static int[] Dijkstra(int[,] graph, int source, int verticesCount)
        {
            int[] distance = new int[verticesCount];
            bool[] shortestPathTreeSet = new bool[verticesCount];

            for (int i = 0; i < verticesCount; ++i)
            {
                distance[i] = int.MaxValue;
                shortestPathTreeSet[i] = false;
            }

            distance[source] = 0;

            for (int count = 0; count < verticesCount - 1; ++count)
            {
                int u = MinimumDistance(distance, shortestPathTreeSet, verticesCount);
                shortestPathTreeSet[u] = true;

                for (int v = 0; v < verticesCount; ++v)
                    if (!shortestPathTreeSet[v] && Convert.ToBoolean(graph[u, v]) && distance[u] != int.MaxValue && distance[u] + graph[u, v] < distance[v])
                        distance[v] = distance[u] + graph[u, v];
            }

            return distance; // array of times to every other node
        }
    }
}
