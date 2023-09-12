# FBS College Football Historical Ranking System
Ranking FBS college football programs. Historical data coallated by those at
https://collegefootballdata.com also at https://github.com/cfbd

This repository is not just for the development of the ranking code, but the
refinement of the model itself.

### Goal:
Provide a mathematical basis for comparing the historical success of  different
college football programs. This model is designed to prioritize teams that have
spent more years in FBS football division. The historical success of a program
is determined by the sum of how successful each individual season in addition to
factors such as the number of national championships and records in New Years
Six Bowl games and Non-NY6 bowl games.

#### Season Ranking Model:
Rankings within a season is split into two parts. The first part is an initial
ranking system that uses the cumulative margin of victory (MoV) for a team and
their strength of schedule (SoS) for that season. The second part is to scale
the results of each game based on location of the game, results, and initial
rank of the opponent. This creates a score that rates how positive or negative
that game's result has on the team's season. Specifics for the model are located
in the **FBS_Football_Rankings.pdf**. 
