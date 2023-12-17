#include "watch.h"

typedef struct Lcg
{
    long long z;
    long long modulus;
    long long multiplier;
    long long increment;
} Lcg;

typedef struct Time
{
    int hour;
    int minute;
    int second;
} Time;

double nextLcgValue(Lcg *lcg);
Lcg createLcg(long long seed, long long modulus, long long multiplier, long long increment);
void getSeedsFromDate(watch_date_time date, long long *minuteSeed, long long *hourSeed);
void getSequenceFromLcg(Lcg lcg, int length, int *sequence);
Time date_to_flowtime(watch_date_time date);
