// 2019-09-14, BVH

using System;
using System.Collections.Generic;
using System.Linq;

namespace Practice1A
{
    class Program
    {
        private const double TWO_PI = 2.0 * Math.PI;

        static void Main(string[] args)
        {
            const bool debug = false;

            string line;
            while ((line = Console.ReadLine()) != null)
            {
                int n = int.Parse(line);
                if (n > 0)
                {
                    // Input
                    var beacons = new List<double[]>();
                    for (int i = 0; i < n; i++)
                    {
                        beacons.Add(Console.ReadLine().Split(' ').Select(s => double.Parse(s)).ToArray());
                    }

                    // Get convex hull
                    var convex = new List<double[]>();
                    var lower = beacons.OrderBy(b => b[1]).First();
                    var pivot = lower;
                    double last = 0.0;
                    convex.Add(pivot);
                    var next = beacons.OrderBy(b => angle(pivot, b, last)).First();
                    while (!convex.Contains(next))
                    {
                        convex.Add(next);
                        pivot = next;
                        next = beacons.OrderBy(b => angle(pivot, b, last)).First();
                        last = angle(pivot, next, 0.0);
                    }

                    // Calculate area
                    double total = 0.0;
                    for (int i = 1; i < convex.Count - 1; i++)
                    {
                        double x1 = lower[0];
                        double y1 = lower[1];
                        double x2 = convex[i][0];
                        double y2 = convex[i][1];
                        double x3 = convex[i + 1][0];
                        double y3 = convex[i + 1][1];
                        double area = Math.Abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
                        if (debug)
                        {
                            Console.WriteLine(area);
                        }
                        total += area;
                    }

                    if (debug)
                    {
                        foreach (var vert in convex)
                            Console.WriteLine(vert[0] + " " + vert[1] + "   ");
                    }

                    Console.WriteLine(total);
                }
            }
        }

        private static double angle(double[] from, double[] to, double last)
        {
            if (from[0] == to[0] && from[1] == to[1])
                return 1000.0; // put last
            else
            {
                double result = Math.Atan2(to[1] - from[1], to[0] - from[0]);
                result -= last;
                result = (result + 2.0 * TWO_PI) % TWO_PI; // force positive
                return result;
            }
        }
    }
}
