#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <regex>

using namespace std;

using Rule = pair<char, vector<vector<int>>>;

unordered_map<int, Rule> rules;
unordered_map<int, string> dp;

string build(int r)
{
    auto it = dp.find(r);
    if (it != dp.end())
        return it->second;
    ostringstream out;
    if (rules[r].first)
        out << rules[r].first;
    else
    {
        bool sep = false;
        out << '(';
        for (auto v : rules[r].second)
        {
            if (sep)
                out << '|';
            sep = true;
            for (int i : v)
                out << (i == -1 ? "+" : "(" + build(i) + ")");
        }
        out << ')';
    }
    return dp[r] = out.str();
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    for (string line; getline(cin, line) && !line.empty();)
    {
        istringstream in(line);
        char tmp;
        int rule_id;
        Rule rule;
        rule.first = 0;

        in >> rule_id >> tmp;
        assert(tmp == ':');

        vector<int> cur;
        for (string s; in >> s;)
        {
            if (s.size() == 3 && s[0] == '"' && s[2] == '"')
                rule.first = s[1];
            else if (s == "|")
            {
                rule.second.push_back(cur);
                cur.clear();
            }
            else
                cur.push_back(stoi(s));
        }
        rule.second.push_back(cur);

        rules[rule_id] = rule;
    }
    rules[8] = Rule(0, { { 42, -1 } });
    rules[11] = Rule(0, {});
    for (int i = 1; i < 10; ++i)
    {
        vector<int> v;
        for (int j = 0; j < i; ++j)
            v.push_back(42);
        for (int j = 0; j < i; ++j)
            v.push_back(31);
        rules[11].second.push_back(v);
    }

    int ans = 0;
    const regex re(build(0));
    for (string line; getline(cin, line);)
        ans += regex_match(line, re);
    cout << ans << '\n';

    return 0;
}
