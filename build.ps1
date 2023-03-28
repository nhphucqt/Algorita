if ($args.count -eq 1) {
    $file_path = $args[0]
    $project_name = (($args[0] -split {$_ -eq "/" -or $_ -eq "\"})[-1] -split "\.", -2)[0]
} else {
    $file_path = $args[0]
    $project_name = $args[1]
}

$file_path = $file_path.replace("\", "/")
$project_name = $project_name.replace("\", "/")

$compile_command = "C:/msys64/mingw64/bin/mingw32-make.exe"

$all_cpp = (
    "libs/rcore/*.cpp",
    "libs/core/*.cpp",
    "libs/graphic/*.cpp"
)

$compile_args = (
    "RAYLIB_PATH=C:/raylib/raylib",
    "PROJECT_NAME=${project_name}",
    "OBJS=`"${file_path} $($all_cpp -join " ")`"",
    "BUILD_MODE=DEBUG"
)

# C:\raylib\w64devkit\bin\windres.exe minecreeper.rc -o minecreeper.rc.data &&^

# ($compile_command + " " + ($compile_args -join " "))
Invoke-Expression ($compile_command + " " + ($compile_args -join " "))