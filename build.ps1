if ($args.count -eq 1) {
    $file_path = $args[0]
    # $project_name = (($args[0] -split {$_ -eq "/" -or $_ -eq "\"})[-1] -split "\.", -2)[0]
    $project_name = ($args[0] -split "\.", -2)[0]
} else {
    $file_path = $args[0]
    if ($args[1] -eq ".") {
        $project_name = (($args[0] -split {$_ -eq "/" -or $_ -eq "\"})[-1] -split "\.", -2)[0]
    } else {
        $project_name = $args[1]
    }
}

$file_path = $file_path.replace("\", "/")
$project_name = $project_name.replace("\", "/")

$compile_command = "C:/msys64/mingw64/bin/mingw32-make.exe"

$all_lib_dirs = @($pwd.Path + "\libs")
$all_lib_dirs += Get-ChildItem -Directory -Recurse libs | Where-Object {$_.PSIsContainer} | Foreach-Object {$_.FullName}
$all_lib_dirs = $all_lib_dirs | % {$_ -replace '\\','/'}

# echo $all_lib_dirs

$all_libs_cpp = $all_lib_dirs | % {$_ + "/*.cpp"}
$all_libs_cpp = $all_libs_cpp | where{(Get-ChildItem $_) -like "*.cpp"}

echo $all_libs_cpp

$compile_args = (
    "RAYLIB_PATH=C:/raylib/raylib",
    "PROJECT_NAME=${project_name}",
    "OBJS=`"${file_path} $($all_libs_cpp -join " ")`"",
    "BUILD_MODE=DEBUG"
)

# C:\raylib\w64devkit\bin\windres.exe minecreeper.rc -o minecreeper.rc.data &&^

# # ($compile_command + " " + ($compile_args -join " "))
Invoke-Expression ($compile_command + " " + ($compile_args -join " "))