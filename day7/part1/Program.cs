using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

public class Part1
{
    const int limit = 100_000;

    class Node
    {
        public string name_;
        public int size_;
        public Node previous_;
        public List<Node> directories_;

        public Node(string name, int size, Node previous, List<Node> directories)
        {
            name_ = name;
            size_ = size;
            previous_ = previous;
            directories_ = directories;
        }
    }

    static Node ReadFile(string path)
    {
        using (var reader = new StreamReader(path))
        {
            var contents = reader.ReadToEnd().Split("\n");
            var directory = new Node("/", 0, null, new List<Node>());
            var current = directory;

            foreach (var line in contents.Skip(1))
            {
                var input = line.Split(' ');

                switch (input[0])
                {
                    case "$":
                    {
                        if (input[1] == "cd")
                        {
                            if (input[2] == "..")
                            {
                                current = current.previous_;
                            }
                            else
                            {
                                current = current.directories_.Find(dir => dir.name_ == input[2]);
                            }
                        }
                        break;
                    }
                    case "dir":
                    {
                        current.directories_.Add(new Node(input[1], 0, current, new List<Node>()));
                        break;
                    }
                    default:
                    {
                        current.size_ += int.Parse(input[0]);
                        break;
                    }
                }
            }

            return directory;
        }
    }

    private static int counter = 0;

    static int Solve(Node input)
    {
        int dir_size = 0;
        foreach (var next in input.directories_)
        {
            var next_size = Solve(next);

            if (next_size <= limit)
            {
                counter += next_size;
            }

            dir_size += next_size;
        }

        return dir_size + input.size_;
    }

    public static void Main(string[] args)
    {
        var input = ReadFile(args[0]);

        var result = Solve(input);

        Console.WriteLine(counter);
    }
}
