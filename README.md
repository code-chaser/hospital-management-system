# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/University-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) ![views](https://visitor-badge.glitch.me/badge?page_id=code-chaser.h-m-s) &nbsp;
## INTRODUCTION
a hospital management system, made using object oriented programming and file handling in C++, that keeps records of doctors & their appointments, patitents, staff, ambulances, etc.

___

<br>

## DESCRIPTION
___
#### BUILD & EXECUTE
- For Windows users: firstly install ` make ` for executing ` makefile `, from this [link](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows);
- For Linux users: ` make ` generally comes pre-installed;
   - if not, then run the following command: ` sudo apt-get install make `
   <br>
- Now, run the following commands:
   - for building executable file: 
  ```
     make all
  ```
   - for executing it:
  ```
     make run        // for linux/macOS;
     make run(win)   // for windows;
  ```
   - for deleting executable file:
  ```
     make clean      // for linux/macOS;
     make clean(win) // for windows;
  ```
___

#### CLASS DESIGN
|CLASS|DESCRIPTION|
|-----|-----------|
|address|stores the address in a structured manner in its private fields: ` line1, line2, city, state, pinCode, country ` ;<br>has publicly accessible methods to take address as input, output address, generate & return string from an address object and read the same string to generate back the same address object whenever required;|
|_person_|it's an **_abstract class_** containing 3 **_abstract methods_**;<br>stores all the basic information of a person in its private fields: ` id, firstName, lastName, gender, age, mobNumber, add ` ;<br>has publicly accessible methods to take the information as input, print it, fill it in an object;
|doctor||
|patient||
|appointment||
|nurse||
|driver||
|ambulance||
___
![image](https://user-images.githubusercontent.com/63065397/124442912-d5680c00-dd9a-11eb-96af-0bf73961016e.png)

___

## Tech Stack
* C++

___
