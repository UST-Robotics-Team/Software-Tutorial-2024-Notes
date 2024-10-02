if [ ! -d "result" ]; then
    mkdir result
fi

echo "-------------------------------------------------------------------------------------------------------"

if [ ! -d "result/hw1" ]; then
    mkdir result/hw1
fi

success=1

echo "Compiling HW1..."
echo "Running gcc -o homework1.exe ./hw1/main.c" 

if gcc -o homework1.exe ./hw1/main.c; then
    echo "Compilation Succeed!"
else
    echo "Sorry, HW1 fails to compile..."
    success=0
fi

if [[ $success == 1 ]]; then
    echo "Generating output... (Use Ctrl+C to stop if your code stucks and there is an infinite loop)"
    hw1_tests=9

    for i in `seq 1 $hw1_tests`
    do
        echo "testing/hw1/input0${i}.txt | ./homework1.exe > result/hw1/out0${i}.txt"
        cat "testing/hw1/input0${i}.txt" | ./homework1.exe > "result/hw1/out0${i}.txt"
    done

    echo "Done generating output for HW1, please use the VSCode diffchecker tool to check the output. Goodluck :)"
fi

echo "-------------------------------------------------------------------------------------------------------"

if [ ! -d "result/hw2" ]; then
    mkdir result/hw2
fi

success=1

echo "Compiling HW2..."
echo "Running gcc -o homework2.exe ./hw2/main.c" 

if gcc -o homework2.exe ./hw2/main.c; then
    echo "Compilation Succeed!"
else
    echo "Sorry, HW2 fails to compile..."
    success=0
fi

if [[ $success == 1 ]]; then
    echo "Generating output... (Use Ctrl+C to stop if your code stucks and there is an infinite loop)"
    hw2_tests=3

    for i in `seq 1 $hw2_tests`
    do
        cat "testing/hw2/input0${i}.txt" | ./homework2.exe > "result/hw2/out0${i}.txt"
    done

    echo "Done generating output for HW2, please use the VSCode diffchecker tool to check the output. Goodluck :)"
fi

echo "-------------------------------------------------------------------------------------------------------"

if [ ! -d "result/hw3" ]; then
    mkdir result/hw3
fi

success=1

echo "Compiling HW3..."
echo "Running gcc -o homework3.exe ./hw3/main.c ./hw3/utility.c ./hw3/utility.h..." 

if gcc -o homework3.exe ./hw3/main.c ./hw3/utility.c ./hw3/utility.h; then
    echo "Compilation Succeed!"
else
    echo "Sorry, HW3 fails to compile..."
    success=0
fi

if [[ $success == 1 ]]; then
    echo "Generating output... (Use Ctrl+C to stop if your code stucks and there is an infinite loop)"
    hw3_tests=3

    for i in `seq 1 $hw3_tests`
    do
        cat "testing/hw3/input0${i}.txt" | ./homework3.exe > "result/hw3/out0${i}.txt"
    done

    echo "Done generating output for HW3, please use the VSCode diffchecker tool to check the output. Goodluck :)"
fi

echo "-------------------------------------------------------------------------------------------------------"

if [ ! -d "result/hwb1" ]; then
    mkdir result/hwb1
fi

success=1

echo "Compiling HW Bonus 1..."
echo "Running gcc -o homeworkb1.exe ./hwb1/main.c" 

if gcc -o homeworkb1.exe ./hwb1/main.c; then
    echo "Compilation Succeed!"
else
    echo "Sorry, Homework Bonus 1 fails to compile..."
    success=0
fi

if [[ $success == 1 ]]; then
    echo "Generating output... (Use Ctrl+C to stop if your code stucks and there is an infinite loop)"
    hwb1_tests=2

    for i in `seq 1 $hwb1_tests`
    do
        cat "testing/hwb1/input0${i}.txt" | ./homeworkb1.exe > "result/hwb1/out0${i}.txt"
    done

    echo "Done generating output for HW Bonus 1, please use the VSCode diffchecker tool to check the output. Goodluck :)"
fi

echo "-------------------------------------------------------------------------------------------------------"

