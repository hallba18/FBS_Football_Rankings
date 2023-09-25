#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "stdbool.h"

int main(int argc, char * argv[])
{
	char fname[256];
	char oname[256];
	char line[64][64];
	char * categories[] = { "Id","Season","Week","Season Type","Start Date","Completed", 
						    "Neutral Site","Conference Game","Home Team","Home Conference", 
						    "Home Division","Home Points","Away Team","Away Conference", 
						    "Away Division","Away Points" };
	int accFields[64];
	int numCategories = (int) sizeof(categories) / (int) sizeof(char *);
	char tmp;
	bool eol, eoc, eof;
	FILE * fp = NULL;
	FILE * ofp = NULL;
	int year, field, cnt, lineCnt, accFieldCnt;
	if(argc > 1)
	{
		assert(fname);
		assert(oname);
		assert(line);
		strcpy(fname, argv[1]);
		memset(oname, 0x00, sizeof(char) * 256);
		sprintf(oname, "%scumulative.csv", argv[1]);
		ofp = fopen(oname, "w");
		if(ofp)
		{
			for(year = 1983; year < 2023; year++)
			{
				memset(fname, 0x00, sizeof(char) * 256);
				memset(line, 0x00, 64*64*sizeof(char));
				memset(accFields, 0x00, 64*sizeof(int));
				sprintf(fname, "%s%d.csv", argv[1], year);
				printf("%d: %s\n",year, fname);
				fp = fopen(fname, "r");
				if(fp)
				{
					eof = false;
					lineCnt = 0;
					while(!feof(fp))
					{
						eol = false;
						eoc = false;
						accFieldCnt = 0;
						memset(line, 0x00, 64*64*sizeof(char));
                        tmp = fgetc(fp);
                        //Handles any byte order bytes at the beginning of each file
                        while(!feof(fp) && tmp != '"')
                            { tmp = fgetc(fp); }
						for(field = 0; (field < 64 && !eol && !feof(fp)); field++)
						{
							cnt = 0;
							eol = false;
							while(!feof(fp))
							{
								tmp = fgetc(fp);
								if(tmp != '\"' && tmp != ',' && tmp != '\n') 
								{ 
									line[field][cnt] = tmp; 
									cnt++;
								}
								if(tmp == ',')    
                                { 
                                    //if(cnt == 0)    { strcpy(line[field], "false"); }
                                    break; 
                                }
								else if(tmp == '\n' && feof(fp))    { eol = true;    eof = true; }
								else if(tmp == '\n')    { eol = true;    break; }
							}
							if(lineCnt == 0 && accFieldCnt < numCategories && 
							   strcmp(line[field], categories[accFieldCnt]) == 0)
							{
								accFields[accFieldCnt] = field;
								if(year == 1983)
									{ fprintf(ofp, "%s%s", line[field], (eol ? "" : ",")); }
								accFieldCnt++;
							}
							else if(lineCnt != 0 && field == accFields[accFieldCnt])
							{
								eoc = (accFieldCnt == (numCategories - 1));
								fprintf(ofp, "%s%s", line[field], (eoc ? "" : ",")); 
								accFieldCnt++;
							}
						}
						if((year == 1983 || lineCnt != 0) && !feof(fp)) { fprintf(ofp, "\n"); }
						lineCnt++;
					}
					fclose(fp);
				}
				else { printf("FAILURE\n"); }
			}
			fclose(ofp);
		}
	}
	
	//if(fname)
	//	{ free(fname);    fname = NULL; }
	//if(oname)
	//	{ free(oname);    oname = NULL;}
	//if(line)
	//	{ free(line);    line = NULL;}
}