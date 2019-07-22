#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString conf_path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->load_config_file(conf_path);
    /*
    this->python_path = this->get_config("mainwindow", "python_path").toString();
    this->scripts_path = this->get_config("mainwindow", "scripts_path").toString();
    */
    qDebug() << this->python_path << this->scripts_path;

    this->p = NULL;

    general_page = new GeneralPage(this);

    atmosphere_page = new AtmosPherePage(this);
    input_conf_page = new InputConfShow(this);
    aerosol_page = new AerosolPage(this);
    cloud_page = new CloudPage(this);
    //excel_page = new ExcelForm(this);
    trans_mode_page = new TransModelPage(this);
    plot_dialog = new PlotDialog(this);
    plot_dialog->setWindowTitle("绘图设置");
    plot_dialog->hide();

    single_plot_dialog = new SingleDialog(this);
    single_plot_dialog->setWindowTitle("绘图设置");
    single_plot_dialog->hide();


    this->wait_dialog = new WaitDialog(this);
    this->wait_dialog->hide();

    this->pFunhello = NULL;


    ui->tabWidget->addTab(general_page, QStringLiteral("主页"));
    ui->tabWidget->addTab(atmosphere_page, QStringLiteral("大气廓线"));
    ui->tabWidget->addTab(aerosol_page, QStringLiteral("气溶胶"));
    ui->tabWidget->addTab(cloud_page, QStringLiteral("水云和冰云"));
    ui->tabWidget->addTab(trans_mode_page, QStringLiteral("辐射传输计算模型"));
    ui->tabWidget->addTab(input_conf_page, QStringLiteral("显示输入项"));

    this->init_widget_list();
    this->init_python("");

    connect(this->general_page, SIGNAL(GeneralSaveConfEvent(QString)),this,SLOT(on_general_page_conf_clicked(QString)));
    connect(this->general_page, SIGNAL(GeneralLoadConfEvent(QString)),this,SLOT(on_general_page_conf_load_clicked(QString)));
    connect(this->general_page, SIGNAL(GeneralSaveOutEvent(QString)),this,SLOT(on_general_page_out_clicked(QString)));
    connect(this->general_page, SIGNAL(GeneralSavePlotEvent(QString)),this,SLOT(on_general_page_plot_clicked(QString)));

    //connect(this->plot_dialog, SIGNAL(GeneralPlotEvent(QString)),this,SLOT(on_general_page_plot_clicked(QString)));

}

MainWindow::~MainWindow()
{

    delete general_page;
    delete atmosphere_page;
    delete input_conf_page;
    delete aerosol_page;
    delete cloud_page;
    delete trans_mode_page;
        delete ui;
    this->close_python();
}

void MainWindow::init_widget_list()
{
    traversalControl_button(this->children(), this->button_list, string("QPushButton"));
    traversalControl_line(this->children(), this->edit_list, this->edit_map, string("QLineEdit"));
    traversalControl_box(this->children(), this->box_list, this->box_map, string("QComboBox"));
}

void MainWindow::get_input()
{
    //每次获取当前输入项之前，先清空map
    this->widget_map.clear();
    for(int index = 0; index < this->edit_list.size(); index ++)
    {
        if(this->edit_list[index] != NULL && !this->edit_list[index]->text().isEmpty())
        {
            QString option_name = this->edit_list[index]->property(string("option_name").c_str()).toString();
            qDebug() << option_name << this->edit_list[index]->text();
            this->widget_map[option_name] = this->edit_list[index]->text();
        }
    }
    for(int index = 0; index < this->box_list.size(); index ++)
    {
        if(this->box_list[index] != NULL && this->box_list[index]->currentText() != QString("off"))
        {
            QString option_name = this->box_list[index]->property(string("option_name").c_str()).toString();
            qDebug() << option_name << this->box_list[index]->currentText();
            this->widget_map[option_name] = this->box_list[index]->currentText();
        }
    }
}
QString MainWindow::get_output_str()
{
    this->get_input();

    QMap<QString, QString>::iterator iter = this->widget_map.begin();
    QString all_str;
    while (iter != this->widget_map.end())
    {
      QString tmp_str = iter.key() + QString(" ") + iter.value();
      all_str = all_str + tmp_str + QString("\n");
      iter++;
    }
    return all_str;
}
void MainWindow::load_conf(QString path)
{
    QVector<QString> line_list;
    this->clear_conf();

    this->read_conf(path, line_list);

    this->set_conf(line_list);
}

void MainWindow::read_conf(QString path, QVector<QString> &line_list)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        line_list.append(line);
    }
    file.close();
}

QString MainWindow::read_all(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString res_str = in.readAll();
    file.close();
    return res_str;
}
void MainWindow::clear_conf()
{
    for(int index = 0; index < this->box_list.size(); index++)
        this->box_list[index]->setCurrentIndex(0);
    for(int index = 0; index < this->edit_list.size(); index++)
        this->edit_list[index]->setText(QString());
}
void MainWindow::set_conf(QVector<QString> &line_list)
{
    for(int index = 0; index < line_list.size(); index++)
    {
        QStringList line_info = line_list[index].split(' ');
        if(line_info.size() < 2)
        {
            continue;
        }
        else
        {
            QString line_property = line_info.at(0);
            line_info.removeAt(0);

            QString line_val = line_info.join(" ");

            if(line_property.isEmpty() || line_val.isEmpty())
            {
                continue;
            }
            if(this->edit_map.contains(line_property))
            {
                this->edit_map[line_property]->setText(line_val);
            }
            else if(this->box_map.contains(line_property))
            {
                qDebug() << line_val;
                this->box_map[line_property]->setCurrentText(line_val);
            }
            else
            {
                continue;
            }
        }
    }
}

void MainWindow::on_general_page_conf_clicked(QString path)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<(this->get_output_str());
    file.close();
}
void MainWindow::on_general_page_conf_load_clicked(QString path)
{
    this->load_conf(path);
}
int MainWindow::close_python()
{
   Py_Finalize();
}
int MainWindow::init_python(QString out_path)
{
    /*
    QFileInfo fileinfo(this->python_path);
    QString python_home = fileinfo.path();
    const char *p = python_home.toStdString().c_str();
    char *tmp=const_cast<char*>(p);
    qDebug() << tmp;
    Py_SetPythonHome(tmp);
    */

    Py_Initialize();
    if(!Py_IsInitialized())
    {
       return -1;
    }

    PyObject* pModule = PyImport_ImportModule("process_qt_input");  // 这里的test_py就是创建的python文件
    if (!pModule)
    {
        cout<< "Cant open python file!\n" << endl;
        return -1;
    }
    PyObject* pFunhello= PyObject_GetAttrString(pModule,"run");  // 这里的hellow就是python文件定义的函数
    if(!pFunhello)
    {
        cout<<"Get function hello failed"<<endl;
        return -1;
    }
    this->pFunhello = pFunhello;
}

 int MainWindow::call_python(QString out_path)
{
    QString Q_path = QCoreApplication::applicationDirPath() + "/process_qt_input.py";

    string tmp_path = out_path.toStdString();
    string script_path = Q_path.toStdString();
    PyObject_CallFunction(this->pFunhello, "ss", tmp_path.c_str(), script_path.c_str());
}

void MainWindow::on_readoutput()
{
    QString out_str = this->read_all(this->std_out_path);

    this->wait_dialog->set_init_status(false);
    this->wait_dialog->setText(out_str);
}


void MainWindow::on_general_page_out_clicked(QString path)
{
    QString qt_out_path = path + ".qt";
    QFile file(qt_out_path);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<(this->get_output_str());
    file.close();

    this->call_python(qt_out_path);
    this->std_out_path = qt_out_path + ".stdout";
    this->on_readoutput();
    this->wait_dialog->setModal(true);
    this->wait_dialog->exec();
}


void MainWindow::on_general_page_plot_clicked(QString path)
{
    QVector<QString> line_list;
    this->read_conf(path, line_list);
    if(line_list.size() == 1 && !line_list[0].contains(" "))
    {
        this->plot_dialog->set_init(line_list[0]);
        this->plot_dialog->show();
    }
    else
    {
        this->single_plot_dialog->set_init(line_list);
        this->single_plot_dialog->show();

    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 5)
        this->input_conf_page->setInputConf(this->get_output_str());
}

void MainWindow::load_config_file(QString path)
{

    if (path.isEmpty())
    {
        this->conf_path = QCoreApplication::applicationDirPath() + "/qt_conf/GUI.ini";
    }
    else
    {
        this->conf_path = path;
    }
    qDebug() << this->conf_path;
    this->config_settings = new QSettings(this->conf_path, QSettings::IniFormat);
}

QVariant MainWindow::get_config(QString qstrnodename,QString qstrkeyname)
{

    QVariant qvar = this->config_settings->value(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname));
    return qvar;

}
