#ifndef EDITCLASSDIALOG_H
#define EDITCLASSDIALOG_H

#include <QDialog>
#include "class.h"

namespace Ui {
class EditClassDialog;
}

class QStringListModel;

class EditClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditClassDialog(const QString &title, QWidget *parent = 0, bool isEditMode = false);
    ~EditClassDialog();

    QString grade() const;
    void setGrade(const QString &grade);

    QString className() const;
    void setClassname(const QString &name);

    QString subject() const;
    void setSubject(const QString &subject);

    QString classroom() const;
    void setClassroom(const QString &room);

    QStringList teachers() const;
    void setTeachers(const QStringList &teachers);

    QStringList students() const;
    void setStudents(const QStringList &students);

    void setClass(const Class &c);
    Class getClass() const;


private slots:
    void onProfileHasChanged();

private:
    void setupConnections();
    void setupDetectEditConnections();
    void toggleOKButton(bool state);

private:
    Ui::EditClassDialog *ui;

    QStringListModel *mModelTeachers;
    QStringListModel *mModelStudents;

    bool mEditMode;

    Class mClass;
};

#endif // EDITCLASSDIALOG_H
