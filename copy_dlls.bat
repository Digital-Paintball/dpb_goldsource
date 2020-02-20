@echo off

echo Mode:        %1
echo Client dir:  %DPB_CLIENT_OUTPUT_DIR%
echo Server dir:  %DPB_SERVER_OUTPUT_DIR%

if not exist build (
	echo Build missing
	exit
)

if not exist build\%1 (
	echo Build configuration missing
	exit
)

copy build\%1\client.dll %DPB_CLIENT_OUTPUT_DIR%
copy build\%1\pb.dll %DPB_SERVER_OUTPUT_DIR%


