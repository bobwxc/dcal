/*
Copyright (c) [2020] [bobwxc]
[dt] is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.

gcc -O3 dt.c -o dt
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <regex.h>
#include <unistd.h>

int test(char p[])
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[i] < 48 || p[i] > 57)
        {
            return 1;
        }
    }
    if (p[4] != '-')
    {
        return 1;
    }

    for (i = 5; i < 7; i++)
    {
        if (p[i] < 48 || p[i] > 57)
        {
            return 1;
        }
    }
    if (p[7] != '-')
    {
        return 1;
    }
    for (i = 8; i < 10; i++)
    {
        if (p[i] < 48 || p[i] > 57)
        {
            return 1;
        }
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

    return 0;
}

int large(char p[], char pp[])
{
    int year, year_, month, month_, day, day_;

    year = (p[0] - '0') * 1000 + (p[1] - '0') * 100 + (p[2] - '0') * 10 + (p[3] - '0');
    month = (p[5] - '0') * 10 + (p[6] - '0');
    day = (p[8] - '0') * 10 + (p[9] - '0');

    year_ = (pp[0] - '0') * 1000 + (pp[1] - '0') * 100 + (pp[2] - '0') * 10 + (pp[3] - '0');
    month_ = (pp[5] - '0') * 10 + (pp[6] - '0');
    day_ = (pp[8] - '0') * 10 + (pp[9] - '0');

    // printf("%d %d %d %d %d %d \n", year, year_, month, month_, day, day_);
    if (year < year_)
    {
        return 1;
    }
    else if (year == year_ && month < month_)
    {
        return 1;
    }
    else if (year == year_ && month == month_ && day < day_)
    {
        return 1;
    }

    return 0;
}

int years;
int months;
int total_days;

int cacu(char p[], char pp[])
{
    int year, year_, month, month_, day, day_;

    year = (p[0] - '0') * 1000 + (p[1] - '0') * 100 + (p[2] - '0') * 10 + (p[3] - '0');
    month = (p[5] - '0') * 10 + (p[6] - '0');
    day = (p[8] - '0') * 10 + (p[9] - '0');

    year_ = (pp[0] - '0') * 1000 + (pp[1] - '0') * 100 + (pp[2] - '0') * 10 + (pp[3] - '0');
    month_ = (pp[5] - '0') * 10 + (pp[6] - '0');
    day_ = (pp[8] - '0') * 10 + (pp[9] - '0');
    // printf("%d %d %d %d %d %d \n", year, year_, month, month_, day, day_);
    int y2, m2, d2;
    int y1, m1, d1;

    m1 = (month_ + 9) % 12;
    y1 = year_ - m1 / 10;
    d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (day_ - 1);

    m2 = (month + 9) % 12;
    y2 = year - m2 / 10;
    d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (day - 1);

    // printf("About: %d year(s) %d month(s)\n", ((year - year_ - 1) * 12 + (12 - month) + month_) / 12, ((year - year_ - 1) * 12 + (12 - month) + month_) % 12);

    /*
    * problem code, no use
    * years = ((year - year_ - 1) * 12 + (12 - month) + month_) / 12;
    * months = ((year - year_ - 1) * 12 + (12 - month) + month_) % 12;
    */

    years = y2 - y1;
    months = m2 - m1;
    if (months < 0)
    {
        years -= 1;
        months = 12 + months;
    }

    total_days = d2 - d1;

    return (d2 - d1);
}

int main(int argc, char *argv[])
{
    char p[] = "1971*01*01", pp[] = "2050*01*01";
    int output_style = 0; //0 normal 1 only days 2 json
    int argc_num = 1;

    int fd[2];
    char *msg;
    if(pipe(fd)!=0)
    {
    	return 1;
	}
    read(fd[0],msg,1024);
    close(fd[0]);
    printf("%s",msg);

    // printf("%d %s %s",argc,argv[0],argv[1]);
    if (argc == 1)
    {
        printf("\33[;31;1mdt\33[1m");
        printf("\33[0m  first_date second_date\n    -h for help\n    -v for version\33[0m\n");
        return 0;
    }

    if (strcmp(argv[argc_num], "-h") == 0)
    {
        printf("\33[;31;1mdt\33[1m");
        printf("\33[0m  first_date second_date\n    -h for help\n    -v for version\n    -s only simple days\n    -j json style output\33[0m\n");
        return 0;
    }
    if (strcmp(argv[argc_num], "-v") == 0)
    {
        printf("\33[;31;1mdt\33[1m");
        printf("\33[0m version v0.3\33[0m\n");
        return 0;
    }
    if (strcmp(argv[argc_num], "-s") == 0)
    {
        output_style = 1;
        argc_num += 1;
        if (argc_num >= argc)
        {
            printf("\33[;31;1merror\33[1m\n");
            return 0;
        }
    }
    if (strcmp(argv[argc_num], "-j") == 0)
    {
        output_style = 2;
        argc_num += 1;
        if (argc_num >= argc)
        {
            printf("\33[;31;1merror\33[1m\n");
            return 0;
        }
    }

    if (test(argv[argc_num]) == 0)
    {
        strcpy(p, argv[argc_num]);
    }
    else
    {
        do
        {
            printf("first date(yyyy-mm-dd): ");
            scanf("%s", p);

        } while (test(p) != 0);
    }

    if (test(p) == 0)
    {
        argc_num += 1;
        if (argc_num > argc)
        {
            printf("\33[;31;1merror\33[1m\n");
            return 0;
        }

        if (test(argv[argc_num]) == 0)
        {
            strcpy(pp, argv[argc_num]);
        }
        else
        {
            do
            {
                printf("second date(yyyy-mm-dd): ");
                scanf("%s", pp);

            } while (test(pp) != 0);
        }
    }

    if (test(p) == 0 && test(pp) == 0)
    {
        //p always keep >= ppp
        if (large(p, pp) == 1)
        {
            char ppp[] = "2050*01*01";
            strcpy(ppp, p);
            strcpy(p, pp);
            strcpy(pp, ppp);
        }

        cacu(p, pp);
        if (output_style == 0)
        {
            printf("---------------------------\n");
            printf("(%s) - (%s) \n", pp, p);
            printf("---------------------------\n");
            // printf("total days: %d\n", cacu(p, pp));
            printf("About: \33[;31;1m%d\33[0m year(s) \33[;31;1m%d\33[0m month(s)\n", years, months);
            printf("total days: \33[;31;1m%d\33[0m\n", total_days);
        }
        else if (output_style == 1)
        {
            printf("%d\n", total_days);
        }
        else if (output_style == 2)
        {
            printf("{\"start_date\": \"%s\", \"end_date\": \"%s\", \"about\": {\"years\": %d, \"months\": %d}, \"total_days\": %d}\n", pp, p, years, months, total_days);
        }
    }

    return 0;
}