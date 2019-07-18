#ifndef INPUTCONFSHOW_H
#define INPUTCONFSHOW_H

#include <QWidget>

namespace Ui {
class InputConfShow;
}

class InputConfShow : public QWidget
{
    Q_OBJECT

public:
    explicit InputConfShow(QWidget *parent = nullptr);
    ~InputConfShow();

    void setInputConf(QString input_str);

private:
    Ui::InputConfShow *ui;
};

#endif // INPUTCONFSHOW_H
