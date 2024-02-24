#include <QApplication>
#include "GUI/APPGUI.h"
#include "validator/ValidatorSubject.h"
using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    FileRepositorySubjects repo{"../subjects.txt"};
    ValidatorSubject val;
    ContractRepo contract;
    SubjectsService serv{repo,contract,val};

    APPGUI gui(serv,contract);
    gui.show();
    return QApplication::exec();
}