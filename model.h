#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QtSql/QSqlQueryModel>

class Model : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        DateRole = Qt::UserRole + 1,
    };

    explicit Model(QObject *parent = 0);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void reloadData();
};

#endif // MODEL_H
