/*
 * KDE. Krita Project.
 *
 * Copyright (c) 2020 Deif Lou <ginoba@gmail.com>
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "KisScreentoneScreentoneFunctions.h"

#include <cmath>

#include <QStringList>
#include <klocalizedstring.h>

QStringList screentonePatternNames()
{
    return QStringList()
        << i18n("Dots")
        << i18n("Lines");
}

QStringList screentoneShapeNames(int pattern)
{
    if (pattern == KisScreentonePatternType_Dots) {
        return QStringList()
            << i18n("Round")
            << i18n("Ellipse")
            << i18n("Diamond")
            << i18n("Square");
    } else if (pattern == KisScreentonePatternType_Lines) {
        return QStringList()
            << i18n("Straight")
            << i18n("Sine Wave")
            << i18n("Triangular Wave")
            << i18n("Sawtooth Wave")
            << i18n("Curtains");
    }
    
    return QStringList();
}

QStringList screentoneInterpolationNames(int pattern, int shape)
{
    if (pattern == KisScreentonePatternType_Dots) {
        if (shape == KisScreentoneShapeType_RoundDots || shape == KisScreentoneShapeType_EllipseDots) {
            return QStringList()
                << i18n("Linear")
                << i18n("Sinusoidal");
        }
    } else if (pattern == KisScreentonePatternType_Lines) {
        return QStringList()
            << i18n("Linear")
            << i18n("Sinusoidal");
    }

    return QStringList();
}

namespace KisScreentoneScreentoneFunctions {

qreal sin(qreal x)
{
    x = std::cos(x * M_PI);
    return  x * x;
}

qreal triangle(qreal x)
{
    return 1.0 - 2.0 * std::abs(x - std::floor(x + 0.5));
}

qreal sawTooth(qreal x)
{
    constexpr qreal peakXOffset = 0.9;
    constexpr qreal peakYOffset = 0.5;
    x = x - std::floor(x);
    return (x < peakXOffset ? 1.0 / peakXOffset * x : -1.0 / (1.0 - peakXOffset) * (x - 1.0)) * peakYOffset;
}

qreal DotsRoundLinear::operator()(qreal x, qreal y) const
{
    x = triangle(x);
    y = triangle(y);
    return std::sqrt(x * x + y * y) / M_SQRT2;
}

qreal DotsRoundSinusoidal::operator()(qreal x, qreal y) const
{
    return (sin(x) + sin(y)) / 2.;
}

qreal DotsEllipseLinear::operator()(qreal x, qreal y) const
{
    constexpr qreal ellipseRatioX = 0.4 / M_SQRT2;
    constexpr qreal ellipseRatioY = 0.6 / M_SQRT2;
    x = triangle(x) * ellipseRatioX;
    y = triangle(y) * ellipseRatioY;
    return std::sqrt(x * x + y * y) * M_SQRT2;
}

qreal DotsEllipseSinusoidal::operator()(qreal x, qreal y) const
{
    constexpr qreal ellipseRatioX = 0.4 * 2.0;
    constexpr qreal ellipseRatioY = 0.6 * 2.0;
    x = sin(x) * ellipseRatioX;
    y = sin(y) * ellipseRatioY;
    return (x + y) / 2.;
}

qreal DotsDiamond::operator()(qreal x, qreal y) const
{
    return (triangle(x) + triangle(y)) / 2.;
}

qreal DotsSquare::operator()(qreal x, qreal y) const
{
    return std::max(triangle(x), triangle(y));
}

qreal LinesStraightLinear::operator()(qreal x, qreal y) const
{
    Q_UNUSED(x);
    return triangle(y);
}

qreal LinesStraightSinusoidal::operator()(qreal x, qreal y) const
{
    Q_UNUSED(x);
    return sin(y);
}

qreal LinesSineWaveLinear::operator()(qreal x, qreal y) const
{
    return triangle(y + sin(x));
}

qreal LinesSineWaveSinusoidal::operator()(qreal x, qreal y) const
{
    return sin(y + sin(x));
}

qreal LinesTriangularWaveLinear::operator()(qreal x, qreal y) const
{
    return triangle(y + triangle(x));
}

qreal LinesTriangularWaveSinusoidal::operator()(qreal x, qreal y) const
{
    return sin(y + triangle(x));
}

qreal LinesSawToothWaveLinear::operator()(qreal x, qreal y) const
{
    return triangle(y + sawTooth(x));
}

qreal LinesSawToothWaveSinusoidal::operator()(qreal x, qreal y) const
{
    return sin(y + sawTooth(x));
}

qreal LinesCurtainsLinear::operator()(qreal x, qreal y) const
{
    x = triangle(x);
    return triangle(y + x * x);
}

qreal LinesCurtainsSinusoidal::operator()(qreal x, qreal y) const
{
    x = triangle(x);
    return sin(y + x * x);
}

}
