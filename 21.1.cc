#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    unordered_set<string> ingredients, allergens;
    vector<pair<unordered_set<string>, unordered_set<string>>> foods;
    for (string line; getline(cin, line);)
    {
        pair<unordered_set<string>, unordered_set<string>> food;
        istringstream in(line);
        for (string ingredient; in >> ingredient;)
        {
            if (ingredient == "(contains")
                break;
            ingredients.insert(ingredient);
            food.first.insert(ingredient);
        }
        for (string allergen; in >> allergen;)
        {
            allergen = allergen.substr(0, allergen.size() - 1);
            allergens.insert(allergen);
            food.second.insert(allergen);
        }
        foods.push_back(food);
    }

    unordered_set<string> bad;
    for (const auto& i : ingredients)
    {
        bool some = false;
        for (const auto& a : allergens)
        {
            bool ok = true;
            for (const auto& [is, as] : foods)
            {
                if (as.count(a) && !is.count(i))
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                some = true;
                break;
            }
        }
        if (!some)
        {
            bad.insert(i);
        }
    }
    int ans = 0;
    for (const auto& i : bad)
        for (const auto& [is, as] : foods)
            if (is.count(i))
                ++ans;
    cout << ans << '\n';

    return 0;
}
