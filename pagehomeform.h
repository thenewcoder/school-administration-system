#ifndef PAGEHOMEFORM_H
#define PAGEHOMEFORM_H

#include <QWidget>

namespace Ui {
class PageHomeForm;
}

class PageHomeForm : public QWidget
{
    Q_OBJECT

public:
    explicit PageHomeForm(QWidget *parent = 0);
    ~PageHomeForm();

private:
    void setupConnections();

public slots:
    void initClasses();
    void initStudents();
    void initTeachers();

private:
    Ui::PageHomeForm *ui;
};

#endif // PAGEHOMEFORM_H
