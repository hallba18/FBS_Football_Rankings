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

#### Intra-Season Rankings:
Rankings within a season is split into two parts. The first part is an initial
ranking system that uses the cumulative margin of victory (MoV) for a team and
their strength of schedule (SoS) for that season. The second part is to scale
the results of each game based on location of the game, results, and initial
rank of the opponent. This creates a score that rates how positive or negative
that game's result has on the team's season.

##### Initial Ranking
*O = Average Opponent Win Percentage*  
*O<sub>2</sub> = Average Opponent's Opponent Win Percentage*  
*MoV = Average Margin of Victory*  
<img src="http://www.sciweavers.org/tex2img.php?eq=%5C%5BInitial%5C%3BRanking%5C%3BScore%3DMoV%5C%3A%5Cfrac%7B%282%5C%2CO%29%2BO_2%7D%7B3%7D%5C%5D&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="\[Initial\;Ranking\;Score=MoV\:\frac{(2\,O)+O_2}{3}\]" width="331" height="43" />

<img src="https://latex.codecogs.com/svg.latex?\Large&space;Initial\,Ranking\,Score=MoV\,\frac{(2O)+O_2}{3}" title="\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" />
