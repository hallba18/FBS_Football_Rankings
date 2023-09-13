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
		Team * Create(char * name);
        //Get functions for private members
        double GetWinPct(int season);
        double GetOppWinPct(int season);
        double GetInitialRanking(int season);

        //Add functions
        bool AddGameResult(int season, const Team * const opponent, 
                int score, int location, bool isNT);
        bool AddSeasonResult(int season, );

        //Finalize Functions
        bool FinalizeSeason(int season);
        bool FinalizeHistory(void);

	private:
        //Historical Statistics Members
		char * m_name;                  //School name
		int m_num_seasons;              //Number of season in FBS
		double m_final_score;           //Final historical score for school
		int m_num_titles;               //Number of National Titles won

        //Per-Season (ps) Statistics Members
		int * m_seasons;                //List of seasons played
		int * m_num_aa_ps;              //Number of All-Americans each season
		int * m_num_games_ps;           //Number of games played each season
		int * m_wins_ps;                //Number of wins each season
		int * m_losses_ps;              //Number of losses each season
		int * m_ties_ps;                //Number of ties each season
        double * m_winpct_ps;           //Team win percentage each season
		double * m_owp_ps;              //Opponent win percentage each season
		double * m_oowp_ps;             //Opponent's Opp. win pct. each season

        //Per-Season (ps) Score Members
        double * m_init_score_ps;       //Initial ranking score per season
        double * m_final_score_ps;      //Final score per season

        //Per-Game (pg) Members
		Team ** * m_opp_pg;             //Pointer to opponent teams each season
        gameLocation ** m_location_pg;  //List of game locations each season
        int ** m_result_pg;             //List of game results each season

        //Private Methods
        Team(char * name);
        ~Team(void);
}
