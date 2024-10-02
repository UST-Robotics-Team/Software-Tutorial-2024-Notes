# Checking Tools Guideline

This guideline explains how to use the checking tools given
Unfortunately we haven't tested this on Mac, please inform us for any issue.

You have two options:

1. Download [test.sh](./test.sh) if you are working on Codespaces/Unix-based OS (Mac or Linux) or [test.bat](./test.bat) if you are working on Windows and place it at the same level as the `hw` folders.

<insert-image-later-here>

2. Download the given testcase folder zip [here](./testcases.zip) and place it at the same level as the `hw` folders

<insert-image-later-here>

3. Unzip the testcase folder 

<insert-image-later-here>

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
  (If windows stops you from running the bat file, you can either confirm that you still want to run the file, or copy the content of `test.bat`, then deleting `test.bat`, make you own test.bat file and paste the content :) )
