class Team
{
    const int C_MAX_SEASONS = 40;

    enum gameLocation
    {
        AWAY = -1,
        NEUTRAL,
        HOME
    };

	public:
		Team * Create(char * name);


        //Get functions for private members
        double GetWinPct(int season);
        double GetOppWinPct(int season);
        double GetInitialScore(int season);
        double GetFinalScore(int season);
        int GetInitialRank(int season);
        int GetFinalRank(int season);

        //Add functions
        bool AddGameResult(int season, const Team * const opponent, 
                int score, gameLocation location);
        bool AddSeasonResult(int season, int num_AA, bool claimed_NT);

        //Finalize Functions
        bool CalcWinPct(int season);
        bool CalcOppWinPct(int season);
        //bool FinalizeSeason(int season);
        //bool FinalizeHistory(void);

	private:
        //Historical Statistics Members
		char * m_name;                  //School name
		unsigned int m_num_seasons;     //Number of season in FBS
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
		double * m_opp_winpct_ps;       //Opponent win percentage each season
		double * m_o_opp_winpct_ps;     //Opponent's Opp. win pct. each season

        //Per-Season (ps) Score Members
        double * m_init_score_ps;       //Initial ranking score per season
        double * m_final_score_ps;      //Final score per season
        int * m_init_rank_ps;           //Intial ranking per season
        int * m_final_rank_ps;          //Final ranking per season

        //Per-Game (pg) Members
		Team ** * m_opp_pg;             //Pointer to opponent teams each season
        gameLocation ** m_location_pg;  //List of game locations each season
        int ** m_result_pg;             //List of game results each season

        //Private Methods
        Team(char * name);
        bool CalcOppOppWinPct(int season);
        bool CalcInitialScore(int season);
        bool CalcFinalScore(int season);
        int GetSeasonIndex(int season);
        ~Team(void);
};
