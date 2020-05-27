SET MSBUILD_PATH="/C/Program Files (x86)/MSBuild/14.0/Bin:/C/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin"
choco install wget
choco install 7z
choco install vcbuildtools -ia "/InstallSelectableItems Win81SDK_CppBuildSKUV1;VisualCppBuildTools_ATLMFC_SDK"
export PATH=$MSBUILD_PATH:$PATH
cd oactobjs32
wget -q "https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.zip"
7z x -bd boost_1_64_0.zip
cd boost_1_64_0
./bootstrap.bat
./b2.exe toolset=msvc-14.0 link=static runtime-link=static threading=multi --with-date_time
cd ..
cd ..
cd anypiab
MSBuild.exe
cd ..
cd anypia32
MSBuild.exe
