:: SCRIPT A32 - CST8152 - Fall 2021
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------

CLS

SET COMPILER=CompilersA3.exe

SET FILE1=a32A_Empty
SET FILE2=a32B_Hello
SET FILE3=a32C_Expression

REM ---------------------------------------------------------------------
REM - Begin of Tests (A32 - F21) ----------------------------------------
REM ---------------------------------------------------------------------

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A32 - F21) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% 3 %FILE1%.fy	> %FILE1%.out	2> %FILE1%.err
%COMPILER% 3 %FILE2%.fy	> %FILE2%.out	2> %FILE2%.err
%COMPILER% 3 %FILE3%.fy	> %FILE3%.out	2> %FILE3%.err

ECHO "Showing A32 Results..."

ECHO =========================
TYPE %FILE1%.out
ECHO .........................
TYPE %FILE2%.out
ECHO .........................
TYPE %FILE3%.out
ECHO =========================
DIR *.out
DIR *.err

REM ---------------------------------------------------------------------
REM - End of Tests (A32 - F21) ------------------------------------------
REM ---------------------------------------------------------------------
