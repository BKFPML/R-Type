@echo off
SET SERVER_NAME=r-type_server
SET CLIENT_NAME=r-type_client

REM Remove directories and files
IF EXIST build RMDIR /S /Q build
IF EXIST %SERVER_NAME% DEL /F /Q %SERVER_NAME%
IF EXIST %CLIENT_NAME% DEL /F /Q %CLIENT_NAME%
IF EXIST .\docs\ RMDIR /S /Q .\docs\
IF EXIST .\vcpkg\ RMDIR /S /Q .\vcpkg\
IF EXIST .\vcpkg_installed\ RMDIR /S /Q .\vcpkg_installed\

echo Cleanup complete.
