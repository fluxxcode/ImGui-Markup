# ImGui-Markup
Layer above [ImGui](https://github.com/ocornut/imgui) with a simple markup language. <br/> The aim is to make it easier for developers and users of software using ImGui to change or develop the GUI. <br/>
With the markup language, the frontend is separated from the backend and enables easy access to the GUI for plugins or modders.
The markup is dynamically loaded at runtime, so most of the GUI changes does not require to recompile the project.<br/><br/>
Note: Currently the project is in such an early state that it cant be really used in a real application. There are still a lot of features missing and the project will probably change a lot in the future.
# Compile
Clone the repository and its submodules
```
git clone --recursive https://github.com/FluxxCode/ImGui-Markup.git
```
## Windows
Generate the project files
```
./scripts/vs2019_generate_project_files.bat
```
Alternatively, the project files can also be generated using ./premake/premake5.exe, which allows to select a different IDE than vs2019.
## Linux
### Ubuntu:
Dependencies if you only want to compile the lib:
```
sudo apt install make g++
```
Dependencies if you also want to compile the sandbox and example programs:
```
sudo apt install make g++ libglu1-mesa-dev xorg-dev freeglut3-dev
```
You can use following helper scripts to compile the project, including sandbox and example programs:
```
./scripst/gmake2_build_run_debug.sh
./scripst/gmake2_build_run_release.sh
```
# Examples
TODO

# TODOs
- Implement every missing ImGui feature
- System for language and style selection
- Different views to allow the alignment of items
- Unit tests
- and a lot more...
