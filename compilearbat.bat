set num=0
:loop
echo #define cmdfeedI %num% > defineI.h
gcc fractal.c render.c settings.c auxiliaryFunctions.c -O3 -o b/%num%
set /a num=%num%+1
if %num% neq 38 goto loop
set num1=0
:loop1
echo START /b %num1%.exe >> b/startcommand.bat
set /a num1=%num1%+1
if %num1% neq 38 goto loop1