#ifndef QDBFTABLE_H
#define QDBFTABLE_H

#include "qdbf_global.h"

QT_BEGIN_NAMESPACE
class QVariant;
QT_END_NAMESPACE

namespace QDbf {
namespace Internal {

class QDbfTablePrivate;

} // namespace Internal

class QDbfRecord;

class QDbfTable
{
public:
    enum Codepage {
        CodepageNotSet = 0,
        IBM866,
        Windows1251,
        UTF8,
        UnspecifiedCodepage
    };

    enum OpenMode {
        ReadOnly = 0,
        ReadWrite
    };

    enum DbfTableError {
        NoError = 0,
        OpenError,
        ReadError,
        WriteError,
        PermissionsError,
        UnspecifiedError
    };

    QDbfTable();
    explicit QDbfTable(const QString &dbfFileName);
    QDbfTable(const QDbfTable &other);
    bool operator==(const QDbfTable &other) const;
    inline bool operator!=(const QDbfTable &other) const { return !operator==(other); }
    QDbfTable &operator=(const QDbfTable &other);
    ~QDbfTable();

    bool open(const QString &fileName, OpenMode openMode = QDbfTable::ReadOnly);
    bool open(OpenMode openMode = QDbfTable::ReadOnly);

    void close();

    QString fileName() const;

    QDbfTable::OpenMode openMode() const;

    DbfTableError error() const;

    bool setCodepage(QDbfTable::Codepage codepage);
    QDbfTable::Codepage codepage() const;

    bool isOpen() const;
    int size() const;
    int at() const;
    bool previous() const;
    bool next() const;
    bool first() const;
    bool last() const;
    bool seek(int index) const;
    QDbfRecord record() const;
    QVariant value(int index) const;

    bool addRecord();
    bool addRecord(const QDbfRecord &record);
    bool updateRecordInTable(const QDbfRecord &record);
    bool removeRecord(int index);

private:
    Internal::QDbfTablePrivate *d;
};

} // namespace QDbf

QDebug operator<<(QDebug, const QDbf::QDbfTable&);

#endif // QDBFTABLE_H
