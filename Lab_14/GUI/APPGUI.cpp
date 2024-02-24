
#include "APPGUI.h"
 void APPGUI::ui_setTableSubjects()
{

}
void APPGUI::ui_setInsertDataSubjects(QVBoxLayout *right_layout) {
    QFormLayout* data_layout=new QFormLayout;
    right_layout->addLayout(data_layout);
    data_layout->addRow(new QLabel{"SUBJECT:"},txtSubject);
    data_layout->addRow(new QLabel{"HOURS:"},txtHours);
    data_layout->addRow(new QLabel{"TYPE:"},txtType);
    data_layout->addRow(new QLabel{"TEACHER:"},txtTeacher);
    QHBoxLayout* actions=new QHBoxLayout;
    right_layout->addLayout(actions);
    actions->addWidget(add);
    actions->addWidget(modify);
    actions->addWidget(del);

    QVBoxLayout* sflayer=new QVBoxLayout;
    right_layout->addLayout(sflayer);
    sflayer->addWidget(new QLabel{"SORT TYPE"});
    sflayer->addWidget(sort_name);
    sflayer->addWidget(sort_hours);
    sflayer->addWidget(sort_teacher);
    sflayer->addWidget(new QLabel{"FILTER"});
    QHBoxLayout* filterlayer=new QHBoxLayout;
    right_layout->addLayout(type);
    right_layout->addLayout(filterlayer);
    filterlayer->addWidget(filter_hours);
    filterlayer->addWidget(filter_teacher);
    right_layout->addWidget(txtfilter);

    right_layout->addWidget(exit);
    right_layout->addWidget(open_roc);

}
void APPGUI::ui_setWindowGUI() {
//main layout
    //setting style :)
    this->setWindowTitle("Subjects App");
    this->setMinimumSize(1400,700);
    QPalette pallete=QPalette();
    pallete.setColor(QPalette::Window,"#1d092b");
    QFont font("Caviar Dreams",12);
    this->setAutoFillBackground(true);
    this->setPalette(pallete);
    this->setFont(font);
}

void APPGUI::initgui() {
    ui_setWindowGUI();
    //main layout orientation!
    auto* lymain=new QHBoxLayout;
    setLayout(lymain);
    /**LIST LAYOUT*/
    auto* left_layout=new QVBoxLayout;
    lymain->addLayout(left_layout,9);
    //now i am gonna populate it
    //Adding the label for the table
    left_layout->addWidget(new QLabel{"Table"});
 //   tblV->setUniformItemSizes(true);
    left_layout->addWidget(tblV);
    left_layout->addWidget(undo);
    left_layout->addWidget(open_contract);
    left_layout->addWidget(load);
    //lymain->stretch(30);
    /**
     * RIGHT LAYOUT
     */
    //right layout -> buttons and operations. Will have 3 other layouts
    QVBoxLayout* right_layout=new QVBoxLayout;
    lymain->addLayout(right_layout,20);
    ui_setInsertDataSubjects(right_layout);

    //operations

    //loadTable(service.getAll());
    modelTable=new MyTableModel{service.getAll()};
    tblV->setModel(modelTable);
   // tblV->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
   // tblV->horizontalHeader()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tblV->setSelectionBehavior(QAbstractItemView::SelectRows);
  //  tblV->setSelectionMode(QAbstractItemView::ExtendedSelection);

//
//
//    lst->addItem(new QListWidgetItem{"item 2"});
//    lymain->addWidget(lst);
}

void APPGUI::ui_generatetypebuttons() {
    set<string> types_from_service=service.number_of_types();

    for(const auto& t:types_from_service)
    {   auto it=find_if(this->buttons_types.begin(),
                           buttons_types.end(),
                           [t](const pair<QPushButton*,string>& but )
                           {
                               if(but.second==t)
                                   return true;
                               else
                                   return false;
                           });

        if(it!=this->buttons_types.end())
        {
            continue;
        }
        else {


            QPushButton *button = new QPushButton{QString::fromStdString(t)};
            buttons_types.push_back(std::make_pair(button, t));
            type->addWidget(button);

            QObject::connect(button, &QPushButton::clicked, [this,t]() {
                map<string, vector<Subject>> m = service.creatingmap();
                int nr = m[t].size();
                QString mes = "Number is:";
                mes += QString::number(nr);
                QMessageBox::information(nullptr, "Info", mes);
            });

        }        }
        vector<string> toremove;
        for(const auto& pair:buttons_types)
        {
            if(std::find(types_from_service.begin(),types_from_service.end(),pair.second)==types_from_service.end())
            {
                toremove.push_back(pair.second);
                std::cout<<pair.second<<" HERE";
            }
        }

        for(const auto& type_to_remove:toremove)
        {
            auto it=find_if(this->buttons_types.begin(),
                            buttons_types.end(),
                            [type_to_remove](const pair<QPushButton*,string>& but )
                            {
                                if(but.second==type_to_remove)
                                    return true;
                                else
                                    return false;
                            });
            int poz= (int)std::distance(this->buttons_types.begin(),it);
           delete this->buttons_types[poz].first;
           this->buttons_types.erase(it);
        }

    }
void APPGUI::loadTable(const vector<Subject> &subject) {
    modelTable->setMasini(subject);

}
void APPGUI::ui_add() {
    string name=txtSubject->text().toStdString();
    string teacher=txtTeacher->text().toStdString();
    string type=txtType->text().toStdString();
    string hours=txtHours->text().toStdString();
    qDebug()<<name<<teacher;
    int h;
    try {
        h= stoi(hours);
    }
    catch(std::invalid_argument& mes)
    {
        QMessageBox::warning(this,"WARNING","INVALID DATA");
        return;
    }
    try
    {
        service.addSubject(name,h,teacher,type);
    }
    catch(RepositoryException& mes)
    {
        QMessageBox::warning(this,"WARNING",QString::fromStdString(mes.getMessage()));
    }
    catch(ValidatorException& mes)
    {
        QMessageBox::warning(this,"WARNING",QString::fromStdString(mes.getMessage()));
    }
    loadTable(service.getAll());

}
void APPGUI::ui_delete() {
    string name=txtSubject->text().toStdString();
    string teacher=txtTeacher->text().toStdString();
    qDebug()<<name<<teacher;
    try
    {
        service.deleteSubject(name,teacher);
    }
    catch(RepositoryException& mes)
    {
        QMessageBox::warning(this,"WARNING",QString::fromStdString(mes.getMessage()));
    }
    catch(ValidatorException& mes)
    {
        QMessageBox::warning(this,"WARNING",QString::fromStdString(mes.getMessage()));
    }
    loadTable(service.getAll());

}
void APPGUI::ui_modify() {
    string name=txtSubject->text().toStdString();
    string teacher=txtTeacher->text().toStdString();
    string type=txtType->text().toStdString();
    string hours=txtHours->text().toStdString();
    qDebug()<<name<<teacher;
    int h;
    try {
        h= stoi(hours);
    }
    catch(std::invalid_argument& mes)
    {
        QMessageBox::warning(this,"WARNING","INVALID DATA");
        return;
    }
    try
    {
        service.updateSubject(name,teacher,h,type);
    }
    catch(RepositoryException& mes)
    {
        QMessageBox::warning(this,"WARNING",QString::fromStdString(mes.getMessage()));
    }
    catch(ValidatorException& mes)
    {
        QMessageBox::warning(this,"WARNING",QString::fromStdString(mes.getMessage()));
    }
    loadTable(service.getAll());
}
void APPGUI::ui_filter_h(){
    string h=txtfilter->text().toStdString();
    int hours;
    try
    {
        hours=stoi(h);
    }
    catch (std::invalid_argument &mes)
    {
        QMessageBox::warning(nullptr,"!","INVALID INPUT");
    }
    vector<Subject> sbj=service.filterByHours(hours);
    for(const auto& s:sbj)
    {
        qDebug()<<s.to_string_print();
    }
    loadTable(sbj);
}
void APPGUI::ui_filter_t(){
    string teacher=txtfilter->text().toStdString();
    qDebug()<<teacher;
    vector<Subject> sbj=service.filterByTeacher(teacher);
    for(const auto& s:sbj)
    {
        qDebug()<<s.to_string_print();
    }
    loadTable(sbj);
}
void APPGUI::ui_sort_n() {
    vector<Subject> s=service.sortByName();
    loadTable(s);
}
void APPGUI::connectSignalSlots() {
    /**GUI*/
    //exit
    QObject::connect(exit,&QPushButton::clicked,[&](){
        this->close();
        contract->close();
        QMessageBox::information(nullptr,"!","Closing app");
    });
    QObject::connect(add,&QPushButton::clicked,this,&APPGUI::ui_add);
    QObject::connect(del,&QPushButton::clicked,this,&APPGUI::ui_delete);
    QObject::connect(modify,&QPushButton::clicked,this,&APPGUI::ui_modify);
    QObject::connect(filter_teacher,&QPushButton::clicked,this,&APPGUI::ui_filter_t);
    QObject::connect(filter_hours,&QPushButton::clicked,this,&APPGUI::ui_filter_h);
    QObject::connect(load,&QPushButton::clicked,[&](){
        this->loadTable(service.getAll());
    });
    QObject::connect(sort_name,&QRadioButton::toggled,this,&APPGUI::ui_sort_n);
    QObject::connect(sort_teacher,&QRadioButton::toggled,[&](){

        loadTable(service.sortByTeacherandType());
    });
    QObject::connect(open_contract, &QPushButton::clicked, [&]() {
        //   contract->show();

        Contract*  contract_n = new Contract(service,contractFile);

        contract_n->innit_contract();
        contract_n->connectSignalContract();
        contract_n->show();
        // contract_n->contractFile.addObserver(contract_n);
    });
    QObject::connect(open_roc, &QPushButton::clicked, [&]() {
        ContractReadOnlyGUI* contractRO = new  ContractReadOnlyGUI(contract);
        contractRO->show();

    });
    QObject::connect(sort_hours,&QRadioButton::toggled,[&](){

        loadTable(service.sortByHours());
    });
    QObject::connect(undo,&QPushButton::clicked,[&](){
        try{
            service.Undo();}
        catch(RepositoryException& mes)
        {
            QMessageBox::warning(nullptr,"!",QString::fromStdString(mes.getMessage()));
        }
    });

    QObject::connect(tblV, &QTableView::pressed, [&]() {
        auto sel = tblV->selectionModel();
        if (sel->selectedRows().size() > 0) {
            QModelIndex index = sel->selectedRows().at(0);
            QAbstractItemModel* model = tblV->model();

            QVariant subjectVariant = model->data(model->index(index.row(), 0));
            QVariant hoursVariant = model->data(model->index(index.row(), 1));
            QVariant teacherVariant = model->data(model->index(index.row(), 2));
            QVariant typeVariant = model->data(model->index(index.row(), 3));
            txtSubject->setText(subjectVariant.toString());
            txtHours->setText(hoursVariant.toString());
            txtTeacher->setText(teacherVariant.toString());
            txtType->setText(typeVariant.toString());
        }
    });




}



void Contract::reloadList(const vector<Subject> &subject) {
   listContract=new MyListModel{subject};
   lsiV->setModel(listContract);

}
void Contract::ui_addContract() {
    string name=txtContractName->text().toStdString();
    string teacher=txtContractTeacher->text().toStdString();
    auto found=ctr.filterBySubjectName(name);
    if(found.empty())
    {
        QMessageBox::warning(nullptr,"1","SUBJECT: UNFOUND");
        return;
    }
    if(found.size()==1)
    {try
        {
            ctr.add_to_contract(name,found[0].get_teacher(),found);
        }
        catch(ContractException &m)
        {
            QMessageBox::warning(nullptr,"!",QString::fromStdString(m.getMessage()));
            return;
        }
        catch(RepositoryException &m)
        {
            QMessageBox::warning(nullptr,"!",QString::fromStdString(m.getMessage()));
            return;
        }
        catch(ValidatorException &m)
        {
            QMessageBox::warning(nullptr,"!",QString::fromStdString(m.getMessage()));
            return;
        }}
    else
    {
        if(teacher!="")
        {
            try
            {
                ctr.add_to_contract(name,teacher,found);
            }
            catch(ContractException &m)
            {
                QMessageBox::warning(nullptr,"!",QString::fromStdString(m.getMessage()));
                return;
            }
            catch(RepositoryException &m)
            {
                QMessageBox::warning(nullptr,"!",QString::fromStdString(m.getMessage()));
                return;
            }
            catch(ValidatorException &m)
            {
                QMessageBox::warning(nullptr,"!",QString::fromStdString(m.getMessage()));
                return;
            }
        }
        else
        {
            QMessageBox::warning(nullptr,"!","You have to provide something in the teacher field!");
        }
    }
    reloadList(ctr.getAllContract());
    //notify();
}
void Contract::innit_contract() {
    //second layout for uh School Contract
    setWindowTitle("Set Contract");
    QPalette second_pal=QPalette();
    second_pal.setColor(QPalette::Window,"#092b2b");
    QFont font2("Comic Sans",12);
    setPalette(second_pal);
    setFont(font2);
    QHBoxLayout* lysecond=new QHBoxLayout;
    setLayout(lysecond);
    QVBoxLayout* l_lay=new QVBoxLayout;
    lysecond->addLayout(l_lay);
    l_lay->addWidget(new QLabel{"CONTRACT"});
    l_lay->addWidget(refreshL);
    l_lay->addWidget(empty_contract);
    QFormLayout* l_form=new QFormLayout;
    l_lay->addLayout(l_form);
    l_form->addRow(new QLabel{"Name:"},txtContractName);
    l_form->addRow(new QLabel{"Teacher:"},txtContractTeacher);
    l_lay->addWidget(add_contract);
    l_lay->addWidget(new QLabel{"GENERATE"});
    QFormLayout* gen_layout=new QFormLayout;
    l_lay->addLayout(gen_layout);
    gen_layout->addRow(new QLabel{"How many:"},txtContractNumber);
    l_lay->addWidget(generate_contract);
    l_lay->addWidget(new QLabel{"Export"});
    QFormLayout* export_layout=new QFormLayout;
    l_lay->addLayout(export_layout);
    export_layout->addRow(new QLabel{"FILE:"},txtContractFile);
    l_lay->addWidget(export_contract);
    QVBoxLayout* r_layout=new QVBoxLayout;
    lysecond->addLayout(r_layout);

    r_layout->addWidget(lsiV);
    r_layout->addWidget(exit_contract);
    //contract->show();

}

void Contract::connectSignalContract() {
    /**CONTRACT WINDOW*/

    this->reloadList(ctr.getAllContract());
    QObject::connect(refreshL,&QPushButton::clicked,[&](){
        reloadList(ctr.getAllContract());
    });
    QObject::connect(exit_contract,&QPushButton::clicked,[&](){
      //  this->notify();
        close();
    });
    QObject::connect(empty_contract,&QPushButton::clicked,[&](){
        ctr.emptyContract();
        reloadList( ctr.getAllContract());
        //notify();
    });
    QObject::connect(generate_contract,&QPushButton::clicked,[&](){
        string n=txtContractNumber->text().toStdString();
        int nr;
        try
        {
            nr=stoi(n);
        }
        catch(std::invalid_argument &m)
        {
            QMessageBox::warning(nullptr,"!","INVALID ARGUMENT");
        }
        ctr.generateContract(nr);

        reloadList( ctr.getAllContract());
        //notify();
    });
    QObject::connect(add_contract,&QPushButton::clicked,this,&Contract::ui_addContract);
    QObject::connect(export_contract,&QPushButton::clicked,[&](){
        string file=txtContractFile->text().toStdString();
        ctr.exportContract(file);
    });

}
