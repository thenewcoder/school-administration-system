#ifndef ATTENDANCETABLEWIDGET_H
#define ATTENDANCETABLEWIDGET_H

#include <QTableWidget>

class AttendanceTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit AttendanceTableWidget(QWidget *parent = nullptr);

signals:
    void onRadioButtonToggled();

public:
    QMap<QString, int> getAttendance() const;
    void setAttendance(const QStringList &students, const QMap<QString, int> &attendance = QMap<QString, int>());
};

#endif // ATTENDANCETABLEWIDGET_H
