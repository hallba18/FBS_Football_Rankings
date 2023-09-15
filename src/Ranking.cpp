#include <string>
#include <list>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Team.h"

using namespace std;


int main(int argc, char ** argv)
{
    //First pass for determining unique FBS teams 
    const string C_FBS = "fbs";
    vector<string> C_1_FIELDS = {"\"Home Team\"","\"Home Division\"",
            "\"Away Team\"","\"Away Division\""};
    int p1_field_indexes[] = {-1, -1, -1, -1};

    //Creating Teams list
    map<const string, Team *> team_list;
    map<const string, Team *>::iterator team_it;
    Team * new_team = NULL;

    char * fname = new char[256];
    int field_cnt, index_cnt, i;
    string line, field;
    string team_info[4];
    ifstream myfile;
    size_t pos, lastpos;// nextpos;
    vector<string>::iterator it;
    int retval = 0;

    memset(fname, 0x00, sizeof(char) * 256);
    if(argc == 2)
    {
        myfile.open(argv[1]);
        if(myfile.is_open())
        {
            getline(myfile, line);

            //Iterates over the first line and finds the index of the 
            //    C_1_FIELDS in that line
            field_cnt = index_cnt = 0;
            lastpos = 0;
            pos = line.find(',');
            while (pos != string::npos) 
            {
                it = find(C_1_FIELDS.begin(),C_1_FIELDS.end(),
                        line.substr(lastpos, pos-lastpos));
                if(C_1_FIELDS.end() != it)
                {
                    p1_field_indexes[index_cnt] = field_cnt;
                    index_cnt++;
                }
                lastpos = ++pos;
                pos = line.find(',', pos);
                field_cnt++;
            }

            if(!(p1_field_indexes[0] == -1 || p1_field_indexes[1] == -1 || 
                p1_field_indexes[2] == -1 || p1_field_indexes[3] == -1))
            {
                //Parse the first game of the data file
                while(!myfile.eof())
                {
                    getline(myfile, line);
                    if(line.size() > 10)
                    {

                        field_cnt = index_cnt = 0;
                        lastpos = 0;
                        pos = line.find(',');
                        while (pos != string::npos) 
                        {
                            if(p1_field_indexes[index_cnt] == field_cnt)
                            {
                                //cout << line.substr(lastpos, pos-lastpos) << " ";
                                team_info[index_cnt] = line.substr(lastpos, pos-lastpos);
                                index_cnt++;
                            }
                            lastpos = ++pos;
                            pos = line.find(',', pos);
                            field_cnt++;
                        }
                        //cout << "\n";
                        if(C_FBS.compare(team_info[1]) == 0 && 
                            team_list.find(team_info[0]) == team_list.end())
                        {
                            new_team = Team::Create(team_info[0].c_str());
                            if(new_team)
                            {
                                team_list.emplace(team_info[0], new_team);
                                printf("Successfully created team: "
                                    "%s - %p\n", team_info[0].c_str(), 
                                    (void *) new_team);
                                //cout << "Successfully created team: " <<
                                //    team_info[0] << " @ " << new_team << "\n";
                                new_team = NULL;
                            }
                            else
                            {
                                retval = -4;
                                cout << "Unable to create team: " << team_info[0] 
                                    << "\n";
                            }
                        }
                        //else    
                        //{ 
                        //    cout << team_info[0] << " already in list or not FBS\n"; 
                        //}

                        if(C_FBS.compare(team_info[3]) == 0 && 
                            team_list.find(team_info[2]) == team_list.end())
                        {
                            new_team = Team::Create(team_info[2].c_str());
                            if(new_team)
                            {
                                team_list.emplace(team_info[2], new_team);
                                printf("Successfully created team: "
                                    "%s - %p\n", team_info[2].c_str(), 
                                    (void *) new_team);
                                //cout << "Successfully created team: " <<
                                //    team_info[2] << " @ " << (void *) new_team << "\n";
                                new_team = NULL;
                            }
                            else
                            {
                                retval = -4;
                                cout << "Unable to create team: " << team_info[2] 
                                    << "\n";
                            }
                        }
                    }
                    //else    
                    //{ 
                    //    cout << team_info[2] << " already in list or not FBS\n"; 
                    //}
                }
            }
            else
            {
                retval = -3;
                cout << "Failed to get field reference indexes\n";
            }
        }
        else
        {
            retval = -2;
            cout << "Failure to open file" << fname << "\n";
        }
    }
    else if(argc < 2)
    { 
        retval = -1; 
        cout << "Too few arguments\n";
    }
    else
    {
        retval = -1;
        cout << "Too many argurments\n";
    }

    cout << "Successfully created " << team_list.size() << " Teams";

    ///TODO: Iterate over the file once
    ///TODO:    Are teams FBS? 
    ///TODO:        Yes: Add unique teams to teams list
    
    ///TODO: (Optional) Sort teams list
    ///TODO: Iterate over teams list and create list of Teams objects

    ///TODO: Iterate over file again
    ///TODO:    Increment number of seasons and games for each team

    ///TODO: Initialize arrays for each Team object

    ///TODO: Iterate over file for the last time
    ///TODO:    Add game results for every team

    ///TODO: Iterate over every season
    ///TODO:    Calculate win percentage for each team
    ///TODO:    Calculate opp. win pct. for each team
    ///TODO:    Calculate opp. opp. win pct. for each team
    ///TODO:    Calculate initial score for each team
    ///TODO:    Rank teams by initial scores
    ///TODO:    Calculate final score for each team
    ///TODO:    Rerank teams by final scores

    ///TODO: Write statistics to output file

    if(new_team)
    {
        new_team->~Team();
        new_team = NULL;
    }
    if(!team_list.empty())
    {
        for(team_it = team_list.begin(); team_it != team_list.end(); ++team_it)
        {
            (team_it->second)->~Team();
            team_it->second = NULL;
        }
        team_list.clear();
    }
    if(fname)    { delete [] fname;    fname = NULL; }
    return retval;
}
