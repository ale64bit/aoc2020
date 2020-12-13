import java.io.*;
import java.util.*;

public class Solution
{
    static class Node
    {
        Node(String col, int n)
        {
            this.col = col;
            this.n = n;
        }

        String col;
        int n;
    }

    Map<String, List<Node>> g = new HashMap<>();
    Map<String, Long> count = new HashMap<>();

    public void readGraph()
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true)
        {
            try
            {
                String line = br.readLine();
                if (line == null)
                    return;
                line = line.replaceAll("bags?\\.?", "");
                String[] parts = line.split("contain");
                String u = parts[0].trim();
                List<Node> adj = g.computeIfAbsent(u, k -> new ArrayList<>());

                parts = parts[1].split(",");
                for (String s : parts)
                {
                    s = s.trim();
                    if (s.equals("no other"))
                        break;
                    String[] cols = s.split(" +");
                    Integer n = Integer.parseInt(cols[0]);
                    String v = cols[1] + " " + cols[2];
                    adj.add(new Node(v, n));
                }
            }
            catch (IOException e)
            {
                return;
            }
        }
    }

    public long dfs(String u)
    {
        if (count.containsKey(u))
            return count.get(u);
        long ret = 1;
        for (Node v : g.getOrDefault(u, new ArrayList<>()))
            ret += v.n * dfs(v.col);
        count.put(u, ret);
        return ret;
    }

    public void run()
    {
        readGraph();
        dfs("shiny gold");
        System.out.println(count.get("shiny gold") - 1);
    }

    public static void main(String[] arg) { new Solution().run(); }
}
