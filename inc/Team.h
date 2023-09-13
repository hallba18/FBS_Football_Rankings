#include "Season.h"

public class Team
{
    enum gameLocation
    {
        HOME,
        NEUTRAL,
        AWAY
    };

	public:
        double GetWinPct(int season);
        double GetOppWinPct(int season);
        bool AddGameResult(int season, const Team * const opponent, 
                int score, int location, bool isNT);
        bool AddSeasonResult(int season, );
		Team * Create(int num_seasons, char * name);

	private:
        //Historical Statistics Members
		char * m_name;                  //School name
		char * m_alias;                 //Alias for school ex. TCU
		int m_num_seasons;              //Number of season in FBS
        double m_init_score;            //Initial score for ranking teams
		double m_final_score;           //Final historical score for school
		int m_num_titles;               //Number of National Titles won

        //Per-Season (ps) Statistics Members
		int m_seasons[];                //List of seasons played
		int m_num_aa_ps[];              //Number of All-Americans each season
		int m_num_games_ps[];           //Number of games played each season
		int m_wins_ps[];                //Number of wins each season
		int m_losses_ps[];              //Number of losses each season
		int m_ties_ps[];                //Number of ties each season
        double m_winpct_ps[];           //Team win percentage each season
		double m_owp_ps[];              //Opponent win percentage each season
		double m_oowp_ps[];             //Opponent's Opponent win percentage each season

        //Season specific members
		Team * m_opp_ps[][];            //Pointer to opponent teams each season
        gameLocation m_locations[][];   //List of game locations each season
        int m_results[][];              //List of game results each season

        //Private Methods
		Team * Create_this(int num_seasons, char * name);
        Team(int num_seasons, char * name);
        ~Team(void);
}
