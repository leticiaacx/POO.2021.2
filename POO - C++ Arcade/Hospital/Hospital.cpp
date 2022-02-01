#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <map>

using namespace std;

class Doctor;// criei antes para poder criar o paciente, em baiaxo vou desenvolver, igual no matricula  

class Patient {// paciente
public:
    virtual void addDoc(Doctor *doctor) = 0;
    virtual void rmDoc(Doctor *doctor) = 0;
    virtual string getDiagnosis() const = 0;
    virtual string getName() const = 0;
    virtual map<string, Doctor *> &getDocs() = 0;
};

class Doctor {// medico
public:
    virtual void addPatient(Patient *pat) = 0;
    virtual void rmPatient(Patient *pat) = 0;
    virtual string getSectors() const = 0;
    virtual string getName() const = 0;
    virtual map<string, Patient *> &getPatients() = 0;
};

class DOC : public Doctor {// doutor é doutor com especialidades e pacientes 
private:
    string name;
    string sector;
    map<string, Patient *> patients;

public:
    DOC(string name, string sector)
        : name{name}, sector{sector} {}

    void addPatient(Patient *pat) override{
        this->patients[pat->getName()] = pat;
    }

    void rmPatient(Patient *pat) override{
        this->patients.erase(pat->getName());
    }

    string getSectors() const override{
        return this->sector;
    }

    string getName() const override{
        return this->name;
    }

    map<string, Patient *> &getPatients() override{
        return this->patients;
    }

    friend ostream &operator<<(ostream &os, Doctor *doc){
        string beginning = "Doc: " + doc->getName() + " : " + doc->getSectors();
        os << beginning;

        os << setw(40 - beginning.length()) << "Pacs: [ ";
        for (auto pacs : doc->getPatients()){
            os << pacs.second->getName() << ' ';
        }

        os << " ]";
        return os;
    }
};

class Ipatient : public Patient { // paciente do tipo paciente 
private:
    string name;
    string diagnosis;
    map<string, Doctor *> doctors;

public:
    Ipatient(string name, string diagnosis)
        : name{name}, diagnosis{diagnosis} {}

    virtual void addDoc(Doctor *doc) override{
        this->doctors[doc->getName()] = doc;
    }

    virtual void rmDoc(Doctor* doc) override{
        this->doctors.erase(doc->getName());
    }

    virtual string getDiagnosis() const override{
        return this->diagnosis;
    }

    virtual string getName() const override{
        return this->name;
    }

    virtual map<string, Doctor *> &getDocs() override{// função que ta la em pacientes 
        return this->doctors;
    }

    friend ostream &operator<<(ostream &os, Patient* pat){
        string beginning = "Pat: " + pat->getName() + " : " + pat->getDiagnosis();
        os << beginning;

        os << setw(40 - beginning.length()) << "Meds: [ ";
        for (auto meds : pat->getDocs()){
            os << static_cast<Doctor *>(meds.second)->getName() << " ";
        }

        os << " ]";
        return os;
    }
};

class HospitalExc : public exception {
    string message;

public:

    HospitalExc(const string &message) : message(message) {}

    const char *what() const noexcept override{
        return message.c_str();
    }
};

class Hospital { //hospital
private:

    map<string, Patient *> patients;
    map<string, Doctor *> docs;

public:

    Hospital() {}

    void addDocs(string name, string sector){
        auto it = this->docs.find(name);
        if (it == this->docs.end()){
            Doctor *med = new DOC(name, sector);
            this->docs[name] = med;
            cout << "doctor " << name << " registered" << endl;
            return;
        }

        throw HospitalExc("Error!! Doctor already registered");
    }

    void addPatient(string name, string diagnosis){
        auto it = this->patients.find(name);
        if (it == this->patients.end())
        {
            Patient *pac = new Ipatient(name, diagnosis);
            this->patients[name] = pac;
            cout << "Patient " << name << " registred\n";
            return;
        }

        throw HospitalExc("Error!!! Patient existent");
    }

    void link(string nameD, string nameP){
        auto itD = this->docs.find(nameD);
        auto itP = this->patients.find(nameP);

        if (itD == this->docs.end() && itP == this->patients.end()){
            throw HospitalExc("Error!!! Non-existent registrations");
            return;
        }

        if (itD== this->docs.end()){
            throw HospitalExc("Error!!! No registration");
            return;
        }

        if (itP == this->patients.end()){
            throw HospitalExc("Error!!! No registration");
            return;
        }

        auto listsDocs = itP->second->getDocs();
        for (auto med : listsDocs){
            if (med.second->getSectors() == itD->second->getSectors()){
                throw HospitalExc("Error!!! Other doctors may attend to you");
                return;
            }
        }

        itP->second->addDoc(itD->second);
        itD->second->addPatient(itP->second);
        cout << "Doctor " << nameD << " and patient " << nameP << " are bound" << endl;
    }

    void rmPatient(string name){
        auto it = this->patients.find(name);
        if (it == this->patients.end()){
            throw HospitalExc("Error!!! Non-existent registration");
            return;
        }

        for (auto med : it->second->getDocs()){
            med.second->getPatients().erase(name);
        }

        this->patients.erase(it);
        cout << "patient" << name << " remove of hospital" << name << endl;
    }

    void rmDocs(string name){
        auto it = this->docs.find(name);
        if (it == this->docs.end()){
            throw HospitalExc("Error!!! Non-existent registration");
            return;
        }

        for (auto pac : it->second->getPatients()){
            pac.second->getDocs().erase(name);
        }

        this->docs.erase(it);
        cout << "Doctor " << name << " remove of doc" << endl;
    }

    friend ostream &operator<<(ostream &os, Hospital &hosp){
        os << "Lists of Hospital: "<< endl;
        for (auto pat : hosp.patients){
            os << static_cast<Patient *>(pat.second) << endl;
        }

        for (auto med : hosp.docs){
            os << static_cast<Doctor *>(med.second) << '\n';
        }

        return os;
    }
};

int main(){
    Hospital hosp;

    while (true){
        cout << endl;
        string cmd{""};
        cin >> cmd;

        try{
            if (cmd == "addmed"){
                string name, sector;
                cin >> name >> sector;
                hosp.addDocs(name, sector);
                continue;
            }
        
        if (cmd == "addpac"){
            string name, diagnosis;
            hosp.addPatient(name, diagnosis);
            continue;
        }

        if (cmd == "vinc"){
            string nameD, nameP;
            cin >> nameD >> nameP;
            hosp.link(nameD, nameP);
            continue;
        }

        if (cmd == "rmmed"){
            string name;
            cin >> name;
            hosp.rmDocs(name);
            continue;
        }

        if (cmd == "rmpac"){
            string name;
            cin >> name;
            hosp.rmPatient(name);
            continue;
        }

        if (cmd == "show"){
            cout << hosp << endl;
            continue;
        }

        if (cmd == "clear"){
            continue;
        }

        if (cmd == "end"){
            exit(1);
        }

        else{
            cout << "Invalid command" << endl;
            continue;
        }
        
        } catch (HospitalExc &he){
            cout << he.what() << endl;
        }
    }
}