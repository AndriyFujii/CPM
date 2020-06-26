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

    vector<int> successors;
    vector<int> predecessors;
};

//Finds in which position of the vector the given ID is, and returns that position or -1 if it didn't find any
int findActivity(vector<activity> activities, string id)
{
    for (int i = 0; i < activities.size(); i++)
    {
        if (activities[i].id == id)
            return i;
    }

    return -1;
}

void activitiesInput(vector<activity> &activities)
{
    for (int i = 0; i < activities.size(); i++)
    {
        cout << "\nActivity " << i + 1 << "\n\n";

        cout << "ID: ";
        cin >> activities[i].id;

        cout << "Duration: ";
        cin >> activities[i].duration;

        int numberPredecessors;
        cout << "Number of predecessors: ";
        cin >> numberPredecessors;
        for (int j = 0; j < numberPredecessors; j++)
        {
            string activityId;
            cout << "Predecessor ID #" << j + 1 << ": ";
            cin >> activityId;

            if (findActivity(activities, activityId) != -1 && activityId != activities[i].id)
            {
                //Sets the predecessor
                activities[i].predecessors.push_back(findActivity(activities, activityId));
                //Sets the sucessor
                activities[findActivity(activities, activityId)].successors.push_back(i);
            }
            else
            {
                cout << "\n ID not found! Try again.\n\n";
                j--;
            }
        }
    }
}

int main()
{
    int numberActivities;
    cout << "Enter the number of activities: ";
    cin >> numberActivities;

    vector<activity> activities(numberActivities);

    activitiesInput(activities);

    //checking if predecessors and sucessors are working
    /*for (int i = 0; i < numberActivities; i++)
    {
        cout << '\n';
        for (int j = 0; j < activities[i].predecessors.size(); j++)
            cout << "predecessors: " << activities[i].predecessors[j] << ' ';
        cout << '\n';
        for (int j = 0; j < activities[i].successors.size(); j++)
            cout << "sucessors: " << activities[i].successors[j] << ' ';
    }*/
    system("pause");
}