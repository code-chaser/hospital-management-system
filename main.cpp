#include <iostream>
#include <fstream>
#include <cmath>
#include "./doctors/doctor.cpp"
#include "./patients/patient.cpp"
using namespace std;

int main(){
    while(1){
        int purpose=0;
        cout<<"\nPurpose?\n";
        cout<<"1  : Book an appointment\n";
        cout<<"2  : Check appointment status\n";
        cout<<"3  : Cancel an appointment\n";
        cout<<"4  : Add a patient\n";
        cout<<"5  : Hospitalize a patient\n";
        cout<<"6  : Remove a patient\n";
        cout<<"7  : Add a doctor\n";
        cout<<"8  : Get doctor details\n";
        cout<<"9  : \n";
        cout<<"10 : \n";
        cout<<"11 : \n";
        cout<<"12 : \n";
        cout<<"-1 : Exit\n";
        cin>>purpose;
        if(purpose==-1){
            cout<<"Shutting Down System...\n\n";
            return 0;
        }
        if(purpose==1){

        }
        else if(purpose==2){

        }
        else if(purpose==3){
            
        }
        else if(purpose==4){
            
        }
        else if(purpose==5){
            
        }
        else if(purpose==6){
            
        }
        else if(purpose==7){
            doctor d;
            d.addADoctor();
        }
        else if(purpose==8){
            doctor d;
            d.printDetails(d.getADoctor(d));
        }
        else if(purpose==9){
            
        }
        else if(purpose==10){
            
        }
        else if(purpose==11){
            
        }
        else if(purpose==12){
            
        }
    }
    return 0;
}

