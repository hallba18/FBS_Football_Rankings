#ifndef RANKING_H
#define RANKING_H

class Team; //Forward declare Team

int main(int argc, char ** argv);

class gameResult
{
    public:
        void reset(void);
        void addTeam(Team * team, bool isHome);
        void newResult(unsigned int season, bool isNeutral,
                unsigned int hScore, unsigned int aScore);
        bool storeResults(void);
        gameResult(void);
        ~gameResult(void);

    private:
        unsigned int m_season;
        bool m_isNeutral;
        Team * m_home;
        Team * m_away;
        unsigned int m_hScore;
        unsigned int m_aScore;
};

#endif //RANKING_H