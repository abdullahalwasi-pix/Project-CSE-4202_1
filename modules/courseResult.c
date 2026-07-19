#include <stdio.h>
#include <string.h>
#include "courseResult.h"

Course nullCourse = {
    "NULL",
    "NULL",
    0.0,
    0
};

CourseResult createCompletedCourseResult(
    Course *course,
    double marks
)
{
    CourseResult result;

    result.course = course;
    result.marks = marks;
    result.completed = 1;

    return result;
}

CourseResult createIncompleteCourseResult(
    Course *course
)
{
    CourseResult result;

    result.course = course;
    result.marks = 0.0;
    result.completed = 0;

    return result;
}

void sortCourseResultsBySemester(
    CourseResult results[],
    int n_results
)
{
    for (int i = 0; i < n_results - 1; i++)
    {
        int selected = i;

        for (int j = i + 1; j < n_results; j++)
        {
            if (
                results[j].course->semester <
                results[selected].course->semester
            )
            {
                selected = j;
            }
        }

        if (selected != i)
        {
            CourseResult temporary = results[i];
            results[i] = results[selected];
            results[selected] = temporary;
        }
    }
}

static int lowerBound(
    CourseResult results[],
    int n_results,
    int semester
)
{
    int left = 0;
    int right = n_results - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (results[middle].course->semester >= semester)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }

    return left;
}

static int upperBound(
    CourseResult results[],
    int n_results,
    int semester
)
{
    int left = 0;
    int right = n_results - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (results[middle].course->semester > semester)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }

    return left;
}

void filterCourseResultsBySemester(
    CourseResult results[],
    int n_results,
    int semester,
    CourseResult filtered[]
)
{
    int start = lowerBound(
        results,
        n_results,
        semester
    );

    int finish = upperBound(
        results,
        n_results,
        semester
    );

    int count = 0;

    for (int i = start; i < finish; i++)
    {
        filtered[count] = results[i];
        count++;
    }

    filtered[count] =
        createCompletedCourseResult(
            &nullCourse,
            0.0
        );
}

int countCourseResultsBeforeNull(
    CourseResult results[],
    int n_results
)
{
    int count = 0;

    while (count < n_results)
    {
        if (strcmp(
                results[count].course->code,
                null_course_code
            ) == 0)
        {
            return count;
        }

        count++;
    }

    return count;
}

void viewCourseResult(CourseResult result)
{
    printf(
        "%s: %s\t\t [Credit: %.1f]\n",
        result.course->code,
        result.course->name,
        result.course->credit
    );

    if (!result.completed)
    {
        printf("Incomplete\n");
        return;
    }

    printf("Marks: %.2f\n", result.marks);
}