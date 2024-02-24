#ifndef L10__APPGUI_H
#define L10__APPGUI_H
#include "../util/observerPattern/Observer.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include <QWidget>
#include <QVBoxLayout>
#include<QLayoutItem>
#include <QHBoxLayout>
#include <QImage>
#include "../util/models/MyTableModel.h"
#include "../util/models/MyListModel.h"
using std::pair;
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>
#include <QListWidget>
#include <QTableWidget>
#include "../service/SubjectsService.h"
#include <QRadioButton>
#include <QHeaderView>
#include <QSplitter>
#include <QWidget>
class ContractReadOnlyGUI;
#include "../ContractRepository/ContractRepo.h"

class Contract: public QWidget, public Observer{
    friend class SubjectsService;
    friend class APPGUI;
    friend class ContractReadOnlyGUI;
    friend class ContractRepo;
private:
    SubjectsService& ctr;
    ContractRepo& contractFile;

    QListView* lsiV=new QListView;
    MyListModel* listContract;
    //buttons
    QPushButton* refreshL=new QPushButton{"&REFRESH LIST"};
    QPushButton* add_contract=new QPushButton{"&ADD TO CONTRACT"};
    QPushButton* empty_contract=new QPushButton{"&EMPTY CONTRACT"};
    QPushButton* generate_contract=new QPushButton{"&Generate CONTRACT"};
    QPushButton* export_contract=new QPushButton{"&EXPORT TO CONTRACT"};
    QPushButton* exit_contract=new QPushButton{"&EXIT"};
    //text fields
    QLineEdit* txtContractName=new QLineEdit;
    QLineEdit* txtContractTeacher=new QLineEdit;
    QLineEdit* txtContractNumber=new QLineEdit;
    QLineEdit* txtContractFile=new QLineEdit;
    //list
    QListWidget* contract_list=new QListWidget;
    void ui_addContract() ;

public:

     Contract(SubjectsService &srv,ContractRepo &contract): ctr(srv),contractFile(contract){
        contractFile.addObserver(this);
    };
    void innit_contract();
    void connectSignalContract();
    void reloadList(const vector<Subject> &list);
    void update() override{
        reloadList(ctr.getAllContract());

    }
    ~Contract()
    {
        contractFile.removeObserver(this);
    }
};
class ContractReadOnlyGUI: public QWidget,public Observer{
    friend class Contract;
    Contract* contr;
    QListWidget* lista_obj;
public:
    explicit ContractReadOnlyGUI(Contract *c): contr(c){
       // contr->addObserver(this);
    }
    void innitContract()
    {
        lista_obj=new QListWidget();
        QHBoxLayout* main=new QHBoxLayout;
        main->addWidget(lista_obj);
        this->setLayout(main);
    }
    void update() override{
        this->repaint();
    }
    void paintEvent(QPaintEvent* e) override{
        QPainter p(this);
       // bool success = image.load("../linos.png");
     //   qDebug() << "Image loading status: " << success;
        srand(time(0));
        int x = -20;
        for (const auto &elem : contr->ctr.getAllContract())
        {
            x += 40;
            int forma = rand()%4;
            int inaltime = rand()%130;
            int start_y = rand()%60;
            QColor color;

            int color_num = rand() %5;
            switch (color_num)
            {
                case 0:
                    color = Qt::red;
                    break;
                case 1:
                    color = Qt::green;
                    break;
                case 2:
                    color = Qt::black;
                    break;
                case 3:
                    color = Qt::blue;
                    break;
                case 4:
                    color = Qt::lightGray;
                    break;
                default:
                    break;
            }

            switch (forma)
            {
                case 0: // dreptunghi
                    p.drawRect(x, start_y, 20, inaltime);
                    break;
                case 1: // elipsa
                    p.drawEllipse(x, start_y, 20, inaltime);
                    break;
                case 2: // dreptunghi colorat
                    p.fillRect(x, start_y, 20, inaltime, color);
                    break;
                default: // dreptunghi colorat
                    p.fillRect(x, start_y, 20, inaltime, color);
                    break;
            }}}
        ~ContractReadOnlyGUI()
        {
          contr->contractFile.removeObserver(this);
        }

};

class APPGUI:public QWidget {
public:
    APPGUI(SubjectsService&  ser,ContractRepo& cont):service{ser},contractFile{cont} {
        initgui();
        //for the beginning i wil show it always!
        //contractgui();
        loadTable(ser.getAll());
        //initiateTable();
        this-> contract=new Contract(service,cont);
        contract->innit_contract();
        contract->connectSignalContract();
        //loadTable(service.getAll());
        connectSignalSlots();
    }

private:
    MyTableModel* modelTable;
    QTableView* tblV=new QTableView;

    SubjectsService& service;
    ContractRepo& contractFile;

   // QWidget* contract=new QWidget;
    QTableWidget* table_main=new QTableWidget;

    /** BUTTONS MAIN
     */
   // Contract*  contract_n;
    QPushButton* undo=new QPushButton{"&UNDO"};
    QPushButton* add=new QPushButton{"&ADD"};
    QPushButton* del=new QPushButton{"&DELETE"};
    QPushButton* modify=new QPushButton{"&MODIFY"};

    QRadioButton* sort_name=new QRadioButton{"&Name"};
    QRadioButton* sort_hours=new QRadioButton{"&Hours"};
    QRadioButton* sort_teacher=new QRadioButton{"&Teacher"};
    QPushButton* filter_hours=new QPushButton{"&HOURS"};
    QPushButton* filter_teacher=new QPushButton{"&TEACHER"};
    QLineEdit* txtfilter=new QLineEdit;
    QPushButton* exit=new QPushButton{"&EXIT"};
    QPushButton* load=new QPushButton{"&LOAD"};
    QHBoxLayout* type=new QHBoxLayout;
    vector<pair<QPushButton*,string>> buttons_types;
    //vector<string> ty_added;

    //CONTRACT BUTTON
    Contract* contract;
    QPushButton* open_contract=new QPushButton{"&OPEN CONTRACT"};
    QPushButton* open_roc=new QPushButton{"Open read only contract"};

    /**FORM LAYOUT*/
    QLineEdit* txtSubject=new QLineEdit;
    QLineEdit* txtHours=new QLineEdit;
    QLineEdit* txtType=new QLineEdit;
    QLineEdit* txtTeacher=new QLineEdit;
    /*
     * Contract
     */

   // void loadList(const vector<Subject> &subject);
    void loadTable(const vector<Subject> &subject);
//    void contractgui();
    void connectSignalSlots();
   // void initiateTable();

    void initgui();
    void ui_setInsertDataSubjects(QVBoxLayout *pLayout);
    void ui_setWindowGUI();
    void ui_setTableSubjects();
    void ui_add();
    void ui_delete();
    void ui_modify();
    void ui_filter_h();
    void ui_filter_t();
    void ui_sort_n();
  //  void ui_addContract();
    void ui_generatetypebuttons();
    void ui_cout_map(const map<string,vector<Subject>> mapFiltered,const string &type);

};
#endif //L10__APPGUI_H
