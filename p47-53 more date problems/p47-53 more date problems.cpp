#include <iostream>
#include <ctime>
using namespace std;





struct stDate
{
    short day;
    short month;
    short year;
};

bool isLeapYear(short year)
{
    return (year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0)));
}

short numberOfDaysInMonth(short year, short month)
{
    if (month == 2)
    {
        if (isLeapYear(year))
            return  29;
        else
            return  28;
    }

    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return  31;

    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    else
        return 0;
}

short numberOfDaysInYear(short year)
{
    return isLeapYear(year) ? 366 : 365;
}

short orderOfDay(short year, short month, short day)
{
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a) - 2;

    return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short orderOfDay(stDate Date)
{
    return orderOfDay(Date.year, Date.month, Date.day);
}

string nameOfDay(short order)
{
    if (order == 0)
        return "Sun";

    else if (order == 1)
        return "Mon";

    else if (order == 2)
        return "Tue";

    else if (order == 3)
        return "Wed";

    else if (order == 4)
        return "Thur";

    else if (order == 5)
        return "Fri";

    else if (order == 6)
        return "Sat";
    else
        return "Wrong day input";
}

stDate getSysytemDate()
{
    stDate sysDate;

    time_t t = time(0);
    tm* now = localtime(&t);

    sysDate.year = now->tm_year + 1900;
    sysDate.month = now->tm_mon + 1;
    sysDate.day = now->tm_mday;
   
    return sysDate;
    
}

bool isEndOfWeek(stDate Date)
{
    return orderOfDay(Date) == 6;
}

bool isWeekEnd(stDate Date)
{
    short dayOrder = orderOfDay(Date);
    return dayOrder == 5 || dayOrder == 6;
}

bool isBusinessDay(stDate Date)
{
    return !isWeekEnd(Date);
}

short daysUntillTheEndOfWeek(stDate Date)//   23/9/2022
{
    return 6 - orderOfDay(Date);
}

int dateDiff(stDate Date1, stDate Date2, bool isIncludeEndDay = false)
{
    int numberOfDays = 0;

    for (short year = Date1.year; year < Date2.year; year++)
        numberOfDays += numberOfDaysInYear(year);

    if (Date1.year == Date2.year)
    {
        for (short month = Date1.month; month < Date2.month; month++)
            numberOfDays += numberOfDaysInMonth(Date1.year, month);
    }

    numberOfDays += Date2.day - Date1.day;

    return (isIncludeEndDay) ? ++numberOfDays : numberOfDays;
}

short daysFromBeginningOfYear(short year, short month, short day)
{
    short numberOfDays = 0;

    for (short mon = 1; mon < month; mon++)
    {
        numberOfDays += numberOfDaysInMonth(year, mon);
    }
    numberOfDays += day;

    return numberOfDays;
}

short daysUntillTheEndOfMonth(stDate Date)//   23/9/2022
{
    stDate DateOfEndOfYear;
    
    DateOfEndOfYear.day = numberOfDaysInMonth(Date.year, Date.month);
    DateOfEndOfYear.month = Date.month;
    DateOfEndOfYear.year = Date.year;

    return dateDiff(Date, DateOfEndOfYear, 1);
    //return (numberOfDaysInMonth(Date.year, Date.month) - Date.day)+1;
}

short daysUntillTheEndOfYear(stDate Date)//   23/9/2022
{
    //short daysOfTodayDate = daysFromBeginningOfYear(Date.year, Date.month, Date.day);
    //return (numberOfDaysInYear(Date.year) - daysOfTodayDate)+1;

    stDate DateOfEndOfYear;

    DateOfEndOfYear.day = 31;
    DateOfEndOfYear.month = 12;
    DateOfEndOfYear.year = Date.year;

    return dateDiff(Date, DateOfEndOfYear, 1);
}





int main()
{
    stDate sysDate;

    //sysDate = getSysytemDate();
    
    sysDate.day = 27;
    sysDate.month = 9;
    sysDate.year = 2022;


    cout << "Today is: ";
    cout << nameOfDay(orderOfDay(sysDate)) << " , ";
    cout << sysDate.day << "/" << sysDate.month << "/" << sysDate.year << "\n";
    

    cout << "\nIs it End of Week?\n";
    isEndOfWeek(sysDate) ? cout << "Yes it is Saturday, It`s end Of Week\n" : cout << "No, Not end of Week\n";

    cout << "\nIs it Weekend?\n";
    isWeekEnd(sysDate) ? cout << "Yes it is a WeekEnd\n" : cout << "No, today is: "<< nameOfDay(orderOfDay(sysDate)) <<", Not a Weekend\n";

    cout << "\nIs it Business Day?\n";
    isBusinessDay(sysDate) ? cout << "Yes it is a Business Day\n\n" : cout << "No, it is Not a Business Day\n\n";

    cout << "Days untill end of week: ";
    cout << daysUntillTheEndOfWeek(sysDate) << " Day(s)\n";

    cout << "Days untill end of month: ";
    cout << daysUntillTheEndOfMonth(sysDate) << " Day(s)\n";

    cout << "Days untill end of year: ";
    cout << daysUntillTheEndOfYear(sysDate) << " Day(s)\n";






    system("pause>0");
    return main();
}
//stDate Date1, Date2;
    //cout << "\nPlease Enter your date1\n\n";
    //Date1 = readStDate();
    //cout << "\n Date After \n";
    //Date2 = decreaseDateByOneDay(Date1);
    //cout << "01- decrease One day is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    //Date2 = decreaseDateByXDays(Date2, 10);
    //cout << "02- decrease 10 days is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByOneWeek(Date2);
    //cout << "03- decrease One week is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByXWeeks(Date2, 10);
    //cout << "04- decrease Ten weeks is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    //Date2 = decreaseDateByOneMonth(Date2);
    //cout << "05- decrease One Month is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByXMonths(Date2, 5);
    //cout << "06- decrease Five Months is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByOneYear(Date2);
    //cout << "07- decrease One Year is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByXYears(Date2, 10);
    //cout << "08- decrease Ten Years is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByXYearsFaster(Date2, 10);
    //cout << "08- decrease Ten Years (faster) is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    ////
    //Date2 = decreaseDateByOneDecade(Date2);
    //cout << "10- decrease One Decade is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    //Date2 = decreaseDateByXDecades(Date2, 10);
    //cout << "11- decrease Ten Decades is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    //Date2 = decreaseDateByXDecadesFaster(Date2, 10);
    //cout << "09- decrease Ten Decades (faster) is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    //Date2 = decreaseDateByOneCentury(Date2);
    //cout << "13- decrease One Century is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;
    //Date2 = decreaseDateByOneMilinium(Date2);
    //cout << "14- decrease One Melinium is: " << Date2.day << "/" << Date2.month << "/" << Date2.year << endl;