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
    DOC(string name, string sector)// criando um doutor com nome e especialidade
        : name{name}, sector{sector} {}

    void addPatient(Patient *pat) override{ // pedindo o doc pra add o pat
        this->patients[pat->getName()] = pat;
    }

    void rmPatient(Patient *pat) override{// removendo paciente
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
    Ipatient(string name, string diagnosis)// criando um paciente com nome e diagnosis
        : name{name}, diagnosis{diagnosis} {}

    virtual void addDoc(Doctor *doc) override{
        this->doctors[doc->getName()] = doc;// pedindo pro paciente add o doc
    }

    virtual void rmDoc(Doctor* doc) override{// removendo o doutor
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

class Hospital { //hospital
private:

    map<string, Patient *> patients;
    map<string, Doctor *> docs;

public:

    Hospital() {} // criando o hospital

    void addDocs(string name, string sector){ // criando um doutor no hospital
        auto it = this->docs.find(name); // procurando doutor
        if (it == this->docs.end()){// não tem o doc e vai criar
            Doctor *med = new DOC(name, sector); // criando um doutor pq nao tinha
            this->docs[name] = med;
            cout << "doctor " << name << " registered" << endl; // add o doutor
            return;
        }

        throw runtime_error("Error!! Doctor already registered"); // caso veja que o doc ja existe
    }

    void addPatient(string name, string diagnosis){// add um paciente ao hospital
        auto it = this->patients.find(name); // procurando o paciente
        if (it == this->patients.end()) {// paciente nao encontrado
            Patient *pac = new Ipatient(name, diagnosis);// criando um paciente
            this->patients[name] = pac;
            cout << "Patient " << name << " registred\n"; // paciente add
            return;
        }

        throw runtime_error("Error!!! Patient existent"); // caso o paciente ja exista
    }

    void link(string nameD, string nameP){// vinculando o doutor e o paciente
        auto itD = this->docs.find(nameD); // procurando o doutor
        auto itP = this->patients.find(nameP); // procurando o paciente

        if (itD == this->docs.end() && itP == this->patients.end()){ // nao achou nem um
            throw runtime_error ("Error!!! Non-existent registrations");
            return;
        }

        if (itD== this->docs.end()){// nao achou o doutor
            throw runtime_error ("Error!!! No registration");
            return;
        }

        if (itP == this->patients.end()){// nao achou o paciente
            throw runtime_error ("Error!!! No registration");
            return;
        }

        auto listsDocs = itP->second->getDocs(); // criando uma lista 
        for (auto med : listsDocs){ // lista tal medical 
            if (med.second->getSectors() == itD->second->getSectors()){ //vendo se x doutor pode atender o paciente, pela especialidade
                throw runtime_error ("Error!!! Other doctors may attend to you"); // pode
                return;
            }
        }

        itP->second->addDoc(itD->second); // add o doutor 
        itD->second->addPatient(itP->second); // add o paciente 
        cout << "Doctor " << nameD << " and patient " << nameP << " are bound" << endl;// doutor agr pode atender o paciente
    }

    void rmPatient(string name){// remover paciente pelo nome 
        auto it = this->patients.find(name); // procurando o paciente
        if (it == this->patients.end()){// nao achou
            throw runtime_error ("Error!!! Non-existent registration");
            return;
        }

        for (auto med : it->second->getDocs()){// achou
            med.second->getPatients().erase(name);// agr vai apagar do doutor
        }

        this->patients.erase(it);//apagando paciente encontrado
        cout << "patient" << name << " remove of hospital" << name << endl;
    }

    void rmDocs(string name){ // remvover doutor
        auto it = this->docs.find(name); //vai procurar atraves do iterator
        if (it == this->docs.end()){// nao achou
            throw runtime_error ("Error!!! Non-existent registration");
            return;
        }

        for (auto pac : it->second->getPatients()){//removendo do paciente
            pac.second->getDocs().erase(name);
        }

        this->docs.erase(it);// apagando
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
            if (cmd == "addMed"){
                string name, sector;
                cin >> name >> sector;
                hosp.addDocs(name, sector);
                continue;
            }

            if (cmd == "addPac"){
                string name, diagnosis;
                hosp.addPatient(name, diagnosis);
                continue;
            }

            if (cmd == "link"){
                string nameD, nameP;
                cin >> nameD >> nameP;
                hosp.link(nameD, nameP);
                continue;
            }

            if (cmd == "rmMed") {
                string name;
                cin >> name;
                hosp.rmDocs(name);
                continue;
            }

            if (cmd == "rmPac"){
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
            } else  {
                cout << "fali: unknown command" << endl;
            }
        } catch (runtime_error &e){
            cout << e.what() << endl;
        }
        
    } 
}