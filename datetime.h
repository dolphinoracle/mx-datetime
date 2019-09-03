// MX Date/Time application.
//
//   Copyright (C) 2019 by AK-47
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
// This file is part of mx-datetime.

#ifndef DATETIME_H
#define DATETIME_H

#include <QDialog>
#include <QString>
#include <QByteArray>
#include <QTimer>
#include <QDateTime>
#include <QTimeEdit>
#include <QTableWidgetItem>

namespace Ui {
class MXDateTime;
}

class MXDateTime : public QDialog
{
    Q_OBJECT

public:
    explicit MXDateTime(QWidget *parent = 0);
    ~MXDateTime();

private slots:
    void on_timeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_cmbTimeZone_currentIndexChanged(int index);
    void on_btnClose_clicked();
    void on_btnApply_clicked();
    void on_calendar_clicked(const QDate &date);
    void on_btnReadHardware_clicked();
    void on_btnSystemToHardware_clicked();
    void on_btnHardwareToSystem_clicked();
    void on_btnSyncNow_clicked();
    void on_tblServers_itemSelectionChanged();
    void on_btnServerAdd_clicked();
    void on_btnServerRemove_clicked();
    void on_btnServerMoveUp_clicked();
    void on_btnServerMoveDown_clicked();
    void on_btnAbout_clicked();
    void on_btnHelp_clicked();

private:
    Ui::MXDateTime *ui;
    QTimer *timer;
    qint64 timeDelta = 0;
    int zoneDelta = 0;
    bool is_systemd, is_openrc;
    QByteArray confBaseNTP;
    QByteArray confServers;
    bool enabledNTP;
    bool isHardwareUTC;
    QTableWidgetItem *addServerRow(bool use, const QString &type, const QString &options, const QString &address);
    void moveServerRow(int movement);
    bool timeChanged = false;
    bool calChanging = false;
    bool secUpdating = false;
    void loadSysTimeConfig();
    void saveSysTimeConfig();
    void secUpdate();
    void setClockLock(bool locked);
    bool execute(const QString &cmd, QByteArray *output = nullptr);
};

// QTimeEdit subclassing just to stop the cursor and selection jumping every second.
class MTimeEdit : public QTimeEdit
{
public:
    MTimeEdit(QWidget *parent = 0);
    void updateDateTime(const QDateTime &dateTime);
};

#endif // DATETIME_H
