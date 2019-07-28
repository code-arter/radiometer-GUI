#include "commonfunction.h"

void traversalControl_button(const QObjectList& q, QVector<QPushButton *> &output_list, string widget_type_string)
{
    for(int i=0;i<q.length();i++)
    {
         if(!q.at(i)->children().empty())
        {
         traversalControl_button(q.at(i)->children(), output_list, widget_type_string);
        }
        else
        {
            QObject* o = q.at(i);
            if (o->inherits(widget_type_string.c_str()))
            {
                if(widget_type_string == string("QPushButton"))
                {
                    QPushButton* b = qobject_cast<QPushButton *>(o);
                    output_list.append(b);
                }
                else
                    break;

            } //end if
        } //end for
    } //end function
}

void traversalControl_line(const QObjectList& q, QVector<QLineEdit *> &output_list, QMap<QString, QLineEdit *> &edit_map, string widget_type_string)
{
    for(int i=0;i<q.length();i++)
    {
         if(!q.at(i)->children().empty())
        {
         traversalControl_line(q.at(i)->children(), output_list, edit_map, widget_type_string);
        }
        QObject* o = q.at(i);
        if (o->inherits(widget_type_string.c_str()))
        {
            if(widget_type_string == string("QLineEdit"))
            {
                QLineEdit* b = qobject_cast<QLineEdit *>(o);
                QString map_key = b->property(string("option_name").c_str()).toString();
                if(!map_key.isEmpty())
                {
                    output_list.append(b);
                    edit_map[map_key]= b;
                }
            }
            else
                break;

        } //end if
    } //end function
}


void traversalControl_box(const QObjectList& q, QVector<QComboBox *> &output_list, QMap<QString, QComboBox *> &box_map, string widget_type_string)
{
    for(int i=0;i<q.length();i++)
    {
         if(!q.at(i)->children().empty())
        {
         traversalControl_box(q.at(i)->children(), output_list, box_map, widget_type_string);
        }

        QObject* o = q.at(i);
        if (o->inherits(widget_type_string.c_str()))
        {

            if(widget_type_string == string("QComboBox"))
            {
                QComboBox* b = qobject_cast<QComboBox *>(o);
                QString map_key = b->property(string("option_name").c_str()).toString();
                if(!map_key.isEmpty())
                {
                    output_list.append(b);
                    box_map[map_key]= b;
                }
            }
            else
                break;

        } //end if
    } //end function
}


void myMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString& msg)
{
    static QMutex mutex;
    mutex.lock();
    QString time=QDateTime::currentDateTime().toString(QString("[ yyyy-MM-dd HH:mm:ss:zzz ]"));
    QString mmsg;
    switch(type)
    {
    case QtDebugMsg:
        mmsg=QString("%1: Debug:\t%2 (file:%3, line:%4, func: %5)").arg(time).arg(msg).arg(QString(context.file)).arg(context.line).arg(QString(context.function));
        break;
    case QtInfoMsg:
        mmsg=QString("%1: Info:\t%2 (file:%3, line:%4, func: %5)").arg(time).arg(msg).arg(QString(context.file)).arg(context.line).arg(QString(context.function));
        break;
    case QtWarningMsg:
        mmsg=QString("%1: Warning:\t%2 (file:%3, line:%4, func: %5)").arg(time).arg(msg).arg(QString(context.file)).arg(context.line).arg(QString(context.function));
        break;
    case QtCriticalMsg:
        mmsg=QString("%1: Critical:\t%2 (file:%3, line:%4, func: %5)").arg(time).arg(msg).arg(QString(context.file)).arg(context.line).arg(QString(context.function));
        break;
    case QtFatalMsg:
        mmsg=QString("%1: Fatal:\t%2 (file:%3, line:%4, func: %5)").arg(time).arg(msg).arg(QString(context.file)).arg(context.line).arg(QString(context.function));
        abort();
    }
    QString log_path = QCoreApplication::applicationDirPath() + "/log/run_log";
    qDebug() << log_path;

    QFile file(log_path);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << mmsg << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
}

