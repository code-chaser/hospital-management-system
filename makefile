all: ./build/hms
./build/hms: main.cpp ./src/global.cpp ./src/address.cpp ./src/person.cpp ./src/doctor.cpp ./src/patient.cpp ./src/appointment.cpp ./src/nurse.cpp ./src/driver.cpp ./src/ambulance.cpp
	g++ -o "./build/hms" main.cpp ./src/global.cpp ./src/address.cpp ./src/person.cpp ./src/doctor.cpp ./src/patient.cpp ./src/appointment.cpp ./src/nurse.cpp ./src/driver.cpp ./src/ambulance.cpp
clean:
	rm -f "./build/hms"
clean(win):
	del /f build\hms.exe
