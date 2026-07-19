gcc -I modules main.c modules/course.c -o calculator.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed."
    exit 1
}

Write-Host "Build successful."