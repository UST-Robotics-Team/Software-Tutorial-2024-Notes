# Checking Tools Guideline

## Important Note : Changes to HW3 Skeleton Code

Please update your `utility.c` in your HW3 code. Although it is informed that it is okay to submit the old version of `utility.c`, I am not sure that it will work for this testing tool as it receives input from files and I am not sure it will work without fixing the `\r\n` issue.

Please find the new version of `utility.c` [here](./hw03-top-down-platformer/utility.c), please copy and replace it directly to your `utility.c` (you are allowed to modify it for this purpose).

If you do not do this, the program may stuck and outputs an enormously large file somehow.

## Testing Tool

This guideline explains how to use the checking tools given

(Unfortunately we haven't tested this on Mac, please inform us for any issue.)

1. Download [test.sh](./test.sh) if you are working on Codespaces/Unix-based OS (Mac or Linux) or [test.bat](./test.bat) if you are working on Windows and place it at the same level as the `hw1`, `hw2`, ... folders.

   Download using the button on the top right side

   ![image](https://github.com/user-attachments/assets/22b27244-0a18-480a-9149-61844e7721d0)

   Put it in this part of the directory (same level as `hw1`, `hw2`, ...):

   ![image](https://github.com/user-attachments/assets/76707f5b-9ddb-40b6-a701-717aff221982)


2. Download the given testcase folder zip [here](./testing.zip) and place it at the same level as the `hw1`, `hw2`, ... folders

    Similarly, download here:

    ![image](https://github.com/user-attachments/assets/32fb562d-9e8a-4d1e-aba9-356e2d073b22)

    Put it in this part of the directory (same as `test.sh`):

    ![image](https://github.com/user-attachments/assets/00de3311-247d-4907-8b04-52bd415fd632)


3. Unzip the testcase folder (On Windows, right click on the file instead from File Explorer)

    ![image](https://github.com/user-attachments/assets/4f2bae14-0155-468a-ace3-c389dc478e84)

    ![image](https://github.com/user-attachments/assets/00f732c4-06d2-4625-954d-517b8954ea0f)
   

4. Run the following command to run the .sh or .bat file (if you feel suspicious, you may check the content of the files before running)

     On Codespaces/Unix-based OS (Mac or Linux)
     ```
     chmod +x ./test.sh && ./test.sh
     ```
     (`chmod` is needed to give permission for the execution of the file)
     
     On Windows
     ```
     ./test.bat
     ```
     (If Windows stops you from running the bat file, you can either confirm that you still want to run the file, or copy the content of `test.bat`, then deleting `test.bat`, make you own `test.bat` file and paste the content :) )


5. After running, you will see a folder named `result`. You then need to compare the content of this file to the one provided in `testing`. If you would like to compare Homework 1 Testcase 1, then compare `result/hw1/out01.txt` and `testing/hw1/output01.txt`

   To compare, first right click one of the file and select "Select for Compare"
   ![image](https://github.com/user-attachments/assets/85e78ec5-7dc4-4d6d-9883-c2b8106c38ba)


   Then, right click the second file and select "Compare with Selected"
   ![image](https://github.com/user-attachments/assets/407cbaa6-b549-4afd-a612-d664fd630aee)

   If you see some red lines, then something is wrong
   ![image](https://github.com/user-attachments/assets/0c53f492-37fa-4a11-95a7-d4a891ef50e0)

   If not, then you are good to go; check this for all outputs :)
   ![image](https://github.com/user-attachments/assets/9ac0f8bd-4631-4c7a-affe-d7dd86a6f4c6)


Goodluck!
