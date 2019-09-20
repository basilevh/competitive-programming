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
                    int[] bits = Enumerable.Range(0, 32).Select(i => -1).ToArray();
                    for (int i = 0; i < count; i++)
                    {
                        string inst = Console.ReadLine();
                        string[] split = inst.Split(' ');
                        string opcode = split[0];
                        var dst = int.Parse(split[1]);
                        var arg = split.Length >= 3 ? int.Parse(split[2]) : -1;
                        switch(opcode)
                        {
                            case "CLEAR":
                                bits[dst] = 0;
                                break;
                            case "SET":
                                bits[dst] = 1;
                                break;
                            case "OR":
                                if (bits[arg] == 1)
                                    bits[dst] = 1;
                                if (bits[dst] == 0 && bits[arg] == -1)
                                    bits[dst] = -1;
                                break;
                            case "AND":
                                if (bits[arg] == 0)
                                    bits[dst] = 0;
                                if (bits[dst] == 1 && bits[arg] == -1)
                                    bits[dst] = -1;
                                break;
                        }
                    }
                    for (int i = 31; i >= 0; i--)
                        Console.Write(bits[i] != -1 ? bits[i].ToString() : "?");
                    Console.WriteLine();
                }
            }
        }
    }
}
