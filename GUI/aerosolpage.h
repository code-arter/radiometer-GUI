#ifndef AEROSOLPAGE_H
#define AEROSOLPAGE_H

#include <QWidget>

namespace Ui {
class AerosolPage;
}

class AerosolPage : public QWidget
{
    Q_OBJECT

public:
    explicit AerosolPage(QWidget *parent = nullptr);
    ~AerosolPage();

private:
    Ui::AerosolPage *ui;
};

#endif // AEROSOLPAGE_H
