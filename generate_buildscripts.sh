# this script requires yq / pip3 install yq
for i in `yq '.matrix.include[] | .name' .travis.yml | tr -d '"'`
do
    filename="./installbuild-$i"
    if test "$i" = 'windows'; then
        #TODO export env on windows
        extention="bat"
        echo "SET" `yq -c --raw-output ".matrix.include[] | select(.name == \"windows\") | .env | @sh" .travis.yml | tr -d \'` > "$filename.$extention"
        echo "choco install wget" >> "$filename.$extention"
        echo "choco install 7z" >> "$filename.$extention"
        #we probably can't use export to set PATH, maybe can just remove the export part?
    elif test "$i" = 'mac-anypiab'; then
        extention="sh"
        echo "brew install " `yq -c --raw-output ".matrix.include[] | select(.name == \"mac-anypiab\") | .addons.homebrew.packages | @sh" .travis.yml | tr -d "\'"` > "$filename.$extention"
    elif test "$i" = 'linux-anypiab'; then
        extention="sh"
        echo "apt install " `yq -c --raw-output ".matrix.include[] | select(.name == \"linux-anypiab\") | .addons.apt.packages | @sh" .travis.yml` > "$filename.$extention"
    else
        extention="sh"
    fi

    yq -c --raw-output ".matrix.include[] | select(.name == \"$i\") | .script[]" .travis.yml >> "$filename.$extention"
    chmod +x "$filename.$extention"
done