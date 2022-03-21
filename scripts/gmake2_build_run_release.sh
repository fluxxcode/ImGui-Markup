#!/bin/bash
./premake/premake5 gmake2
make config=release
cd sandbox
../bin/Release-linux-x86_64/sandbox/sandbox
