#ifndef ATTENDANCETABLEWIDGET_H
#define ATTENDANCETABLEWIDGET_H

#include <QTableWidget>

class Attendance;

class AttendanceTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit AttendanceTableWidget(QWidget *parent = nullptr);

signals:
    void onRadioButtonToggled();

public:
    QVector<Attendance> getAttendance() const;
    void setAttendance(const QVector<Attendance> &records);
};

#endif // ATTENDANCETABLEWIDGET_H
