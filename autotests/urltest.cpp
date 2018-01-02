/*
 * Copyright (c) 2016 Elvis Angelaccio <elvis.angelaccio@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "../src/onedriveurl.h"

#include <QTest>

class UrlTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testOneDriveUrl_data();
    void testOneDriveUrl();
};

QTEST_GUILESS_MAIN(UrlTest)

void UrlTest::testOneDriveUrl_data()
{
    QTest::addColumn<QUrl>("url");
    QTest::addColumn<QString>("expectedAccount");
    QTest::addColumn<QString>("expectedParentPath");
    QTest::addColumn<QStringList>("expectedPathComponents");

    QTest::newRow("root url")
            << QUrl(QStringLiteral("onedrive://"))
            << QString()
            << QString()
            << QStringList();

    QTest::newRow("account root url")
            << QUrl(QStringLiteral("onedrive:///foo@outlook.com"))
            << QStringLiteral("foo@outlook.com")
            << QStringLiteral("/")
            << QStringList {QStringLiteral("foo@outlook.com")};

    QTest::newRow("file in account root")
            << QUrl(QStringLiteral("onedrive:///foo@outlook.com/bar.txt"))
            << QStringLiteral("foo@outlook.com")
            << QStringLiteral("/foo@outlook.com")
            << QStringList {QStringLiteral("foo@outlook.com"), QStringLiteral("bar.txt")};

    QTest::newRow("folder in account root - no trailing slash")
            << QUrl(QStringLiteral("onedrive:///foo@outlook.com/bar"))
            << QStringLiteral("foo@outlook.com")
            << QStringLiteral("/foo@outlook.com")
            << QStringList {QStringLiteral("foo@outlook.com"), QStringLiteral("bar")};
    QTest::newRow("folder in account root - trailing slash")
            << QUrl(QStringLiteral("onedrive:///foo@outlook.com/bar/"))
            << QStringLiteral("foo@outlook.com")
            << QStringLiteral("/foo@outlook.com")
            << QStringList {QStringLiteral("foo@outlook.com"), QStringLiteral("bar")};

    QTest::newRow("file in subfolder")
            << QUrl(QStringLiteral("onedrive:///foo@outlook.com/bar/baz.txt"))
            << QStringLiteral("foo@outlook.com")
            << QStringLiteral("/foo@outlook.com/bar")
            << QStringList {QStringLiteral("foo@outlook.com"), QStringLiteral("bar"), QStringLiteral("baz.txt")};
}

void UrlTest::testOneDriveUrl()
{
    QFETCH(QUrl, url);
    QFETCH(QString, expectedAccount);
    QFETCH(QString, expectedParentPath);
    QFETCH(QStringList, expectedPathComponents);

    const auto onedriveUrl = OneDriveUrl(url);

    QCOMPARE(onedriveUrl.account(), expectedAccount);
    QCOMPARE(onedriveUrl.parentPath(), expectedParentPath);
    QCOMPARE(onedriveUrl.pathComponents(), expectedPathComponents);

    if (expectedPathComponents.isEmpty()) {
        QVERIFY(onedriveUrl.isRoot());
    } else if (expectedPathComponents.count() == 1) {
        QVERIFY(onedriveUrl.isAccountRoot());
    }
}

#include "urltest.moc"
