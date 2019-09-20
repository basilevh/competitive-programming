// 2019-09-14, BVH

using System;
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
                int count = int.Parse(line);
                if (count > 0)
                {
                    Enumerable.Range(0, count)
                        .Select(i => Console.ReadLine())
                        .OrderBy(s => s.Substring(0, 2), StringComparer.Ordinal)
                        .ToList()
                        .ForEach(s => Console.WriteLine(s));
                    Console.WriteLine();
                }
            }
        }
    }
}
