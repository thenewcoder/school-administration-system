#include "attendancetablewidget.h"

#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>

#include "attendance.h"


AttendanceTableWidget::AttendanceTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    QStringList headerLabels;
    headerLabels << tr("Students") << tr("Present") << tr("Absent") << tr("Tardy") <<
                    tr("Absent W/ Excuse") << tr("Tardy W/ Excuse") << tr("Remarks");

    // setup the attendance table widget
    setColumnCount(headerLabels.length());
    setSelectionMode(QAbstractItemView::NoSelection);
    setFocusPolicy(Qt::NoFocus);

    // set headers
    setHorizontalHeaderLabels(headerLabels);
    resizeColumnsToContents();
    setColumnWidth(0, 200);
    const int widthSmallColumns = columnWidth(1)+2;
    setColumnWidth(1, widthSmallColumns);
    setColumnWidth(2, widthSmallColumns);
    setColumnWidth(3, widthSmallColumns);
    setColumnWidth(4, columnWidth(4)+2);
    setColumnWidth(5, columnWidth(4)+2); // same as previous column width
    horizontalHeader()->setStretchLastSection(true);
}

QVector<Attendance> AttendanceTableWidget::getAttendance() const
{
    QVector<Attendance> records;

    for (int row = 0; row < rowCount(); ++row)
    {
        Attendance attendance(item(row, 0)->text());

        // check each radio button if it's checked or not - don't check the remarks column
        for (int col = 1; col < columnCount() - 1; ++col)
        {
            QRadioButton *btn = cellWidget(row, col)->findChild<QRadioButton*>();
            if (btn->isChecked()) // if attendance has been found
            {
                attendance.setAttendanceType(col);
                break;
            }
        }
        attendance.setRemarks(item(row, columnCount()-1)->text());

        records.append(attendance);
    }
    return records;
}

void AttendanceTableWidget::setAttendance(const QVector<Attendance> &records)
{
    // populate the table widget
    for (int row = 0; row < records.size(); ++row)
    {
        // insert a new row
        insertRow(row);

        // add students
        Attendance att = records.at(row);
        QTableWidgetItem *item = new QTableWidgetItem(att.student());
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // non editable
        setItem(row, 0, item);

        // add a radio button for the remaining columns
        QButtonGroup *grp = new QButtonGroup(this);
        int num_columns = columnCount() - 1;  // don't go through the remarks column
        for (int col = 1; col < num_columns; ++col)
        {
            // create the radio button
            QRadioButton *rbtn = new QRadioButton;
            grp->addButton(rbtn);

            // setup connections for the radio buttons
            connect(rbtn, &QRadioButton::toggled, this, [this] {
                        emit onRadioButtonToggled();
                    });

            if (att.attendanceType() != -1) // TODO: clean this up a bit
            {
                if (att.attendanceType() == col)
                    rbtn->setChecked(true);
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

        // add remarks
        item = new QTableWidgetItem(att.remarks());
        setItem(row, columnCount()-1, item);

        // fixes memory leak warning
        if (grp->buttons().count() < 1)
            delete grp;
    }
}
