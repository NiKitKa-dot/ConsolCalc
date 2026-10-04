#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>
#include <QString>

class CsvParser : public QObject
{
    Q_OBJECT

public:
    explicit CsvParser(QObject *parent = nullptr);

public slots:
    // Парсит файл: каждая строка — набор чисел, разделённых , или ;
    void parseFile(const QString &filePath);

signals:
    // Излучается для каждой успешно разобранной строки
    void lineProcessed(int lineNumber, double sum, double average);

    // Излучается после обработки всего файла
    void finished(int totalLines, double grandSum, double grandAverage);

    // Излучается при любой ошибке (не открылся файл, не число и т.д.)
    void errorOccurred(const QString &message);
};

#endif // CSVPARSER_H
