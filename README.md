# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/University-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) <!--![views](https://visitor-badge.glitch.me/badge?page_id=code-chaser.hospital-management-system)--> &nbsp;
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
|[address](https://github.com/code-chaser/hospital-management-system/blob/main/docs/address.md#class-address)|<li>stores the address of a location in a structured manner in its private fields: `line1, line2, city, state, pinCode, country`;<li>has publicly accessible methods to take address as input, output it in a particular manner, generate & return string of a specific format from some address and read the same string to generate back the same address, whenever required (for more details: [link](https://github.com/code-chaser/hospital-management-system/blob/main/docs/address.md#class-address));|
|**_person_**|<li>it's an **_abstract class_** containing **_5 abstract (pure virtual) methods_**;<li>**'has-a'** (object of class) `address`;<li>stores all the basic information of a person in its private fields: `id, firstName, lastName, gender, age, mobNumber, add`;<li>has publicly accessible methods to take the information as input, print it and fill it in an object;<li>class `doctor`, `patient`, `nurse` & `driver` **'inherits'** class `person` and in addition contains a few class-specific fields and methods;
|appointment|<li>**'has-a'** (object of class) `doctor` and **'has-a'** (object of class) `patient`;<li>in addition, it has two more private member fields : `id, hh` to store the appointment ID and its starting hour (in 24-Hr format);<li>has publicly accessible methods to book an appointment, get and print details of a booked appointment;|
|ambulance|<li>**'has-a'** (object of class) `driver` and **'has-a'** (object of class) `address`;<li>in addition, has a few more private fields to store the basic details of an ambulance;<li>has publicly accessible methods to register an ambulance, print it's details, send an ambulance to a destination and report its arrival;|
|hospital|<li>contains the list of all the entities (**'has-a'**): `doctor, patient, appointment, nurse, driver, ambulance` (stores them in a privately accessible map with their `id` as the key);<li>classes `doctor, patient, appointment, nurse, driver, ambulance` are all `friend class` of class `hospital` and they all contain publicly accessible methods `void fillMap();` & `void saveMap();` to fill & overwrite their respective maps (contained in class `hospital`) from and to their respective `*.csv` files at the startup and closing of the program, respectively;<li>in addition, has private fields to store the limits of all the entities;<li>all members of this class are static, so, it doesn't require instantiation;|
___


![UML Class Diagram](https://user-images.githubusercontent.com/63065397/125062323-e3d06380-e0cb-11eb-98e5-f242393b4e1f.jpeg)


___

## Tech Stack
* C++

___
