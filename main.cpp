#include <iostream>
#include <vector>

using namespace std;

struct activity
{
    string id;
    int duration;
    int earliestStart = -1; 
    int earliestFinish = -1;
    int latestStart = -1;
    int latestFinish = -1;
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

//Inputs the data of the activities
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

//Sets the earliest times of the activities
void setEarliestTimes(vector<activity> &activities, int nextIndex, int totalDuration)
{
    if(totalDuration > activities[nextIndex].earliestStart)
    {
        activities[nextIndex].earliestStart = totalDuration;
        totalDuration += activities[nextIndex].duration;
        activities[nextIndex].earliestFinish = totalDuration;
    }
    for (int j = 0; j < activities[nextIndex].successors.size(); j++)
    {
        setEarliestTimes(activities, activities[nextIndex].successors[j], totalDuration);
    }
}

void setLatestTimes(vector<activity> &activities, int nextIndex, int totalDuration)
{
    if(activities[nextIndex].latestFinish == -1 || totalDuration < activities[nextIndex].latestFinish)
    {
        activities[nextIndex].latestFinish = totalDuration;
        totalDuration -= activities[nextIndex].duration;
        activities[nextIndex].latestStart = totalDuration;
    }
    for (int j = 0; j < activities[nextIndex].predecessors.size(); j++)
    {
        setLatestTimes(activities, activities[nextIndex].predecessors[j], totalDuration);
    }
}

int highestTime(vector<activity> activities)
{
    int highestTime = 0;
    for (int i = 0; i < activities.size(); i++)
    {
        if(activities[i].earliestFinish > highestTime)
            highestTime = activities[i].earliestFinish;
    }
    return highestTime;
}

int main()
{
    int numberActivities;
    cout << "Enter the number of activities: ";
    cin >> numberActivities;

    vector<activity> activities(numberActivities);

    activitiesInput(activities);

    for (int i = 0; i < activities.size(); i++)
    {
        //Only on start nodes
        if(activities[i].predecessors.size() == 0)
        {
            setEarliestTimes(activities, i, 0);
        }
    }

    for (int i = 0; i < activities.size(); i++)
    {
        //Only on finish nodes
        if(activities[i].successors.size() == 0)
        {
            setLatestTimes(activities, i, highestTime(activities));
        }
    }

    //checking if predecessors and sucessors are working
    /*for (int i = 0; i < numberActivities; i++)
    {
        cout << "\n\n";
        cout << "Activity ID: " << activities[i].id << '\n' << "Predecessors: ";
        for (int j = 0; j < activities[i].predecessors.size(); j++)
            cout  << activities[i].predecessors[j] << ' ';
        cout  << "\nSucessors: ";
        for (int j = 0; j < activities[i].successors.size(); j++)
            cout << activities[i].successors[j] << ' ';
        cout << "\nEarliest start: " << activities[i].earliestStart;
        cout << "\nEarliest finish: " << activities[i].earliestFinish;
        cout << "\nLatest start: " << activities[i].latestStart;
        cout << "\nLatest finish: " << activities[i].latestFinish;
    }*/
    cout << '\n';
    system("pause");
}