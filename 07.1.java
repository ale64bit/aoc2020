import java.io.*;
import java.util.*;

public class Solution
{
    Map<String, List<String>> g = new HashMap<>();
    Set<String> seen = new HashSet<>();

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
                String v = parts[0].trim();
                parts = parts[1].split(",");
                for (String s : parts)
                {
                    s = s.trim();
                    if (s.equals("no other"))
                        break;
                    String[] cols = s.split(" +");
                    String u = cols[1] + " " + cols[2];
                    List<String> adj = g.computeIfAbsent(u, k -> new ArrayList<>());
                    adj.add(v);
                }
            }
            catch (IOException e)
            {
                return;
            }
        }
    }

    public void dfs(String u)
    {
        seen.add(u);
        for (String v : g.getOrDefault(u, new ArrayList<>()))
            if (!seen.contains(v))
                dfs(v);
    }

    public void run()
    {
        readGraph();
        dfs("shiny gold");
        System.out.println(seen.size() - 1);
    }

    public static void main(String[] arg) { new Solution().run(); }
}
