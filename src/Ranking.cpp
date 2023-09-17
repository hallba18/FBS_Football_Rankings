#include <functional>
#include <string>
#include <list>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Ranking.h"
#include "Team.h"

using namespace std;

int main(int argc, char ** argv)
{
    //First pass for determining unique FBS teams 
    const string C_FBS = "fbs";
    vector<string> CSV_FIELDS = {"Season","Week","Season Type", "Start Date",
            "Completed","Neutral Site", "Conference Game","Home Team",
            "Home Conference", "Home Division","Home Points","Away Team",
            "Away Conference","Away Division","Away Points"};
    int p1_field_indexes[] = 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    //Creating Teams list
    map<const string, Team *> team_list;
    map<const string, Team *>::iterator team_it;
    Team * team_ptr = NULL;
    Team * fcs_team = NULL;
    map<const string, Team *>::iterator home_it;
    map<const string, Team *>::iterator away_it;

    gameResult new_game;

    char * fname = new char[256];
    int field_cnt, index_cnt, i;
    unsigned int latest_sn;
    string line, field;
    string game_info[CSV_FIELDS.size()];
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
                it = find(CSV_FIELDS.begin(),CSV_FIELDS.end(),
                        line.substr(lastpos, pos-lastpos));
                if(CSV_FIELDS.end() != it)
                {
                    p1_field_indexes[index_cnt] = field_cnt;
                    index_cnt++;
                }
                lastpos = ++pos;
                pos = line.find(',', pos);
                field_cnt++;
            }

            if(!(p1_field_indexes[7] == -1 || p1_field_indexes[9] == -1 || 
                p1_field_indexes[11] == -1 || p1_field_indexes[13] == -1))
            {
                while(!myfile.eof())
                {
                    getline(myfile, line);
                    if(line.size() > 10)
                    {
                        
                        new_game.reset();

                        field_cnt = index_cnt = 0;
                        lastpos = 0;
                        pos = line.find(',');
                        while (pos != string::npos) 
                        {
                            if(p1_field_indexes[index_cnt] == field_cnt)
                            {
                                game_info[index_cnt] = line.substr(lastpos, pos-lastpos);
                                index_cnt++;
                            }
                            lastpos = ++pos;
                            pos = line.find(',', pos);
                            field_cnt++;
                        }
                        game_info[index_cnt] = line.substr(lastpos);

                        if(game_info[4].compare("true"))    { continue; }

                        new_game.newResult(stoul(game_info[0]), 
                            game_info[5].compare("false"), stoul(game_info[10]), 
                            stoul(game_info[14]));
                            
                        home_it = team_list.find(game_info[7]);
                        if(C_FBS.compare(game_info[9]) == 0 && 
                            home_it == team_list.end())
                        {
                            team_ptr = Team::Create(game_info[7].c_str(), true);
                            if(team_ptr)
                            {
                                team_list.emplace(game_info[7], team_ptr);
                                //printf("Successfully created team: "
                                //    "%s\n", game_info[7].c_str());
                                new_game.addTeam(team_ptr, true);
                                team_ptr = NULL;
                            }
                            else
                            {
                                retval = -4;
                                cout << "Unable to create team: " << game_info[7] 
                                    << "\n";
                                break;
                            }
                        }
                        else if(home_it != team_list.end())
                            { new_game.addTeam(home_it->second, true); }
                        else 
                        {
                            if(fcs_team == NULL)    { fcs_team = Team::Create("FCS", false); }
                            new_game.addTeam(fcs_team, true);
                        }

                        away_it = team_list.find(game_info[11]);
                        if(C_FBS.compare(game_info[13]) == 0 && 
                            away_it == team_list.end())
                        {
                            team_ptr = Team::Create(game_info[11].c_str(), true);
                            if(team_ptr)
                            {
                                team_list.emplace(game_info[11], team_ptr);
                                //printf("Successfully created team: "
                                //    "%s\n", game_info[11].c_str());
                                new_game.addTeam(team_ptr, false);
                                team_ptr = NULL;
                            }
                            else
                            {
                                retval = -5;
                                cout << "Unable to create team: " << 
                                    game_info[11] << "\n";
                                break;
                            }
                        }
                        else if(away_it != team_list.end())
                            { new_game.addTeam(away_it->second, false); }
                        else 
                        {
                            if(fcs_team == NULL)    { fcs_team = Team::Create("FCS", false); }
                            new_game.addTeam(fcs_team, false);
                        }

                        if(C_FBS.compare(game_info[9]) == 0 &&
                           C_FBS.compare(game_info[13]) == 0)
                        {
                            if(!new_game.storeResults())
                            {
                                retval = -6;
                                break;
                            }
                        }
                    }
                }


                if(retval == 0)
                {
                    for(team_it = team_list.begin(); team_it != team_list.end(); ++team_it)
                    {
                        team_it->second->CalcWinPct();
                        team_it->second->CalcOppWinPct();
                        team_it->second->PrintTeam();
                    }
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

    if(team_ptr)
    {
        team_ptr->~Team();
        team_ptr = NULL;
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


void gameResult::reset(void)
{
    m_season = 0;
    m_isNeutral = false;
    m_home = NULL;
    m_away = NULL;
    m_hScore = 0;
    m_aScore = 0;
}


void gameResult::addTeam(Team * team, bool isHome)
{
    assert(team);
    if(isHome)    { m_home = team; }
    else          { m_away = team; }
}


void gameResult::newResult(unsigned int season, bool isNeutral, 
        unsigned int hScore, unsigned int aScore)
{
    m_season = season;
    m_isNeutral = isNeutral;
    m_hScore = hScore;
    m_aScore = aScore;
}


bool gameResult::storeResults(void)
{
    bool retval = true;
    if(m_home && m_away)
    {
        retval = m_home->AddGameResult(m_season, m_away, (m_hScore - m_aScore), 
            (m_isNeutral) ? Team::NEUTRAL : Team::HOME);
        if(retval)
        {
            retval = m_away->AddGameResult(m_season, m_home, (m_aScore-m_hScore), 
                (m_isNeutral) ? Team::NEUTRAL : Team::AWAY);
        }
    }
    else    { cout << "Failed to store results\n"; }

    return retval;
}


gameResult::gameResult(void)
{
    m_season = 0;
    m_isNeutral = false;
    m_home = NULL;
    m_away = NULL;
    m_hScore = 0;
    m_aScore = 0;
}

gameResult::~gameResult(void)
{
    m_season = 0;
    m_isNeutral = false;
    m_home = NULL;
    m_away = NULL;
    m_hScore = 0;
    m_aScore = 0;
}