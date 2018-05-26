// by 70!

using System;
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
                    string encWord = reader.ReadLine();
                    int len = encWord.Length;
                    char[] enc = encWord.ToCharArray();
                    string decWord;

                    if (len == 2)
                        decWord = encWord[1].ToString() + encWord[0];
                    else if (len % 2 == 1)
                        decWord = "AMBIGUOUS";
                    else // len >= 4 and even
                    {
                        char[] dec = new char[len];

                        dec[1] = enc[0];
                        for (int i = 2; i < len; i+=2)
                            dec[i+1] = (char)((enc[i] - dec[i-1] + 26) % 26 + 'A');

                        dec[len-2] = enc[len-1];
                        for (int i = len-3; i >= 0; i-=2)
                            dec[i-1] = (char)((enc[i] - dec[i+1] + 26) % 26 + 'A');

                        decWord = new string(dec);
                    }

                    Console.WriteLine("Case #{0}: {1}", cs, decWord);
                    writer.WriteLine("Case #{0}: {1}", cs, decWord);
                }
            }
        }
    }
}
