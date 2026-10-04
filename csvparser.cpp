#include "csvparser.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <QDebug>

CsvParser::CsvParser(QObject *parent)
    : QObject(parent)
{
    qDebug() << "CsvParser created";
}

void CsvParser::parseFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorOccurred(
            QString("Не удалось открыть файл: %1").arg(filePath));
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    int    lineNumber = 0;   // номер строки в файле (с 1)
    int    validLines = 0;   // сколько строк успешно разобрано
    double grandSum   = 0.0; // сумма всех чисел во всём файле
    int    grandCount = 0;   // сколько всего чисел во всём файле

    while (!in.atEnd()) {
        const QString line = in.readLine();
        ++lineNumber;

        const QString trimmed = line.trimmed();
        if (trimmed.isEmpty())
            continue; // пропускаем пустые строки

        // Разделители: запятая или точка с запятой
        QStringList parts = trimmed.split(
            QRegularExpression("[,;]"),
            Qt::SkipEmptyParts);

        double lineSum = 0.0;
        int    count   = 0;
        bool   lineOk  = true;

        for (const QString &tokenRaw : parts) {
            const QString token = tokenRaw.trimmed();
            bool ok = false;
            const double v = token.toDouble(&ok);
            if (!ok) {
                emit errorOccurred(
                    QString("Строка %1: не удалось преобразовать «%2» в число")
                        .arg(lineNumber).arg(token));
                lineOk = false;
                break;
            }
            lineSum += v;
            ++count;
        }

        if (!lineOk || count == 0)
            continue;

        const double lineAvg = lineSum / count;
        ++validLines;
        grandSum   += lineSum;
        grandCount += count;

        emit lineProcessed(lineNumber, lineSum, lineAvg);
    }

    file.close();

    const double grandAvg = (grandCount > 0) ? (grandSum / grandCount) : 0.0;
    emit finished(validLines, grandSum, grandAvg);
}
