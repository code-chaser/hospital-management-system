# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/University-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) &nbsp;
## INTRODUCTION
a hospital management system, made using object oriented programming and file handling in C++, that keeps records of doctors & their appointments, patitents, staff, ambulances, etc.

___

<br>

## DESCRIPTION
___

#### GOALS & OBJECTTIVES
|S.No.|GOAL|OBJECTIVES|
|:-----:|:-:|----------|
|1.|add people|<ul><li>create a base class `person` to derive classes of doctors, patients and other staff members from it later on;<li>class `person`:<ul><li>create appropriate fields to store the basic details of a person;<li>create a method that takes basic details of a person as input from the user side, whenever a new person is to be registered;<li>declare an abstract method to search for a registered person in the database so that it can be defined later in the derived classes;<li>create a method to print the basic details of a person;<li>create a method to remove (un-register) a registered person;|
|2.|add doctors, patients, nurses, ambulance drivers|<ul><li>derive the classes `doctor, patient, nurse, driver` from the class `person`;<li>define the abstract methods declared inside class `person` in each of the derived classes;<li>re-define some methods defined in class `person` if required, *for example while registering a driver, in addition to his basic details, his license number will also be required, and, for that, the method *`addPerson();`* shall be provided an extended definition*;<li>class `doctor`:<ul><li>add a private field `string type;` to store the type of the doctor;</ul><li>class `patient`:<ul><li>add private fields `int height, weight;` for storing the obvious;<li>add fields `bool hospitalized, alive;` which tells us if the patient was hospitalized or not and if (hospitalized), is still alive or not;<li>create a method to hospitalize a patient (i.e. change the value of `hospitalized` field of a particular object of class `patient` to `TRUE`);<li>create a method to report a patient's death (i.e. change the value of `alive` field of a particular object of class `patient` to `FALSE`);</ul><li>class `nurse`:<ul><li>add a private field `string type;` to store the type of the nurse;|
|3.|;|<li>;<li>;<li>;|
|4.|create |<li>;<li>;<li>;|
|5.|create |<li>;<li>;<li>;|
|6.|create |<li>;<li>;<li>;|
___

#### SYSTEM DESIGN
|CLASS|DESCRIPTION|
|:-----:|-----------|
|address|<ul><li>stores the address of a location in a structured manner in its private fields: `line1, line2, city, state, pinCode, country`;<li>has publicly accessible methods to take address as input, output it in a particular manner, generate & return string of a specific format from some address and read the same string to generate back the same address, whenever required ([read more](https://github.com/code-chaser/hospital-management-system/blob/main/docs/address.md#class-address));|
|**_person_**|<ul><li>it's an **_abstract class_** containing **_5 abstract (pure virtual) methods_**;<li>**'has-a'** (object of class) `address`;<li>stores all the basic information of a person in its private fields: `id, firstName, lastName, gender, age, mobNumber, add`;<li>has publicly accessible methods to take the information as input, print it and fill it in an object;<li>class `doctor`, `patient`, `nurse` & `driver` **'inherits'** class `person` and in addition contains a few class-specific fields and methods;
|appointment|<ul><li>**'has-a'** (object of class) `doctor` and **'has-a'** (object of class) `patient`;<li>in addition, it has two more private member fields : `id, hh` to store the appointment ID and its starting hour (in 24-Hr format);<li>has publicly accessible methods to book an appointment, get and print details of a booked appointment;|
|ambulance|<ul><li>**'has-a'** (object of class) `driver` and **'has-a'** (object of class) `address`;<li>in addition, has a few more private fields to store the basic details of an ambulance;<li>has publicly accessible methods to register an ambulance, print it's details, send an ambulance to a destination and report its arrival;|
|hospital|<ul><li>contains the list of all the entities (**'has-a'**): `doctor, patient, appointment, nurse, driver, ambulance` (stores them in a privately accessible map with their `id` as the key);<li>classes `doctor, patient, appointment, nurse, driver, ambulance` are all `friend class` of class `hospital` and they all contain publicly accessible methods `void fillMap();` & `void saveMap();` to fill & overwrite their respective maps (contained in class `hospital`) from and to their respective `*.csv` files at the startup and closing of the program, respectively;<li>in addition, has private fields to store the limits of all the entities;<li>all members of this class are static, so, it doesn't require instantiation;|
___


![UML Class Diagram](https://user-images.githubusercontent.com/63065397/125062323-e3d06380-e0cb-11eb-98e5-f242393b4e1f.jpeg)


___

#### FUNCTIONING
...

___
