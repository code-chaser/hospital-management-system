# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/Semester-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) &nbsp;
## INTRODUCTION
A hospital management system, made using object oriented programming and file handling in C++, that keeps records of doctors & their appointments, patients, staff, ambulances, etc. ...

___


#### GO TO:
- [**GOALS & OBJECTTIVES**](https://github.com/code-chaser/hospital-management-system/blob/main/docs/project-documentation.md#-goals--objecttives)
- [**SYSTEM DESIGN**](https://github.com/code-chaser/hospital-management-system/blob/main/docs/project-documentation.md#system-design)
- [**DATA STORAGE**](https://github.com/code-chaser/hospital-management-system/blob/main/docs/project-documentation.md#data-storage)
- [**IMPLEMENTATION**](https://github.com/code-chaser/hospital-management-system/blob/main/docs/project-documentation.md#implementation)

___


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
|<h4>GOAL 7 :&nbsp; &nbsp; implement limits</h4><hr><h4>OBJECTIVES :</h4><ul><li>inside class hospital, create private fields (of type **`static const int`**) `doctorsLimit, nursesLimit, driversLimit, ambulancesLimit, appointmentsLimit`;<li>in the add methods of these entities (that function which is used to register/add a new object of that entity) add a condition in the beginning to check whether the limit is reached, if it's reached then throw an exception;|
|<h4>GOAL 8 :&nbsp; &nbsp; keep a history record of all the entities</h4><hr><h4>OBJECTIVES :</h4><ul><li>for all the entities, create **`*History.csv`** files for storing their data even after the entity is no longer a part of the hospital;<li>in the `add/register` funtions of all the entities after adding them to their corresponding static map, create a record of them in their corresponding `*History.csv` file as well;<li>the history records are of not much use for the functionalitites, so, no need to create seperate static maps for them, whenever needed they can be directly accessed through file handling;|
___

  <br>
  
### SYSTEM DESIGN
  
|CLASS|DESCRIPTION|
|:-----:|-----------|
|address|<ul><li>stores the address of a location in a structured manner in its private fields: `line1, line2, city, state, pinCode, country`;<li>has publicly accessible methods to take address as input, output it in a particular manner, generate & return string of a specific format from some address and read the same string to generate back the same address, whenever required ([read more](https://github.com/code-chaser/hospital-management-system/blob/main/docs/address.md));|
|**_person_**|<ul><li>it's an **_abstract class_** containing **_5 abstract (pure virtual) methods_**;<li>**'has-a'** (object of class) `address`;<li>stores all the basic information of a person in its private fields: `id, firstName, lastName, gender, age, mobNumber, add`;<li>has publicly accessible methods to take the information as input, print it and fill it in an object;<li>class `doctor`, `patient`, `nurse` & `driver` **'inherits'** class `person` and in addition contains a few class-specific fields and methods;
|appointment|<ul><li>**'has-a'** (object of class) `doctor` and **'has-a'** (object of class) `patient`;<li>in addition, it has two more private member fields : `id, hh` to store the appointment ID and its starting hour (in 24-Hr format);<li>has publicly accessible methods to book an appointment, get and print details of a booked appointment;|
|ambulance|<ul><li>**'has-a'** (object of class) `driver` and **'has-a'** (object of class) `address`;<li>in addition, has a few more private fields to store the basic details of an ambulance;<li>has publicly accessible methods to register an ambulance, print its details, send an ambulance to a destination and report its arrival;|
|hospital|<ul><li>contains the list of all the entities (**'has-a'**): `doctor, patient, appointment, nurse, driver, ambulance` (stores them in a privately accessible map with their `id` as the key);<li>classes `doctor, patient, appointment, nurse, driver, ambulance` are all `friend class` of class `hospital` and they all contain publicly accessible methods `void fillMap();` & `void saveMap();` to fill & overwrite their respective maps (contained in class `hospital`) from and to their respective `*.csv` files at the startup and closing of the program, respectively;<li>in addition, has private fields to store the limits of all the entities;<li>all members of this class are static, so, it doesn't require instantiation;|
___



![UML Class Diagram](https://user-images.githubusercontent.com/63065397/125205629-d5877080-e2a0-11eb-9f9e-56154600fe32.jpeg)


___

  <br>
  
### DATA STORAGE
  - for data storage details: kindly refer to this [link](https://github.com/code-chaser/hospital-management-system/blob/main/data/README.md) 
  ___
  
  <br>
  
### IMPLEMENTATION
  
  - ### `fillMap();` functions:
  
    - these functions are defined in the classes of each and every entity i.e. classes `doctor, patient, nurse, driver, ambulance, appointment`;
    -it fetches saved data from the class's corresponding CSV file using a `fstream` object and save it in its corresponding **`static map`** for further use by all other methods;
  
    - *for example following is the* `doctor::fillMap();` *function:*<br><br>
    ```cpp
    void doctor::fillMap()
    {
        fstream f;
        f.open("./data/doctors.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
  
            //reading data from doctors.csv file and
            //filling it in the doctor class object 'd'
            //long code - omitted!
  
            hospital::doctorsList[d.id] = d;
        }
        f.close();
        return;
    }
    ```

  <br>

  - ### `saveMap();` functions:
  
    - these functions, again, are defined in the classes of each and every entity i.e. classes `doctor, patient, nurse, driver, ambulance, appointment`;
    - it overwrites the changed data, present inside the corresponding **`static map`**, (changed by the user during the span of the program) to the corresponding CSV file using a `fstream` object;
  
    - *for example following is the* `doctor::saveMap();` *function:*<br><br>
    ```cpp
    void doctor::saveMap()
    {
        fstream f;
        f.open("./data/temp.csv", ios::out);
        // `le first line conataining column headers:
        f << "doctorId,firstName,lastName,gender,age,mobNumber,address,type,appointmentsBooked\n";
        for (auto i : hospital::doctorsList)
            f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
              << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
              << "," << i.second.type << "," << i.second.appointmentsBooked << endl;
        f.close();
        remove("./data/doctors.csv");
        rename("./data/temp.csv", "./data/doctors.csv");
        return;
    }
    ```

  <br>
  
- ### `addPerson();` functions:
  
    - **`person::addPerson();`** :&nbsp; &nbsp;takes the first name, last name, age, gender, mobile number and address as the input;<br><br>
  
    - class-specific **`addPerson();`** function :&nbsp; &nbsp;includes a function call to its base class copy `person::addPerson();` and once the basic details are input, the class specific addPerson(); funtion takes class-specific details as input from the user side;
  
    - *for example following is the* `doctor::addPerson();` *function:*<br><br>
    ```cpp
    void doctor::addPerson()
    {
        if (hospital::doctorsList.size() == hospital::doctorsLimit)
        {
            cout<<"\n\nDoctors limit reached, can't add more!\n\n";
            return;
        }
        //18 and 65 are the age limits for registration of a new doctor;
        person::addPerson(18, 65);
        //called base class version of addPerson(); to get the basic details as input;
        if ((age < 18) || (age > 65))
            return;
        cout << "\nEnter the type of the doctor: \n";
        //now, getting doctor specific details;
        getline(cin >> ws, type);
        if (hospital::doctorsList.rbegin() != hospital::doctorsList.rend())
            id = ((hospital::doctorsList.rbegin())->first) + 1;
        else
            id = 1;
        hospital::doctorsList[id] = *this;

        //creating a fstream object to read/write from/to files;
        fstream f;
        //creating a record in doctorsHistory.csv;
        f.open("./data/doctorsHistory.csv", ios::app);
        f << firstName << "," << lastName << "," << gender << "," << age << "," 
          << mobNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
        f.close();

        cout << "\n" << firstName << " " << lastName << " registered successfully!\n";
        cout << "Their ID is: " << id << "\n";

        return;
    }
    ```
  
    - *add function of class* `ambulance` *i.e.* `addAmbulance();` *works in a similar fashion*;

  <br>
 
- ### `printDetails();` functions:
  
    - **`person::printDetails();`** :&nbsp; &nbsp;prints the first name, last name, age, gender, mobile number and address of the object that invoked the class-specific `printDetails();` function;<br><br>
    
    - class-specific **`printDetails();`** function :&nbsp; &nbsp;includes a function call to its base class copy `person::printDetails();` and once the basic details are printed, the class specific printDetails(); funtion prints class-specific details of the object that invoked this function;
  
    - *for example following is the* `doctor::printDetails();` *function:*<br><br>
    ```cpp
    void doctor::printDetails()
    {
        if (id == -1)
            return;
        person::printDetails();
        //called its base class version, to print the basic details;
        //now printing class-specific details;
        cout << "Type            : " << type << "\n";
        cout << "Appointments    : " << appointmentsBooked << "/8 (appointments booked today)\n";
        return;
    }
    ```

  <br>
  
 - ### `printDetailsFromHistory(string extraDetails = "");` functions:
  
    - **`person::printDetailsFromHistory();`** :&nbsp; &nbsp;prints the first name, last name, age, gender, mobile number and address of the object that invoked the class-specific `printDetailsFromHistory();` function;<br><br>
    
    - class-specific **`printDetailsFromHistory();`** function :&nbsp; &nbsp;includes a function call to its base class copy `person::printDetailsFromHistory();` and once the basic details are printed, the class specific printDetailsFromHistory(); funtion prints class-specific details of the object that invoked this function;
    - the argument `string extraDetails` contains all those details from the class's corresponding `*History.csv` file which couldn't be stored inside the object of the class but were required to be printed, *for example, the file `doctorsHistory.csv` contains two extra columns, `leftWork?` to tell if the doctor is still registered with the hospital or not and `reasonForLeaving` to tell (if the doctor has left work) the reason why he/she left the hospital, these two values have no place in the class `doctor` object to be stored, so, the last part (after the second last `,` (comma char)) of the `doctorsHistory.csv` file is stored as it is in the string `extraDetails`*;
  
    - *for example following is the* `doctor::printDetailsFromHistory();` *function:*<br><br>
    ```cpp
    void doctor::printDetailsFromHistory(string extraDetails = "")
    {
        if (id == -1)
            return;
        person::printDetailsFromHistory();
        stringstream k(extraDetails);
        string s1, s2;
        getline(k, s1, ',');
        getline(k, s2, ',');

        if (extraDetails == "")
        {
            //in case those extra details are not passed by the calling function,
            //we get them manually from the CSV file;
            //long code - omitted!
        }
        cout << "Type            : " << type << "\n";
        cout << "Left Work?      : " << s1 << "\n";
        if (s1 == "Y")
            cout << "Reason          : " << s2 << "\n";
        return;
    }
    ```

  <br>

  - ### `getDetails();` & `getDetailsFromHistory();` functions:
  
    - these functions are defined in the classes of each and every entity i.e. classes `doctor, patient, nurse, driver, ambulance, appointment`;
    - they let the user search for the required entry in the class's corresponding static map (getDetails();) & class's corresponding `*History.csv` file (getDetailsFromHistory();) (respectively) and then fills the details of the selected entry into the calling object for further use;
    - `getDetails();` function can directly use the filled `static map` for the data; but `getDetailsFromHistory();` has to access the History CSV file, as there's no map storing history data;
  
  <br>
  
  - ### `removePerson();` functions:
  
    - these functions are defined in the classes derived from class `person` i.e. classes `doctor, patient, nurse, driver` *(has a slightly different meaning for class* `patient`*, there it rather means "discharge a patient", name of the function is same though)*;
    - funtioning:
        - first of all, it gives a call to class's `getDetails();` function to let the user search and select the person to be removed;
        - once selected, it checks if the selected person can be removed (in case of doctor, checks if the doctor has no appointments booked for the day);
        - if can be removed, then it deletes that person's object from the class's corresponding `static map` and in the History CSV file, marks the appropriate column to denote that the person is no longer a part of the hospital;
  
    - *for example following is the* `doctor::removePerson();` *function:*<br><br>
    ```cpp
    void doctor::removePerson()
    {
        cout << "\nSearch for the doctor you want to remove.\n";
        getDetails();
        if (id == -1)
            return;
        if (appointmentsBooked > 0)
        {
            cout << "\nSelected doctor has appointments booked for today, can't be removed.\n\n";
            return;
        }
        hospital::doctorsList.erase(id);

        //a new file temp.csv is created then each and every line of;
        //doctorsHistory.csv is copied to temp.csv except for the line;
        //of the person to be removed, that line is stored in a string;
        //required changes are made to it and it's pasted in the place of;
        //original line, in temp.csv file.
        //long code - omitted!
        //after that doctorsHistory.csv is removed and temp.csv is renamed.
        remove("./data/doctorsHistory.csv");
        rename("./data/temp.csv", "./data/doctorsHistory.csv");
        cout << firstName << " " << lastName << " removed successfully!\n";
        return;
    }
    ```
      - *remove function of class* `ambulance` *i.e.* `removeAmbulance();` *works in a similar fashion*;

  <br>
  
  - ### `patient::hospitalize();` & `patient::reportADeath();` functions:
    - these functions are implemented really simply, they just change the values of `patient` class fields `bool hospitalized, alive;` to TRUE and FALSE respectively
    - in addition, they also change the values of `patientsHistory.csv` file's columns, namely "was Hospitalized?", "still Alive?" to 'Y' and 'N' respectively;
  
  <br>
  
  - ### `ambulance::send();` function:
    - it fetches an idle ambulance and an idle driver and then changes their `bool idle;` fields to FALSE, takes the address of the destination location from the user side as input and sends the ambulance to that address;
    - functioning:
        - searches in the map `hospital::ambulancesList` for the first ambulance which has its `bool idle;` field set as TRUE, and if not found prints not found message and returns the control, else moves further;
        - searches in the map `hospital::driversList` for the first driver which has its `bool idle;` field set as TRUE, and if not found prints not found message and returns the control, else moves further;
        - takes the address of the location where the ambulance is to be sent as input from the user side;
        - adds that address into `address add` field of the ambulance object;<br><br>
  
    ```cpp
    void ambulance::send()
    {
        //*************picking an idle ambulance*************;
        bool gotOne = 0;
        for (auto i : hospital::ambulancesList)
        {
            if (i.second.idle)
            {
                *this = i.second;
                gotOne = 1;
                break;
            }
        }
        if (!gotOne)
        {
            cout << "No, idle ambulance found!" << "\n";
            return;
        }
        //*************  picking a free driver  *************;
        gotOne = 0;
        for (auto i : hospital::driversList)
        {
            if (i.second.idle)
            {
                D = i.second;
                gotOne = 1;
                break;
            }
        }
        if (!gotOne)
        {
            cout << "No, idle driver found!" << "\n";
            return;
        }
        idle = 0;
        cout << "Enter destination address:\n";
        add.takeInput();
        //updating status of ambulance;
        hospital::ambulancesList[id] = *this;
        //updating status of driver;
        hospital::driversList[D.id].idle = 0;
        cout << model << " by " << manufacturer << " sent with driver " 
             << D.firstName << " " << D.lastName << " (ID = " << D.id << ") successfully!\n";
        return;
    }
    ```

  <br>
  
  - ### `ambulance::reportArrival();` function:
    - implementation of this function is pretty simple;
    - firstly it gives the call to `ambulance::getDetails();` function to let the user select the ambulance whose arrival is to be reported;
    - once selected, it just changes the `bool idle;` fields of the associated driver and ambulance objects to TRUE;<br><br>
  
    ```cpp
    void ambulance::reportArrival()
    {
        getDetails();
        
        //updating status of driver;
        hospital::driversList[D.id].idle = 1;

        //updating status of ambulance;
        hospital::ambulancesList[id].idle = 1;
        hospital::ambulancesList[id].add.strToAdd("`````");
        driver d;
        hospital::ambulancesList[id].D = d;

        cout << "\nStatus updated successfully!\n\n";
        return;
    }
    ```

<br>

___
___
