#ifndef TRANSMODELPAGE_H
#define TRANSMODELPAGE_H

#include <QWidget>

namespace Ui {
class TransModelPage;
}

class TransModelPage : public QWidget
{
    Q_OBJECT

public:
    explicit TransModelPage(QWidget *parent = nullptr);
    ~TransModelPage();

private:
    Ui::TransModelPage *ui;
};

#endif // TRANSMODELPAGE_H
