#include <iostream>
#include <vector>

using namespace std;

int find_max(vector<string> &neighbor, string target)
{
    int count = 0;
    for (size_t i = 0; i < neighbor.size(); i++)
    {
        if (neighbor[i] == target)
        {
            count++;
        }
    }
    return count;
}

class Neighbor
{
public:
    string majorityNeighbor(vector<string> &neighbor)
    {
        string max = "";
        int maxx = 0;
        for (size_t i = 0; i < neighbor.size(); i++)
        {
            int count_name = find_max(neighbor, neighbor[i]);
            if (count_name > maxx)
            {
                maxx = count_name;
                max = neighbor[i];
            }
        }
        return max;
    }
};

int main()
{
    vector<string> nums = {
        "Peter",
        "Bob",
        "Peter",
        "Bob"};
    Neighbor s;
    cout << s.majorityNeighbor(nums);
}