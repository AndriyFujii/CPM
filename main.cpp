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

//Checks if the given ID exists or not, and if it's not the same as the one being changed
bool checkActivityId(vector<activity> activities, string id, int currentActivity)
{
    for (int i = 0; i < activities.size(); i++)
        if(activities[i].id == id && activities[currentActivity].id != id)
            return true;
    
    return false;
}

void setSucessor(vector<activity> &activities, string id, string currentActivityId)
{
    for (int i = 0; i < activities.size(); i++)
    {
        if(activities[i].id == id)
            activities[i].successors.push_back(currentActivityId);
    }
    
}

//In
void activitiesInput(vector<activity> &activities)
{
    for (int i = 0; i < activities.size(); i++)
    {
        cout << "\nActivity " << i+1 << "\n\n";
        
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
            cout << "Predecessor ID #" << j+1 << ": ";
            cin >> activityId;
            if(checkActivityId(activities, activityId, i))
            {
                //Sets the predecessor
                activities[i].predecessors.push_back(activityId);
                //Sets the sucessor
                setSucessor(activities, activityId, activities[i].id);

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