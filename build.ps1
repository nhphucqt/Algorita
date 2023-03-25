if ($args.count -eq 1) {
    $file_path = $args[0]
    $project_name = (($args[0] -split {$_ -eq "/" -or $_ -eq "\"})[-1] -split "\.", -2)[0]
} else {
    $file_path = $args[0]
    $project_name = $args[1]
}

$file_path = $file_path.replace("\", "/")
$project_name = $project_name.replace("\", "/")

# C:\raylib\w64devkit\bin\windres.exe minecreeper.rc -o minecreeper.rc.data &&^
C:\msys64\mingw64\bin\mingw32-make.exe RAYLIB_PATH=C:/raylib/raylib PROJECT_NAME=${project_name} OBJS="${file_path} libs/rcore/*.cpp libs/core/*.cpp libs/graphic/*.cpp" BUILD_MODE=DEBUG 