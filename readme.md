# Official Social Security Calculator javascript port project

Sister project of 
- https://github.com/bslabs/anypiamac
- https://github.com/codeforboston/windfall-elimination/

To build for Windows using MSBuild (no requirements):
- Open administrator terminal
- Install [Choco](https://chocolatey.org/install)
- Install build tools `choco install --force -y vcbuildtools -ia "/InstallSelectableItems Win81SDK_CppBuildSKUV1;VisualCppBuildTools_ATLMFC_SDK"` or `choco install --force -y vcbuildtools -ia "/Full"` (larger install, but won't uninstall anything)
- install `choco install wget`
- install `choco install 7z`
- install `choco install microsoft-visual-cpp-build-tools`
- Update your Path `PATH="/C/Program Files (x86)/MSBuild/14.0/Bin:/C/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin:$PATH"`
- install git, locally clone/open repository folder.
- `cd oactobjs32`
- `wget -q "https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.zip"`
- `7z x -bd boost_1_64_0.zip`
- `cd boost_1_64_0`
- `./bootstrap.bat`
- `./b2.exe toolset=msvc-14.0 link=static runtime-link=static threading=multi --with-date_time`
- `cd ../..`
- `cd anypiab`
- `MSBuild.exe`
- `cd ../anypia32`
- `MSBuild.exe`
- Find the executable in `\anypia-js\anypia32\Debug`

To build for Windows with CMake:
- Conversion from SLN files was done with https://github.com/pavelliavonau/cmakeconverter
-  `choco cmake`
- `cd anypia-js\anypiab`
- `"C:\Program Files\CMake\bin\cmake.exe" .`

To setup emscripten itself, loosely [based off this resource](https://mirano.blog/emscripten/):
- run `python` and if it launches Microsoft Store, install it.
- close and reopen your terminal (you need a new environment variable)
- `git clone https://github.com/emscripten-core/emsdk.git`
- `cd emsdk`
- `git pull` (if old)
- `./emsdk install latest` Download and install the latest SDK tools.
- `./emsdk activate latest` Make the "latest" SDK "active" for the current user. (writes ~/.emscripten file)
- `emsdk_env.bat`
- if it worked, you should be able to check the install with `emcc -v`
- go back to anypia-js repository

