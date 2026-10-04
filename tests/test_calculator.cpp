#include <QtTest>
#include <QSignalSpy>
#include "calculator.h"

class TestCalculator : public QObject
{
    Q_OBJECT

private slots:
    void testAdd();
    void testSubtract();
    void testMultiply();
    void testDivide();
    void testDivideByZero();
    void testReset();
    void testLcm();
    void testLcmNonPositive();
    void testSignalEmitted();
};

void TestCalculator::testAdd()
{
    Calculator c;
    c.add(2.0, 3.0);
    QCOMPARE(c.result(), 5.0);
    QCOMPARE(c.hasError(), false);
}

void TestCalculator::testSubtract()
{
    Calculator c;
    c.subtract(10.0, 4.0);
    QCOMPARE(c.result(), 6.0);
}

void TestCalculator::testMultiply()
{
    Calculator c;
    c.multiply(6.0, 7.0);
    QCOMPARE(c.result(), 42.0);
}

void TestCalculator::testDivide()
{
    Calculator c;
    c.divide(10.0, 4.0);
    QCOMPARE(c.result(), 2.5);
}

void TestCalculator::testDivideByZero()
{
    Calculator c;
    QSignalSpy errSpy(&c, &Calculator::errorOccurred);

    c.divide(10.0, 0.0);

    QCOMPARE(c.hasError(), true);
    QCOMPARE(errSpy.count(), 1);
}

void TestCalculator::testReset()
{
    Calculator c;
    c.add(2.0, 3.0);
    c.reset();

    QCOMPARE(c.result(), 0.0);
    QCOMPARE(c.hasError(), false);
}

void TestCalculator::testLcm()
{
    Calculator c;
    c.nok(12, 18);
    QCOMPARE(c.result(), 36.0);
    QCOMPARE(c.hasError(), false);
}

void TestCalculator::testLcmNonPositive()
{
    Calculator c;
    QSignalSpy errSpy(&c, &Calculator::errorOccurred);

    c.nok(0, 5);

    QCOMPARE(c.hasError(), true);
    QCOMPARE(errSpy.count(), 1);
}

void TestCalculator::testSignalEmitted()
{
    Calculator c;
    QSignalSpy spy(&c, &Calculator::resultReady);

    c.add(1.0, 1.0);
    c.multiply(2.0, 2.0);

    // Два успешных вычисления → два сигнала
    QCOMPARE(spy.count(), 2);
}

QTEST_MAIN(TestCalculator)
#include "test_calculator.moc"
