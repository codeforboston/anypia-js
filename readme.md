# Official Social Security Calculator javascript port project

Sister project of 
- https://github.com/bslabs/anypiamac
- https://github.com/codeforboston/windfall-elimination/

To build for Windows (no requirements):
- Open administrator terminal
- Install [Choco](https://chocolatey.org/install)
- Install build tools `choco install --force -y vcbuildtools -ia "/InstallSelectableItems Win81SDK_CppBuildSKUV1;VisualCppBuildTools_ATLMFC_SDK"`
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