gcc -I modules main.c modules/course.c modules/courseResult.c modules/gpa.c modules/student.c -o calculator.exe

if ($LASTEXITCODE -eq 0)
{
    Write-Host "Build successful."
}
else
{
    Write-Host "Build failed."
    exit $LASTEXITCODE
}