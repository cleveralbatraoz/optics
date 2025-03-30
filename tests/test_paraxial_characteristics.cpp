#include <QtTest>

#include <lens.h>

#include <QtNumeric>

#include <limits>

static constexpr double EPS = std::numeric_limits<double>::epsilon();

class TestParaxialCharacteristics : public QObject
{
    Q_OBJECT

  private slots:
    void test1();
};

void TestParaxialCharacteristics::test1()
{
    Lens lens(-50.0, -50.0, 15.0, 15.0, 1.5);
    ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QVERIFY(qFuzzyCompare(p.f.front, -1000.0));
    QVERIFY(qFuzzyCompare(p.f.back, 1000.0));
    QVERIFY(qFuzzyCompare(p.sf.front, -900.0));
    QVERIFY(qFuzzyCompare(p.sf.back, 1100.0));
    QVERIFY(qFuzzyCompare(p.sh.front, 100.0));
    QVERIFY(qFuzzyCompare(p.sh.back, 100.0));
}

QTEST_APPLESS_MAIN(TestParaxialCharacteristics)

#include "test_paraxial_characteristics.moc"
