#include <cmath>
#include <cstddef>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <limits>
#include <cmath>
#include "Team.h"

/*******************************************************************/
/*                         Public Methods                          */
/*******************************************************************/
//Public Destructor
Team::~Team(void)
{
    if(m_seasons)           
        { delete [] m_seasons;    m_seasons = NULL; }
    if(m_num_aa_ps)         
        { delete [] m_num_aa_ps;    m_num_aa_ps = NULL; }
    if(m_num_games_ps)      
        { delete [] m_num_games_ps;    m_num_games_ps = NULL; }
    if(m_wins_ps)           
        { delete [] m_wins_ps;    m_wins_ps = NULL; }
    if(m_losses_ps)         
        { delete [] m_losses_ps;    m_losses_ps = NULL; }
    if(m_ties_ps)           
        { delete [] m_ties_ps;    m_ties_ps = NULL; }
    if(m_avg_mov_ps)         
        { delete [] m_avg_mov_ps;    m_avg_mov_ps = NULL; }
    if(m_winpct_ps)         
        { delete [] m_winpct_ps;    m_winpct_ps = NULL; }
    if(m_opp_winpct_ps)     
        { delete [] m_opp_winpct_ps;    m_opp_winpct_ps = NULL; }
    if(m_o_opp_winpct_ps)   
        { delete [] m_o_opp_winpct_ps;    m_o_opp_winpct_ps = NULL; }
    if(m_init_score_ps)     
        { delete [] m_init_score_ps;    m_init_score_ps = NULL; }
    if(m_final_score_ps)    
        { delete [] m_final_score_ps;    m_final_score_ps = NULL; }
    if(m_num_teams_ps)      
        { delete [] m_num_teams_ps;    m_num_teams_ps = NULL; }
    if(m_init_rank_ps)      
        { delete [] m_init_rank_ps;    m_init_rank_ps = NULL; }
    if(m_final_rank_ps)     
        { delete [] m_final_rank_ps;    m_final_rank_ps = NULL; }
    if(m_opp_pg)            
    { 
        for(int i = 0; i < (C_MAX_SEASONS * C_MAX_GAMES); i++)
            { m_opp_pg[i] = NULL; }
        delete [] m_opp_pg;
        m_opp_pg = NULL;
    }
    if(m_location_pg)       
        { delete [] m_location_pg;    m_location_pg = NULL; }
    if(m_result_pg)         
        { delete [] m_result_pg;    m_result_pg = NULL; }
}

/*******************************************************************/
/*                         Team :: Create                          */
/*  Description: Public Function to create a Team object to keep   */
/*      the constructor private                                    */
/*  Input:  String "name": Name of the school                      */
/*  Output: Team *: Pointer to the new Team object                 */
/*                                                                 */
/*******************************************************************/
Team * Team::Create(const char * name, bool isFBS)
{
    Team * that = NULL;

    that = new Team(name, isFBS);

    return that;
}


void Team::PrintTeam(void)
{
    int season;

    /*printf("%s: %d seasons, Records: \n", m_name, m_num_seasons);
    for(season = 0; season < m_num_seasons; season++)
    {
        printf("%f", m_init_score_ps[season]);
        //if(m_ties_ps[season]) { printf("-%d",m_ties_ps[season]); }
        printf(", ");
    }
    printf("\n");*/
    printf("%s", m_name);
}


bool Team::GetIsFBS(void)
    { return m_isFBS; }


/*******************************************************************/
/*                     Team :: GetLatestSeason                     */
/*  Description: Return the most recent season value               */
/*  Input:  (VOID)                                                 */
/*  Output: Unsigned Int: The last year stored in m_seasons        */
/*                                                                 */
/*******************************************************************/
unsigned int Team::GetLatestSeason(void)
{
    unsigned int season = 0;
    if(m_num_seasons)    { season = m_seasons[m_num_seasons-1]; }

    return season;
}


/*******************************************************************/
/*                        Team :: GetWinPct                        */
/*  Description: Return the value from m_winpct_ps for a           */
/*      given season                                               */
/*  Input:  Integer "season": Year                                 */
/*  Output: Double: value stored in m_winpct_ps                    */
/*                                                                 */
/*******************************************************************/
double Team::GetWinPct(int season)
{
    double retval = 0;
    int index, i;

    if(m_isFBS)
    {
        for(i = 0; i < m_num_seasons; i++)
        {
            if(season == m_seasons[i]) 
            {
                retval = m_winpct_ps[i];
                break;
            }
        }
        if(i == m_num_seasons)
        {
            retval = -2.0;
        }

    }
    else {
        retval = -1.0;
    }

    return retval;
}


/*******************************************************************/
/*                      Team :: GetOppWinPct                       */
/*  Description: Return the value from m_opp_winpct_ps for a       */
/*      given season                                               */
/*  Input:  Integer "season": Year                                 */
/*  Output: Double: value stored in m_opp_winpct                   */
/*                                                                 */
/*******************************************************************/
double Team::GetOppWinPct(int season)
{
    double retval = 0;
    int index, i;

    if(m_isFBS)
    {
        for(i = 0; i < m_num_seasons; i++)
        {
            if(season == m_seasons[i]) 
            {
                retval = m_opp_winpct_ps[i];
                break;
            }
        }
        if(i == m_num_seasons)
        {
            retval = -2.0;
        }

    }
    else {
        retval = -1.0;
    }

    return retval;
}


/*******************************************************************/
/*                     Team :: GetInitialScore                     */
/*  Description: Return the value from m_init_score_ps for a       */
/*      given season                                               */
/*  Input:  Integer "season": Year                                 */
/*  Output: Double: value stored in m_init_score_ps                */
/*                                                                 */
/*******************************************************************/
double Team::GetInitialScore(int season)
{
    double retval = 0;
    int index, i;

    if(m_isFBS)
    {
        for(i = 0; i < m_num_seasons; i++)
        {
            if(season == m_seasons[i]) 
            {
                retval = m_init_score_ps[i];
                break;
            }
        }
        if(i == m_num_seasons)
        {
            retval = -1 * std::numeric_limits<double>::max();
        }

    }
    else {
        retval = std::numeric_limits<double>::max();
    }

    return retval;
}


/*******************************************************************/
/*                      Team :: GetFinalScore                      */
/*  Description: Return the value from m_final_score_ps for a      */
/*      given season                                               */
/*  Input:  Integer "season": Year                                 */
/*  Output: Double: value stored in m_final_score_ps               */
/*                                                                 */
/*******************************************************************/
double Team::Team::GetFinalScore(int season)
{
    double retval = 0;
    int index, i;

    if(m_isFBS)
    {
        if(season)
        {
            for(i = 0; i < m_num_seasons; i++)
            {
                if(season == m_seasons[i]) 
                {
                    retval = m_final_score_ps[i];
                    break;
                }
            }
            if(i == m_num_seasons)
            {
                retval = -1 * std::numeric_limits<double>::max();
            }
        }
        else    { retval = m_final_score; }

    }
    else {
        retval = std::numeric_limits<double>::max();
    }

    return retval;
}


/*******************************************************************/
/*                     Team :: GetInitialRank                      */
/*  Description: Return the value from m_init_rank_ps for a        */
/*      given season                                               */
/*  Input:  Integer "season": Year                                 */
/*  Output: Integer: value stored in m_init_rank_ps                */
/*                                                                 */
/*******************************************************************/
int Team::GetInitialRank(int season)
{
    int retval = 0;
    int index, i;

    for(i = 0; i < m_num_seasons; i++)
    {
        if(season == m_seasons[i]) 
        {
            retval = m_init_rank_ps[i];
            break;
        }
    }
    assert(i != m_num_seasons);

    return retval;
}


/*******************************************************************/
/*                      Team :: GetFinalRank                       */
/*  Description: Return the value from m_final_rank_ps for a       */
/*      given season                                               */
/*  Input:  Integer "season": Year                                 */
/*  Output: Integer: value stored in m_final_rank_ps               */
/*                                                                 */
/*******************************************************************/
int Team::GetFinalRank(int season)
{
    return 0;
}


/*******************************************************************/
/*                      Team :: AddGameResult                      */
/*  Description: Add the result of a game to a specific team       */
/*  Input:  Integer "season": Year                                 */
/*          Team * "opponent": Constant pointer to the opponent's  */
/*              team object                                        */
/*          Integer "score": Point differential of the game        */
/*          gameLocation "location": location of the game          */
/*  Output: Boolean: Was the game successfully added to the team   */
/*                                                                 */
/*******************************************************************/
bool Team::AddGameResult(int season, Team * opponent, 
        int score, gameLocation location)
{
    bool retval = false;
    unsigned int cur_sn = (m_num_seasons) ? m_num_seasons - 1 : 0;
    unsigned int cur_gm;
    double delta, temp;

    if(cur_sn < C_MAX_SEASONS)
    {
        if(season == m_seasons[cur_sn])
            { cur_gm = m_num_games_ps[cur_sn]; }
        else    
        { 
            if(m_num_seasons)    
            { 
                if(m_num_games_ps[cur_sn] > m_max_num_games)
                    { m_max_num_games = m_num_games_ps[cur_sn]; }
                cur_sn++; 
            }
            m_seasons[cur_sn] = season;
            m_num_seasons++;    
            cur_gm = 0; 
        }

        if(cur_gm < C_MAX_GAMES)
        {
            m_location_pg[(cur_sn * C_MAX_GAMES) + cur_gm] = location;
            m_result_pg[(cur_sn * C_MAX_GAMES) + cur_gm] = score;
            m_opp_pg[(cur_sn * C_MAX_GAMES) + cur_gm] = opponent;
            if(score > 0)           { m_wins_ps[cur_sn]++; }
            else if(score == 0)     { m_ties_ps[cur_sn]++; }
            else                    { m_losses_ps[cur_sn]++; }

            m_num_games_ps[cur_sn]++;
            temp = (double) score;
            delta = temp - m_avg_mov_ps[cur_sn];
            m_avg_mov_ps[cur_sn] += delta / (double) m_num_games_ps[cur_sn];
            
            retval = true;
        }
        else
        {
            printf("Current game index is greater than the "
                "max number of games\n");
            retval = false;
        }
    }
    else
    {
        printf("Current season index is greater than the "
            "max number of seasons\n");
        retval = false;
    }

    return retval;
}


void Team::SetInitialRank(int season, int rank, int num_teams)
{
    assert(season);
    assert(rank);
    int i;
    
    for(i = 0; i < m_num_seasons; i++)
    {
        if(season == m_seasons[i]) 
        {
            m_num_teams_ps[i] = num_teams;
            m_init_rank_ps[i] = rank;
            break;
        }
    }
    if(m_isFBS && i == m_num_seasons)
    {
        printf("\n\n\nERROR\n\n\n");
    }
}


/*******************************************************************/
/*                     Team :: AddSeasonResult                     */
/*  Description: Add the result of a season not available from     */
/*      individual game results                                    */
/*  Input:  Integer "season": Year                                 */
/*          Integer "num_AA": Number of All-American selections    */
/*          Boolean "claimed_NT": Claimed National Title           */
/*  Output: Boolean: Was the season successfully added             */
/*                                                                 */
/*******************************************************************/
bool Team::AddSeasonResult(int season, int num_AA, bool claimed_NT)
{
    return false;
}


/*******************************************************************/
/*                       Team :: CalcWinPct                        */
/*  Description: Iterate through opponents and calculate the       */
/*      season's win percentage                                    */
/*  Input:  Integer "season": Year                                 */
/*  Output: Boolean: Was the win percentage successfully calculated*/
/*                                                                 */
/*******************************************************************/
bool Team::CalcWinPcts(void)
{
    bool retval = false;
    int index, i;
    double winpct, mean, delta;

    for(i = 0; i < m_num_seasons; i++)
    {
        winpct = (double) m_wins_ps[i];
        winpct += ((double) m_ties_ps[i]) / 2;
        winpct /= m_num_games_ps[i];
        m_winpct_ps[i] = winpct;
    }


    return true;
}


/*******************************************************************/
/*                     Team :: CalcOppWinPct                       */
/*  Description: Iterate through each opponent and calculate the   */
/*      average opponent's win percentage                          */
/*  Input:  Void                                                   */
/*  Output: Boolean: Was the opponent's win percentage successfully*/
/*      calculated                                                 */
/*                                                                 */
/*******************************************************************/
bool Team::CalcOppWinPcts(void)
{
    int season, op, cnt, gm_index;
    double temp, op_win_pct;

    for(season = 0; season < m_num_seasons; season++)
    {
        cnt = 0;
        op_win_pct = 0.0;
        for(op = 0; op < m_num_games_ps[season]; op++)
        {
            gm_index = (season * C_MAX_GAMES) + op;
            temp = m_opp_pg[gm_index]->GetWinPct(m_seasons[season]);
            if(temp >= 0) 
            {
                op_win_pct += temp;
                cnt++;
            }
        }
        op_win_pct /= (double) cnt;
        m_opp_winpct_ps[season] = op_win_pct;
    }

    return true;
}


/*******************************************************************/
/*                     Team :: CalcOppOppWinPct                    */
/*  Description: Iterate through each opponent to calculate the    */
/*      average opponent's opponent win percentage                 */
/*  Input:  Void                                                   */
/*  Output: Boolean: Was the opponent's opponent win percentage    */
/*      successfully calculated                                    */
/*                                                                 */
/*******************************************************************/
bool Team::CalcOppOppWinPcts(void)
{
    int season, op, cnt, gm_index;
    double temp, opp_opp_win_pct;

    for(season = 0; season < m_num_seasons; season++)
    {
        cnt = 0;
        opp_opp_win_pct = 0.0;
        for(op = 0; op < m_num_games_ps[season]; op++)
        {
            gm_index = (season * C_MAX_GAMES) + op;
            temp = m_opp_pg[gm_index]->GetOppWinPct(m_seasons[season]);
            if(temp >= 0) 
            {
                opp_opp_win_pct += temp;
                cnt++;
            }
        }
        opp_opp_win_pct /= (double) cnt;
        m_o_opp_winpct_ps[season] = opp_opp_win_pct;
    }

    return true;
}


/*******************************************************************/
/*                    Team :: CalcInitialScore                     */
/*  Description: Calculate the intial score for a team's season    */
/*  Input:  Integer "season": Year                                 */
/*  Output: Boolean: Was the initial score calculated successfully */
/*                                                                 */
/*******************************************************************/
bool Team::CalcInitialScores(void)
{
    int season;
    double temp;

    for(season = 0; season < m_num_seasons; season++)
    {
        temp = 2 * m_opp_winpct_ps[season];
        temp += m_o_opp_winpct_ps[season];
        temp *= m_avg_mov_ps[season];
        m_init_score_ps[season] = temp / 3.0;
    }

    return true;
}


/*******************************************************************/
/*                     Team :: CalcFinalScore                      */
/*  Description: Calculate teh final score for a team's season     */
/*  Input:  Integer "season": Year                                 */
/*  Output: Boolean: Was the final score calculated successfully   */
/*                                                                 */
/*******************************************************************/
bool Team::CalcFinalScores()
{
    int season, cnt, op, gm_index;
    double temp, MoV, sum, rank, score;

    m_final_score = 0.0;
    for(season = 0; season < m_num_seasons; season++)
    {
        cnt = 0;
        sum = 0.0;
        for(op = 0; op < m_num_games_ps[season]; op++)
        {
            gm_index = (season * C_MAX_GAMES) + op;
            rank = (double) m_opp_pg[gm_index]->GetInitialRank(m_seasons[season]);
            score = (double) m_result_pg[gm_index];
            temp = (score < 0) ? -1.0 : 1.0;
            temp *= (double) m_init_rank_ps[season] - rank;
            temp /= (double) m_num_teams_ps[season];
            sum += score * pow(3,temp);
        }
        m_final_score_ps[season] = sum;
        m_final_score += sum;
    }

    return true;
}


/*******************************************************************/
/* Class :: Template */
/*  Description: */
/*  Input:  Type "input1": */
/*          Type "input2": */
/*  Output: Type: */
/*                                                                 */
/*******************************************************************/
//bool Team::FinalizeSeason(int season);


/*******************************************************************/
/* Class :: Template */
/*  Description: */
/*  Input:  Type "input1": */
/*          Type "input2": */
/*  Output: Type: */
/*                                                                 */
/*******************************************************************/
//bool Team::FinalizeHistory(void);

/*******************************************************************/
/*                         Private Methods                         */
/*******************************************************************/

/*******************************************************************/
/*                     Team :: GetSeasonIndex                      */
/*  Description: Determine the index associated with a given season*/
/*  Input:  Integer "season": Year                                 */
/*  Output: Unsigned Integer: Value used to index into all arrays  */
/*                                                                 */
/*******************************************************************/
int Team::GetSeasonIndex(int season)
{
    unsigned int i;

    assert(season);
    assert(m_num_seasons);

    for(i = 0; i < m_num_seasons; i++)
        { if(m_seasons[i] == season)    { return(i); } }
    
    return(-1); //Return an error value
}


/*******************************************************************/
/*                     Constructor & Destructor                    */
/*******************************************************************/
Team::Team(const char * name, bool isFBS)
{
    m_name              = new char[strlen(name)];
    m_isFBS             = isFBS;
    m_num_seasons       = 0;
    m_game_it           = 0;
    m_final_score       = 0.0;
    m_num_titles        = 0;
    m_max_num_games     = 0;

    m_seasons           = new int[C_MAX_SEASONS];
    m_num_aa_ps         = new int[C_MAX_SEASONS];
    m_num_games_ps      = new int[C_MAX_SEASONS];
    m_wins_ps           = new int[C_MAX_SEASONS];
    m_losses_ps         = new int[C_MAX_SEASONS];
    m_ties_ps           = new int[C_MAX_SEASONS];
    m_avg_mov_ps        = new double[C_MAX_SEASONS];
    m_winpct_ps         = new double[C_MAX_SEASONS];
    m_opp_winpct_ps     = new double[C_MAX_SEASONS];
    m_o_opp_winpct_ps   = new double[C_MAX_SEASONS];

    m_init_score_ps     = new double[C_MAX_SEASONS];
    m_final_score_ps    = new double[C_MAX_SEASONS];
    m_num_teams_ps      = new int[C_MAX_SEASONS];
    m_init_rank_ps      = new int[C_MAX_SEASONS];
    m_final_rank_ps     = new int[C_MAX_SEASONS];

    m_opp_pg            = (Team **) new void*[C_MAX_SEASONS * C_MAX_GAMES];
    m_location_pg       = new gameLocation[C_MAX_SEASONS * C_MAX_GAMES];
    m_result_pg         = new int[C_MAX_SEASONS * C_MAX_GAMES];

    strcpy(m_name, name);

    memset(m_seasons,           0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_num_aa_ps,         0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_num_games_ps,      0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_wins_ps,           0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_losses_ps,         0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_ties_ps,           0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_avg_mov_ps,        0x00, sizeof(double) * C_MAX_SEASONS);
    memset(m_winpct_ps,         0x00, sizeof(double) * C_MAX_SEASONS);
    memset(m_opp_winpct_ps,     0x00, sizeof(double) * C_MAX_SEASONS);
    memset(m_o_opp_winpct_ps,   0x00, sizeof(double) * C_MAX_SEASONS);
    memset(m_init_score_ps,     0x00, sizeof(double) * C_MAX_SEASONS);
    memset(m_final_score_ps,    0x00, sizeof(double) * C_MAX_SEASONS);
    memset(m_num_teams_ps,      0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_init_rank_ps,      0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_final_rank_ps,     0x00, sizeof(int) * C_MAX_SEASONS);
    memset(m_opp_pg,            0x00, sizeof(void *) * C_MAX_SEASONS * C_MAX_GAMES);
    memset(m_location_pg,       0x00, sizeof(gameLocation) * C_MAX_SEASONS * C_MAX_GAMES);
    memset(m_result_pg,         0x00, sizeof(int) * C_MAX_SEASONS * C_MAX_GAMES);
    /*m_seasons           = NULL;
    m_num_aa_ps         = NULL;
    m_num_games_ps      = NULL;
    m_wins_ps           = NULL;
    m_losses_ps         = NULL;
    m_ties_ps           = NULL;
    m_winpct_ps         = NULL;
    m_opp_winpct_ps     = NULL;
    m_o_opp_winpct_ps   = NULL;

    m_init_score_ps     = NULL;
    m_final_score_ps    = NULL;
    m_init_rank_ps      = NULL;
    m_final_rank_ps     = NULL;

    m_opp_pg            = NULL;
    m_location_pg       = NULL;
    m_result_pg         = NULL;*/
}