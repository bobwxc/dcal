/*
   Copyright (c) [2020] [bobwxc]
   [dcal] is licensed under Mulan PSL v2.
   You can use this software according to the terms and conditions of the Mulan PSL v2.
   You may obtain a copy of Mulan PSL v2 at:
           http://license.coscl.org.cn/MulanPSL2
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
   EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
   MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
   See the Mulan PSL v2 for more details.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <unistd.h>

struct date_
{
	int year;
	int month;
	int day;	
	char str[15];
};

struct date_ date0, date1,result;


int test(char p[])
{
	char *regex = "^[0-9][0-9][0-9][0-9]-[0-2][0-9]-[0-3][0-9]$";
	regex_t comment;
	regcomp(&comment, regex, REG_EXTENDED|REG_NEWLINE);
	size_t nmatch=1;
	regmatch_t regmatch[24];
	int res = regexec(&comment,p,nmatch,regmatch,0);

	if(res!=0)
	{
		return 1;
	}

	int year, month, day;

	year = (p[0] - '0') * 1000 + (p[1] - '0') * 100 + (p[2] - '0') * 10 + (p[3] - '0');
	month = (p[5] - '0') * 10 + (p[6] - '0');
	day = (p[8] - '0') * 10 + (p[9] - '0');
	if (month < 1 || month > 12)
	{
		return 1;
	}
	if (day < 1 || day > 30)
	{
		return 1;
	}
	if (year % 4 == 0 && year % 400 != 0 && month == 2 && day > 29)
	{
		return 1;
	}
	else if (month == 2 && day > 28)
	{
		return 1;
	}
	if(date0.year==0&&date0.month==0&&date0.day==0)
	{
		date0.year=year;
		date0.month=month;
		date0.day=day;
		strcpy(date0.str,p);
		//printf("%d %d %d",date0.year,date0.month,date0.day);
	}else{
		date1.year=year;
		date1.month=month;
		date1.day=day;
		strcpy(date1.str,p);
		//printf("%d %d %d",date1.year,date1.month,date1.day);
	}
	return 0;
}

int large()
{
	int year, year_, month, month_, day, day_;
	int flag=0;

	year = date0.year;
	month = date0.month;
	day = date0.day;
	year_ = date1.year;
	month_ = date1.month;
	day_ = date1.day;

	if (year < year_)
	{
		flag=1;
	}
	else if (year == year_ && month < month_)
	{
		flag=1;
	}
	else if (year == year_ && month == month_ && day < day_)
	{
		flag=1;
	}

	if(flag==1)
	{
		struct date_ c;
		c=date0;
		date0=date1;
		date1=c;
	}

	return flag;
}

int cacu()
{
	int year, year_, month, month_, day, day_;

	year = date0.year;
	month = date0.month;
	day = date0.day;
	year_ = date1.year;
	month_ = date1.month;
	day_ = date1.day;

	int y2, m2, d2;
	int y1, m1, d1;

	m1 = (month_ + 9) % 12;
	y1 = year_ - m1 / 10;
	d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (day_ - 1);

	m2 = (month + 9) % 12;
	y2 = year - m2 / 10;
	d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (day - 1);

	result.year = y2 - y1;
	result.month = m2 - m1;

	if (result.month < 0)
	{
		result.year -= 1;
		result.month = 12 + result.month;
	}
	result.day = d2 - d1;

	return result.day;
}

int main(int argc, char *argv[])
{
	char p[] = "1971*01*01", pp[] = "2050*01*01";
	int output_style = 0; //0 normal 1 only days 2 json

	date0.year=0;
	date0.month=0;
	date0.day=0;
	date1.year=0;
	date1.month=0;
	date1.day=0;

	if (argc == 1)
	{
		printf("\33[;31;1mdt\33[1m");
		printf("\33[0m  first_date second_date\n    -h for help\n    -v for version\33[0m\n");
		return 0;
	}

	int opt;
	char *optstring="hvfsj";
	while((opt=getopt(argc,argv,optstring))!=-1)
	{
		if(opt=='h')
		{
			printf("\33[;31;1mdt\33[1m");
			printf("\33[0m  first_date second_date\n    -h for help\n    -v for version\n    -f full human read\n    -s only simple days\n    -j json style output\33[0m\n");
			return 0;
		}
		if(opt=='v')
		{
			printf("\33[;31;1mdt\33[1m");
			printf("\33[0m version v0.6.0\33[0m\n");
			return 0;
		}
		if(opt=='f')
		{
			output_style = 1;
		}
		if(opt=='s')
		{
			output_style = 2;
		}
		if(opt=='j')
		{
			output_style = 3;
		}
	}


	for(int i=0;i<argc;i++)
	{
		test(argv[i]);
	}

	if(date1.year==0&&date1.month==0&&date1.day==0)
	{
		printf("Input date error!\n");
		return 1;
	}else{
		large();
		cacu();

		if (output_style == 0)
		{
			printf("Year(s) Month(s) Day(s)\n", result.year, result.month);
			printf("%d %d %d\n", result.year, result.month, result.day);
		}
		else if (output_style == 1)
		{
			printf("---------------------------\n");
			printf("(%s) - (%s) \n", date0.str, date0.str);
			printf("---------------------------\n");
			printf("About: \33[;31;1m%d\33[0m year(s) \33[;31;1m%d\33[0m month(s)\n", result.year, result.month);
			printf("Total days: \33[;31;1m%d\33[0m\n", result.day);
		}
		else if (output_style == 2)
		{
			printf("%d\n", result.day);
		}
		else if (output_style == 3)
		{
			printf("{\"start_date\": \"%s\", \"end_date\": \"%s\", \"about\": {\"years\": %d, \"months\": %d}, \"total_days\": %d}\n", date0.str, date0.str, result.year, result.month, result.day);
		}
	}

	return 0;
}
