#include <stdio.h>

#include "course.h"
#include "courseResult.h"
#include "gpa.h"

#define MAX_ITEMS 1000

void showMenu()
{
    printf("\n========== CGPA CALCULATOR ==========\n");
    printf("1. Add Course\n");
    printf("2. Edit Course\n");
    printf("3. Delete Course\n");
    printf("4. View Courses\n");
    printf("5. Add Course Result\n");
    printf("6. Edit Course Result\n");
    printf("7. Delete Course Result\n");
    printf("8. View Marksheet\n");
    printf("9. Required GPA Calculator\n");
    printf("10. Exit\n");
    printf("Enter Choice: ");
}

void addCourse(
    Course courses[],
    int *n_courses
)
{
    char code[16];
    char name[100];
    double credit;
    int semester;

    if (*n_courses >= MAX_ITEMS)
    {
        printf("Course list is full.\n");
        return;
    }

    printf("Course Code: ");
    scanf("%15s", code);

    printf("Course Name: ");
    scanf(" %99[^\n]", name);

    printf("Credit: ");
    scanf("%lf", &credit);

    printf("Semester: ");
    scanf("%d", &semester);

    courses[*n_courses] = createCourse(
        code,
        name,
        credit,
        semester
    );

    *n_courses = *n_courses + 1;

    printf("Course added successfully.\n");
}

void viewCourses(
    Course courses[],
    int n_courses
)
{
    if (n_courses == 0)
    {
        printf("No courses added yet.\n");
        return;
    }

    printf("\n========== COURSE LIST ==========\n");

    for (int i = 0; i < n_courses; i++)
    {
        printf("\n%d.\n", i + 1);
        viewCourse(courses[i]);
    }
}

void editCourse(
    Course courses[],
    int n_courses
)
{
    int course_no;
    char code[16];
    char name[100];
    double credit;
    int semester;

    if (n_courses == 0)
    {
        printf("No courses available to edit.\n");
        return;
    }

    viewCourses(courses, n_courses);

    printf("\nCourse Number: ");
    scanf("%d", &course_no);

    if (course_no < 1 || course_no > n_courses)
    {
        printf("Invalid course number.\n");
        return;
    }

    printf("New Course Code: ");
    scanf("%15s", code);

    printf("New Course Name: ");
    scanf(" %99[^\n]", name);

    printf("New Credit: ");
    scanf("%lf", &credit);

    printf("New Semester: ");
    scanf("%d", &semester);

    courses[course_no - 1] = createCourse(
        code,
        name,
        credit,
        semester
    );

    printf("Course updated successfully.\n");
}

void deleteCourse(
    Course courses[],
    int *n_courses,
    CourseResult results[],
    int *n_results
)
{
    int course_no;

    if (*n_courses == 0)
    {
        printf("No courses available to delete.\n");
        return;
    }

    viewCourses(courses, *n_courses);

    printf("\nCourse Number: ");
    scanf("%d", &course_no);

    if (course_no < 1 || course_no > *n_courses)
    {
        printf("Invalid course number.\n");
        return;
    }

    Course *deleted_course =
        &courses[course_no - 1];

    int kept_results = 0;

    /*
        যে course delete হচ্ছে, তার result বাদ যাবে।

        Deleted course-এর পরে থাকা course-গুলো
        array-তে এক ঘর সামনে যাবে। তাই result-এর
        course pointer-ও এক ঘর পিছিয়ে দেওয়া হচ্ছে।
    */
    for (int i = 0; i < *n_results; i++)
    {
        if (results[i].course == deleted_course)
        {
            continue;
        }

        if (results[i].course > deleted_course)
        {
            results[i].course--;
        }

        results[kept_results] = results[i];
        kept_results++;
    }

    *n_results = kept_results;

    for (int i = course_no - 1;
         i < *n_courses - 1;
         i++)
    {
        courses[i] = courses[i + 1];
    }

    *n_courses = *n_courses - 1;

    printf("Course deleted successfully.\n");
}

void viewResultList(
    CourseResult results[],
    int n_results
)
{
    if (n_results == 0)
    {
        printf("No course results available.\n");
        return;
    }

    printf("\n========== COURSE RESULTS ==========\n");

    for (int i = 0; i < n_results; i++)
    {
        printf("\n%d.\n", i + 1);

        viewCourseResult(results[i]);

        printf(
            "Grade: %s\n",
            getLetterGrade(results[i])
        );
    }
}

void addCourseResult(
    Course courses[],
    int n_courses,
    CourseResult results[],
    int *n_results
)
{
    int course_no;
    int completed;
    double marks;

    if (n_courses == 0)
    {
        printf("Add a course first.\n");
        return;
    }

    if (*n_results >= MAX_ITEMS)
    {
        printf("Course result list is full.\n");
        return;
    }

    viewCourses(courses, n_courses);

    printf("\nCourse Number: ");
    scanf("%d", &course_no);

    if (course_no < 1 || course_no > n_courses)
    {
        printf("Invalid course number.\n");
        return;
    }

    printf(
        "\n%s: %s Completed?\n",
        courses[course_no - 1].code,
        courses[course_no - 1].name
    );

    printf("1. YES\n");
    printf("2. NO\n");
    printf("Enter Choice: ");
    scanf("%d", &completed);

    if (completed == 1)
    {
        printf(
            "Marks for %s: ",
            courses[course_no - 1].name
        );

        scanf("%lf", &marks);

        results[*n_results] =
            createCompletedCourseResult(
                &courses[course_no - 1],
                marks
            );
    }
    else if (completed == 2)
    {
        results[*n_results] =
            createIncompleteCourseResult(
                &courses[course_no - 1]
            );
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    *n_results = *n_results + 1;

    printf("Course result added successfully.\n");
}

void editCourseResult(
    CourseResult results[],
    int n_results
)
{
    int result_no;
    int completed;
    double marks;

    if (n_results == 0)
    {
        printf(
            "No course results available to edit.\n"
        );

        return;
    }

    viewResultList(results, n_results);

    printf("\nCourse Result Number: ");
    scanf("%d", &result_no);

    if (result_no < 1 || result_no > n_results)
    {
        printf("Invalid course result number.\n");
        return;
    }

    Course *course =
        results[result_no - 1].course;

    printf(
        "\n%s: %s Completed?\n",
        course->code,
        course->name
    );

    printf("1. YES\n");
    printf("2. NO\n");
    printf("Enter Choice: ");
    scanf("%d", &completed);

    if (completed == 1)
    {
        printf(
            "Marks for %s: ",
            course->name
        );

        scanf("%lf", &marks);

        results[result_no - 1] =
            createCompletedCourseResult(
                course,
                marks
            );
    }
    else if (completed == 2)
    {
        results[result_no - 1] =
            createIncompleteCourseResult(course);
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    printf("Course result updated successfully.\n");
}

void deleteCourseResult(
    CourseResult results[],
    int *n_results
)
{
    int result_no;

    if (*n_results == 0)
    {
        printf(
            "No course results available to delete.\n"
        );

        return;
    }

    viewResultList(results, *n_results);

    printf("\nCourse Result Number: ");
    scanf("%d", &result_no);

    if (result_no < 1 ||
        result_no > *n_results)
    {
        printf("Invalid course result number.\n");
        return;
    }

    for (int i = result_no - 1;
         i < *n_results - 1;
         i++)
    {
        results[i] = results[i + 1];
    }

    *n_results = *n_results - 1;

    printf("Course result deleted successfully.\n");
}

void viewMarksheet(
    CourseResult results[],
    int n_results
)
{
    if (n_results == 0)
    {
        printf("No course results available.\n");
        return;
    }

    sortCourseResultsBySemester(
        results,
        n_results
    );

    printf("\n========== MARKSHEET ==========\n");

    for (int i = 0; i < n_results; i++)
    {
        printf("\n%d.\n", i + 1);

        viewCourseResult(results[i]);

        printf(
            "Grade: %s\n",
            getLetterGrade(results[i])
        );
    }

    printf("\n========== SEMESTER GPA ==========\n");

    for (int semester = 1;
         semester <= 8;
         semester++)
    {
        CourseResult semester_results[MAX_ITEMS];

        filterCourseResultsBySemester(
            results,
            n_results,
            semester,
            semester_results
        );

        int n_semester_results =
            countCourseResultsBeforeNull(
                semester_results,
                MAX_ITEMS
            );

        if (n_semester_results > 0)
        {
            printf(
                "Semester %d GPA: %.2f\n",
                semester,
                calculateGPA(
                    semester_results,
                    n_semester_results
                )
            );
        }
    }

    printf(
        "CGPA: %.2f\n",
        calculateGPA(
            results,
            n_results
        )
    );
}

void showRequiredGPACalculator()
{
    double current_cgpa;
    double completed_credits;
    double target_cgpa;
    double remaining_credits;

    printf("\n========== REQUIRED GPA CALCULATOR ==========\n");

    printf("Current CGPA: ");
    scanf("%lf", &current_cgpa);

    printf("Completed Credits: ");
    scanf("%lf", &completed_credits);

    printf("Target CGPA: ");
    scanf("%lf", &target_cgpa);

    printf("Remaining Credits: ");
    scanf("%lf", &remaining_credits);

    if (remaining_credits <= 0.0)
    {
        printf(
            "Remaining credits must be greater than zero.\n"
        );

        return;
    }

    double required_gpa =
        calculateRequiredGPA(
            current_cgpa,
            completed_credits,
            target_cgpa,
            remaining_credits
        );

    printf(
        "Required GPA: %.2f\n",
        required_gpa
    );

    if (required_gpa > 4.00)
    {
        printf(
            "The target CGPA is not achievable "
            "with the given remaining credits.\n"
        );
    }
    else if (required_gpa < 0.00)
    {
        printf(
            "You have already exceeded the target CGPA.\n"
        );
    }
}

int main()
{
    Course courses[MAX_ITEMS];
    CourseResult results[MAX_ITEMS];

    int n_courses = 0;
    int n_results = 0;
    int choice = 0;

    while (choice != 10)
    {
        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }

        if (choice == 1)
        {
            addCourse(
                courses,
                &n_courses
            );
        }
        else if (choice == 2)
        {
            editCourse(
                courses,
                n_courses
            );
        }
        else if (choice == 3)
        {
            deleteCourse(
                courses,
                &n_courses,
                results,
                &n_results
            );
        }
        else if (choice == 4)
        {
            viewCourses(
                courses,
                n_courses
            );
        }
        else if (choice == 5)
        {
            addCourseResult(
                courses,
                n_courses,
                results,
                &n_results
            );
        }
        else if (choice == 6)
        {
            editCourseResult(
                results,
                n_results
            );
        }
        else if (choice == 7)
        {
            deleteCourseResult(
                results,
                &n_results
            );
        }
        else if (choice == 8)
        {
            viewMarksheet(
                results,
                n_results
            );
        }
        else if (choice == 9)
        {
            showRequiredGPACalculator();
        }
        else if (choice == 10)
        {
            printf("Program closed.\n");
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}