#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVector>
#include <QString>
#include <string>
#include <QDebug>
#include <QMap>
#include <QFile>
#include <QFileDialog>
#include <math.h>
#include <QProcess>
using namespace std;
void traversalControl_button(const QObjectList& q, QVector<QPushButton *> &output_list, string widget_type_string);
void traversalControl_line(const QObjectList& q, QVector<QLineEdit *> &output_list, QMap<QString, QLineEdit *> &edit_map, string widget_type_string);
void traversalControl_box(const QObjectList& q, QVector<QComboBox *> &output_list, QMap<QString, QComboBox *> &box_map, string widget_type_string);

#endif // COMMONFUNCTION_H

