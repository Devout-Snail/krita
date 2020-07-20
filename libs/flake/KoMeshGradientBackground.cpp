#include "KoMeshGradientBackground.h"
#include <KoColorSpaceRegistry.h>
#include <KoMixColorsOp.h>

#include <QRegion>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

#include "KoMeshPatchesRenderer.h"

class KoMeshGradientBackground::Private : public QSharedData
{
public:
    Private()
        : QSharedData()
        , gradient(0)
        , renderer(new KoMeshPatchesRenderer)
    {}

    ~Private() {
        delete gradient;
        delete renderer;
    }

    SvgMeshGradient *gradient;
    QTransform matrix;
    KoMeshPatchesRenderer *renderer;
};

KoMeshGradientBackground::KoMeshGradientBackground(SvgMeshGradient *gradient, const QTransform &matrix)
    : KoShapeBackground()
    , d(new Private)
{
    d->gradient = gradient;
    d->matrix = matrix;
    Q_ASSERT(d->gradient);
}

KoMeshGradientBackground::~KoMeshGradientBackground()
{
}

void KoMeshGradientBackground::paint(QPainter &painter,
                                     KoShapePaintingContext &,
                                     const QPainterPath &fillPath) const
{
    if (!d->gradient || !d->gradient->isValid())   return;
    painter.save();

    QRectF meshBoundingRect = d->gradient->boundingRect();

    if (d->renderer->patchImage()->isNull()) {

        d->renderer->configure(meshBoundingRect, painter.transform());
        SvgMeshArray *mesharray = d->gradient->getMeshArray().data();

        for (int row = 0; row < mesharray->numRows(); ++row) {
            for (int col = 0; col < mesharray->numColumns(); ++col) {
                SvgMeshPatch *patch = mesharray->getPatch(row, col);
                d->renderer->fillPatch(patch, d->gradient->type(), mesharray, row, col);
            }
        }
        // uncomment to debug
        //  d->renderer->patchImage()->save("mesh-patch.png");
    }

    painter.setClipPath(fillPath);

    // patch is to be drawn wrt. to "user" coordinates
    painter.drawImage(meshBoundingRect, *d->renderer->patchImage());

    painter.restore();
}

bool KoMeshGradientBackground::compareTo(const KoShapeBackground *other) const
{
    return false;
}

void KoMeshGradientBackground::fillStyle(KoGenStyle &style, KoShapeSavingContext &context)
{

}

bool KoMeshGradientBackground::loadStyle(KoOdfLoadingContext &context, const QSizeF &shapeSize)
{
    return false;
}
