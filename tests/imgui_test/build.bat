@echo off

set CommonInclude=-I..\..\.
set ImguiInclude=-I.\imgui

cl -nologo -Od -FC -Zi %CommonInclude% %ImguiInclude% imgui_test.cpp -link opengl32.lib -out:imgui_test.exe