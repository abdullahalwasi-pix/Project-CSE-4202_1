gcc -I modules tests/test_course.c modules/course.c -o test_course.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Course test compilation failed."
    exit 1
}

.\test_course.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Course module tests failed."
    exit 1
}

gcc -I modules tests/test_course_result.c modules/course.c modules/courseResult.c -o test_course_result.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Course result test compilation failed."
    exit 1
}

.\test_course_result.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Course result module tests failed."
    exit 1
}