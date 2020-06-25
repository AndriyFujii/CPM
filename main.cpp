#include <iostream>
#include <vector>

using namespace std;

struct activity
{
    string id;
    int duration;
    int earliestStart, earliestFinish;
    int latestStart, latestFinish;
    int slack;

    vector<string> successors;
    vector<string> predecessors;
};

int main()
{
    int numberActivities;
    cout << "Enter the number of activities: ";
    cin >> numberActivities;

    vector<activity> activities(numberActivities);

}