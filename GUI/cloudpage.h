#ifndef CLOUDPAGE_H
#define CLOUDPAGE_H

#include <QWidget>

namespace Ui {
class CloudPage;
}

class CloudPage : public QWidget
{
    Q_OBJECT

public:
    explicit CloudPage(QWidget *parent = nullptr);
    ~CloudPage();

private:
    Ui::CloudPage *ui;
};

#endif // CLOUDPAGE_H
