#include "main.h"
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

//Finds in which position of the vector the given activity ID is, and returns that position or -1 if it didn't find any
int findActivity(vector<activity> activities, string id)
{
    for (int i = 0; i < activities.size(); i++)
    {
        if (activities[i].id == id)
            return i;
    }

    return -1;
}

//Checks if ID already exists in the activities vector, true if it does
bool isDuplicate(vector<activity> activities, string id)
{
    int count = 0;
    for (int i = 0; i < activities.size(); i++)
    {
        if (activities[i].id == id)
            count++;
    }
    
    if(count > 1)
        return true;
    else
        return false;
}

//Returns the highest total time of the activities
int getHighestTime(vector<activity> activities)
{
    int highestTime = 0;
    for (int i = 0; i < activities.size(); i++)
    {
        if (activities[i].earliestFinish > highestTime)
            highestTime = activities[i].earliestFinish;
    }
    return highestTime;
}

//Shows every data from every activity
void showActivities(vector<activity> activities)
{
    for (int i = 0; i < activities.size(); i++)
    {
        cout << "    Activity ID: " << activities[i].id << '\n'
             << "   Predecessors: ";
        for (int j = 0; j < activities[i].predecessors.size(); j++)
            cout << activities[i].predecessors[j] << ' ';
        cout << "\n      Sucessors: ";
        for (int j = 0; j < activities[i].successors.size(); j++)
            cout << activities[i].successors[j] << ' ';
        cout << "\n Earliest start: " << activities[i].earliestStart;
        cout << "\nEarliest finish: " << activities[i].earliestFinish;
        cout << "\n   Latest start: " << activities[i].latestStart;
        cout << "\n  Latest finish: " << activities[i].latestFinish;
        cout << "\n          Slack: " << activities[i].slack;
        cout << "\n\n";
    }
}

//Inputs the data of the activities
void activitiesInput(vector<activity> &activities)
{
    for (int i = 0; i < activities.size(); i++)
    {
        cout << "\nActivity " << i + 1 << "\n\n";

        cout << "ID: ";
        bool exit;
        //Validates if the ID already exists
        do
        {
            cin >> activities[i].id;

            exit = true;
            if(isDuplicate(activities, activities[i].id))
            {
                cout << "Already exists! Try again: ";
                exit = false;
            }
        }
        while(!exit);

        cout << "Duration: ";
        cin >> activities[i].duration;

        int numberPredecessors;
 
        cout << "Number of predecessors: ";
        //Validates that there will be enough predecessors
        do
        {
            cin >> numberPredecessors;

            exit = true;
            if(numberPredecessors > i)
            {
                cout << "Not enough predecessors! Try again: ";
                exit = false;
            }
        } while (!exit);
        
        
        for (int j = 0; j < numberPredecessors; j++)
        {
            string activityId;
            cout << "Predecessor ID #" << j + 1 << ": ";
            cin >> activityId;
            //Checks if the predecessor ID exists
            if (findActivity(activities, activityId) != -1 && activityId != activities[i].id)
            {
                //Sets the predecessor
                activities[i].predecessors.push_back(findActivity(activities, activityId));
                //Sets the sucessor
                activities[findActivity(activities, activityId)].successors.push_back(i);
            }
            else
            {
                cout << "Invalid predecessor! Try again.\n";
                j--;
            }
        }
    }
}

//Sets the earliest times of the activities
void setEarliestTimes(vector<activity> &activities, int nextIndex, int totalDuration)
{
    if (totalDuration > activities[nextIndex].earliestStart)
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

//Sets the latest times of the activities
void setLatestTimes(vector<activity> &activities, int nextIndex, int totalDuration)
{
    if (activities[nextIndex].latestFinish == -1 || totalDuration < activities[nextIndex].latestFinish)
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

//Sets the slack of the activities
void setSlack(vector<activity> &activities)
{
    for (int i = 0; i < activities.size(); i++)
    {
        activities[i].slack = activities[i].latestFinish - activities[i].earliestFinish;
    }
}

//Returns the IDs of the critical path activities
vector<string> getCriticalPath(vector<activity> activities)
{
    vector<string> criticalPath;
    for (int i = 0; i < activities.size(); i++)
    {
        if (activities[i].slack == 0)
            criticalPath.push_back(activities[i].id);
    }
    return criticalPath;
}

int main()
{
    header();

    bool tryAgain;
    do
    {
        system("cls");

        int numberActivities;
        cout << "Enter the number of activities: ";
        cin >> numberActivities;

        vector<activity> activities(numberActivities);

        activitiesInput(activities);

        //Earliest times
        for (int i = 0; i < activities.size(); i++)
        {
            //Only on start nodes
            if (activities[i].predecessors.size() == 0)
            {
                setEarliestTimes(activities, i, 0);
            }
        }
        int totalTime = getHighestTime(activities);
        //Latest times
        for (int i = 0; i < activities.size(); i++)
        {
            //Only on finish nodes
            if (activities[i].successors.size() == 0)
            {
                setLatestTimes(activities, i, totalTime);
            }
        }

        setSlack(activities);

        vector<string> criticalPath = getCriticalPath(activities);

        system("cls");

        showActivities(activities);
        //Shows the critical path
        cout << "\nCritical path: ";
        for (int i = 0; i < criticalPath.size(); i++)
        {
            cout << criticalPath[i] << ' ';
        }

        bool exit;
        char choice;
        //If the program should run again or close
        do
        {
            cout << "\n\nFinished! Try again? (Y/N) ";
            cin >> choice;
            choice = tolower(choice);

            exit = false;
            //Only leaves the loop if Y or N are typed
            if (choice == 'y')
            {
                tryAgain = true;
                exit = true;
            }
            else if (choice == 'n')
            {
                tryAgain = false;
                exit = true;
            }
        } while (!exit);

    } while (tryAgain);
}