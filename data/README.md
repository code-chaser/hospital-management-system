<br>
<h2 align="center"> DISCLAIMER </h2>

All the data contained in these documents ( `*.csv` ) is exhaustively random, any resemblance to an actual person's data, living or dead, is purely coincidental.



___

<br>

# Description of Data Storage

All the data of this **hospital-management-system** is stored in **CSV** (Comma-Seperated-Value) files, because of two major reasons:
- these plain-text files can be easily converted to spreadsheets, thus making it human-readable, plus;
- CSV files are easy to parse, making data extraction easier.

<br>

___
### Commonly used column headers in project's CSV files:

<br>

|S.No.|Header(s)|Description|
|-----|:---:|-----------|
|1.|id|ID : string (composed of positive integers);|
|2.|firstName|First Name of a person : string;|
|3.|lastName| Last Name of a person : string (might be blank);|
|4.|gender|Gender of a person : string (composed of a char, either 'M' or 'F');|
|5.|age|Age of a person : string (composed of positive integers);|
|6.|mobNumber|Mobile Number of a person : string;|
|7.|address|Address of a place : string;<br><br>Formation of the address string :<br><ul><li>values of the different fields of the class `address` i.e. `line1, line2, city, state, pinCode, country` are pushed into the address string seperated by a [backtick](https://en.wikipedia.org/wiki/Grave_accent) character, since commas (`,`) are already used by csv files for differentiating adjacent cells of the same row;</li><li>also, since values of the fields `line1` and `line2` might contain commas (`,`), so, before storing them, an iteration is performed over them and each `,` is replaced by `^`;</li></ul> |
<br>

___
