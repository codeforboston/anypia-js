# this script requires yq / pip3 install yq
for i in `yq '.matrix.include[] | .name' .travis.yml | tr -d '"'`
do
    filename="./installbuild-$i"
    if test "$i" = 'windows'; then
        #TODO export env on windows
        extension="bat"
        #echo "SET" `yq -c --raw-output ".matrix.include[] | select(.name == \"windows\") | .env | @sh" .travis.yml | tr -d \'` > "$filename.$extension"
        echo "SET MSBUILD_PATH=C:/Program Files (x86)/MSBuild/14.0/Bin;C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin" > "$filename.$extension" 
        echo "SET PATH=%PATH%;%MSBUILD_PATH%" >> "$filename.$extension"
        echo "choco install wget" >> "$filename.$extension"
        echo "choco install 7z" >> "$filename.$extension"
        #we probably can't use export to set PATH, maybe can just remove the export part?
    elif test "$i" = 'mac-anypiab'; then
        extension="sh"
        echo "brew install " `yq -c --raw-output ".matrix.include[] | select(.name == \"mac-anypiab\") | .addons.homebrew.packages | @sh" .travis.yml | tr -d "\'"` > "$filename.$extension"
    elif test "$i" = 'emscripten-anypiab-mac'; then
        extension="sh"
        echo "brew install " `yq -c --raw-output ".matrix.include[] | select(.name == \"emscripten-anypiab-mac\") | .addons.homebrew.packages | @sh" .travis.yml | tr -d "\'"` > "$filename.$extension"
    elif test "$i" = 'linux-anypiab'; then
        extension="sh"
        echo "apt install " `yq -c --raw-output ".matrix.include[] | select(.name == \"linux-anypiab\") | .addons.apt.packages | @sh" .travis.yml` > "$filename.$extension"
    else
        extension="sh"
        echo "" > "$filename.$extension"
    fi

    yq -c --raw-output ".matrix.include[] | select(.name == \"$i\") | .script[]" .travis.yml >> "$filename.$extension"
    if test "$i" = 'windows'; then
        # If you don't use call, the batch file stops after the other batch file.
        sed 's/\.\/bootstrap.bat/call bootstrap.bat/g' "$filename.$extension" > "$filename.$extension.tmp"
        mv "$filename.$extension.tmp" "$filename.$extension"
    fi
    chmod +x "$filename.$extension"
done