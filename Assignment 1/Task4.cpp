#include<iostream>
#include<string>
using namespace std;

const int studentNO = 1500;
const int stopsNO = 40;

class Student {
    string name;
    int studentID;
    bool isStudentRegistered;
    bool isSemesterFeePaid;

    public:
    Student(string name = "",int studentID = 0,bool isStudentRegistered = false,bool isSemesterFeePaid = false)
    : name(name), studentID(studentID), isStudentRegistered(isStudentRegistered), isSemesterFeePaid(isSemesterFeePaid) {}

    int getStudentID() const {
        return studentID;
    }
    string getStudentName() const {
        return name;
    }
    bool getIsStudentRegistered() const {
        return isStudentRegistered;
    }
    bool getIsSemesterFeePaid() const {
        return isSemesterFeePaid;
    }

    void registerStudents() {
        isStudentRegistered = true;
        cout<<"Student: "<<name<<" with ID: "<<studentID<<" is registered for transportation"<<endl;
    } 

    void PayFee() {
        isSemesterFeePaid = true;
        cout<<"Student: "<<name<<" with ID: "<<studentID<<" has paid the fee..."<<endl;
    }

};

class Stop {
    int stopID;
    string stopName;
    
    public:
    Stop(int stopID = 0,string stopName = "") : stopID(stopID) , stopName(stopName) {}

    int getStopID() const {
        return stopID;
    }
    string getStopName() const {
        return stopName;
    }

    void setStopID(int stopID) {
        this->stopID = stopID;
    }
    void setStopName(string stopName) {
        this->stopName = stopName;
    }

}; 

class Route {
    string routeName;
    int routeID;
    Stop S[stopsNO];
    int stopCount;

    public:
    Route(string routeName = "",int routeID = 0) : routeName(routeName), routeID(routeID), stopCount(0) {}
    
    string getRouteName() const {
        return routeName;
    }
    int getRouteNameID() const {
        return routeID;
    }
    int getStopCount() const {
        return stopCount;
    }

    void addStops(const Stop &S1) {
        if(stopCount < stopsNO) {
            S[stopCount++] = S1;
            cout<<"Stop ("<<S1.getStopName()<<") added to route ("<<routeName<<") "<<endl;
        }
        else {
            cout<<"Sorry!!!There is no extra space to add more Stops"<<endl;
        }
    } 
    
    void displayStops() const {
            cout<<"Stops of the route ("<<routeName<<") are..."<<endl;
            for(int i=0;i<stopCount;i++) {
                cout<<"Stop "<<i+1<<". "<<S[i].getStopName()<<endl;
            }
    }
};

class Bus {
    int busID;
    Route R1;
    Student stud[studentNO];
    int studentCount;

    public:
    Bus(int busID = 0,const Route& R1 = Route()) : busID(busID), R1(R1), studentCount(0) {}

    int getBusID() const {
        return busID;
    }
    Route getRoute() const {
        return R1;
    }

    void addStudent(const Student& stud1) {
        if(studentCount < studentNO) {
            stud[studentCount++] = stud1;
            cout<<"Student ("<<stud1.getStudentName()<<") ID: ("<<stud1.getStudentID()<<" is added to bus ("<<busID<<") "<<endl;
        }
    }

    void checkAttendance(int studentID) {
        for(int i=0;i<studentCount;i++) {
            if(stud[i].getStudentID() == studentID) {
                cout<<"Attendance of the student ("<<stud[i].getStudentName()<<") ID ("<<studentID<<") checked successfully"<<endl;
                return;
            }
        }
        cout<<"Student of ID: "<<studentID<<" is not found on bus: "<<busID<<endl;
    }
};

int main() {
    Student Stu1("Sahil Kumar",100);
    Student Stu2("Dev Kumar",101);

    Stu1.registerStudents();
    Stu2.registerStudents();

    Stu1.PayFee();
    Stu2.PayFee();

    Stop Stp1(90,"Gulshan Hadeed");
    Stop Stp2(91,"Clifton");
    Stop Stp3(92,"Malir cant");
    cout<<endl;
    Route route1("Route 9",50);
    route1.addStops(Stp1);
    route1.addStops(Stp2);
    route1.addStops(Stp3);
    cout<<endl;
    route1.displayStops();
    cout<<endl;
    Bus B1(60,route1);
    B1.addStudent(Stu1);
    B1.addStudent(Stu2);
    cout<<endl;
    B1.checkAttendance(101);
    B1.checkAttendance(99);
    B1.checkAttendance(100);

    return 0;
}
