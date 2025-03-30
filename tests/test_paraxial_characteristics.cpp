#include <QtTest>

#include <lens.h>

#include <QtNumeric>

static constexpr double EPS = 1e-5;

class TestParaxialCharacteristics : public QObject
{
    Q_OBJECT

  private slots:
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
};

void TestParaxialCharacteristics::test1()
{
    const Lens lens(-50.0, -50.0, 15.0, 15.0, 1.5);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QVERIFY(qFuzzyCompare(p.f.front, -1000.0));
    QVERIFY(qFuzzyCompare(p.f.back, 1000.0));
    QVERIFY(qFuzzyCompare(p.sf.front, -900.0));
    QVERIFY(qFuzzyCompare(p.sf.back, 1100.0));
    QVERIFY(qFuzzyCompare(p.sh.front, 100.0));
    QVERIFY(qFuzzyCompare(p.sh.back, 100.0));
}

void TestParaxialCharacteristics::test2()
{
    const Lens lens(-50.0, 50.0, 10.0, 10.0, 1.518292);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QCOMPARE_LE(fabs(p.f.front - 46.6431239), EPS);
    QCOMPARE_LE(fabs(p.f.back - -46.6431239), EPS);
    QCOMPARE_LE(fabs(p.sf.front - 49.82759145), EPS);
    QCOMPARE_LE(fabs(p.sf.back - -49.82759145), EPS);
    QCOMPARE_LE(fabs(p.sh.front - 3.184467543), EPS);
    QCOMPARE_LE(fabs(p.sh.back - -3.184467543), EPS);
}

void TestParaxialCharacteristics::test3()
{
    const Lens lens(50.0, -50.0, 15.0, 15.0, 1.518292);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QCOMPARE_LE(fabs(p.f.front - -50.83853333), EPS);
    QCOMPARE_LE(fabs(p.f.back - 50.83853333), EPS);
    QCOMPARE_LE(fabs(p.sf.front - -45.63218202), EPS);
    QCOMPARE_LE(fabs(p.sf.back - 45.63218202), EPS);
    QCOMPARE_LE(fabs(p.sh.front - 5.206351304), EPS);
    QCOMPARE_LE(fabs(p.sh.back - -5.206351304), EPS);
}

void TestParaxialCharacteristics::test4()
{
    const Lens lens(-15.0, -50.0, 20.0, 20.0, 1.518292);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QCOMPARE_LE(fabs(p.f.front - 51.36394099), EPS);
    QCOMPARE_LE(fabs(p.f.back - -51.36394099), EPS);
    QCOMPARE_LE(fabs(p.sf.front - 44.3503969), EPS);
    QCOMPARE_LE(fabs(p.sf.back - -74.74242129), EPS);
    QCOMPARE_LE(fabs(p.sh.front - -7.013544089), EPS);
    QCOMPARE_LE(fabs(p.sh.back - -23.3784803), EPS);
}

void TestParaxialCharacteristics::test5()
{
    const Lens lens(15.0, 50.0, 10.0, 10.0, 1.518292);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QCOMPARE_LE(fabs(p.f.front - -37.67048088), EPS);
    QCOMPARE_LE(fabs(p.f.back - 37.67048088), EPS);
    QCOMPARE_LE(fabs(p.sf.front - -40.24235887), EPS);
    QCOMPARE_LE(fabs(p.sf.back - 29.09755425), EPS);
    QCOMPARE_LE(fabs(p.sh.front - -2.571877989), EPS);
    QCOMPARE_LE(fabs(p.sh.back - -8.572926629), EPS);
}

void TestParaxialCharacteristics::test6()
{
    const Lens lens(0.1, 15.0, 10.0, 10.0, 1.518292);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QCOMPARE_LE(fabs(p.f.front - -0.1580308239), EPS);
    QCOMPARE_LE(fabs(p.f.back - 0.1580308239), EPS);
    QCOMPARE_LE(fabs(p.sf.front - -0.1939949695), EPS);
    QCOMPARE_LE(fabs(p.sf.back - -5.236591014), EPS);
    QCOMPARE_LE(fabs(p.sh.front - -0.03596414559), EPS);
    QCOMPARE_LE(fabs(p.sh.back - -5.394621838), EPS);
}

void TestParaxialCharacteristics::test7()
{
    const Lens lens(15.0, 0.1, 10.0, 10.0, 1.518292);
    const ParaxialCharacteristics p = lens.compute_paraxial_characteristics();

    QCOMPARE_LE(fabs(p.f.front - 0.2519618397), EPS);
    QCOMPARE_LE(fabs(p.f.back - -0.2519618397), EPS);
    QCOMPARE_LE(fabs(p.sf.front - 8.853061354), EPS);
    QCOMPARE_LE(fabs(p.sf.back - -0.1946211763), EPS);
    QCOMPARE_LE(fabs(p.sh.front - 8.601099514), EPS);
    QCOMPARE_LE(fabs(p.sh.back - 0.05734066343), EPS);
}

QTEST_APPLESS_MAIN(TestParaxialCharacteristics)

#include "test_paraxial_characteristics.moc"
