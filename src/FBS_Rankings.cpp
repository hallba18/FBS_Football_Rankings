#include <string>
#include <list>
#include <cstdio>
#include <cstring>
#include "Team.h"

int main(int argc, char ** argv)
{
    char * fname = new char[256];
    FILE * fp = NULL;
    int retval = 0;

    memset(fname, 0x00, sizeof(char) * 256);
    if(argc == 2)
    {
        strcpy(fname, argv[1]);
        fp = fopen(fname, "r");
        if(fp)
        {
            printf("Success\n");
            fclose(fp);
        }
        else
        {
            retval = -2;
            printf("Failure to open file: %s", fname);
        }
    }
    else    { retval = -1; }

    ///TODO: Parse input and open data file

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

    if(fname)    { delete [] fname;    fname = NULL; }    
    return retval;
}