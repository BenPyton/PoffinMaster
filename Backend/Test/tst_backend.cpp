#include <QtTest>
#include "backend.h"
#include "poffin.h"

// add necessary includes here

class Test_Backend : public QObject
{
    Q_OBJECT

public:
    Test_Backend();
    virtual ~Test_Backend() override;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_poffin_data();
    void test_poffin();

private:
    Backend* m_backend {nullptr};
};

Test_Backend::Test_Backend() {}

Test_Backend::~Test_Backend() {}

void Test_Backend::initTestCase()
{
    m_backend = new Backend();
    qDebug() << "Loaded berries: " << m_backend->berries()->count();
    QVERIFY(m_backend->berries()->count() > 0);
}

void Test_Backend::cleanupTestCase()
{
    delete m_backend;
    m_backend = nullptr;
}

using StatArray = std::array<int, 5>;

void Test_Backend::test_poffin_data()
{
    QTest::addColumn<QString>("berryNames");
    QTest::addColumn<Poffin::Type>("resultType");
    QTest::addColumn<int>("resultLevel");
    QTest::addColumn<int>("resultCount");
    QTest::addColumn<int>("resultSmoothness");
    QTest::addColumn<StatArray>("resultStats");

    QTest::newRow("foul") << "oran,cheri,cheri" << Poffin::Type::Foul << /*level:*/ 2 << /*count:*/ 3 << /*smooth:*/ 20 << StatArray{0,0,0,0,0};
    QTest::newRow("overripe") << "oran,pecha" << Poffin::Type::Overripe << /*level:*/ 2 << /*count:*/ 2 << /*smooth:*/ 20 << StatArray{0,0,0,0,0};
    QTest::newRow("1-flavors (spicy)") << "cheri" << Poffin::Type::Normal << /*level:*/ 9 << /*count:*/ 1 << /*smooth:*/ 24 << StatArray{9,0,0,0,0};
    QTest::newRow("2-flavors (sweet-dry)") << "pecha,wiki,persim" << Poffin::Type::Normal << /*level:*/ 18 << /*count:*/ 3 << /*smooth:*/ 20 << StatArray{0,3,18,0,0};
    QTest::newRow("rich (equal stats)") << "oran,cheri,rawst" << Poffin::Type::Rich << /*level:*/ 8 << /*count:*/ 3 << /*smooth:*/ 20 << StatArray{8,8,0,8,0};
    QTest::newRow("rich (different stats)") << "wiki,pecha,iapapa,persim" << Poffin::Type::Rich << /*level:*/ 18 << /*count:*/ 4 << /*smooth:*/ 19 << StatArray{0,3,18,0,13};
}

void Test_Backend::test_poffin()
{
    // Fetch data from the test data table
    QFETCH(QString, berryNames);
    QFETCH(Poffin::Type, resultType);
    QFETCH(int, resultLevel);
    QFETCH(int, resultCount);
    QFETCH(int, resultSmoothness);
    QFETCH(StatArray, resultStats);

    // Retrieve the berry basket from their names
    QList<Berry*> berries;
    QStringList names = berryNames.split(",");
    for (const QString& name : names)
    {
        Berry* berry = m_backend->berries()->getByName(name);
        if (berry != nullptr)
            berries.append(berry);
        else
            qWarning() << "Berry not found:" << name;
    }

    // Cook the poffin
    Poffin poffin;
    poffin.cook(berries);

    // Check resulting poffin
    QCOMPARE(poffin.type(), resultType);
    QCOMPARE(poffin.level(), resultLevel);
    QCOMPARE(poffin.count(), resultCount);
    QCOMPARE(poffin.smoothness(), resultSmoothness);
    for (int i = 0; i < 5; ++i)
        QCOMPARE(poffin.stats()->statValue(i), resultStats[static_cast<size_t>(i)]);
}

QTEST_APPLESS_MAIN(Test_Backend)
#include "tst_backend.moc"
