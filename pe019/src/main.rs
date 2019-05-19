const DAYS_IN_WEEK: i32 = 7;

#[derive(PartialEq)]
enum Month {
    Jan,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec,
}

struct Date {
    day_of_month: i32,
    day_of_week: i32,
    month: Month,
    year: i32,
}

fn is_leap_year(date: &Date) -> bool {
    let year = date.year;
    (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))
}

fn days_of_month(date: &Date) -> i32 {
    let month = &date.month;
    match month {
        Month::Jan => 31,
        Month::Feb => {
            if is_leap_year(date) {
                29
            } else {
                28
            }
        }
        Month::Mar => 31,
        Month::Apr => 30,
        Month::May => 31,
        Month::Jun => 30,
        Month::Jul => 31,
        Month::Aug => 31,
        Month::Sep => 30,
        Month::Oct => 31,
        Month::Nov => 30,
        Month::Dec => 31,
    }
}

// Wow I reinvented the finite field
fn next_month(month: &Month) -> Month {
    match month {
        Month::Jan => Month::Feb,
        Month::Feb => Month::Mar,
        Month::Mar => Month::Apr,
        Month::Apr => Month::May,
        Month::May => Month::Jun,
        Month::Jun => Month::Jul,
        Month::Jul => Month::Aug,
        Month::Aug => Month::Sep,
        Month::Sep => Month::Oct,
        Month::Oct => Month::Nov,
        Month::Nov => Month::Dec,
        Month::Dec => Month::Jan,
    }
}

// Advances the date to the first of the next month
fn month_succesor(date: &Date) -> Date {
    let days_in_this_month = days_of_month(date);
    let days_to_advance_month = days_in_this_month - date.day_of_month + 1;
    let first_of_next_month_day = (date.day_of_week + days_to_advance_month) % DAYS_IN_WEEK;
    let next_month = next_month(&date.month);

    let year = if next_month == Month::Jan {
        date.year + 1
    } else {
        date.year
    };

    Date {
        day_of_month: 1,
        day_of_week: first_of_next_month_day,
        month: next_month,
        year: year,
    }
}

fn main() {
    let initial_date = Date {
        day_of_month: 1,
        day_of_week: 1,
        month: Month::Jan,
        year: 1900,
    };
    let mut century_begin = initial_date;
    while century_begin.year < 1901 {
        century_begin = month_succesor(&century_begin);
    }

    let mut first_sundays = 0;
    let mut iter = century_begin;
    while iter.year < 2001 {
        if iter.day_of_week == 6 {
            first_sundays += 1;
        }
        iter = month_succesor(&iter);
    }

    println!("First Sundays: {}", first_sundays);
}
