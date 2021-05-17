#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    void loadNationalityData();

signals:

public slots:
};

#endif // DATAMANAGER_H
