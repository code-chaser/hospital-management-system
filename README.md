# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/University-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) <!--![views](https://visitor-badge.glitch.me/badge?page_id=code-chaser.h-m-s) &nbsp;-->
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
  ```bash
     make all
  ```
   - for executing it:
  ```bash
     make run        # universal;
  ```
   - for deleting executable file:
  ```bash
     make clean      # for linux/macOS;
     make clean(win) # for windows;
  ```
___

#### CLASS DESIGN
|CLASS|DESCRIPTION|
|-----|-----------|
|address|- stores the address in a structured manner in its private fields: `line1, line2, city, state, pinCode, country`;<br>- has publicly accessible methods to take address as input, output address in a particular manner, generate & return string of a specific format from some address and read the same string to generate back the same address, whenever required;|
|**_person_**|- it's an **_abstract class_** containing **_5 abstract (pure virtual) methods_**;<br>- stores all the basic information of a person in its private fields: `id, firstName, lastName, gender, age, mobNumber, add`;<br>- has publicly accessible methods to take the information as input, print it, fill it in an object;<br>- **classes `doctor`, `patient`, `nurse` & `driver` inherits class `person`** and in addition contains a few class-specific fields and methods;
|appointment||
|ambulance||
|hospital||
___


![UML Class Diagram](https://user-images.githubusercontent.com/63065397/125062323-e3d06380-e0cb-11eb-98e5-f242393b4e1f.jpeg)


___

## Tech Stack
* C++

___
