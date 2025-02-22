#include <iostream>
#include <string>

using namespace std;

const int MAX_SKILLS_PER_SPORT = 10;
const int MAX_SPORTS_PER_PERSON = 5;
const int MAX_STUDENTS_PER_MENTOR = 3;

class Skill {
public:
    int skillId;
    string skillName;
    string skillDescription;

    Skill() : skillId(0), skillName(""), skillDescription("") {}

    Skill(int id, const string& name, const string& desc)
        : skillId(id), skillName(name), skillDescription(desc) {}

    void displaySkillInfo() const {
        cout << "Skill ID: " << skillId << ", Skill Name: " << skillName << ", Description: " << skillDescription << endl;
    }
};

class Sport {
public:
    int sportId;
    string sportName;
    string sportDescription;
    Skill skillsRequired[MAX_SKILLS_PER_SPORT];
    int skillCount;

    Sport() : sportId(0), sportName(""), sportDescription(""), skillCount(0) {}

    Sport(int id, const string& name, const string& desc)
        : sportId(id), sportName(name), sportDescription(desc), skillCount(0) {}

    void addRequiredSkill(const Skill& skill) {
        if (skillCount < MAX_SKILLS_PER_SPORT) {
            skillsRequired[skillCount++] = skill;
        } else {
            cout << "Maximum skills reached for this sport." << endl;
        }
    }

    void displaySportInfo() const {
        cout << "Sport ID: " << sportId << ", Sport Name: " << sportName
             << ", Description: " << sportDescription << endl;
        cout << "Required Skills: " << endl;
        for (int i = 0; i < skillCount; i++) {
            skillsRequired[i].displaySkillInfo();
        }
    }
};

class Mentor {
public:
    int mentorId;
    string mentorName;
    Sport expertise[MAX_SPORTS_PER_PERSON];
    int expertiseCount;
    int maxStudents;
    int studentsAssigned[MAX_STUDENTS_PER_MENTOR];
    int studentCount;

    Mentor(int id, const string& name, int maxStudentsAllowed)
        : mentorId(id), mentorName(name), maxStudents(maxStudentsAllowed), expertiseCount(0), studentCount(0) {}

    void assignStudent(int studentId) {
        if (studentCount < maxStudents) {
            studentsAssigned[studentCount++] = studentId;
            cout << "Student " << studentId << " assigned to mentor " << mentorName << "." << endl;
        } else {
            cout << "Mentor " << mentorName << " has reached maximum student capacity." << endl;
        }
    }

    void removeStudent(int studentId) {
        bool found = false;
        for (int i = 0; i < studentCount; i++) {
            if (studentsAssigned[i] == studentId) {
                for (int j = i; j < studentCount - 1; j++) {
                    studentsAssigned[j] = studentsAssigned[j + 1];
                }
                --studentCount;
                cout << "Student " << studentId << " removed from mentor " << mentorName << "." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student " << studentId << " not found for mentor " << mentorName << "." << endl;
        }
    }

    void showAssignedStudents() const {
        cout << "Mentor " << mentorName << " has students: ";
        for (int i = 0; i < studentCount; i++) {
            cout << studentsAssigned[i] << " ";
        }
        cout << endl;
    }

    void giveGuidance() const {
        cout << "Mentor " << mentorName << " is providing guidance." << endl;
    }

    void addExpertise(const Sport& sport) {
        if (expertiseCount < MAX_SPORTS_PER_PERSON) {
            expertise[expertiseCount++] = sport;
        } else {
            cout << "Mentor " << mentorName << " has reached maximum sports expertise." << endl;
        }
    }

    void displayMentorInfo() const {
        cout << "Mentor ID: " << mentorId << ", Mentor Name: " << mentorName << endl;
        cout << "Sports Expertise: " << endl;
        for (int i = 0; i < expertiseCount; i++) {
            expertise[i].displaySportInfo();
        }
    }
};

class Student {
public:
    int studentId;
    string studentName;
    int studentAge;
    Sport interests[MAX_SPORTS_PER_PERSON];
    int interestCount;
    Mentor* assignedMentor;

    Student(int id, const string& name, int age)
        : studentId(id), studentName(name), studentAge(age), interestCount(0), assignedMentor(nullptr) {}

    void registerWithMentor(Mentor* mentor) {
        if (assignedMentor == nullptr) {
            assignedMentor = mentor;
            mentor->assignStudent(studentId);
            cout << "Student " << studentName << " registered with mentor " << mentor->mentorName << "." << endl;
        } else {
            cout << "Student " << studentName << " is already registered with a mentor." << endl;
        }
    }

    void viewMentorDetails() const {
        if (assignedMentor != nullptr) {
            cout << "Mentor: " << assignedMentor->mentorName << ", ID: " << assignedMentor->mentorId << endl;
        } else {
            cout << "No mentor assigned." << endl;
        }
    }

    void addInterest(const Sport& sport) {
        if (interestCount < MAX_SPORTS_PER_PERSON) {
            interests[interestCount++] = sport;
            cout << "Sport " << sport.sportName << " added to interests for student " << studentName << "." << endl;
        } else {
            cout << "Student " << studentName << " has reached maximum sports interests." << endl;
        }
    }

    void displayStudentInfo() const {
        cout << "Student ID: " << studentId << ", Student Name: " << studentName << ", Age: " << studentAge << endl;
        cout << "Sports Interests: " << endl;
        for (int i = 0; i < interestCount; i++) {
            interests[i].displaySportInfo();
        }
    }
};

int main() {
    Skill tennisServe(1, "Serve", "Serving the ball in tennis.");
    Skill tennisForehand(2, "Forehand", "Hitting the ball with a forehand stroke.");

    Sport tennis(1, "Tennis", "A racket sport.");
    tennis.addRequiredSkill(tennisServe);
    tennis.addRequiredSkill(tennisForehand);

    Mentor ali(101, "Ali", 3);
    ali.addExpertise(tennis);

    Student saad(201, "Saad", 20);
    saad.addInterest(tennis);

    saad.registerWithMentor(&ali);

    saad.viewMentorDetails();
    ali.showAssignedStudents();

    ali.giveGuidance();

    ali.removeStudent(saad.studentId);

    ali.showAssignedStudents();

    return 0;
}