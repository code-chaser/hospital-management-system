# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/University-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) &nbsp;
## INTRODUCTION
a hospital management system, made using object oriented programming and file handling in C++, that keeps records of doctors & their appointments, patitents, staff, ambulances, etc.

___

<br>

## DESCRIPTION
___

<h3> GOALS & OBJECTTIVES:</h3>

||
|:-|
|<h4>GOAL 1 :&nbsp; &nbsp; add people</h4><hr><h4>OBJECTIVES :</h4><ul><li>create a base class `person` to derive classes of doctors, patients and other staff members from it later on;<li>class `person`:<ul><li>add appropriate fields to store the basic details of a person;<li>create a method that takes basic details of a person as input from the user side, whenever a new person is to be registered;<li>declare an abstract method to search for a registered person in the database so that it can be defined later in the derived classes;<li>create a method to print the basic details of a person;<li>create a method to remove (un-register) a registered person;</ul></ul>|
|<h4>GOAL 2 :&nbsp; &nbsp; add doctors, patients, nurses, ambulance drivers</h4><hr><h4>OBJECTIVES :</h4><ul><li>derive the classes `doctor, patient, nurse, driver` from the class `person`;<li>define the abstract methods declared inside class `person` in each of the derived classes;<li>re-define some methods inside sub-classes which were already defined in the class `person`, if required;<br>*(for example while registering a driver, in addition to his basic details, his license number will also be required, and, for that, the method* `person::addPerson();` *shall be provided an extended definition to take the license number as input along with the basic details)*;<li>class `doctor`:<ul><li>add a private field `string type;` to store the type of the doctor;<li>add a private field `int appointmentsBooked` to store the number of appointments booked with the doctor for the day;</ul><li>class `patient`:<ul><li>add private fields `int height, weight;` for storing the obvious;<li>add private fields `bool hospitalized, alive;` which tells us if the patient was hospitalized or not and if (hospitalized), is still alive or not;<li>create a method to hospitalize a patient (i.e. change the value of `hospitalized` field of a particular object of class `patient` to `TRUE`);<li>create a method to report a patient's death (i.e. change the value of `alive` field of a particular object of class `patient` to `FALSE`);</ul><li>class `nurse`:<ul><li>add a private field `string type;` to store the type of the nurse;</ul><li>class `driver`:<ul><li>add a private field `string licenseNumber;` to store the obvious;<li>add a private field `bool idle;` to tell whether a driver is idle or not;<br>*(the driver is NOT idle when he/she is going to pick up a patient)*</ul></ul>|
|<h4>GOAL 3 :&nbsp; &nbsp; store address separately, in a structured manner</h4><hr><h4>OBJECTIVES :</h4><ul><li>create a class `address` containing private fields: `string line1, line2, city, state, pinCode, country` to store the address of a location;<li>create appropriate methods to take address as input from the user-side, encrypt (not-really) it into a string to store it into a single cell of a CSV file, decrypt encrypted address string and output the address in a structured manner;<li>create an instance of class `address` in class `person` to store the address and do the required changes in the functions;|
|<h4>GOAL 4 :&nbsp; &nbsp; add ambulances</h4><hr><h4>OBJECTIVES :</h4><ul><li>create a class `ambulance`;<li>add appropriate private fields to store basic details of an ambulance *(id, model, manufacturer, registration number)*;<li>add a private field `bool idle` to tell whether an ambulance is parked (idle) or not;<li>create an instance of class `address` & class `driver` in class `ambulance` to store the details of the address towards which the ambulance is headed & its driver (if the ambulance is NOT idle);<li>create methods to add an ambulance, search for a particular ambulance, print its details and remove it;<li>create a method to send an ambulance to a destination;<ul><li>get an idle ambulance;<li>get an idle driver;<li>if there's no idle ambulance OR if there's no idle driver, throw exception, else change the `idle` fields of the selected objects of class `driver` and class `ambulance` to `FALSE` and; <li>get the address of the destination location as input from the user-side;</ul>|
|<h4>GOAL 5 :&nbsp; &nbsp; store appointment details</h4><hr><h4>OBJECTIVES :</h4><ul><li>create a class `appointment`;<li>create private fields `int id, hour;` to store the ID and starting hour of an appointment;<li>create an instance each of class `doctor` and class `patient`;<li>create methods to search for a booked appointment and print its details;<li>create a method to book an appointment:<ul><li>register the patient if isn't already registered;<li>if already registered let the user search for the patient;<li>then, let the user search for the required doctor;<li>once the doctor is selected, check if his/her appoinments hasn't reached the max limit for the day, i.e. check if the doctor is free;<li>if the doctor is NOT free, throw exception;<li>else if the doctor is free, output the appointment ID and time;</ul>|
|<h4>GOAL 6 :&nbsp; &nbsp; store all the doctors, patients, nurses, drivers, ambulances and appointments in a map</h4><hr><h4>OBJECTIVES :</h4><ul><li>create a class `hospital`;<li>create private fields (static maps) inside it to store all the doctors, patients, nurses, drivers, ambulances and appointments with their `id` as the map's key;<li>make all the mentioned classes friend class of class `hospital` so that they can access these maps;<li>create two methods inside all the classes (`doctor, patient, nurse, driver, ambulance and appointment`) **to fill** the data from their CSV file into their (corresponding) static map & **to overwrite** the data stored inside their map (featuring all the amendments done by the user) to their (corresponding) CSV file;<br>*(the first method will be used with the start of the system and the latter while exiting the system);*<li>create public methods inside class `hospital` one for each of the entities: `doctor, patient, nurse, driver, ambulance and appointment` to print the details of each of their object stored in the corresponding static map from class `hospital`;|
|<h4>GOAL 7 :&nbsp; &nbsp; Implement Limits</h4><hr><h4>OBJECTIVES :</h4><ul><li>inside class hospital, create private fields (of type **`static const int`**) `doctorsLimit, nursesLimit, driversLimit, ambulancesLimit, appointmentsLimit`;<li>in the add methods of these entities (that function which is used to register/add a new object of that entity) add a condition in the beginning to check whether the limit is reached, if it's reached then throw an exception;*|
___

<br>
  
  
### SYSTEM DESIGN
<br>
  
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
