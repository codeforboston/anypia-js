# this script requires yq / pip3 install yq
for i in `yq '.matrix.include[] | .name' .travis.yml | tr -d '"'`
do
    filename="./installbuild-$i"
    if test "$i" = 'windows'; then
        #TODO export env on windows
        extension="bat"
        echo "SET" `yq -c --raw-output ".matrix.include[] | select(.name == \"windows\") | .env | @sh" .travis.yml | tr -d \'` > "$filename.$extension"
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
    chmod +x "$filename.$extension"
done