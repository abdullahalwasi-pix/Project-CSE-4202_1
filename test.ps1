gcc -I modules tests/test_course.c modules/course.c -o test_course.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed."
    exit 1
}

.\test_course.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Course module tests failed."
    exit 1
}