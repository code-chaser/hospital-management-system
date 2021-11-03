# hospital-management-system &nbsp; ![Generic badge](https://img.shields.io/badge/Semester-Project-red.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://en.wikipedia.org/wiki/MIT_License) <!--![views](https://visitor-badge.glitch.me/badge?page_id=code-chaser.hospital-management-system)--> &nbsp;

<br>

## INTRODUCTION
It's a hospital management system, that can be used to keep records of doctors, their appointments, patients, nurses, ambulances and ambulance drivers.

___

<br>

## SET-UP INSTRUCTIONS
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

<br>

## FEATURES & LIMITATIONS
___
#### FEATURES

- **Book a new appointment** - system automatically alots a free time slot of the selected doctor to the patient and if no free time slot available, it reports so.
- **System automatically clears appointments of dates older than today**
- **Get an appointment's details**.
- **Register a new patient, doctor, nurse, ambulance & ambulance driver** - a unique ID is provided by the system itself.
- **Remove (Unregister) them**.
- **Get their details** - filter options: Unique ID, Name, Mobile Number, Type - for doctors and nurses.
- **Keep a history record of staff and patients and fetch details from history**
- **Hospitalize a registered patient**
- **Discharge a hospitalized patient**
- **Report a death of a patient**
- **Send an ambulance to an address** - the system itself checks for an idle ambulance and an idle driver and if not available, it reports so.
- **Report arrival of ambulance** - along with ambulance's status, system automatically updates the status of the driver who was sent with that ambulance as well.

___
#### LIMITATIONS

- Appointments can only be booked for the same day. Future appointment booking is not possible yet.
- Appointment slots are fixed for doctors and cannot be changed. They're of 1 hour length and from 9:00 AM to 5:00 PM.
- There's no support for checking beds' availability while hospitalizing a patient.


___

<br>
<br>


___
>##### *Hope you like it! :)*
___
