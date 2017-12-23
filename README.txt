NavMesh Explorer                                          24.12.2017 - florian0
===============================================================================
                           thanks to DaxterSoul for his fileformats and support
               thanks to Exo for listening to me shedding tears about MSVC bugs

This tool acts as an addon to sro_client.exe. It overrides various functions of
the client and is therefore not compatible with any other 3rd-party software
and/or might even break other 3rd-party software.

It shows Silkroad Online's NavMesh components:

* Terrain-Mesh
  * Cell Grid
  * Borders

* Object-Mesh
  * Cell Grid

Currently unsupported are:
* Dungeon-Mesh
  * entirely

* Object-Mesh
  * Borders

-------------------------------------------------------------------------------
Usage:

Copy the Dll to your Silkroad Folder, run the client and inject the dll. If 
your client is VSRO188, you may use the client shipped with this package.

In any other case: The DllMain must be executed before the original WinMain of 
the Clients starts. Your injection method can be either detouring the 
entrypoint or adding an import. Common dll-injection-tools may work if they 
support creating the client process suspended.

-------------------------------------------------------------------------------
Bugs:

? Help, my NavMesh is displaced
- This is a bug related to my poor way of getting the current active NavMesh
  When getting close to the mesh border, the client will sometimes change the 
  mesh to early. You can freeze the correct mesh with the checkbox. Don't 
  forget to untick it when you pass a border.

? Help, my client crashes
- Oops ... make sure to show the window when being logged in. There is no 
  NavMesh for the login screen, the character selection or the character 
  creation.

-------------------------------------------------------------------------------
Compiling:

As always, compiling is a little tricky. This software is designed to be binary
compatible to the client. Therefore building with Visual C++ 8.0 (install 
Visual Studio 2005) is mandatory! You'll need Daffodil (1) and Visual Studio 
2010 to open the project. You'll also need DirectX SDK (i'm using v9.0b, but 
newers might work, too). Put it inside the lib-folder.

Always compile on Release-mode. Debug will produce incompatible code.

This combination is guaranteed to work as it is binary compatible. Newer 
compilers can work, but are neither tested nor supported by me.

(1) https://daffodil.codeplex.com/

-------------------------------------------------------------------------------
Attribution:

Do what ever the f*ck you want with it. But don't be that a**hole claiming 
others work as your own. Thank you. Merry christmas.
