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

