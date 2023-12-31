#ifndef TEAM_H
#define TEAM_H

class Team
{
    const int C_MAX_SEASONS     = 40;
    const int C_MAX_GAMES       = 15;

	public:
        enum gameLocation
        {
            AWAY = -1,
            NEUTRAL,
            HOME
        };

        ~Team(void);
		static Team * Create(const char * name, bool isFBS);

        //Get functions for private members
        void PrintTeam(void);
        bool GetIsFBS(void);
        unsigned int GetLatestSeason(void);
        double GetWinPct(int season);
        double GetOppWinPct(int season);
        double GetInitialScore(int season);
        double GetFinalScore(int season);
        int GetInitialRank(int season);
        int GetFinalRank(int season);

        //Add functions
        bool AddGameCount(int season);
        bool AddGameResult(int season, Team * opponent, 
                int score, gameLocation location);
        void SetInitialRank(int season, int rank, int num_teams);
        bool AddSeasonResult(int season, int num_AA, bool claimed_NT);

        //Finalize Functions
        bool CalcWinPcts(void);
        bool CalcOppWinPcts(void);
        bool CalcOppOppWinPcts(void);
        bool CalcInitialScores(void);
        bool CalcFinalScores(void);
        //bool FinalizeSeason(int season);
        //bool FinalizeHistory(void);

	private:
        //Historical Statistics Members
		char * m_name;                  //School name
        bool m_isFBS;
		unsigned int m_num_seasons;     //Number of season in FBS
        unsigned int m_game_it;         //Iterator for games in a season
		double m_final_score;           //Final historical score for school
		int m_num_titles;               //Number of National Titles won
        int m_max_num_games;

        //Per-Season (ps) Statistics Members
		int * m_seasons;                //List of seasons played
		int * m_num_aa_ps;              //Number of All-Americans each season
		int * m_num_games_ps;           //Number of games played each season
		int * m_wins_ps;                //Number of wins each season
		int * m_losses_ps;              //Number of losses each season
		int * m_ties_ps;                //Number of ties each season
        double * m_avg_mov_ps;
        double * m_winpct_ps;           //Team win percentage each season
		double * m_opp_winpct_ps;       //Opponent win percentage each season
		double * m_o_opp_winpct_ps;     //Opponent's Opp. win pct. each season

        //Per-Season (ps) Score Members
        double * m_init_score_ps;       //Initial ranking score per season
        double * m_final_score_ps;      //Final score per season
        int * m_num_teams_ps;           //Number of teams in a season
        int * m_init_rank_ps;           //Intial ranking per season
        int * m_final_rank_ps;          //Final ranking per season

        //Per-Game (pg) Members
		Team ** m_opp_pg;               //Pointer to opponent teams each season
        gameLocation * m_location_pg;   //List of game locations each season
        int * m_result_pg;              //List of game results each season

        //Private Methods
        Team(const char * name, bool isFBS);
        int GetSeasonIndex(int season);
};

#endif //TEAM_H