if ($args.count -ne 2) {
    echo "Invalid arguments, the number of arguments MUST BE 2"
} else {
    $test_name = $args[0]
    if ($args[1] -eq 0) { # build test
        ./build test/$test_name/test.cpp
    } elseif ($args[1] -eq 1) { # run test
        Invoke-Expression "test/$test_name/test"
    } elseif ($args[1] -eq 2) {
        ./build test/$test_name/test.cpp
        if ($LASTEXITCODE -eq 0) {
            Invoke-Expression "test/$test_name/test"
        }
    } else {
        echo "Invalid Test Type, the second argument MUST BE 0 (build test), 1 (run test), or 2 (build and run test)"
    }
}