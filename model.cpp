#include "model.h"
#include "database.h"

Model::Model(QObject *parent) :
    QSqlQueryModel(parent) {}

QVariant Model::data(const QModelIndex & index, int role) const {
    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> Model::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DateRole] = "date";
    return roles;
}


void Model::reloadData()
{
    this->setQuery("SELECT " TABLE_DATE ", " TABLE_TIME ", " TABLE_RANDOM ", " TABLE_MESSAGE
                    " FROM " TABLE);
}
