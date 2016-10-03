/*
 * Copyright (C) 2014 Daniel Vrátil <dvratil@redhat.com>
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

#include "urlhelper.h"

QString UrlHelper::accountFromPath(const QUrl &url)
{
    const QStringList components = pathComponents(url);
    if (components.isEmpty()) {
        return QString();
    }
    return components[0];
}

QStringList UrlHelper::pathComponents(const QString &path)
{
    return path.split(QLatin1Char('/'), QString::SkipEmptyParts);
}

QStringList UrlHelper::pathComponents(const QUrl &url)
{
    return pathComponents(url.adjusted(QUrl::StripTrailingSlash).path());
}

bool UrlHelper::isRoot(const QUrl &url)
{
    return pathComponents(url).length() == 0;
}

bool UrlHelper::isAccountRoot(const QUrl &url)
{
    return pathComponents(url).length() == 1;
}

