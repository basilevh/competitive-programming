// by 70!

using System;
using System.Collections;
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
                    int Q = int.Parse(info[1]);
                    bool[][] answers = new bool[N][];
                    bool[] myAns;
                    int[] scores;
                    for (int i = 0; i < N; i++)
                        answers[i] = reader.ReadLine().Select(c => c == 'T').ToArray();
                    myAns = reader.ReadLine().Select(c => c == 'T').ToArray();
                    scores = reader.ReadLine().Split(' ').Select(s => int.Parse(s)).ToArray();

                    int res = 0;
                    if (N == 1)
                    {
                        res = solveOne(Q, answers[0], myAns, scores[0]);
                    }
                    else // N == 2
                    {
                        bool[] friendAns;
                        int score;
                        int best;
                        best = (scores[0] > scores[1] ? 0 : 1);
                        friendAns = answers[best];
                        score = scores[best];
                        if (scores[1-best] != 0)
                            // compare with best friend
                            res = solveOne(Q, friendAns, myAns, score);
                        else
                            // difference from worst
                            res = solveOne(Q, answers[1-best], myAns, 0);
                    }

                    Debug.Assert(0 <= res && res <= Q);
                    Console.WriteLine("Case #{0}: {1}", cs, res);
                    writer.WriteLine("Case #{0}: {1}", cs, res);
                }
            }
        }

        static int solveOne(int Q, bool[] friendAns, bool[] myAns, int score)
        {
            int res = score;
            bool reachedMax = (res == Q);
            for (int i = 0; i < Q; i++)
                if (friendAns[i] != myAns[i])
                {
                    if (!reachedMax)
                    {
                        res++;
                        reachedMax = (res == Q);
                    }
                    else
                        res--;
                }
            return res;
        }
    }
}
