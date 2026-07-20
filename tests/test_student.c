#include <stdio.h>
#include <string.h>

#include "course.h"
#include "courseResult.h"
#include "student.h"

int testStudentId()
{
    Student student =
        createStudent(
            "240041001",
            "Alice"
        );

    return strcmp(
        student.id,
        "240041001"
    ) == 0;
}

int testStudentName()
{
    Student student =
        createStudent(
            "240041001",
            "Alice"
        );

    return strcmp(
        student.name,
        "Alice"
    ) == 0;
}

int testStudentInitialCGPA()
{
    Student student =
        createStudent(
            "240041001",
            "Alice"
        );

    return student.cgpa == 0.0;
}

int testAddCourseResultUpdatesCGPA()
{
    Course course =
        createCourse(
            "CSE 4107",
            "Structured Programming I",
            3.0,
            1
        );

    Student student =
        createStudent(
            "240041001",
            "Alice"
        );

    CourseResult result =
        createCompletedCourseResult(
            &course,
            252
        );

    addCourseResultToStudent(
        &student,
        result
    );

    return student.cgpa == 4.00;
}

int testHighestCGPAStudentComesFirst()
{
    Student students[3] = {
        createStudent(
            "240041001",
            "Alice"
        ),
        createStudent(
            "240041002",
            "Bob"
        ),
        createStudent(
            "240041003",
            "Carol"
        )
    };

    students[0].cgpa = 3.25;
    students[1].cgpa = 4.00;
    students[2].cgpa = 3.75;

    sortStudentsByCGPA(
        students,
        3
    );

    return strcmp(
        students[0].id,
        "240041002"
    ) == 0;
}

int testRankingReordersStudents()
{
    Student students[3] = {
        createStudent(
            "240041001",
            "Alice"
        ),
        createStudent(
            "240041002",
            "Bob"
        ),
        createStudent(
            "240041003",
            "Carol"
        )
    };

    students[0].cgpa = 3.25;
    students[1].cgpa = 4.00;
    students[2].cgpa = 3.75;

    sortStudentsByCGPA(
        students,
        3
    );

    return
        strcmp(
            students[0].id,
            "240041002"
        ) == 0
        &&
        strcmp(
            students[1].id,
            "240041003"
        ) == 0
        &&
        strcmp(
            students[2].id,
            "240041001"
        ) == 0;
}

int main()
{
    printf("Student module tests\n");

    int passed = 0;
    int total = 0;

    total++;
    if (testStudentId())
    {
        passed++;
    }

    total++;
    if (testStudentName())
    {
        passed++;
    }

    total++;
    if (testStudentInitialCGPA())
    {
        passed++;
    }

    total++;
    if (testAddCourseResultUpdatesCGPA())
    {
        passed++;
    }

    total++;
    if (testHighestCGPAStudentComesFirst())
    {
        passed++;
    }

    total++;
    if (testRankingReordersStudents())
    {
        passed++;
    }

    printf(
        "Passed %d/%d tests\n",
        passed,
        total
    );

    if (passed == total)
    {
        return 0;
    }

    return 1;
}