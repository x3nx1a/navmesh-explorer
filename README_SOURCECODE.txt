NavMesh Explorer SOURCECODE                               24.12.2017 - florian0
===============================================================================
                           thanks to DaxterSoul for his fileformats and support
               thanks to Exo for listening to me shedding tears about MSVC bugs

This file acts as a small introduction on my code. I've tried to fake the 
original source layout to get a better understanding how Silkroad Online was
developed and maintained. The implementation is designed to binary compatible
to the original client. This allows using the std-lib without any wrappers and
makes your life a lot easier.

-------------------------------------------------------------------------------
Where to start?

The interesting code is in MyGUI.cpp, MyGUI::NavMeshInfo will spawn the ImGui-
Window and draw the entire overlay. From here you can check out how the NavMesh
structure can be used.

-------------------------------------------------------------------------------
Other interesting areas?

Client.cpp contains a reverse-engineered WinMain that is pretty close to what
the original function does. I've replaced MyRegisterClass and InitInstance with
their original calls for simplicity reasons.

All the other classes are mostly empty wrappers. Some have guessed names that
match the function of their originals so if you're into reverse engineering,
have a look at them.

-------------------------------------------------------------------------------
How does it work at all?

The DllMain overwrites the WinMain with out FakeWinMain(Client.cpp) and the 
EndScene-Function of CGFXVideo3d (sdk/gfx/GFX3DFunction/GFXVideo3d.cpp).

These two hooks allow access to the 3d renderer for imgui windows, and the 
main loop to get mouse movement and keystrokes.

The client will startup as usual, but run on our custom WinMain instead.

FakeWinMain will setup imgui and supply it with messages.

EndSceneIMPL (i couldn't name it EndScene because there already is a virtual 
named EndScene and function pointers to virtuals are garbage to work with) 
will call MyGui::DoWork (MyGui.cpp) to render the window and the overlays.

MyGui::DoWork will check if any window is visible. Visible windows get drawn
and usually the function that draws the window also does all the logic for,
in this case the line-overlays.

-------------------------------------------------------------------------------
Attribution:

Do what ever the f*ck you want with it. But don't be that a**hole claiming 
others work as your own. Thank you. Merry christmas.
