#ifndef PATIENT
#define PATIENT
using namespace std;
class patient
{
private:
    int patientId;
    string firstname, lastname;
    int8_t age;
    char gender;

public:
    void addAPatient()
    {
        cout << "\nEnter the name of the patient: \nFirst Name:\n";
        getline(cin >> ws, firstname);
        cout << "\nLast name:\n";
        getline(cin >> ws, lastname);
        cout << "\nEnter the age of the patient: \n";
        cin >> age;
        while (age <= 0)
            cout << "Was that supposed to make any kind of sense?\nEnter again!\n", cin >> age;
        cout << "\nEnter the gender of the patient (M = Male || F = Female): \n";
        cin >> gender;
        while (gender != 'M' && gender != 'F')
            cout << "M or F?\n", cin >> gender;
        fstream f;
        f.open("./doctors/doctors.csv", ios::app);
        f << firstname << "," << lastname << "," << age << "," << gender << endl;
        f.close();
        return;
    }
};
#endif // !CLASS_PATIENT