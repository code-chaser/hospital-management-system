## class `address`:
___
the class `address` is made to be able to perform the following tasks:
- take addresses as inputs,
- convert them to a string (of a specified format) and return the string to be saved in `*.csv` files &
- read the same strings to generate back the initially input address and output it.

___
### fields:
the class `address` has the following fields as its private members;
```cpp
    string line1, line2;
    string city;
    string state;
    string pinCode;
    string country;
```

___
### methods:
the class `address` has the following methods as its public members;
```cpp
    address();
    void takeInput();
    void print();
    string addToStr();
    void strToAdd(string);
```
___
### funtioning:
- `address();` : the constructor of the class initializes all the fields of the class by an empty string i.e. `""`;
- `void takeInput();` : this function takes each of the fields (all are of type `string`) as input from the user side;
- `void print();` : this function outputs each of the fields in a structured manner;
- `string addToStr();` : this function converts the address contained in the fields of address object that called this funtion into a string (of specified format) and returns it;

    - values of the different fields i.e. `line1, line2, city, state, pinCode, country` are pushed into the address string seperated by a [backtick](https://en.wikipedia.org/wiki/Grave_accent) character, since commas (`,`) are already used by csv files for differentiating adjacent cells of the same row;
    - also, since values of the fields `line1` and `line2` might contain commas (`,`), so, before storing them, an iteration is performed over them and each `,` is replaced by `^`;

        ```cpp
        for (auto &i : line1)
            if (i == ',')
                i = '^';

        for (auto &i : line2)
            if (i == ',')
                i = '^';

        stringstream s;
        s << line1 << "`" << line2 << "`" << city << "`" << state << "`" << pinCode << "`" << country;
        string add;
        getline(s, add);
        ```

<br>

 - `strToAdd(string);` : takes the address string as the only argument and fills the fields of calling object (aka `this`) accordingly by reading the address string using `getline();` function and an `stringstream` object;

    - the [backtick](https://en.wikipedia.org/wiki/Grave_accent) character is passed as the delimiter to the `getline();` function and the fields are filled one by one;
    - once all the fields are filled, an iteration is performed over the fields `line1` and `line2` and each `^` is replaced back by `,`;

        ```cpp
        stringstream s(str);
        
        getline(s, line1, '`');
        for (auto &i : line1)
            if (i == '^')
                i = ',';

        getline(s, line2, '`');
        for (auto &i : line2)
            if (i == '^')
                i = ',';

        getline(s, city, '`');
        getline(s, state, '`');
        getline(s, pinCode, '`');
        getline(s, country, '`');
        ```

<br>

___