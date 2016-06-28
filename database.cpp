#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    this->connectToDataBase();
    for(int i = 0; i < 50; i++){
        QVariantList data;
        int random = qrand();
        data.append(QDate::currentDate());
        data.append(QTime::currentTime());
        data.append(random);
        data.append("Получено сообщение от " + QString::number(random));
        inserIntoTable(data);
    }
}

DataBase::~DataBase()
{

}

void DataBase::connectToDataBase()
{
    if(!QFile("/tmp/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("/tmp/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_DATE      " DATE            NOT NULL,"
                            TABLE_TIME      " TIME            NOT NULL,"
                            TABLE_RANDOM    " INTEGER         NOT NULL,"
                            TABLE_MESSAGE   " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DataBase::inserIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                                             TABLE_TIME ", "
                                             TABLE_RANDOM ", "
                                             TABLE_MESSAGE " ) "
                  "VALUES (:Date, :Time, :Random, :Message )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Random",      data[2].toInt());
    query.bindValue(":Message",     data[3].toString());
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}
