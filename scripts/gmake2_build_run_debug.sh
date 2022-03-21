#!/bin/bash
./premake/premake5 gmake2
make config=debug
cd sandbox
../bin/Debug-linux-x86_64/sandbox/sandbox
