#ifndef CLOUDPAGE_H
#define CLOUDPAGE_H

#include <QWidget>
#include "commonfunction.h"

namespace Ui {
class CloudPage;
}

class CloudPage : public QWidget
{
    Q_OBJECT

public:
    explicit CloudPage(QWidget *parent = nullptr);
    ~CloudPage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::CloudPage *ui;
};

#endif // CLOUDPAGE_H
