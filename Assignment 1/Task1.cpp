#include <iostream>
#include <string>
using namespace std;

class Skill;
class Sport;
class Mentor;

class Skill {
    string skillName;
    int skillID;
    string description;

public:
    Skill(string skillName, int skillID, string description) {
        this->skillName = skillName;
        this->skillID = skillID;
        this->description = description;
    }

    void showSkillDetails() {
        cout << "Skill Name: " << skillName << endl;
        cout << "Skill ID: " << skillID << endl;
        cout << "Description: " << description << endl;
        cout << endl;
    }

    void updateSkillDescription(string newDescription) {
        description = newDescription;
        cout << "Old description updated to new description: " << description << endl;
    }

    string getSkillName() {
        return skillName;
    }
};

class Sport {
    string name;
    int sportID;
    string description;
    Skill** requiredSkills;
    int skillsCount;
    int skillsCapacity;

public:
    Sport(string name, int sportID, string description) {
        this->name = name;
        this->sportID = sportID;
        this->description = description;
        this->skillsCount = 0;
        this->skillsCapacity = 4;
        requiredSkills = new Skill*[skillsCapacity];
    }

    ~Sport() {
        delete[] requiredSkills;
    }

    void addSkill(Skill* S);

    void removeSkills(Skill* S) {
        bool found = false;
        for (int i = 0; i < skillsCount; i++) {
            if (requiredSkills[i] == S) {
                for (int j = i; j < skillsCount - 1; j++) {
                    requiredSkills[j] = requiredSkills[j + 1];
                }
                skillsCount--;
                found = true;
                cout << "Skill: " << S->getSkillName() << " removed successfully..." << endl;
                break;
            }
        }
        if (!found) {
            cout << "There is no skill: " << S->getSkillName() << " to remove." << endl;
        }
    }

    void displaySportDetails() {
        cout << endl;
        cout << "Sport Name: " << name << endl;
        cout << "Sport ID: " << sportID << endl;
        cout << "Description: " << description << endl;
        cout << "Required skills are: " << endl;
        for (int i = 0; i < skillsCount; i++) {
            cout << "Skill " << i + 1 << ": " << requiredSkills[i]->getSkillName() << endl;
        }
        cout << endl;
    }
};

class Student {
    int studentID;
    string name;
    int age;
    string* sportsInterests;
    int interestCount;
    int interestCapacity;
    Mentor* mentorAssigned;

public:
    Student(int studentID, string name, int age) {
        this->studentID = studentID;
        this->name = name;
        this->age = age;
        interestCount = 0;
        interestCapacity = 4;
        mentorAssigned = nullptr;
        sportsInterests = new string[interestCapacity];
    }

    ~Student() {
        delete[] sportsInterests; 
    }

    void registerForMentorship(Mentor* m);

    void viewMentorDetails();

    void updateSportsInterest(string interest) {
        if (interestCount < interestCapacity) {
            sportsInterests[interestCount++] = interest;
            cout << "Interest updated successfully: " << interest << endl;
        } else {
            cout << "Interest cannot be updated due to over the limit..." << endl;
        }
    }

    void displayStudentDetails() {
        cout << "Student name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Student age: " << age << endl;
        cout << "Sport interests: " << endl;
        for (int i = 0; i < interestCount; i++) {
            cout << "Sport interest " << i + 1 << ": " << sportsInterests[i] << endl;
        }
    }

    string getName() {
        return name;
    }
};

class Mentor {
    string name;
    int mentorID;
    string* sportsExercise;
    int exerciseCount;
    int exerciseCapacity;
    Student** assignedLearners;
    int learnerCount;
    int learnerCapacity;

public:
    Mentor(string name, int mentorID) {
        this->name = name;
        this->mentorID = mentorID;
        exerciseCount = 0;
        exerciseCapacity = 4;
        learnerCount = 0;
        learnerCapacity = 3;
        sportsExercise = new string[exerciseCapacity];
        assignedLearners = new Student*[learnerCapacity];
    }

    ~Mentor() {
        delete[] sportsExercise; // Free dynamically allocated memory
        delete[] assignedLearners;
    }

    void addExercise(string exercise) {
        if (exerciseCount < exerciseCapacity) {
            sportsExercise[exerciseCount++] = exercise;
            cout << "Exercise " << exercise << " added successfully..." << endl;
        } else {
            cout << "No enough space..." << endl;
        }
    }

    void assignLearner(Student* s) {
        if (learnerCount < learnerCapacity) {
            assignedLearners[learnerCount++] = s;
            cout << "Student: " << s->getName() << " assigned to mentor: " << name << endl;
        } else {
            cout << "The learner cannot be assigned. Limit is over." << endl;
        }
    }

    void removeLearners(Student* s) {
        bool found = false;
        for (int i = 0; i < learnerCount; i++) {
            if (assignedLearners[i] == s) {
                for (int j = i; j < learnerCount - 1; j++) {
                    assignedLearners[j] = assignedLearners[j + 1];
                }
                learnerCount--;
                found = true;
                cout << "Student: " << s->getName() << " removed by mentor: " << name << endl;
                break;
            }
        }
        if (!found) {
            cout << "Student not found from mentor: " << name << endl;
        }
    }

    void viewLearners() {
        cout << "Mentor " << name << "'s assigned learners are: " << endl;
        for (int i = 0; i < learnerCount; i++) {
            cout << " " << i + 1 << ": " << assignedLearners[i]->getName() << endl;
        }
    }

    void provideGuidance() {
        cout << "Mentor " << name << " is providing guidance..." << endl;
    }

    string getName() {
        return name;
    }

    void viewMentorDetails() {
        cout << "Name: " << name << endl;
        cout << "Mentor ID: " << mentorID << endl;
        cout << "Sports Exercises: " << endl;
        for (int i = 0; i < exerciseCount; i++) {
            cout << "Exercise " << i + 1 << ": " << sportsExercise[i] << endl;
        }
    }
};

void Student::registerForMentorship(Mentor* m) {
    mentorAssigned = m;
    m->assignLearner(this);
    cout << "Student " << name << " registered for mentorship with " << m->getName() << endl;
}

void Student::viewMentorDetails() {
    if (mentorAssigned != nullptr) {
        mentorAssigned->viewMentorDetails();
    } else {
        cout << "No mentor assigned to " << name << endl;
    }
}

void Sport::addSkill(Skill* S) {
    if (skillsCount < skillsCapacity) {
        requiredSkills[skillsCount++] = S;
        cout << "Skill: " << S->getSkillName() << " added successfully..." << endl;
    } else {
        cout << "There is no capacity to add any skill..." << endl;
    }
}

int main() {
    Skill skill1("Backhand", 434, "Mastering the backhand stroke in tennis");
    skill1.showSkillDetails();

    Skill skill2("Dribbling", 234, "Improving dribbling skills for basketball");
    skill2.showSkillDetails();

    Sport tennis("Tennis", 123, "A racket sport played individually or in doubles.");
    tennis.displaySportDetails();

    Sport basketball("Basketball", 545, "A team sport where the goal is to score by shooting a ball through a hoop.");
    basketball.displaySportDetails();

    tennis.addSkill(&skill1);
    tennis.displaySportDetails();

    basketball.addSkill(&skill2);
    basketball.displaySportDetails();

    Mentor M("Sahil Kumar", 3);
    M.viewMentorDetails();

    Student S1(1, "Dev Kumar", 20);
    S1.displayStudentDetails();

    Student S2(2, "Gotam Lal", 21);
    S2.displayStudentDetails();

    S1.registerForMentorship(&M);
    S2.registerForMentorship(&M);

    S1.viewMentorDetails();

    S1.updateSportsInterest("Tennis");

    M.provideGuidance();

    M.removeLearners(&S1);

    M.viewLearners();

    return 0;
}
