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

public slots:
    void onSchoolNameChanged(const QString &name);

private:
    void setupConnections();

public slots:
    void initClasses();
    void initStudents();
    void initTeachers();

private:
    Ui::PageHomeForm *ui;

    // QWidget interface
protected:
    void changeEvent(QEvent *e) override;
};

#endif // PAGEHOMEFORM_H
