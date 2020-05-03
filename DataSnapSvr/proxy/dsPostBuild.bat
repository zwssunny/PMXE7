@echo off

set PROJ_DIR=%1
set OUTPUT_DIR=%2

if NOT exist %PROJ_DIR% goto skipit;
if NOT exist %OUTPUT_DIR% goto skipit;

pushd .
cd /D %PROJ_DIR%
set PROJ_DIR=%CD%

cd /D %OUTPUT_DIR%
set OUTPUT_DIR=%CD%
popd

if NOT "%PROJ_DIR%"=="%OUTPUT_DIR%" ( 
  FOR %%A IN (proxy,js,templates,css,images) DO (
    if exist "%PROJ_DIR%\%%A" (
      if exist "%OUTPUT_DIR%\%%A" RMDIR /S /Q "%OUTPUT_DIR%\%%A"
      mkdir "%OUTPUT_DIR%\%%A"
      %WINDIR%\System32\xcopy "%PROJ_DIR%\%%A" "%OUTPUT_DIR%\%%A" /E /Q /Y
    )
  )
)
:skipit