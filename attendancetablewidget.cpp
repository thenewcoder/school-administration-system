#include "attendancetablewidget.h"

#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>


AttendanceTableWidget::AttendanceTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    QStringList headerLabels;
    headerLabels << tr("Students") << tr("Present") << tr("Absent") << tr("Tardy") <<
                    tr("Absent W/ Excuse") << tr("Tardy W/ Excuse");

    // setup the attendance table widget
    setColumnCount(headerLabels.length());
    setSelectionMode(QAbstractItemView::NoSelection);
    setFocusPolicy(Qt::NoFocus);

    // set headers
    setHorizontalHeaderLabels(headerLabels);
    setColumnWidth(0, 220);
}

QMap<QString, int> AttendanceTableWidget::getAttendance() const
{
    QMap<QString, int> att;

    for (int row = 0; row < rowCount(); ++row)
    {
        // check each radio button if it's checked or not
        for (int col = 1; col < columnCount(); ++col)
        {
            QRadioButton *btn = cellWidget(row, col)->findChild<QRadioButton*>();
            if (btn->isChecked()) // if attendance has been found
            {
                // get the student name
                QString name = item(row, 0)->text();

                // add the key and value
                att.insert(name, col);
            }
        }
    }
    return att;
}

void AttendanceTableWidget::setAttendance(const QStringList &students, const QMap<QString, int> &attendance)
{
    bool takeAttendance = !attendance.isEmpty(); // not empty

    // populate the table widget
    for (int row = 0; row < students.size(); ++row)
    {
        // insert a new row
        insertRow(row);

        // add students
        QString student = students.at(row);
        QTableWidgetItem *item = new QTableWidgetItem(student);
        setItem(row, 0, item);

        // add a radio button for the remaining columns
        QButtonGroup *grp = new QButtonGroup(this);
        int num_columns = columnCount();
        for (int col = 1; col < num_columns; ++col)
        {
            // create the radio button
            QRadioButton *rbtn = new QRadioButton;
            grp->addButton(rbtn);

            // setup connections for the radio buttons
            connect(rbtn, &QRadioButton::toggled, this, [this] {
                        emit onRadioButtonToggled();
                    });

            if (takeAttendance) // TODO: clean this up a bit
            {
                if (attendance.contains(student))
                {
                    int val = attendance.value(student);
                    if (val == col)
                        rbtn->setChecked(true);
                }
            }

            // Create an empty widget to help with adding the radio button
            QWidget *wdg = new QWidget;

            // create a layout for the empty widget and add the radio button
            QHBoxLayout *layout = new QHBoxLayout(wdg);
            layout->addWidget(rbtn);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0,0,0,0);

            // add widget to the cell
            setCellWidget(row, col, wdg);
        }

        // fixes memory leak warning
        if (grp->buttons().count() < 1)
            delete grp;
    }
}
